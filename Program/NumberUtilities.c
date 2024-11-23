// Warship. Методы для работы с числами
// Большую часть попереносил из других файлов, чтобы все в одном месте было

#define PI 3.14159265
#define PIm2 6.28318530
#define PId2 1.57079632

float FRAND(float _x)
{
	return rand(32768) / 32768.0 * _x;
}

// boal
float frandSmall(float _x)
{
	return rand(32) / 32.0 * _x;
}

// Warship 30.07.09. -->
// Рандом 0.0 ... 1.0
float Random()
{
	return rand(32768) / 32768.0; // 65536
}

/*	Псевдорандом на одну цифру. Работает так:
	Первое cгенерированное число записывается в переменную игрока и при последующих активациях метод проверяет если переменная аналогична генерирующемуся числу,
	то рандом генерит его заново до тех пор, пока оно не будет отличаться от записанной переменной. При окончании цикла записывает новое сгенеренное число в переменную игрока.*/
int prand(int _max)
{
	if (!CheckAttribute(pchar,"prandvalue")) pchar.prandvalue = 0;
	int value = rand(_max); //генерация числа по диапазону
	while (value == sti(pchar.prandvalue)) //проверочный цикл по совпадению/несовпадению с записанным ранее значением в переменной игрока
	{
		value = rand(_max);
	}
	pchar.prandvalue = value; //запись в переменную игрока сгенерированного числа для последующей проверки
	return value;
}

// Коммент - не нравится мне cRand() - он возвращает не псевдослучайное число,
// а зависящее от конкретного дня месяца, да ещё и подряд может быть несколько
// одинаковых числе, например, cRand(5) будет давать 5 дней подряд одно и тоже.
// Функция ниже вернёт псевдослучайное число, потом запоминает его в PChar и пока не наступит
// новый день будет возвращать его-же. PChar.dayRandom устанавливается в первом шаге обновления дня
int dRand(int _max)
{
	float dayRandom;

	if(CheckAttribute(PChar, "dayRandom"))
	{
		dayRandom = stf(PChar.dayRandom);
		// Log_Info(""+dayRandom);
		// Log_Info(""+MakeInt(dayRandom * (_max+1)));
		return MakeInt(dayRandom * (_max+1)); // 1.0 / (_max + 1) - для округления, иначе _max не выпадет никогда
	}

	dayRandom = Random();
	PChar.dayRandom = dayRandom;

	return MakeInt(dayRandom * (_max+1));
}

int dRand1(int _max1)
{
	float dayRandom1;

	if(CheckAttribute(PChar, "dayRandom1"))
	{
		dayRandom1 = stf(PChar.dayRandom1);
		// Log_Info(""+dayRandom1);
		// Log_Info(""+MakeInt(dayRandom1 * (_max1+1)));
		return MakeInt(dayRandom1 * (_max1+1)); // 1.0 / (_max + 1) - для округления, иначе _max не выпадет никогда
	}

	dayRandom1 = Random();
	PChar.dayRandom1 = dayRandom1;

	return MakeInt(dayRandom1 * (_max1+1));
}

int dRand2(int _max2)
{
	float dayRandom2;

	if(CheckAttribute(PChar, "dayRandom2"))
	{
		dayRandom2 = stf(PChar.dayRandom2);
		// Log_Info(""+dayRandom2);
		// Log_Info(""+MakeInt(dayRandom2 * (_max2+1)));
		return MakeInt(dayRandom2 * (_max2+1)); // 1.0 / (_max + 1) - для округления, иначе _max не выпадет никогда
	}

	dayRandom2 = Random();
	PChar.dayRandom2 = dayRandom2;

	return MakeInt(dayRandom2 * (_max2+1));
}

int dRand3(int _max3)
{
	float dayRandom3;

	if(CheckAttribute(PChar, "dayRandom3"))
	{
		dayRandom3 = stf(PChar.dayRandom3);
		// Log_Info(""+dayRandom3);
		// Log_Info(""+MakeInt(dayRandom3 * (_max3+1)));
		return MakeInt(dayRandom3 * (_max3+1)); // 1.0 / (_max + 1) - для округления, иначе _max не выпадет никогда
	}

	dayRandom3 = Random();
	PChar.dayRandom3 = dayRandom3;

	return MakeInt(dayRandom3 * (_max3+1));
}
// <-- Warship 30.07.09

// cRand() - античитовый рандом Эдди. Юзать не рекомендуется, за место него - dRand()
//античитовый рендом
int cRand(int num)
{
	if (num < 1) return 0;
	if (num > 30) return rand(num);
	int sResult = num;
	int iData = GetDataDay();

	int iDel = 30.0 / (num + 1) + 0.5; //делитель месяца
	int step = iDel; //шаг увеличения уровня сравнения в месяце

	for (i=0; i<num; i++)
	{
		if (iData < iDel)
		{
			sResult = i;
			break;
		}
		else iDel += step;
	}
	return sResult;
}

// Радианы в градусы
float Radian2Degree(float _rad)
{
	return 180 / PI * _rad;
}

int func_max(int a, int b)
{
	if (a > b) return a;
	return b;
}

int func_min(int a, int b)
{
	if (a > b) return b;
	return a;
}
//генерирует псевдорандомные значения, имеющие устойчивое распределение случайной величины и мат ожидание probability.
//отличается меньшей дисперсией, что позволяет уменьшить эффекты чрезмерной удачи\неудачи(срабатывание\несрабатывание n-раз подряд)
//0 < probability < 1
bool pnrand(ref chr, float probability, string type) 
{
	if(!CheckAttribute(chr, "prc." + type) || stf(chr.prc.(type).probability) != probability) 
	{
		chr.prc.(type) = 0;
		chr.prc.(type).probability = probability;
		chr.prc.(type).cMod = getCMod(probability / 100.0);
	}
	chr.prc.(type) = sti(chr.prc.(type)) + 1; 
	int correctedProb = makeint(stf(chr.prc.(type).cMod) * 10000 * sti(chr.prc.(type)));
	if(rand(10000) <= correctedProb) 
	{
		chr.prc.(type) = 0;
		return true;
	}
	else return false;
}

float getCMod(float probability)
{
	float upBound = probability;
	float lowBound = 0.0;
	float p2 = 1.0;
	float p1, C;
	while(true)
	{
		C = (upBound + lowBound) / 2.0;
		p1 = getP(C);
		if(abs(p1 - p2) <= 0.0001) break;
		if(p1 > probability) upBound = C;
		else lowBound = C;
		p2 = p1;
	}
	return C;
}

float getP(float CMod)
{
	float Temp;
	float pProcOnN = 0;
	float pProcByN = 0;
	float sumNpProcOnN = 0;
	int n = ceil(1.0 / CMod);
	for(int i = 1; i <= n; i++)
	{
		Temp = i * CMod;
		if(1.0 < Temp) Temp = 1.0;
		pProcOnN = Temp * (1.0 - pProcByN);
		pProcByN = pProcByN + pProcOnN;
		sumNpProcOnN = sumNpProcOnN + i * pProcOnN;
	}
	return 1.0 / sumNpProcOnN;
}
//в движке ceil есть но не пробросан в скрипты -_-
int ceil(float a)
{
	if(abs(a) - makeint(abs(a)) != 0)
	{
		if(a >= 0) return makeint(a) + 1;
		else return makeint(a);
	}
	else return makeint(a);
}

int round_up(float x) // evganat - округление вверх
{
	if (makefloat(makeint(x)) == x)
	{
		return makeint(x);
	}
	if (x > 0)
	{
		return makeint(x+1.0);
	}
	return makeint(x-1.0);
}

int round_near(float x) // evganat - округление до ближайшего
{
	if (makefloat(makeint(x)) == x)
	{
		return makeint(x);
	}
	if (abs(x) - makefloat(makeint(abs(x))) >= 0.5)
	{
		return round_up(x);
	}
	return makeint(x);
}