// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы, "+ GetSexPhrase("молодой человек","юная леди") +"?", "Чего ты хочешь, "+ GetSexPhrase("красавчик","красотка") +"? Ну хоть задай его."), "Опять вопросы?", "Хи-хи, третий раз на дню одно и то же - вопросы...",
                          ""+ GetSexPhrase("Хм, может ты выберешь какую-нибудь красотку себе? А то у меня уже складывается в отношении тебя вполне определённое мнение...","Хм, может ты выберешь какую-нибудь красотку себе? Мальчиков не держим, хи-хи...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+GetSexPhrase("","а")+"...", "Хм, да ничего..."), "Не могу... Нет вопросов...",
                      "Да уж, действительно в третий раз... Извини.", "Не сейчас... В другой раз...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Анжелика Тич: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.AT_PZD_Bordel"))
			{
				DeleteAttribute(pchar, "questTemp.AT_PZD_Bordel")
				link.l1 = "Я к вам с несколько необычным предложением. Не могли бы вы мне продать самое лучшее платье из вашего гардероба?";
				link.l1.go = "AT_PZD_Bordel_1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.AT_PZD_Bordel_2"))
			{
				DeleteAttribute(pchar, "questTemp.AT_PZD_Bordel_2")
				link.l1 = "Я снова по поводу платья.";
				link.l1.go = "AT_PZD_Bordel_6";
				break;
			}
			// <== Анжелика Тич: Портниха знатной дамы
			if (pchar.questTemp.Sharp == "seekSharp" && GetNpcQuestPastDayWOInit(npchar, "quest.SharpTime") > 7 && !LAi_IsDead(&characters[GetCharacterIndex("Sharp")]))
			{
				link.l1 = "Послушай, " + npchar.name + ", я ищу Шарпа. Ты не знаешь, где он?";
				link.l1.go = "SharpPearl_1";
				SaveCurrentNpcQuestDateParam(npchar, "quest.SharpTime");
			}
		break;
		
		//============ Анжелика Тич: Портниха знатной дамы
		case "AT_PZD_Bordel_1":
    		dialog.text = "Действительно необычное. Боюсь, такая услуга обойдётся вам в целое состояние.";
    		link.l1 = "Может быть его можно арендовать на вечер-другой?";
    		link.l1.go = "AT_PZD_Bordel_2";
 		break;
		case "AT_PZD_Bordel_2":
    		dialog.text = "Пожалуй, это можно устроить. Скажем 15000 пиастров и гарантия того, что оно будет возвращено вовремя, в целости и сохранности.";
			link.l1 = "Без единого пятнышка... И раз уж мы сошлись в цене, может быть у вас отыщется ещё и подходящая карнавальная маска, такая, чтоб закрывала лицо целиком?";
    		link.l1.go = "AT_PZD_Bordel_3";
 		break;
		case "AT_PZD_Bordel_3":
    		dialog.text = "Что-нибудь подберём. Пятьдесят тысяч и она ваша.";
			link.l1 = "Что?! Вы случайно не промахнулись с ценой?";
    		link.l1.go = "AT_PZD_Bordel_4";
 		break;
		case "AT_PZD_Bordel_4":
    		dialog.text = "Уверенна, между нами просто произошло некоторое недопонимание. Вероятно, по ошибке вы приняли меня за глупую женщину, не способную понять намерений инкогнито проникнуть в местную резиденцию. Пятьдесят тысяч за моё молчание, в пятнадцать обойдётся вам платье на вечер и маску получите от меня в подарок. Так как?";
			if (sti(pchar.Money) >= 65000)
			{
				link.l1 = "А вы умеете вести дела. Кажется, у меня нет выхода. Вот ваши деньги. Надеюсь, фасон меня не разочарует.";
				link.l1.go = "AT_PZD_Bordel_5";
			}
			link.l2 = "Что же, я подумаю и возможно зайду позже.";
    		link.l2.go = "AT_PZD_Bordel_4_1";
 		break;
		case "AT_PZD_Bordel_4_1":
    		DialogExit();
			pchar.questTemp.AT_PZD_Bordel_2 = true;
 		break;
		case "AT_PZD_Bordel_6":
    		dialog.text = "Так как, наша сделка состоится? (65000)";
			if (sti(pchar.Money) >= 65000)
			{
				link.l1 = "Вот ваши деньги. Надеюсь, фасон меня не разочарует.";
				link.l1.go = "AT_PZD_Bordel_5";
			}
			link.l2 = "Я ещё обдумываю, стоит ли того ваше предложение.";
    		link.l2.go = "AT_PZD_Bordel_4_1";
 		break;		
		case "AT_PZD_Bordel_5":
			LAi_Fade("", "");
			Log_info("Вы надели карнавальный костюм");
			pchar.Cirgnore = true; //атрибут, блокирующий смену модели кирасной логикой
			bDisableOfficers = true;
			AddMoneyToCharacter(pchar, -65000);
			//PlaySound("Interface\important_item.wav");
			GiveItem2Character(PChar, "AT_PZD_KarnavalKostum");
    		dialog.text = "Ещё немного подвязать вот здесь и я буду практически довольна результатом. Очень жаль, Анжелика, что ты не носила в юности корсет, оно бы сидело значительно лучше. Талия всё ещё выдаёт простолюдинку.";
			link.l1 = "Солдаты на это внимания не обратят, а дальше я справлюсь.";
    		link.l1.go = "AT_PZD_Bordel_8";
 		break;
		case "AT_PZD_Bordel_8":
    		dialog.text = "Нет, всё же не дурно, не дурно. Пожалуй, я даже передумала, можешь не возвращать мне наряд, считай, ты его купила.";
			link.l1 = "Такая сделка мне нравится намного больше. Отказываться не стану. Всё, мне надо спешить, а то опоздаю!";
    		link.l1.go = "AT_PZD_Bordel_9";
 		break;
		case "AT_PZD_Bordel_9":
    		DialogExit();
			
			SetCurrentTime(22, 1);
			DoQuestReloadToLocation("Marigo_town", "goto", "goto19", "AT_PZD_IdemNaKarnaval");
 		break;
		
		// капитан Шарп, грабёж жемчужных промыслов
		case "SharpPearl_1":
			if (drand(1) || bBettaTestMode)
			{
				if (sti(pchar.questTemp.Sharp.brothelChance) < 9)
				{	//футболим геймера в город
					pchar.questTemp.Sharp.City = GetSharpCity();
					pchar.questTemp.Sharp.City.rumour = true; //флаг дачи слуха
					dialog.text = "Насколько мне известно, капитан Шарп отправился в " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + ".";
					link.l1 = "Хех! Благодарю тебя, " + npchar.name + ". Ты мне здорово помогла!";
					link.l1.go = "exit";
					pchar.questTemp.Sharp = "toSharp_going"; //в бордели больше не заходить
					pchar.questTemp.Sharp.count = 0; //счетчик нулим для след. раза
					pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
					pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
					ReOpenQuestHeader("SharpPearl");
					AddQuestRecord("SharpPearl", "1");
					AddQuestUserData("SharpPearl", "sCity", XI_ConvertString("Colony" + npchar.city + "Voc"));
					AddQuestUserData("SharpPearl", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
					if (GetIslandByCityName(pchar.questTemp.Sharp.City) != pchar.questTemp.Sharp.City)
					{
						AddQuestUserData("SharpPearl", "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(pchar.questTemp.Sharp.City) + "Voc"));
					}
					//запускаем энкаунтер Шарпа на карте
					group_DeleteGroup("Sharp_Group");
					sld = characterFromId("Sharp");
					string sGroup = "Sharp_Group";
					Group_FindOrCreateGroup(sGroup);
					Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
					Group_LockTask(sGroup);
					Group_AddCharacter(sGroup, sld.id);
					Group_SetGroupCommander(sGroup, sld.id);
					sld.mapEnc.type = "trade";
					sld.mapEnc.worldMapShip = "quest_ship";
					sld.mapEnc.Name = "бриг 'Шарпоносец'";
					string sColony= SelectAnyColony(npchar.city); //колония, откуда плывёт Шарп
					int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sColony), GetArealByCityName(pchar.questTemp.Sharp.City)) + 1; //дней доехать даём с запасом
					Map_CreateTrader(sColony, pchar.questTemp.Sharp.City, sld.id, daysQty);
					Log_TestInfo("Шарпоносец установлен из " + sColony + "  в " + pchar.questTemp.Sharp.City);
				}
				else
				{	//чудо, Шарп здесь, в борделе!
					dialog.text = "Знаю. Он у меня в заведении отдыхает. Могу позвать, если он тебе срочно нужен.";
					link.l1 = "Сделай, одолжение, " + npchar.name + "...";
					link.l1.go = "SharpPearl_2";
				}
			}
			else
			{
				dialog.text = "Не знаю, у меня его давно уже не было.";
				link.l1 = "Понятно... Ну что же, спасибо тебе, " + npchar.name + ".";
				link.l1.go = "exit";
			}
		break;
		case "SharpPearl_2":
			dialog.text = "Барталомью-ю-ша! Зайди ко мне, дорогой, тебя тут спрашивают!";
			link.l1 = "Хех, а Шарп у вас в почёте, как я погляжу...";
			link.l1.go = "SharpPearl_3";
		break;
		case "SharpPearl_3":
			chrDisableReloadToLocation = true;
			pchar.questTemp.Sharp.count = 0; //счётчик нулим для след. раза
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
			pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
			sld = &characters[GetCharacterIndex("Sharp")];
			sld.dialog.currentnode = "BrothelSharp";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

