
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//Скипаем с отравления три дня. ГГ приходит в себя в комнате таверны. Запись в СЖ: «Неожиданно. Но предсказуемо. Флинт поимел нас всех. Кто бы мог подумать. Хорошо, что жив(ва) остался(лась)! Нужно разобраться в происходящем. Дьявол, как же мутит то!»

		//Далее, Вейна нет на Багамах. Спускаемся в таверну. Подходит Макс

		case "BS_F3_1":	//Максин
			LAi_SetActorType(npchar);
			dialog.text = "You're finally awake, you've been out the longest.";
			link.l1 = "Is everyone alive? What's new?";
			link.l1.go = "BS_F3_2";
		break;

		case "BS_F3_2": //Максин
			dialog.text = "Everybody's alive, he put belladonna in the wine. Inez gave us all a drink of charcoal and God knows what else. Puked all over the place, but we survived.";
			link.l1 = "I'll be sure to thank her somehow. So what's the news? Flint? Gold?";
			link.l1.go = "BS_F3_3";
		break;

		case "BS_F3_3":	//Максин
			dialog.text = "No Flint, no gold. There's only one chest of doubloons in the warehouse, about fifty thousand each. And a note. 'Sorry, divide this up and forget about 'Urka' and Flint. It's the right thing to do. You wouldn't understand anyway. Ф.'";
			link.l1 = "Fucking prude! And I almost believed in his 'friendship'. Where are the others?";
			link.l1.go = "BS_F3_4";
			AddMoneyToCharacter(PChar, 50000);
		break;

		case "BS_F3_4":	//Максин
			dialog.text = "Eleanor's at her place, with Rackham and Bonnie, all three of them mad as hell. Always hitting things and yelling at each other. Vane, as soon as he was on his feet, hoisted the sails and went off somewhere.";
			link.l1 = "I think it's best to stay out of the residence for now. I'm gonna go get some air.";
			link.l1.go = "BS_F1_9exit";
		break;
		
		case "BS_F1_9exit":	//Максин
			DialogExit();
			PChar.quest.BS_SentJonsTavernAgentDialugue.win_condition.l1 = "location";
			PChar.quest.BS_SentJonsTavernAgentDialugue.win_condition.l1.location = "SentJons_tavern";
			PChar.quest.BS_SentJonsTavernAgentDialugue.function = "BS_SentJonsTavernAgentDialugue";
			pchar.BSLookingForAgentDialugue = true;
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddQuestRecord("BSHangover", "21");
		break;

		//Запись в СЖ: «Трудно думать, когда тебя постоянно тошнит. Но нужно что-то делать. Попробую подключить разведку. Какой там пароль? На Антигуа! В путь».

		//В таверну Сен Джонса посадить непися, который отзовётся на пароль

		//На Антигуа, идём в таверну и начинаем донимать нпс паролем «Рыбалка удалась». Ответы в духе: «Пойди проспись!», «Закусывать надо!», «Что? О чем вы?».

		//Нужный непись:

		case "BS_F3_5":	//Агент
			dialog.text = RandPhraseSimple(RandPhraseSimple("Don't block my light, you can't see the flies in my mug!", "What do you want?"), RandPhraseSimple("I won't let you have a hangover, I won't get sober!", "Do you have anything to drink?"));
			link.l1 = "The fishing was good.";
			link.l1.go = "BS_F3_6";
		break;

		case "BS_F3_6":	//Агент
			dialog.text = "The catch was a ...?";
			link.l1 = "No catch, the salmon got away, or the eel. Tuna? To hell with your games! We're talking!";
			link.l1.go = "BS_F3_7";
		break;

		case "BS_F3_7":	//Агент
			dialog.text = "Ahem. Well, uh. I'm listening.";
			link.l1 = "Arrange for me to meet with your superiors. It's urgent. The fish could slip out of my hands, if you know what I mean!";
			link.l1.go = "BS_F3_8";
		break;

		case "BS_F3_8":	//Агент
			dialog.text = "I don't have that authority, but I'll pass on the information. How do I get in touch with you?";
			link.l1 = "I'll be stopping by this tavern from time to time.";
			link.l1.go = "BS_F3_9";
		break;

		case "BS_F3_9":	//Агент
			npchar.location = "none";
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(PChar, "BSLookingForAgentDialugue");
			AddQuestRecord("BSHangover", "22");
			pchar.quest.BS_AfterAgentMeeting.win_condition.l1          = "location";
			pchar.quest.BS_AfterAgentMeeting.win_condition.l1.location = "Nassau_OfisGatri";
			pchar.quest.BS_AfterAgentMeeting.function             = "BS_AfterAgentMeeting";
			LocatorReloadEnterDisable("Nassau_town", "houseS1", false);
			dialog.text = "Fine, if you don't catch me there, see the serving lady.";
			link.l1 = "Okay, but tell him time is of the essence. All the best!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Весточку отправил(ла). Нужно вернуться на Багамы и поискать Вейна. Как бы он дров не наломал".
		//Плывём на Багамы. В резиденции Гатри, Бонни, Рекхэм.


		case "BS_F3_10":	//Гатри начинает диалог.
			dialog.text = "Did you find Wayne?";
			link.l1 = "No. Any idea where he went?";
			link.l1.go = "BS_F3_10_1";
		break;
		
		case "BS_F3_10_1":
			StartInstantDialogNoType("BS_Rakham", "BS_F3_11", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_11":	//Рэкхэм.
			dialog.text = "Said he'd shake the soul out of the black creatures, gave me a black eye and was gone.";
			link.l1 = "Obrasin? It's getting more and more interesting!";
			link.l1.go = "BS_F3_11_1";
		break;
		
		case "BS_F3_11_1":
			StartInstantDialogNoType("BS_Bony", "BS_F3_12", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_12":	//Бонни.
			dialog.text = "Flint was doing some business with runaway slaves. Maybe they have him now.";
			link.l1 = "Is there anyone here that he doesn't have connections and business with?";
			link.l1.go = "BS_F3_12_1";
		break;
		
		case "BS_F3_12_1":
			StartInstantDialog("gatri_temp", "BS_F3_13", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_13":	//Гатри.
			dialog.text = "He filled their heads with the idea of a free state in the New World. Equal rights, no lords, peace and happiness. In reality, he's using them as cannon fodder\n Did I mention that Flint is a cruel and rational man? He's an idealist, and anyone who believes his fiery speeches will become a tool, nothing more.";
			link.l1 = "(Private speech) I don't think they need to know about my pact with Bones yet. (Addressing everyone) Jack, Ann. You stayed ashore? I'm offering you a place on my team. We'll find Charles, deal with the slaves, look for Flint's tracks at their hideouts.";
			link.l1.go = "BS_F3_13_1";
		break;
		
		case "BS_F3_13_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialogNoType("BS_Rakham", "BS_F3_14", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_14":	//Рэкхэм.
			dialog.text = "We'd love to, but Ann's pregnant. I bought an old schooner for next to nothing. Anyway, we've decided to take a break from the business for a while. We're gonna stay in Charlestown with Ann's father. I'm gonna do some coastal shipping and a few other odd jobs.";
			link.l1 = "Here, here's a little bit. For the young family, so to speak. Ahem. And don't you dare say no! Well, then. Good luck to you three. Don't let us out of your sight."; //отдаём 35к 7.04.2023
			link.l1.go = "BS_F3_14_1";
		break;
		
		case "BS_F3_14_1":
			AddMoneyToCharacter(PChar, -35000);
			StartInstantDialog("gatri_temp", "BS_F3_15", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_15":	//Гатри.
			dialog.text = "A noble gesture! But to the point. The slaves are runaways, hiding in the jungle, being fed by buccaneers. Which means we're looking for them in Cuba or Española. But what do you want with Vane? Pirate brotherhood? I'd be looking at the Dutch West India Company.";
			link.l1 = "Wayne and I have unfinished business. No sentimentality. What does this have to do with Dutch peddlers?";
			link.l1.go = "BS_F3_16";
		break;

		case "BS_F3_16":	//Гатри.
			dialog.text = "Flint has a recognizable ship and several tons of Spanish gold. It would be logical to split the cargo into pieces and send it by merchant galleons under military guard anywhere. To the Carolinas, for instance, or even Boston. I wouldn't be surprised if my dearest daddy was in on it.";
			link.l1 = "It's worth checking that out, too. Thank you. Anything else?";
			link.l1.go = "BS_F3_17";
		break;

		case "BS_F3_17":	//Гатри.
			SetFunctionLocationCondition("BS_AfterAgentMeetingExit", "Nassau_tavern", false);
			LocatorReloadEnterDisable("Nassau_town", "houseS1", true);
			AddQuestRecord("BSHangover", "23");
			Lai_SetActorTypeNoGroup(npchar);
			dialog.text = "Maxine. Get her out of here. If I have to, I'll do it by force!";
			link.l1 = "Is that it? All right, then. I'll do a search. I have no idea which direction. Too many inputs. I'll see you later.";
			link.l1.go = "BS_F3_17exit";
		break;

		//Запись в СЖ: "Возможное участие отца Элеоноры? Вест-Индская торговая компания? Джек и Энн – благочестивые плантаторы? Беглые рабы и ссора Элеоноры с Макс. Ах да, ещё британская военная разведка. Не хватает только мстительных испанцев, проклятого сокровища и древнего бога местных дикарей! Ну, начнём с простого. Макс. Проверю таверну"
		//Идём в таверну. Говорим с Макс.
		
		case "BS_F3_17exit":	//Гатри.
			DialogExit();
			sld = CharacterFromID("BS_Rakham");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("BS_Bony");
			LAi_CharacterDisableDialog(sld);
			LAi_SetPlayerType(PChar);
			ChangeCharacterAddressGroup(PChar, "Nassau_OfisGatri", "goto", "goto5");
		break;
		
		case "BS_F3_18":	//Максин.
			dialog.text = "She's demanding I get off her island! After everything we've been through! I am...";
			link.l1 = "Shh. I don't want to know what happened. I'm going after our money, and I'm gonna need your information-gathering talents. So, aboard! No arguments!";
			link.l1.go = "BS_F3_18_exit";
		break;
		
		case "BS_F3_18_exit":	//Максин.
			DialogExit();
			AddQuestRecord("BSHangover", "24");
			Lai_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			SetFunctionLocationCondition("BS_HangoverMaksPortRoyalArriving", "PortRoyal_town", false);
		break;

		//Макс в пассажиры. Выходим в море.
		//Запись в СЖ: "Доставлю Максин в Порт Рояль, пусть собирает слухи. А после решу, что делать дальше"
		//Отвозим Макс в ПР. Диалог на причале.

		case "BS_F3_19":	//Максин. Вариант с отказом от секаса.
			SetFunctionLocationCondition("BS_HangoverToAntigua", "Antigua", false);
			dialog.text = "You know, we've been through so much together and we've never gotten to know each other. Why don't we set aside tonight and spend it over a nice bottle of wine?";
			link.l1 = "I'm going to get wine all over my throat, if you know what I mean. Business first, fun later! No offense.";
			link.l1.go = "BS_F3_20";
			link.l2 = "That's a tempting offer! But wine makes me sick, if you know what I mean. How about rum.";
			link.l2.go = "BS_F3_21";
		break;

		case "BS_F3_20":	//Максин.
			dialog.text = "No hard feelings. Goodbye, Captain!";
			link.l1 = "(Private speech) Or maybe...? No! Time is of the essence!";
			link.l1.go = "BS_F3_20exit";
		break;
		
		case "BS_F3_20exit":	//Максин.
			DialogExit();
			chrDisableReloadToLocation = false;
			BS_ReplaceHostessWithMaks();
			LAi_ActorGoToLocation(npchar, "reload", "reload9_back", "none", "", "", "", 2.3);
			AddQuestRecord("BSHangover", "25");
		break;

		case "BS_F3_21":	//Максин. Вариант с секасом.
			dialog.text = "Let there be rum! Come on!";
			link.l1 = "Come on! I've got a couple or three bottles on me!";
			link.l1.go = "BS_F3_21_exit";
		break;
		
		case "BS_F3_21_exit":	//Максин. Вариант с секасом.
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload9_back", "none", "", "", "", 2.3);
			PChar.quest.BS_IntimWithMaks.win_condition.l1 = "locator";
			PChar.quest.BS_IntimWithMaks.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.BS_IntimWithMaks.win_condition.l1.locator_group = "reload";
			PChar.quest.BS_IntimWithMaks.win_condition.l1.locator = "reload9_back";
			PChar.quest.BS_IntimWithMaks.function = "BS_IntimWithMaks";
		break;

		//В обоих вариантах запись в СЖ: "Итак, я на перепутье. Искать Вейна и лагеря беглых рабов? Или узнать, чем может помочь британский флот? Или стоит проверить версию Элеоноры с торгашами? Распыляться не стоит, банально не хватит времени на всё сразу. Отмету голландцев сразу, пусть и логично звучит, но у Компании своя разведка есть, и Флинт немало им крови попортил. Значит поиски Вейна или помощь флота. Вейн большой мальчик, думаю, что справится и без меня, значит на Антигуа!" 7.04.2023 // так как выбора уже и нет, то не забыть потереть лишее из СЖ финала_2
		//Ниже вариант помощи разведке и Бонсу.
		//Плывём на Антигуа, в локации острова запись в СЖ: "Вейн – большой мальчик, надеюсь, дров не наломает. Проверю таверну. Агент говорил, что если его не будет на месте, спросить разносчицу."

		case "BS_F3_23":	//Офицантка.
			dialog.text = "Can I get you anything, Captain?";
			link.l1 = "No. Honey, have you seen a friend of mine around here? He's a big fisherman, we had a drink here a while back?";
			link.l1.go = "BS_F3_24";
		break;


		case "BS_F3_24":	//Офицантка.
			dialog.text = "Hunting for big fish? He said to tell you that another fisherman will be waiting for you in Dominica waters off Castle Brush Beach.";
			link.l1 = "Thank you. Here's one for, uh, something pretty!"; //Отдаём 500 рублей
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Сбор рыбаков у Доминики. Нужно поспешить".
		//У пляжа стоит фрегат Бонса. Если решим пострелять - провал линейки. Высылаем шлюпку, разговор с Бонсом на борту.

		case "BS_F3_25":	//Бонс.
			dialog.text = "You should be practicing your memory, Captain. The right password can sometimes save a life!";
			link.l1 = "I don't care about your games of passwords and identities. I'm on a case! Flint's gone! With the ship and the gold. It's a miracle we survived! Through my channels, I have no leads. Give me what you got. Maybe we can catch your fish together. And then we'll go our separate ways!";
			link.l1.go = "BS_F3_26";
		break;


		case "BS_F3_26":	//Бонс.
			dialog.text = "What about the honors? Reward? A pardon, finally?";
			link.l1 = "With Urca's gold, I can at least buy myself a title. And you can buy the crown's favor, too. Come on, Billy. I'm itching to stab someone!";
			link.l1.go = "BS_F3_27";
		break;

		case "BS_F3_27":	//Бонс.
			dialog.text = "I'll start at the beginning. 'Scarboro' and the rest of the squadron are here not only to capture Flint and intimidate the pirates. The first priority is to keep the gold from the Urca out of Europe. Spain would easily pay off some of her debts with that gold, and that would deprive them of the influence of their creditors. In addition, this amount of already minted coin - will devalue the already existing ones. So, if the gold disappears in the Caribbean, it's even better. That is, no one in Europe will look for it, and claim rights to it - too.";
			link.l1 = "I understand. Politics, intrigue, conspiracies. Old Europe, it just won't let up.";
			link.l1.go = "BS_F3_28";
		break;

		case "BS_F3_28":	//Бонс.
			dialog.text = "My formal commander, Sir Francis Newm, captain of the Scarborough, is a pompous prat, son of some petty lord. Handing out patents and pardons left and right, recruiting supporters. He seeks what you seek and I suspect my failures are his doing. I have every reason to believe he's going after the gold.";
			link.l1 = "I'm losing the thread, Bill. Flint, the gold. What can you do for me?";
			link.l1.go = "BS_F3_29";
		break;

		case "BS_F3_29":	//Бонс.
			dialog.text = "There's anecdotal information about the Walrus' anchorages in various bays. I don't have the ability to check them quickly. So we'll split up. I'll go to Cape Catoce and head south under the Spanish flag. You go to Boca de la Sierpe and head west from there, checking every cove. We'll meet at Chiriquet Lagoon. Do not enter ports, avoid collisions. Starting now, two weeks should be enough.";
			link.l1 = "You said there was specific information on anchorages! You'd have to look at every cove!";
			link.l1.go = "BS_F3_30";
		break;

		case "BS_F3_30":	//Бонс.
			dialog.text = "The informant was not very accurate in his descriptions and died quickly. Newm is not only an asshole, he's a sadist.";
			link.l1 = "So is Newm looking for parking lots as well?";
			link.l1.go = "BS_F3_31";
		break;

		case "BS_F3_31":	//Бонс.		
			SetFunctionExitFromLocationCondition("BS_BonsDominicaNone", "Dominica", false);
			SetFunctionLocationCondition("BS_ShoreSeeking", "Shore18", false);
			AddQuestRecord("BSHangover", "63");
			dialog.text = "She'll be starting soon. A courier brig from the metropolis arrived the other day and 'Scarborough' has dropped anchor. What orders Newm got, I don't know. But it gives us a head start.";
			link.l1 = "Then let's not delay!";
			link.l1.go = "BS_F3_31exit";
		break;
		
		case "BS_F3_31exit":
			DialogExit();
			npchar.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
			npchar.dialog.currentnode = "BS_F3_31_loop";
		break;
		
		case "BS_F3_31_loop":	//Бонс.
			dialog.text = "We must hurry!";
			link.l1 = "Then let's not delay!";
			link.l1.go = "BS_F3_31exit";
		break;

		//Запись в СЖ: "От Бонса-Блэкхема проку немного, нужно исследовать большой кусок побережья Мэйна. Но это хоть что-то. Начну с бухты Бока де ла Сьерпе"
		//В бухте Бока де ла Сьерпэ, на берегу пусто. Запись в СЖ: "Пусто. Продолжу поиски. Нужно исключить бухты, которые находятся в виду фортов, Флинт не стал бы так рисковать. Сверюсь с картой. Ага, остаются: Пляж Лос Текес, бухта Гуахира, бухта Ковеньяс, залив Москитос. Что же, в путь."
		//В Лос Текес – пара агрессивных английских фрегатов. Бой. Высадка. На берегу штук 30 военных – файт. Запись в СЖ: "Похоже люди Ньюма. Ищут зацепки на месте гибели 'Урки'. Нужно быть настороже". //игрок может и не высадиться в бухте. нужна принудиловка ! 7.04.2023
		//Москитос. На берегу подбегает матрос.

		case "BS_F3_32":	//Матрос.
			dialog.text = "Captain " + GetFullName(pchar) + "? I'm from a fellow fisherman!";
			link.l1 = "Billy still can't play? What you got there?";
			link.l1.go = "BS_F3_33";
		break;

		case "BS_F3_33":	//Матрос.
			dialog.text = "Get to Bridgetown now! The search will be tolerated. That's what he said.";
			link.l1 = "That's it? What's the emergency?";
			link.l1.go = "BS_F3_34";
		break;


		case "BS_F3_34":	//Матрос.
			dialog.text = "I have no idea, "+ GetSexPhrase("sir","ma'am") +", I'm just a messenger!" ;
			link.l1 = "Okay, I get it.";
			link.l1.go = "BS_F3_34exit";
		break;
		
		case "BS_F3_34exit":	//Матрос.
			AddQuestRecord("BSHangover", "66");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 3.0);
			SetFunctionLocationCondition("BS_BridgetownBonsAlarm", "Bridgetown_town", false);
			DialogExit();
		break;

		//Запись в СЖ: "Что-то произошло. Бонс требует срочно прибыть в Бриджтаун."
		//Плывём на Барбадос. В городе подходит Бонс.

		case "BS_F3_35":	//Бонс.
			dialog.text = "You're here. Good. The Barbados authorities are asking for help, their garrison is still understaffed after the Spanish raid. And Scarborough's out of the woods.";
			link.l1 = "What's up? I came across Newm's men on Los Teques beach. Digging through the wreckage of the Urca.";
			link.l1.go = "BS_F3_36";
		break;

		case "BS_F3_36":	//Бонс.
			dialog.text = "They won't find much. The plantations on the island are scheduled to be attacked. Today, tomorrow, soon. And leading the attack is a man you won't believe. Flint himself!";
			link.l1 = "Why the hell would he want to do that?";
			link.l1.go = "BS_F3_37";
		break;

		case "BS_F3_37":	//Бонс.	
			dialog.text = "Somewhere in the colonies, he's building an army of convicts and runaway slaves, and this is the king's penal servitude. Thugs of all stripes, arm them and you're done.  That's what the Spanish gold is for. And he has no intention of sharing it. The local garrison is made up of recruits and colonist militia. They'll scatter at the first volleys. But if we unite our teams, we can fight back and, God willing, capture him!";
			link.l1 = "Ambush me? Well, that could work. Gather your men, meet me at the plantation!";
			link.l1.go = "BS_F3_37exit";
		break;
		
		case "BS_F3_37exit":
			AddQuestRecord("BSHangover", "67");
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			SetFunctionLocationCondition("BS_BridgetownPlantationPrepare", "Bridgetown_Plantation", false);
			pchar.BS_PlantationBattle = true;
			PChar.quest.BS_ReloadToPlantation.win_condition.l1 = "locator";
			PChar.quest.BS_ReloadToPlantation.win_condition.l1.location = "Bridgetown_town";
			PChar.quest.BS_ReloadToPlantation.win_condition.l1.locator_group = "reload";
			PChar.quest.BS_ReloadToPlantation.win_condition.l1.locator = "gate1_back";
			PChar.quest.BS_ReloadToPlantation.function = "BS_ReloadToPlantation";
			LAi_MethodDelay("BS_BridgetownPlantationOrders",0.1);
			DialogExit();
		break;

		//Запись в СЖ: "Предстоит жаркое дельце. Флинт собирается освободить каторжан для своей армии. Отличная возможность прихлопнуть ублюдка. Но, всё же стоит помнить, с кем мы имеем дело. Устроим засаду на плантации".
		//Идём на плантацию. Там бродят наши в перемешку с английскими солдатами, заходим за калитку плантации. Вывести лог «Засада организована! Всем быть на готове!» Начинаем спаунить пиратов от ворот. В три-четыре волны.
		//Перебили всех, Бонс орёт : «Они с полей прут, ещё больше! Стрелки, к бою!»
		
		case "BS_F3_PlantOfficer":
			dialog.text = "Captain, on your orders, the ambush has been organized.";
			link.l1 = "Хорошо.";
			link.l1.go = "BS_F3_PlantOfficerexit";
		break;
		
		case "BS_F3_PlantOfficerexit":	
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, false);
			Group_AddCharacter(LAI_GROUP_PLAYER, npchar.id);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("BS_BridgetownPlantationBattleStart", 30.0);
			DialogExit();
		break;	
		
		case "BS_F3_38":	//Бонс.
			dialog.text = "They're coming from the fields, more of them! Riflemen, to battle!";
			link.l1 = "Follow me!";
			link.l1.go = "BS_F3_38tobattle";
		break;
		
		case "BS_F3_38tobattle":	//Бонс.
			BS_BridgetownPlantationReinforcement_2();
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		//Спауним пиратов прям на плантации. Перебили.

		case "BS_F3_39":	//Бонс.
			dialog.text = "Where the hell is Flint?";
			link.l1 = "This isn't over! Hear that? The cannons are firing! Get down!";
			link.l1.go = "exit";
		break;

		//Нужна пара взрывов где-нибудь. От ворот ещё толпа пиратов. С ними Флинт и Вейн. Пока живы их пираты - Ф и В бессмернтые. Как только полегли все пираты Флинт начинает диалог.

		case "BS_F3_40Flint_1":	//Флинт.
			dialog.text = "Vane! Fall back, reinforcements are coming from the fort!";
			link.l1 = ""; //Вейн
			link.l1.go = "BS_F3_40Vein_1";
		break;
		
		case "BS_F3_40Vein_1":
			StartInstantDialog("BS_Vein", "BS_F3_40Vein_2", "Quest\BlackSails\BS_Final_3.c");
		break;
		
		case "BS_F3_40Vein_2":	//Флинт.
			dialog.text = "I'll cover you, go away!";
			link.l1 = ""; //Вейн
			link.l1.go = "BS_F3_40Bons_1";
		break;
		
		case "BS_F3_40Bons_1":	//Флинт.
			StartInstantDialog("BSBons", "BS_F3_40Bons_2", "Quest\BlackSails\BS_Final_3.c");
		break;


		case "BS_F3_40Bons_2":	//Флинт.
			dialog.text = "I get it. "+pchar.name+", you're fighting on the wrong side! But it's your choice." ; //Убегает.
			link.l1 = "I'm going after Flint. We can't let him get away!"; //Бонс. Убегает.
			link.l1.go = "BS_F3_40Vein_3";
		break;
		
		case "BS_F3_40Vein_3":
			sld = CharacterFromID("Flint");
			Group_AddCharacter(LAI_GROUP_NEITRAL, sld.id);
			LAi_group_MoveCharacter(sld, LAI_GROUP_NEITRAL);
			Lai_SetActorTypeNoGroup(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 10.0);
			StartInstantDialog("BS_Vein", "BS_F3_40Vein_4", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_40Vein_4":	//Вейн.
			sld = CharacterFromID("BSBons");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			dialog.text = "Well? Just you and me?!";
			link.l1 = "What the hell, Charles? We had a deal!";
			link.l1.go = "BS_F3_42";
		break;

		case "BS_F3_42":	//Вейн.
			dialog.text = "You change sides too often. And your new friends killed Eleanor!";
			link.l1 = "How?! When?";
			link.l1.go = "BS_F3_43";
		break;

		case "BS_F3_43":	//Вейн.
			dialog.text = "The 'Scarboro' came to the Bahamas while I was looking for Flint, and made a sweep. Eleanor was taken in chains to Port Royal and hanged in the harbor. Maxine is in jail and will be hanged soon. Jack is in Charlestown jail, but he'll get out of it. Ann has been pardoned. A humane court has decided that hanging a pregnant woman, even though she's a pirate, is overkill. And you've become a dog sniffing out Spanish gold for British intelligence.";
			link.l1 = "Flint told you that? He knows how to play with brains!";
			link.l1.go = "BS_F3_44";
		break;

		case "BS_F3_44":	//Вейн.
			dialog.text = "I saw her body. They put her in a cage so she wouldn't fall apart during decomposition. She's still hanging by the wharf. Stop talking! Someone's going to walk out of here alone!";
			link.l1 = "It's not my fault, Charles. But I can't change your mind. Start when you're ready!";
			link.l1.go = "BS_F3_44VeinFight";
		break;
		
		case "BS_F3_44VeinFight":	//Вейн.
			DialogExit();
			BS_RestoreMaksHostess();
			BS_QuestCleaning(false);
			DoQuestFunctionDelay("BS_BridgetownPlantationVeinFight", 5.0);
		break;
		
		//Рубимся с Вейном. Убиваем. Страдаем, какой автор гнида. Идём в город. Подбегает Сильвер.

		case "BS_F3_45":	//Сильвер.
			dialog.text = "Hey, "+pchar.name+", you're not wearing your face! What was that? Is that Flint?";
			link.l1 = "Shut up, John. How did you get here?";
			link.l1.go = "BS_F3_46";
		break;

		case "BS_F3_46":	//Сильвер.
			dialog.text = "Got away from Flint when he started cleaning up his mess. Cut out the whole old crew!";
			link.l1 = "I'm thinking of catching up with him at sea. Are you with me?";
			link.l1.go = "BS_F3_47";
		break;

		case "BS_F3_47":	//Сильвер.
			dialog.text = "Flint?! No! Yes! Yeah! Yeah, I think you'd be safer. I've been hiding under hookers' skirts for a week!";
			link.l1 = "To the sea, then!";
			link.l1.go = "BS_F3_47exit";
		break;
		
		case "BS_F3_47exit":	//Сильвер.
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("BSHangover", "68");
			Lai_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5.0);
			SetFunctionLocationCondition("BS_Hangover_BarbadosRangerSeaBattle", "Barbados", false);
			Pchar.BonsFlintRunning = true;
			SetFunctionTimerConditionParam("BS_Hangover_CapeCatocheBattle", 0, 0, 5, 0, false);
			SetFunctionTimerConditionParam("BS_SecondFinalEndingTimeOutFail", 0, 0, 14, 0, false);
			BS_Hangover_ChaseFromBarbados();		
		break;

		//Запись в СЖ: "Вейн. Чёрт тебя дери. Ты был мне другом! И Бонс, чёртов Бонс. Пока я искал(ла) непойми что, англичане устроили зачистку. Гатри мертва. Всё катиться в бездну! Осталось поквитаться с Флинтом и плевать, что будет дальше!"
		//Выходим в море, нас атакует «Рейнджер». Топим. Выходим на глобалку. От нас по съёбам удирает квестовик-энка (типо Флинт с Бонсом). Нужно скорости им накрутить, чтоб мы только-только угнаться могли. Энка пиздует к мысу Каточе и там исчезает. Выходим на локалку. Там фрегат Бонса гасится с Моржом (Бонс зелёненький). Берём Моржа на абордаж. В каюте рубилово с Флинтом. Нулим Флинта. Диалог
		//Диалог после боя в каюте Моржа, ниже 7.04.2023																	   


		case "BS_F3_48":	//Флинт.
			dialog.text = "Wayne's dead? It's a shame, but he was too emotional. And did you accept the offer of the English authorities? A pardon, a patent, royal favors? You realize they make promises easily and take them back just as easily. I was one of them!";
			link.l1 = "...";
			link.l1.go = "BS_F3_49";
		break;

		case "BS_F3_49":	//Флинт.
			dialog.text = "Don't give me the stare. It doesn't work on me.  There are other ways to settle this. Capture Bones's frigate, then under English flags and use his signal book to trap the Scarborough. That way, we'll get the attention of military intelligence, they've got their hands full right now. Next ...";
			link.l1 = "Is that how your head works? Plans within plans? There are no friends, no enemies. There are only tools and hindrances. Are you even human?";
			link.l1.go = "BS_F3_50";
		break;

		case "BS_F3_50":	//Флинт.
			dialog.text = "Emotions are misplaced, morality is a sign of weakness, compromise is the path to mediocrity. My goals are a new world. And to build a new one, you have to break the old one. You could be a useful tool, but I see irrational feelings that will hinder your effectiveness. So be it. It'll be a little harder, but nothing is impossible!";
			link.l1 = "Just shut up and die!";
			link.l1.go = "BS_F3_50exit";
		break;

		case "BS_F3_50exit":	//Флинт.
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar);
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			SetFunctionExitFromLocationCondition("BS_Hangover_CapeCatocheBattleOver", pchar.location, false);
			SetFunctionLocationCondition("BS_Hangover_CapeCatocheDialogue", "Shore6", false);
			Log_Info("A book catches your eye - Marcus Aurelius 'Meditations'. You take it, along with Flint's ship's log.");
		break;

			
		//Файт. На трупе Нарвал, книга Марк Аврелий «Размышления». В сундуке 5кк денег, судовой журнал Флинта (зашифрованый).
		//Как только закрываем окно захвата корабля - СЮРПРИЗ. Спаун "Скарборо" с парой фрегатов. Бой, без диалогов в случае захвата. 7.04.2023 //если не получится такой спавн, то по старинке - спавн на глобалке
		//После победы ТП на берег. Скотс Хэд или второй пляж - не важно 7.04.2023 Фрегат Бонса удаляем, он потонул. На берегу Бонс, Сильвер, ГГ.
		
		case "BS_F3_50BonsDeck":	//Флинт.
			dialog.text = "Let's finally get that bastard!";
			link.l1 = "Yes!";
			link.l1.go = "BS_F3_50BonsDeckexit";
		break;
		
		case "BS_F3_50BonsDeckexit":
			DialogExit();
			npchar.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
			npchar.dialog.currentnode = "BS_F3_50BonsDeck_loop";
		break;
		
		case "BS_F3_50BonsDeck_loop":	//Бонс.
			dialog.text = "Let's finally get that bastard!";
			link.l1 = "Yes!";
			link.l1.go = "BS_F3_50BonsDeckexit";
		break;
		
		case "BS_F3_51":	//Сильвер.
			dialog.text = "Flint's dead?";
			link.l1 = "Dead.";
			link.l1.go = "BS_F3_52_1";
		break;
		
		case "BS_F3_52_1":
			LAi_SetStayTypeNoGroup(npchar);
			npchar.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
			npchar.dialog.currentnode = "BS_F3_54";
			StartInstantDialog("BSBons", "BS_F3_52", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_52":	//Бонс.
			dialog.text = "Heh. It's a shame. He'd be very welcome alive in London.";
			link.l1 = "After all that's happened, I think YOU, in London would be welcome too!";
			link.l1.go = "BS_F3_53";
		break;

		case "BS_F3_53":	//Бонс.
			dialog.text = "I think so. Francis Newm, Esquire, died as a hero, and some commander survived. I don't feel at all like answering the questions that will arise!";
			link.l1 = "You two! These are Flint's papers, encrypted. Can you figure it out? I'm gonna lie here and rest. I'm tired of killing."; //Отдаём книгу, журнал.
			link.l1.go = "BS_F3_53exit";
		break;
		
		case "BS_F3_53exit":	//Бонс.
			DialogExit();
			Lai_SetActorTypeNoGroup(npchar);
			WaitDate("",0,0,0,10,0);
			AddQuestRecord("BSHangover", "69");
			SetLaunchFrameFormParam("Прошло десять часов", "", 0.1, 3.0);
			DoQuestFunctionDelay("SilverSpeech", 3.0);
			LaunchFrameForm();
		break;

		//Запись в СЖ: "Где-то на этом пути я сделал(ла) неправильный выбор. Какой момент стал поворотным? Элеонора, Чарльз. Как бы сложились их судьбы, прими я другие решения? Стал(ла) бы я бездушной машиной под руководством Флинта? Чёрт, как голова болит! Нужно отдохнуть".
		//Ставим табличку "Прошло десять часов", мотаем время.

		case "BS_F3_54":	//Сильвер.
			dialog.text = "Hey! Are you alive? You're a master snorer!";
			link.l1 = "What? How's it going?";
			link.l1.go = "BS_F3_55_1";
		break;
		
		case "BS_F3_55_1":
			StartInstantDialog("BSBons", "BS_F3_55", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_55":	//Бонс.
			dialog.text = "Two sheets of coordinates. Latitude, longitude. That's it. No 'Seven paces from a withered tree', nothing!";
			link.l1 = "How this devil thought, how his head works, is beyond comprehension.";
			link.l1.go = "BS_F3_56";
		break;

		case "BS_F3_56":	//Бонс.
			dialog.text = "Could this be the route? But where's the beginning and the end? There are hundreds of points on the map! There must be a connection! There has to be! All I have to do is think, reread the bloody book, there's got to be something!";
			link.l1 = "Where can I take you?";
			link.l1.go = "BS_F3_57_1";
		break;
		
		case "BS_F3_57_1":
			StartInstantDialog("BS_Silver", "BS_F3_57", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_57":	//Сильвер.
			dialog.text = "What? You're giving up?";
			link.l1 = "Puerto Prisipe? We're not far from Cuba.";
			link.l1.go = "BS_F3_58_1";
		break;
		
		case "BS_F3_58_1":
			StartInstantDialog("BSBons", "BS_F3_58", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_58":	//Бонс.
			dialog.text = "Yeah, Puerto Prisipede's fine. I got a stash there. It'll be enough for a while.";
			link.l1 = "Then let's go.";
			link.l1.go = "BS_F3_58exit";
		break;
		
		case "BS_F3_58exit":	//Бонс.
			DialogExit();
			DeleteAttribute(pchar, "BSBonsAccept");
			DeleteAttribute(pchar, "BonsFlintRunning");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", -1);			
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			pchar.BSBonsSpawned = true;
			BSBons_SeaBattle(true);
			SetFunctionLocationCondition("BS_CubaSilverOut", "PuertoPrincipe_port", false);
			DeleteAttribute(PChar, "currentsoundtrack");
			string shore = "Shore6";
			Locations[FindLocation(shore)].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation(shore)], false);
			LAi_LocationDisableOfficersGen(shore, false);
		break;

		//Везём братву на Кубу. В бухте Ла Франсуа подходит Сильвер.

		case "BS_F3_59":	//Сильвер.
			dialog.text = "I'll keep an eye on Billy, I think he's a little out of it. Where are you going?";
			link.l1 = "I'm gonna try to save Max. I'm gonna go to the prison. I'll do something right. Good luck, John!";
			link.l1.go = "BS_F3_59exit";
		break;
		
		case "BS_F3_59exit":	//Сильвер.
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto6", "none", "", "", "", -1);
			pchar.ToHelpMaksInPortRoyal = true;
		break;

		//Плывём в Порт Рояль, идём в тюрягу, комендант.

		case "BS_F3_60":	//Комендант.
			dialog.text = "What's your question?";
			link.l1 = "I was wondering about the fate of a certain person. Maxine.";
			link.l1.go = "BS_F3_61";
		break;

		case "BS_F3_61":	//Комендант.
			dialog.text = "Ah, ma'am! She's all right. They kept her in a cage for a couple of days, then a messenger came from the governor himself with a pardon. And they let her go with God!";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
		break;

		//Идём в бордель. Комната мадам.

		case "BS_F3_62":	//ГГ
			dialog.text = "" ;
			link.l1 = "I never thought I'd see you alive!";
			link.l1.go = "BS_F3_63";
		break;
		
		case "BS_F3_63":	//ГГ
			dialog.text = "My captain! As long as my girls gather rumors, I'm safe. I share them generously with both the authorities and the corsairs. Everyone is ready to stand up for me.";
			link.l1 = "Well, then. Then my mission is complete. Here's your share, companion. Here's everything we recovered from the 'Urca's' gold.";
			link.l1.go = "BS_F3_64";			
		break;

		case "BS_F3_64":	//ГГ.
			dialog.text = "I won't say no. Especially with the expense involved. I've secured permission to give Eleanor a proper burial. And I'll send money to Anne. Did you hear about Jack?";
			link.l1 = "Yeah. Flint's dead, Wayne's dead.";
			link.l1.go = "BS_F3_65";
			if (sti(pchar.money) >= 1000000)
			{
				pchar.makslover = true;
				SaveCurrentQuestDateParam("MaksLoverDateDay");
			}
			AddMoneyToCharacter(PChar, -1000000);
		break;

		case "BS_F3_65":	//ГГ.
			dialog.text = "Has the story come to an end?";
			link.l1 = "That story, yes. There are many more untold stories. Goodbye Max!";
			link.l1.go = "BS_F3_66";
		break;

		case "BS_F3_66":	//ГГ.
			SetFunctionLocationCondition("BS_PortRoyalSilver", "PortRoyal_town", false);
			RestoreOldDialog(npchar);
			dialog.text = "Visit me, Captain, from time to time.";
			link.l1 = "I will!";
			link.l1.go = "exit";
		break;

		//Уходим в закат. Макс – остаётся в роли мадам, с бесплатными потрахушками. Можно ей добавить слухов по «Лёгкой добыче».
		//На выходе из борделя – подбегает Сильвер


		case "BS_F3_67":	//Сильвер.
			dialog.text = "Bones found the connection! They really are waypoints! And he's the only one with a map!";
			link.l1 = "Captain Flint's treasure island map?";
			link.l1.go = "BS_F3_68";
		break;


		case "BS_F3_68":	//Сильвер.
			dialog.text = "Yes! But he got away. Disappeared. Disappeared with the map! We have to find him!";
			link.l1 = "That's your story, John. Here's some for you. Buy yourself a sucker and chase Billy Bones all the way to England!"; //отдаём 25к
			link.l1.go = "BS_F3_69";
		break;

		case "BS_F3_69":	//Сильвер.
			dialog.text = "But... Are you sure?! I can see that I am. I'll find you, I will. Oh, we're gonna feast on Flint's money!";
			link.l1 = "Get out of here, Silver!";
			link.l1.go = "BS_F3_69exit";
			AddMoneyToCharacter(PChar, -25000);
		break;
		
		case "BS_F3_69exit":	//Сильвер.
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto4", "none", "", "", "", 2.0);
			DoQuestFunctionDelay("BS_SecondFinalEndingQuest", 3.0);
			SetMusic("Theme_from_Black_Sails");
		break;

		//Квест уходит в архив.
	}
}
