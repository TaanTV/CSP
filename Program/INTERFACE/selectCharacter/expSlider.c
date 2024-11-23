void setMinMaxExpRate()
{
	setDefaultExpValue();
	int iMinExpVal = floatToExpRate(0.0);
	int iMaxExpVal = floatToExpRate(1.0);
	SetFormatedText("EXP_SLIDE_MIN", "Min\nx"+FloatToString(EXP_RATE_ONE_SCALE/iMinExpVal, 2));
	SetFormatedText("EXP_SLIDE_MAX", "Max\nx"+FloatToString(EXP_RATE_ONE_SCALE/iMaxExpVal, 2));
}

void setDefaultExpValue()
{
	int expRate = EXP_RATE_ONE_SCALE;
	switch (MOD_SKILL_ENEMY_RATE) {
		case SAILOR_DIFFICULTY: expRate = DEFAULT_SAILOR_DIFFICULTY_EXP_RATE; break;
		case CAPTAIN_DIFFICULTY: expRate = DEFAULT_CAPTAIN_DIFFICULTY_EXP_RATE; break;
		case ADMIRAL_DIFFICULTY: expRate = DEFAULT_ADMIRAL_DIFFICULTY_EXP_RATE; break;
	}
	float slideExpRate = intToExpRate(expRate);
	GameInterface.nodes.EXP_SLIDE.value = slideExpRate;
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"EXP_SLIDE", 0, slideExpRate);
	SetFormatedText("EXP_SLIDE_VALUE", "x"+FloatToString(EXP_RATE_ONE_SCALE/slideExpRate, 2));
}

int floatToExpRate(float sliderVal)
{
	int iMin = getMinExpRate();
	int iMax = getMaxExpRate();
	int iVal = iMin + ((iMax - iMin) * (1.0 - sliderVal));
	return iVal;
}

int getMinExpRate() {
	switch (MOD_SKILL_ENEMY_RATE) {
		case SAILOR_DIFFICULTY: return MIN_SAILOR_EXP_RATE; break;
		case CAPTAIN_DIFFICULTY: return MIN_CAPTAIN_EXP_RATE; break;
		case ADMIRAL_DIFFICULTY: return MIN_ADMIRAL_EXP_RATE; break;
	}
}

int getMaxExpRate() {
	return MAX_EXP_RATE;
}

float intToExpRate(int expRate) {
	int iMin = getMinExpRate();
	int iMax = getMaxExpRate();
	return 1.0 - ((expRate - iMin) / makefloat(iMax - iMin));
}

void updateExpSlide() {
	int iExpVal = floatToExpRate(stf(GameInterface.nodes.EXP_SLIDE.value));
	SetFormatedText("EXP_SLIDE_VALUE", "x"+FloatToString(EXP_RATE_ONE_SCALE/iExpVal, 2));
}