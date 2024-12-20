// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Все сплетни города "+ GetCityName(npchar.city) +" к вашим услугам. Что бы вы хотели узнать?",
                          "Мы только что поднимали это тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Что ты "+ GetSexPhrase("заладил","заладила") +" как попугай одно и то же...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Да уж...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				dialog.text = "Задавайте свои вопросы, "+ GetSexPhrase("сеньор","сеньорита") +".";
				link.l1 = "Я "+ GetSexPhrase("слышал","слышала") +", недавно вы сумели захватить Рока Бразильца, того самого пирата!";
				link.l1.go = "Step_F7_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PK_IshemKoltso"))	// Квест "Потерянное кольцо"
            {
                link.l1 = "Я разыскиваю кольцо, которое принадлежало... одному из моих знакомых. Довольно ценное кольцо. И это кольцо находится где-то в этом городе. Быть может, ты что-то слышал о нём? Большой сапфир, в золотой оправе.";
                link.l1.go = "IshemKoltso";
            }
			if(PChar.MysteriousIsland == "10" && PChar.MysteriousIsland.FindForser.Tavern == false && NPChar.City == "SantoDomingo")	//Квест "Загадочный остров"
			{
				link.l1 = "Не заявлялся ли к вам некий Дэви Форсер?";
				link.l1.go = "MysteriousIsland_2";
			}
		break;
//******************** Фр.линейка, квест №7. Спасение Рока Бразильца ******************
 	 	case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat("Да, верно, было дело. Неслыханная удача, скажу я вам, "+ GetSexPhrase("сеньор","сеньорита") +".", "Вы уже спрашивали меня о Бразильце.",
				          "Опять о Бразильце?", "Ну сколько можно об этих пиратах, давайте о другом поговорим...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Что верно - то верно... И что с ним сделали? Небось удавили тут же.", ""+ GetSexPhrase("Спрашивал","Спрашивала") +"? Ну да, наверное...", "Да, точно, "+ GetSexPhrase("спрашивал","спрашивала") +", извини...", "Можно и о другом...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_F7_2":
			dialog.text = "Что вы, "+ GetSexPhrase("сеньор","сеньорита") +". Привезли и показали всем желающим. А потом уже отдали святым отцам...";
			link.l1 = "А святым отцам-то он зачем?";
			link.l1.go = "Step_F7_3";
        break;
 	 	case "Step_F7_3":
			dialog.text = "Хех, "+ GetSexPhrase("сеньор","сеньорита") +", это же не исповедники. Те святые отцы - воинствующие монахи! Инквизиция...";
			link.l1 = "У-у-у, дело ясное. Ну что же, спасибо тебе, друг.";
			link.l1.go = "exit";
        break;
//******************** Квест "Потерянное кольцо" ******************
		case "IshemKoltso":
			dialog.text = "Хммм... Вы говорите - сапфир? Да, я помню, что видел кольцо, вроде того, о котором вы говорите. Оно у одной девки - может быть, вы даже знаете её - по крайней мере, большинству моряков она неплохо знакома, хе-хе. Её зовут Франческа. Я ещё никогда не встречал девчонки тупее, если честно. Какой-то солдат подарил ей это кольцо пару лет назад. Быть может он был ещё более глуп, чем она - поскольку это кольцо стоит неплохих денег. Да, это наверное то кольцо, которое вы ищете\nНу так что - желаете устроить соревнование с вашими офицерами, кто больше всех выпьет?";
			link.l1 = "Отличная мысль! Я, пожалуй, приведу команду. Жди меня здесь, никуда не уходи - я скоро вернусь.";
			link.l1.go = "IshemKoltso_2";
        break;
		
		case "IshemKoltso_2":
			DialogExit();
			
			AddQuestRecord("PDM_Poteryanoe_Koltso", "3");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("","а"));
			DeleteAttribute(pchar, "questTemp.PDM_PK_IshemKoltso");

			sld = GetCharacter(NPC_GenerateCharacter("PDM_PK_Francheska", "BaynesDaughterSTOK", "woman", "woman", 10, SPAIN, -1, false));
			sld.name = "Франческа";
			sld.lastname = "";
			sld.city = "SantoDomingo";
			sld.location	= "SantoDomingo_Brothel";
			sld.location.group = "goto";
			sld.location.locator = "goto3";
			sld.dialog.filename   = "Quest\PDM\Poteryanoe_Koltso.c";
			sld.dialog.currentnode   = "Francheska";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			LAi_SetImmortal(sld, true);
        break;
		
		// Загадочный остров -->
		case "MysteriousIsland_2":
			PChar.MysteriousIsland.FindForser.Tavern = true;
			dialog.text = "Дэви Форсер?.. Никогда о таком не слышал.";
			link.l1 = LinkRandPhrase("Эх, жаль...", "Спасибо и на том.", "До скорых встреч.");
			link.l1.go = "exit";
		break;
		// Загадочный Остров <--
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

