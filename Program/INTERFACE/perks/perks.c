
#event_handler("evntChrPerkDelay","procChrPerkDelay");
#event_handler("evntChrPerkDelayAnim","procChrPerkDelayAnim");

object ChrPerksList;

extern void extrnInitPerks();

void InitPerks()
{
	if( LoadSegment("interface\perks\perks_init.c") )
	{
		extrnInitPerks();
		UnloadSegment("interface\perks\perks_init.c");
	}
}

bool CheckCharacterPerk(ref chref, string perkName)
{
	if( CheckAttribute(chref,"perks.list."+perkName) ) return true;
	return false;
}

bool SetCharacterPerk(ref chref, string perkName)
{
	//Boyer mod to continue
	bool bReturn = false;
	if (perkName == "Grunt" || perkName == "Trader" || perkName == "Fencer" || perkName == "Adventurer" || perkName == "Buccaneer" || perkName == "Agent" || perkName == "SeaWolf")
		{SetSpeciality(chref, perkName);}
	else
		{chref.perks.list.(perkName) = true;}
	// разовые применения при назначении -->
	switch (perkName)
	{
		/*case "HPPlus":
			LAi_SetHP(chref, LAi_GetCharacterHP(chref) + 20, LAi_GetCharacterMaxHP(chref) + 20);
			return true; // нужен рефрешь

		break;

		case "EnergyPlus":
			SetEnergyToCharacter(chref);
			return true; // нужен рефрешь

		break; */

		case "Grus":
			return true; // нужен рефрешь
			bReturn = true;
		break;
	}
	// разовые применения при назначении <--
	//Boyer mod #20170318-25 to apply item equip logic with new skillset
	if(chref.id != pchar.id)
        CharacterCheckEquipAll(chref);
	//return false;
	return bReturn; // нужен рефрешь
}

void ActivateCharacterPerk(ref chref, string perkName)
{
	if( !CheckAttribute(&ChrPerksList,"list."+perkName) )
	{
		trace("Invalid perk name - " + perkName);
		return;
	}

	if(perkName == "rush")
	{
		if(CheckAttribute(chref, "chr_ai.Swift"))
		{
			DeleteAttribute(chref, "chr_ai.Swift");
			Log_Info(GetConvertStrWithReplace("Variable_LAi_character_2", "Logs.txt", "#space#", " "));
			if(CheckAttribute(chref, "quest.questflag.model") && chref.quest.questflag.model == "FX_StanS") UnmarkCharacter(chref);
		}		
		if(CheckAttribute(chref, "chr_ai.understun"))
		{
			DeleteAttribute(chref, "chr_ai.understun");
			if(CheckAttribute(chref, "quest.questflag.model") && chref.quest.questflag.model == "FX_StanH") UnmarkCharacter(chref);
			LAi_SetPlayerType(chref);
			LAi_SetFightMode(chref, true);
		}
	}

	int timeDelay = 0;
	int timeDuration = 0;

	if( CheckAttribute(&ChrPerksList,"list."+perkName+".TimeDuration") )
	{	timeDelay = sti(ChrPerksList.list.(perkName).TimeDuration);
		timeDuration = timeDelay;
	}
	if( CheckAttribute(&ChrPerksList,"list."+perkName+".TimeDelay") )
	{	timeDelay = sti(ChrPerksList.list.(perkName).TimeDelay);
		if(timeDuration<=0)	{timeDuration=timeDelay;}
	}
	
    // boal fix
    // иначе после применения давался ГГ

    int cn;
    if (!CheckCharacterPerk(chref, perkName))
    {

        cn = GetOfficersPerkUsingIdx(chref, perkName);
        if (cn != -1)
        chref = GetCharacter(cn);
    }
    // <--
	chref.perks.list.(perkName).delay = timeDelay;
	chref.perks.list.(perkName).active = timeDuration;

	//if(sti(chref.index) == nMainCharacterIndex)
	if (sti(chref.index) == nMainCharacterIndex || isOfficerInShip(chref, false)) // наследие перка от офа boal 30.06.06
	{
		AddPerkToActiveList(perkName);
	}

	if(timeDelay>0) PostEvent("evntChrPerkDelay",1000,"sl",perkName,sti(chref.index));
	Event("eSwitchPerks","l",sti(chref.index));
	// fix boal всегда для ГГ
	Event("eSwitchPerks","l", GetMainCharacterIndex());
}

bool GetCharacterPerkUsing(ref chref, string perkName)
{   // можно ли пользовать умение (задержки нет)
	if( !CheckAttribute(chref,"perks.list."+perkName) ) return false;
	if( CheckAttribute(chref,"perks.list."+perkName+".delay") ) return false;
	return true;
}

bool GetOfficersPerkUsing(ref chref, string perkName)
{ // boal препишем внутрянку под новых офов, че в к3 не было? не ведаю.
	string  sOfficerType;
	ref   offc;
	bool  ok = false; // boal fix 25.03.05 проверка на запрет
	bool  okDelay = true;
	int   cn;
	if (GetCharacterPerkUsing(chref, perkName)) {return true;} // босс отдельно
	if (!CheckAttribute(chref,"perks.list."+perkName))  // у гг нет перка вообще, тогда смотрим офов, иначе выход
	{
		for(int i=1; i<=6; i++)
		{
			sOfficerType = GetOfficerTypeByNum(i);
			if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
			{
				if(!CheckAttribute(chref, "fellows")) {continue;} //Boyer fix added
				cn = sti(chref.Fellows.Passengers.(sOfficerType));
				if(cn<0) {continue;}
				offc = &Characters[cn];
				if (CheckAttribute(offc, "perks.list."+perkName) )          ok = true;
				if (CheckAttribute(offc, "perks.list."+perkName+".delay") ) okDelay = false;
				//if (GetCharacterPerkUsing(chref, perkName) return true;
			}
		}
	}
	return (ok) && (okDelay);
}

// boal
int GetOfficersPerkUsingIdx(ref chref, string perkName)
{
	string  sOfficerType;
	int     cn;
	if (GetCharacterPerkUsing(chref, perkName)) {return sti(chref.index);} // босс отдельно
	for(int i=1; i<=6; i++)
	{
		sOfficerType = GetOfficerTypeByNum(i);
		if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
		{
			cn = sti(chref.Fellows.Passengers.(sOfficerType));
			if(cn<0) {continue;}
			if (GetCharacterPerkUsing(&Characters[cn], perkName) ) {return cn;}
		}
	}
	return -1;
}

bool IsCharacterPerkOn(ref chref, string perkName)
{
	aref arRoot, arBase;
	makearef(arRoot,chref.perks.list);
	if( !CheckAttribute(arRoot,perkName) ) return false;
	makearef(arBase,ChrPerksList.list.(perkName));
	if( CheckAttribute(arBase,"TimeDuration") || CheckAttribute(arBase,"TimeDelay") ) {
		return CheckAttribute(arRoot,perkName+".active");
	}
	return true;
}

void CharacterPerkOff(ref chref, string perkName)
{
	DeleteAttribute(chref,"perks.list."+perkName+".active");
	Event("eSwitchPerks","l",sti(chref.index));
	// fix boal всегда для ГГ
	Event("eSwitchPerks","l", GetMainCharacterIndex());
	if (sti(chref.index) == nMainCharacterIndex || isOfficerInShip(chref, false)) // наследие перка от офа boal 30.06.06
	{
		/* Удаляем перки без анимации с экрана. У перков с анимацией свой путь */
		if(!CheckAttribute(&ChrPerksList, "list." + perkName + ".UseAnimation"))
		{
			DelPerkFromActiveList(perkName);
		}
	}
}

bool CheckOfficersPerk(ref chref, string perkName)
{ // активность перка в данный момент, для временных - режим активности, а не задержки
	bool ret = CheckOfficersPerkWOSelf(chref, perkName);
	if (ret) return true;
	// самого НПС
	if(IsCharacterPerkOn(chref,perkName) == true)
	{
		return true;
	}
	return false;
}

bool CheckOfficersPerkWOSelf(ref chref, string perkName)
{
	int     iOfficer = -1;
	string  sOfficerType;
	if(chref.id == pchar.id)
	{
		// boal новая схема наследования. switch не наш метод
		if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType"))
		{
			sOfficerType = ChrPerksList.list.(perkName).OfficerType;
			iOfficer = sti(pchar.Fellows.Passengers.(sOfficerType));
		}
	}

	if(iOfficer != -1)
	{
		if(IsCharacterPerkOn(GetCharacter(iOfficer), perkName) == true )
		{
			return true;
		}
	}
	return false;
}
// нигде не юзан
bool CheckCompanionsPerk(ref chref, string perkName)
{
	int i,cn;
	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(chref,i);
		if(cn>=0)
		{	if( IsCharacterPerkOn(GetCharacter(cn),perkName) )	{return true;}
		}
	}
	return false; // fix by boal
}

void procChrPerkDelayAnim()
{
	string perkName = GetEventData();
	int iActive = GetEventData();
	UpdatePerkIcon(perkName, sti(ChrPerksList.list.(perkName).UseAnimationIconCnt) - iActive);
	if(iActive - 1 > 0)
	{
		PostEvent("evntChrPerkDelayAnim",(sti(ChrPerksList.list.(perkName).TimeDuration) * 1000) / sti(ChrPerksList.list.(perkName).UseAnimationIconCnt),"sl",perkName,iActive - 1);
	}
}

void procChrPerkDelay()
{
	
	string perkName = GetEventData();
	int chrIdx = GetEventData();

	aref arPerk;
	makearef(arPerk,Characters[chrIdx].perks.list.(perkName));
	if( !CheckAttribute(arPerk,"delay") ) return;
	int delay = sti(arPerk.delay);
	// фикс в каюте, палубе, абордаже
 	bool ok;
 	ok = (!bAbordageStarted) && (!bSeaReloadStarted);
 	if (ok || perkName == "Rush")
 	{
		delay--;
	}
	/* Проверяем, что перк наш или офицера а не компаньона */
	int iOfficer = 1;
	if(CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType"))
	{
		string sOfficerType = ChrPerksList.list.(perkName).OfficerType;
		iOfficer = sti(pchar.Fellows.Passengers.(sOfficerType));
	}

	if( CheckAttribute(arPerk,"active") )
	{
		int iActive = sti(arPerk.active)-1;
		if( iActive>0 )
		{
			arPerk.active = iActive;
			/* Включение анимации для отрисованных перков */
			/* chrIdx 1 - ГГ, проверка что перк выдал не компаньон, иначе анимация будет накладываться при использовании перка компаньонами */
			if (chrIdx == iOfficer || chrIdx == 1)
			{
				/* Рисуем анимацию если она поддерживается перком */
				if(CheckAttribute(&ChrPerksList, "list." + perkName + ".UseAnimation"))
				{
					/* Проверяем переход между сушей и морем */
					bool seaStateAnim = sti(ChrPerksList.list.(perkName).seaPerk) && (bSeaActive) && (!bSeaReloadStarted);
                    bool landStateAnim = (!sti(ChrPerksList.list.(perkName).seaPerk)) && (!bSeaActive) && (bSeaReloadStarted);
                    bool rush_abord = false;
                    if(perkName == "Rush" && bAbordageStarted)
                    {
                        rush_abord = true;
                    }

                    if(seaStateAnim || landStateAnim || rush_abord)
					{
						/* Для перков, у которых количество кадров сделано под время действия, т.е. 1 fps, например у морских */
						if(sti(ChrPerksList.list.(perkName).TimeDuration) >= sti(ChrPerksList.list.(perkName).UseAnimationIconCnt))
						{
							if(!isPerkInActiveList(perkName))
							{
								AddAndUpdatePerkIcon(perkName, sti(ChrPerksList.list.(perkName).UseAnimationIconCnt) - iActive);
							}
							else
							{
								UpdatePerkIcon(perkName, sti(ChrPerksList.list.(perkName).UseAnimationIconCnt) - iActive);
							}
						}
						/* Для перков, у которых количество кадров больше чем время действия, т.е. 1 fps, например для берсерка */
						else
						{
							if(getPerkCurrentIconID(perkName) == 0)
							{
								/* 10 - кол-во кадров в секунду */
								if(getPerkCurrentIconID(perkName) != sti(ChrPerksList.list.(perkName).UseAnimationIconCnt) - ((iActive + 1) * (sti(ChrPerksList.list.(perkName).UseAnimationIconCnt) / 10)))
								{
									if(!isPerkInActiveList(perkName))
									{
										AddAndUpdatePerkIcon(perkName, sti(ChrPerksList.list.(perkName).UseAnimationIconCnt) - iActive);
									}
									PostEvent("evntChrPerkDelayAnim",0,"sl",perkName, ((iActive + 1) * (sti(ChrPerksList.list.(perkName).UseAnimationIconCnt) / 10)));
								}
							}
						}
					}
					else
					{
						/* Перешли с суши на море или наоборот и нужно удалить перк с экрана */
						if(CheckAttribute(&ChrPerksList, "list." + perkName + ".UseAnimation"))
						{
							DelPerkFromActiveList(perkName);
						}
					}
				}
			}
		}
		else
		{
			/* Сюда попадаем когда перка закончил действие */
			CharacterPerkOff(GetCharacter(chrIdx),perkName);
		}
	}
	else
	{
		/* chrIdx 1 - ГГ, проверка что перк выдал не компаньон, иначе анимация будет накладываться при откате перка компаньонами */
		if (chrIdx == iOfficer || chrIdx == 1)
		{
			/* Рисуем анимацию отката */
			if(CheckAttribute(&ChrPerksList, "list." + perkName + ".UseAnimation") && delay > 1)
			{
				/* Проверяем переход между сушей и морем */
				bool seaStateCoolDown = sti(ChrPerksList.list.(perkName).seaPerk) && (bSeaActive) && (!bSeaReloadStarted);
				bool landStateCoolDown = (!sti(ChrPerksList.list.(perkName).seaPerk)) && (!bSeaActive) && (bSeaReloadStarted);
				if(seaStateCoolDown || landStateCoolDown)
				{
					int tmp = getAnimFpsCnt(perkName);
					if(tmp != 0)
					{
						/* Проверяем наличие иконки перка на экране через объект objActivePerkShower и если её нет - рисуем согласно проценту заполнения */
						if(!isPerkInActiveList(perkName))
						{
							AddAndUpdatePerkIcon(perkName, (delay / tmp) - 1);
						}
						else if(delay % tmp == 0)
						{
							UpdatePerkIcon(perkName, (delay / tmp) - 1);
						}
					}
				}
			}
		}
	}

	if( delay<=0 )
	{
		/* Сюда попадаем, когда закончился кулдаун */
		DeleteAttribute(&Characters[chrIdx],"perks.list."+perkName+".delay");
		DeleteAttribute(&Characters[chrIdx],"perks.list."+perkName+".active");
		PostEvent("evntPerkAgainUsable",1);
		/* Удаляем анимированный перк с экрана. Неанимированный перк удаляется раньше в CharacterPerkOff */
		if(CheckAttribute(&ChrPerksList, "list." + perkName + ".UseAnimation"))
		{
			DelPerkFromActiveList(perkName);
		}
	}
	else
	{
		Characters[chrIdx].perks.list.(perkName).delay = delay;
		PostEvent("evntChrPerkDelay",1000,"sl",perkName,chrIdx);
	}
}

void EnableUsingAbility(ref chref,string perkName)
{
    // boal fix
    // иначе после применения давался ГГ
	int cn;
    if (!CheckCharacterPerk(chref, perkName))
    {

        cn = GetOfficersPerkUsingIdx(chref, perkName);
        if (cn != -1)
        chref = GetCharacter(cn);
    }
    // <--

	Event("evntChrPerkDelay","sl",perkName, sti(chref.index));
}

void PerkLoad(bool noDelay)
{
//	int iRDTSC = RDTSC_B();
	string locName = pchar.location;
	aref arPerksRoot,arPerk;
	int i,j,n,tmpi;
	for(i=0; i<MAX_CHARACTERS; i++)
	{
		makearef(arPerksRoot,Characters[i].perks.list);
		n = GetAttributesNum(arPerksRoot);
		for(j=0; j<n; j++)
		{
			arPerk = GetAttributeN(arPerksRoot,j);
			if( CheckAttribute(arPerk,"delay") )
			{
				if (noDelay) {
					DeleteAttribute(arPerk,"delay");
					DeleteAttribute(arPerk,"active");
					PostEvent("evntPerkAgainUsable",1);
					continue;
				}

				tmpi = sti(arPerk.delay);
				if( tmpi>0 )
				{
					PostEvent("evntChrPerkDelay",1000,"sl",GetAttributeName(arPerk),i);
				}
			}
		}
	}

//	trace("TIME!!! PerkLoad() = " + RDTSC_E(iRDTSC));
}

// boal под новые слоты -->
void ClearActiveChrPerks(ref chref)
{
	int i,cn;
    ref offc; // boal
    string  sOfficerType;

    if (bAbordageStarted || bSeaReloadStarted) return;

	ClearActive(chref); // босс отдельно
	if (CheckAttribute(chref, "Fellows.Passengers")) // не у всех есть
	{
		for (i=1; i<=6; i++)
		{
			sOfficerType = GetOfficerTypeByNum(i);
			cn = sti(chref.Fellows.Passengers.(sOfficerType));
			if(cn<0) {continue;}
			offc = &Characters[cn];
			ClearActive(offc);
		}
	}
}

void ClearActive(ref offic)
{
	aref arPerksRoot, arPerk;
	int i,n;

	makearef(arPerksRoot, offic.perks.list);

	n = GetAttributesNum(arPerksRoot);
	for (i=0; i<n; i++)
	{
		arPerk = GetAttributeN(arPerksRoot,i);

		if (CheckAttribute(arPerk, "delay"))
        {
			DeleteAttribute(arPerk,"delay");
		}
		if (CheckAttribute(arPerk,"active"))
        {
			DeleteAttribute(arPerk,"active");
		}
	}
}
// был баг К3, этот перк не работал вовсе
void AcceptWindCatcherPerk(ref refCharacter)
{
    int  nShipType;
    ref  refBaseShip, refRealShip;

	nShipType = GetCharacterShipType(refCharacter);
	if (nShipType==SHIP_NOTUSED) return;

	refRealShip = GetRealShip(nShipType);
	refBaseShip = GetShipByType(sti(refRealShip.BaseType));

	if (CheckOfficersPerk(refCharacter, "WindCatcher"))
	{
		refRealShip.InertiaAccelerationX	= stf(refBaseShip.InertiaAccelerationX) + stf(refBaseShip.InertiaAccelerationX) / 10.0;
		refRealShip.InertiaAccelerationY	= stf(refBaseShip.InertiaAccelerationY) + stf(refBaseShip.InertiaAccelerationY) / 10.0;
		refRealShip.InertiaAccelerationZ	= stf(refBaseShip.InertiaAccelerationZ) + stf(refBaseShip.InertiaAccelerationZ) / 10.0;
		// потмоу что перк помогает только быстрее набирать скорость, нет торможения
	}
	else
	{   // вернем, если перк снят
	    refRealShip.InertiaAccelerationX	= stf(refBaseShip.InertiaAccelerationX);
		refRealShip.InertiaAccelerationY	= stf(refBaseShip.InertiaAccelerationY);
		refRealShip.InertiaAccelerationZ	= stf(refBaseShip.InertiaAccelerationZ);
	}
	refRealShip.InertiaAccelerationY	= stf(refBaseShip.InertiaAccelerationY) * (1.0 + ((CheckAttribute(refRealShip,"Tuning.SailsSpecial") - 2 * CheckAttribute(refRealShip,"Tuning.HullSpecial")) / 6.0));
	if (iArcadeSails == 0) // момент инерции ниже для тактики
	{
	    refRealShip.InertiaAccelerationY = stf(refRealShip.InertiaAccelerationY) / 2.0;
	}
}
