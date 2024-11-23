/*

	Возможные типы атаки attackType:
	"fast" быстрая атака
	"force" обычная
	"round" круговая
	"break" пробивающая блок
	"feint" атака после финта

*/
#define BLADE_DMG_RAND 0.1 // уровень рандома урона ножа
#define BLADE_EXP_MULT 0.12
#define BLOODING_MIN_TIME 10
#define SWIFT_TIME_RAND 2
#define STUN_TIME_RAND 2
#define TRAUMA_TIME_RAND 40
#define POISON_TIME_RAND 30
//--------------------------------------------------------------------------------
//Blade parameters
//--------------------------------------------------------------------------------

//Расчитать повреждение для персонажа
//#20200522-01
//iFencingType 0 = fencinglight, 1 = fencing, 2 = fencingheavy
//iAttackType 0 = fast, 1 = force, 2 = round, 3 = break, 4 = feint
float LAi_CalcDamageForBlade(aref attack, float aSkill, int iAttackType, string sFencingType, bool isBlocked, bool blockSave, bool bIsRandomOn)
{
	//Расчитываем повреждение от сабли
	float min = 10.0;
	float max = 10.0;
	if(CheckAttribute(attack, "chr_ai.dmgbldmin")) {
		min = stf(attack.chr_ai.dmgbldmin);
	}
	if(CheckAttribute(attack, "chr_ai.dmgbldmax")) {
		max = stf(attack.chr_ai.dmgbldmax);
	}
	//float bladeDmg = min + frand((max - min));//*(rand(10)*0.1);
	if (findsubstr(attack.model.animation, "mushketer" , 0) != -1) {
		min = stf(Items[GetItemIndex(attack.equip.gun)].melee_dmg_min);
		max = stf(Items[GetItemIndex(attack.equip.gun)].melee_dmg_max);
	}

	//Коэфициент в зависимости от скилов
	float bladeDmg = 0;
	float atSkill = aSkill + BLADE_DMG_RAND * bIsRandomOn * (Random() - 0.5);
	if (atSkill < 0.0) { atSkill *= -1; }// чуть больше чем мин урон

	bladeDmg = (min + atSkill * (max - min))
	//Коэфициент в зависимости от удара
	float kAttackDmg = 1.0;

	// TO_DO оптимизация на ветку параметров
	//if (sti(attack.index) == GetMainCharacterIndex()) Log_Info(attackType);

	bool isAttTypeBreak = false;
	if (iAttacktype == 3) { isAttTypeBreak = true;}
	// множ урона в блок
	kAttackDmg *= (1 - 0.33 * isBlocked);
	bool bABProfHitPenalty = false;
	switch(iAttacktype) {
		case 0: // быстрая атака
			/*
			//пример коррекции
			if(isBlocked) {
				kAttackDmg *= 1.1;
			}
			*/
			kAttackDmg *= 0.7;

			if (sFencingType != "Fencing") { bABProfHitPenalty = true; }
		break;

		case 1: // обычная атака
			//kAttackDmg *= 1.0;

			if (sFencingType != "FencingLight") { bABProfHitPenalty = true; }
		break;

		case 2: // круговая атака
			kAttackDmg *= 0.6;

			kAttackDmg *= (1.0 + 0.3 * CheckCharacterPerk(attack, "BladeDancer"));
			if (sFencingType != "Fencing") { bABProfHitPenalty = true; }
			else { kAttackDmg *= 1.2; }// +20% конкретно для СО без учета профильных ударов
		break;

		case 3: // пробивающая блок
			if ( MOD_SKILL_ENEMY_RATE == 3)	{ kAttackDmg *= 1.6; }
			else { kAttackDmg *= 2.0; }

			kAttackDmg *= (1 + IsEquipCharacterByArtefact(attack, "talisman19"));
			if (sFencingType != "FencingHeavy") { bABProfHitPenalty = true; }
			//if (!CheckCharacterPerk(attack, "HardHitter")) kAttackDmg /= 2.0;
		break;

		case 4:  // фикс после изучения ядра //Атакующие продолжение финта
			if(isBlocked && blockSave) {
				kAttackDmg = 0.0;
			}
			else {
				kAttackDmg = 0.8;
			}

			kAttackDmg *= (1 + CheckCharacterPerk(attack, "Agent"));
			if (sFencingType != "FencingLight") { bABProfHitPenalty = true; }
		break;
	}
	// только пробивающий бьет в идеальный блок
	if (blockSave) { kAttackDmg = 0.8 * isAttTypeBreak;}

	kAttackDmg *= (1 - 0.3 * bAltBalanceProHits * bABProfHitPenalty);// профильные удары
	//float kSkillDmg = 1.0;
	//kSkillDmg = 1.0 * (1.0 + (0.3 * aSkill));

	if (kAttackDmg <= 0) {// оптимизация boal
		return 0.0;
	}

	if (findsubstr(attack.model.animation, "mushketer" , 0) != -1) {
		if (IsEquipCharacterByItem(attack, "mushket_SeaCarbine") && iAttacktype == 1) {
			kAttackDmg += 1.0;
		}
		if (iAttacktype == 0) { kAttackDmg += 0.5; }
		if (iAttacktype == 3) { kAttackDmg += 1.5; }
	}

	//Результирующий демедж
	float dmg = bladeDmg * kAttackDmg; // *kArcadeDmg * kSkillDmg
	dmg *= (1.0 + CheckAttribute(attack, "perks.list.Rush.active")); // берсерк атака //IsCharacterPerkOn(attack, "Rush")
	dmg *= (1.0 + 0.1 * IsEquipCharacterByArtefact(attack, "talisman1")); // Пернатый Змей
	dmg *= (1.0 + 0.15 * IsCharacterPerkOn(attack, "Grunt")); // Рубака
	dmg *= (1.0 + 0.1 * CheckAttribute(attack, "StrangeElixir")); // Убойная смесь
	
	return dmg;
}

string RecalculateMushketHitsType(aref attack)
{
	if (IsEquipCharacterByItem(attack, "mushket_SeaCarbine"))
	{
		return "force";
	}
	return "";
}

//Расчитать полученный опыт при ударе саблей
//#20200522-01
float LAi_CalcExperienceForBlade(aref attack, aref enemy, int iAttackType, bool isBlocked, float dmg, bool blockSave)
{
	float fEnemyHP = stf(enemy.chr_ai.hp);
	if (fEnemyHP < dmg) {
       dmg = fEnemyHP;
	}
	/*//Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	if (CheckAttribute(attack, "rank"))
		ra = 1.0 + 0.5*stf(attack.rank);
	if (CheckAttribute(enemy, "rank"))
		re = 1.0 + 0.5*stf(enemy.rank);
	ra = re/ra;
	if (ra > 3.0)
		ra = 3.0;//обрезание слишком большого множителя. кривые множители тоже решает*/
	float exp = dmg * (0.8 + Random() * 0.2);

	if(iAttackType == 4) {//feintc
		exp *= 1.5;
	}
	if (CheckCharacterPerk(attack,"SwordplayProfessional")) {
		exp *= (1.5 + 0.03 * sti(attack.rank));
	}
	return exp;
}

//Энергия, необходимая для запуска действия
float LAi_CalcUseEnergyForBlade(aref character, string actionType, float fSkill)
{
	float energytype = LAi_GetBladeEnergyType(character);// = weight / 9 + 0.4
	float energy = 0.0;
	switch(actionType)
	{
		case "fast":
			energy = 8.0;
		break;
		case "force":
			energy = 7.0;
		break;
		case "round":
			energy = 16.0;
			if (energytype > 1.17) {//~7.0
				energy *= 1.5;
			}
		break;
		case "break":
			energy = 22.0;
		break;
		// case "feint":
			// energy = 7.0;
		// break;
		// case "parry":
			// energy = 20.0;
		// break;
		case "hit_parry":  // boal fix эту энергию тратит не атакующий, а атакуемый в анимации fgt_hit_parry
			energy = 16.0;
		break;
		case "feintc":
			energy = 7.0; // расход при успехе финта
		break;
	}
	/*if(CheckCharacterPerk(character, "BladeDancer"))  // to_do
	{
		energy = energy * 0.9;
	}*/
	 // честно все всем
	/*if(character.id == pchar.id || character.chr_ai.group == LAI_GROUP_PLAYER)
	{
		energy = energy * (1.05 - (0.025 * MOD_SKILL_ENEMY_RATE*3));
	} */
	//чек на энергию ломает ИИ
	fSkill = 1.0 - 0.3 * fSkill;

	if (CheckAttribute(character, "model.animation") && findsubstr(character.model.animation, "mushketer", 0) != -1) {
		energy = energy * fSkill * GetMushketEnergyDrain(character);
	}
	else {
		energy = energy * fSkill * (2.0 * energytype + 1.0) / 3.0;  // энергоемкость от веса
	}
	return energy;
}

float GetMushketEnergyDrain(ref character)
{
	if (!CheckAttribute(character,"equip")) return 0.0;
	return stf(Items[GetItemIndex(character.equip.gun)].weight)/10.0 + 0.2;
}

float Lai_UpdateEnergyPerDltTime(aref chr, float curEnergy, float dltTime, attack)
{
	float fMultiplier = 1.35+(GetCharacterSPECIALSimple(chr,SPECIAL_S)/20.0);// 1.5 ... 1.85 - влияние силы на скорость восстановления энергии

	if((MOD_SKILL_ENEMY_RATE == 3) || (CheckCharacterPerk(chr, "Energaiser"))) // скрытый перк боссов и ГГ
	{
		fMultiplier = fMultiplier * 1.5;
	}
	if(CheckCharacterPerk(chr, "Tireless"))
	{
		fMultiplier = fMultiplier * 1.15;
	}
	if(CheckAttribute(chr, "bonusEnergy"))
	{
		fMultiplier = fMultiplier * 2;
	}
    // честно все всем
	/*
	if(chr.id == pchar.id || chr.chr_ai.group == LAI_GROUP_PLAYER)
	{
		fMultiplier = fMultiplier * (1.0 + (0.025 * MOD_SKILL_ENEMY_RATE*3));
	}
	*/
	float fEnergy;
	fEnergy = curEnergy + dltTime * fMultiplier;

	return fEnergy;
}


//--------------------------------------------------------------------------------
//Gun parameters
//--------------------------------------------------------------------------------

//Расчитаем вероятность попадания
float LAi_GunCalcProbability(aref attack, aref enemy, float kDist)
{
	//Если близко, то попадём точно
	if(kDist >= 0.9) return 1.0;
	//Расчитаем вероятность на конце отрезка
	float pmin = 0.3;
 	if(CheckAttribute(attack, "chr_ai.accuracy")) // boal это меткость самого пистолета, а не скил!
	{
		pmin = stf(attack.chr_ai.accuracy);
	}
 	//Применим разброс от скила
	// boal -->
	float aSkill = LAi_GetCharacterGunLevel(attack);
	// boal <--

	pmin = pmin + 0.3*aSkill;

	//Вероятность попадания в текущей позиции
	//float p = pmin + (1.0 - pmin)*(kDist/0.9)+(GetCharacterSPECIALSimple(attack, SPECIAL_P)*0.01);
	float p = pmin + (1.0 - pmin)*(kDist/0.9)+(GetCharacterSPECIALSimple(attack, SPECIAL_P)*0.01)-0.25; //добавил базовый штраф в 25%, убирается перками
 	//Учесть абилити
	if(IsCharacterPerkOn(attack, "GunProfessional"))
	{
		p = p + 0.25;
	}else{
		if(IsCharacterPerkOn(attack, "Gunman"))
		{
			p = p + 0.1;
		}
	}
	if(!IsDay() && IsEquipCharacterByArtefact(attack, "talisman15")) p = p * 2;
	if(IsEquipCharacterByArtefact(enemy,  "talisman18")) p = p * 0.75;
	return p;
}

//Получить повреждение от пистолета
float LAi_GunCalcDamage(aref attack, aref enemy)
{
	//Расчитываем повреждение
	float min = 10.0;
	float max = 10.0;
	if(CheckAttribute(attack, "chr_ai.dmggunmin"))
	{
		min = stf(attack.chr_ai.dmggunmin);
	}
	if(CheckAttribute(attack, "chr_ai.dmggunmax"))
	{
		max = stf(attack.chr_ai.dmggunmax);
	}
	string sBullet = LAi_GetCharacterBulletType(attack);
	if(sBullet == "powder_pellet") LaunchBlastPellet(enemy);
	if(sBullet == "grenade") LaunchBlastGrenade(enemy);
	if(CheckAttribute(enemy, "cirassId"))
	{
		min = stf(attack.chr_ai.DmgMin_C);
		max = stf(attack.chr_ai.DmgMax_C);

		if(stf(attack.chr_ai.EnergyP_C) > 0.0 )
		{
			if(sBullet == "powder_pellet")
			{
				if(enemy.chr_ai.group != LAI_GROUP_PLAYER) Lai_CharacterChangeEnergy(enemy, -stf(attack.chr_ai.EnergyP_C));
			}
		}
	}
	else
	{
		min = stf(attack.chr_ai.DmgMin_NC);
		max = stf(attack.chr_ai.DmgMax_NC);

		if(stf(attack.chr_ai.EnergyP_NC) > 0.0)
		{
			if(sBullet == "powder_pellet")
			{
				if(enemy.chr_ai.group != LAI_GROUP_PLAYER) Lai_CharacterChangeEnergy(enemy, -stf(attack.chr_ai.EnergyP_C));
			}
		}
	}
	//Учитываем скилы
	float aSkill = LAi_GetCharacterGunLevel(attack);
	float eSkill = LAi_GetCharacterLuckLevel(enemy); // good luck

	float dmg = min + (max - min)*frandSmall(aSkill);
	//Модифицировать повреждение от pistol с учетом скилов
    if(aSkill < eSkill)
	{
		dmg = dmg * (1.0 + 0.7 * (aSkill - eSkill));
	}
	// упрощение игры новичкам
	/*if (MOD_SKILL_ENEMY_RATE == 1 && CheckAttribute(enemy, "chr_ai.group"))
	{
		if (enemy.chr_ai.group == LAI_GROUP_PLAYER)
		{
			dmg = dmg / MOD_Complexity_1_DMG;
		}
	}*/
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	//if (MOD_SKILL_ENEMY_RATE < 2 && sti(enemy.index) == GetMainCharacterIndex())
	if (sti(enemy.index) == GetMainCharacterIndex())
	{
		dmg = (dmg * (4.0 + MOD_SKILL_ENEMY_RATE*3) / 10.0) * bModDamage;
	}

	if(IsEquipCharacterByArtefact(attack, "talisman18")) dmg *= 1.25;

	if(CheckCharacterPerk(attack, "Buccaneer"))
	{
		if(CheckAttribute(enemy, "chr_ai.energy"))
		{
			enemy.chr_ai.energy = (stf(enemy.chr_ai.energy) * 0.65); //fix
		}
	}
	return dmg;
}

//Расчитать полученный опыт при попадании из пистолета
float LAi_GunCalcExperience(aref attack, aref enemy, float dmg)
{
	if (stf(enemy.chr_ai.hp) < dmg)
       dmg = stf(enemy.chr_ai.hp);
	//Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	if (CheckAttribute(attack, "rank"))
		ra = 1.0 + 0.5*stf(attack.rank);
	if (CheckAttribute(enemy, "rank"))
		re = 1.0 + 0.5*stf(enemy.rank);
	ra = re/ra;
	if (ra > 3.0)
		ra = 3.0;//обрезание слишком большого множителя. кривые множители тоже решает
	dmg = dmg * (0.8 + Random() * 0.2);
	if (findsubstr(attack.model.animation, "mushketer" , 0) != -1) dmg *= 0.8;
	if (!bRechargePistolOnLine) dmg *= 2;
	return dmg;
}

//Расчитаем текущую скорость перезарядки пистолета
float LAi_GunReloadSpeed(aref chr)
{
	//Получим текущее состояние скорости зарядки
	float charge_dlt = LAI_DEFAULT_DLTCHRG;
	if(CheckAttribute(chr, "chr_ai.charge_dlt"))
	{
		charge_dlt = stf(chr.chr_ai.charge_dlt);
	}
	//Модифицируем скилом
	// boal -->
	//float skill = LAi_GetCharacterFightLevel(chr);
	float skill = LAi_GetCharacterGunLevel(chr);
	// boal <--

	charge_dlt = charge_dlt*(1.0 + 0.3*skill);//boal
	//УчтЈм абилити
	if(IsCharacterPerkOn(chr, "GunProfessional"))
	{
		if(IsCharacterPerkOn(chr, "Buccaneer")) charge_dlt = charge_dlt*1.5;
		else charge_dlt = charge_dlt*1.25;
	}
	else
	{
		if(IsCharacterPerkOn(chr, "Gunman"))
		{
			if(IsCharacterPerkOn(chr, "Buccaneer")) charge_dlt = charge_dlt*1.35;
			else charge_dlt = charge_dlt*1.1;
		}
		else
		{
			if(IsCharacterPerkOn(chr, "Buccaneer")) charge_dlt = charge_dlt*1.25;
		}
	}
	return charge_dlt;
}

//--------------------------------------------------------------------------------
//All
//--------------------------------------------------------------------------------

/*float LAi_CalcDeadExp(aref attack, aref enemy)
{
	//Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	if(CheckAttribute(attack, "rank"))
	{
		ra = stf(attack.rank);
	}
	if(CheckAttribute(enemy, "rank"))
	{
		re = stf(enemy.rank);
	}
	if(ra < 1.0) ra = 1.0;
	if(re < 1.0) re = 1.0;
	float dmg = (0.5 + 4.0*LAi_GetCharacterFightLevel(enemy))*LAi_GetCharacterMaxHP(enemy);
	dmg = dmg*((1.0 + re*0.5)/(1.0 + ra*0.5));
	return dmg*0.5;
} */

//Поломка катаром оружия - Gregg
void CheckForWeaponBreak(ref attack, ref enemy) 
{
	if(!HasSubStr(attack.equip.blade, "katar")) {
		return;
	}
	if (rand(19) != 0) {
		return;
	}

	string weaponID = GetCharacterEquipByGroup(enemy, BLADE_ITEM_TYPE);
	aref weapon;
	Items_FindItem(weaponID, &weapon);
	if(weapon.model == "unarmed" || weapon.quality == "excellent") {//Не отличное и не безоружный
		return;
	}

	if(GetCharacterItem(enemy, weaponID) <= 1) { RemoveCharacterEquip(enemy, weapon.groupID); }
	TakeItemFromCharacter(enemy, weaponID);

	string sEquipItem = GetGeneratedItem("unarmed");
	AddItems(enemy, sEquipItem, 1);
	EquipCharacterbyItem(enemy, sEquipItem);

	if(sti(attack.index) == GetMainCharacterIndex()) {
		Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_2", "Logs.txt", "#space#", " "));	
	}
	else {
		Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_3", "Logs.txt", "#space#", " "));
	}
	PlaySound("interface\Crash_"+rand(2)+".wav");
	return;
}

int LAi_CalcCritChance(ref attack, int iAttackType, string fencing_type, int valueCrB)
{
	int critchance = 0;
	critchance += 10 * IsCharacterPerkOn(attack, "SwordplayProfessional");
	critchance += 5 * IsCharacterPerkOn(attack, "CriticalHit");
	critchance += 5 * IsCharacterPerkOn(attack, "Fencer");
	if (iAttackType == 4) {//финт
		critchance += 33 * IsCharacterPerkOn(attack, "Agent"); 
	}
	if(critchance > 0)	{
		critchance += GetCharacterSPECIALSimple(attack, SPECIAL_L);
		critchance += valueCrB;//доп крит
		if (iAttackType == 2 && fencing_type == "FencingLight") {//круговой ЛО
			critchance += 15; 
		}
	}
	return critchance;
}

//бонусный урон крита от удачи
float LAi_CalcCritDamageMult(ref attack) {
	return (2 + 0.05 * GetCharacterSPECIALSimple(attack, SPECIAL_L));
} 

//чекает на смерть. если убило, то возвращает экспу и начисляет опыт в везение, авторитет и защиту
float LAi_CalcExpForBladeKill(ref attack, ref enemy, bool isSetBlade)
{
	if (!LAi_IsDead(enemy)) {
		return 0.0;
	}
	float experience = 0;
	//Начислим за убийство
	//exp = exp + LAi_CalcDeadExp(attack, enemy);
	//exp = LAi_GetCharacterMaxHP(enemy) * 10;
	//DoCharacterKilledStatistics(sti(attack.index), sti(enemy.index));
	/*if(!isSetBlade)
	{
		//ChangeCharacterReputation(attack, -3);
	}*/
	// boal  check skill -->
	float ra = 1.0;
	float re = 1.0;
	if(CheckAttribute(attack, "rank")) {
		ra = stf(attack.rank);
	}
	if(CheckAttribute(enemy, "rank")) {
		re = stf(enemy.rank);
	}
	if (re < 4.0) {
		experience = GetCharacterSPECIALSimple(attack, SPECIAL_I) + rand(GetCharacterSPECIALSimple(attack, SPECIAL_A)); 
	}
	else {
		experience = Lai_GetCharacterMaxHP(enemy)/re + GetCharacterSPECIALSimple(attack, SPECIAL_I) * re / ra;;//Lipsar передeлка опыта
	}
	AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
	AddCharacterExpToSkill(attack, SKILL_FORTUNE, 1);
	AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
	// boal <--
	// boal statistic info 17.12.2003 -->
	Statistic_KillChar(attack, enemy, "_s");
	// boal statistic info 17.12.2003 <--
	LAi_SetResultOfDeath(attack, enemy, isSetBlade);
	return experience;
}

//--------------------------------------------------------------------------------
//Calculate total
//--------------------------------------------------------------------------------

//Начисление повреждений при атаке мечём
//#20200522-01
void LAi_ApplyCharacterAttackDamage(aref attack, aref enemy, string fencing_type, string attackType, bool isBlocked, bool blockSave, float aSkill)
{
	//Если неубиваемый, то нетрогаем его
	if(CheckAttribute(enemy, "chr_ai.immortal"))	{
		if(sti(enemy.chr_ai.immortal) != 0)	{
			return;
		}
	}
	if(CheckAttribute(attack, "chr_ai.group") && CheckAttribute(enemy, "chr_ai.group"))	{
		if(attack.chr_ai.group == enemy.chr_ai.group)	{
			return;
		}
	}
	if(IsCharacterPerkOn(enemy, "Fencer") && rand(9)==1)  {
		Log_Info(GetFullName(enemy) + GetConvertStrWithReplace("Variable_LAi_fightparams_1", "Logs.txt", "#space#", " ")); 
		return;
	}

	int iFencingType = 0;
	switch (fencing_type) {
		case "FencingLight": iFencingType = 0; break;//условный дефолт
		case "Fencing": iFencingType = 1; break;
		case "FencingHeavy": iFencingType = 2; break;
	}
	int iAttackType = 0;
	switch (attackType) {
		case "fast": iAttackType = 0; break;//условный дефолт
		case "force": iAttackType = 1; break;
		case "round": iAttackType = 2; break;
		case "break": iAttackType = 3; break;
		case "feint": iAttackType = 4; break;
	}
	float coeff = 0.0;

	int nAttackIdx = sti(attack.index);
	int nEnemyIdx = sti(enemy.index);
	float eSkill = LAi_GetCharacterFightLevel(enemy);
	int valueCrB = sti(attack.chr_ai.special.valueCrB);
	bool bEnemyRush = CheckAttribute(enemy, "perks.list.Rush.active");
	bool bAttackHardHitter = CheckCharacterPerk(attack, "HardHitter");
	/*switch (fencing_type) старый расчёт чистого стата без учёта бонусов. Ниже с учётом - Gregg
	{
		case "FencingLight": coeff = makefloat(attack.Skill.FencingLight)/20; break;
		case "Fencing": coeff = makefloat(attack.Skill.Fencing)/20; break;
		case "FencingHeavy": coeff = makefloat(attack.Skill.FencingHeavy)/20; break;
	}*/
	//--->Пробитие блоков - Gregg
	/*if (isBlocked && blockSave)//перенёс в ивенты - Gregg
	{
		if (fencing_type == "FencingHeavy") blockSave = CheckForBlockBreak(attack,enemy,true);
		else blockSave = CheckForBlockBreak(attack,enemy,false);
	}*/
	//<---Пробитие блоков тяжёлым оружием

	bool cirign = false;
	string sEnemyCuirassID;
	int iEnemyCuirassID = 0;
	if (CheckAttribute(enemy, "cirassId")) {
		sEnemyCuirassID = enemy.cirassId;
		iEnemyCuirassID = sti(sEnemyCuirassID);
	}
	int iDmgAdd = 0;
	if (!blockSave && !isBlocked) {
		iDmgAdd += CheckForBlooding(attack, nAttackIdx, enemy, nEnemyIdx, iFencingType, aSkill, iAttackType);
		if (!bEnemyRush) {
			iDmgAdd += CheckForSwift(attack, nAttackIdx, enemy, nEnemyIdx, iFencingType, aSkill);
			CheckForStun(attack, nAttackIdx, enemy, nEnemyIdx);
		}
		if (iFencingType == 2) {//только ТО
			CheckForTrauma(attack, nAttackIdx, enemy, nEnemyIdx, iEnemyCuirassID)
		}
		cirign = CheckForCirassBreak(attack, nAttackIdx, enemy, nEnemyIdx, iFencingType, bAttackHardHitter, iEnemyCuirassID, aSkill);
	}
	else {// if (isBlocked)
		CheckForWeaponBreak(attack, enemy);// Поломка катаром оружия - Gregg 
    }

	// дамаг начало
	float dmg = LAi_CalcDamageForBlade(attack, aSkill, iAttackType, fencing_type, isBlocked, blockSave, true);

	if(CheckAttribute(enemy, "sex") && enemy.sex == "skeleton") {
		dmg *= (1 + 0.33 * IsEquipCharacterByArtefact(attack, "talisman9"));
	}
	// модификатор от сложности
	if (nEnemyIdx == GetMainCharacterIndex()) {
		dmg = (dmg * (4.0 + MOD_SKILL_ENEMY_RATE*3) / 10.0) * bModDamage;

		// Warship 27.08.09 Для сильных противников
		// Если долбить совсем сильных (хардкорные абордажи), то шансов взять шип будет меньше
		if (CheckAttribute(loadedLocation, "CabinType")) {
			dmg *= (1.0 + stf(attack.rank)/100);
		}
	}

	// дамаг защита
	dmg *= (1.0 - 0.5 * IsCharacterPerkOn(enemy, "Rush"));

	float kDmg = 1.0;// сборный множитель
	kDmg -= 0.1 * IsCharacterPerkOn(enemy, "SwordplayProfessional");
	kDmg -= 0.1 * IsCharacterPerkOn(enemy, "AdvancedDefense");
	kDmg -= 0.1 * IsCharacterPerkOn(enemy, "BasicDefense");
	if (CheckAttribute(attack, "sex") && attack.sex == "skeleton") {	
		kDmg -= (0.33 * IsEquipCharacterByArtefact(enemy, "talisman9"));
	}
	
	// Warship 27.08.09 Для сильных противников
	// Если долбить совсем сильных (хардкорные абордажи), то шансов взять шип будет меньше
	if (sti(enemy.Rank) > 50) {
		dmg *= (45.0 / stf(enemy.Rank));
	}
	if (aSkill < eSkill) {
		dmg *= (1.0 + 0.7 * (aSkill - eSkill));
	}

	if(!cirign && iEnemyCuirassID) {//сопротивления уронам у кирас
		switch (iAttackType) {
			case 0: dmg *= (1.0 - stf(Items[iEnemyCuirassID].CirassLevel.fast)); break;
			case 1: dmg *= (1.0 - stf(Items[iEnemyCuirassID].CirassLevel.force)); break;
			case 2: dmg *= (1.0 - stf(Items[iEnemyCuirassID].CirassLevel.round)); break;
			case 3: dmg *= (1.0 - stf(Items[iEnemyCuirassID].CirassLevel.break)); break;
			case 4: dmg *= (1.0 - stf(Items[iEnemyCuirassID].CirassLevel.feint)); break;
		}
	}

	// ГПК 1.2.3
	dmg = kDmg * dmg + iDmgAdd;
	// дамаг конец

	if (dmg < 1.0) {// крит от <1 урона - рофл
		return;
	}

	// крит начало
	float critical = 0.0;
	int critchance = LAi_CalcCritChance(attack, iAttackType, fencing_type, valueCrB);

	// блочим криты обычным блоком?
	if (!isBlocked && (rand(99) < critchance))	{//"<=" не нужно 
		critical = 1.0;
	}

	// крит защита
	if (critical > 0.0) {
		int iCritDefPrc = 0;
		if(!cirign && iEnemyCuirassID) {// защиты от критов у кирас
			switch (Items[iEnemyCuirassID].id) {// внутреннее имя предмета
				case "cirass1": iCritDefPrc += 40; break;
				case "cirass2": iCritDefPrc += 60; break;
				case "cirass3": iCritDefPrc += 50; break;
				case "cirass4": iCritDefPrc += 80; break;
				case "cirass5": iCritDefPrc += 100; break;
			}
		}
		if (iCritDefPrc > rand(99)) {
			critical = 0.0;
			if(nEnemyIdx == GetMainCharacterIndex()) {
				Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_4", "Logs.txt", "#space#", " "));
			}
			else {
				Log_TestInfo("" + enemy.Name + GetConvertStrWithReplace("Variable_LAi_fightparams_5", "Logs.txt", "#space#", " "));
			}
		}
	}
	// крит опыт и множитель
	if (critical > 0.0) {
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 5);
		critical = LAi_CalcCritDamageMult(attack);
		
		if(nAttackIdx == GetMainCharacterIndex()) {
			Log_SetStringToLog(XI_ConvertString("Critical Hit"));
			Log_TestInfo(" " + critical + GetConvertStrWithReplace("Variable_LAi_fightparams_6", "Logs.txt", "#space#", " "));

			int iCriticalCount = sti(pchar.questTemp.criticalcount) + 1;
			pchar.questTemp.criticalcount = iCriticalCount;
			
			// Открываем достижения
			if(iCriticalCount >= 100) UnlockAchievement("criticals", 1);
			if(iCriticalCount >= 250) UnlockAchievement("criticals", 2);
			if(iCriticalCount >= 500) UnlockAchievement("criticals", 3);
		}
	}
	else {
		critical = 1.0;//оверрайдим
	}

	dmg = dmg * critical;
	// крит конец

	//Начисляем опыт - ДО нанесения урона
	float exp = LAi_CalcExperienceForBlade(attack, enemy, iAttackType, isBlocked, dmg, blockSave);
	
	LAi_ApplyCharacterDamage(enemy, MakeInt(dmg + 0.5));

	//Проверим на смерть
	enemy.chr_ai.KilledByIDx = nAttackIdx; 
	LAi_CheckKillCharacter(enemy);
	//проверим на отравление
	MakePoisonAttackCheckSex(attack, enemy);
	//Есть ли оружие у цели
	bool isSetBlade = (CheckAttribute(enemy, "equip.blade"));//(SendMessage(enemy, "ls", MSG_CHARACTER_EX_MSG, "isSetBlade") != 0);
	if (CheckAttribute(attack,"vampire") || sti(attack.chr_ai.special.valueV) > 0) {
		float hp = attack.chr_ai.hp;
		float maxhp = attack.chr_ai.hp_max;
		float hpup = dmg / 2.0;
		log_Testinfo(FloatToString(hpup, 2));
		if ((hp + hpup) >= maxhp) { attack.chr_ai.hp = maxhp; }
		else { attack.chr_ai.hp = hp + hpup; }

		SendMessage(attack, "lfff", MSG_CHARACTER_VIEWDAMAGE, hpup, MakeFloat(attack.chr_ai.hp), MakeFloat(attack.chr_ai.hp_max));
	}

	if(CheckAttribute(enemy, "chr_ai.energy")) {
		float fEnergy = stf(enemy.chr_ai.energy);
		fEnergy *= (1.0 - 0.1 * bAttackHardHitter); //fix
		enemy.chr_ai.energy = fEnergy * isEquippedArtefactUse(attack, "talisman10", 1.0, 0.9); // отнимаем энергию
	}
	/*if(LAi_grp_alarmactive == false)
	{
		if(CheckAttribute(pchar, "sneak.success"))
		{
			if(sti(pchar.sneak.success) == 1)
			{
				pchar.sneak.success = 0;
			}
		}
	} */
	if(!isSetBlade) {
		return;//не начисляем опыт
	}

	//уже чекается в checkkillcharacter
	//LAi_CalcExpForBladeKill(attack, enemy, isSetBlade);

    AddCharacterExpToSkill(attack, fencing_type, Makefloat(BLADE_EXP_MULT * exp));
}

int LAi_CalcBloodingChance(ref attack, int iFencingType, float aSkill, int iAttackType)
{
	if (iAttackType == 2) {//не круговой
		return 0;
	}
	float coeff = 0.0;
	if (iFencingType == 0) {
		coeff = 2.5 + 5.0 * aSkill;
	}
	return (sti(attack.chr_ai.special.valueB) + MakeInt(coeff));
}

float LAi_CalcBloodingDuration(ref attack, int iFencingType, float aSkill, bool bIsRandomOn) 
{
	float coeff = 0.0;
	if (iFencingType == 0) {
		coeff = 5.0 * aSkill;
	}
	else {
		coeff = 3.0; //для урона СО/ТО
	}
	return (BLOODING_MIN_TIME + 5 * coeff * (1 - bIsRandomOn * Random()));// отнимаем рандом
}

//возвращает доп урон если не нанесло кровоток. доп урон при iFencingType = 0 (Легкое оружие)
int CheckForBlooding(ref attack, int nAttackIdx, ref enemy, int nEnemyIdx, int iFencingType, float aSkill, int iAttackType)
{
	int valueB = LAi_CalcBloodingChance(attack, iFencingType, aSkill, iAttackType);
	if (valueB <= 0) { 
		return 0;
	}
	float coeff = LAi_CalcBloodingDuration(attack, iFencingType, aSkill, 1);
	
	//if (100.0 * Random() < valueB) {
	if (!pnrand(attack,  valueB, "bleed")) {//основной чек 
		return 0;
	}
	if(nAttackIdx == GetMainCharacterIndex()) {
		PlaySound("Fx_Krovotok");
		pchar.questTemp.bloodingcount = sti(pchar.questTemp.bloodingcount) + 1;
	}
	if(nEnemyIdx == GetMainCharacterIndex()) {
		if(IsEquipCharacterByArtefact(enemy, "talisman9") && rand(9)>0) {//чек на сввятую чашу
			Log_info(GetConvertStrWithReplace("Variable_LAi_fightparams_10", "Logs.txt", "#space#", " "));
			return 0;
		}
		PlaySound("Fx_Krovotok");
	}
	if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator" && enemy.sex != "skeleton") {
		if(nAttackIdx == GetMainCharacterIndex()) {
			Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_9", "Logs.txt", "#space#", " "));
		}
		if(nEnemyIdx == GetMainCharacterIndex()) {
			Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_11", "Logs.txt", "#space#", " "));
		}
		MakeBloodingAttack(enemy, attack, coeff);
	}
	else {
		if(nAttackIdx == GetMainCharacterIndex()) { 
			Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_12", "Logs.txt", "#space#", " "));
		}
		if(nEnemyIdx == GetMainCharacterIndex()) { 
			Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_13", "Logs.txt", "#space#", " "));
		}
		return MakeInt(5.0 + 4.0 * coeff);
	}
	return 0;
}

int LAi_CalcSwiftChance(ref attack, int iFencingType, float aSkill)
{
	float coeff = 0.0;
	if (iFencingType == 1) {
		coeff = 2.5 + 5.0 * aSkill;
	}
	return (sti(attack.chr_ai.special.valueSS) + MakeInt(coeff));
}

float LAi_CalcSwiftDuration(ref attack, int iFencingType, float aSkill, bool bIsRandomOn) 
{
	float coeff = 0.0;
	if (iFencingType == 1) {
		coeff = 2.5 * aSkill;
	}
	else {
		coeff = 1.5; //для ЛО/ТО
	}
	return (1 + bIsRandomOn * rand(SWIFT_TIME_RAND) + coeff);
}

int CheckForSwift(ref attack, int nAttackIdx, ref enemy, int nEnemyIdx, int iFencingType, float aSkill)
{
	int valueSS = LAi_CalcSwiftChance(attack, iFencingType, aSkill);
	if (valueSS <= 0) { 
		return 0;// не вызываем pnrand лишний раз
	}
	float coeff = LAi_CalcSwiftDuration(attack, iFencingType, aSkill, 1);

	if (!pnrand(attack, valueSS, "swift")) {//основной чек
		return 0;
	}

	if(nAttackIdx == GetMainCharacterIndex()) {
		pchar.questTemp.swiftcount = sti(pchar.questTemp.swiftcount) + 1;
	}

	if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator" && enemy.sex != "skeleton") {
		if(nAttackIdx == GetMainCharacterIndex()) {
			Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_19", "Logs.txt", "#space#", " "));
			PlaySound("Fx_Stan");
		}
		if(nEnemyIdx == GetMainCharacterIndex()) {
			Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_20", "Logs.txt", "#space#", " "));
			PlaySound("Fx_Stan");
		}
		MakeSwiftAttack(enemy, attack, coeff);
	}
	else {
		if(nAttackIdx == GetMainCharacterIndex()) {
			Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_21", "Logs.txt", "#space#", " "));
			PlaySound("Fx_Krovotok");
		}
		if(nEnemyIdx == GetMainCharacterIndex()) {
			Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_22", "Logs.txt", "#space#", " "));
			PlaySound("Fx_Krovotok");
		}
		return MakeInt(5 + 4 * coeff);
	}
	return 0;
}

void CheckForStun(ref attack, int nAttackIdx, ref enemy, int nEnemyIdx)
{
	int valueStS = sti(attack.chr_ai.special.valueStS);
	if (valueStS == 0) {
		return;// не вызываем pnrand лишний раз
	}
	if (!pnrand(attack, valueStS, "stun")) {
		return;
	}

	if(nAttackIdx == GetMainCharacterIndex())
	{
		Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_27", "Logs.txt", "#space#", " "));
		PlaySound("Fx_Stan");
		pchar.questTemp.stuncount = sti(pchar.questTemp.stuncount) + 1;
	}
	if(nEnemyIdx == GetMainCharacterIndex())
	{
		Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_28", "Logs.txt", "#space#", " "));
		PlaySound("Fx_Stan");
	}
	MushketStun(enemy);
	return;
}

//шанс травмы. Чекает кирасу цели при iEnemyCuirassID > 0
int LAi_CalcTraumaChance(ref attack, int iEnemyCuirassID)
{
	float valueT = sti(attack.chr_ai.special.valueT);
	if (iEnemyCuirassID) {
		valueT *= 0.833;
	}
	return MakeInt(valueT);
}

void CheckForTrauma(ref attack, int nAttackIdx, ref enemy, int nEnemyIdx, int iEnemyCuirassID)
{
	int valueT = LAi_CalcTraumaChance(attack, iEnemyCuirassID);
	if (valueT == 0) {
		return;
	}
	if (!pnrand(attack, valueT, "injury")) {//основной чек
		return;
	}

	if (!CheckAttribute(enemy,"chr_ai.TraumaQ")) { enemy.chr_ai.TraumaQ = 1; }
	else { enemy.chr_ai.TraumaQ = sti(enemy.chr_ai.TraumaQ)+1; }

	if(nAttackIdx == GetMainCharacterIndex()) {
		Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_29", "Logs.txt", "#space#", " "));
		PlaySound("Fx_HrustBones");
		pchar.questTemp.traumacount = sti(pchar.questTemp.traumacount) + 1;
	}
	if(nEnemyIdx == GetMainCharacterIndex()) {
		Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_30", "Logs.txt", "#space#", " "));
		PlaySound("Fx_HrustBones");
		if (CheckAttribute(enemy,"chr_ai.TraumaQ") && sti(enemy.chr_ai.TraumaQ) > 2) {
			Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_31", "Logs.txt", "#space#", " "));
			enemy.chr_ai.HeavyTrauma = 2;
			SetNoRun(enemy);
		}
	}
	MakeTraumaAttack(enemy, attack);
	return;
}

int LAi_CalcCuirassBreakChance(ref attack, int iFencingType, bool bAttackHardHitter, float aSkill)
{
	float valueCB = stf(attack.chr_ai.special.valueCB) + 5.0 * bAttackHardHitter;
	if (iFencingType == 2) {
		valueCB += (5.0 + 10.0 * aSkill);
	}
	valueCB += 3.0 * HasSubStr(attack.equip.blade, "topor");
	return MakeInt(valueCB);
}

bool CheckForCirassBreak(ref attack, int nAttackIdx, ref enemy, int nEnemyIdx, int iFencingType, bool bAttackHardHitter, int iEnemyCuirassID, float aSkill) 
{
	if (!iEnemyCuirassID) {
		return 0;
	}
	int valueCB = LAi_CalcCuirassBreakChance(attack, iFencingType, bAttackHardHitter, aSkill);
	if (valueCB <= 0) {
		return 0;
	} 
	if (!pnrand(attack, valueCB, "cpen")) {//основной чек
		return 0;
	}

	if(nAttackIdx == GetMainCharacterIndex()) {
		Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_39", "Logs.txt", "#space#", " "));
		PlaySound("Fx_Breaking");
	}
	if(nEnemyIdx == GetMainCharacterIndex()) {
		Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_40", "Logs.txt", "#space#", " "));
		PlaySound("Fx_Breaking");
	}
	return 1;
}

//boal 19.09.05 -->
void LAi_SetResultOfDeath(ref attack, ref enemy, bool isSetBlade)
{
    if (sti(attack.index) == GetMainCharacterIndex())
    {
		if (GetRelation2BaseNation(sti(enemy.nation)) == RELATION_ENEMY)
		{
			if (!isSetBlade)
			{
				ChangeCharacterReputation(attack, -1);   // to_do
				if (rand(1) && CheckAttribute(enemy, "City"))
				{
					ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 1);
				}
			}
		}
		else
		{
			if (CheckAttribute(enemy, "City"))
			{
				ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 2);
			}
		}
		// обида нации на разборки в городе boal 19.09.05
  		if (CheckAttribute(enemy, "City"))
		{
			// нужна проверка на дуэли и квесты
			if (GetSummonSkillFromName(attack, SKILL_SNEAK) < rand(140)) // скрытность
			{
			    SetNationRelation2MainCharacter(sti(enemy.nation), RELATION_ENEMY);
		    }
		}
		if (startherotype == 8)
		{
			if (CheckAttribute(pchar,"equip.blade") && HasSubStr(pchar.equip.blade, "Lilarcor"))
			{
				if (!CheckAttribute(pchar,"LilarcorKills")) pchar.LilarcorKills = 0;
				pchar.LilarcorKills = sti(pchar.LilarcorKills)+1;
				if (sti(pchar.LilarcorKills) == 300)
				{
					LAi_CharacterPlaySound(PChar, "Lilarcor_Up1");
					DeleteAttribute(pchar,"items.Lilarcor_Sword1");
					AddItems(pchar, "Lilarcor_Sword2", 1);
					EquipCharacterbyItem(pchar, "Lilarcor_Sword2");
				}
				if (sti(pchar.LilarcorKills) == 800)
				{
					LAi_CharacterPlaySound(PChar, "Lilarcor_Up2");
					DeleteAttribute(pchar,"items.Lilarcor_Sword2");
					AddItems(pchar, "Lilarcor_Sword3", 1);
					EquipCharacterbyItem(pchar, "Lilarcor_Sword3");
				}
				if (sti(pchar.LilarcorKills) == 1800)
				{
					LAi_CharacterPlaySound(PChar, "Lilarcor_Victory");
					string sEquipItem = GetGeneratedItem("blade48");
					AddItems(pchar, sEquipItem, 1);
					EquipCharacterbyItem(pchar, sEquipItem);
					RemoveItems(pchar, "Lilarcor_Sword3", 1);
				}
			}
		}
	}
}
// boal <--

//Начисление повреждений при попадании
void LAi_ApplyCharacterFireDamage(aref attack, aref enemy, float kDist)
{
	Lai_CharacterChangeEnergy(attack, -4); // жрем энергию за выстрел boal 20/06/06
	//Если неубиваемый, то нетрогаем его
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}
	//Вероятность поподания
	float p = LAi_GunCalcProbability(attack, enemy, kDist);
	//Если промахнулись, то выйдем
	if(rand(10000) > p*10000)
	{
		if(sti(attack.index) == GetMainCharacterIndex())
		{
			string missed = "";
			if(LanguageGetLanguage() != "russian")
			{
				switch (rand(4))
				{
					case 0: missed = "Missed!"; break;
					case 1: missed = "Are you blind?!"; break;
					case 2: missed = "Aim better!"; break;
					case 3: missed = "Aim already!"; break;
					case 4: missed = "Don't shoot in the air!"; break;
				}
			}
			else
			{
				switch (rand(4))
				{
					case 0: missed = "Промах!"; break;
					case 1: missed = "Мазила!"; break;
					case 2: missed = "Целься лучше!"; break;
					case 3: missed = "Да прицелься уже!"; break;
					case 4: missed = "Не попал!"; break;
				}
			}
			Log_Info(missed);
		}
		return;
	}
	string sBullet = LAi_GetCharacterBulletType(attack);
	bool ignore = false;
	if(sBullet == "powder_pellet") ignore = true;
	if(sBullet == "grenade") ignore = true;
	if(CheckCharacterPerk(enemy, "AgileMan"))
	{
		if (rand(3)==0 && !ignore)
		{
			Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_46", "Logs.txt", "#space#", " "))
			return;
		}
	}
	// boal брон работает всегда, а не токо в блоке 23.05.2004 -->
	if(CheckAttribute(enemy, "cirassId"))
	{
		if (CheckCharacterPerk(attack,"Buccaneer") || ignore) {}
		else
		{
			if(rand(1000) < stf(Items[sti(enemy.cirassId)].CirassLevel)*500)
			{
				if(sti(enemy.index) == GetMainCharacterIndex()) Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_47", "Logs.txt", "#space#", " "));
				PlayStereoSound("Fx_Ricochet");
				return;
			}
		}
	}

	// boal 23.05.2004 <--
	//Начисляем повреждение
	float damage = LAi_GunCalcDamage(attack, enemy);
	if (attack.chr_ai.sgun == "pistol_grapebok") damage *= 2;

	//Аттака своей группы
	bool noExp = false;
	if(CheckAttribute(attack, "chr_ai.group"))
	{
		if(CheckAttribute(enemy, "chr_ai.group"))
		{
			if(attack.chr_ai.group == enemy.chr_ai.group)
			{
				damage = 0.0;
				noExp = true;
			}
		}
	}
	if (HasSubStr(attack.equip.gun, "mushket")) //Мушкетное оглушение - Gregg
	{
		if (damage > 0 && rand(1)==0)
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_48", "Logs.txt", "#space#", " "));
				//PlaySound("interface\Breaking_"+rand(5)+".wav");
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_49", "Logs.txt", "#space#", " "));
				//PlaySound("interface\Breaking_"+rand(5)+".wav");
			}
			MushketStun(enemy);
		}
	}
	if(CheckAttribute(enemy, "cirassId"))
	{
		if (CheckCharacterPerk(attack,"Buccaneer") && rand(2)>0)
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_50", "Logs.txt", "#space#", " "));
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_51", "Logs.txt", "#space#", " "));
			}
		}
		else
		{
			if (!ignore)
			{
				damage = damage * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel));
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_52", "Logs.txt", "#space#", " "));
				}
			}
		}
	}
	if(damage > 0.0)
	{
		//Влияние точности на урон
		damage *= p;
		//Начисляем опыт
		float exp = LAi_GunCalcExperience(attack, enemy, damage);
		float critd = 1.0;
		int critchance = 0;
		int pured = 0;
		if (CheckCharacterPerk(attack,"Buccaneer")) 
		{
			critd = 1.3;
			critchance = 10;
		}
		if(IsEquipCharacterByArtefact(attack, "talisman1"))
		{
			critd = 2.0;
			critchance += 20;
			pured = 25;
		}
		if (critchance > 0 && rand(99)<critchance)	{LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5)*critd); Log_Info(GetConvertStrWithReplace("Variable_LAi_fightparams_53", "Logs.txt", "#space#", " "));}
		else LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5)+pured);

		//Проверим на смерть
		LAi_CheckKillCharacter(enemy);
	}
	//Есть ли оружие у цели
	bool isSetBlade = (CheckAttribute(enemy, "equip.blade"));//(SendMessage(enemy, "ls", MSG_CHARACTER_EX_MSG, "isSetBlade") != 0);
	/*if(LAi_grp_alarmactive == false)
	{
		if(CheckAttribute(pchar, "sneak.success"))
		{
			if(sti(pchar.sneak.success) == 1)
			{
				pchar.sneak.success = 0;
			}
		}
	}  */
	if(LAi_IsDead(enemy) && isSetBlade)
	{
		//Начислим за убийство
		//exp = exp + LAi_CalcDeadExp(attack, enemy);
		//exp = LAi_GetCharacterMaxHP(enemy) * 10;
		//noExp = false;
		//if(!isSetBlade)
		//{
			//ChangeCharacterReputation(attack, -3);
		//	exp = 0.0;
		//}
		//DoCharacterKilledStatistics(sti(attack.index), sti(enemy.index));
		// boal skill -->
		float ra = 1.0;
	    float re = 1.0;
	    if(CheckAttribute(attack, "rank"))
	    {
	       ra = stf(attack.rank);
	    }
	    if(CheckAttribute(enemy, "rank"))
	    {
	       re = stf(enemy.rank);
	    }
		if (stf(enemy.rank) < 4) int experience = GetCharacterSPECIALSimple(attack, SPECIAL_P) + rand(GetCharacterSPECIALSimple(attack, SPECIAL_I));
		else experience = Lai_GetCharacterMaxHP(enemy)/stf(enemy.rank) + GetCharacterSPECIALSimple(attack, SPECIAL_P) * re / ra;//Lipsar передeлка опыта
		AddCharacterExpToSkill(attack, SKILL_PISTOL, experience);
        AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 2);
        AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
		// boal skill <--
		// boal statistic info 17.12.2003 -->
        Statistic_KillChar(attack, enemy, "_g");
        // boal statistic info 17.12.2003 <--

        //Начислим за убийство
		/*exp = exp + */
        //LAi_CalcDeadExp(attack, enemy); // начисляем только за удар и смерть
  		LAi_SetResultOfDeath(attack, enemy, isSetBlade);
	}
	if(sBullet == "grapeshot")
		exp *= 2;
	if(!isSetBlade)
	{
		//ChangeCharacterReputation(attack, -1);
		exp = 0.0;
	}

	if(!noExp)
    {
        AddCharacterExpToSkill(attack, SKILL_PISTOL, MakeFloat(exp*0.65));
    }
}

void SetBack()
{

}

//--------------------------------------------------------------------------------
//Параметры NPC
//--------------------------------------------------------------------------------

float npc_return_tmp;
bool npc_return_tmpb;

//Атаки
//Скорость нарастания вероятности атаки в секунду  p > 0, или средняя скорость ударов в секунду
//нужно выставлять соответсвенно скорости анимок ИИ, оставляя минимум 10-20% на защиты/пробивные
#event_handler("NPC_Event_GetAttackActive","LAi_NPC_GetAttackActive");
float LAi_NPC_GetAttackActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = 0.22 + MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE*0.04 - level*0.1;
	//скилл 10 - 0.25, 0.37, 0.57;
	//скилл 100 - 0.16, 0.28, 0.43;
	if(CheckAttribute(chr, "SaveItemsForDead"))
	{
		if(chr.SaveItemsForDead == true)
		{
			npc_return_tmp *= 1.18;
		}
	}
	else
	{
		if(random()*4 <= 1)
		{
			npc_return_tmp *= 1.15;
		}
	}
	return npc_return_tmp;
}

//Вес выбора удара "fast", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightFast","LAi_NPC_GetAttackWeightFast");
float LAi_NPC_GetAttackWeightFast()
{
	aref chr = GetEventData();
	npc_return_tmp = 1.0;
	//npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE*3));
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	if (LAi_GetBladeEnergyType(chr) == "Fencing")
	{
		npc_return_tmp = npc_return_tmp * 5 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE + 0.05));
	}
	else
	{
		npc_return_tmp = npc_return_tmp * 2 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE + 0.05));
	}
	return npc_return_tmp;
}

//Вес выбора удара "force", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightForce", "LAi_NPC_GetAttackWeightForce");
float LAi_NPC_GetAttackWeightForce()
{
	aref chr = GetEventData();
	npc_return_tmp = 1.0;
	//npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE*3));
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	if (LAi_GetBladeEnergyType(chr) == "FencingLight")
	{
		npc_return_tmp = npc_return_tmp * 5 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE + 0.05));
	}
	else
	{
		npc_return_tmp = npc_return_tmp * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE + 0.05));
	}
	return npc_return_tmp;
}

//Вес выбора удара "round", 0 - никогда не выбирать, если врагов <3 то вес удара не накапливается
#event_handler("NPC_Event_GetAttackWeightRound", "LAi_NPC_GetAttackWeightRound");
float LAi_NPC_GetAttackWeightRound()
{
	aref chr = GetEventData();
	npc_return_tmp = 1.0;
	//npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE*3));
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	if (LAi_GetBladeEnergyType(chr) == "FencingLight")
	{
		npc_return_tmp = npc_return_tmp * 2 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE + 0.05));
	}
	else
	{
		npc_return_tmp = npc_return_tmp * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE + 0.05));
	}
	return npc_return_tmp;
}

//Вес выбора удара "break", 0 - никогда не выбирать. если цель не блокирует, то вес удара не накапливается
#event_handler("NPC_Event_GetAttackWeightBreak", "LAi_NPC_GetAttackWeightBreak");
float LAi_NPC_GetAttackWeightBreak()
{
	aref chr = GetEventData();
	npc_return_tmp = 1.0;
	if (LAi_GetBladeEnergyType(chr) == "FencingHeavy")
	{
		npc_return_tmp = npc_return_tmp * 2 * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE));
	}
	else
	{
		npc_return_tmp = npc_return_tmp	* 0.5 * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE));
	}
	return npc_return_tmp;
}

//Вес выбора удара "feint", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightFeint", "LAi_NPC_GetAttackWeightFeint");
float LAi_NPC_GetAttackWeightFeint()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = 1.0; //boal fix
	npc_return_tmp = npc_return_tmp * ((0.14 + 0.06 * level) * MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE));
	//cкилл 10 0.15, 0.6, 1.35
	//скилл 100 0.2, 0.8, 1.8
	return npc_return_tmp;
}

//Прараметры защиты
//Вероятность желания защитится - кубик с такой вероятностью кидается 2 раза в секунду, 1 = 100%
//больше 1 может выдать несколько защит по очереди
#event_handler("NPC_Event_GetDefenceActive", "LAi_NPC_GetAttackDefence");
float LAi_NPC_GetAttackDefence()
{
	aref chr = GetEventData();

	npc_return_tmp = 0.2 + (MOD_SKILL_ENEMY_RATE*4.5-3.5)*0.08;//матрос 0.28, кэп 0.64, ад 1

	return npc_return_tmp;

}/*old reaction
float LAi_NPC_GetAttackDefence()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	if (LAi_GetBladeFencingType(pchar) == "FencingHeavy")

	{
		npc_return_tmp = 1 + level * 0.35;
		return npc_return_tmp;
	}
	else
	{
		npc_return_tmp = 0.35 + level * 0.35;
		return npc_return_tmp;
	}
}*/

// boal 20.01.08 коммент - забавно, что спустя два года, понал как и что с вероятностями. Они все приводятся к 0-1 от веса общей суммы, то есть фактически умножение на сложность или цифры распределяют сумму по другим акшенам, а не усиливают этот
// Экшены идут парами - все атаки и защита (блок + пари)
//Вес выбора блока, 0 - никогда не выбирать
#event_handler("NPC_Event_GetDefenceWeightBlock", "LAi_NPC_GetDefenceWeightBlock");
float LAi_NPC_GetDefenceWeightBlock()
{
	aref chr = GetEventData();	
	float level = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = 0.4 + 0.5 * (level - 0.2);// влияние exe - 0 навык увеличивает время блока в ~3 раза сравнительно с 100
	/*if (LAi_GetBladeFencingType(pchar) == "FencingHeavy")
	{
		npc_return_tmp /= 2;
	}*/
	return npc_return_tmp;
}

//Вес выбора  паррирования, 0 - никогда не выбирать
//кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetDefenceWeightParry","LAi_NPC_GetDefenceWeightParry");
float LAi_NPC_GetDefenceWeightParry()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = 2.0 - 0.5 * level; // 40 boal
	return npc_return_tmp;
}

//Разрешён ли отскок
#event_handler("NPC_Event_EnableRecoil","LAi_NPC_EnableRecoil");
bool LAi_NPC_EnableRecoil()
{
	aref chr = GetEventData();
	npc_return_tmpb = true;
	return npc_return_tmpb;
}

#event_handler("NPC_Event_StunChance","LAi_NPC_StunChance");//Добавлен евент на стан после удара. Шансы расписаны ниже. Lipsar
float LAi_NPC_StunChance()
{
	aref chr = GetEventData();
	npc_return_tmp = 100;
	if (CheckAttribute(chr,"cirassid")) npc_return_tmp -= 35;
	if (IsCharacterPerkOn(chr, "SwordplayProfessional")) return npc_return_tmp -= 50;
	if (IsCharacterPerkOn(chr, "AdvancedDefence")) return npc_return_tmp -= 30;
	if (IsCharacterPerkOn(chr, "BasicDefence")) return npc_return_tmp -= 10;
	return npc_return_tmp;
}

//Параметры стрельбы

//Shot through allies
#event_handler("NPC_Event_ShotOnlyEnemyTest", "LAi_NPC_ShotOnlyEnemyTest");
bool LAi_NPC_ShotOnlyEnemyTest()
{
	if (bShootOnlyEnemy) return LAi_grp_alarmactive;
	else return false;
}

//Вероятность желания выстрелить - кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetFireActive","LAi_NPC_GetFireActive");
float LAi_NPC_GetFireActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmp = 0.005 + level*0.01;
	// boal наши офицеры пулят из всех стволов -->
	if (chr.chr_ai.group == LAI_GROUP_PLAYER)
	{
      npc_return_tmp = 0.38 + npc_return_tmp;
	}
	else
	{
	// boal наши офицеры пулят из всех стволов <--
		if (CheckAttribute(chr, "SuperShooter"))
		{
			npc_return_tmp = npc_return_tmp + 0.4 * MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE / 9.0;
		}
		else
		{
			npc_return_tmp = npc_return_tmp + 0.05 * MOD_SKILL_ENEMY_RATE*MOD_SKILL_ENEMY_RATE / 9.0;
		}
	}
	//if (npc_return_tmp > 0.5) npc_return_tmp = 0.5;
	return npc_return_tmp;
}

//Разрешён ли выстрел
#event_handler("NPC_Event_EnableFire","LAi_NPC_EnableFire");
bool LAi_NPC_EnableFire()
{
	aref chr = GetEventData();
	return   true;
	/*float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmpb = false;
	if(!iArcadeFencingAI)
	{
		level = level + 0.02;
	}
	else
	{
		level = level - 0.01;
	}
	if(level > 0.1) npc_return_tmpb = true;
	return npc_return_tmpb;    */
}

//Разрещён ли временный перевыбор цели среди ближних - опрашивается постоянно
#event_handler("NPC_Event_AdaptiveTargetSelect","LAi_NPC_AdaptiveTargetSelect");
bool LAi_NPC_AdaptiveTargetSelect()
{
	aref chr = GetEventData();
	if(chr.chr_ai.type == LAI_TYPE_ACTOR)
	{
		npc_return_tmpb = false;
	}else{
		npc_return_tmpb = true;
	}
	return npc_return_tmpb;
}


//--------------------------------------------------------------------------------
//Work
//--------------------------------------------------------------------------------

#event_handler("Location_CharacterSGFire","LAi_Location_CharacterSGFire");
void LAi_Location_CharacterSGFire()
{
	aref attack = GetEventData();
	aref enemy = GetEventData();
	float kDmg = GetEventData();
	if(LAi_IsDead(enemy)) return;
	//Реакция груп на атаку
	LAi_group_Attack(attack, enemy);
	//AddCharacterExp(attack, 100*kDmg);
	//Наносим повреждение
	LAi_ApplyCharacterDamage(enemy, MakeInt((5 + rand(5))*kDmg));
	//Проверим на смерть
	LAi_CheckKillCharacter(enemy);
}

#event_handler("ChrAttackAction", "LAi_ChrAttackAction");
bool LAi_ChrAttackAction()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float fAttackSkill = LAi_GetCharacterFightLevel(attack);
	float curEnergy = Lai_CharacterGetEnergy(attack);
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType, fAttackSkill);
	if(curEnergy >= needEnergy)
	{
		npc_return_tmpb = true;
	}
	else
	{
		npc_return_tmpb = false;
	}
	return npc_return_tmpb;
}
//#20200510-03
#event_handler("Event_ChrFeint_Init", "LAi_BlockInitTime");
#event_handler("Event_ChrBlock_Init", "LAi_BlockInitTime");
#event_handler("Event_ChrParry_Init", "LAi_BlockInitTime");
void LAi_BlockInitTime()
{
	aref chr = GetEventData();
	float fSet = GetEventData();
	chr.chr_ai.BlockInitTime = fSet;
}

#event_handler("ChrFgtActApply", "LAi_ChrFightActionApply");
void LAi_ChrFightActionApply()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float fAttackSkill = LAi_GetCharacterFightLevel(attack);
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType, fAttackSkill);
	Lai_CharacterChangeEnergy(attack, -needEnergy);
}

//Получить относительную затрачиваемую энергию
#event_handler("NPC_Event_GetActionEnergy","LAi_NPC_GetActionEnergy");
float LAi_NPC_GetActionEnergy()
{
	aref chr = GetEventData();
	string act = GetEventData();
	float fAttackSkill = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = LAi_CalcUseEnergyForBlade(chr, act, fAttackSkill) / LAi_GetCharacterMaxEnergy(chr);  // boal
	return npc_return_tmp;
}

//Необходимо вернуть максимально быстро нормализованое значение жизни
#event_handler("NpcEvtHP", "LAi_NPC_EvtGetHP");
float LAi_NPC_EvtGetHP()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelHP(chr);
	return npc_return_tmp;
}


//Необходимо вернуть максимально быстро нормализованое значение энергии
#event_handler("NpcEvtEny", "LAi_NPC_EvtGetEny");
float LAi_NPC_EvtGetEny()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelEnergy(chr);
	return npc_return_tmp;
}

// EvgAnat - требование энергии для отскока -->
bool bIsRecoilEnableWithoutEnergy = false; // можно ли выполнять отскоки при недостатке энергии (это не влияет на расход энергии)

#event_handler("ChrCheckEnergy", "LAi_Chr_CheckEnergy");
bool LAi_Chr_CheckEnergy()
{
	aref chr = GetEventData();
	string action = GetEventData(); // "recoil" - отскок назад, "strafe_l" и "strafe_r" - отскоки влево и вправо
	bool res = false;
	float needEnergy = 0.0;
	switch(action)
	{
		case "recoil":		needEnergy = 3.0;	break;
		case "strafe_l":	needEnergy = 4.0;	break;
		case "strafe_r":	needEnergy = 4.0;	break;
	}
	if (stf(chr.chr_ai.energy) >= needEnergy)
	{	
		res = true;
		Lai_CharacterChangeEnergy(chr, -needEnergy);
	}
	if (bIsRecoilEnableWithoutEnergy)
		return true;
	return res;
}
// EvgAnat - требование энергии для отскока <--

// EvgAnat - включено ли уклонение от выстрела для нпс -->
#event_handler("NPC_IsDodgeEnabled", "LAi_Chr_IsDodgeEnabled");
bool LAi_Chr_IsDodgeEnabled()
{
	return true;
}
// EvgAnat - включено ли уклонение от выстрела для нпс <--

// EvgAnat - уклонение от выстрела -->
#event_handler("Check_ChrHitFire", "LAi_Chr_CheckHitFire");
int LAi_Chr_CheckHitFire() // 0 - не попал, 1 - попал
{
	aref shooter = GetEventData(); // стрелок
	aref target = GetEventData(); // цель
	bool isRecoil = GetEventData(); // находится ли цель в окне уклонения 
	float kDist = GetEventData(); // коэффициент дальности, равный 1-d/25; k(0)=1; k(10)=0.6; k(25)=0
	int res = 1;
	float r = Random();
	if (isRecoil && r <= 0.75)
	{
		res = 0;
		if (shooter.index == GetMainCharacterIndex())
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_LAi_fightparams_54", "Logs.txt", "#space#", " "));
	}
	return res;
}
// EvgAnat - уклонение от выстрела <--

// EvgAnat - уклонение от атаки -->
#event_handler("Check_ChrHitAttack", "LAi_Chr_CheckHitAttack");
bool LAi_Chr_CheckHitAttack() // попала ли атака
{
	aref attack = GetEventData();
	aref enemy = GetEventData();
	bool isRecoil = GetEventData(); // находится ли цель в окне уклонения
	bool res = true;
	if (isRecoil)
		res = false;	
	return res;
}
// EvgAnat - уклонение от атаки <--

// EvgAnat - вероятность желания уклониться от выстрела у нпс -->
#event_handler("NPC_IsDodge", "LAi_NPC_IsDodge");
bool LAi_NPC_IsDodge() // true - уклоняется, false - не уклоняется
{
	aref chr = GetEventData();
	float r = Random();
	bool res = false;
	if (r <= 0.25)
		res = true;
	return res;
}
// EvgAnat - вероятность желания уклониться от выстрела у нпс <--

// EvgAnat - дальность отскока и стрейфа -->
#event_handler("GetCharacterRecoilDistance", "LAi_GetRecoilDistance");
float LAi_GetRecoilDistance()
{
	aref chr = GetEventData();
	string aType = GetEventData();
	float res = 2.0;
	switch(aType)
	{
		case "recoil":
			res = 1.0; // по умолчанию 2.0
		break;
		case "strafe":
			res = 10.0; // по умолчанию 15.0
		break;
	}
	return res;
}
// EvgAnat - дальность отскока и стрейфа <--
