object objActivePerkShower;
int animPerkCnt = 0;	/*!< Кол-во анимированных перков (морских или на суше), используется для динамического добавления перков без "гвоздей" */

#event_handler(EVENT_LOCATION_LOAD,"procLoadIntoNew");

void InitActivePerkShower()
{
    //#20200706-01
    float fHtRatio = stf(Render.screen_y) / screenscaling;
	objActivePerkShower.ShowParam.PosRect.left		= sti(showWindow.right) - RecalculateHIcon(makeint((48+132) * fHtRatio));
	objActivePerkShower.ShowParam.PosRect.top		= RecalculateVIcon(makeint(445* fHtRatio));
	objActivePerkShower.ShowParam.PosRect.right		= sti(showWindow.right) - RecalculateHIcon(makeint(48* fHtRatio));
	objActivePerkShower.ShowParam.PosRect.bottom	= sti(showWindow.bottom) - RecalculateVIcon(makeint(28* fHtRatio));
	objActivePerkShower.ShowParam.IconSize.horz		= RecalculateHIcon(makeint(48* fHtRatio));
	objActivePerkShower.ShowParam.IconSize.vert		= RecalculateVIcon(makeint(48* fHtRatio));
	objActivePerkShower.ShowParam.IconSpace.horz	= RecalculateHIcon(2);
	objActivePerkShower.ShowParam.IconSpace.vert	= RecalculateVIcon(2);
}

void procLoadIntoNew()
{
	UnloadActivePerkShower();
	SetEventHandler("frame","LoadActivePerkShower",1);
}

void LoadActivePerkShower()
{
	DelEventHandler("frame","LoadActivePerkShower");

	DeleteAttribute(&objActivePerkShower,"PerkList.list");
	DeleteAttribute(&objActivePerkShower,"Textures");

	// информация о текстурах
	if(bSeaActive && !bAbordageStarted)
	{	// морская часть
		if(InterfaceStates.AltIntIcons) objActivePerkShower.Textures.t0.file = "battle_interface\list_icons_Konshud.dds";
		else objActivePerkShower.Textures.t0.file = "battle_interface\list_icons.dds";
		objActivePerkShower.Textures.t0.horz = 16;
		objActivePerkShower.Textures.t0.vert = 8;
		/* Добавляем анимированные перки для моря */
		addAnimationToPerk("ImmediateReload", "battle_interface\ImmediateReload.dds", "battle_interface\ImmediateReloadAlt.dds", 60, 8, 8, true);
		addAnimationToPerk("Turn180", "battle_interface\Turn180.dds", "battle_interface\Turn180Alt.dds", 60, 8, 8, true);
		addAnimationToPerk("InstantRepair", "battle_interface\InstantRepair.dds", "battle_interface\InstantRepairAlt.dds", 30, 8, 4, true);
	}
	else
	{	// земная часть
		if(InterfaceStates.AltIntIcons) objActivePerkShower.Textures.t0.file = "battle_interface\LandCommands_Konshud.dds";
		else objActivePerkShower.Textures.t0.file = "battle_interface\LandCommands.dds";
		objActivePerkShower.Textures.t0.horz = 16;
		objActivePerkShower.Textures.t0.vert = 4;
		/* Добавляем анимированные перки для суши */
		addAnimationToPerk("Rush", "battle_interface\Rush_fast.dds", "battle_interface\RushAlt_fast.dds", 60, 8, 8, false);
	}

	aref arPerksRoot,arPerk;
	makearef(arPerksRoot,pchar.perks.list);
	int perksQ = GetAttributesNum(arPerksRoot);

	string stmp;
	int idx = 0;
	for(int j=0; j<perksQ; j++)
	{
		arPerk = GetAttributeN(arPerksRoot,j);
		if( CheckAttribute(arPerk,"delay") )
		{
			if( CheckAttribute(arPerk,"active") )
			{
				string tmpStr = GetAttributeName(arPerk);
				/* Проверяем переход между сушей и морем */
				bool seaState = sti(ChrPerksList.list.(tmpStr).seaPerk) && (bSeaActive) && (!bSeaReloadStarted);
				bool landState = (!sti(ChrPerksList.list.(tmpStr).seaPerk)) && (!bSeaActive) && (bSeaReloadStarted);
				if(seaState || landState)
				{
					AddAndUpdatePerkIcon(GetAttributeName(arPerk), sti(ChrPerksList.list.(tmpStr).UseAnimationIconCnt) - sti(arPerk.active)-1);
				}
				else
				{
					/* Перешли с суши на море или наоборот и нужно удалить перк с экрана */
					if(CheckAttribute(&ChrPerksList, "list." + tmpStr + ".UseAnimation"))
					{
						DelPerkFromActiveList(tmpStr);
					}
				}
			}
		}
	}

	CreateEntity(&objActivePerkShower,"ActivePerkShower");
	if(bSeaActive && !bAbordageStarted)
	{	// морская часть
		LayerAddObject(SEA_EXECUTE,&objActivePerkShower,-1);
		LayerAddObject(SEA_REALIZE,&objActivePerkShower,-1);
	}
	else
	{
		LayerAddObject(EXECUTE,&objActivePerkShower,-1);
		LayerAddObject(REALIZE,&objActivePerkShower,-1);
	}
}

/*!
 * \brief Добавить поддержку анимации для перка. Так же необходимо указать пути к атласам в функции "GetPerkTextureName" или реализовать
 * возврат свойства objActivePerkShower.Textures.tx.file в зависимости от перка
 * \param perkID идентификатор перка
 * \param perkIconPath путь к атласу иконок
 * \param perkAltIconPath путь к атласу иконок альтернативного интерфейса
 * \param perkIconCnt Количество иконок в файле .dds для анимации перка, необходимо для корректного вызова обновления иконки перка в perks.c
 * \param horzCnt кол-во иконок в атласе по горизонтали
 * \param vertCnt кол-во иконок в атласе по вертикали
 * \param seaPerk тип перка, true - морской, false - земной. Для фикса подмены перков между переходами локаций
 */
void addAnimationToPerk(string perkID, string perkIconPath, string perkAltIconPath, int perkIconCnt, int horzCnt, int vertCnt, bool seaPerk)
{
	int tmpCnt = animPerkCnt + 1;
	for (int i = 0; i < tmpCnt; i++)
	{
		if(!CheckAttribute(&objActivePerkShower, "Textures.t" + its(i)))
		{
			string tmpStr = "t" + its(i);
			if(InterfaceStates.AltIntIcons) objActivePerkShower.Textures.(tmpStr).file = perkAltIconPath;
			else objActivePerkShower.Textures.(tmpStr).file = perkIconPath;
			objActivePerkShower.Textures.(tmpStr).horz = horzCnt;
			objActivePerkShower.Textures.(tmpStr).vert = vertCnt;
			/* Флаг поддержки анимации использования и отката перка */
			ChrPerksList.list.(perkID).UseAnimation = true;
			/* Кол-во иконок перка в атласе */
			ChrPerksList.list.(perkID).UseAnimationIconCnt = perkIconCnt;
			/* Число секунд на один кадр анимации. Используется для отката, время которого больше чем кол-во иконок */
			ChrPerksList.list.(perkID).FPS = its(((sti(ChrPerksList.list.(perkID).TimeDelay) - sti(ChrPerksList.list.(perkID).TimeDuration)) / sti(ChrPerksList.list.(perkID).UseAnimationIconCnt)));
			/* Номер анимированного перка. Используется для поиска атласа перка */
			ChrPerksList.list.(perkID).AnimPerkCnt = i;
			ChrPerksList.list.(perkID).seaPerk = seaPerk;
			animPerkCnt = animPerkCnt + 1;
			break;
		}
		tmpCnt = tmpCnt + 1;
	}
}

void UnloadActivePerkShower()
{
	DeleteClass(&objActivePerkShower);
	DeleteAttribute(&objActivePerkShower,"PerkList");
}

bool IsPerkIntoList(string perkID)
{
	return CheckAttribute(&objActivePerkShower,"PerkList.list."+perkID);
}

int GetPerkPictureIndex(string perkName)
{
	switch(perkName)
	{
		case "TimeSpeed":
	        if(bSeaActive && !bAbordageStarted)
			{
				return 59;
			}
			else
			{
			    return 15;
			}
		break;
		case "Sink":			return 43; break;
		case "Repair":			return 55; break;
		// boal зачем же так игру кастрировать? грустно, однако :( -->
		case "LightRepair":		return 54; break;
		// boal <--
	}
	/* Первая текстура у анимированных перрков всегда полностью цветная (индекс 0) */
	if(CheckAttribute(&objActivePerkShower, "PerkList.list."+(perkName)) && CheckAttribute(&ChrPerksList, "list." + perkName + ".UseAnimation"))
	{
		return 0;
	}
	trace("WARNING!!! Perk name - "+perkName+" hav`t picture");
	return 0;
}

string GetPerkTextureName(string perkName)
{
	if(InterfaceStates.AltIntIcons)
	{
		switch(perkName)
		{
			case "TimeSpeed":
				if(bSeaActive && !bAbordageStarted)
				{
					return "battle_interface\list_icons_Konshud.dds";
				}
				else
				{
					return "battle_interface\LandCommands_Konshud.dds";
				}
			break;
			case "Sink":			return "battle_interface\list_icons_Konshud.dds"; break;
			case "Repair":			return "battle_interface\list_icons_Konshud.dds"; break;
			case "InstantBoarding":	return "battle_interface\list_icons_Konshud.dds"; break;
			case "LightRepair":		return "battle_interface\list_icons_Konshud.dds"; break;
		}
	}
	else
	{
		switch(perkName)
		{
			case "TimeSpeed":
				if(bSeaActive && !bAbordageStarted)
				{
					return "battle_interface\list_icons.dds";
				}
				else
				{
					return "battle_interface\LandCommands.dds";
				}
			break;
			case "Sink":			return "battle_interface\list_icons.dds"; break;
			case "Repair":			return "battle_interface\list_icons.dds"; break;
			case "InstantBoarding":	return "battle_interface\list_icons.dds"; break;
			case "LightRepair":		return "battle_interface\list_icons.dds"; break;
		}
	}
	/* У анимированных перков путь к атласу берем не прибитый гвоздями а тот, который задали выше */
	if(CheckAttribute(&objActivePerkShower, "PerkList.list."+(perkName)) && CheckAttribute(&ChrPerksList, "list." + perkName + ".UseAnimation") && CheckAttribute(&ChrPerksList, "list." + perkName + ".AnimPerkCnt"))
	{
		string tmpStr = "t" + its(ChrPerksList.list.(perkName).AnimPerkCnt);
		return objActivePerkShower.Textures.(tmpStr).file;
	}
	trace("WARNING!!! Perk name - "+perkName+" hav`t texture");
	return "";
}

int GetTextureIndex(string texName)
{
	aref arTexList,arCurTex;
	makearef(arTexList,objActivePerkShower.Textures);
	int i,q;

	q = GetAttributesNum(arTexList);
	for(i=0; i<q; i++)
	{
		arCurTex = GetAttributeN(arTexList,i);
		if(arCurTex.file == texName) return i;
	}
	trace("WARNING!!! Texture name - "+texName+" hav`t describe");
	return -1;
}

/*!
 * \brief Отображает иконку активного перка в правую часть экрана
 * \param perkID идентификатор перка
 */
void AddPerkToActiveList(string perkID)
{
	if( !IsEntity(&objActivePerkShower) ) return;
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);
	if( CheckAttribute(arRoot,perkID) ) return;

	makearef(arCur,arRoot.(perkID));
	arCur.texture = GetTextureIndex(GetPerkTextureName(perkID));
	arCur.pic_idx = GetPerkPictureIndex(perkID);
	/* Начальная инициализация маркера иконок для движка, если подразумевается их анимация */
	arCur.old_texture = arCur.texture;
	arCur.old_pic_idx = arCur.pic_idx;
	arCur.start_pic_idx = arCur.pic_idx;
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"add",arCur);
}

void DelPerkFromActiveList(string perkID)
{
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);
	if( !CheckAttribute(arRoot,perkID) ) return;

	makearef(arCur,arRoot.(perkID));
	/* Костыль для возвращения иконке родного айди для корректного удаления движком, иначе он не найдет её в своем списке */
	if(perkID != "TimeSpeed")
	{
		UpdatePerkIcon(perkID, arCur.start_pic_idx);
	}
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"del",arCur);
	DeleteAttribute(arRoot,perkID);
}

/*!
 * \brief Обновляет иконку перка. Используется для отрисовки анимации времени отката перка
 * \param perkID: string строка идентификатора перка, например "ImmediateReload"
 * \param iconID: идентификатор иконки в массиве текстур, следите что бы кол-во
 * иконок в файле соответствовало iconID
 */
void UpdatePerkIcon(string perkID, int iconID)
{
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);
	if( !CheckAttribute(arRoot,perkID) ) return;
	makearef(arCur,arRoot.(perkID));
	/* Путь (постоянный) и айди новой текстуры для анимации */
	arCur.new_texture = GetTextureIndex(GetPerkTextureName(perkID));
	arCur.new_pic_idx = iconID;
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"upd",arCur);
	/* Обновляем маркеры поиска активных перков для движка */
	arCur.old_texture = arCur.new_texture;
	arCur.old_pic_idx = arCur.new_pic_idx;
}

/*!
 * \brief Добавить перк в список с указанием иконки.
 * Используется для установки нужной иконки прогресса после перезагрузки,
 * т.к. теряется вызов "AddPerkToActiveList" и иконка пропадает с экрана
 * \param perkID идентификатор перка
 * \param iconID номер иконки в атласе перка
 */
void AddAndUpdatePerkIcon(string perkID, int iconID)
{
	if( !IsEntity(&objActivePerkShower) ) return;
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);
	if( CheckAttribute(arRoot,perkID) ) return;

	makearef(arCur,arRoot.(perkID));
	arCur.texture = GetTextureIndex(GetPerkTextureName(perkID));
	arCur.pic_idx = iconID;
	/* Начальная инициализация маркера иконок для движка, если подразумевается их анимация */
	arCur.old_texture = arCur.texture;
	arCur.old_pic_idx = arCur.pic_idx;
	arCur.start_pic_idx = arCur.pic_idx;
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"add",arCur);
}

/*!
 * \brief Возвращает текущий кадр иконки перка. Используется для анимированных перков
 * \param perkID: string строка идентификатора перка, например "ImmediateReload"
 * \return int номер кадра из .dds для анимированных перков
 */
int getPerkCurrentIconID(string perkID)
{
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);
	if( !CheckAttribute(arRoot,perkID) ) return 0;
	makearef(arCur,arRoot.(perkID));
	return sti(arCur.old_pic_idx);
}

/*!
 * \brief Возвращает наличие иконки перка на экране.
 * Используется для установки нужной иконки прогресса после перезагрузки
 * \param perkID идентификатор перка
 * \return true перк есть на экране (перезагрузки не было)
 * \return false перка на экране нет (была перезагрузка)
 */
bool isPerkInActiveList(string perkID)
{
	return CheckAttribute(&objActivePerkShower, "PerkList.list."+(perkID));
}

/*!
 * \brief Возвращает отношение кадров к времени действия перка,
 * т.е. сколько секунд приходится на один кадр (процесс обработки
 * перков запускается раз в секунду)
 * \param perkID идентификатор перка
 * \return int число секунд на один кадр
 */
int getAnimFpsCnt(string perkID)
{
	return sti(ChrPerksList.list.(perkID).FPS);
}
