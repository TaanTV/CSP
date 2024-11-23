
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;






/*
		==Начало в части 3== BS_F3_1 - BS_F3_22
//Скипаем с отравления три дня. ГГ приходит в себя в комнате таверны.
//Запись в СЖ: 'Неожиданно. Но предсказуемо. Флинт поимел нас всех. Кто бы мог подумать. Хорошо, что жив(ва) остался(лась)! Нужно разобраться в происходящем. Дьявол, как же мутит то!'
		case "BS_F2_1":	//Максин
			dialog.text = "Awake? Finally! You've been out the longest.";
			link.l1 = "Is everyone alive? What's new?";
			link.l1.go = "BS_F2_2";
CloseQuestHeader("BSUrka");
SetQuestHeader("BSSevereHangover");
AddQuestRecord("BSSevereHangover", "1");
AddQuestUserData("BSSevereHangover", "sSex", GetSexPhrase("", "a"));
		break;
		==Начало в части 3== BS_F3_1 - BS_F3_22
*/






//ВАРИАНТ 2 - помощь Бонсу, а позже Вейну.
//Если ищем Вейна, то при визите в Ла Вегу – он в Пуэрто-Присипе, если на Кубу, то в Ла Веге.
//Прибыв в один из вариантов – запись в СЖ: ''Рейнджера' на рейде не видно. Расспрошу местных'		 	AddQuestRecord("BSSevereHangover", "41");
		case "BS_F2_23":	//Бармены и мэры Ла Веги/ПуэртоПринсипе
			dialog.text = "No, Captain Wayne hasn't been here for a long time";
			link.l1 = "...";
			link.l1.go = "exit";
		break;

//Плывём на второй вариант.
//Запись в СЖ: ''Рейнджер' на якоре! Шлюпку на воду!'		AddQuestRecord("BSSevereHangover", "42");
		case "BS_F2_24":	//Говорим с вахтенным
			dialog.text = "";
			link.l1 = "Hello, " + GetFullName(NPChar) + ". Where is captain? We have a conversation with him.";
			link.l1.go = "BS_F2_25";
		break;
		case "BS_F2_25":
			dialog.text = "Landed yesterday with a boarding company and went into the jungle. I made a lot of noise in the village, it almost came to a fight, our people are afraid to go ashore";
			link.l1 = "Wayne's Diplomacy. Ha. I understand. I'm on shore, don't get drunk here with mine!";
			link.l1.go = "exit";
		break;

//Высаживаемся на берег, идём в поселение. У главы или бармена диалог
		case "BS_F2_26":	//Бармены и мэры Ла Веги/ПуэртоПринсипе
			dialog.text = "";
			link.l1 = "I heard that Captain Wayne checked in here the other day. What were you brawling about?";
			link.l1.go = "BS_F2_27";
		break;
		case "BS_F2_27":
			dialog.text = "He is a respected and dashing pirate, but too hot. I ruined my property here, smashed a couple of heads and was like that";
			link.l1 = "And where did you go? We have a common business with him and, of course, I am not such a respected pirate, but I also know how to spoil property and heads!";
			link.l1.go = "BS_F2_28";
		break;
		case "BS_F2_28":
			dialog.text = "Far away, into the jungle. There are slave camps of fugitives from all over the archipelago";
			link.l1 = "Has Flint shown up here?";
			link.l1.go = "BS_F2_29";
		break;
		case "BS_F2_29":
			dialog.text = "It's been a long time, I used to go to the jungle a lot";
			link.l1 = "Are there guides who will indicate the camps?";
			link.l1.go = "BS_F2_30";
		break;
		case "BS_F2_30":
			dialog.text = "I was alone, I left with Wayne";
//Запись в СЖ: 'Возможность последовать за Вейном я упустил(), без опытных проводников, соваться в джунгли – самоубийство. Что же, подожду тут'
			AddQuestRecord("BSSevereHangover", "43");
			link.l1 = "Damn. It remains only to wait. Be there";
			link.l1.go = "exit";
		break;

//Снимаем комнату, на второй день в таверну приходят Вейн и чел с моделькой негра, в красной рубахе Коффи.
		case "BS_F2_29":	//Вейн
			dialog.text = "";
			link.l1 = "Hello Charles. I barely found you! Who is that with you?";//Qwerry: Друг? Толерастия!
			link.l1.go = "BS_F2_30";
		break;
		case "BS_F2_30":	//Вейн
			dialog.text = "This is Coffey, someone like the leader of the runaways. And he knows where Flint is.";
			link.l1 = "";
			link.l1.go = "BS_F2_30_1";
		break;
		case "BS_F2_30_1":
			DialogExit();
sld = CharacterFromID("");//TO DO<<<<<<<<!!!!!!!указать имя===================================<<<<<<<<<<<<<<<<<<<<<<<<
			sld.dialog.filename = "Quest\BlackSails\BS_Final_2.c";
			sld.dialog.currentnode   = "BS_F2_31";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_F2_31":	//Коффи
			dialog.text = "Coffey knows. Wayne promised to help. Coffey tells me where Flint is.";
			link.l1 = "";
			link.l1.go = "BS_F2_31_1";
		break;
		case "BS_F2_31_1":
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\BS_Final_2.c";
			sld.dialog.currentnode   = "BS_F2_32";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_F2_32":	//Вейн
			dialog.text = "Flint guy, nothing gets through him. The bottom line is this: Flint promised to ferry the fugitives to the mainland, to the northern colonies. No one there cares who you are or where you come from. Yes, I only partially kept my promise. Those who got on the ship are recruited, and those who are against are immediately overboard. Flint is starting something like a war with the colonial authorities. He's aiming for kings himself. And our loot is the treasury of his kingdom.";
			link.l1 = "Flint is an ambitious man! I can't help but respect him.";
			link.l1.go = "BS_F2_33";
		break;
		case "BS_F2_33":	//Вейн
			dialog.text = "At least kiss him in the hickey! First our money, then Flint's head, then do whatever you want with it!";
			link.l1 = "";
			link.l1.go = "BS_F2_33_1";
		break;
		case "BS_F2_33_1":
			DialogExit();
sld = CharacterFromID("");//TO DO<<<<<<<<!!!!!!!указать имя===================================<<<<<<<<<<<<<<<<<<<<<<<<
			sld.dialog.filename = "Quest\BlackSails\BS_Final_2.c";
			sld.dialog.currentnode   = "BS_F2_34";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_F2_34":	//Коффи
			dialog.text = "Wayne promised to help!";
			link.l1 = "";
			link.l1.go = "BS_F2_34_1";
		break;
		case "BS_F2_34_1":
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\BS_Final_2.c";
			sld.dialog.currentnode   = "BS_F2_35";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_F2_35":	//Вейн
			dialog.text = "The local governor recently decided to brandish his weapon in front of some big shot from the metropolis. The soldiers caught a bunch of fugitives in the jungle and sold them to a plantation. To Barbados. Our friend asks for the release of his subjects, and in return he will surrender Flint's shelter.";
			link.l1 = "The plantation in Barbados is a penal colony of the British Crown, in a gorge, covered by fort cannons and city walls. After the Spanish raid, there is a garrison reinforced with marines and Swedish mercenaries. This is a fucking fortress";//Qwerry: Нужна особая реплика для Блада?
			link.l1.go = "BS_F2_36";
		break;
		case "BS_F2_36":
			dialog.text = "So let's take it by storm!";
			link.l1 = "To do this, you need to prepare... and the squadron... and there are about a thousand people or more, and time is running out. We are moving to Barbados, we have an idea how to turn this case around with a little blood. Join the squadron.";
			link.l1.go = "exit";
			AddQuestRecord("BSSevereHangover", "44");
//Запись в СЖ: 'Флинт строит своё королевство. Вот так новость. Не удивлюсь, если он принц крови, в изгнании или бастард королевский. Информация о его схроне стоит дорого. Но надеюсь дело того стоит. Направляемся на Барбадос. Нужно продумать атаку плантации'
		break;

//Высаживаемся на мысе Гаррисон. На берегу Вейн, куча матросни.
		case "BS_F2_37":	//Вейн
			dialog.text = "";
			link.l1 = "I sent scouts to find out how it is here and what. How to get back – they will take you to the plantation, I heard rumors that there are trails in the mountains. And I'm going to the city to sniff out the situation. My guys will change their clothes more decently and come closer to the plantation through the city gates. When everything is ready, we will strike from both sides at the same time. The signal is a musket salvo.";
			link.l1.go = "BS_F2_38";
		break;
		case "BS_F2_38":	//Вейн
			dialog.text = "And you and Flint are similar. You think the same way. Will you follow the same path?";
			link.l1 = "Does it bother you? We have a case and it needs to be done without mistakes. That's it, I'm in the city, wait for the scouts to return and move out.";
			link.l1.go = "exit";
//Запись в СЖ: 'Я на Флинта похожу? Что за бред. Осмотрюсь в городе, пока мои бойцы проникают за ворота'.
			AddQuestRecord("BSSevereHangover", "45");
		break;

//Проникаем в город. Просто бродим туда-сюда. У выхода из борделя встречаем Сильвера.
		case "BS_F2_39":	//Сильвер
			dialog.text = "";
			link.l1 = "What a surprise! John, it's been a long time! Is Flint here too?";
			link.l1.go = "BS_F2_40";
		break;
		case "BS_F2_40":	//Сильвер
			dialog.text = "I got away from Flint, he started getting rid of the old team, right in the sea. The whole deck was soaked in blood. Barely got away with it! I'm looking for someone to drop me off to the mainland, I need to disappear";
			link.l1 = "Why would Flint want to get rid of you?";
			link.l1.go = "BS_F2_41";
		break;
		case "BS_F2_41":	//Сильвер
			dialog.text = "Ends in water! He achieved his goal, got the gold, and now he's started on the next one.";
			link.l1 = "Are you talking about the free pirate kingdom? I heard about it.";
			link.l1.go = "BS_F2_42";
		break;
		case "BS_F2_42":	//Сильвер
			dialog.text = "Listen, we didn't quarrel and there is no blood between us. Let's split up?";
			link.l1 = "I feel in my gut that you are not telling me something, but there is no time to figure it out. Okay, disappear.";
			link.l1.go = "exit";
			AddQuestRecord("BSSevereHangover", "46");
//Запись в СЖ: 'На улицах Бриджтауна встретил() Джона Сильвера, говорит, что сбежал от Флинта. Подозрительный тип, глазки бегают и напуган явно не мной. Ладно, к дьяволу Сильвера. Пора выдвигаться к плантации'.
		break;
//Сильвер уходит

//Плантация. Кучка англичан – солдат у входа. Человек 15 наших. Четверо с мушкетами.
		case "BS_F2_43":	//ГГ сам себе
			dialog.text = "";
			link.l1 = "Fire on the uniforms! In one gulp, fire!";
			link.l1.go = "exit";
		break;

//Бабах!! Начинается файт. Англичане прут в три волны со стороны плантации. На третьей волне со стороны плантации – Вейн с бригадой. Мясо. Говорим ч Вейном
		case "BS_F2_44":	//Вейн
			dialog.text = "";
			link.l1 = "You're late! We were almost crushed!";
			link.l1.go = "BS_F2_45";
		break;
		case "BS_F2_45":	//Вейн
			dialog.text = "Patrols in the mountains, crawling on their bellies so as not to make a noise ahead of time!";
			link.l1 = "Okay, the job is done, gather the convicts in a bunch, let them pick up their weapons and retreat to the mountains. Do you hear? The devil, the garrison is coming from the city. Ready to fight!";
			link.l1.go = "exit";
		break;

//Со стороны города прут ещё пару волн англичан. Файт
		case "BS_F2_46":	//Qwerry: Вейн? или сразу после боя сам себе?
			dialog.text = "";
			link.l1 = "They fought back, soon uniforms will come from the fort! Run to the mountains!";
			link.l1.go = "exit";
		break;
//Загрузка. Перемещаем ГГ, Вейна, матросов и кучку каторжан на пляж мыса Гаррисон.
		case "BS_F2_47":	//Вейн
			dialog.text = "It's a small matter. We unload the poor devils in La Vega. Coffey will be waiting there.";
			link.l1 = "On all sails! It was not enough to fight with the guards.";
			link.l1.go = "exit";
		break;

//Выходим в море. На глобалке атакует фиолетовая энка. 'Скарборо' линейник 1 ранга и с ним пара фрегатов. Морской бой.
//Если брать на абордаж 'Скарборо' - капитан Френсис Ньюм, моделька офицера английского. Файт в каюте. Диалог
		case "BS_F2_48":	//Ньюм
			dialog.text = "In the name of the king! Surrender!";
			link.l1 = "Ha. You've been boarded, Captain. Surrender yourself! And why the hell did you attack us? We have an agreement with Commander Blackham!";
			link.l1.go = "BS_F2_49";
		break;
		case "BS_F2_49":	//Ньюм
			dialog.text = "Blackham has been demoted and arrested for collaborating with pirates, he is awaiting trial and hanging in Boston.";
			link.l1 = "That's how I knew that all the words about pardons and awards are bullshit! It's time to die!";
			link.l1.go = "exit";
			AddQuestRecord("BSSevereHangover", "47");
//Запись в СЖ: 'Каторжники отбиты. Недалеко от Барбадоса, были атакованы 'Скарборо', капитан Ньюм, перед смертью рассказал о судьбе Билли. Туда и дорога. Путь на Эспаньолу, в Ла Вега ждёт своих соплеменников Кофии'.
		break;

//Берег Ла Веги. Вейн, ГГ, Коффи.
		case "BS_F2_50":	//Коффи
			dialog.text = "";
			link.l1 = "Here are your friends Coffey, we have fulfilled our part of the deal. Where is Flint?";
			link.l1.go = "BS_F2_51";
		break;
		case "BS_F2_51":	//Коффи
			dialog.text = "There is an abandoned house two days away from here. Flint's woman lived there. He often goes there. Coffey will be shown the way.";
			link.l1 = "I'm ready to go now. Wayne?";
			link.l1.go = "BS_F2_51_1";
		break;
		case "BS_F2_51_1":
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\BS_Final_2.c";
			sld.dialog.currentnode   = "BS_F2_52";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_F2_52":	//Вейн
			dialog.text = "Me too";
			link.l1 = "";
			link.l1.go = "BS_F2_52_1";
		break;
		case "BS_F2_52_1":
			DialogExit();
sld = CharacterFromID("");//TO DO<<<<<<<<!!!!!!!указать имя===================================<<<<<<<<<<<<<<<<<<<<<<<<
			sld.dialog.filename = "Quest\BlackSails\BS_Final_2.c";
			sld.dialog.currentnode   = "BS_F2_53";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_F2_53":	//Коффи
			dialog.text = "";
			link.l1 = "You follow in the footsteps. Coffey will show you how.";
			link.l1.go = "BS_F2_54";
		break;

//Загрузка, дом в джунглях. Коффи остаётся у выхода из локи. ГГ с Вейном заходят в дом. В сундуке 2кк денег, книга Марк Аврелий 'Размышления'.
		case "BS_F2_54":	//Вейн
			dialog.text = "The ash is still hot. He was here recently. Shall we set up an ambush?";
			link.l1 = "There is money and an old book in the chest. Will you take your share now?";//Qwerry: Реплика до обыска сундука или после должна быть? Нужен ли вообще обыск сундука?
			link.l1.go = "BS_F2_55";
		break;
		case "BS_F2_55":	//Вейн
			dialog.text = "Later. Let's nail Flint first.";
			link.l1 = "Whatever you say. Let's take a look outside.";
			link.l1.go = "exit";
		break;

//Выходим. На улице труп Коффи, Флинт.
		case "BS_F2_56":	//Флинт
			dialog.text = "You can't foresee everything. Isn't it? And I liked you. Why did they chase me? You won't see any Urca gold anyway. It's safely hidden.";
			link.l1 = "";
			link.l1.go = "BS_F2_56_1";
		break;
		case "BS_F2_56_1":
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\BS_Final_2.c";
			sld.dialog.currentnode   = "BS_F2_57";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_F2_57":	//Вейн
			dialog.text = "So we'll find it, but first I'll get even with you!";
			link.l1 = "";
			link.l1.go = "BS_F2_58";
		break;
//Вейн кидается в атаку – Флинт скриптово стреляет в него. Вейн падает. И атакует ГГ
//Сурьёзный замес. Нулим НР Флинту – он скриптово стреляет, нас корчит, Флинт убегает.

		case "BS_F2_58":	//ГГ себе
			dialog.text = "Damn, the rib is broken! Wayne, how are you, buddy? The wound is serious, he may bleed out.";
			link.l1 = "Stay and bandage Wayne.";
			link.l1.go = "BS_F2_59";
		break;

//Прошло четыре дня. Еле-еле с раненым Вейном доковыляли до кораблей.  Загрузкой с табличкой, повествующей о событиях.
//Запись в СЖ: 'Логово Флинта найдено и сам Флинт тоже. Внушительная сумма денег и старая книга. Мерзавец скрылся. Понятия не имею, что делать дальше. Доставлю Чарльза на Бермуды и обмозгуем с Гатри варианты'.
//			AddQuestRecord("BSSevereHangover", "48");

//Отплываем на Бермуды, выводим 'Рейнджера' из эскадры.
//Бермуды. Резиденция закрыта. Идём в таверну.
		case "BS_F2_59":	//бармен
			dialog.text = "";
			link.l1 = "Hey, where's Miss Guthrie? The residence is closed...";
			link.l1.go = "BS_F2_60";
		break;
		case "BS_F2_60":	//бармен
			dialog.text = "The British military landed here recently. Five hundred people and the Scarborough liner stood up in the bay. They've set up a hell of a thing here. Ms. Guthrie and several other people were arrested. Captain Newm was yelling that justice had overtaken them, and the trial in Port Royal would be quick.";
			link.l1 = "How? I need to hurry. Goodbye.";
			link.l1.go = "BS_F2_61";
			AddQuestRecord("BSSevereHangover", "49");
//Запись в СЖ: 'Гатри арестована Ньюмом! Тем самым, кого я на корм рыбам отправил(ла)! Поспешу в Порт Рояль, может быть Максин чем то поможет. И не слова Вейну, какие у них бы там отношения не были, наделает глупостей. Слишком горяч. В порт заходить не стоит, неизвестно чем всё там обернётся'
		break;

//Высаживаемся в бухте, топаем в город. Сразу в бордель.
		case "BS_F2_61":	//Максин
			dialog.text = "I know why you're here. Recently, Captain Newm staged a whole performance in the city. He led Eleanor and Bones from the port to Fort, in chains. The hero, the winner of the pirates. A pompous turkey.";
			link.l1 = "Dead turkey! I met 'Scarborough' near Barbados and sink it to the bottom! Are the prisoners still here?";
			link.l1.go = "BS_F2_62";
		break;
		case "BS_F2_62":
			dialog.text = "Yes, in the fort. What are you up to? This is suicide! They can't be helped anymore!";
			link.l1 = "Them? I don't care about Bones, he deserves to be hanged. I want to get Eleanor out and get out of here in full sail! Are you with me? The ship is in Portland Bay.";
			link.l1.go = "BS_F2_63";
		break;
		case "BS_F2_63":
			dialog.text = "No, I'm sorry. It took me a long time to achieve what I have now. I've had enough of adventures!";
			link.l1 = "We found Flint's cache, but the bastard ran away, severely injuring Wayne in the process. There's some money here. I am sure that this is the Urca's gold. Here you go, 500 thousand.";
			link.l1.go = "BS_F2_64";
		break;
		case "BS_F2_64":
			AddmoneyToCharacter(PChar, -500000);
			dialog.text = "Can you stop chasing the rest? Be content with what fate sends!";
			link.l1 = "I won't stop at the end of the road!";
			link.l1.go = "BS_F2_65";
		break;
		case "BS_F2_65":
			dialog.text = "Sometimes you need to! You will ruin yourself!";
			link.l1 = "Thanks for your concern, but I decide my destiny. Goodbye Max. Maybe I'll see you again!";
			link.l1.go = "exit";
		break;

//Топаем в форт. В тюрьму. Комендант пропускает без вопросов. В камере – Бонс
		case "BS_F2_66":
			dialog.text = "";	//Бонс
			link.l1 = "Sir William! What a meeting! Have you decided to switch from a luxurious cabin to a simpler apartment?";
			link.l1.go = "BS_F2_67";
		break;
		case "BS_F2_67":
			dialog.text = "Something new. Otherwise, give everyone pirate treasures or just throw rot. By what fates, Captain?";
			link.l1 = "Where is Miss Guthrie?";
			link.l1.go = "BS_F2_68";
		break;
		case "BS_F2_68":
			dialog.text = "Oh, yes. The pirate queen. You are too late, she was sent to England by courier brig at dawn yesterday. They want to hang it in London itself.";
			link.l1 = "...";
			link.l1.go = "BS_F2_69";
		break;
		case "BS_F2_69":
			dialog.text = "No words? I know sometimes everything goes to hell. And you just don't understand what's going on.";
			link.l1 = "How did you end up here? You looked like a brave imperial knight last time!";
			link.l1.go = "BS_F2_70";
		break;
		case "BS_F2_70":
			dialog.text = "Flint is to blame. When I didn't get any news from you, I started searching on my own. And I found something. Parking places of the Walrus. He is even more elusive than Urca. Except, I was presumptuous and went looking alone. And at a certain point he ran into Flint and two more frigates. Obviously not local. The battle was hot, then boarding. He even managed to get into Flint's cabin. In the heat of battle, I got so carried away that I single-handedly made my way there, and there was an ambush. I don't know how I survived. I woke up on the shore.";
			link.l1 = "And then 'Scarborough' picked you up.";
			link.l1.go = "BS_F2_71";
		break;
		case "BS_F2_71":
			dialog.text = "Exactly. Newm was very pleased with himself and decided to pin all his failures on me. You pompous, self-satisfied cretin! Listen, will you do me a favor? Finish him off when you meet him.";
			link.l1 = "Already. What am I going to do with you, Billy? You say you know Flint's parking spots? Will you share it?";
			link.l1.go = "BS_F2_72";
		break;
		case "BS_F2_72":
			dialog.text = "Why would that be?";
			link.l1 = "I killed Newman.";
			link.l1.go = "BS_F2_73";
		break;
		case "BS_F2_73":
			dialog.text = "He would have been stabbed by his own adjutant while shaving. Listen, can you get me out of here? I'll give you Flint.";
			link.l1 = "Trusting you is clearly a mistake. But I just don't have any ideas what to do next. Okay. Step back.";
			link.l1.go = "exit";
		break;
//Скриптово стреляем в замок, Бонс в абордаги, месим стражу, удираем в бухту. Пиздим на берегу с Бонсом.

		case "BS_F2_74":	//Бонс
			dialog.text = "";
			link.l1 = "Flint.";
			link.l1.go = "BS_F2_75";
		break;
		case "BS_F2_75":
			dialog.text = "Chiriqui Lagoon, Boca de la Sierte Bay. I had the pleasure of meeting him at Cape Katoche, so he can be crossed out.";
			link.l1 = "Go to the ship, sit in the hold. Then I'll decide what to do with you!";
			link.l1.go = "BS_F2_76";
		break;
		case "BS_F2_76":
			dialog.text = "That's right, Cap. You look just like Flint, you should train your eyes!";
			link.l1 = "Into the boat!";
			link.l1.go = "exit";
			AddQuestRecord("BSSevereHangover", "50");
			AddQuestUserData("BSSevereHangover", "sSex", GetSexPhrase("", "a"));
//Запись в СЖ: 'Неужели я становлюсь Флинтом? Может плюнуть на всё, по совету Макс и довольствоваться малым? Как я устал(ла)! Нужно проверить стоянки, указанные Бонсом'

			//Вешаем НЗГ от Англии.

		break;

//В Чирике – пусто. Бока де ла Сьрпе – Морж, два фрегата. Месиво, берём Моржа на абордаж – в каюте кэп ОЗГ (наёмник) без диалогов валим пидора. В сундуке СЖ Флинта, зашифрованный, 1кк денег.
//После абордажа запись в СЖ: 'Стоянка найдена, эскадра уничтожена. Флинта на борту Моржа – нет. Высаживаюсь в бухте, нужно проверить здесь всё. В судовом журнале,  какая – то околесица, явно шифр'.
//			AddQuestRecord("BSSevereHangover", "51");
//На берегу файт в следующей локе – файт.
//Запись в СЖ: 'Флинт как сквозь землю провалился. Перебили уйму наёмников. Что дальше? Клад зарыт где то тут? Что делать?'
//			AddQuestRecord("BSSevereHangover", "52");

//Выходим в бухту, на берегу Бонс
		case "BS_F2_77":	//Бонс
			dialog.text = "";
			link.l1 = "Your skills are needed. Are you good at encryption?";
			link.l1.go = "BS_F2_78";
		break;
		case "BS_F2_78":
			dialog.text = "I understand, I often used different ciphers in my service";
			link.l1 = "Here is Flint's logbook, here is a book that has been read to holes. (we pass the items) Move to the forecastle and start decoding. As soon as we arrive in Bermudes, I will need ready answers.";
			link.l1.go = "exit";
		break;

//Выходим в море. Идём на Бермуды. Причалив, сразу ТП в резиденцию. Внутри Вейн, Бонс, ГГ
		case "BS_F2_79":	//Вейн
			dialog.text = "";
			link.l1 = "Charles, I see you're already on your feet!";
			link.l1.go = "BS_F2_80";
		break;
		case "BS_F2_80":
			dialog.text = "It's been worse. What's the news?";
			link.l1 = "Eleanor is being taken to England, there will be a trial and she will most likely be hanged. Flint has disappeared, but we have his logbook and perhaps Mr. Bones will be pleased with its contents. Jack and Bonnie are now a happy family and have given up piracy, at least for a while, until Anne gives birth to little Jack, or Jane. And here's some of Flint's money. Your share.";
			link.l1.go = "BS_F2_81";
		break;
		case "BS_F2_81":
			AddmoneyToCharacter(PChar, -750000);
			dialog.text = "The hell I'm going to let her hang up. I'll strangle her myself, someday!";
			link.l1 = "Are you determined? I need a companion like you, Charles!";
			link.l1.go = "BS_F2_82";
		break;
		case "BS_F2_82":
			dialog.text = "It couldn't be harder. In another scenario, I might have agreed. But you've become too much like Flint! Give my regards to the Wrexham family. Goodbye!";
			link.l1 = "";
			link.l1.go = "BS_F2_83";
		break;
//Вейн уходит

		case "BS_F2_83":	//Бонс
			dialog.text = "I have deciphered the logbook. Take a look (passes several pages filled with coordinates). Nothing else.";
			link.l1 = "(runs through the pages) Keep it for yourself. Flint won. To hell with it all!";
			link.l1.go = "BS_F2_84";
		break;
		case "BS_F2_84":
			dialog.text = "Stop. Yes, there are a lot of coordinates, a hell of a lot, but by way of elimination... Having a fast ship... Hey, are you listening?";
			link.l1 = "Shut up, Billy, just shut up.";
			link.l1.go = "exit";
		break;
//Релоад на улицу
//Запись в СЖ: 'Кто такой, этот Флинт? Может сам дьявол? Как я стал(ла) превращаться в него? Бескомпромиссного, жестокого, расчётливого ублюдка! Погоня за его золотом, отобрала часть меня самого(самой). Мудрая шлюха Максин, ты была права. Нужно довольствоваться, тем, что имеешь и не гоняться за чужим, иначе, рискуешь потерять и то, что имеешь'
//			AddQuestRecord("BSSevereHangover", "53");
//			AddQuestUserData("BSSevereHangover", "sSex", GetSexPhrase("", "a"));
//			CloseQuestHeader("BSSevereHangover");
//Квест уходит в архив. Макс остаётся в ПР бригадиром шлюх (бесплатный перепихон). THE END
	}
}
