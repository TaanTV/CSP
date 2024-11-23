// -------------------------------------------------------------
// Mett: настройки моря
// заготовки на разные типы волнения:
// штиль, легкий бриз, бриз, умеренный бриз, сильный бриз, шторм
// -------------------------------------------------------------

// bestreducer 22.10.23:
// значения моря сильно багуют:
// fReflection требуется >0.5. Если ставить 0.5 или меньше, то отражения вдали начинают "чернить". Если нужны отражения слабее, подымай fFrenel;
// iSkyColor - основной параметр Reflection-а - не учитывает цвет моря/свет солнца, тч нужно смешивать в него свет солнца, облаков и моря. Оно еще отражает туман в туманную погоду смесью этого цвета и цвета тумана;
// Transparency ночью у островов может создать/усилить визуальные артефакты (если >0.05). При ниже 0.11 перестает быть прозрачным в принципе и усиливает зеркальность моря, при выше 0.15 просвечивает слишком сильно.
// Sea.MaxSeaDistance - дальность реальных волн. 
// fFoamK - сила градиента пены - не стоит ставить высокой, тк пена в реальности не сохраняет форму и расползается по волне
// fFrenel и fAttenuation нужно настраивать вместе. Первый - не выше 0.65 - усиливает свет проходящий под поверхностью воды издали(как по линзе, на глубине примерно 10-150 см, и тем самым уменьшает светимость воды из глубины), второй увеличивает общую светимость воды. Также fFrenel уменьшает отражения, не затемняя их. Вблизи отражения намного слабее, это тоже стоит учитывать. 
// iWaterColor - если море светится после всех настроек,  то можно затемнить цвет моря в инитах - Sea2.WaterColor
// Weather.Fog, Weather.Sun 
// параметры в первую очередь подхватываются отсюда 

object PSea;	//объект для хранения настроек пресетов

//выбераем нужный пресет от силы ветра в море
string WhrGetSeaPresetFromWind(float fWind)

{
	ref mchr = GetMainCharacter();
	string sLocation = mchr.location;
	string sPreset = "calm";
	if(fWind > 1.5) sPreset = "light_breeze";
	//мин скорость ветра в погодах 4-5
	if(fWind > 3.3) sPreset = "gentle_breeze";
	if(fWind > 5.4) sPreset = "moderate_breeze";
	if(fWind > 7.9) sPreset = "fresh_breeze";
	if(fWind > 10.7) sPreset = "strong_breeze";
	if(fWind > 13.8) sPreset = "near_gale";
	if(fWind > 17.1) sPreset = "gale";
	if(FindLocation(sLocation) != -1){
		if (fWind > 1.0) sPreset = "light_breeze_land";
		if (fWind > 10.0) sPreset = "strong_breeze_land";
		if (fWind > 18.0) sPreset = "storm_land";
	}
	if(CheckAttribute(&WeatherParams, "Storm") && sti(WeatherParams.Storm) == 1) sPreset = "storm";
	return sPreset;
}

//настройки пресетов
void WhrSetSeaPreset(int iCurWeatherNum, string sPreset, float fWind)
{
	ref Whr = &Weathers[iCurWeatherNum];
	Sea.MaxSeaDistance = 2700.0;
	string sMoveSpeed1, sMoveSpeed2
	float fAmp1, fAnimSpeed1, fScale1;
	float fAmp2, fAnimSpeed2, fScale2;
	float fBumpScale, fPosShift = 2.25;
	float fFoamK, fFoamV, fFoamUV, fFoamTexDisturb;
	float fReflection, fTransparency, fFrenel, fAttenuation;
	int iWaterColor = Whr_GetColor(Whr,"Sea2.WaterColor");
	int iSkyColor;
	int iHour = MakeInt(GetHour());
	bool bRain = CheckAttribute(&WeatherParams,"Rain") * sti(WeatherParams.Rain);
	
	fReflection = 0.51;
	fFrenel = 0.62;
	fAttenuation = 0.3;
	fTransparency = 0.13;
	
	fFoamK = 0.08;
	fFoamTexDisturb = 0.5;// [0.5,0.7]	
	iSkyColor = argb(0,255,255,255);
	
	if (iHour < 5 ) {
		fReflection = 0.17;
		fAttenuation = 0.4;
		fFoamK = fFoamK / 5;
	} else {
	if (iHour == 22) {
		fReflection = 0.28;
	} else {
	if (iHour == 5 || iHour == 23) {
		fReflection = 0.24;
		fFoamK = fFoamK / 2;
	}}}

	switch(sPreset)
	{
		case "calm": //штиль --unused
			fAmp1 = 2.0;
			fAnimSpeed1 = 1.0;
			fScale1 = 1.25;
			sMoveSpeed1 = "1.5, 0.0, 1.5";

			fAmp2 = 1.25;
			fAnimSpeed2 = 1.25;
			fScale2 = 2.0;
			sMoveSpeed2 = "-1.5, 0.0, -1.5";

			fBumpScale = 0.075; 

			fFoamV = 1.75;
			fFoamUV = 0.7;

			if( iHour >= 10.0 && iHour < 17.0 )	{
				iWaterColor = argb(0,0,100,160);
			}
		break;

		case "light_breeze": //легкий ветер --unused
			fAmp1 = fWind * 0.625 + 1;//3.0;
			fAnimSpeed1 = 2.5;
			fScale1 = 1.0;
			sMoveSpeed1 = "0.0, 0.0, 2.5";

			fAmp2 = 1.75;
			fAnimSpeed2 = 2.5;
			fScale2 = 2.0;
			sMoveSpeed2 = "-2.5, 0.0, 0.0";

			fBumpScale = 0.08;

			fFoamV = 4.0;
			fFoamUV = 0.7;
			fFoamTexDisturb = 0.7;
			
			if( iHour > 10.0 && iHour < 17.0 )	{
				iWaterColor = argb(0,0,95,160);
			}
		break;

		case "gentle_breeze":	//слабый ветер - 4-5.5
			fAmp1 = fWind * 0.8 + 1;//5.0;
			fAnimSpeed1 = 1.25;
			fScale1 = 0.6;
			sMoveSpeed1 = "0.0, 0.0, 2.0";

			fAmp2 = 2.0;
			fAnimSpeed2 = 2.0;
			fScale2 = 1.5;
			sMoveSpeed2 = "-2.0, 0.0, 0.0";

			fBumpScale = 0.05;

			fFoamV = fAmp1 * 0.76;//4.25;
			fFoamUV = 0.5;
		break;

		case "moderate_breeze":	//умеренный ветер 5.5-8
			fAmp1 = fWind * 0.8 + 1;//7.0;
			fAnimSpeed1 = 3.0;
			fScale1 = 0.4;
			sMoveSpeed1 = "0.0, 0.0, 3.5";

			fAmp2 = 2.0;
			fAnimSpeed2 = 2.0;
			fScale2 = 1.5;
			sMoveSpeed2 = "-3.5, 0.0, 0.0";

			fPosShift = 3.2;
			fBumpScale = 0.08;

			fFoamV = fAmp1 * 0.74;//5.0;
			fFoamUV = 0.4;
		break;

		case "fresh_breeze":// свежий ветер 8-11
			fAmp1 = fWind * 0.65 + 1;//9.0;
			fAnimSpeed1 = 1.5;
			fScale1 = 0.30;
			sMoveSpeed1 = "0.0, 0.0, 3.0";

			fAmp2 = 3.0;
			fAnimSpeed2 = 3.0;
			fScale2 = 1.25;
			sMoveSpeed2 = "1.0, 0.0, 1.0";

			fBumpScale = 0.075;

			fFoamV = fAmp1 * 0.775;//7.0;
			fFoamUV = 0.3;
		break;

		case "strong_breeze":// сильный ветер - 11-14
			fAmp1 = fWind * 0.65 + 1;//15;
			fAnimSpeed1 = 2.0;
			fScale1 = 0.30;
			sMoveSpeed1 = "0.0, 0.0, 4.0";

			fAmp2 = 3.0;
			fAnimSpeed2 = 3.0;
			fScale2 = 1.0;
			sMoveSpeed2 = "0.0, 0.0, -1.0";

			fBumpScale = 0.075;
			fPosShift = 3.0;

			fFoamV = fAmp1 * 0.7;//8.0;
			fFoamUV = 0.24;
			fFoamTexDisturb = 0.7;
		break;

		case "near_gale"://крепкий ветер - 14-17
			fAmp1 = fWind * 0.8 + 1;//20.0;
			fAnimSpeed1 = 1.75;
			fScale1 = 0.20;
			sMoveSpeed1 = "0.0, 0.0, 5.0";

			fAmp2 = 3.3;
			fAnimSpeed2 = 4.0;
			fScale2 = 1.0;
			sMoveSpeed2 = "0.0, 0.0, -1.0";

			fBumpScale = 0.075;
			fPosShift = 3.2;

			fFoamV = fAmp1 * 0.70;//12.0;
			fFoamUV = 0.23;
			fAttenuation = 0.2;
		break;

		case "gale"://очень крепкий ветер - 17+
			fAmp1 = 22.0;
			fAnimSpeed1 = 2.0;
			fScale1 = 0.125;
			sMoveSpeed1 = "8.0, 0.0, 0.0";

			fAmp2 = 6.0;
			fAnimSpeed2 = 6.0;
			fScale2 = 0.75;
			sMoveSpeed2 = "0.0, 0.0, -1.0";

			fBumpScale = 0.08;
			fPosShift = 3.8;

			fFoamV = 15.0;
			fFoamUV = 0.1;
			fFoamTexDisturb = 0.7;
			fAttenuation = 0.2;
			
			if( iHour > 6.0 && iHour < 10.0 ) {
				fFoamK = 0.05;
			} 
		break;

		case "storm"://шторм
			fAmp1 = fWind * 2 + 1;//48;
			fAnimSpeed1 = 2.25;
			fScale1 = 0.075;
			sMoveSpeed1 = "12.0, 0.0, 0.0";

			fAmp2 = 9.0;
			fAnimSpeed2 = 8.0;
			fScale2 = 0.5;
			sMoveSpeed2 = "0.0, 0.0, 4.0";

			fBumpScale = 0.05;
			fPosShift = 2.25;

			fFoamV = fAmp1 * 0.53;//36.0;
			fFoamUV = 0.3;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.6;
			fAttenuation = 0.12;
			fReflection = 0.35;
			fTransparency = 0.02;
			
			if (iHour < 6.0 || iHour >= 21.0) {
				fFoamK = 0.011;
				iWaterColor = argb(0,5,10,20);
			} else {
			if( iHour >= 6.0 && iHour < 10.0 ) {
				fFoamK = 0.014;
				iWaterColor = argb(0,5,30,40);
			} else {
			if( iHour >= 10.0 && iHour < 21.0 )	{
				fFoamK = 0.014;
				iWaterColor = argb(0,0,55,60);
			}}}
		break;

		case "light_breeze_land":	//легкий ветер суша
			fAmp1 = 0.5;
			fAnimSpeed1 = 1.0;
			fScale1 = 1.75;
			sMoveSpeed1 = "0.5, 0.0, 0.0";

			fAmp2 = 0.5;
			fAnimSpeed2 = 1.0;
			fScale2 = 1.75;
			sMoveSpeed2 = "0.0, 0.0, -0.5";

			fBumpScale = 0.15; 
			fPosShift = 1.75;

			fFoamV = 5.0;
			fFoamK = 0.0;
			fFoamUV = 0.3;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.3;
		break;

		case "strong_breeze_land": //сильный ветер суша
			fAmp1 = 3.0;
			fAnimSpeed1 = 1.0;
			fScale1 = 2.5;
			sMoveSpeed1 = "0.5, 0.0, 0.0";

			fAmp2 = 3.0;
			fAnimSpeed2 = 1.0;
			fScale2 = 2.5;
			sMoveSpeed2 = "0.0, 0.0, -0.5";

			fBumpScale = 0.15; 
			fPosShift = 1.3;

			fFoamV = 0.45;
			fFoamK = 1.0;
			fFoamUV = 0.3;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.3;
		break;

		case "storm_land": //сильный ветер суша
			fAmp1 = 20.0;
			fAnimSpeed1 = 2.0;
			fScale1 = 0.125;
			sMoveSpeed1 = "8.0, 0.0, 0.0";

			fAmp2 = 6.0;
			fAnimSpeed2 = 6.0;
			fScale2 = 0.55;
			sMoveSpeed2 = "0.0, 0.0, -1.0";

			fBumpScale = 0.08;
			fPosShift = 3.8;

			fFoamV = 15.0;
			fFoamUV = 0.20;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.6;
			fReflection = 0.3;
		break;	
	}
	//дождь работает только с 6 до 21 часов
	if(bRain && !(sPreset == "storm")){			
		if (iHour < 6.0 || iHour >= 21.0) {
			iWaterColor = argb(0,5,10,20);
		} else {
		if( iHour >= 6.0 && iHour < 10.0 ) {
			iWaterColor = argb(0,5,30,54);
		} else {
		if( iHour >= 10.0 && iHour < 21.0 )	{
			iWaterColor = argb(0,0,55,80);
		}}}
		fTransparency = 0.03;
	}	
	if(iCurWeatherNum == 29)//шторм и гпк
	{
		fFrenel = 0.6; 
		fAttenuation = 0.2;
	}
	
	DeleteAttribute(PSea, "");				//чистим объект перед записью данных

	PSea.Amp1 = fAmp1;						//амплитуда 1 волны
	PSea.AnimSpeed1 = fAnimSpeed1; 			//скорость анимации
	PSea.Scale1 = fScale1;					//размеры волны
	PSea.MoveSpeed1 = sMoveSpeed1;			//скорость движени¤

	PSea.Amp2 = fAmp2;						//амплитуда 2 волны
	PSea.AnimSpeed2 = fAnimSpeed2;			//скорость анимации
	PSea.Scale2 = fScale2;					//размеры волны
	PSea.MoveSpeed2 = sMoveSpeed2;			//скорость движени¤

	PSea.BumpScale = fBumpScale;			//ћ≈Ћ »≈ ¬ќЋЌџ
	PSea.PosShift = fPosShift;				//остроконечность волн

	PSea.FoamK = fFoamK;					//¤ркость пены
	PSea.FoamV = fFoamV;					//высота с которой начинаетс¤ пена
	PSea.FoamUV = fFoamUV;					//тайлинг пены
	PSea.FoamTexDisturb = fFoamTexDisturb;	//сдвиг по нормали, значение от 0.0 до 1.0

	PSea.Reflection = fReflection;
	PSea.Transparency = fTransparency;
	PSea.Frenel = fFrenel;
	PSea.Attenuation = fAttenuation;
	PSea.WaterColor = iWaterColor;
	PSea.SkyColor = iSkyColor;

	Log_TestInfo("WhrSetSeaPreset: " + sPreset + " FoamK = " + fFoamK);
	Log_TestInfo("WindSpeed: " + fWeatherSpeed);
}

//записываем значени¤ из PSea в море Sea.Sea2
void WhrSetNewSea(float fWind)
{
	string sPreset = WhrGetSeaPresetFromWind(fWind);

	WhrSetSeaPreset(iCurWeatherNum, sPreset, fWind);

	Sea.Sea2.Amp1 = Whr_GetFloat(PSea, "Amp1");
	Sea.Sea2.AnimSpeed1 = Whr_GetFloat(PSea, "AnimSpeed1");
	Sea.Sea2.Scale1 = Whr_GetFloat(PSea, "Scale1");
	Sea.Sea2.MoveSpeed1 = Whr_GetString(PSea, "MoveSpeed1");

	Sea.Sea2.Amp2 = Whr_GetFloat(PSea, "Amp2");
	Sea.Sea2.AnimSpeed2 = Whr_GetFloat(PSea, "AnimSpeed2");
	Sea.Sea2.Scale2 = Whr_GetFloat(PSea, "Scale2");
	Sea.Sea2.MoveSpeed2 = Whr_GetString(PSea, "MoveSpeed2");

	Sea.Sea2.BumpScale = Whr_GetFloat(PSea, "BumpScale");
	Sea.Sea2.PosShift = Whr_GetFloat(PSea, "PosShift");
	
	Sea.Sea2.FoamK = Whr_GetFloat(PSea, "FoamK");
	Sea.Sea2.FoamV = Whr_GetFloat(PSea, "FoamV");
	Sea.Sea2.FoamUV = Whr_GetFloat(PSea, "FoamUV");
	Sea.Sea2.FoamTexDisturb = Whr_GetFloat(PSea, "FoamTexDisturb");

	Sea.Sea2.Reflection = Whr_GetFloat(PSea, "Reflection");
	Sea.Sea2.Transparency = Whr_GetFloat(PSea, "Transparency");
	Sea.Sea2.Frenel = Whr_GetFloat(PSea, "Frenel");
	Sea.Sea2.Attenuation = Whr_GetFloat(PSea, "Attenuation");
	Sea.Sea2.WaterColor = Whr_GetColor(PSea, "WaterColor");	

	Sea.Sea2.SkyColor = Whr_GetColor(PSea, "SkyColor");
}
