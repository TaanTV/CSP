
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

		//Заменить хозяйку борделя в ПР на Максин. Пускать на глобалке английских охотников (скоростые) 2-3 третьеклассника.//по поводу охотников. сейчас спавнится только один рядом с Бермудами. так как переезжаем на Багамы - спавнить фиолетового догонялу от Пуэрто Принсибе и ещё одного у Ямайки. для огоньку 7.04.2023

		//Прибыли в ПР. Идём в бордель к мадам. Опа, сюрприз. Это Макс //помимо квестовых диалогов, на будущее, её нужно сделать мадам в ПР по завершению квеста. если возможно, то с дармовыми шлюхами. типо по старой дружбе. ну или лично с ней дармовой перепихон. пусть отрабатывает лям =) 7.04.2023

		case "BS_NU_1":	//Максин
			dialog.text = "...";
			link.l1 = "Congratulations on your career growth! Unexpectedly, however.";
			link.l1.go = "BS_NU_2";
		break;

		case "BS_NU_2":
            dialog.text = "Greetings, "+pchar.name+". Decided to relax or entertain the team?";
            link.l1 = "I need your help. I know that girls from brothels see and hear a lot of things, and I'm ready to buy some information from you.";
			link.l1.go = "BS_NU_3";
		break;

		case "BS_NU_3":
            dialog.text = "Do you need a tip on a fat prey? You don't have to pay anything, I'll share it out of reciprocity, but I still owe you.";
            link.l1 = "We don't need a tip, we need any clue about the fattest prey imaginable! Do you understand what I mean?";
			link.l1.go = "BS_NU_4";
		break;

		case "BS_NU_4":
            dialog.text = "'Urca De Lima'! Flint doesn't waste time on trifles. I know something, but it's not free, I'm sorry.";
            link.l1 = "Name the price.";
			link.l1.go = "BS_NU_5";
		break;

		case "BS_NU_5":
            dialog.text = "Equal share as a companion. And some things are free from me. About the English raiders.";
            link.l1 = "Do you understand that shares need to be negotiated with all participants in the enterprise? Or do you want a share of my share?";
			link.l1.go = "BS_NU_6";
		break;

		case "BS_NU_6":
            dialog.text = "I understand, and that's why I'm going with you. And after meeting with the rest of the partners, I hope we will come to an agreement that is mutually beneficial for all parties.";
            link.l1 = "Persuaded, let's go now!";
			link.l1.go = "BS_NU_7";
		break;

		case "BS_NU_7":
            dialog.text = "Wait a minute. Something about the British. A squadron led by the warship Scarborough arrived in the Caribbean. It is rumored that this is the military intelligence of the Admiralty. They do not enter English ports, they do not report to the governors. Many privateers and pirates have already gone missing. And some were seen, but they pretended that they were not who they were supposed to be. Something strange is happening.";
            link.l1 = "I've already run into it several times with raiders under English flags. Nothing special. But these Brits are very persistent. Suicidally persistent.";
			link.l1.go = "BS_NU_8";
		break;

		case "BS_NU_8":
            dialog.text = "That's all I know about them. I'm ready to go.";
            link.l1 = "Let's go. Wait, though. Have you heard anything about Charles Wayne? Did he show up in the colonies?";
			link.l1.go = "BS_NU_9";
		break;

		case "BS_NU_9":
            dialog.text = "The wreck of the Ranger was fished out of Portland Harbor. Somebody heard something about a fight off the island, ask around the tavern. Here or Fort Orange. I haven't heard anything about Charles himself."; //посещать саму бухту - не нужно. сразу по завершению диалога, садить алкашей со слухом нужным и в ПР и в ФО. либо там либо там, по отработке слуха - следующая стадия 7.04.2023
            link.l1 = "That's something. We'll have to check it out. You go aboard, I'll run the taverns, see if the local boozers have seen anything. Ask Sandro Thorn to show you to your quarters, or you'll never know. My boys are well-trained, but they might not let a pretty girl like that in for nothing.";
			AddQuestRecord("BSUrka", "1");
			SetQuestHeader("BSUrka");
			CloseQuestHeader("BSChaseBegun");
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_NU_9_exit";
			pchar.BSUrka_Negril = true;
			PChar.quest.BSUrka_Negril.win_condition.l1 = "location";
			PChar.quest.BSUrka_Negril.win_condition.l1.location = "Shore36";
			PChar.quest.BSUrka_Negril.function = "BSUrka_Negril";
			SetFunctionExitFromLocationCondition("BS_RestoreMaksHostess", pchar.location, false);
		break;

		case "BS_NU_9_exit":
            dialog.text = "See you on the ship, captain.";
            link.l1 = "Yeah, I'll see you around.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_NU_9_exit";
		break;
		//Запись в СЖ: «Таинственные английские военные, пропавший Вейн и новый компаньон в нашем дельце на сто пятьдесят миллионов. Нужно проверить информацию о разбившемся 'Рейнджере' у местных выпивох и выдвигаться на Багамы. Как бы не упустить денежный галеон». 7.04.2023

		//бухта Портленд запись в СЖ: «Сломанные мачты, куски обшивки, рваный такелаж и прочий мусор. Нужно расспросить местных о случившемся» // для особо въедливых это можно и оставить. хз. только перенести триггер в бухту Портленд 7.04.2023

		//В форт Оранж или в Порт Рояле в таверне у бармена ничего. Выпиваем с алкашом – бинго. кстати слух в текущих фиксах ловится очень не сразу. нужен гарантированный алкаш 7.04.2023

		case "BS_NU_10":	//Алкоголик
            dialog.text = "Cheers! Ooh, nice rum. You should have seen what happened in the bay a couple of days ago. A pirate brig, all dented from the nukes, with sails like a ghost ship gave battle to two Spanish frigates. And then, out of nowhere, from behind the cape, three pirates on corvettes! It's not clear who was chasing whom. The Spaniards laid down on their left tack and started firing battery fire. One corvette was shot through from bow to stern, it was a scream! You could hear it in the fort! So, the one that was shot at once fell on board and began to sink, and the other two, with their own broadsides, almost at point-blank range blew the frigate apart. And the brig, which was fleeing from the Spaniards, suddenly became bolder, threw anchor on the port side and made a sharp turn around the chain, so that the mast was even lost. And began to shoot at the pirate from the side. In general, they sank the second corvette together with the Spanish survivor. Heh, my throat's dry.";
            link.l1 = "Here, have some more. So what happened next? Interesting story! I can see that fight in my mind's eye!";
			link.l1.go = "BS_NU_11";
		break;

		case "BS_NU_11":
            dialog.text = "Uh-huh. That's good, thank you. Okay. The pirate, on the surviving corvette, realized that things were bad, went downwind and ran away at full sail over the horizon! And on the brig, the anchor chain was cut off and the side of the frigate was piled on top of it. So they went to board the frigate. And defeated the Spaniards! The frigate hoisted a black flag, fired a salvo at the shabby brig and went somewhere to the north. It was such a battle, you could paint a picture of it! The whole coast was strewn with wreckage!";
            link.l1 = "Thanks for the story. You should write books with such talent!"; // хорошо бы вообще именного НПС под этот слух сделать Александр Оливье Эксквемелин. кто в теме пиратской истории - тот поймёт отсылку 7.04.2023
			link.l1.go = "exit";
		break;

		//Запись в СЖ: «Вейн жив, обзавёлся новым кораблём и выполнил свою часть по отвлечению сопровождения. Каков корсар! Надеюсь, увидимся на Багамах»

		//Выходим в море, спауним фиолетовую энку (англичане). Файт. Три фрегата, кэп флагмана – Билли Бонс. Берём на абордаж. Файт в каюте, после «убиения» - диалог.ВАЖНО! это ключевой момент для второго фварианта финала! Если убить Билла, то идём по первой ветке, если согласились, то по BS_Final_3 7.04.2023

		case "BS_NU_12":	//Билли Бонс
            dialog.text = "Stop! I need to talk to you!";
            link.l1 = "Well, well, well. Flint's own chief mate and suddenly an English captain. What's that supposed to mean?";
			link.l1.go = "BS_NU_13";
		break;

		case "BS_NU_13":
            dialog.text = "I have always been and am an English captain, or rather a commander! Admiralty Intelligence, Commander William Blackham, at your service.";
            link.l1 = "And why the hell is Admiralty Intelligence after me? Are all those raiders I sunk yours, too?";
			link.l1.go = "BS_NU_14";
		break;

		case "BS_NU_14":
            dialog.text = "Privateers, pirates who have been pardoned and joined His Majesty's service. There is much zeal, but unfortunately little skill.";
            link.l1 = "I see. Expendable. So what does your office want with me?";
			link.l1.go = "BS_NU_15";
		break;

		case "BS_NU_15":
            dialog.text = "Flint. Or rather Captain James McGraw, traitor, thief, murderer. A former officer in His Majesty's navy, guilty of the murder of Lord Hamilton, his wife and a hundred other crimes. All my attempts to arrest or kill this man have failed, and I offer you, as his trusted companion, to help a representative of the Royal Navy arrest or destroy the traitor!";
            link.l1 = "And what's the interest in me doing that?";
			link.l1.go = "BS_NU_16";
		break;

		case "BS_NU_16":	//Тут выбор
            dialog.text = "A royal pardon for you and your men, four hundred thousand pounds in silver and the opportunity for a brilliant career in the Admiralty. And the gratitude of the Hamilton family, which, believe me, is worth a lot!";
            link.l1 = "Go to hell, Billy, with your pardon and his majesty! I don't betray my friends! And I'm gonna get more out of this friendship than you'll ever get out of it! Ready to continue? Die!";
			link.l1.go = "Fight_Billi_Bons";
			link.l2 = "I'll think about it. How do I get in touch with you?"; //собственно вот вариант для второй финалки 7.04.2023
			link.l2.go = "BS_NU_17";
		break;

		case "Fight_Billi_Bons":
			AddQuestRecord("BSUrka", "4");
			pchar.BSBonsKilled = true;
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "BS_NU_17":
            dialog.text = "In Antigua, in a tavern, my man will be waiting. Password: 'Fishing was a success. The catch was a sight to behold'.";
            link.l1 = "See you later, Sir William.";
			link.l1.go = "Accept_Billi_Bons";
		break;
		
		case "Accept_Billi_Bons":
			pchar.BSBonsAccept = true;
			AddQuestRecord("BSUrka", "5");
            SetFunctionExitFromLocationCondition("BS_Billi_Bons", pchar.location, false);
			BS_Billi_Bons_NotEnemy();
			Map_ReleaseQuestEncounter(npchar.id);
			QuestAboardCabinDialogSurrender();			
		break;

		//Расходимся миром. В таверну Антигуа поселить непися за стол. имеется ввиду, что корабль отпускаем после абордажа, он становится зелёным. для особо упоротых, а таких хватает - как в "потрёпанном корабле" сделать его "прозрачным", чтоб не не дамажился и не брался на абордаж 7.04.2023

		//Запись в СЖ если убили Билла: «Ситуация с английскими рейдерами прояснилась. Надо же. Разведка адмиралтейства! Нужно предупредить Флинта. Где-то всё ещё охотится ‘Скарборо’ и с этим, нужно что-то делать. В путь. На Багамы».

		//Запись в СЖ если приняли сторону Билла: «Я принял(ла) косвенно предложение Бонса, то есть Блэкхэма. Но сначала 'Урка'! Такую добычу нельзя упускать. Нужно записать пароль для встречи со связным на Антигуа. «Рыбалка успешной была. Улов – загляденье»»

		//При любом раскладе – рейдеров, на глобалке выключаем.

		//Пиздуем на Багамы. По улицам гуляют Бонни и Рекхэм. Просто гуляют с обычными для нпс диалогами.

		//В доме Флинт, Сильвер, Гатри, Вейн. С нами приходит Макс. Если согласились топить за Англию – про «Скарборо» нет веток.

		case "BS_NU_18":	//Флинт
            dialog.text = "Finally, everyone's here. Who's your date, "+pchar.name+"?";
            link.l1 = "Meet Maxine. Uh. She runs a brothel in Port Royal.";
			link.l1.go = "BS_NU_18_1";
		break;

		case "BS_NU_18_1":
			DialogExit();
			StartInstantDialogNoType("BS_Vein", "BS_NU_19", "Quest\BlackSails\Neulovimaya_Urka.c");
		break;

		case "BS_NU_19":	//Вейн
            dialog.text = "Wow, Max! You flew high! Remember, it hurts to fall, it really hurts!";
            link.l1 = "";
			link.l1.go = "BS_NU_19_1";
		break;

		case "BS_NU_19_1":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_20";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_20":	//Максин
            dialog.text = "I'll keep that in mind, thank you, Charles. Gentlemen, I have the information you need about the money galleon, and I propose to sell it to you for an equal share of the booty.";
            link.l1 = "";
			link.l1.go = "BS_NU_20_1";
		break;
		case "BS_NU_20_1":
			DialogExit();
			sld = CharacterFromID("Gatri_temp");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_21";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_21":	//Гатри
            dialog.text = "Someone you know, Charlie? The brothel owner? Somebody sang me stories about eternal love and fidelity to the grave, and he's a whoremonger!";
            link.l1 = "";
			link.l1.go = "BS_NU_21_1";
		break;
		case "BS_NU_21_1":
			DialogExit();
			StartInstantDialogNoType("Flint", "BS_NU_21_2", "Quest\BlackSails\Neulovimaya_Urka.c");
		break;
		case "BS_NU_21_2":	//Флинт
            dialog.text = "Business first, Eleanor! Equal share, Miss Maxine, implies equal participation and risk. I hope your information is worth it. Outline it and we'll consider your participation in our partnership.";
            link.l1 = "";
			link.l1.go = "BS_NU_21_3";
		break;
		case "BS_NU_21_3":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_22";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_22":	//Максин
            dialog.text = "As far as I know, your hunt for the Urca has been thwarted. The thing is, she took a different route, didn't go to Havana, it was all a diversion. And I know where the ship went!";
            link.l1 = "Unbelievable! How? From your employees?";
			link.l1.go = "BS_NU_23";
		break;
		case "BS_NU_23":
            dialog.text = "'Urka' has received strictest orders not to call at any ports, but to use the services of trusted captains for resupply and troop transportation. One of these captains has peculiar tastes, and only my establishment can satisfy them. A couple of visits and he has sung so much that he can be hanged, shot, or quartered at choice, or all at once.";
            link.l1 = "";
			link.l1.go = "BS_NU_23_1";
		break;
		case "BS_NU_23_1":
			DialogExit();
			StartInstantDialogNoType("BS_Vein", "BS_NU_24", "Quest\BlackSails\Neulovimaya_Urka.c");
		break;
		case "BS_NU_24":	//Вейн
            dialog.text = "What kind of flavors are these?";
            link.l1 = "";
			link.l1.go = "BS_NU_24_1";
		break;
		case "BS_NU_24_1":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_25";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_25":	//Максин
            dialog.text = "Let it remain a secret. Now, the 'Urca De Lima' will proceed along the coast of Maine and anchor off the west coast of Curaçao, where she will await the arrival of a convoy squadron from Havana and thence proceed to Europe, passing Barbados and Trinidad. Have I earned my share, gentlemen?";
            link.l1 = "";
			link.l1.go = "BS_NU_25_1";
		break;
		case "BS_NU_25_1":
			DialogExit();
			StartInstantDialogNoType("Flint", "BS_NU_26", "Quest\BlackSails\Neulovimaya_Urka.c");
		break;
		case "BS_NU_26":	//Флинт
            dialog.text = "Quite. But I would ask you to keep me company, Miss Guthrie, here on the island. And we must get our ships ready and get to sea at once! The west coast of Curaçao is a dangerous place for sudden squalls and the currents are unpredictable, and could easily carry us and our prize under the guns of Willemstad. We need to calculate the route more carefully.";
            link.l1 = "";
			link.l1.go = "BS_NU_26_exit";
			AddQuestRecord("BSUrka", "6");
		break;

		case "BS_NU_26_exit":
			DialogExit();
			NextDiag.CurrentNode = "BS_NU_28";
			SetFunctionLocationCondition("BS_BSUrka_NassauFlintDialogue", "Nassau_town", false);
			DoReloadCharacterToLocation("Nassau_Town", "officers", "HouseS1_3");
		break;
		//Запись в СЖ: «Макс дала важную информацию. Испанцы предвидели охоту за галеоном и запутали следы. Но болтливые и похотливые людишки рушат любые планы и вскрывают любые тайны. Заметка себе: «Не болтать в борделях!»»

		//Все сваливают из резиденции. Остаётся ГГ и Флинт.

		case "BS_NU_28":	//Флинт
			pchar.quest.BSUrka_Fail1.win_condition.c1 = "NPC_Death";
			pchar.quest.BSUrka_Fail1.win_condition.c1.character ="Flint";
			PChar.quest.BSUrka_Fail1.function = "BSUrka_Fail";

			pchar.quest.BSUrka_Fail2.win_condition.c1 = "NPC_Death";
			pchar.quest.BSUrka_Fail2.win_condition.c1.character ="BS_Vein";
			PChar.quest.BSUrka_Fail2.function = "BSUrka_Fail";

			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//Флинт присоединяется к эскадре
			Flag_Change(PIRATE);
			SetCharacterGoods(npchar, GOOD_FOOD, 1200+rand(500));
			SetCharacterGoods(npchar, GOOD_MEDICAMENT, 1200+rand(500));
			SetCharacterGoods(npchar, GOOD_RUM, 500+rand(250));
			LAi_SetImmortal(npchar, false);

			SetShipRemovable(npchar, false);
			SetCharacterRemovable(npchar, false);
            dialog.text = "";
            link.l1 = "One last push?";
			if (CheckAttribute(pchar, "BSBonsAccept"))
			{
				link.l1.go = "BS_NU_29_Ya_Shpion";
			}
			else
			{
				link.l1.go = "BS_NU_29_Ya_Ne_Krisa";
			}
		break;

		//Если мы остались верны Флинту, то следующий диалог:

		case "BS_NU_29_Ya_Ne_Krisa":
            dialog.text = "I suspect it won't be the last.";
			if(CheckAttribute(pchar, "BSBonsKilled"))
			{
				link.l1 = "I met your first officer off Jamaica. Commander William Blackham. Bones. Billy Bones.";
				link.l1.go = "BS_NU_30_Ya_Ne_Krisa";
			}
			else
			{
				link.l1 = "We've been through a lot together. You can count on me, no matter what happens.";
				link.l1.go = "BS_NU_32_Ya_Ne_Krisa";
			}
		break;

		case "BS_NU_30_Ya_Ne_Krisa":
            dialog.text = "Commander? Hmm... I suspected he was a spy, but he works for Jackman. But the Admiralty...";
            link.l1 = "They want your head for killing Lord Hamilton and so on and so forth and so on and so forth. I'm a gold digger.";
			link.l1.go = "BS_NU_31_Ya_Ne_Krisa";
		break;

		case "BS_NU_31_Ya_Ne_Krisa":
            dialog.text = "But you didn't listen to him? Why?";
            link.l1 = "One hundred and fifty million brilliant reasons, for crying out loud! And I don't sell friends.";
			link.l1.go = "BS_NU_32_Ya_Ne_Krisa";
		break;

		case "BS_NU_32_Ya_Ne_Krisa":
            dialog.text = "You honor me by offering your friendship. I accept it gladly. Here is my hand.";
            link.l1 = "Here's mine. What's up? Time to check on the elusive 'Urka'!";
			link.l1.go = "BS_NU_32_exit";
		break;

		case "BS_NU_32_exit":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			ChangeCharacterAddressGroup(sld, "Nassau_town", "reload", "houseS1");
			sld.dialog.currentnode = "BS_NU_33_Ya_Ne_Krisa";
			LAi_SetStayTypeNoGroup(sld);
			sld.talker = 10;
		break;

		//Если мы предаём Флинта, то следующий диалог: //для второй финалки 7.04.2023

		case "BS_NU_29_Ya_Shpion":
            dialog.text = "I suspect it won't be the last.";
            link.l1 = "...";
			link.l1.go = "BS_NU_30_Ya_Shpion_exit";
		break;
		
		case "BS_NU_30_Ya_Shpion_exit":
            LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			ChangeCharacterAddressGroup(sld, "Nassau_town", "reload", "houseS1");
			sld.dialog.currentnode = "BS_NU_33_Ya_Shpion";
			LAi_SetStayTypeNoGroup(sld);
			sld.talker = 10;
		break;

		//Ставим Моржа и Вейна на ТФ «Рейнджер» в эскадру. На выходе из резиденции говорим с Вейном.

		//Если мы остались верны Флинту, то следующий диалог:

		case "BS_NU_33_Ya_Ne_Krisa":
            dialog.text = "What did you and Flint talk about?";
            link.l1 = "Planning a camping trip. I heard about your fight with the Spaniards! And I see you have a new ship. That's a hell of a thing to pull off! How did you even survive?";
			link.l1.go = "BS_NU_34_Ya_Ne_Krisa";
		break;

		case "BS_NU_34_Ya_Ne_Krisa":
            dialog.text = "I'm damn lucky, I don't know any other explanation myself.";
            link.l1 = "I wish I had a little bit of your luck. Well, let's get moving.";
			link.l1.go = "BS_NU_34_exit";
		break;

		//Если мы предаём Флинта, то следующий диалог:

		case "BS_NU_33_Ya_Shpion":
            dialog.text = "What did you and Flint talk about?";
            link.l1 = "There is something that needs to be discussed. But that's after "Urka.";
			link.l1.go = "BS_NU_34_Ya_Shpion";
		break;

		case "BS_NU_34_Ya_Shpion":
			
            dialog.text = "Whatever you say. Let's go.";
            link.l1 = "";
			link.l1.go = "BS_NU_34_exit";
		break;

		case "BS_NU_34_exit":
			chrDisableReloadToLocation = false;
			FantomMakeCoolestSailor(npchar, SHIP_DIANA, "Ranger", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//вейн присоединяется к эскадре
			BSRepairShip(npchar);
			SetCharacterGoods(npchar, GOOD_FOOD, 1200+rand(500));
			SetCharacterGoods(npchar, GOOD_MEDICAMENT, 1200+rand(500));
			SetCharacterGoods(npchar, GOOD_RUM, 500+rand(250));
			SetShipRemovable(npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			BSUrka_Curacao_SeaBattle();
            pchar.quest.BSUrka_Curacao_SeaBattle.win_condition.l1 = "EnterToSea";
			pchar.quest.BSUrka_Curacao_SeaBattle.function    = "BSUrka_Curacao_SeaBattle";
			DialogExit();
		break;

		//Выходим в море, чешем до Кюрасао. С западной стороны выходим на локалку. Сюрпрайз. Урки нету! Зато есть 6-8 испанских фрегатов и линейников. Адовое мочилово. После боя, ТП на палубу Флинта.

		case "BS_NU_35":
            dialog.text = "";
            link.l1 = "Almost everything fits, but where's 'Urka'?";
			link.l1.go = "BS_NU_36";
		break;

		case "BS_NU_36":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "LockShoreReload");
            dialog.text = "Relax, we caught some Spaniards out of the water, they're being questioned now. We'll make for the roadstead at Cape Calvinistas. We'll talk ashore.";
            link.l1 = "";
			link.l1.go = "exit";
			pchar.LockMapReload = "First we must interrogate the captured Spaniards at Cape Calvinistas.";
			pchar.quest.BSUrka_Curacao_Shore.win_condition.l1          = "location";
			pchar.quest.BSUrka_Curacao_Shore.win_condition.l1.location = "Shore23";
			pchar.quest.BSUrka_Curacao_Shore.function             = "BSUrka_Curacao_Shore";
		break;

		//Доплываем до мыса Кальвинистов, выходим на берег. На берегу испанский офицер, Флинт, Вейн, Бонни.

		case "BS_NU_37":	//Флинт
            DeleteAttribute(pchar, "LockMapReload");
			dialog.text = "We are in Curaçao, you will be released without harm if we get the information we are interested in. Otherwise, you know my reputation! And don't delay in making a decision.";
            link.l1 = "";
			link.l1.go = "BS_NU_381";
		break;

		case "BS_NU_381":
			DialogExit();
			sld = CharacterFromID("BSUrka_Prisoner");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_38";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_38":	//Испанский офицер
			sld = CharacterFromId("Flint");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorTurnToCharacter(sld, npchar);
            dialog.text = "Damned cabrons! Hell awaits you all! But I accept your terms! The ship you're interested in has been swept by a squall in the direction of Maine. It's battered by the storm and will be refloated in one of the bays. That's all I can tell you.";
            link.l1 = "";
			link.l1.go = "BS_NU_391";
		break;

		case "BS_NU_391":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_39";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_39":	//Флинт
            dialog.text = "Thank you, you may go.";
            link.l1 = "";
			link.l1.go = "BS_NU_401";
		break;

		case "BS_NU_401":
			DialogExit();
			sld = CharacterFromID("BS_Bony");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_40";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_40":	//Бонни убивает испанца
            dialog.text = "Like hell he can walk!";
            link.l1 = "";
			link.l1.go = "exit";
			DoQuestFunctionDelay("BSUrka_BonyHits", 0.3);
		break;

		case "BS_NU_41":	//Вейн
            dialog.text = "What the hell, Ann? What's gotten into you?";
            link.l1 = "";
			link.l1.go = "BS_NU_421";
		break;

		case "BS_NU_421":
			DialogExit();
			sld = CharacterFromID("BS_Bony");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_42";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_42":	//Бонни
            dialog.text = "The search had dragged on and there were too many surprises already to let go of this prisoner who would bring another squadron upon us!";
            link.l1 = "";
			link.l1.go = "BS_NU_431";
		break;

		case "BS_NU_431":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_43";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_43":	//Флинт
            dialog.text = "Mr. Wayne, watch your employees! This is the last prank I will tolerate.";
            link.l1 = "";
			link.l1.go = "BS_NU_44";
		break;

		case "BS_NU_44":	//Флинт
			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
            dialog.text = "Anne, into the dinghy! Silence! We'll talk later.";
            link.l1 = "Time to search a lot of coves. Let's get to work!";
			link.l1.go = "BS_NU_44_exit";
		break;

		case "BS_NU_44_exit":
			AddQuestRecord("BSUrka", "7");
			DialogExit();
			sld = CharacterFromID("Flint");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			BSUrka_PlaceUrka();
			pchar.quest.BSUrka_Found.win_condition.l1          = "location";
			pchar.quest.BSUrka_Found.win_condition.l1.location = "Cumana";
			pchar.quest.BSUrka_Found.function             = "BSUrka_Found";
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_4_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: «Охота затянулась, и нервы начинают сдавать. Нужно разобраться с этим поскорее, пока мы не передрались»

		//Выходим в море. Ищем по бухтам Мурку. Мурка в Лос Текос. В бухте ставим раздолбаный имперский галеон под названием «Урка де Лима». Взаимодействовать с ней нельзя. Она просто декорация. На рейде – испанский мановар. Файт.

		//После потопления самовара, запись в СЖ: «Наконец то! Вот она 'Урка'. Её сильно потрепало штормом и команды не видно на борту. Высаживаемся на берег!»

		//На берегу – адский файт. Испанцев лучше пускать волнами, чтоб не лагало всё к херам штук по 30 и так пять раз. Флинта, Вейна, Сильвера – лучше сделать либо бессмертными, либо очень толстыми на момент файта.

		//После победы запись в СЖ: «Дело сделано, столько крови я никогда не проливал(ла) за один раз. Нет сил, даже говорить. Грузим сундуки на корабли и отчаливаем, пока на шум не налетела береговая охрана».

		//Ставим табличку «Прошло 3 часа, сундуки погружены на корабли»

		//Подходит Флинт

		case "BS_NU_45":	//Флинт
            dialog.text = "It's done, we'll do it in the Bahamas. Time to go.";
            link.l1 = "";
			link.l1.go = "BS_NU_45_exit";
		break;

		case "BS_NU_45_exit":
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", -1);
			DialogExit();
			
			PChar.quest.BSUrka_Nassau_Ending.win_condition.l1 = "location";
			PChar.quest.BSUrka_Nassau_Ending.win_condition.l1.location = "Nassau_OfisGatri";
			PChar.quest.BSUrka_Nassau_Ending.function = "BSUrka_Nassau_Ending";
			PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1 = "locator";
			PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.location = "Nassau_town";
			PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.locator_group = "reload";
			PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.locator = "houseS1";
			PChar.quest.BSUrka_Pirates_town_residence.function = "BSUrka_Pirates_town_residence";

			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Rakham");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);

			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";				
			if (CheckAttribute(pchar, "BSBonsAccept"))
			{
				sld.dialog.currentnode = "BS_NU_46_Ya_Shpion";
			}
			else
			{
				sld.dialog.currentnode = "BS_NU_46_Ya_Ne_Krisa";	
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		//Флинт уходит на корабль. Остаётся Вейн.

		//Если мы остались верны Флинту, то следующий диалог:

		case "BS_NU_46_Ya_Ne_Krisa":	//Вейн
			RemoveCharacterCompanion(PChar, npchar);
			dialog.text = "I've almost given up believing this galleon is real. You're a good fighter. Find me afterwards, maybe we can do some business together!";
            link.l1 = "I'm very unlikely to go to the next case! You know, but thanks for the offer! You're one hell of a corsair too!";
			link.l1.go = "BS_NU_47_Ya_Ne_Krisa";
		break;

		case "BS_NU_47_Ya_Ne_Krisa":
            dialog.text = "I'm a pirate. You can't lure me with a patent. I don't like uniforms.";
            link.l1 = "Time to go to the Bahamas. Let's go.";
			link.l1.go = "BS_NU_47_Ya_Ne_Krisaexit";
		break;

		case "BS_NU_47_Ya_Ne_Krisaexit":
			chrDisableReloadToLocation = false;
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", -1);
			DialogExit();
			AddQuestRecord("BSUrka", "9");
			pchar.BSBonsSpawned = true;
			BSBons_SeaBattle(true);
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_5_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
			PChar.quest.BSChaseBegun_Fail.over = "yes";
			PChar.quest.BSUrka_Fail1.over = "yes";
			PChar.quest.BSUrka_Fail2.over = "yes";
			PChar.quest.BSUrka_Curacao_EndSeaBattle.over = "yes";
			PChar.quest.BSUrka_SeaBattleEnded.over = "yes";
		break;

		//Если мы предаём Флинта, то следующий диалог://финалка номер два ! 7.04.2023

		case "BS_NU_46_Ya_Shpion":	//Вейн
            dialog.text = "Is there something you wanted to talk about? Before the final push.";
            link.l1 = "Yeah, there's something. Off Jamaica, I ran into Billy Bones, who is not Bones at all, but a British naval intelligence officer. Don't interrupt! They want Flint's head in exchange for colonial loyalty and a reward. Four hundred thousand pounds in silver. In local currency, that's two and a half million each, if you're in. What do you say?";
			link.l1.go = "BS_NU_47_Ya_Shpion";
		break;

		case "BS_NU_47_Ya_Shpion":
            dialog.text = "A piece of all those Spanish millions and a reward from the British crown? In exchange for that arrogant son of a bitch's head? How do you think you're gonna pull it off?";
            link.l1 = "If we attack him at sea right now, our own crews will chop us to mincemeat. Flint's a demigod to them now! When we get back, after the sharing, when everyone's drunk, we'll get him then. We can get some more money for him alive.";
			link.l1.go = "BS_NU_48_Ya_Shpion";
		break;

		case "BS_NU_48_Ya_Shpion":
            dialog.text = "I'm in, even though this case reeks of shit, but to see the look in his eyes when he realizes he's been screwed is worth it!";
            link.l1 = "So tonight, after the split. Okay, we're being watched. Let's go.";
			link.l1.go = "BS_NU_48_Ya_Shpionexit";
		break;
		
		case "BS_NU_48_Ya_Shpionexit":
			chrDisableReloadToLocation = false;
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", -1);
			DialogExit();
			AddQuestRecord("BSUrka", "10");
			PChar.quest.BSChaseBegun_Fail.over = "yes";
			PChar.quest.BSUrka_Fail1.over = "yes";
			PChar.quest.BSUrka_Fail2.over = "yes";
			PChar.quest.BSUrka_Curacao_EndSeaBattle.over = "yes";
			PChar.quest.BSUrka_SeaBattleEnded.over = "yes";
		break;

		//Если мы остались верны Флинту, то следующая запись в СЖ: «Осталось самое интересное – делёжка добычи! Пора отправляться на Бермуды»

		//Если мы предаём Флинта, то следующая запись в СЖ: «Вейн в деле, делим добычу и ловим Флинта. Надо постараться оставить его в живых. Пора на Багамы»

		//Если решили не продавать Флинтушку – на глобалке догоняет фиолетовая энка. «Скарборо» линейник первого ранг. С ним пара фрегатов. Никаких диалогов, просто замес в море. По окончанию – запись в СЖ «Скарборо» на дне. Остался только Джекман»

		//Если решили продать, англичан нету, спокойно идём до бермуд.// это важно! Скарборо будет в другом месте 7.04.2023

		//В обоих вариантах – при выходе на локалку Бермуд – атакует эскадра Джекмена. Джекмен на «Нептуне». Бах-бах. Абордируем «Нептуна» файт с Джекменом. Диалог

		//Селим Гатри и Макс в резиденцию, в магаз – рандомного челика.

		//Высаживаемся, идём в резиденцию. ГГ, Флинт, Вейн, Гатри, Макс

		case "BS_NU_50":	//Флинт
            dialog.text = "The gold is being unloaded from the ships into Miss Guthrie's warehouse, and we'll count and divide it as soon as it's done. In the meantime, I suggest we drink to the successful completion of the case! You're the best team I've ever dealt with. Cheers! Bottoms up!";
            link.l1 = "Bottoms up!";
			link.l1.go = "BS_NU_50exit";
		break;

		case "BS_NU_50exit":	//Флинт
			DialogExit();
			BSUrka_Poison();
		break;

		//Типа пьём и валимся с ног все, кроме Флинта, Флинт уходит из резиденции. Нас отравили.

	}
}
