// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question, " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Are we going to ask questions again?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yeah, really for the third time...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.RomanticQuest == "SeekInPortoBello")
			{
				link.l1 = "Listen, don't you know, no one is waiting for the arrival of the brig 'Enthusiastic' here?";
				link.l1.go = "Romantic_1";
			}

			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Listen, have you seen a privateer named Francois Gontier? He was in your city recently.";
                link.l1.go = "Portobello_rat_1";
            }

			if (CheckAttribute(pchar, "questTemp.mushket2x2_stid") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = "Listen, Rolando, do you know where I can find Albert Sievert, captain of the brig 'Arrow'?";
				link.l1.go = "Mushket_stid";
			}

			if (CheckAttribute(pchar, "questTemp.PDM_ONV_PortoBello"))	//Квест "Witch Hunt"
            {
                link.l1 = "Does the name Maria Carle mean anything to you?";
                link.l1.go = "PDM_ONV_PB_1";
            }
		break;

		case "PDM_ONV_PB_1":	//Квест "Witch Hunt"
			dialog.text = "This name doesn't mean anything to me. But you're lucky, that man at the table said that name more than once when he was swallowing rum in a frenzied rage.";
			link.l1 = "How did you help me out. Thank you!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_PortoBello");
			if(InterfaceStates.EnabledQuestsMarks)
			{
				sld = CharacterFromID("PDM_ONV_Viktor_Martos");
				sld.quest.questflag.model = "questionmarkY";
			}
		break;

		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("No, I don't know. He did not go into the tavern, and I did not see him in the city.", "You have already"+ GetSexPhrase("asked", "asked") +"about that, I answered you.", "I'm telling you, you already"+ GetSexPhrase("asked", "asked") +"about this Gontiere.", "Listen, step back and don't get in the way! Are you screw loose?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Well... It aint gotta be easy.", "Yeah, right...", "Yeah, already "+ GetSexPhrase("asked", "asked") +"...", "Sorry, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			break;

		case "Mushket_stid":
			dialog.text = "Wow!.. Ah-ha-ha! Why do you need my best friend, the famous robber Alberto Sievert?!";
			link.l1 = "Needed... I have business with him.";
			link.l1.go = "Mushket_stid_1";
			break;

		case "Mushket_stid_1":
			dialog.text = "Really?! The last one who had a 'case' for him had been eaten by crabs for a long time. He has nothing to do with anyone - a lone psycho, an unhappy greedy man. Only smugglers tolerate it, because the goods are regularly delivered. He does not enter the ports - a one-legged one is waiting for him in each one. Even pirates are hunting him... Did Jackman send you after him, by any chance?";
			link.l1 = "No... He has a little thing that doesn't belong to him, I want to buy it back...";
			link.l1.go = "Mushket_stid_2";
		break;

		case "Mushket_stid_2":
			dialog.text = "Haha! Yes, Sievert doesn't even own his own skin-Jackman swore that he would take it off as soon as he caught him. Although no - the Arrow belongs to him legally - he built it from Alexus with his own money, according to his own drawings. Listen, didn't you put your eye on his boat, huh? And then I keep thinking - what kind of 'business' do you have with him! Just keep in mind - Sievert can easily put you on the bottom before you lower the boat. That's the way he does it-he shoots first, then he talks.";
			link.l1 = "I don't need his brig! Can you just tell me where to find him?";
			link.l1.go = "Mushket_stid_3";
		break;

		case "Mushket_stid_3":
			dialog.text = "He's a lone pirate, hiding in coves, sneaking from island to island, attacking suddenly, so it's not easy to find him... But I wouldn't be a Catalan Fox if I didn't know where he went! So prepare a purse, "+ GetSexPhrase("buddy", "girlfriend") +"!";
			link.l1 = "That's great! And how much do you want for this information?";
			link.l1.go = "Mushket_stid_4";
		break;

		case "Mushket_stid_4":
			dialog.text = "One hundred thousand, buddy! A hundred thousand, right now.";
			if(makeint(Pchar.money) >= 100000)
			{
				link.l1 = "How much?? Are you crazy to ask for such money for two words?!";
				link.l1.go = "Mushket_stid_nopay";
				link.l2 = "No problem, Rolando. Hold your piastres.";
				link.l2.go = "Mushket_stid_paymoney";
			}
			link.l3 = "Listen, but I don't have enough money!";
			link.l3.go = "Mushket_stid_nomoney";
		break;

		case "Mushket_stid_nopay":
			dialog.text = "Don't think of me as a simpleton - his brig is much more expensive. And your story about the 'thing' if you tell a goose in the backyard of a tavern, only the son of a Panamanian shipyard will believe you... If you manage to take possession of the brig, you will thank me again. And if it fails, the dead don't need money, ha ha ha...";
			link.l1 = "Okay, the hell with you. Here you go.";
			link.l1.go = "Mushket_stid_paymoney";
			link.l2 = "Cut the cackle. I can do it without gold. I'll find it myself.";
			link.l2.go = "Mushket_stid_nomoney";
		break;

		case "Mushket_stid_nomoney":
			dialog.text = "Well, it's obviously not your destiny to get the 'Arrow'. I'll wait until someone more respectable is interested in my ex-boyfriend. And there's no point in waiting for you to get rich-he's in one place today and in another tomorrow... So if you want to, you'll find it if you keep your eyes open. And I'm not your assistant.";
			link.l1 = "Well, goodbye, Rolando. Don't worry, I'll bring your money...";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "5");
		break;

		case "Mushket_stid_paymoney":
			AddMoneyToCharacter(Pchar, -100000);
			SetMushketCapitainInWorld();
			dialog.text = "Oh, I got a"+ GetSexPhrase("a generous friend", "a generous friend") +"! I even began to wonder if I had sold out! Well, come on - what you won't do for the sake of selfless friendship... Now listen: he recently went to a bay called Mosquitos. He won't be there for long - he'll unload and leave, so hurry up and fly faster than the wind, hehe... If not, then you will have to search for him by yourself. I glad to help you, as a sign of our friendship, but he doesn't tell me his routes.";
			link.l1 = "Thank you, Fox! I'm moving out immediately.";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "4");
			//AddQuestUserData("SeekDoubleMushket", "sShore", XI_ConvertString(pchar.questTemp.Mushket.Shore));
			DeleteAttribute(pchar, "questTemp.mushket2x2_stid");
		break;

		case "Romantic_1":
            dialog.text = "No, no one asked me.";
            link.l1 = "Understood... Tell me, does anyone rent a room from you?";
			link.l1.go = "Romantic_2";
		break;
		case "Romantic_2":
            dialog.text = "No, " + GetAddress_Form(pchar) + ", It's empty.";
            link.l1 = "Clear... Well, thank you.";
			link.l1.go = "exit";
			pchar.RomanticQuest = "ToRositaInBeliz";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SetMushketCapitainInWorld()
{
	//создаём кэпов
	int Rank = sti(pchar.rank) + 15;
	if (Rank > 30) Rank = 30;
	if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) ref sld = GetCharacter(NPC_GenerateCharacter("MushketCap", "officer_17", "man", "man_fast", Rank, PIRATE, -1, true));
	else sld = GetCharacter(NPC_GenerateCharacter("MushketCap", "officer_17", "man", "man", Rank, PIRATE, -1, true));
	sld.name = "Albert";
	sld.lastname = "Sievert";
 	SetCaptanModelByEncType(sld, "pirate");
	FantomMakeCoolSailor(sld, SHIP_VALCIRIA, "Arrow", CANNON_TYPE_CANNON_LBS20, 100, 100, 100);
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade34", "pistol2", 50);
	sld.Ship.Mode = "pirate";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	sld.WatchFort = true; //видеть форты
	if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "MushketCapShip";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.city = "SantaCatalina"; //определим колонию, из бухты которой с мушкетом выйдет
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = "PortoBello"; //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = "Shore47";
	pchar.questTemp.Mushket.Shore = sld.quest.targetShore;
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Brig 'Arrow'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city)) + 1; //дней доехать даём с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);

	Log_TestInfo("Cap with a musket came out of: " + sld.cityShore + " and headed to: " + sld.quest.targetShore);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "mushket"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = "SeekDoubleMushket"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SeekDoubleMushket"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 2;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
