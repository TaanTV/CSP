int iColor = 0;
// int iMoneyColor = argb(255,255,255,128);

int iInfoBuildCount = 0;

int NeedMoney;

void InitInterface(string iniName)
{
	GameInterface.title = "titleColony";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	PChar.Colony.Interface.UpMenu = "NormalBuilds";
	PChar.Colony.Interface.DownMenu = "ProBuilds";
	PChar.ColonyBuilding.Interface.Nalog = "1";

	PChar.ColonyBuilding.Money.Temp = 0;

	CloseTakeMoneyWindow();
	CloseInformationAboutBuildings();

	SetInformation();
	SetNalogInformation();
	SetMoneyInformation();
	SetColonyInformation();
	SetPopulationInformation();

	//SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("MoneyTempUptade","MoneyTempUptade",0);
	SetEventHandler("TakeMoneyTempUptade","TakeMoneyTempUptade",0);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_SALARY_EXIT);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_SALARY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("MoneyTempUptade","MoneyTempUptade");
	DelEventHandler("TakeMoneyTempUptade","TakeMoneyTempUptade");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "STORE_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("Store");
			}
		break;

		case "SHIPYARD_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("Shipyard");
			}
		break;

		case "TAVERN_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("Tavern");
			}
		break;

		case "BANK_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("Bank");
			}
		break;

		case "CHURCH_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("Church");
			}
		break;

		case "HEADPORT_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("Headport");
			}
		break;

		case "EXPIDITION_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("Expidition");
			}
		break;

		case "STOREHOUSE_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("StoreHouse");
			}
		break;

		case "STOREHOUSE_RESIZE":
			if(comName=="activate" || comName=="click")
			{
				ResizeMine("StoreHouse");
			}
		break;

		case "PLANTATION_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("Plantation");
			}
		break;

		case "GOLDMINE_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("GoldMine");
			}
		break;

		case "SILVERMINE_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("SilverMine");
			}
		break;

		case "IRONMINE_OPEN":
			if(comName=="activate" || comName=="click")
			{
				OpenBuild("IronMine");
			}
		break;

		case "CHECK_NORMALBUILDS_LEFT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectBuildsMenu("NormalBuilds");
			}
		break;

		case "CHECK_NORMALBUILDS_RIGHT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectBuildsMenu("Expiditions");
			}
		break;

		case "CHECK_PROBUILDS_LEFT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectBuildsMenu("ProBuilds");
			}
		break;

		case "CHECK_PROBUILDS_RIGHT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectBuildsMenu("Mines");
			}
		break;

		case "GOLDMINE_RESIZE":
			if(comName=="activate" || comName=="click")
			{
				ResizeMine("GoldMine");
			}
		break;

		case "SILVERMINE_RESIZE":
			if(comName=="activate" || comName=="click")
			{
				ResizeMine("SilverMine");
			}
		break;

		case "IRONMINE_RESIZE":
			if(comName=="activate" || comName=="click")
			{
				ResizeMine("IronMine");
			}
		break;

		case "MORALE_UP":
			if(comName=="activate" || comName=="click")
			{
				MoraleUp(sti(PChar.ColonyBuilnding.Population.Morale.Cost));
			}
		break;

		case "MONEY_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectMoneyForTransfer(false, false);
			}
		break;

		case "MONEY_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectMoneyForTransfer(true, false);
			}
		break;

		case "MONEY_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectMoneyForTransfer(false, true);
			}
		break;

		case "MONEY_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectMoneyForTransfer(true, true);
			}
		break;

		case "GIVEGOLD":
			if(comName=="activate" || comName=="click")
			{
				GiveMoneyToCharacter(sti(PChar.ColonyBuilding.Money.Temp));
			}
		break;

		case "SBROS":
			if(comName=="activate" || comName=="click")
			{
				GoldTransferSbros();
			}
		break;

		case "GIVE_ALL":
			if(comName=="activate" || comName=="click")
			{
				GiveMoneyToCharacter(sti(PChar.ColonyBuilding.Money));
			}
		break;

		case "REPAIR_ALL_SHIPS":
			if(comName=="activate" || comName=="click")
			{
				RepairAllShipsInColony();
			}
		break;

		case "NALOG_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectNalog(true);
			}
		break;

		case "NALOG_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectNalog(false);
			}
		break;

		case "INSTALL_HIGH_NALOG":
			if(comName=="activate" || comName=="click")
			{
				InstallNalog(PChar.ColonyBuilding.Interface.Nalog);
			}
		break;

		case "PLANTATION_RESIZE":
			if(comName=="activate" || comName=="click")
			{
				PlantationUp();
			}
		break;

		case "TAKE_MONEY":
			if(comName=="activate" || comName=="click")
			{
				ShowTakeMoneyWindow();
			}
		break;

		case "TAKE_MONEY_LEFT":
			if(comName=="activate" || comName=="click")
			{
				TakeMoneyCheckQty(true, false);
			}
		break;

		case "TAKE_MONEY_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				TakeMoneyCheckQty(false, false);
			}
		break;

		case "TAKE_MONEY_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				TakeMoneyCheckQty(true, true);
			}
		break;

		case "TAKE_MONEY_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				TakeMoneyCheckQty(false, true);
			}
		break;

		case "CANCEL_TAKE_MONEY":
			if(comName=="activate" || comName=="click")
			{
				CloseTakeMoneyWindow();
			}
		break;

		case "OK_TAKE_MONEY":
			if(comName=="activate" || comName=="click")
			{
				TakeMoneyDone();
			}
		break;

		case "BUILDINGS_INFORMATION_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckInfoBuildCount(true);
			}
		break;

		case "BUILDINGS_INFORMATION_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckInfoBuildCount(false);
			}
		break;

		case "BUILDINGS_INFORMATION_EXIT":
			if(comName=="activate" || comName=="click")
			{
				CloseInformationAboutBuildings();
			}
		break;

		case "BUILDINGS_INFORMATION":
			if(comName=="activate" || comName=="click")
			{
				ShowInformationAboutBuildings();
			}
		break;

		case "BUILDINGS_INFORMATION_SELECT_TEXTURE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectTexture(true);
			}
		break;

		case "BUILDINGS_INFORMATION_SELECT_TEXTURE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectTexture(false);
			}
		break;
	}
}

void PlantationUp()
{
	ref PChar = GetMainCharacter();

	int iMoney = sti(PChar.Plantation.ResizeMoney);

	if(CheckAttribute(pchar, "VedekerDiscount")) iMoney = iMoney/2;

	ChangeColonyMoney(-iMoney, false);

	PChar.ColonyBuilding.Plantation.Resize = true;
	PChar.Plantation.Size.Resize.BuildingTime = true;
	PChar.ColonyBuilding.Plantation.Resize.BuildingTime = true;
	LAi_QuestDelay("Plantation_resize", 1.0);

	SetMoneyInformation();
	SetExpiditionInformation();
}

void RepairAllShipsInColony()
{
	ref PChar = GetMainCharacter();

	int cn;
	ref chr;
	for (int i = 0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(PChar, i);
		if(cn != -1)
		{
			chr = &Characters[cn];
			chr.ship.hp = GetCharacterShipHP(chr);
			DeleteAttribute(chr, "ship.blots");

			chr.ship.sp = GetCharacterShipSP(chr);
			DeleteAttribute(chr, "ship.sails");
			RepairMasts(chr);
		}
	}

	//RepairAllShips();
	SetMoneyInformation();
	SetColonyInformation();
}

void GiveMoneyToCharacter(int iMoney)
{
	ref PChar = GetMainCharacter();
	PChar.ColonyBuilding.Money = sti(PChar.ColonyBuilding.Money) - iMoney;
	PChar.ColonyBuilding.Money.Temp = 0;
	AddMoneyToCharacter(PChar, iMoney);
	SetMoneyInformation();
	SetPopulationInformation();
}

void SelectMoneyForTransfer(bool bGive, bool bAll)
{
	ref PChar = GetMainCharacter();

	if(bAll)
	{
		if(!bGive)
		{
			PChar.ColonyBuilding.Money.Temp = 0;
		}
		else
		{
			PChar.ColonyBuilding.Money.Temp = sti(PChar.ColonyBuilding.Money);
		}
	}
	else
	{
		if(bGive)
		{
			PChar.ColonyBuilding.Money.Temp = sti(PChar.ColonyBuilding.Money.Temp) + 500;
		}
		else
		{
			PChar.ColonyBuilding.Money.Temp = sti(PChar.ColonyBuilding.Money.Temp) - 500;
		}
	}

	if(sti(PChar.ColonyBuilding.Money.Temp) > sti(PChar.ColonyBuilding.Money))  { PChar.ColonyBuilding.Money.Temp = sti(PChar.ColonyBuilding.Money); }
	if(sti(PChar.ColonyBuilding.Money.Temp) < 0)  { PChar.ColonyBuilding.Money.Temp = 0; }

	SetMoneyInformation();
}

void GoldTransferSbros()
{
	ref PChar = GetMainCharacter();
	GameInterface.MONEY_STRING.str = 0;
	PChar.ColonyBuilding.Money.Temp = 0;
	SetMoneyInformation();
}

void MoraleUp(int iCost)
{
	ref PChar = GetMainCharacter();
	ChangeColonyMoney(-iCost, false);
	PChar.ColonyBuilding.Population.Morale = sti(PChar.ColonyBuilding.Population.Morale) + 10;
	SetPopulationInformation();
	SetMoneyInformation();
}

void ResizeMine(string sMine)
{
	ref PChar = GetMainCharacter();
	PChar.ColonyBuilding.(sMine).Resize = true;
	PChar.ColonyBuilding.(sMine).Resize.BuildingTime = true;
	PChar.ColonyBuilding.(sMine).Size = "Big";

	int iMoney = sti(PChar.ColonyBuilding.(sMine).ResizeCost);

	if(CheckAttribute(pchar, "VedekerDiscount")) iMoney = sti(iMoney)/2;

	ChangeColonyMoney(-iMoney, false);

	if(sMine == "StoreHouse")
	{
		SetExpiditionInformation();
	}
	else
	{
		SetMinesInformation();
	}

	SetPopulationInformation();
	SetMoneyInformation();

	string sQuest = sMine + "_resize";
	LAi_QuestDelay(sQuest, 0.5);
}

void OpenBuild(string sBuild)
{
	ref PChar = GetMainCharacter();
	PChar.ColonyBuilding.(sBuild) = true;
	PChar.ColonyBuilding.(sBuild).BuildingTime = true;

	if(sBuild == "GoldMine" || sBuild == "SilverMine" || sBuild == "IronMine")
	{
		PChar.Mines.(sBuild) = true;
	}

	ref chr;
	string sCharacter = "Caiman";
	string sModel = "";
	switch(sBuild)
	{
		case "Store": sCharacter += "_trader"; sModel = "trader_" + (rand(15)+1); break;
		case "Shipyard": sCharacter += "_shipyarder"; sModel = "shipowner_" + (rand(15)+1); break;

		case "Tavern":
			sCharacter += "_tavernkeeper"; sModel = "barmen_" + (rand(15)+1);
			Characters[GetCharacterIndex("Caiman_waitress")].model = "girl_" + (rand(8)+1);
			SetRandomNameToCharacter(&Characters[GetCharacterIndex("Caiman_waitress")]);

			sCharacter += "_tavernkeeper"; sModel = "barmen_" + (rand(15)+1);
		break;

		case "Bank": sCharacter += "_usurer"; sModel = "usurer_" + (rand(7)+1); break;
		case "Church": sCharacter += "_Priest"; sModel = "priest_" + (rand(3)+1); break;
		case "HeadPort": sCharacter += "_PortMan"; sModel = "usurer_" + (rand(7)+1); break;
	}

	if(GetCharacterIndex(sCharacter) != -1)
	{
		chr = &Characters[GetCharacterIndex(sCharacter)];
		chr.model = sModel;
		SetRandomNameToCharacter(chr);
	}

	if(sBuild == "Store")
	{
		PChar.ColonyBuilding.AutoPurchaseFirst = true;
	}

	int iMoney = sti(PChar.ColonyBuilding.(sBuild).Cost);

	if(CheckAttribute(pchar, "VedekerDiscount")) iMoney = iMoney/2;

	ChangeColonyMoney(-iMoney, false);
	string sQuest = sBuild + "_build";
	LAi_QuestDelay(sQuest, 0.5);

	if(sBuild == "Shipyard")
	{
		SetColonyInformation();
	}

	if(sBuild == "Expidition" || sBuild == "StoreHouse" || sBuild == "Plantation")
	{
		if(sBuild == "StoreHouse")
		{
			PChar.ColonyBuilding.(sBuild).Size = "Small";
		}

		SetExpiditionInformation();

		if(PChar.Colony.Interface.DownMenu == "Mines")
		{
			SetMinesInformation();
		}

		SetMoneyInformation();
		return;
	}

	if(sBuild == "GoldMine" || sBuild == "SilverMine" || sBuild == "IronMine")
	{
		SetMinesInformation();
		SetMoneyInformation();
		return;
	}

	SetInformation();
	SetPopulationInformation();
}

void SelectBuildsMenu(string sMenu)
{
	switch(sMenu)
	{
		case "NormalBuilds":
			if(PChar.Colony.Interface.UpMenu == "NormalBuilds")
			{
				return;
			}
			GameInterface.pictures.StoreBorder.tex = "BORDER1";
		    	GameInterface.pictures.StoreBorder.pic = "border";

			GameInterface.pictures.StorePicture.tex = GetCurrentTexture();
		    	GameInterface.pictures.StorePicture.pic = "Store";

			GameInterface.pictures.ShipyardBorder.tex = "BORDER1";
		    	GameInterface.pictures.ShipyardBorder.pic = "border";

			GameInterface.pictures.ShipyardPicture.tex = GetCurrentTexture();
		    	GameInterface.pictures.ShipyardPicture.pic = "Shipyard";

			GameInterface.pictures.TavernBorder.tex = "BORDER1";
		    	GameInterface.pictures.TavernBorder.pic = "border";

			GameInterface.pictures.TavernPicture.tex = GetCurrentTexture();
		    	GameInterface.pictures.TavernPicture.pic = "Tavern";

		    	GameInterface.strings.NormalBuildHeader = GetConvertStrWithReplace("Variable_Colony_1", "Interface.txt", "#space#", " ");

			GameInterface.strings.ExpiditionHeader = "";
			GameInterface.strings.ExpiditionStatus = "";
			GameInterface.strings.ExpiditionCost = "";
			GameInterface.pictures.ExpiditionBorder.tex = "";
		    	GameInterface.pictures.ExpiditionBorder.pic = "";
			GameInterface.pictures.ExpiditionPicture.tex = "";
		    	GameInterface.pictures.ExpiditionPicture.pic = "";
			GameInterface.strings.StoreHouseHeader = "";
			GameInterface.strings.StoreHouseStatus = "";
			GameInterface.strings.StoreHouseCost = "";
			GameInterface.strings.StoreHouseResizeCost = "";
			GameInterface.pictures.StoreHouseBorder.tex = "";
		    	GameInterface.pictures.StoreHouseBorder.pic = "";
			GameInterface.pictures.StoreHousePicture.tex = "";
		    	GameInterface.pictures.StoreHousePicture.pic = "";
			GameInterface.strings.PlantationHeader = "";
			GameInterface.strings.PlantationStatus = "";
			GameInterface.strings.PlantationCost = "";
			GameInterface.strings.PlantationResizeCost = "";
			GameInterface.pictures.PlantationBorder.tex = "";
		    	GameInterface.pictures.PlantationBorder.pic = "";
			GameInterface.pictures.PlantationPicture.tex = "";
		    	GameInterface.pictures.PlantationPicture.pic = "";

		    	GameInterface.strings.StoreHeader = GetConvertStrWithReplace("Variable_Colony_2", "Interface.txt", "#space#", " ");
			string sStoreStatus = "";

			if(PChar.ColonyBuilding.Store == false)
			{
				if(PChar.ColonyBuilding.Store.BuildingTime == true)
				{
					sStoreStatus = GetConvertStrWithReplace("Variable_Colony_3", "Interface.txt", "#space#", " ");
					iColor = argb(255,255,255,255);
				}
				else
				{
					sStoreStatus = GetConvertStrWithReplace("Variable_Colony_4", "Interface.txt", "#space#", " ");
					iColor = argb(255,255,128,128);
				}
			}
			else
			{
				sStoreStatus = GetConvertStrWithReplace("Variable_Colony_5", "Interface.txt", "#space#", " ");
				iColor = argb(255,128,255,128);
			}

		    	GameInterface.strings.StoreStatus = GetConvertStrWithReplace("Variable_Colony_6", "Interface.txt", "#space#", " ") + sStoreStatus;

			if(PChar.ColonyBuilding.Store == false)
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) GameInterface.strings.StoreCost = GetConvertStrWithReplace("Variable_Colony_7", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Store.Cost)/2;
				else GameInterface.strings.StoreCost = GetConvertStrWithReplace("Variable_Colony_8", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Store.Cost);
			}
			else
			{
				GameInterface.strings.StoreCost = "";
			}

			if(PChar.ColonyBuilding.Store == true)
			{
				SetSelectable("STORE_OPEN", false);
			}
			else
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Store.Cost/2;
				else NeedMoney = PChar.ColonyBuilding.Store.Cost;

				if(GetMyColonyMoney() < sti(NeedMoney))
				{
					SetSelectable("STORE_OPEN", false);
				}
				else
				{
					SetSelectable("STORE_OPEN", true);
				}
			}

			//-------------------------------------------------------------------------------------------------

		    	GameInterface.strings.ShipyardHeader = GetConvertStrWithReplace("Variable_Colony_9", "Interface.txt", "#space#", " ");
			string sShipyardStatus = "";

			if(PChar.ColonyBuilding.Shipyard == false)
			{
				sShipyardStatus = GetConvertStrWithReplace("Variable_Colony_10", "Interface.txt", "#space#", " ");
				iColor = argb(255,255,128,128);
			}
			else
			{
				sShipyardStatus = GetConvertStrWithReplace("Variable_Colony_11", "Interface.txt", "#space#", " ");
				iColor = argb(255,128,255,128);
			}

		    	GameInterface.strings.ShipyardStatus = GetConvertStrWithReplace("Variable_Colony_12", "Interface.txt", "#space#", " ") + sShipyardStatus;

			if(PChar.ColonyBuilding.Shipyard == false)
			{
				GameInterface.strings.ShipyardCost = GetConvertStrWithReplace("Variable_Colony_13", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Shipyard.Cost);
			}
			else
			{
				GameInterface.strings.ShipyardCost = "";
			}

			if(PChar.ColonyBuilding.Shipyard == true)
			{
				SetSelectable("SHIPYARD_OPEN", false);
			}
			else
			{
				if(PChar.ColonyBuilding.Stage == "0" || PChar.ColonyBuilding.Stage == "1")
				{
					SetSelectable("SHIPYARD_OPEN", false);
				}
				else
				{
					if(GetMyColonyMoney() < sti(PChar.ColonyBuilding.Shipyard.Cost))
					{
						SetSelectable("SHIPYARD_OPEN", false);
					}
					else
					{
						SetSelectable("SHIPYARD_OPEN", true);
					}
				}
			}

			//-------------------------------------------------------------------------------------------------

		    	GameInterface.strings.TavernHeader = GetConvertStrWithReplace("Variable_Colony_14", "Interface.txt", "#space#", " ");
			string sTavernStatus = "";

			if(PChar.ColonyBuilding.Tavern == false)
			{
				sTavernStatus = GetConvertStrWithReplace("Variable_Colony_15", "Interface.txt", "#space#", " ");
				iColor = argb(255,255,128,128);
			}
			else
			{
				sTavernStatus = GetConvertStrWithReplace("Variable_Colony_16", "Interface.txt", "#space#", " ");
				iColor = argb(255,128,255,128);
			}

		    	GameInterface.strings.TavernStatus = GetConvertStrWithReplace("Variable_Colony_17", "Interface.txt", "#space#", " ") + sTavernStatus;

			if(PChar.ColonyBuilding.Tavern == false)
			{
				GameInterface.strings.TavernCost = GetConvertStrWithReplace("Variable_Colony_18", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Tavern.Cost);
			}
			else
			{
				GameInterface.strings.TavernCost = "";
			}

			if(PChar.ColonyBuilding.Tavern == true)
			{
				SetSelectable("TAVERN_OPEN", false);
			}
			else
			{
				if(GetMyColonyMoney() < sti(PChar.ColonyBuilding.Tavern.Cost))
				{
					SetSelectable("TAVERN_OPEN", false);
				}
				else
				{
					SetSelectable("TAVERN_OPEN", true);
				}
			}

			SetNodeUsing("STORE_OPEN", true);
			SetNodeUsing("SHIPYARD_OPEN", true);
			SetNodeUsing("TAVERN_OPEN", true);
			SetNodeUsing("EXPIDITION_OPEN", false);
			SetNodeUsing("STOREHOUSE_OPEN", false);
			SetNodeUsing("STOREHOUSE_RESIZE", false);
			SetNodeUsing("PLANTATION_OPEN", false);
			SetNodeUsing("PLANTATION_RESIZE", false);

			PChar.Colony.Interface.UpMenu = "NormalBuilds";
		break;

		//---------------------------------------------------------------------------------------------------------

		case "Expiditions":
			if(PChar.Colony.Interface.UpMenu == "Expiditions")
			{
				return;
			}

			GameInterface.pictures.StoreBorder.tex = "";
		    	GameInterface.pictures.StoreBorder.pic = "";
			GameInterface.pictures.StorePicture.tex = "";
		    	GameInterface.pictures.StorePicture.pic = "";

			GameInterface.pictures.ShipyardBorder.tex = "";
		    	GameInterface.pictures.ShipyardBorder.pic = "";
			GameInterface.pictures.ShipyardPicture.tex = "";
		    	GameInterface.pictures.ShipyardPicture.pic = "";

			GameInterface.pictures.TavernBorder.tex = "";
		    	GameInterface.pictures.TavernBorder.pic = "";
			GameInterface.pictures.TavernPicture.tex = "";
		    	GameInterface.pictures.TavernPicture.pic = "";

		    	iColor = 0;

		    	GameInterface.strings.NormalBuildHeader = GetConvertStrWithReplace("Variable_Colony_19", "Interface.txt", "#space#", " ");

			GameInterface.strings.StoreHeader = "";
			GameInterface.strings.StoreStatus = "";
			GameInterface.strings.StoreCost = "";
			GameInterface.strings.ShipyardHeader = "";
			GameInterface.strings.ShipyardStatus = "";
			GameInterface.strings.ShipyardCost = "";
			GameInterface.strings.TavernHeader = "";
			GameInterface.strings.TavernStatus = "";
			GameInterface.strings.TavernCost = "";

			SetNodeUsing("STOREHOUSE_OPEN", true);
			SetNodeUsing("PLANTATION_OPEN", true);

			CreateImage("ExpiditionBorder", "BORDER1", "border", 350,110,485,210);
			CreateImage("ExpiditionPicture", GetCurrentTexture(), "Expedition", 350,110,485,210);
			CreateString(true,"ExpiditionHeader", GetConvertStrWithReplace("Variable_Colony_20", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 410,87,SCRIPT_ALIGN_CENTER,1.0);

			string sExpiditionStatus = "";

			if(PChar.ColonyBuilding.Expidition == false)
			{
				sExpiditionStatus = GetConvertStrWithReplace("Variable_Colony_21", "Interface.txt", "#space#", " ");
				iColor = argb(255,255,128,128);
			}
			else
			{
				sExpiditionStatus = GetConvertStrWithReplace("Variable_Colony_22", "Interface.txt", "#space#", " ");
				iColor = argb(255,128,255,128);
			}

			CreateString(true,"ExpiditionStatus", GetConvertStrWithReplace("Variable_Colony_23", "Interface.txt", "#space#", " ") + sExpiditionStatus, FONT_NORMAL, iColor, 355,218,SCRIPT_ALIGN_LEFT, 1.0);

			if(PChar.ColonyBuilding.Expidition == false)
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"ExpiditionCost", GetConvertStrWithReplace("Variable_Colony_24", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Expidition.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 355,238,SCRIPT_ALIGN_LEFT,1.0);
				else CreateString(true,"ExpiditionCost", GetConvertStrWithReplace("Variable_Colony_25", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Expidition.Cost), FONT_NORMAL, COLOR_NORMAL, 355,238,SCRIPT_ALIGN_LEFT,1.0);
			}
			else
			{
				GameInterface.strings.ExpiditionCost = "";
			}

			if(PChar.ColonyBuilding.Expidition == true)
			{
				SetSelectable("EXPIDITION_OPEN", false);
			}
			else
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Expidition.Cost/2;
				else NeedMoney = PChar.ColonyBuilding.Expidition.Cost;

				if(PChar.ColonyBuilding.Stage == "2" || PChar.ColonyBuilding.Stage == "3")
				{
					if(GetMyColonyMoney() < sti(NeedMoney))
					{
						SetSelectable("EXPIDITION_OPEN", false);
					}
					else
					{
						SetSelectable("EXPIDITION_OPEN", true);
					}
				}
				else
				{
					SetSelectable("EXPIDITION_OPEN", false);
				}
			}

			//---------------------------------------------------------------------------------------------------------------------------------

			CreateImage("StoreHouseBorder", "BORDER1", "border", 495,110,630,210);
			CreateImage("StoreHousePicture", GetCurrentTexture(), "StoreHouse", 495,110,630,210);
			CreateString(true,"StoreHouseHeader", GetConvertStrWithReplace("Variable_Colony_26", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 560,87,SCRIPT_ALIGN_CENTER,1.0);

			string sStoreHouseStatus = "";

			if(PChar.ColonyBuilding.StoreHouse == false)
			{
				sStoreHouseStatus = GetConvertStrWithReplace("Variable_Colony_27", "Interface.txt", "#space#", " ");
				iColor = argb(255,255,128,128);
			}
			else
			{
				if(PChar.ColonyBuilding.StoreHouse.Resize == true)
				{
					sStoreHouseStatus = GetConvertStrWithReplace("Variable_Colony_28", "Interface.txt", "#space#", " ");
				}
				else
				{
					sStoreHouseStatus = GetConvertStrWithReplace("Variable_Colony_29", "Interface.txt", "#space#", " ");
				}
				iColor = argb(255,128,255,128);
			}

			CreateString(true,"StoreHouseStatus", GetConvertStrWithReplace("Variable_Colony_30", "Interface.txt", "#space#", " ") + sStoreHouseStatus, FONT_NORMAL, iColor, 500,218,SCRIPT_ALIGN_LEFT, 1.0);

			if(PChar.ColonyBuilding.StoreHouse == false)
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"StoreHouseCost", GetConvertStrWithReplace("Variable_Colony_31", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.StoreHouse.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 500,238,SCRIPT_ALIGN_LEFT,1.0);
				else CreateString(true,"StoreHouseCost", GetConvertStrWithReplace("Variable_Colony_32", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.StoreHouse.Cost), FONT_NORMAL, COLOR_NORMAL, 500,238,SCRIPT_ALIGN_LEFT,1.0);
			}
			else
			{
				GameInterface.strings.StoreHouseCost = "";
			}

			if(PChar.ColonyBuilding.StoreHouse == true)
			{
				SetSelectable("STOREHOUSE_OPEN", false);
			}
			else
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.StoreHouse.Cost/2;
				else NeedMoney = PChar.ColonyBuilding.StoreHouse.Cost;

				if(GetMyColonyMoney() < sti(NeedMoney))
				{
					SetSelectable("STOREHOUSE_OPEN", false);
				}
				else
				{
					SetSelectable("STOREHOUSE_OPEN", true);
				}
			}

			if(PChar.ColonyBuilding.StoreHouse == true)
			{
				SetNodeUsing("STOREHOUSE_OPEN", false);
				SetNodeUsing("STOREHOUSE_RESIZE", true);

				if(PChar.ColonyBuilding.StoreHouse.Resize == false)
				{
					if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"StoreHouseResizeCost", GetConvertStrWithReplace("Variable_Colony_33", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.StoreHouse.ResizeCost)/2, FONT_NORMAL, COLOR_NORMAL, 500,238,SCRIPT_ALIGN_LEFT,1.0);
					else CreateString(true,"StoreHouseResizeCost", GetConvertStrWithReplace("Variable_Colony_34", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.StoreHouse.ResizeCost), FONT_NORMAL, COLOR_NORMAL, 500,238,SCRIPT_ALIGN_LEFT,1.0);
				}
				else
				{
					GameInterface.strings.StoreHouseResizeCost = "";
				}

				if(PChar.ColonyBuilding.Stage == "2" || PChar.ColonyBuilding.Stage == "3")
				{
					if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.StoreHouse.ResizeCost/2;
					else NeedMoney = PChar.ColonyBuilding.StoreHouse.ResizeCost;

					if(GetMyColonyMoney() >= sti(NeedMoney) && PChar.ColonyBuilding.StoreHouse.BuildingTime == false)
					{
						SetSelectable("STOREHOUSE_RESIZE", true);
					}
					else
					{
						SetSelectable("STOREHOUSE_RESIZE", false);
					}
				}
				else
				{
					SetSelectable("STOREHOUSE_RESIZE", false);
				}
			}

			if(PChar.ColonyBuilding.StoreHouse.Resize == true)
			{
				SetSelectable("STOREHOUSE_RESIZE", false);
			}

			//-----------------------------------------------------------------------------

			CreateImage("PlantationBorder", "BORDER1", "border", 640,110,775,210);
			CreateImage("PlantationPicture", GetCurrentTexture(), "Plantation", 640,110,775,210);
			CreateString(true,"PlantationHeader", GetConvertStrWithReplace("Variable_Colony_35", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 705,87,SCRIPT_ALIGN_CENTER,1.0);

			string sPlantationStatus = "";

			if(PChar.ColonyBuilding.Plantation == false)
			{
				sPlantationStatus = GetConvertStrWithReplace("Variable_Colony_36", "Interface.txt", "#space#", " ");
				iColor = argb(255,255,128,128);
			}
			else
			{
				if(PChar.ColonyBuilding.Plantation.Resize == true && PChar.ColonyBuilding.Plantation.Resize.BuildingTime == false)
				{
					sPlantationStatus = GetConvertStrWithReplace("Variable_Colony_37", "Interface.txt", "#space#", " ");
				}
				else
				{
					sPlantationStatus = GetConvertStrWithReplace("Variable_Colony_38", "Interface.txt", "#space#", " ");
				}

				iColor = argb(255,128,255,128);
			}

			CreateString(true,"PlantationStatus", GetConvertStrWithReplace("Variable_Colony_39", "Interface.txt", "#space#", " ") + sPlantationStatus, FONT_NORMAL, iColor, 645,218,SCRIPT_ALIGN_LEFT, 1.0);

			if(PChar.ColonyBuilding.Plantation == false)
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"PlantationCost", GetConvertStrWithReplace("Variable_Colony_40", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Plantation.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 645,238,SCRIPT_ALIGN_LEFT,1.0);
				else CreateString(true,"PlantationCost", GetConvertStrWithReplace("Variable_Colony_41", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Plantation.Cost), FONT_NORMAL, COLOR_NORMAL, 645,238,SCRIPT_ALIGN_LEFT,1.0);
			}
			else
			{
				GameInterface.strings.PlantationCost = "";
			}

			if(PChar.ColonyBuilding.Plantation == true)
			{
				SetSelectable("PLANTATION_OPEN", false);
			}
			else
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Plantation.Cost/2;
				else NeedMoney = PChar.ColonyBuilding.Plantation.Cost;

				if(PChar.ColonyBuilding.Expidition == true && PChar.ColonyBuilding.Expidition.BuildingTime == false)
				{
					if(GetMyColonyMoney() < sti(NeedMoney))
					{
						SetSelectable("PLANTATION_OPEN", false);
					}
					else
					{
						SetSelectable("PLANTATION_OPEN", true);
					}
				}
				else
				{
					SetSelectable("PLANTATION_OPEN", false);
				}
			}


			if(PChar.ColonyBuilding.Plantation == true)
			{
				SetNodeUsing("PLANTATION_OPEN", false);
				SetNodeUsing("PLANTATION_RESIZE", true);

				if(PChar.ColonyBuilding.Plantation.Resize == false && PChar.ColonyBuilding.Plantation.Resize.BuildingTime == false)
				{
					if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"PlantationResizeCost", GetConvertStrWithReplace("Variable_Colony_42", "Interface.txt", "#space#", " ") + sti(PChar.Plantation.ResizeMoney)/2, FONT_NORMAL, COLOR_NORMAL, 645,238,SCRIPT_ALIGN_LEFT,1.0);
					else CreateString(true,"PlantationResizeCost", GetConvertStrWithReplace("Variable_Colony_43", "Interface.txt", "#space#", " ") + sti(PChar.Plantation.ResizeMoney), FONT_NORMAL, COLOR_NORMAL, 645,238,SCRIPT_ALIGN_LEFT,1.0);
				}
				else
				{
					GameInterface.strings.PlantationResizeCost = "";
				}

			    if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.Plantation.ResizeMoney/2;
				else NeedMoney = PChar.Plantation.ResizeMoney;

				if(GetMyColonyMoney() >= sti(NeedMoney) && PChar.ColonyBuilding.Plantation.BuildingTime == false)
				{
					SetSelectable("PLANTATION_RESIZE", true);
				}
				else
				{
					SetSelectable("PLANTATION_RESIZE", false);
				}
			}

			if(PChar.ColonyBuilding.Plantation.Resize == true || PChar.ColonyBuilding.Plantation.Resize.BuildingTime == true)
			{
				SetSelectable("PLANTATION_RESIZE", false);
			}

			//-----------------------------------------------------------------------------

			SetNodeUsing("STORE_OPEN", false);
			SetNodeUsing("SHIPYARD_OPEN", false);
			SetNodeUsing("TAVERN_OPEN", false);
			SetNodeUsing("EXPIDITION_OPEN", true);

			PChar.Colony.Interface.UpMenu = "Expidition";
		break;

		case "ProBuilds":
			if(PChar.Colony.Interface.DownMenu == "ProBuilds")
			{
				return;
			}
			GameInterface.pictures.BankBorder.tex = "BORDER1";
			GameInterface.pictures.BankBorder.pic = "border";

			GameInterface.pictures.BankPicture.tex = GetCurrentTexture();
			GameInterface.pictures.BankPicture.pic = "Bank";

			GameInterface.pictures.ChurchBorder.tex = "BORDER1";
			GameInterface.pictures.ChurchBorder.pic = "border";

			GameInterface.pictures.ChurchPicture.tex = GetCurrentTexture();
			GameInterface.pictures.ChurchPicture.pic = "Church";

			GameInterface.pictures.HeadPortBorder.tex = "BORDER1";
			GameInterface.pictures.HeadPortBorder.pic = "border";

			GameInterface.pictures.HeadportPicture.tex = GetCurrentTexture();
			GameInterface.pictures.HeadportPicture.pic = "HeadPort";

		    	GameInterface.strings.ProBuildHeader = GetConvertStrWithReplace("Variable_Colony_44", "Interface.txt", "#space#", " ");

			GameInterface.strings.GoldMineHeader = "";
			GameInterface.strings.GoldMineStatus = "";
			GameInterface.strings.GoldMineCost = "";
			GameInterface.strings.GoldMineResizeCost = "";
			GameInterface.strings.SilverMineHeader = "";
			GameInterface.strings.SilverMineStatus = "";
			GameInterface.strings.SilverMineCost = "";
			GameInterface.strings.SilverMineResizeCost = "";
			GameInterface.strings.IronMineHeader = "";
			GameInterface.strings.IronMineStatus = "";
			GameInterface.strings.IronMineCost = "";
			GameInterface.strings.IronMineResizeCost = "";

		    GameInterface.strings.BankHeader = GetConvertStrWithReplace("Variable_Colony_45", "Interface.txt", "#space#", " ");
			string sBankStatus = "";

			if(PChar.ColonyBuilding.Bank == false)
			{
				sBankStatus = GetConvertStrWithReplace("Variable_Colony_46", "Interface.txt", "#space#", " ");
				iColor = argb(255,255,128,128);
			}
			else
			{
				sBankStatus = GetConvertStrWithReplace("Variable_Colony_47", "Interface.txt", "#space#", " ");
				iColor = argb(255,128,255,128);
			}

		    	GameInterface.strings.BankStatus = GetConvertStrWithReplace("Variable_Colony_48", "Interface.txt", "#space#", " ") + sBankStatus;

			if(PChar.ColonyBuilding.Bank == false)
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) GameInterface.strings.BankCost = GetConvertStrWithReplace("Variable_Colony_49", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Bank.Cost)/2;
				else GameInterface.strings.BankCost = GetConvertStrWithReplace("Variable_Colony_50", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Bank.Cost);
			}
			else
			{
				GameInterface.strings.BankCost = "";
			}

			if(PChar.ColonyBuilding.Bank == true)
			{
				SetSelectable("BANK_OPEN", false);
			}
			else
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Bank.Cost/2;
				else NeedMoney = PChar.ColonyBuilding.Bank.Cost;

				if(GetMyColonyMoney() > sti(NeedMoney) && sti(PChar.ColonyBuilding.Stage) > 1)
				{
					SetSelectable("BANK_OPEN", true);
				}
				else
				{
					SetSelectable("BANK_OPEN", false);
				}
			}

			//-------------------------------------------------------------------------------------------------

		    	GameInterface.strings.ChurchHeader = GetConvertStrWithReplace("Variable_Colony_51", "Interface.txt", "#space#", " ");
			string sChurchStatus = "";

			if(PChar.ColonyBuilding.Church == false)
			{
				sChurchStatus = GetConvertStrWithReplace("Variable_Colony_52", "Interface.txt", "#space#", " ");
				iColor = argb(255,255,128,128);
			}
			else
			{
				sChurchStatus = GetConvertStrWithReplace("Variable_Colony_53", "Interface.txt", "#space#", " ");
				iColor = argb(255,128,255,128);
			}

		    	GameInterface.strings.ChurchStatus = GetConvertStrWithReplace("Variable_Colony_54", "Interface.txt", "#space#", " ") + sChurchStatus;

			if(PChar.ColonyBuilding.Church == false)
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) GameInterface.strings.ChurchCost = GetConvertStrWithReplace("Variable_Colony_55", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Church.Cost)/2;
				else GameInterface.strings.ChurchCost = GetConvertStrWithReplace("Variable_Colony_56", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Church.Cost);
			}
			else
			{
				GameInterface.strings.ChurchCost = "";
			}

			if(PChar.ColonyBuilding.Church == true)
			{
				SetSelectable("CHURCH_OPEN", false);
			}
			else
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Church.Cost/2;
				else NeedMoney = PChar.ColonyBuilding.Church.Cost;

				if(GetMyColonyMoney() > sti(NeedMoney) && sti(PChar.ColonyBuilding.Stage) > 1)
				{
					SetSelectable("CHURCH_OPEN", true);
				}
				else
				{
					SetSelectable("CHURCH_OPEN", false);
				}
			}

			//-------------------------------------------------------------------------------------------------

		    	GameInterface.strings.HeadportHeader = GetConvertStrWithReplace("Variable_Colony_57", "Interface.txt", "#space#", " ");
			string sHeadportStatus = "";

			if(PChar.ColonyBuilding.Headport == false)
			{
				sHeadportStatus = GetConvertStrWithReplace("Variable_Colony_58", "Interface.txt", "#space#", " ");
				iColor = argb(255,255,128,128);
			}
			else
			{
				sHeadportStatus = GetConvertStrWithReplace("Variable_Colony_59", "Interface.txt", "#space#", " ");
				iColor = argb(255,128,255,128);
			}

		    	GameInterface.strings.HeadportStatus = GetConvertStrWithReplace("Variable_Colony_60", "Interface.txt", "#space#", " ") + sHeadportStatus;

			if(PChar.ColonyBuilding.Headport == false)
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) GameInterface.strings.HeadportCost = GetConvertStrWithReplace("Variable_Colony_61", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Headport.Cost)/2;
				else GameInterface.strings.HeadportCost = GetConvertStrWithReplace("Variable_Colony_62", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Headport.Cost);
			}
			else
			{
				GameInterface.strings.HeadportnCost = "";
			}

			if(PChar.ColonyBuilding.Headport == true)
			{
				SetSelectable("HEADPORT_OPEN", false);
			}
			else
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Headport.Cost/2;
				else NeedMoney = PChar.ColonyBuilding.Headport.Cost;

				if(GetMyColonyMoney() > sti(NeedMoney) && sti(PChar.ColonyBuilding.Stage) > 1)
				{
					SetSelectable("HEADPORT_OPEN", true);
				}
				else
				{
					SetSelectable("HEADPORT_OPEN", false);
				}
			}

			SetNodeUsing("BANK_OPEN", true);
			SetNodeUsing("CHURCH_OPEN", true);
			SetNodeUsing("HEADPORT_OPEN", true);
			SetNodeUsing("GOLDMINE_OPEN", false);
			SetNodeUsing("SILVERMINE_OPEN", false);
			SetNodeUsing("IRONMINE_OPEN", false);
			SetNodeUsing("GOLDMINE_RESIZE", false);
			SetNodeUsing("SILVERMINE_RESIZE", false);
			SetNodeUsing("IRONMINE_RESIZE", false);
			PChar.Colony.Interface.DownMenu = "ProBuilds";
			//SetInformation();
		break;

		case "Mines":
			if(PChar.Colony.Interface.DownMenu == "Mines")
			{
				return;
			}

			GameInterface.pictures.BankBorder.tex = "";
			GameInterface.pictures.BankBorder.pic = "";
			GameInterface.pictures.BankPicture.tex = "";
			GameInterface.pictures.BankPicture.pic = "";

			GameInterface.pictures.ChurchBorder.tex = "";
			GameInterface.pictures.ChurchBorder.pic = "";
			GameInterface.pictures.ChurchPicture.tex = "";
			GameInterface.pictures.ChurchPicture.pic = "";

			GameInterface.pictures.HeadPortBorder.tex = "";
			GameInterface.pictures.HeadPortBorder.pic = "";
			GameInterface.pictures.HeadportPicture.tex = "";
			GameInterface.pictures.HeadportPicture.pic = "";

		    	iColor = 0;

		    	GameInterface.strings.ProBuildHeader = GetConvertStrWithReplace("Variable_Colony_63", "Interface.txt", "#space#", " ");

			GameInterface.strings.BankHeader = "";
			GameInterface.strings.BankStatus = "";
			GameInterface.strings.BankCost = "";
			GameInterface.strings.ChurchHeader = "";
			GameInterface.strings.ChurchStatus = "";
			GameInterface.strings.ChurchCost = "";
			GameInterface.strings.HeadPortHeader = "";
			GameInterface.strings.HeadPortStatus = "";
			GameInterface.strings.HeadPortCost = "";

		    	//-------------------------------------------------------------------------------------------------

			CreateImage("GoldMineBorder", "BORDER1", "border", 350,385,485,485);
			CreateImage("GoldMinePicture", GetCurrentTexture(), "GoldMine", 350,385,485,485);
			CreateString(true,"GoldMineHeader", GetConvertStrWithReplace("Variable_Colony_64", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 413,360,SCRIPT_ALIGN_CENTER,1.0);

			string sGoldMineStatus = "";

			if(PChar.ColonyBuilding.GoldMine == false)
			{
				sGoldMineStatus = GetConvertStrWithReplace("Variable_Colony_65", "Interface.txt", "#space#", " ");
				iColor = argb(255,255,128,128);
			}
			else
			{
				if(PChar.ColonyBuilding.GoldMine.Resize == true)
				{
					sGoldMineStatus = GetConvertStrWithReplace("Variable_Colony_66", "Interface.txt", "#space#", " ");
				}
				else
				{
					sGoldMineStatus = GetConvertStrWithReplace("Variable_Colony_67", "Interface.txt", "#space#", " ");
				}
				iColor = argb(255,128,255,128);
			}

			CreateString(true,"GoldMineStatus", GetConvertStrWithReplace("Variable_Colony_68", "Interface.txt", "#space#", " ") + sGoldMineStatus, FONT_NORMAL, iColor, 355,493,SCRIPT_ALIGN_LEFT, 1.0);

			if(PChar.ColonyBuilding.GoldMine == false)
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"GoldMineCost", GetConvertStrWithReplace("Variable_Colony_69", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.GoldMine.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 355,513,SCRIPT_ALIGN_LEFT,1.0);
				else CreateString(true,"GoldMineCost", GetConvertStrWithReplace("Variable_Colony_70", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.GoldMine.Cost), FONT_NORMAL, COLOR_NORMAL, 355,513,SCRIPT_ALIGN_LEFT,1.0);
			}
			else
			{
				GameInterface.strings.GoldMineCost = "";
			}

			if(PChar.ColonyBuilding.GoldMine == true)
			{
				SetSelectable("GOLDMINE_OPEN", false);
			}
			else
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.GoldMine.Cost/2;
				else NeedMoney = PChar.ColonyBuilding.GoldMine.Cost;

				if(PChar.ColonyBuilding.Expidition == true && PChar.ColonyBuilding.Expidition.BuildingTime == false)
				{
					if(GetMyColonyMoney() < sti(NeedMoney) && PChar.ColonyBuilding.GoldMine.BuildingTime == false)
					{
						SetSelectable("GOLDMINE_OPEN", false);
					}
					else
					{
						SetSelectable("GOLDMINE_OPEN", true);
					}
				}
				else
				{
					SetSelectable("GOLDMINE_OPEN", false);
				}
			}

			if(PChar.ColonyBuilding.GoldMine == true)
			{
				SetNodeUsing("GOLDMINE_OPEN", false);
				SetNodeUsing("GOLDMINE_RESIZE", true);

				if(PChar.ColonyBuilding.GoldMine.Resize == false)
				{
					if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"GoldMineResizeCost", GetConvertStrWithReplace("Variable_Colony_71", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.GoldMine.ResizeCost)/2, FONT_NORMAL, COLOR_NORMAL, 355,513,SCRIPT_ALIGN_LEFT,1.0);
					else CreateString(true,"GoldMineResizeCost", GetConvertStrWithReplace("Variable_Colony_72", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.GoldMine.ResizeCost), FONT_NORMAL, COLOR_NORMAL, 355,513,SCRIPT_ALIGN_LEFT,1.0);
				}
				else
				{
					GameInterface.strings.GoldMineResizeCost = "";
				}

			    if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.GoldMine.ResizeCost/2;
				else NeedMoney = PChar.ColonyBuilding.GoldMine.ResizeCost;

				if(GetMyColonyMoney() >= sti(NeedMoney) && PChar.ColonyBuilding.GoldMine.BuildingTime == false)
				{
					SetSelectable("GOLDMINE_RESIZE", true);
				}
				else
				{
					SetSelectable("GOLDMINE_RESIZE", false);
				}
			}

			if(PChar.ColonyBuilding.GoldMine.Resize == true)
			{
				SetSelectable("GOLDMINE_RESIZE", false);
			}

		    	//-------------------------------------------------------------------------------------------------

			CreateImage("SilverMineBorder", "BORDER1", "border", 495,385,630,485);
			CreateImage("SilverMinePicture", GetCurrentTexture(), "SilverMine", 495,385,630,485);
			CreateString(true,"SilverMineHeader", GetConvertStrWithReplace("Variable_Colony_73", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 560,360,SCRIPT_ALIGN_CENTER,1.0);

			string sSilverMineStatus = "";

			if(PChar.ColonyBuilding.SilverMine == false)
			{
				sSilverMineStatus = GetConvertStrWithReplace("Variable_Colony_74", "Interface.txt", "#space#", " ");
				iColor = argb(255,255,128,128);
			}
			else
			{
				if(PChar.ColonyBuilding.SilverMine.Resize == true)
				{
					sSilverMineStatus = GetConvertStrWithReplace("Variable_Colony_75", "Interface.txt", "#space#", " ");
				}
				else
				{
					sSilverMineStatus = GetConvertStrWithReplace("Variable_Colony_76", "Interface.txt", "#space#", " ");
				}
				iColor = argb(255,128,255,128);
			}

			CreateString(true,"SilverMineStatus", GetConvertStrWithReplace("Variable_Colony_77", "Interface.txt", "#space#", " ") + sSilverMineStatus, FONT_NORMAL, iColor, 500,493,SCRIPT_ALIGN_LEFT, 1.0);

			if(PChar.ColonyBuilding.SilverMine == false)
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"SilverMineCost", GetConvertStrWithReplace("Variable_Colony_78", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.SilverMine.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 500,513,SCRIPT_ALIGN_LEFT,1.0);
				else CreateString(true,"SilverMineCost", GetConvertStrWithReplace("Variable_Colony_79", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.SilverMine.Cost), FONT_NORMAL, COLOR_NORMAL, 500,513,SCRIPT_ALIGN_LEFT,1.0);
			}
			else
			{
				GameInterface.strings.SilverMineCost = "";
			}

			if(PChar.ColonyBuilding.SilverMine == true)
			{
				SetSelectable("SILVERMINE_OPEN", false);
			}
			else
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.SilverMine.Cost/2;
				else NeedMoney = PChar.ColonyBuilding.SilverMine.Cost;

				if(PChar.ColonyBuilding.Expidition == true && PChar.ColonyBuilding.Expidition.BuildingTime == false)
				{
					if(GetMyColonyMoney() < sti(NeedMoney) && PChar.ColonyBuilding.SilverMine.BuildingTime == false)
					{
						SetSelectable("SILVERMINE_OPEN", false);
					}
					else
					{
						SetSelectable("SILVERMINE_OPEN", true);
					}
				}
				else
				{
					SetSelectable("SILVERMINE_OPEN", false);
				}
			}

			if(PChar.ColonyBuilding.SilverMine == true)
			{
				SetNodeUsing("SILVERMINE_OPEN", false);
				SetNodeUsing("SILVERMINE_RESIZE", true);

				if(PChar.ColonyBuilding.SilverMine.Resize == false)
				{
					if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"SilverMineResizeCost", GetConvertStrWithReplace("Variable_Colony_80", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.SilverMine.ResizeCost)/2, FONT_NORMAL, COLOR_NORMAL, 500,513,SCRIPT_ALIGN_LEFT,1.0);
					else CreateString(true,"SilverMineResizeCost", GetConvertStrWithReplace("Variable_Colony_81", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.SilverMine.ResizeCost), FONT_NORMAL, COLOR_NORMAL, 500,513,SCRIPT_ALIGN_LEFT,1.0);
				}
				else
				{
					GameInterface.strings.SilverMineResizeCost = "";
				}

			    if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.SilverMine.ResizeCost/2;
				else NeedMoney = PChar.ColonyBuilding.SilverMine.ResizeCost;

				if(GetMyColonyMoney() >= sti(NeedMoney) && PChar.ColonyBuilding.SilverMine.BuildingTime == false)
				{
					SetSelectable("SILVERMINE_RESIZE", true);
				}
				else
				{
					SetSelectable("SILVERMINE_RESIZE", false);
				}
			}

			if(PChar.ColonyBuilding.SilverMine.Resize == true)
			{
				SetSelectable("SILVERMINE_RESIZE", false);
			}

		    	//-------------------------------------------------------------------------------------------------

			CreateImage("IronMineBorder", "BORDER1", "border", 640,385,775,485);
			CreateImage("IronMinePicture", GetCurrentTexture(), "IronMine", 640,385,775,485);
			CreateString(true,"IronMineHeader", GetConvertStrWithReplace("Variable_Colony_82", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 705,360,SCRIPT_ALIGN_CENTER,1.0);

			string sIronMineStatus = "";

			if(PChar.ColonyBuilding.IronMine == false)
			{
				sIronMineStatus = GetConvertStrWithReplace("Variable_Colony_83", "Interface.txt", "#space#", " ");
				iColor = argb(255,255,128,128);
			}
			else
			{
				if(PChar.ColonyBuilding.IronMine.Resize == true)
				{
					sIronMineStatus = GetConvertStrWithReplace("Variable_Colony_84", "Interface.txt", "#space#", " ");
				}
				else
				{
					sIronMineStatus = GetConvertStrWithReplace("Variable_Colony_85", "Interface.txt", "#space#", " ");
				}
				iColor = argb(255,128,255,128);
			}

			CreateString(true,"IronMineStatus", GetConvertStrWithReplace("Variable_Colony_86", "Interface.txt", "#space#", " ") + sIronMineStatus, FONT_NORMAL, iColor, 645,493,SCRIPT_ALIGN_LEFT, 1.0);

			if(PChar.ColonyBuilding.IronMine == false)
			{
				if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"IronMineCost", GetConvertStrWithReplace("Variable_Colony_87", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.IronMine.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 645,513,SCRIPT_ALIGN_LEFT,1.0);
				else CreateString(true,"IronMineCost", GetConvertStrWithReplace("Variable_Colony_88", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.IronMine.Cost), FONT_NORMAL, COLOR_NORMAL, 645,513,SCRIPT_ALIGN_LEFT,1.0);
			}
			else
			{
				GameInterface.strings.IronMineCost = "";
			}

			if(PChar.ColonyBuilding.IronMine == true)
			{
				SetSelectable("IRONMINE_OPEN", false);
			}
			else
			{
				if(PChar.ColonyBuilding.Expidition == true && PChar.ColonyBuilding.Expidition.BuildingTime == false)
				{
					if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.IronMine.Cost/2;
					else NeedMoney = PChar.ColonyBuilding.IronMine.Cost;

					if(GetMyColonyMoney() < sti(NeedMoney) && PChar.ColonyBuilding.IronMine.BuildingTime == false)
					{
						SetSelectable("IRONMINE_OPEN", false);
					}
					else
					{
						SetSelectable("IRONMINE_OPEN", true);
					}
				}
				else
				{
					SetSelectable("IRONMINE_OPEN", false);
				}
			}

			if(PChar.ColonyBuilding.IronMine == true)
			{
				SetNodeUsing("IRONMINE_OPEN", false);
				SetNodeUsing("IRONMINE_RESIZE", true);

				if(PChar.ColonyBuilding.IronMine.Resize == false)
				{
					if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"IronMineResizeCost", GetConvertStrWithReplace("Variable_Colony_89", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.IronMine.ResizeCost)/2, FONT_NORMAL, COLOR_NORMAL, 645,513,SCRIPT_ALIGN_LEFT,1.0);
					else CreateString(true,"IronMineResizeCost", GetConvertStrWithReplace("Variable_Colony_90", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.IronMine.ResizeCost), FONT_NORMAL, COLOR_NORMAL, 645,513,SCRIPT_ALIGN_LEFT,1.0);
				}
				else
				{
					GameInterface.strings.IronMineResizeCost = "";
				}

			    if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.IronMine.ResizeCost/2;
				else NeedMoney = PChar.ColonyBuilding.IronMine.ResizeCost;

				if(GetMyColonyMoney() >= sti(NeedMoney) && PChar.ColonyBuilding.IronMine.BuildingTime == false)
				{
					SetSelectable("IRONMINE_RESIZE", true);
				}
				else
				{
					SetSelectable("IRONMINE_RESIZE", false);
				}
			}

			if(PChar.ColonyBuilding.IronMine.Resize == true)
			{
				SetSelectable("IRONMINE_RESIZE", false);
			}

			SetNodeUsing("BANK_OPEN", false);
			SetNodeUsing("CHURCH_OPEN", false);
			SetNodeUsing("HEADPORT_OPEN", false);
			SetNodeUsing("GOLDMINE_OPEN", true);
			SetNodeUsing("SILVERMINE_OPEN", true);
			SetNodeUsing("IRONMINE_OPEN", true);

			PChar.Colony.Interface.DownMenu = "Mines";
		break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

int GetCostForRaisePopulationMorale()
{
	ref PChar = GetMainCharacter();

	int iCost = 0;
	int iPopulation = sti(PChar.ColonyBuilding.Population);
	int iNalog = sti(PChar.ColonyBuilding.Nalog);

	float fLeaderShip = 1;

	ref mayor;
	if(CheckAttribute(PChar, "ColonyBuilding.Hovernor"))
	{
		if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1)
		{
			mayor = CharacterFromID(PChar.ColonyBuilding.Hovernor);
			fLeaderShip = GetCharacterSkill(mayor, SKILL_LEADERSHIP);
		}
	}

	iCost = (iPopulation * 100) + (iNalog * 100) - (fLeaderShip * 10);

	if(iCost <= 0)
	{
		iCost = 1000;
	}

	if(sti(PChar.ColonyBuilding.Population.Morale) >= 90)
	{
		iCost = 0;
	}

	return iCost;
}

void SetPopulationInformation()
{
	int iColor, iPopulationColor, iColonyStatus;
	int iPopulation = sti(PChar.ColonyBuilding.Population);
	int iPopulationMax = sti(PChar.ColonyBuilding.Population.Max);
	int iPopulationOptimal = sti(PChar.ColonyBuilding.Population.Optimal);
	int iMorale = sti(PChar.ColonyBuilding.Population.Morale);
	int iMoneyColor =  argb(255,255,255,128);

	string sMorale = "";

	if(iMorale >= 90)
	{
		sMorale = GetConvertStrWithReplace("Variable_Colony_91", "Interface.txt", "#space#", " ");
		iColor = argb(255,128,255,128);
	}
	if(iMorale < 90 && iMorale >= 80)
	{
		sMorale = GetConvertStrWithReplace("Variable_Colony_92", "Interface.txt", "#space#", " ");
		iColor = argb(255,128,255,128);
	}
	if(iMorale < 80 && iMorale >= 70)
	{
		sMorale = GetConvertStrWithReplace("Variable_Colony_93", "Interface.txt", "#space#", " ");
		iColor = argb(255,192,255,192);
	}
	if(iMorale < 70 && iMorale >= 60)
	{
		sMorale = GetConvertStrWithReplace("Variable_Colony_94", "Interface.txt", "#space#", " ");
		iColor = argb(255,192,255,192);
	}
	if(iMorale < 60 && iMorale >= 50)
	{
		sMorale = GetConvertStrWithReplace("Variable_Colony_95", "Interface.txt", "#space#", " ");
		iColor = argb(255,192,255,192);
	}
	if(iMorale < 50 && iMorale >= 40)
	{
		sMorale = GetConvertStrWithReplace("Variable_Colony_96", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,255,255);
	}
	if(iMorale < 40 && iMorale >= 30)
	{
		sMorale = GetConvertStrWithReplace("Variable_Colony_97", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	if(iMorale < 30 && iMorale >= 20)
	{
		sMorale = GetConvertStrWithReplace("Variable_Colony_98", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,192,192);
	}
	if(iMorale < 20 && iMorale >= 10)
	{
		sMorale = GetConvertStrWithReplace("Variable_Colony_99", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	if(iMorale < 10)
	{
		sMorale = GetConvertStrWithReplace("Variable_Colony_100", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}

	if(iPopulation > iPopulationOptimal)
	{
		iPopulationColor = argb(255,255,128,128);
	}
	else
	{
		iPopulationColor = argb(255,128,255,128);
	}

	int iMoraleUpCost = GetCostForRaisePopulationMorale();
	PChar.ColonyBuilnding.Population.Morale.Cost = iMoraleUpCost;

	string sColonyStatus = "";

	if(PChar.ColonyBuilding.Stage == "0")
	{
		sColonyStatus = GetConvertStrWithReplace("Variable_Colony_101", "Interface.txt", "#space#", " ");
		iColonyStatus = argb(255,255,128,128);
	}
	if(PChar.ColonyBuilding.Stage == "1")
	{
		sColonyStatus = GetConvertStrWithReplace("Variable_Colony_102", "Interface.txt", "#space#", " ");
		iColonyStatus = argb(255,255,192,192);
	}
	if(PChar.ColonyBuilding.Stage == "2")
	{
		sColonyStatus = GetConvertStrWithReplace("Variable_Colony_103", "Interface.txt", "#space#", " ");
		iColonyStatus = argb(255,192,255,192);
	}
	if(PChar.ColonyBuilding.Stage == "3")
	{
		sColonyStatus = GetConvertStrWithReplace("Variable_Colony_104", "Interface.txt", "#space#", " ");
		iColonyStatus = argb(255,128,255,128);
	}

	CreateString(true,"PopulationHeader", GetConvertStrWithReplace("Variable_Colony_105", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 160,39,SCRIPT_ALIGN_CENTER,1.5);

	CreateString(true,"ColonyStatus", GetConvertStrWithReplace("Variable_Colony_106", "Interface.txt", "#space#", " "), FONT_NORMAL, COLOR_NORMAL, 22,80,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"ColonyStatusContinue", sColonyStatus, FONT_NORMAL, iColonyStatus, 195,80,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"Population", GetConvertStrWithReplace("Variable_Colony_106.1", "Interface.txt", "#space#", " "), FONT_NORMAL, COLOR_NORMAL, 22,103,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"PopulationContinue", "" + iPopulation + " / " + iPopulationMax, FONT_NORMAL, iPopulationColor, 195,103,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"PopulationOptimal", GetConvertStrWithReplace("Variable_Colony_107", "Interface.txt", "#space#", " "), FONT_NORMAL, COLOR_NORMAL, 22,126,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"PopulationMaxContinue", "" + iPopulationOptimal, FONT_NORMAL, COLOR_NORMAL, 195,126,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"PopulationMorale", GetConvertStrWithReplace("Variable_Colony_108", "Interface.txt", "#space#", " "), FONT_NORMAL, COLOR_NORMAL, 22,149,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"PopulationMoraleContinue", sMorale, FONT_NORMAL, iColor, 195,149,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"MoraleUpCost", GetConvertStrWithReplace("Variable_Colony_109", "Interface.txt", "#space#", " "), FONT_NORMAL, COLOR_NORMAL, 22,172,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"MoraleUpCostContinue", "" + iMoraleUpCost, FONT_NORMAL, argb(255,255,192,192), 195,172,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"YourMoney", GetConvertStrWithReplace("Variable_Colony_110", "Interface.txt", "#space#", " "), FONT_NORMAL, COLOR_NORMAL, 22,195,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"YourMoneyContinue", "" + sti(PChar.money), FONT_NORMAL, iMoneyColor, 195,195,SCRIPT_ALIGN_LEFT, 1.0);

	if(GetMyColonyMoney() < iMoraleUpCost || iMorale >= 90)
	{
		SetSelectable("MORALE_UP", false);
	}
	else
	{
		SetSelectable("MORALE_UP", true);
	}
}

void SelectNalog(bool bTrue)
{
	ref PChar = GetMainCharacter();
	if(bTrue)
	{
		if(PChar.ColonyBuilding.Interface.Nalog == "1")
		{
			return;
		}

		if(PChar.ColonyBuilding.Interface.Nalog == "2")
		{
			PChar.ColonyBuilding.Interface.Nalog = "1";
		}

		if(PChar.ColonyBuilding.Interface.Nalog == "3")
		{
			PChar.ColonyBuilding.Interface.Nalog = "2";
		}
	}
	else
	{
		if(PChar.ColonyBuilding.Interface.Nalog == "3")
		{
			return;
		}

		if(PChar.ColonyBuilding.Interface.Nalog == "2")
		{
			PChar.ColonyBuilding.Interface.Nalog = "3";
		}

		if(PChar.ColonyBuilding.Interface.Nalog == "1")
		{
			PChar.ColonyBuilding.Interface.Nalog = "2";
		}
	}
	SetNalogInformation();
}

void InstallNalog(string sNalog)
{
	ref PChar = GetMainCharacter();
	int iNalog = sti(PChar.ColonyBuilding.Interface.Nalog);
	PChar.ColonyBuilding.Nalog = iNalog;
	PChar.ColonyBuilding.Interface.Nalog = "1";
	SetNalogInformation();
}

void SetNalogInformation()
{
	int iNalog;
	string sNalog = "";

	if(sti(PChar.ColonyBuilding.Nalog) == 1)
	{
		sNalog = GetConvertStrWithReplace("Variable_Colony_111", "Interface.txt", "#space#", " ");
		iNalog = argb(255,192,255,192);
	}
	if(sti(PChar.ColonyBuilding.Nalog) == 2)
	{
		sNalog = GetConvertStrWithReplace("Variable_Colony_112", "Interface.txt", "#space#", " ");
		iNalog = argb(255,255,255,255);
	}
	if(sti(PChar.ColonyBuilding.Nalog) == 3)
	{
		sNalog = GetConvertStrWithReplace("Variable_Colony_113", "Interface.txt", "#space#", " ");
		iNalog = argb(255,255,192,192);
	}

	// CreateImage("NalogPicture", "MAIN_ICONS", "skillborder", 14,263,321,292);
	CreateString(true,"NalogHeader", GetConvertStrWithReplace("Variable_Colony_114", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 160,257,SCRIPT_ALIGN_CENTER,1.5);

	CreateString(true,"Nalog", GetConvertStrWithReplace("Variable_Colony_115", "Interface.txt", "#space#", " "), FONT_NORMAL, COLOR_NORMAL, 30,300,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"NalogContinue", sNalog, FONT_NORMAL, iNalog, 195,300,SCRIPT_ALIGN_LEFT, 1.0);


	string sSelectNalog = "";
	int iNalogX = 0;

	if(PChar.ColonyBuilding.Interface.Nalog == "1")
	{
		sSelectNalog = GetConvertStrWithReplace("Variable_Colony_116", "Interface.txt", "#space#", " ");
		iNalogX = 135;
	}
	if(PChar.ColonyBuilding.Interface.Nalog == "2")
	{
		sSelectNalog = GetConvertStrWithReplace("Variable_Colony_117", "Interface.txt", "#space#", " ");
		iNalogX = 135;
	}
	if(PChar.ColonyBuilding.Interface.Nalog == "3")
	{
		sSelectNalog = GetConvertStrWithReplace("Variable_Colony_118", "Interface.txt", "#space#", " ");
		iNalogX = 135;
	}

	CreateString(true,"NalogSelect", sSelectNalog, FONT_CAPTION, COLOR_NORMAL, iNalogX,329,SCRIPT_ALIGN_LEFT, 1.2);

	if(PChar.ColonyBuilding.Stage == "0" || PChar.ColonyBuilding.Stage == "1")
	{
		if(PChar.ColonyBuilding.Interface.Nalog == "2" || PChar.ColonyBuilding.Interface.Nalog == "3")
		{
			SetSelectable("INSTALL_HIGH_NALOG", false);
		}
		else
		{
			if(sti(PChar.ColonyBuilding.Nalog) == 1 && PChar.ColonyBuilding.Interface.Nalog == "1")
			{
				SetSelectable("INSTALL_HIGH_NALOG", false);
			}
			else
			{
				SetSelectable("INSTALL_HIGH_NALOG", true);
			}
		}
	}
	else
	{
		if(sti(PChar.ColonyBuilding.Nalog) == 1 && PChar.ColonyBuilding.Interface.Nalog == "1")
		{
			SetSelectable("INSTALL_HIGH_NALOG", false);
		}
		else
		{
			if(sti(PChar.ColonyBuilding.Nalog) == 2 && PChar.ColonyBuilding.Interface.Nalog == "2")
			{
				SetSelectable("INSTALL_HIGH_NALOG", false);
			}
			else
			{
				if(sti(PChar.ColonyBuilding.Nalog) == 3 && PChar.ColonyBuilding.Interface.Nalog == "3")
				{
					SetSelectable("INSTALL_HIGH_NALOG", false);
				}
				else
				{
					SetSelectable("INSTALL_HIGH_NALOG", true);
				}
			}
		}
	}
}

void MoneyTempUptade()
{
	if(sti(GameInterface.MONEY_STRING.str) > sti(PChar.ColonyBuilding.Money))
	{
		GameInterface.MONEY_STRING.str = sti(PChar.ColonyBuilding.Money);
	}

	PChar.ColonyBuilding.Money.Temp = sti(GameInterface.MONEY_STRING.str);

	if(sti(PChar.ColonyBuilding.Money.Temp) > 0)
	{
		SetSelectable("GIVEGOLD", true);
	}
	else
	{
		SetSelectable("GIVEGOLD", false);
	}
}

void SetMoneyInformation()
{
	int iMoneyColor =  argb(255,255,255,128);
	// CreateImage("GoldPicture", "MAIN_ICONS", "skillborder", 14,408,321,438);

	//CreateImage("GoldIcon", "GOLD_ICON", "Gold", 251,442,315,506);

	CreateString(true,"GoldHeader", GetConvertStrWithReplace("Variable_Colony_119", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 160,403,SCRIPT_ALIGN_CENTER,1.5);

	GameInterface.MONEY_STRING.str = sti(PChar.ColonyBuilding.Money.Temp);

	CreateString(true,"GoldQuantity", GetConvertStrWithReplace("Variable_Colony_120", "Interface.txt", "#space#", " "), FONT_NORMAL, COLOR_NORMAL, 30,443,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"GoldQuantityContinue", "" + sti(PChar.ColonyBuilding.Money), FONT_NORMAL, iMoneyColor, 195,441,SCRIPT_ALIGN_LEFT, 1.0);

	if(sti(PChar.ColonyBuilding.Money.Temp) > 0)
	{
		SetSelectable("GIVEGOLD", true);
	}
	else
	{
		SetSelectable("GIVEGOLD", false);
	}

	SetSelectable("TAKE_MONEY", false);
	if(sti(PChar.money) > 0)
	{
		SetSelectable("TAKE_MONEY", true);
	}

	//CreateImage("GoldQuantityPicture", "MAIN_ICONS", "skillborder", 110,467,210,502);
	//CreateString(true,"GoldTempQuantity", "" + sti(PChar.ColonyBuilding.Money.Temp), FONT_CAPTION, COLOR_NORMAL, 160,468,SCRIPT_ALIGN_CENTER, 1.5);
}

void SetColonyInformation()
{
	if(PChar.ColonyBuilding.Shipyard == true && PChar.ColonyBuilding.Shipyard.BuildingTime == false)
	{
		SetSelectable("REPAIR_ALL_SHIPS", true);
	}
	else
	{
		SetSelectable("REPAIR_ALL_SHIPS", false);
	}
}

void SetInformation()
{
	ClearAllElements();

	//-----------------------------------------------------------------------------------------------------------------

	CreateImage("StoreBorder", "BORDER1", "border", 350,110,485,210);
	CreateImage("ShipyardBorder", "BORDER1", "border", 495,110,630,210);
	CreateImage("TavernBorder", "BORDER1", "border", 640,110,775,210);
	CreateImage("BankBorder", "BORDER1", "border", 350,385,485,485);
	CreateImage("ChurchBorder", "BORDER1", "border", 495,385,630,485);
	CreateImage("HeadPortBorder", "BORDER1", "border", 640,385,775,485);

	SetNodeUsing("STORE_OPEN", true);
	SetNodeUsing("SHIPYARD_OPEN", true);
	SetNodeUsing("TAVERN_OPEN", true);
	SetNodeUsing("BANK_OPEN", true);
	SetNodeUsing("CHURCH_OPEN", true);
	SetNodeUsing("HEADPORT_OPEN", true);
	SetNodeUsing("EXPIDITION_OPEN", false);
	SetNodeUsing("STOREHOUSE_OPEN", false);
	SetNodeUsing("PLANTATION_OPEN", false);
	SetNodeUsing("PLANTATION_RESIZE", false);
	SetNodeUsing("STOREHOUSE_RESIZE", false);
	SetNodeUsing("GOLDMINE_OPEN", false);
	SetNodeUsing("SILVERMINE_OPEN", false);
	SetNodeUsing("IRONMINE_OPEN", false);
	SetNodeUsing("GOLDMINE_RESIZE", false);
	SetNodeUsing("SILVERMINE_RESIZE", false);
	SetNodeUsing("IRONMINE_RESIZE", false);


	CreateString(true,"NormalBuildHeader", GetConvertStrWithReplace("Variable_Colony_121", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 560,39,SCRIPT_ALIGN_CENTER,1.5);

	CreateImage("StorePicture", GetCurrentTexture(), "Store", 350,110,485,210);
	CreateString(true,"StoreHeader", GetConvertStrWithReplace("Variable_Colony_122", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 410,87,SCRIPT_ALIGN_CENTER,1.0);

	string sStoreStatus = "";

	if(PChar.ColonyBuilding.Store == false)
	{
		sStoreStatus = GetConvertStrWithReplace("Variable_Colony_123", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		sStoreStatus = GetConvertStrWithReplace("Variable_Colony_124", "Interface.txt", "#space#", " ");
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"StoreStatus", GetConvertStrWithReplace("Variable_Colony_125", "Interface.txt", "#space#", " ") + sStoreStatus, FONT_NORMAL, iColor, 355,218,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.Store == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"StoreCost", GetConvertStrWithReplace("Variable_Colony_126", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Store.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 355,238,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"StoreCost", GetConvertStrWithReplace("Variable_Colony_127", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Store.Cost), FONT_NORMAL, COLOR_NORMAL, 355,238,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.StoreCost = "";
	}

	if(PChar.ColonyBuilding.Store == true)
	{
		SetSelectable("STORE_OPEN", false);
	}
	else
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Store.Cost/2;
		else NeedMoney = PChar.ColonyBuilding.Store.Cost;

		if(GetMyColonyMoney() < sti(NeedMoney))
		{
			SetSelectable("STORE_OPEN", false);
		}
		else
		{
			SetSelectable("STORE_OPEN", true);
		}
	}

	//-----------------------------------------------------------------------------------------------------------------

	CreateImage("ShipyardPicture", GetCurrentTexture(), "Shipyard", 495,110,630,210);
	CreateString(true,"ShipyardHeader", GetConvertStrWithReplace("Variable_Colony_128", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 560,87,SCRIPT_ALIGN_CENTER,1.0);

	string sShipyardStatus = "";

	if(PChar.ColonyBuilding.Shipyard == false)
	{
		sShipyardStatus = GetConvertStrWithReplace("Variable_Colony_129", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		sShipyardStatus = GetConvertStrWithReplace("Variable_Colony_130", "Interface.txt", "#space#", " ");
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"ShipyardStatus", GetConvertStrWithReplace("Variable_Colony_131", "Interface.txt", "#space#", " ") + sShipyardStatus, FONT_NORMAL, iColor, 500,218,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.Shipyard == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"ShipyardCost", GetConvertStrWithReplace("Variable_Colony_132", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Shipyard.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 500,238,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"ShipyardCost", GetConvertStrWithReplace("Variable_Colony_133", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Shipyard.Cost), FONT_NORMAL, COLOR_NORMAL, 500,238,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.ShipyardCost = "";
	}

	if(PChar.ColonyBuilding.Shipyard == true)
	{
		SetSelectable("SHIPYARD_OPEN", false);
	}
	else
	{
		if(PChar.ColonyBuilding.Stage == "0" || PChar.ColonyBuilding.Stage == "1")
		{
			SetSelectable("SHIPYARD_OPEN", false);
		}
		else
		{
			if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Shipyard.Cost/2;
			else NeedMoney = PChar.ColonyBuilding.Shipyard.Cost;

			if(GetMyColonyMoney() < sti(NeedMoney))
			{
				SetSelectable("SHIPYARD_OPEN", false);
			}
			else
			{
				SetSelectable("SHIPYARD_OPEN", true);
			}
		}
	}

	//-----------------------------------------------------------------------------------------------------------------

	CreateImage("TavernPicture", GetCurrentTexture(), "Tavern", 640,110,775,210);
	CreateString(true,"TavernHeader", GetConvertStrWithReplace("Variable_Colony_134", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 705,87,SCRIPT_ALIGN_CENTER,1.0);

	string sTavernStatus = "";

	if(PChar.ColonyBuilding.Tavern == false)
	{
		sTavernStatus = GetConvertStrWithReplace("Variable_Colony_135", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		sTavernStatus = GetConvertStrWithReplace("Variable_Colony_136", "Interface.txt", "#space#", " ");
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"TavernStatus", GetConvertStrWithReplace("Variable_Colony_137", "Interface.txt", "#space#", " ") + sTavernStatus, FONT_NORMAL, iColor, 645,218,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.Tavern == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"TavernCost", GetConvertStrWithReplace("Variable_Colony_138", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Tavern.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 645,238,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"TavernCost", GetConvertStrWithReplace("Variable_Colony_139", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Tavern.Cost), FONT_NORMAL, COLOR_NORMAL, 645,238,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.TavernCost = "";
	}

	if(PChar.ColonyBuilding.Tavern == true)
	{
		SetSelectable("TAVERN_OPEN", false);
	}
	else
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Tavern.Cost/2;
		else NeedMoney PChar.ColonyBuilding.Tavern.Cost;

		if(GetMyColonyMoney() < sti(NeedMoney))
		{
			SetSelectable("TAVERN_OPEN", false);
		}
		else
		{
			SetSelectable("TAVERN_OPEN", true);
		}
	}

	//-----------------------------------------------------------------------------------------------------------------

	// CreateImage("ProBuild", "MAIN_ICONS", "skillborder", 339,313,786,345);
	CreateString(true,"ProBuildHeader", GetConvertStrWithReplace("Variable_Colony_140", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 563,298,SCRIPT_ALIGN_CENTER,1.5);

	CreateImage("BankPicture", GetCurrentTexture(), "Bank", 350,385,485,485);
	CreateString(true,"BankHeader", GetConvertStrWithReplace("Variable_Colony_141", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 413,360,SCRIPT_ALIGN_CENTER,1.0);

	string sBankStatus = "";

	if(PChar.ColonyBuilding.Bank == false)
	{
		sBankStatus = GetConvertStrWithReplace("Variable_Colony_142", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		sBankStatus = GetConvertStrWithReplace("Variable_Colony_143", "Interface.txt", "#space#", " ");
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"BankStatus", GetConvertStrWithReplace("Variable_Colony_144", "Interface.txt", "#space#", " ") + sBankStatus, FONT_NORMAL, iColor, 355,493,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.Bank == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"BankCost", GetConvertStrWithReplace("Variable_Colony_145", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Bank.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 355,513,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"BankCost", GetConvertStrWithReplace("Variable_Colony_146", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Bank.Cost), FONT_NORMAL, COLOR_NORMAL, 355,513,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.BankCost = "";
	}

	if(PChar.ColonyBuilding.Bank == true)
	{
		SetSelectable("BANK_OPEN", false);
	}
	else
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Bank.Cost/2;
		else NeedMoney = PChar.ColonyBuilding.Bank.Cost;

		if(GetMyColonyMoney() > sti(NeedMoney) && sti(PChar.ColonyBuilding.Stage) > 1)
		{
			SetSelectable("BANK_OPEN", true);
		}
		else
		{
			SetSelectable("BANK_OPEN", false);
		}
	}

	//-----------------------------------------------------------------------------------------------------------------

	CreateImage("ChurchPicture", GetCurrentTexture(), "Church", 495,385,630,485);
	CreateString(true,"ChurchHeader", GetConvertStrWithReplace("Variable_Colony_147", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 560,360,SCRIPT_ALIGN_CENTER,1.0);

	string sChurchStatus = "";

	if(PChar.ColonyBuilding.Church == false)
	{
		sChurchStatus = GetConvertStrWithReplace("Variable_Colony_148", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		sChurchStatus = GetConvertStrWithReplace("Variable_Colony_149", "Interface.txt", "#space#", " ");
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"ChurchStatus", GetConvertStrWithReplace("Variable_Colony_150", "Interface.txt", "#space#", " ") + sChurchStatus, FONT_NORMAL, iColor, 500,493,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.Church == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"ChurchCost", GetConvertStrWithReplace("Variable_Colony_151", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Church.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 500,513,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"ChurchCost", GetConvertStrWithReplace("Variable_Colony_152", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Church.Cost), FONT_NORMAL, COLOR_NORMAL, 500,513,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.ChurchCost = "";
	}

	if(PChar.ColonyBuilding.Church == true)
	{
		SetSelectable("CHURCH_OPEN", false);
	}
	else
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Church.Cost/2;
		else NeedMoney = PChar.ColonyBuilding.Church.Cost;

		if(GetMyColonyMoney() > sti(NeedMoney) && sti(PChar.ColonyBuilding.Stage) > 1)
		{
			SetSelectable("CHURCH_OPEN", true);
		}
		else
		{
			SetSelectable("CHURCH_OPEN", false);
		}
	}

	//-----------------------------------------------------------------------------------------------------------------

	CreateImage("HeadportPicture", GetCurrentTexture(), "HeadPort", 640,385,775,485);
	CreateString(true,"HeadportHeader", GetConvertStrWithReplace("Variable_Colony_153", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 705,360,SCRIPT_ALIGN_CENTER,1.0);

	string sHeadportStatus = "";

	if(PChar.ColonyBuilding.Headport == false)
	{
		sHeadportStatus = GetConvertStrWithReplace("Variable_Colony_154", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		sHeadportStatus = GetConvertStrWithReplace("Variable_Colony_155", "Interface.txt", "#space#", " ");
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"HeadportStatus", GetConvertStrWithReplace("Variable_Colony_156", "Interface.txt", "#space#", " ") + sHeadportStatus, FONT_NORMAL, iColor, 645,493,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.Headport == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"HeadportCost", GetConvertStrWithReplace("Variable_Colony_157", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Headport.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 645,513,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"HeadportCost", GetConvertStrWithReplace("Variable_Colony_158", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Headport.Cost), FONT_NORMAL, COLOR_NORMAL, 645,513,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.HeadportCost = "";
	}

	if(PChar.ColonyBuilding.Headport == true || PChar.ColonyBuilding.Headport.BuildingTime == true)
	{
		SetSelectable("HEADPORT_OPEN", false);
	}
	else
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Headport.Cost/2;
		else NeedMoney = PChar.ColonyBuilding.Headport.Cost;

		if(GetMyColonyMoney() > sti(NeedMoney) && sti(PChar.ColonyBuilding.Stage) > 1)
		{
			SetSelectable("HEADPORT_OPEN", true);
		}
		else
		{
			SetSelectable("HEADPORT_OPEN", false);
		}
	}
}

void SetExpiditionInformation()
{
	string sExpiditionStatus = "";

	if(PChar.ColonyBuilding.Expidition == false)
	{
		sExpiditionStatus = GetConvertStrWithReplace("Variable_Colony_159", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		sExpiditionStatus = GetConvertStrWithReplace("Variable_Colony_160", "Interface.txt", "#space#", " ");
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"ExpiditionStatus", GetConvertStrWithReplace("Variable_Colony_161", "Interface.txt", "#space#", " ") + sExpiditionStatus, FONT_NORMAL, iColor, 355,218,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.Expidition == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"ExpiditionCost", GetConvertStrWithReplace("Variable_Colony_162", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Expidition.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 355,238,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"ExpiditionCost", GetConvertStrWithReplace("Variable_Colony_163", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Expidition.Cost), FONT_NORMAL, COLOR_NORMAL, 355,238,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.ExpiditionCost = "";
	}

	if(PChar.ColonyBuilding.Expidition == true)
	{
		SetSelectable("EXPIDITION_OPEN", false);
	}
	else
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Expidition.Cost/2;
		else NeedMoney = PChar.ColonyBuilding.Expidition.Cost;

		if(PChar.ColonyBuilding.Stage == "2" || PChar.ColonyBuilding.Stage == "3")
		{
			if(GetMyColonyMoney() < sti(NeedMoney))
			{
				SetSelectable("EXPIDITION_OPEN", false);
			}
			else
			{
				SetSelectable("EXPIDITION_OPEN", true);
			}
		}
		else
		{
			SetSelectable("EXPIDITION_OPEN", false);
		}
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------

	string sStoreHouseStatus = "";

	if(PChar.ColonyBuilding.StoreHouse == false)
	{
		sStoreHouseStatus = GetConvertStrWithReplace("Variable_Colony_164", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		if(PChar.ColonyBuilding.StoreHouse.Resize == true)
		{
			sStoreHouseStatus = GetConvertStrWithReplace("Variable_Colony_165", "Interface.txt", "#space#", " ");
		}
		else
		{
			sStoreHouseStatus = GetConvertStrWithReplace("Variable_Colony_166", "Interface.txt", "#space#", " ");
		}
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"StoreHouseStatus", GetConvertStrWithReplace("Variable_Colony_167", "Interface.txt", "#space#", " ") + sStoreHouseStatus, FONT_NORMAL, iColor, 500,218,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.StoreHouse == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"StoreHouseCost", GetConvertStrWithReplace("Variable_Colony_168", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.StoreHouse.Cost), FONT_NORMAL, COLOR_NORMAL, 500,238,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"StoreHouseCost", GetConvertStrWithReplace("Variable_Colony_169", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.StoreHouse.Cost), FONT_NORMAL, COLOR_NORMAL, 500,238,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.StoreHouseCost = "";
	}

	if(PChar.ColonyBuilding.StoreHouse == true)
	{
		SetSelectable("STOREHOUSE_OPEN", false);
	}
	else
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.StoreHouse.Cost/2;
		else NeedMoney = PChar.ColonyBuilding.StoreHouse.Cost;

		if(sti(PChar.money) < sti(NeedMoney))
		{
			SetSelectable("STOREHOUSE_OPEN", false);
		}
		else
		{
			SetSelectable("STOREHOUSE_OPEN", true);
		}
	}

	if(PChar.ColonyBuilding.StoreHouse == true)
	{
		SetNodeUsing("STOREHOUSE_OPEN", false);
		SetNodeUsing("STOREHOUSE_RESIZE", true);

		if(PChar.ColonyBuilding.StoreHouse.Resize == false)
		{
			if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"StoreHouseResizeCost", GetConvertStrWithReplace("Variable_Colony_170", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.StoreHouse.ResizeCost)/2, FONT_NORMAL, COLOR_NORMAL, 500,238,SCRIPT_ALIGN_LEFT,1.0);
			else CreateString(true,"StoreHouseResizeCost", GetConvertStrWithReplace("Variable_Colony_171", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.StoreHouse.ResizeCost), FONT_NORMAL, COLOR_NORMAL, 500,238,SCRIPT_ALIGN_LEFT,1.0);
		}
		else
		{
			GameInterface.strings.StoreHouseResizeCost = "";
		}

		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.StoreHouse.ResizeCost/2;
		else NeedMoney = PChar.ColonyBuilding.StoreHouse.ResizeCost;

		if(PChar.ColonyBuilding.Stage == "2" || PChar.ColonyBuilding.Stage == "3")
		{
			if(GetMyColonyMoney() >= sti(NeedMoney) && PChar.ColonyBuilding.StoreHouse.BuildingTime == false)
			{
				SetSelectable("STOREHOUSE_RESIZE", true);
			}
			else
			{
				SetSelectable("STOREHOUSE_RESIZE", false);
			}
		}
		else
		{
			SetSelectable("STOREHOUSE_RESIZE", false);
		}
	}

	if(PChar.ColonyBuilding.StoreHouse.Resize == true)
	{
		SetSelectable("STOREHOUSE_RESIZE", false);
	}

	//-----------------------------------------------------------------------------

	string sPlantationStatus = "";

	if(PChar.ColonyBuilding.Plantation == false)
	{
		sPlantationStatus = GetConvertStrWithReplace("Variable_Colony_172", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		sPlantationStatus = GetConvertStrWithReplace("Variable_Colony_173", "Interface.txt", "#space#", " ");
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"PlantationStatus", GetConvertStrWithReplace("Variable_Colony_174", "Interface.txt", "#space#", " ") + sPlantationStatus, FONT_NORMAL, iColor, 645,218,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.Plantation == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"PlantationCost", GetConvertStrWithReplace("Variable_Colony_175", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Plantation.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 645,238,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"PlantationCost", GetConvertStrWithReplace("Variable_Colony_176", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Plantation.Cost), FONT_NORMAL, COLOR_NORMAL, 645,238,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.PlantationCost = "";
	}

	if(PChar.ColonyBuilding.Plantation == true)
	{
		SetSelectable("PLANTATION_OPEN", false);
	}
	else
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.Plantation.Cost/2;
		else NeedMoney = PChar.ColonyBuilding.Plantation.Cost;

		if(PChar.ColonyBuilding.Expidition == true && PChar.ColonyBuilding.Expidition.BuildingTime == false)
		{
			if(GetMyColonyMoney() < sti(NeedMoney))
			{
				SetSelectable("PLANTATION_OPEN", false);
			}
			else
			{
				SetSelectable("PLANTATION_OPEN", true);
			}
		}
		else
		{
			SetSelectable("PLANTATION_OPEN", false);
		}
	}


	if(PChar.ColonyBuilding.Plantation == true)
	{
		SetNodeUsing("PLANTATION_OPEN", false);
		SetNodeUsing("PLANTATION_RESIZE", true);

		if(PChar.ColonyBuilding.Plantation.Resize == false && PChar.ColonyBuilding.Plantation.Resize.BuildingTime == false)
		{
			if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"PlantationResizeCost", GetConvertStrWithReplace("Variable_Colony_177", "Interface.txt", "#space#", " ") + sti(PChar.Plantation.ResizeMoney)/2, FONT_NORMAL, COLOR_NORMAL, 645,238,SCRIPT_ALIGN_LEFT,1.0);
			else CreateString(true,"PlantationResizeCost", GetConvertStrWithReplace("Variable_Colony_178", "Interface.txt", "#space#", " ") + sti(PChar.Plantation.ResizeMoney), FONT_NORMAL, COLOR_NORMAL, 645,238,SCRIPT_ALIGN_LEFT,1.0);
		}
		else
		{
			GameInterface.strings.PlantationResizeCost = "";
		}

		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.Plantation.ResizeMoney/2;
		else NeedMoney = PChar.Plantation.ResizeMoney;

		if(GetMyColonyMoney() >= sti(PChar.Plantation.ResizeMoney) && PChar.ColonyBuilding.Plantation.BuildingTime == false)
		{
			SetSelectable("PLANTATION_RESIZE", true);
		}
		else
		{
			SetSelectable("PLANTATION_RESIZE", false);
		}
	}

	if(PChar.ColonyBuilding.Plantation.Resize == true || PChar.ColonyBuilding.Plantation.Resize.BuildingTime == true)
	{
		SetSelectable("PLANTATION_RESIZE", false);
	}

}

void SetMinesInformation()
{
    	iColor = 0;

    	//-------------------------------------------------------------------------------------------------

	string sGoldMineStatus = "";

	if(PChar.ColonyBuilding.GoldMine == false)
	{
		sGoldMineStatus = GetConvertStrWithReplace("Variable_Colony_179", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		if(PChar.ColonyBuilding.GoldMine.Resize == true)
		{
			sGoldMineStatus = GetConvertStrWithReplace("Variable_Colony_180", "Interface.txt", "#space#", " ");
		}
		else
		{
			sGoldMineStatus = GetConvertStrWithReplace("Variable_Colony_181", "Interface.txt", "#space#", " ");
		}
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"GoldMineStatus", GetConvertStrWithReplace("Variable_Colony_182", "Interface.txt", "#space#", " ") + sGoldMineStatus, FONT_NORMAL, iColor, 355,493,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.GoldMine == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"GoldMineCost", GetConvertStrWithReplace("Variable_Colony_183", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.GoldMine.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 355,513,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"GoldMineCost", GetConvertStrWithReplace("Variable_Colony_184", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.GoldMine.Cost), FONT_NORMAL, COLOR_NORMAL, 355,513,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.GoldMineCost = "";
	}

	if(PChar.ColonyBuilding.GoldMine == true)
	{
		SetSelectable("GOLDMINE_OPEN", false);
	}
	else
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.GoldMine.Cost/2;
		else NeedMoney = PChar.ColonyBuilding.GoldMine.Cost;

		if(PChar.ColonyBuilding.Expidition == true && PChar.ColonyBuilding.Expidition.BuildingTime == false)
		{
			if(GetMyColonyMoney() < sti(NeedMoney) && PChar.ColonyBuilding.GoldMine.BuildingTime == false)
			{
				SetSelectable("GOLDMINE_OPEN", false);
			}
			else
			{
				SetSelectable("GOLDMINE_OPEN", true);
			}
		}
		else
		{
			SetSelectable("GOLDMINE_OPEN", false);
		}
	}

	if(PChar.ColonyBuilding.GoldMine == true)
	{
		SetNodeUsing("GOLDMINE_OPEN", false);
		SetNodeUsing("GOLDMINE_RESIZE", true);

		if(PChar.ColonyBuilding.GoldMine.Resize == false)
		{
			if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"GoldMineResizeCost", GetConvertStrWithReplace("Variable_Colony_185", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.GoldMine.ResizeCost), FONT_NORMAL, COLOR_NORMAL, 355,513,SCRIPT_ALIGN_LEFT,1.0);
			else CreateString(true,"GoldMineResizeCost", GetConvertStrWithReplace("Variable_Colony_186", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.GoldMine.ResizeCost), FONT_NORMAL, COLOR_NORMAL, 355,513,SCRIPT_ALIGN_LEFT,1.0);
		}
		else
		{
			GameInterface.strings.GoldMineResizeCost = "";
		}

		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.GoldMine.ResizeCost/2;
		else NeedMoney = PChar.ColonyBuilding.GoldMine.ResizeCost;

		if(GetMyColonyMoney() >= sti(NeedMoney) && PChar.ColonyBuilding.GoldMine.BuildingTime == false)
		{
			SetSelectable("GOLDMINE_RESIZE", true);
		}
		else
		{
			SetSelectable("GOLDMINE_RESIZE", false);
		}
	}

	if(PChar.ColonyBuilding.GoldMine.Resize == true)
	{
		SetSelectable("GOLDMINE_RESIZE", false);
	}

    	//-------------------------------------------------------------------------------------------------

	string sSilverMineStatus = "";

	if(PChar.ColonyBuilding.SilverMine == false)
	{
		sSilverMineStatus = GetConvertStrWithReplace("Variable_Colony_187", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		if(PChar.ColonyBuilding.SilverMine.Resize == true)
		{
			sSilverMineStatus = GetConvertStrWithReplace("Variable_Colony_188", "Interface.txt", "#space#", " ");
		}
		else
		{
			sSilverMineStatus = GetConvertStrWithReplace("Variable_Colony_189", "Interface.txt", "#space#", " ");
		}
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"SilverMineStatus", GetConvertStrWithReplace("Variable_Colony_190", "Interface.txt", "#space#", " ") + sSilverMineStatus, FONT_NORMAL, iColor, 500,493,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.SilverMine == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"SilverMineCost", GetConvertStrWithReplace("Variable_Colony_191", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.SilverMine.Cost)/2, FONT_NORMAL, COLOR_NORMAL, 500,513,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"SilverMineCost", GetConvertStrWithReplace("Variable_Colony_192", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.SilverMine.Cost), FONT_NORMAL, COLOR_NORMAL, 500,513,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.SilverMineCost = "";
	}

	if(PChar.ColonyBuilding.SilverMine == true)
	{
		SetSelectable("SILVERMINE_OPEN", false);
	}
	else
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.SilverMine.Cost/2;
		else NeedMoney = PChar.ColonyBuilding.SilverMine.Cost;

		if(PChar.ColonyBuilding.Expidition == true && PChar.ColonyBuilding.Expidition.BuildingTime == false)
		{
			if(GetMyColonyMoney() < sti(NeedMoney) && PChar.ColonyBuilding.SilverMine.BuildingTime == false)
			{
				SetSelectable("SILVERMINE_OPEN", false);
			}
			else
			{
				SetSelectable("SILVERMINE_OPEN", true);
			}
		}
		else
		{
			SetSelectable("SILVERMINE_OPEN", false);
		}
	}

	if(PChar.ColonyBuilding.SilverMine == true)
	{
		SetNodeUsing("SILVERMINE_OPEN", false);
		SetNodeUsing("SILVERMINE_RESIZE", true);

		if(PChar.ColonyBuilding.SilverMine.Resize == false)
		{
			if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"SilverMineResizeCost", GetConvertStrWithReplace("Variable_Colony_193", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.SilverMine.ResizeCost), FONT_NORMAL, COLOR_NORMAL, 500,513,SCRIPT_ALIGN_LEFT,1.0);
			else CreateString(true,"SilverMineResizeCost", GetConvertStrWithReplace("Variable_Colony_194", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.SilverMine.ResizeCost), FONT_NORMAL, COLOR_NORMAL, 500,513,SCRIPT_ALIGN_LEFT,1.0);
		}
		else
		{
			GameInterface.strings.SilverMineResizeCost = "";
		}

		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.SilverMine.ResizeCost/2;
		else NeedMoney = PChar.ColonyBuilding.SilverMine.ResizeCost;

		if(GetMyColonyMoney() >= sti(NeedMoney) && PChar.ColonyBuilding.SilverMine.BuildingTime == false)
		{
			SetSelectable("SILVERMINE_RESIZE", true);
		}
		else
		{
			SetSelectable("SILVERMINE_RESIZE", false);
		}
	}

	if(PChar.ColonyBuilding.SilverMine.Resize == true)
	{
		SetSelectable("SILVERMINE_RESIZE", false);
	}

    	//-------------------------------------------------------------------------------------------------

	string sIronMineStatus = "";

	if(PChar.ColonyBuilding.IronMine == false)
	{
		sIronMineStatus = GetConvertStrWithReplace("Variable_Colony_195", "Interface.txt", "#space#", " ");
		iColor = argb(255,255,128,128);
	}
	else
	{
		if(PChar.ColonyBuilding.IronMine.Resize == true)
		{
			sIronMineStatus = GetConvertStrWithReplace("Variable_Colony_196", "Interface.txt", "#space#", " ");
		}
		else
		{
			sIronMineStatus = GetConvertStrWithReplace("Variable_Colony_197", "Interface.txt", "#space#", " ");
		}
		iColor = argb(255,128,255,128);
	}

	CreateString(true,"IronMineStatus", GetConvertStrWithReplace("Variable_Colony_198", "Interface.txt", "#space#", " ") + sIronMineStatus, FONT_NORMAL, iColor, 645,493,SCRIPT_ALIGN_LEFT, 1.0);

	if(PChar.ColonyBuilding.IronMine == false)
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"IronMineCost", GetConvertStrWithReplace("Variable_Colony_199", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.IronMine.Cost), FONT_NORMAL, COLOR_NORMAL, 645,513,SCRIPT_ALIGN_LEFT,1.0);
		else CreateString(true,"IronMineCost", GetConvertStrWithReplace("Variable_Colony_200", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.IronMine.Cost), FONT_NORMAL, COLOR_NORMAL, 645,513,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		GameInterface.strings.IronMineCost = "";
	}

	if(PChar.ColonyBuilding.IronMine == true)
	{
		SetSelectable("IRONMINE_OPEN", false);
	}
	else
	{
		if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.IronMine.Cost/2;
		else NeedMoney = PChar.ColonyBuilding.IronMine.Cost;

		if(PChar.ColonyBuilding.Expidition == true && PChar.ColonyBuilding.Expidition.BuildingTime == false)
		{
			if(GetMyColonyMoney() < sti(NeedMoney))
			{
				SetSelectable("IRONMINE_OPEN", false);
			}
			else
			{
				SetSelectable("IRONMINE_OPEN", true);
			}
		}
		else
		{
			SetSelectable("IRONMINE_OPEN", false);
		}
	}

	if(PChar.ColonyBuilding.IronMine == true)
	{
		SetNodeUsing("IRONMINE_OPEN", false);
		SetNodeUsing("IRONMINE_RESIZE", true);

		if(PChar.ColonyBuilding.IronMine.Resize == false)
		{
			if(CheckAttribute(pchar, "VedekerDiscount")) CreateString(true,"IronMineResizeCost", GetConvertStrWithReplace("Variable_Colony_201", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.IronMine.ResizeCost), FONT_NORMAL, COLOR_NORMAL, 645,513,SCRIPT_ALIGN_LEFT,1.0);
			else CreateString(true,"IronMineResizeCost", GetConvertStrWithReplace("Variable_Colony_202", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.IronMine.ResizeCost), FONT_NORMAL, COLOR_NORMAL, 645,513,SCRIPT_ALIGN_LEFT,1.0);
		}
		else
		{
			GameInterface.strings.IronMineResizeCost = "";
		}

	    if(CheckAttribute(pchar, "VedekerDiscount")) NeedMoney = PChar.ColonyBuilding.IronMine.ResizeCost/2;
		else NeedMoney = PChar.ColonyBuilding.IronMine.ResizeCost;

		if(GetMyColonyMoney() >= sti(NeedMoney) && PChar.ColonyBuilding.IronMine.BuildingTime == false)
		{
			SetSelectable("IRONMINE_RESIZE", true);
		}
		else
		{
			SetSelectable("IRONMINE_RESIZE", false);
		}
	}

	if(PChar.ColonyBuilding.IronMine.Resize == true)
	{
		SetSelectable("IRONMINE_RESIZE", false);
	}
}

void ClearAllElements()
{
	PChar.Colony.Interface.UpMenu = "NormalBuilds";
	PChar.Colony.Interface.DownMenu = "ProBuilds";

	GameInterface.pictures.BankBorder.tex = "";
	GameInterface.pictures.BankBorder.pic = "";
	GameInterface.pictures.BankPicture.tex = "";
	GameInterface.pictures.BankPicture.pic = "";
	GameInterface.pictures.ChurchBorder.tex = "";
	GameInterface.pictures.ChurchBorder.pic = "";
	GameInterface.pictures.ChurchPicture.tex = "";
	GameInterface.pictures.ChurchPicture.pic = "";
	GameInterface.pictures.HeadPortBorder.tex = "";
	GameInterface.pictures.HeadPortBorder.pic = "";
	GameInterface.pictures.HeadportPicture.tex = "";
	GameInterface.pictures.HeadportPicture.pic = "";
	GameInterface.pictures.BankBorder.tex = "";
	GameInterface.pictures.BankBorder.pic = "";
	GameInterface.pictures.BankPicture.tex = "";
	GameInterface.pictures.BankPicture.pic = "";
	GameInterface.pictures.ChurchBorder.tex = "";
	GameInterface.pictures.ChurchBorder.pic = "";
	GameInterface.pictures.ChurchPicture.tex = "";
	GameInterface.pictures.ChurchPicture.pic = "";
	GameInterface.pictures.HeadPortBorder.tex = "";
	GameInterface.pictures.HeadPortBorder.pic = "";
	GameInterface.pictures.HeadportPicture.tex = "";
	GameInterface.pictures.HeadportPicture.pic = "";
	GameInterface.pictures.ExpiditionBorder.tex = "";
	GameInterface.pictures.ExpiditionBorder.pic = "";
	GameInterface.pictures.ExpiditionPicture.tex = "";
	GameInterface.pictures.ExpiditionPicture.pic = "";
	GameInterface.pictures.StoreHouseBorder.tex = "";
	GameInterface.pictures.StoreHouseBorder.pic = "";
	GameInterface.pictures.StoreHousePicture.tex = "";
	GameInterface.pictures.StoreHousePicture.pic = "";
	GameInterface.pictures.PlantationBorder.tex = "";
    	GameInterface.pictures.PlantationBorder.pic = "";
	GameInterface.pictures.PlantationPicture.tex = "";
    	GameInterface.pictures.PlantationPicture.pic = "";
	GameInterface.pictures.GoldMineBorder.tex = "";
    	GameInterface.pictures.GoldMineBorder.pic = "";
	GameInterface.pictures.GoldMinePicture.tex = "";
    	GameInterface.pictures.GoldMinePicture.pic = "";
	GameInterface.pictures.SilverMineBorder.tex = "";
    	GameInterface.pictures.SilverMineBorder.pic = "";
	GameInterface.pictures.SilverMinePicture.tex = "";
    	GameInterface.pictures.SilverMinePicture.pic = "";
	GameInterface.pictures.IronMineBorder.tex = "";
    	GameInterface.pictures.IronMineBorder.pic = "";
	GameInterface.pictures.IronMinePicture.tex = "";
    	GameInterface.pictures.IronMinePicture.pic = "";
	DisableString("NormalBuildHeader");
	DisableString("StoreHeader");
	DisableString("StoreStatus");
	DisableString("StoreCost");
	DisableString("ShipyardHeader");
	DisableString("ShipyardStatus");
	DisableString("ShipyardCost");
	DisableString("TavernHeader");
	DisableString("TavernStatus");
	DisableString("TavernCost");
	DisableString("BankHeader");
	DisableString("BankStatus");
	DisableString("BankCost");
	DisableString("ChurchHeader");
	DisableString("ChurchStatus");
	DisableString("ChurchCost");
	DisableString("HeadPortHeader");
	DisableString("HeadPortStatus");
	DisableString("HeadPortCost");
	DisableString("ExpiditionHeader");
	DisableString("ExpiditionStatus");
	DisableString("ExpiditionCost");
	DisableString("PlantationHeader");
	DisableString("PlantationStatus");
	DisableString("PlantationCost");
	DisableString("GoldMineHeader");
	DisableString("GoldMineStatus");
	DisableString("GoldMineCost");
	DisableString("GoldMineResizeCost");
	DisableString("SilverMineHeader");
	DisableString("SilverMineStatus");
	DisableString("SilverMineCost");
	DisableString("SilverMineResizeCost");
	DisableString("IronMineHeader");
	DisableString("IronMineStatus");
	DisableString("IronMineCost");
	DisableString("IronMineResizeCost");
	DisableString("StoreHouseHeader");
	DisableString("StoreHouseStatus");
	DisableString("StoreHouseCost");
}

////////////////////////////////////////////////////////////////////////////////////
// TAKE MONEY TO TRESURY
////////////////////////////////////////////////////////////////////////////////////
void ShowTakeMoneyWindow()
{
	ClearAllElements();

	GameInterface.pictures.StoreBorder.tex = "";
	GameInterface.pictures.StoreBorder.pic = "";
	GameInterface.pictures.ShipyardBorder.tex = "";
	GameInterface.pictures.ShipyardBorder.pic = "";
	GameInterface.pictures.TavernBorder.tex = "";
	GameInterface.pictures.TavernBorder.pic = "";
	GameInterface.pictures.StorePicture.tex = "";
	GameInterface.pictures.StorePicture.pic = "";
	GameInterface.pictures.ShipyardPicture.tex = "";
	GameInterface.pictures.ShipyardPicture.pic = "";
	GameInterface.pictures.TavernPicture.tex = "";
	GameInterface.pictures.TavernPicture.pic = "";

	GameInterface.pictures.ProBuild.tex = "";
	GameInterface.pictures.ProBuild.pic = "";
	GameInterface.pictures.GoldPicture.tex = "";
	GameInterface.pictures.GoldPicture.pic = "";
	GameInterface.pictures.NalogPicture.tex = "";
	GameInterface.pictures.NalogPicture.pic = "";

    	GameInterface.strings.GoldHeader = "";
    	GameInterface.strings.GoldQuantity = "";
    	GameInterface.strings.GoldQuantityContinue = "";
    	GameInterface.strings.ProBuildHeader = "";
    	GameInterface.strings.Nalog = "";
    	GameInterface.strings.NalogContinue = "";
    	GameInterface.strings.NalogHeader = "";
    	GameInterface.strings.NalogSelect = "";
    	GameInterface.strings.PopulationHeader = "";
    	GameInterface.strings.PopulationHeader = "";
    	GameInterface.strings.ColonyStatus = "";
    	GameInterface.strings.ColonyStatusContinue = "";
    	GameInterface.strings.Population = "";
    	GameInterface.strings.PopulationContinue = "";
    	GameInterface.strings.PopulationOptimal = "";
    	GameInterface.strings.PopulationMaxContinue = "";
    	GameInterface.strings.PopulationMorale = "";
    	GameInterface.strings.PopulationMoraleContinue = "";
    	GameInterface.strings.MoraleUpCost = "";
    	GameInterface.strings.MoraleUpCostContinue = "";
    	GameInterface.strings.YourMoney = "";
    	GameInterface.strings.YourMoneyContinue = "";
    	GameInterface.strings.StoreHouseCost = "";
	GameInterface.strings.StoreHouseResizeCost = "";
	GameInterface.strings.PlantationCost = "";
	GameInterface.strings.PlantationResizeCost = "";

	EnableDisableMainInterface(false);

	SetNodeUsing("FRAME3", true);
	SetNodeUsing("TAKE_MONEY_STRING", true);
	SetNodeUsing("TAKE_MONEY_LEFT", true);
	SetNodeUsing("TAKE_MONEY_RIGHT", true);
	SetNodeUsing("TAKE_MONEY_LEFT_ALL", true);
	SetNodeUsing("TAKE_MONEY_RIGHT_ALL", true);
	SetNodeUsing("CANCEL_TAKE_MONEY", true);
	SetNodeUsing("OK_TAKE_MONEY", true);
	SetNodeUsing("MONEY_ALL_EDIT_2", true);

	GameInterface.TAKE_MONEY_STRING.str = 0;

	CreateString(true,"TakeMoney_Header", GetConvertStrWithReplace("Variable_Colony_203", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 322,122,SCRIPT_ALIGN_LEFT, 1.5);
	CreateImage("TakeMoney_Image", "GOLD_ICON", "Gold", 470,180,550,260);

	CreateString(true,"TakeMoney_YouMoney", GetConvertStrWithReplace("Variable_Colony_204", "Interface.txt", "#space#", " ") + sti(PChar.money), FONT_NORMAL, argb(255,255,255,128), 280,200,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"TakeMoney_TresuryMoney", GetConvertStrWithReplace("Variable_Colony_205", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.Money), FONT_NORMAL, argb(255,255,255,128), 280,220,SCRIPT_ALIGN_LEFT, 1.0);
}

void EnableDisableMainInterface(bool bEnable)
{
	SetNodeUsing("FRAME1", bEnable);
	SetNodeUsing("FRAME1_1", bEnable);
	SetNodeUsing("FRAME1_2", bEnable);
	SetNodeUsing("FRAME2", bEnable);
	SetNodeUsing("FRAME2_1", bEnable);
	SetNodeUsing("BORDERS", bEnable);
	SetNodeUsing("STORE_OPEN", bEnable);
	SetNodeUsing("SHIPYARD_OPEN", bEnable);
	SetNodeUsing("TAVERN_OPEN", bEnable);
	SetNodeUsing("BANK_OPEN", bEnable);
	SetNodeUsing("CHURCH_OPEN", bEnable);
	SetNodeUsing("HEADPORT_OPEN", bEnable);
	SetNodeUsing("EXPIDITION_OPEN", bEnable);
	SetNodeUsing("STOREHOUSE_OPEN", bEnable);
	SetNodeUsing("STOREHOUSE_RESIZE", bEnable);
	SetNodeUsing("PLANTATION_OPEN", bEnable);
	SetNodeUsing("GOLDMINE_OPEN", bEnable);
	SetNodeUsing("SILVERMINE_OPEN", bEnable);
	SetNodeUsing("IRONMINE_OPEN", bEnable);
	SetNodeUsing("GOLDMINE_RESIZE", bEnable);
	SetNodeUsing("SILVERMINE_RESIZE", bEnable);
	SetNodeUsing("IRONMINE_RESIZE", bEnable);
	SetNodeUsing("PLANTATION_RESIZE", bEnable);
	SetNodeUsing("MORALE_UP", bEnable);
	SetNodeUsing("INSTALL_HIGH_NALOG", bEnable);
	SetNodeUsing("GIVEGOLD", bEnable);
	SetNodeUsing("SBROS", bEnable);
	SetNodeUsing("TAKE_MONEY", bEnable);
	SetNodeUsing("REPAIR_ALL_SHIPS", bEnable);
	SetNodeUsing("CHECK_NORMALBUILDS_LEFT_BUTTON", bEnable);
	SetNodeUsing("CHECK_NORMALBUILDS_RIGHT_BUTTON", bEnable);
	SetNodeUsing("CHECK_PROBUILDS_LEFT_BUTTON", bEnable);
	SetNodeUsing("CHECK_PROBUILDS_RIGHT_BUTTON", bEnable);
	SetNodeUsing("MONEY_LEFT", bEnable);
	SetNodeUsing("MONEY_RIGHT", bEnable);
	SetNodeUsing("MONEY_LEFT_ALL", bEnable);
	SetNodeUsing("MONEY_RIGHT_ALL", bEnable);
	SetNodeUsing("MONEY_ALL_EDIT_1", bEnable);
	SetNodeUsing("NALOG_LEFT", bEnable);
	SetNodeUsing("NALOG_RIGHT", bEnable);
	SetNodeUsing("MONEY_STRING", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION", bEnable);
}

void TakeMoneyCheckQty(bool bLeft, bool bAll)
{
	if(bLeft)
	{
		if(bAll)
		{
			GameInterface.TAKE_MONEY_STRING.str = 0;
		}
		else
		{
			GameInterface.TAKE_MONEY_STRING.str = sti(GameInterface.TAKE_MONEY_STRING.str) - 5000;
		}
	}
	else
	{
		if(bAll)
		{
			GameInterface.TAKE_MONEY_STRING.str = sti(PChar.money);
		}
		else
		{
			GameInterface.TAKE_MONEY_STRING.str = sti(GameInterface.TAKE_MONEY_STRING.str) + 5000;
		}
	}

	if(sti(GameInterface.TAKE_MONEY_STRING.str) < 0)
	{
		GameInterface.TAKE_MONEY_STRING.str = 0;
	}

	if(sti(GameInterface.TAKE_MONEY_STRING.str) > sti(PChar.money))
	{
		GameInterface.TAKE_MONEY_STRING.str = sti(PChar.money);
	}
}

void TakeMoneyTempUptade()
{
	if(sti(GameInterface.TAKE_MONEY_STRING.str) < 0)
	{
		GameInterface.TAKE_MONEY_STRING.str = 0;
	}

	if(sti(GameInterface.TAKE_MONEY_STRING.str) > sti(PChar.money))
	{
		GameInterface.TAKE_MONEY_STRING.str = sti(PChar.money);
	}
}

void CloseTakeMoneyWindow()
{
	GameInterface.TAKE_MONEY_STRING.str = 0;

	SetNodeUsing("FRAME3", false);
	SetNodeUsing("TAKE_MONEY_STRING", false);
	SetNodeUsing("TAKE_MONEY_LEFT", false);
	SetNodeUsing("TAKE_MONEY_RIGHT", false);
	SetNodeUsing("TAKE_MONEY_LEFT_ALL", false);
	SetNodeUsing("TAKE_MONEY_RIGHT_ALL", false);
	SetNodeUsing("CANCEL_TAKE_MONEY", false);
	SetNodeUsing("OK_TAKE_MONEY", false);
	SetNodeUsing("MONEY_ALL_EDIT_2", false);

	GameInterface.pictures.TakeMoney_Image.tex = "";
	GameInterface.pictures.TakeMoney_Image.pic = "";

    	GameInterface.strings.TakeMoney_Header = "";
    	GameInterface.strings.TakeMoney_YouMoney = "";
    	GameInterface.strings.TakeMoney_TresuryMoney = "";

	EnableDisableMainInterface(true);

	SetInformation();
	SetNalogInformation();
	SetMoneyInformation();
	SetColonyInformation();
	SetPopulationInformation();
}

void TakeMoneyDone()
{
	TakeMoneyTempUptade();

	int iMoney = sti(GameInterface.TAKE_MONEY_STRING.str);
	ChangeColonyMoney(iMoney, false);

	AddMoneyToCharacter(PChar, -iMoney);
	CloseTakeMoneyWindow();
}

////////////////////////////////////////////////////////////////////////////
// ИНФОРМАЦИЯ О ПОСТРОЙКЕ ЗДАНИЙ
////////////////////////////////////////////////////////////////////////////
void ShowInformationAboutBuildings()
{
	ClearAllElements();

	GameInterface.pictures.StoreBorder.tex = "";
	GameInterface.pictures.StoreBorder.pic = "";
	GameInterface.pictures.ShipyardBorder.tex = "";
	GameInterface.pictures.ShipyardBorder.pic = "";
	GameInterface.pictures.TavernBorder.tex = "";
	GameInterface.pictures.TavernBorder.pic = "";
	GameInterface.pictures.StorePicture.tex = "";
	GameInterface.pictures.StorePicture.pic = "";
	GameInterface.pictures.ShipyardPicture.tex = "";
	GameInterface.pictures.ShipyardPicture.pic = "";
	GameInterface.pictures.TavernPicture.tex = "";
	GameInterface.pictures.TavernPicture.pic = "";

	GameInterface.pictures.ProBuild.tex = "";
	GameInterface.pictures.ProBuild.pic = "";
	GameInterface.pictures.GoldPicture.tex = "";
	GameInterface.pictures.GoldPicture.pic = "";
	GameInterface.pictures.NalogPicture.tex = "";
	GameInterface.pictures.NalogPicture.pic = "";

    	GameInterface.strings.GoldHeader = "";
    	GameInterface.strings.GoldQuantity = "";
    	GameInterface.strings.GoldQuantityContinue = "";
    	GameInterface.strings.ProBuildHeader = "";
    	GameInterface.strings.Nalog = "";
    	GameInterface.strings.NalogContinue = "";
    	GameInterface.strings.NalogHeader = "";
    	GameInterface.strings.NalogSelect = "";
    	GameInterface.strings.PopulationHeader = "";
    	GameInterface.strings.PopulationHeader = "";
    	GameInterface.strings.ColonyStatus = "";
    	GameInterface.strings.ColonyStatusContinue = "";
    	GameInterface.strings.Population = "";
    	GameInterface.strings.PopulationContinue = "";
    	GameInterface.strings.PopulationOptimal = "";
    	GameInterface.strings.PopulationMaxContinue = "";
    	GameInterface.strings.PopulationMorale = "";
    	GameInterface.strings.PopulationMoraleContinue = "";
    	GameInterface.strings.MoraleUpCost = "";
    	GameInterface.strings.MoraleUpCostContinue = "";
    	GameInterface.strings.YourMoney = "";
    	GameInterface.strings.YourMoneyContinue = "";
    	GameInterface.strings.StoreHouseCost = "";
	GameInterface.strings.StoreHouseResizeCost = "";
	GameInterface.strings.PlantationCost = "";
	GameInterface.strings.PlantationResizeCost = "";

	EnableDisableMainInterface(false);
	EnableDisableBuildingInformation(true);

	SetCurrentNode("BUILDINGS_INFORMATION_EXIT");

	SetInformationAboutBuildings();
	SetInformationSelectTexture();
}

void EnableDisableBuildingInformation(bool bEnable)
{
	SetNodeUsing("FRAME4", bEnable);
	SetNodeUsing("FRAME5", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_EXIT", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_HEADER", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_SELECT_TEXTURE_HEADER", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_SELECT_TEXTURE_TEXT", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_BUILD", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_INFO", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_BUILD_PICTURE", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_BUILD_BORDER", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_LEFT", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_RIGHT", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_SELECT_TEXTURE_LEFT", bEnable);
	SetNodeUsing("BUILDINGS_INFORMATION_SELECT_TEXTURE_RIGHT", bEnable);
}

void SetInformationAboutBuildings()
{
	int iLngFile = LanguageOpenFile("BuildingsInformation.txt");

	SetFormatedText("BUILDINGS_INFORMATION_HEADER", GetConvertStrWithReplace("Variable_Colony_206", "Interface.txt", "#space#", " "));

	string sCurType = GetBuildNameFromCount();

	SetFormatedText("BUILDINGS_INFORMATION_BUILD", LanguageConvertString(iLngFile, sCurType));
	SetNewGroupPicture("BUILDINGS_INFORMATION_BUILD_PICTURE", GetCurrentTexture(), sCurType);

	string sInfo = LanguageConvertString(iLngFile, sCurType + "_Info");
	sInfo = sInfo + NewStr();
	sInfo = sInfo + LanguageConvertString(iLngFile, "AllInfo");

	SetFormatedText("BUILDINGS_INFORMATION_INFO", sInfo);
	LanguageCloseFile("BuildingsInformation.txt");
}

void SetInformationSelectTexture()
{
	SetFormatedText("BUILDINGS_INFORMATION_SELECT_TEXTURE_HEADER", GetConvertStrWithReplace("Variable_Colony_207", "Interface.txt", "#space#", " "));
	SetFormatedText("BUILDINGS_INFORMATION_SELECT_TEXTURE_TEXT", GetConvertStrWithReplace("Variable_Colony_208", "Interface.txt", "#space#", " ") + sti(PChar.ColonyBuilding.CurrentIconsTexture));

	SetInformationAboutBuildings();
}

void CloseInformationAboutBuildings()
{
	EnableDisableBuildingInformation(false);
	EnableDisableMainInterface(true);

	SetInformation();
	SetNalogInformation();
	SetMoneyInformation();
	SetColonyInformation();
	SetPopulationInformation();

	SetCurrentNode("SBROS");
}


void CheckInfoBuildCount(bool left)
{
	if(left)
	{
		iInfoBuildCount--;
	}
	else
	{
		iInfoBuildCount++;
	}

	if(iInfoBuildCount < 0) { iInfoBuildCount = 11; }
	if(iInfoBuildCount > 11) { iInfoBuildCount = 0; }

	SetInformationAboutBuildings();
}

string GetBuildNameFromCount()
{
	switch(iInfoBuildCount)
	{
		case 0: return "Store"; break;
		case 1: return "Shipyard"; break;
		case 2: return "Tavern"; break;
		case 3: return "Bank"; break;
		case 4: return "Church"; break;
		case 5: return "HeadPort"; break;
		case 6: return "StoreHouse"; break;
		case 7: return "Expedition"; break;
		case 8: return "Plantation"; break;
		case 9: return "GoldMine"; break;
		case 10: return "SilverMine"; break;
		case 11: return "IronMine"; break;
	}

	return "None";
}

void SelectTexture(bool left)
{
	if(left)
	{
		PChar.ColonyBuilding.CurrentIconsTexture = sti(PChar.ColonyBuilding.CurrentIconsTexture) - 1;
	}
	else
	{
		PChar.ColonyBuilding.CurrentIconsTexture = sti(PChar.ColonyBuilding.CurrentIconsTexture) + 1;
	}

	if(sti(PChar.ColonyBuilding.CurrentIconsTexture) < 1) { PChar.ColonyBuilding.CurrentIconsTexture = 3; }
	if(sti(PChar.ColonyBuilding.CurrentIconsTexture) > 3) { PChar.ColonyBuilding.CurrentIconsTexture = 1; }

	SetInformationSelectTexture();
}

string GetCurrentTexture()
{
	if(CheckAttribute(PChar, "ColonyBuilding.CurrentIconsTexture"))
	{
		return "COLONY_BUILDINGS_" + sti(PChar.ColonyBuilding.CurrentIconsTexture);
	}

	return "COLONY_BUILDINGS_1";
}