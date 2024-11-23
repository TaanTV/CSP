
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int iRang = sti(PChar.rank);
	float fRandom = FRAND(1) + 1;

	float fLuck = GetCharacterSkillToOld(PChar, SKILL_FORTUNE);
	if(fLuck < 1.1) { fLuck = 1.1; }
	fLuck /= 10;

	int iMoney = iRang * 500 * fLuck * fRandom + drand(100);
	if(iMoney < 500) { iMoney = 500 + drand2(100); }
	if(iMoney > 10000) { iMoney = 9900 + drand2(100); }

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "There's nothing to talk about.";
			link.l1 = "Okay...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//--------------------------- линейка ГПК --------------------------------
		//заказчик устранения всех нищих
		case "Begin_PoorKill":
			dialog.text = "Good afternoon, Captain. Would you mind talking to me about a case?";
			link.l1 = "Why not talk? With pleasure!";
			link.l1.go = "Begin_PoorKill_1";
		break;

		case "Begin_PoorKill_close":
			dialog.text = "Hmm, I see... Well, it's a pity.";
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterReputation(pchar, 10);
			pchar.questTemp.LSC = "PoorIsGood";
			SetQuestHeader("ISS_PoorsMurder");
			AddQuestRecord("ISS_PoorsMurder", "12");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("ым", "ой"));
		break;

		case "Begin_PoorKill_1":
			dialog.text = "Great! You can immediately see a business person.";
			link.l1 = "Get to the point, my dear.";
			link.l1.go = "Begin_PoorKill_2";
		break;
		case "Begin_PoorKill_2":
			dialog.text = "Ha-ha, I like your grip!  Well, first I suggest you meet. My name is " + GetFullName(npchar) + "I'm sorry, but I've made inquiries about you and I know you're the captain " + GetFullName(pchar) + ". I also know that you are a privateer. Is that so?";
			link.l1 = "That's right. You are well informed about me. And who are you by the nature of your work?";
			link.l1.go = "Begin_PoorKill_3";
		break;
		case "Begin_PoorKill_3":
			dialog.text = "I'm a business person, let's just say.";
			link.l1 = "That's fine. And what business do you have with me?";
			link.l1.go = "Begin_PoorKill_4";
		break;
		case "Begin_PoorKill_4":
			dialog.text = "Yes, actually, it's nothing for "+ GetSexPhrase("such a brave man", "such a brave girl") +" like you. The fact is that my employer is seriously concerned about the state of morality and morality in the Caribbean Islands. Yes, that's right!";
			link.l1 = "Glad for your employer. However, I'm not a good moralist...";
			link.l1.go = "Begin_PoorKill_5";
		break;
		case "Begin_PoorKill_5":
			dialog.text = "But the 'forest orderly' will be wonderful!";
			link.l1 = "What are you talking about? I repeat: get to the point, my dear...";
			link.l1.go = "Begin_PoorKill_6";
		break;
		case "Begin_PoorKill_6":
			dialog.text = "Well, all right. I need you to get rid of the beggars and beggars in the cities. And everywhere, in every city, regardless of nationality. We are ready to pay you a million piastres for this work!";
			link.l1 = "Heh, it's tempting. A million is not lying on the road...";
			link.l1.go = "Begin_PoorKill_7";
			link.l2 = "Who do you take me for? For a bountyhunter?! Get out of here, buddy, while you're safe...";
			link.l2.go = "Begin_PoorKill_close";
		break;
		case "Begin_PoorKill_7":
			dialog.text = "Million doesn't grow on trees either, my dear, hehe...";
			link.l1 = "You're a joker, I see! Let's discuss the terms of the deal.";
			link.l1.go = "Begin_PoorKill_8";
		break;
		case "Begin_PoorKill_8":
			dialog.text = "With pleasure! So, I'm making a contribution of a million piastres in your name from a usurer, well, let's say this city. The deposit. After completing the task, you can take this money away.";
			link.l1 = "And the advance? I will need to travel a lot.";
			link.l1.go = "Begin_PoorKill_9";
		break;
		case "Begin_PoorKill_9":
			dialog.text = "I'm sorry, but an advance is out of the question. This is completely unacceptable.";
			link.l1 = "Hmm, that's sad... And the timing? Am I somehow limited in time?";
			link.l1.go = "Begin_PoorKill_10";
		break;
		case "Begin_PoorKill_10":
			dialog.text = "Practically not. Just do it and get your million. I guess you won't be stalling, hehe...";
			link.l1 = "Hmm, then let's get to work. Where and when can I verify the availability of a deposit in my name?";
			link.l1.go = "Begin_PoorKill_11";
		break;
		case "Begin_PoorKill_11":
			dialog.text = "At the local usurer's, today. And you will be able to collect your million upon my notification. When I don't see beggars on the streets of cities, I will immediately let the usurer know about your fulfillment of obligations.";
			link.l1 = "Well, then it's a deal!";
			link.l1.go = "Begin_PoorKill_12";
		break;
		case "Begin_PoorKill_12":
			dialog.text = "Well, that's fine. Well, we won't see you again, goodbye. I am glad that your consent to this work has been received. I hope to complete the assignment as soon as possible.";
			link.l1 = "Goodbye. By the way, what kind of employer is this, who is so hampered by these ragamuffins?";
			link.l1.go = "Begin_PoorKill_13";
		break;
		case "Begin_PoorKill_13":
			dialog.text = "I'm sorry, but I can't say that.";
			link.l1 = "Hmm, well, okay. Goodbye...";
			link.l1.go = "Begin_PoorKill_14";
		break;
		case "Begin_PoorKill_14":
			SetQuestHeader("ISS_PoorsMurder");
			AddQuestRecord("ISS_PoorsMurder", "1");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ISS_PoorsMurder", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			pchar.quest.ISS_Murder1.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder1.win_condition.l1.character = "SentJons_Poorman";
			pchar.quest.ISS_Murder1.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder2.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder2.win_condition.l1.character = "Bridgetown_Poorman";
			pchar.quest.ISS_Murder2.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder3.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder3.win_condition.l1.character = "Beliz_Poorman";
			pchar.quest.ISS_Murder3.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder4.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder4.win_condition.l1.character = "Caracas_Poorman";
			pchar.quest.ISS_Murder4.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder5.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder5.win_condition.l1.character = "Cartahena_Poorman";
			pchar.quest.ISS_Murder5.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder6.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder6.win_condition.l1.character = "Cumana_Poorman";
			pchar.quest.ISS_Murder6.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder7.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder7.win_condition.l1.character = "BasTer_Poorman";
			pchar.quest.ISS_Murder7.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder8.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder8.win_condition.l1.character = "Havana_Poorman";
			pchar.quest.ISS_Murder8.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder9.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder9.win_condition.l1.character = "PortRoyal_Poorman";
			pchar.quest.ISS_Murder9.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder10.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder10.win_condition.l1.character = "FortFrance_Poorman";
			pchar.quest.ISS_Murder10.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder11.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder11.win_condition.l1.character = "Charles_Poorman";
			pchar.quest.ISS_Murder11.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder12.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder12.win_condition.l1.character = "PortoBello_Poorman";
			pchar.quest.ISS_Murder12.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder13.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder13.win_condition.l1.character = "PortPax_Poorman";
			pchar.quest.ISS_Murder13.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder14.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder14.win_condition.l1.character = "Santiago_Poorman";
			pchar.quest.ISS_Murder14.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder15.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder15.win_condition.l1.character = "Marigo_Poorman";
			pchar.quest.ISS_Murder15.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder16.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder16.win_condition.l1.character = "Tortuga_Poorman";
			pchar.quest.ISS_Murder16.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder17.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder17.win_condition.l1.character = "PortSpein_Poorman";
			pchar.quest.ISS_Murder17.function = "ISS_MurderSignExecute";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "SignOnPoorMurder";
			pchar.questTemp.LSC.killCost = 17; //счётчик убитых нищих на декремент
			pchar.questTemp.LSC.usurerId = npchar.city + "_usurer"; //флаг на депозит у ростовщика
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "gate_back", "none", "", "", "CanFightCurLocation", -1);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			chrDisableReloadToLocation = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//воришка ключа
		case "GiveKeyMan":
			dialog.text = "What?";
			link.l1 = "Hmm, listen, are you the Master of Keys?";
			link.l1.go = "GiveKeyMan_1";
		break;
		case "GiveKeyMan_1":
			dialog.text = "Yes, I am. Who are you?";
			link.l1 = "My name is Captain " + GetFullName(pchar) + ".";
			link.l1.go = "GiveKeyMan_2";
		break;
		case "GiveKeyMan_2":
			dialog.text = "And what do you need, Captain " + GetFullName(pchar) + "?";
			link.l1 = "Listen, did you make the chests in Governor General Stuyvesant's house? I want to order one for myself, with a lock.";
			link.l1.go = "GiveKeyMan_3";
		break;
		case "GiveKeyMan_3":
			dialog.text = "I did the one with the lock. And I can say without exaggeration that you have turned at the address. I am the most famous Master of Keys! True, I have a namesake-a narrow-eyed bastard, but he's no match for me. So I am the real Master of Keys!";
			link.l1 = "Well, great! So that's what I want. I need exactly the same chest as the Governor General's.";
			link.l1.go = "GiveKeyMan_4";
		break;
		case "GiveKeyMan_4":
			dialog.text = "Heh, I don't make identical chests-it's not a manufactory, you know! I have every piece of work. And where has it been seen, to put identical locks? After all, the keys will fit.";
			link.l1 = "You know, buddy, this is what I'm talking about...";
			link.l1.go = "GiveKeyMan_5";
		break;
		case "GiveKeyMan_5":
			dialog.text = "Ha! You are a difficult customer, as I see...";
			link.l1 = "That's right, my friend!!! For a difficult order, a difficult fee...";
			link.l1.go = "GiveKeyMan_6";
		break;
		case "GiveKeyMan_6":
			dialog.text = "A difficult fee, you say? I take it you only need the key.";
			link.l1 = "That's right.";
			link.l1.go = "GiveKeyMan_7";
		break;
		case "GiveKeyMan_7":
			npchar.quest.price = makeint((6666 * ((sti(pchar.rank))/2.0)*MOD_SKILL_ENEMY_RATE*3*(100-(GetCharacterSkill(pchar, SKILL_LEADERSHIP)/2)))/100);
			if (sti(pchar.money) >= sti(npchar.quest.price))
			{
				dialog.text = "Mmm... Good! I want " + FindRussianMoneyString(sti(npchar.quest.price)) + " for this key.";
				link.l1 = "Carramba, not a bad price!";
				link.l1.go = "GiveKeyMan_10";
			}
			else
			{
				dialog.text = "Ho-oh-oh, "+ GetSexPhrase("Buddy, you're a sucker.", "Girlfriend, you're hungry.") +"!!! What kind of fees can I talk to you about?! You know, whoever has the wind whistling in his pockets is not my client. And where did I look before?";
				link.l1 = "What does this mean?!";
				link.l1.go = "GiveKeyMan_8";
			}
		break;
		case "GiveKeyMan_8":
			dialog.text = "It means, "+ GetSexPhrase("buddy", "girlfriend") +", that even my usual services are beyond your means, let alone special ones. Come as soon as you earn piastres, but now don't bother me.";
			link.l1 = "Okay, I'll find you later...";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toMasterKeysNoMoney";
			NextDiag.TempNode = "GiveKeyMan_NoMoney";
		break;
		case "GiveKeyMan_NoMoney":
			npchar.quest.price = makeint((6666 * ((sti(pchar.rank))/2.0)*MOD_SKILL_ENEMY_RATE*3*(100-(GetCharacterSkill(pchar, SKILL_LEADERSHIP)/2)))/100);
			if (sti(pchar.money) >= sti(npchar.quest.price))
			{
				dialog.text = "Well, that's better, as they say... Let's get back to our conversation about the key. In general, I'm ready to make it for you, let's say, for " + FindRussianMoneyString(sti(npchar.quest.price)) + ".";
				link.l1 = "Hehe, not bad!!";
				link.l1.go = "GiveKeyMan_10";
			}
			else
			{
				dialog.text = "Don't even bother me with your suggestions. You don't have enougth. I don't need such clients.";
				link.l1 = "Hmm, I'll help you with some more money.";
				link.l1.go = "exit";
			}
		break;
		case "GiveKeyMan_10":
			dialog.text = "I'm not used to being petty. You see, I'm the Master of Keys! In general, fork out and be done with it. There is no other way!";
			link.l1 = "Hmm, it looks like there's definitely nowhere to go... listen, maybe you can cut the price?";
			link.l1.go = "GiveKeyMan_11";
		break;
		case "GiveKeyMan_11":
			dialog.text = "No, "+ GetSexPhrase("buddy", "girlfriend") +". Yyou know what you're asking...";
			link.l1 = "Take it. Where is my key?";
			link.l1.go = "GiveKeyMan_12";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
		break;
		case "GiveKeyMan_12":
			dialog.text = "It needs to be manufactured. Come to me in two days. I live in a house near the stairs to the church.";
			link.l1 = "Good.";
			link.l1.go = "exit";
			SetTimerFunction("LSC_openMasterHouse", 0, 0, 2);
			LocatorReloadEnterDisable("Villemstad_town", "houseSp5", true);
			npchar.location = "none";
			AddQuestRecord("ISS_PoorsMurder", "6");
		break;

		case "GiveKeyManInside":
			dialog.text = "Yeah, there you are!";
			link.l1 = "Yeah, here I am! Where is my key?";
			link.l1.go = "GiveKeyManInside_1";
		break;
		case "GiveKeyManInside_1":
			dialog.text = "The key? Hmm, you know, I hate to say this, but the Governor General really wants to talk to you.";
			link.l1 = "Did you rat out, you brat?!";
			link.l1.go = "GiveKeyManInside_2";
		break;
		case "GiveKeyManInside_2":
			dialog.text = "And how did you want to ? I'm not my own enemy... In general, there are soldiers here, they will escort you...";
			link.l1 = "Oh, you parasite! Why did you take the money then?!";
			link.l1.go = "GiveKeyManInside_3";
		break;
		case "GiveKeyManInside_3":
			dialog.text = "Let's get to work. I did the key, as promised. I keep my word!";
			link.l1 = "Well, well...";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("LSC_enterSoldiers");
		break;
		//арестовывающий офицер
		case "MK_HollOfficer":
			dialog.text = "Come with me, Captain!";
			link.l1 = "Where is it going?";
			link.l1.go = "MK_HollOfficer_1";
		break;
		case "MK_HollOfficer_1":
			dialog.text = "To the temporary detention center. Until we find out, so to speak... And don't try to fool around, otherwise I'll be forced to use force!";
			link.l1 = "Eh, Officer, the trouble is that I'll have to, use force too...";
			link.l1.go = "MK_HollOfficer_2";
		break;
		case "MK_HollOfficer_2":
			LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_houseSp5")], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//заказчик нищих в Мариго
		case "PKInMarigo":
			dialog.text = "Hmm, I wasn't planning on meeting you again! Have you completed the task yet? Problems with the deposit?";
			link.l1 = "No, the deposit is fine. You know, the thing is, I can't find one of tramps - Teaser Dan.";
			link.l1.go = "PKInMarigo_1";
		break;
		case "PKInMarigo_1":
			dialog.text = "Don't worry about him, you won't find him anymore. Take care of the others.";
			link.l1 = "I see... But still, where's Teaser?";
			link.l1.go = "PKInMarigo_2";
		break;
		case "PKInMarigo_2":
			dialog.text = "Am I talking vaguely? Teaser Dan is not included in the application list. Do you understand me?";
			link.l1 = "I understand, of course. But still, I'd really like to know where he is.";
			link.l1.go = "PKInMarigo_3";
		break;
		case "PKInMarigo_3":
			dialog.text = "I don't like your persistence. If you keep this up, you'll follow Teaser straight.";
			link.l1 = "So he's dead...";
			link.l1.go = "PKInMarigo_4";
		break;
		case "PKInMarigo_4":
			dialog.text = "It can't be deader. And now please explain yourself regarding your curiosity!";
			link.l1 = "Good. I know that you are the representative of the Dutch West India Company in the Caribbean. I also know that you do business with Governor General Stuyvesant. And I also want to know why the hell you didn't like the local tramps.";
			link.l1.go = "PKInMarigo_5";
		break;
		case "PKInMarigo_5":
			dialog.text = "Don't you want too much?";
			link.l1 = "These are not all my questions to you. I want to know about the Island!";
			link.l1.go = "PKInMarigo_6";
		break;
		case "PKInMarigo_6":
			dialog.text = "Do you have any idea what you're getting into, Captain? Swim in your health, pinch individual traders - that's okay. But meddling with a company that owns the entire Indian Ocean is insane.\n"+
				"Fulfill your obligations, withdraw the deposit - and continue to play tricks on your health, no one will touch you. But your curiosity will very quickly lead you to the grave. I'm giving you one last chance, Captain, to leave here in peace.";
			link.l1 = "I don't think I'm going to take this chance. I also want to know about the luxury goods that you are so afraid of falling prices for...";
			link.l1.go = "PKInMarigo_7";
		break;
		case "PKInMarigo_7":
			dialog.text = "Uh-uh, Captain, I'm afraid your song is sung. As one of my friends, now deceased, said: 'I knew too much...'.";
			link.l1 = "So what are you going to do, West Indian ferret?";
			link.l1.go = "PKInMarigo_8";
		break;
		case "PKInMarigo_8":
			dialog.text = "I'll kill you. And right now! Security!!!";
			link.l1 = "Don't lose your knickers when you kill...";
			link.l1.go = "PKInMarigo_9";
		break;
		case "PKInMarigo_9":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(loadedLocation, false);

			TeleportCharacterToLocator(npchar, "goto", "goto3");
			LAi_group_Delete("OliverTrust");
			LAi_group_MoveCharacter(npchar, "OliverTrust");

			for (int i = 1; i <= 2; i++)
			{
				ref sld = SetFantomOfficer("reload", "reload1", HOLLAND, "");
				// FantomMakeCoolFighter(sld, 40, 100, 100, "blade28", "pistol4", 200 + 10 * MOD_SKILL_ENEMY_RATE*3); // annoer, я всё понимаю, но это ебля без вазелина уже (LEO)
				FantomMakeCoolFighter(sld, sti(Pchar.rank), 25+drand(50), 25+drand(50), "blade31", "pistol2", 20/*  + 10 * MOD_SKILL_ENEMY_RATE*3 */);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "OliverTrust");
			}

			LAi_group_SetHearRadius("OliverTrust", 100.0);
			LAi_group_SetRelation("OliverTrust", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("OliverTrust", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("OliverTrust", "OpenTheDoors");

            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//мент в Протекторе
		case "LSCQuestMent":
			dialog.text = "Well, tell me, what's your news?";
			link.l1 = "What are you talking about?";
			link.l1.go = "LSCQuestMent_1";
		break;
		case "LSCQuestMent_1":
			dialog.text = "Stop pretending! Andre told me all about your hints.";
			link.l1 = "What an idiot!..";
			link.l1.go = "LSCQuestMent_2";
		break;
		case "LSCQuestMent_2":
			dialog.text = "Andre Labor is a law-abiding citizen of the city. But you'll have to tell me all about Teaser Dan, or the Admiral will be looking after you tomorrow.";
			link.l1 = "So he doesn't know yet? Why, it's wonderful!.. Hmm, I'm afraid you'll have to die.";
			link.l1.go = "LSCQuestMent_3";
		break;
		case "LSCQuestMent_3":
			dialog.text = "What?!! Andre, come to me!";
			link.l1 = "Huh, so the carpenter is on the lookout? And that's great too!";
			link.l1.go = "LSCQuestMent_4";
		break;
		case "LSCQuestMent_4":
			AddQuestRecord("ISS_MainLine", "9");
			pchar.questTemp.LSC = "afterFightInProtector";
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetWarriorTypeNoGroup(npchar);
			sld = characterFromId("AndreLabor");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//одиночный нарвал, которого надо замочить
		case "LSCQuestNarval":
			dialog.text = "What are you doing here?!";
			link.l1 = "Me? Well, how can I tell you...";
			link.l1.go = "LSCQuestNarval_1";
		break;
		case "LSCQuestNarval_1":
			dialog.text = "Are you fool? Don't you know that this is narwhal territory?";
			link.l1 = "Yes, I know...";
			link.l1.go = "LSCQuestNarval_2";
		break;
		case "LSCQuestNarval_2":
			dialog.text = "Are you crazy? Are you looking for death?";
			link.l1 = "Well, yes... Only your death. I'm sorry, buddy, but I'm going to have to kill you.";
			link.l1.go = "LSCQuestNarval_3";
		break;
		case "LSCQuestNarval_3":
			AddQuestRecord("ISS_MainLine", "11");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся", "ась"));
			pchar.questTemp.LSC = "toAdmNarvalRing";
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//--------------------------- дача шебеки Синяя Птица --------------------------------
		//капитан шебеки Синяя Птица
		case "SharpCapitain":
			dialog.text = "What the hell are you doing, "+ GetFullName(pchar) + "?";
			link.l1 = "Nothing personal, just business. I've been offered a generous reward for covering up your shop.";
			link.l1.go = "SharpCapitain_1";
			link.l2 = "To hell with talking, defend yourself!";
			link.l2.go = "SharpCapitain_fight";
		break;

		case "SharpCapitain_1":
			dialog.text = "The devil... You don't understand anything, after just a few trips to get pearls, you would be many times richer than from any one-time payment from your employer. But now it's too late, without an informant, the tartans of the pearl fishermen are forever lost to us...";
			link.l1 = "Forget about the pearls, this little thing is not worth your attention. I know of more profitable sources of income. Join my team and you will bathe in riches!";
			link.l1.go = "SharpCapitain_2";
			link.l2 = "To hell with talking, defend yourself!";
			link.l2.go = "SharpCapitain_fight";
		break;

		case "SharpCapitain_2":
			dialog.text = "In my current position, it would be foolish to refuse... Wealth, you say? Well, I'm at your service, Captain!";
			link.l1 = "Welcome to the team, corsair!";
			link.l1.go = "Sharp_hired";
		break;

		case "Sharp_hired":
			bQuestDisableMapEnter = false;
			characters[GetCharacterIndex("Sharp")].lifeDay = 0;
			sld = GetCharacter(NPC_GenerateCharacter("SharpOf", "Sharp", "man", "man", 20, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 30, 70, 70, "blade25", "pistol6", 120);
			sld.name = "Bartholomew";
			sld.lastname = "Sharp";
			sld.greeting = "Gr_Officer";
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // Контузия
			//SetSelfSkill(sld, 30, 30, 30, 30, 30);
			//SetShipSkill(sld, 30, 50, 30, 35, 80, 35, 30, 35, 30);
			SetSelfSkill(sld, 40, 40, 40, 40, 40);
			SetShipSkill(sld, 50, 50, 50, 50, 60, 40, 30, 40, 30);
			SetSPECIAL(sld, 6, 6, 8, 5, 8, 8, 10);
			LAi_SetHP(sld, 200.0, 200.0);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			AddItems(sld, "talisman11", 1);
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle();
            DialogExit();
		break;

		case "SharpCapitain_fight":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			Npchar.SaveItemsForDead = true;
		break;

		case "PGG_cabin":
			LAi_SetCurHPMax(npchar);
			ref chr = CharacterFromID(npchar.CaptanId);
			chr.willDie = true;
			dialog.text = "Soon you will be feeding the fish, "+ GetFullName(pchar) + "! I guarantee it to you!";
			link.l1 = "You and I are colleagues, why should we kill each other for nothing? Maybe we should join forces?";
			link.l1.go = "PGG_cabin_1";
			link.l2 = "Self-confidence will lead you to the grave. Defend yourself!";
			link.l2.go = "PGG_cabin_fight";
		break;

		case "PGG_cabin_1":
			int hirePrice = sti(npchar.rank) * 10000 + 100000;
			npchar.hirePrice = hirePrice;
			dialog.text = "Swimming with you? I'd rather die\nAlthough, there is always time for this. Perhaps I will go with you if you are able to satisfy my appetite. First I want "+npchar.hirePrice+" piastres, here and now.";
			if(makeint(Pchar.money) >= sti(npchar.hirePrice))
			{
				link.l1 = "What an appetite you have. But so be it, I agree. Here's your money.";
				link.l1.go = "PGG_cabin_2";
			}
			else
			{
				link.l1 = "How much?! I've never seen so much money in my life. It's cheaper for me to kill you!";
				link.l1.go = "PGG_cabin_fight";
			}
			link.l2 = "Self-confidence, and even greed. No, you and I won't find a common language. Defend yourself!";
			link.l2.go = "PGG_cabin_fight";
		break;
		case "PGG_cabin_2":
			dialog.text = "Damn it, I should have demanded more... But the contract is more expensive than money, I am at your service.";
			AddMoneyToCharacter(Pchar, -sti(npchar.hirePrice));
			link.l1 = "Welcome to the team!";
			link.l1.go = "PGG_hired";
		break;

		case "PGG_hired":
			bQuestDisableMapEnter = false;
			chr = CharacterFromID(npchar.CaptanId);
			Restore_PGG(chr);
			sld = GetCharacter(NPC_GenerateCharacter(npchar.CaptanId+"Of", "none", chr.sex, chr.model.animation, 1, PIRATE, -1, false));
			ChangeAttributesFromCharacter(sld, chr, true);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			if (sld.sex != "woman")
			{
				sld.greeting = "Gr_Officer";
			}
			else
			{
				if(rand(1) == 0)
				{
					sld.greeting = "Gr_Danielle";
				}
				else
				{
					sld.greeting = "GR_marycasper";
				}
			}
			if (sld.model.animation == "man") sld.CanTakeMushket = true;
			if (HasSubStr(sld.model, "Whisper"))
			{
				sld.CanTakeMushket = true;
				if(sld.model == "PGG_Whisper_6") EquipCharacterByItem(sld, "suit_1");
			}
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			sld.HoldEquip = true;
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			QuestAboardCabinDialogNotBattle();
            DialogExit();
		break;

		case "PGG_cabin_fight":
				QuestAboardCabinDialogExitWithBattle("");
				DialogExit();
				AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "zpqCapitain":
			dialog.text = "I can go on like this for a whole day. Give me the money for the gunpowder, "+ GetFullName(pchar) + ", if you want to live.";
			if(makeint(Pchar.money) >= 300000)
			{
				link.l1 = "Your ship has been captured, and the entire crew has been killed. But you fight pretty well. I'm thinking of saving your life and even giving you money for gunpowder if you go swimming under my command. Either...";
				link.l1.go = "zpqCapitain_1";
			}

			link.l2 = "And you haven't seen such menacing ones! You'll only get a blade between your ribs from me!";
			link.l2.go = "zpqCapitain_fight";
		break;

		case "zpqCapitain_1":
			dialog.text = "There is no need to continue. I can't leave here alive anyway. I agree.";
			AddMoneyToCharacter(Pchar, -300000);
			link.l1 = "Welcome to the team, corsair!";
			link.l1.go = "zpq_hired";
		break;

		case "zpq_hired":
			bQuestDisableMapEnter = false;
			characters[GetCharacterIndex(npchar)].lifeDay = 0;
			sld = GetCharacter(NPC_GenerateCharacter("zpqCaptainOf", "Lil_Jim_0", "man", "man", 25, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 25, 105, 105, "blade23", "pistol3", 120);
			sld.name 	= "Small";
			sld.lastname = "Jimmy";
			sld.greeting = "Gr_Officer";

			sld.rank = 25;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // Контузия
			sld.HeroModel = "Lil_Jim_0,Lil_Jim_1,Lil_Jim_2,Lil_Jim_3,Lil_Jim_4,Lil_Jim_5";
			SetSelfSkill(sld, 80, 80, 75, 80, 80);
			SetShipSkill(sld, 60, 75, 75, 75, 65, 70, 70, 60, 70);
			SetSPECIAL(sld, 9, 9, 10, 10, 8, 10, 10);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "Ciras");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			//SetCharacterPerk(sld, "Medic");
			AddItems(sld, "talisman13", 1);
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle();
            DialogExit();
		break;

		case "zpqCapitain_fight":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			Npchar.SaveItemsForDead = true;
		break;

		case "BlueBirdCapitain":
			dialog.text = "I wish I knew who you are...";
			link.l1 = "My name is " + GetFullName(pchar) + ". I'm a privateer.";
			link.l1.go = "BlueBirdCapitain_1";
		break;
		case "BlueBirdCapitain_1":
			dialog.text = "And what the hell did you attack my xebec?!!";
			link.l1 = "This is an order, I owe to sink you to the bottom. You've ruined your relationship with the merchants too much...";
			link.l1.go = "BlueBirdCapitain_2";
		break;
		case "BlueBirdCapitain_2":
			dialog.text = "And this is a privateer talking?! I guess you probably don't like merchants either...";
			link.l1 = "It's a job, buddy, nothing personal. Tell me better, how do you and Pascal keep in touch? You have no idea how hard it was to find you.";
			link.l1.go = "BlueBirdCapitain_3";
		break;
		case "BlueBirdCapitain_3":
			dialog.text = "None of your business, carramba! Thank you for a little respite, and now let's continue!";
			link.l1 = "Well, all right...";
			link.l1.go = "BlueBirdCapitain_4";
		break;

			case "BlueBirdCapitain_4":
			dialog.text = "Wait... Listen, I'll offer you something else. I've lost, it's over, let me go, huh?! And maybe I'll put in a good word for you to the employer! You have no idea what you're into!" ;
			link.l1 = "Uh no, mate. Ends, as they say, in the water! It's nothing personal, business is business.";
			link.l1.go = "BlueBirdCapitain_5";
			/*link.l2 = "Ha! That's interesting! And you know, Ja- I agree. We still need to look for an officer like you. But look - if you decide to make jokes, I'll send you overboard in a jiffy!";
			link.l2.go = "BlueBirdCapitain_6";*/
		break;

		case "BlueBirdCapitain_6":
			dialog.text = "The warning is unnecessary, Captain. For me, now the safest place in the archipelago is your boat. Don't doubt me. I'm glad we have an agreement.";
			link.l1 = "Welcome to the team, corsair!";
			link.l1.go = "Ja_hired";
		break;

		case "Ja_hired":
			bQuestDisableMapEnter = false;
			characters[GetCharacterIndex("Jafar")].lifeDay = 0;
			sld = GetCharacter(NPC_GenerateCharacter("Jafarry", "QuestCaptain", "man", "man", 25, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 25, 70, 70, "blade14", "pistol6", 100);
			sld.name = "Ja";
			sld.lastname = "Preston";
			sld.greeting = "Gr_Officer";
			sld.rank = 25;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // Контузия
			sld.HeroModel = "QuestCaptain,QuestCaptain_1,QuestCaptain_2,QuestCaptain_3,QuestCaptain_4,QuestCaptain_5";
			SetSelfSkill(sld, 80, 80, 75, 80, 80);
			SetShipSkill(sld, 60, 50, 60, 60, 65, 70, 60, 60, 60);
			SetSPECIAL(sld, 9, 9, 10, 10, 8, 10, 10);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "Ciras");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			//SetCharacterPerk(sld, "Medic");
			AddItems(sld, "talisman14", 1);
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle();
            DialogExit();
		break;

		case "BlueBirdCapitain_5":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//капитаны флейтов торговцев
		case "BlueBirdTrader":
			dialog.text = "Damn it, why did you attack us?!!";
			link.l1 = "This is retribution for your master, buddy. I have nothing against you.";
			link.l1.go = "BlueBirdTrader_1";
		break;
		case "BlueBirdTrader_1":
			dialog.text = "It's good to hear...";
			link.l1 = "Now you take the boat, and with the rest of the crew you can return to the owner. Tell him that " + GetFullName(pchar) + " sends him " + GetSexPhrase("his","her") + " regards.";
			link.l1.go = "BlueBirdTrader_2";
		break;
		case "BlueBirdTrader_2":
			dialog.text = "I'll definitely give him your regards.";
			link.l1 = "Then that's it. Live for now...";
			link.l1.go = "BlueBirdTrader_3";
		break;
		case "BlueBirdTrader_3":
			QuestAboardCabinDialogNotBattle();
            DialogExit();
		break;
		//--------------------------- жемчужный промысел, Шарп --------------------------------
		//капитан Шарп, первый базар на палубе
		case "DeckSharp":	//на палубе
			dialog.text = ""+ GetSexPhrase("Hello, buddy. To what do I owe the pleasure of seeing you on my brig", "Ho-oh, what guests we have! To what do I owe the pleasure of seeing you on my brig, beautiful Amazon") +"?";
			link.l1 = "Greetings to Captain Bartholomew Sharp! I hardly found you...";
			link.l1.go = "DeckSharp_1";
			npchar.quest.meeting = true;
			//блокировка генератора, если взят грабёж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = ""+ GetSexPhrase("Buddy", "Girlfriend") +"I'm busy right now! I can't help you with anything. No offense...";
				link.l1 = "All right, buddy...";
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "DeckSharp_1":
			dialog.text = "Yes, it's not easy... So what brings you to me?";
			link.l1 = "You know, buddy, I want to visit the pearl fisheries. To earn extra money, so to speak...";
			link.l1.go = "DeckSharp_2";
		break;
		case "DeckSharp_2":
			dialog.text = "Oh, my soul mate!!! So what's the problem? Come visit!";
			link.l1 = "The problem is that I do not know where they are fishing. They are very secretive and move around all the time! I came to you for advice as an expert in this matter.";
			link.l1.go = "DeckSharp_3";
		break;
		case "DeckSharp_3":
			dialog.text = "Yeah, well, pearl catchers are tricky these days, you can't pick 'em up with your bare hands\nWell, I'll help you for the first time, give you a tip on the fishing.";
			link.l1 = "Oh, Sharp, my friend, thank you!";
			link.l1.go = "DeckSharp_4";
		break;
		case "DeckSharp_4":
			dialog.text = "Well, don't thank me enough\nAnyway, listen to our strategy. So, pearl fishermen behave very carefully, they trade only from uninhabited islands or away from the curious, so to speak. \nPack have to take them warm, just when they are at sea!";
			link.l1 = "Listen, how do you know where they're fishing at the moment?";
			link.l1.go = "DeckSharp_5";
		break;
		case "DeckSharp_5":
			dialog.text = "This is my big secret. I won't tell anyone. "+ GetSexPhrase("", "Even to a cutie like you. ") +"Don't even ask!";
			link.l1 = "Hmm, well, whatever you want...";
			link.l1.go = "DeckSharp_6";
		break;
		case "DeckSharp_6":
			GetPerlShore(); //где промысел ведётся
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Sharp.PearlAreal.add")) sTemp = pchar.questTemp.Sharp.PearlAreal.add;
			dialog.text = "So listen up. There is on " + XI_ConvertString(pchar.questTemp.Sharp.PearlAreal + "Voc") + " a place called " + GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt") +
				sTemp + ". If you get there in " + FindRussianDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms)) + "Then the pearl fishers will be there.";
			link.l1 = "I understand. Thank you, Bartholomew.";
			link.l1.go = "DeckSharp_7";
		break;
		case "DeckSharp_7":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Call me Captain Sharp! I like it better that way.", "Just Barty to you, beautiful.") +".", ""+ GetSexPhrase("I prefer to be called Captain Sharp.", "For a cutie like you, it's just Barty.") +"!");
			link.l1 = "Hmm, I see. Thank you, "+ GetSexPhrase("Captain Sharp", "Barty") +". You helped me a lot!";
			link.l1.go = "DeckSharp_8";
		break;
		case "DeckSharp_8":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("You're welcome, buddy, if you need anything, contact...", "Contact me again, my beauty. Or maybe we'll meet sometime, so to speak, in an informal setting?") +"", ""+ GetSexPhrase("Helping colleagues is a sacred duty, so to speak... Come in again, I'll help you!", "Come in again, I'll help you. " + pchar.name + "or maybe we'll continue our communication...in another, more comfortable place?") +"");
			link.l1 = ""+ GetSexPhrase("By all means, Captain Sharp!!", "You're an incorrigible womanizer, Barty. See you again!") +"";
			link.l1.go = "DeckSharp_8exit";
		break;
		case "DeckSharp_8exit":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Sharp.PearlAreal.add")) sTemp = pchar.questTemp.Sharp.PearlAreal.add;
			NextDiag.TempNode = "DeckSharp_over";
			npchar.DeckDialogNode = "NewDeckSharp"; //новая нода на палубу
			pchar.questTemp.Sharp = "toPearl"; //флаг квеста - на промысел!!!
			AddQuestRecord("SharpPearl", "5");
			AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("SharpPearl", "sSex1", GetSexPhrase("Oh, Captain Sharp!", "Lovelace Barty..."));
			AddQuestUserData("SharpPearl", "iDay", FindRussianDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms)));
			AddQuestUserData("SharpPearl", "sAreal", XI_ConvertString(pchar.questTemp.Sharp.PearlAreal + "Voc"));
			AddQuestUserData("SharpPearl", "sTarget", GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt") + sTemp);
			pchar.quest.SeaPearl_login.win_condition.l1 = "location";
			pchar.quest.SeaPearl_login.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
			pchar.quest.SeaPearl_login.function = "SeaPearl_login";
			SetTimerFunction("SeaPearl_Late", 0, 0, sti(pchar.questTemp.Sharp.PearlAreal.terms));
			if (pchar.location != "Deck_Near_Ship")
			{
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 15.0);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//капитан Шарп, последующие разговоры на палубе
		case "NewDeckSharp":
			dialog.text = "Oh, who do I see?! Greetings "+ GetSexPhrase("like-minded person", "you, beauty") +"!";
			link.l1 = "Hello, Captain Sharp. How are you?";
			link.l1.go = "NewDeckSharp_1";
			//блокировка генератора, если взят грабёж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = ""+ GetSexPhrase("Buddy", "Girlfriend") +"I'm busy right now! I can't help you with anything. No offense...";
				link.l1 = "All right, buddy...";
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "NewDeckSharp_1":
			dialog.text = "Yes, it's all right, "+ GetSexPhrase("buddy", "darling") +", can't complain\nWell, tell me why you're here this time?";
			link.l1 = "Yes, all for the same, buddy, for a tip on the crafts...";
			link.l1.go = "NewDeckSharp_2";
		break;
		case "NewDeckSharp_2":
			if (pchar.questTemp.Sharp.SeekSpy == "alwaysKnow" || pchar.questTemp.Sharp.SeekSpy == "over")
			{
				dialog.text = "You know, "+ GetSexPhrase("buddy", "darling") +", I have a problem with this case. I lost one trusted person from the team, and with him... Well, in general, I don't know where the hunters are.";
				link.l1 = "Yeah, it's sad... Well, that's life. Goodbye, Sharp.";
				link.l1.go = "exit";
				CloseQuestHeader("SharpPearl");
				NextDiag.TempNode = "DeckSharp_noWork";
				pchar.questTemp.Sharp = "over";
			}
			else
			{
				dialog.text = "Hmm, this is certainly a good case. But I can't use my resource on you, "+ GetSexPhrase("buddy, ", "pretty woman, ") +", I have to live by myself!";
				link.l1 = "Which resource should I use?";
				link.l1.go = "NewDeckSharp_3";
			}
		break;
		case "NewDeckSharp_3":
			dialog.text = "Ordinary. "+ GetSexPhrase("None of your business, actually.", "Don't be curious, I won't tell you anyway.") +".\nWell, I can give you a tip, but not for nothing. You have to compensate me for the lost profit, "+ GetSexPhrase("buddy", "darling") +".";
			link.l1 = "Hmm, how much do you want?";
			link.l1.go = "NewDeckSharp_4";
		break;
		case "NewDeckSharp_4":
			dialog.text = "Well, I guess the amount is in " + FindRussianMoneyString(sti(pchar.questTemp.Sharp.price)) + "that'll do for me.";
			link.l1 = "Hey, friend Captain Sharp, what's up? This is too much for me at the moment! Be a friend, drop the price.";
			link.l1.go = "NewDeckSharp_noMoney";
			if (sti(pchar.money) >= sti(pchar.questTemp.Sharp.price))
			{
				link.l2 = "Well, I agree, buddy. Take your compensation!";
				link.l2.go = "NewDeckSharp_GiveMoney";
			}
		break;

		case "NewDeckSharp_GiveMoney":
			dialog.text = "Well, that's fine! I like this approach, "+ GetSexPhrase("buddy", "darling") +".";
			link.l1 = "It's great. So what's with the tip?";
			link.l1.go = "DeckSharp_6";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharp.price));
		break;
		case "NewDeckSharp_noMoney":
			if ((sti(pchar.questTemp.Sharp.price)*10) < sti(pchar.money))
			{
				if (pchar.location == "Deck_Near_Ship")
				{
					dialog.text = ""+ GetSexPhrase("Hello Hagel! What are you doing, " + pchar.name + "Did you find a sucker?! I'm not a liar, I'm CAPTAIN SHARP!! Sounds proud, got it?! Do you think I don't know that you have a lot of money? I know, buddy, I know that very well. So, come on, fork out or get off my deck in all four directions relative to the southwest!", "Hello Hagel! " + pchar.name + ", of course, you are a beautiful and fighting girl, but I am not a liar, but CAPTAIN SHARP! It sounds proud! Do you think I don't know that you have a lot of money? I know, darling, I know that very well. We have a business relationship...Ahem, it's a pity, however, that it's only business. In general, either fork out or look for divers on your own") +"..";
					link.l1 = ""+ GetSexPhrase("Bartholomew, what are you getting turned on for?! You creak like a mast... I didn't come to you to mop a cloth or sharpn an anchor. So be careful what you say. Remember who you're talking to.", "Bartholomew, why are you getting all worked up? You do it, be careful in your expressions, I'm not some kind of bordello girl, don't forget that.") +"...";
				}
				else
				{
					dialog.text = ""+ GetSexPhrase("Why didn't I understand, are you taking me for a sucker? Why are you treating me, do you think I do not know that you have a decent amount of money? I know, buddy, I know that very well. So, come on, fork out or look for pearl fishermen somewhere south-south-east from here, for example.", "Hey, " + pchar.name + "Are you trying to get me divorced? Do you think I don't know that you have a decent amount of money? I know, beautiful, I know that very well. We have a business relationship... At least not yet. So, or share it with me, look for pearl fishers somewhere south-south-east from here, for example.") +"...";
					link.l1 = "Bartholomew, don't get started, you're creaking like a mast. Remember who you're talking to...";
				}
				link.l1.go = "NewDeckSharp_5";
			}
			else
			{
				if (sti(pchar.questTemp.Sharp.price.evil))
				{	//Шарп не в настроении
					dialog.text = "No, "+ GetSexPhrase("buddy", "darling") +"Not today! I'm not doing well myself, and then there's you with your requests. I did not sign up as a patron. Money for a barrel, in general...";
					link.l1 = "Yeah, it's a pity, Sharp, it's a pity. I was thinking that you are a true friend...";
					link.l1.go = "NewDeckSharp_7";
					if (sti(pchar.money) >= sti(pchar.questTemp.Sharp.price))
					{
						link.l2 = "Yes, there is nowhere to go. But I really don't have enough pearls for complete Caribbean happiness... Take your compensation!";
						link.l2.go = "NewDeckSharp_GiveMoney";
					}
				}
				else
				{
					dialog.text = "Well, okay, so be it, today I am kind to something beyond measure... I'll help you!";
					link.l1 = "That's right! That's coastal brotherly!.. So what's with the tip, Benefactor Sharp?";
					link.l1.go = "DeckSharp_6";
				}
			}
		break;
		case "NewDeckSharp_5":
			dialog.text = "Okay, sorry, I overreacted. However, this does not change the essence of the matter. Don't be like that, " + pchar.name + ", it doesn't reflect well on the complexion... In general, the money is on the barrel, or you won't get a tip.";
			link.l1 = "All right, take your compensation!";
			link.l1.go = "NewDeckSharp_6";
			link.l2 = "Nah, I'm going to get away from this case. Then somehow...";
			link.l2.go = "NewDeckSharp_7";
		break;
		case "NewDeckSharp_6":
			dialog.text = "Well, that's another matter! I respect the captain and colleagues!"+ GetSexPhrase("", " And anyway, just a wonderful girl!") +"";
			link.l1 = "It's mutual, Sharp, it's mutual. So, what's up with the tip?";
			link.l1.go = "DeckSharp_6";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharp.price));
		break;
		case "NewDeckSharp_7":
			dialog.text = "Well, whatever you want. Goodbye!";
			link.l1 = "Have a nice day...";
			link.l1.go = "NewDeckSharp_7exit";
		break;
		case "NewDeckSharp_7exit":
			AddQuestRecord("SharpPearl", "10");
			CloseQuestHeader("SharpPearl");
			pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
			pchar.questTemp.Sharp.brothelChance = rand(10);
			NextDiag.TempNode = "DeckSharp_overBad";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			if (pchar.location != "Deck_Near_Ship")
			{
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 15.0);
			}
		break;

		case "DeckSharp_over":
			dialog.text = "We've discussed everything, "+ GetSexPhrase("buddy", "girlfriend") +". If I were you, I wouldn't waste any time.";
			link.l1 = "Yes, Captain Sharp.";
			link.l1.go = "exit";
		break;
		case "DeckSharp_overBad":
			dialog.text = "We've already talked...";
			link.l1 = "Yeah...";
			link.l1.go = "exit";
		break;
		case "DeckSharp_noWork":
			dialog.text = "I can't help you, "+ GetSexPhrase("my friend", "darling") +". I suffer without doing anything. Now we'll have to chase galleons again...";
			link.l1 = "Well, welcome back, buddy!";
			link.l1.go = "exit";
			CloseQuestHeader("SharpPearl");
		break;
		//капитан Шарп, первый разговор в городе на улице
		case "CitySharp":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah, captain " + pchar.name + "! I'm listening to you carefully.";
				link.l1 = "Bartholomew, I'm so glad to see you! I had to look for you, but I was lucky in this city...";
				link.l1.go = "CitySharp_1";
				npchar.quest.meeting = true;
			}
			else
			{
				dialog.text = "Oh, who do I see in this city?! It's captain " + pchar.lastname + ", my colleague and like-minded person!";
				link.l1 = "Yes, Bartholomew, it's me.";
				link.l1.go = "CitySharp_2";
			}
		break;

		case "CitySharp_1":
			dialog.text = "So, to what do I owe for such attention?";
			link.l1 = "You see, I am going to visit the pearl fisheries, and you are a recognized expert in this matter.";
			link.l1.go = "DeckSharp_2";
		break;
		case "CitySharp_2":
			dialog.text = ""+ GetSexPhrase("Eh, my friend, it's good to see you! Well, let's start, perhaps... First to the pub, then to the girls. Which do you prefer, mulatto or white? I have such connections here - you'll be rocked", "Uh-huh, " + pchar.name + ", when I see you, my heart stops already") +"!";
			link.l1 = "Listen, "+ GetSexPhrase("Sharp", "Bartholomew") +", I'm not up to it right now. I'm sorry. I'm on business with you.";
			link.l1.go = "CitySharp_3";
			//блокировка генератора, если взят грабёж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = ""+ GetSexPhrase("Buddy", "Darling") +", I'm busy right now! I can't help you with anything. No offense...";
				link.l1 = "All right, buddy...";
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "CitySharp_3":
			dialog.text = "Well, uh, "+ GetSexPhrase("it's not that interesting.", "it's always like this") +"... What's the deal?";
			link.l1 = "Yes, I've decided to rid pearl fishermen of excess...";
			link.l1.go = "NewDeckSharp_2";
		break;
		//капитан Шарп в борделе
		case "BrothelSharp":
			dialog.text = ""+ GetSexPhrase("Oh, oh, " + pchar.lastname + "My friend!! Come upstairs with me, it's so much fun!!!", "Oh, oh, " + pchar.name + "Is that you, beautiful? Well, now I'm going to think only about you again for a whole week...") +"";
			link.l1 = ""+ GetSexPhrase("No, buddy, I can't right now, I'm busy.", "Come on, Bartholomew, he'll be thinking for a week..") +". I'm here on business.";
			link.l1.go = "BrothelSharp_1";
			//блокировка генератора, если взят грабёж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = ""+ GetSexPhrase("Buddy", "Darling") +"I'm busy right now! I can't help you with anything. No offense...";
				link.l1 = "All right, buddy...";
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "BrothelSharp_1":
			dialog.text = ""+ GetSexPhrase("Tell me...", "Oh, I'm telling you the truth, " + pchar.name + "All right, what do you have there?") +"";
			link.l1 = "I want to visit the pearl fishermen again, shake them a little.";
			link.l1.go = "NewDeckSharp_2";
		break;
		//Эмилио Гарсиа. в бухте Сан-Хуна дель Норте
		case "SharpSeekSpy_Emi":
			dialog.text = "Damn it, we're being eavesdropped on!!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog");
		break;
		case "SharpSeekSpy_fri":
			dialog.text = "Ah, that's the captain " + pchar.name + "! I didn't expect to see you here...";
			link.l1 = "Heh, surprise! Do I know you, buddy?";
			link.l1.go = "SharpSeekSpy_fri_1";
		break;
		case "SharpSeekSpy_fri_1":
			dialog.text = "Well, how to say it... You may not have noticed me, but I remember you well when you visited our brig Sharpnose.";
			link.l1 = "Ha! So you're from Sharp's team?! So I've arrived right at the address.";
			link.l1.go = "SharpSeekSpy_fri_2";
		break;
		case "SharpSeekSpy_fri_2":
			dialog.text = "I don't understand the meaning of that, Captain.";
			link.l1 = "You see, buddy, I was very interested to find out where Sharp gets the tips on the hunters' tartans. Now I've found out.";
			link.l1.go = "SharpSeekSpy_fri_3";
		break;
		case "SharpSeekSpy_fri_3":
			dialog.text = "Captain, Sharp could kill for this secret...";
			link.l1 = "Yeah, and here I am."+ GetSexPhrase("I shit my pants", "scared") +". Besides, this secret is very much wanted by someone in the pearl fisheries ...";
			link.l1.go = "SharpSeekSpy_fri_4";
		break;
		case "SharpSeekSpy_fri_4":
			dialog.text = "And who is this mystery lover?";
			link.l1 = "Mm-hmm...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog_2");
		break;
		case "SharpSeekSpy_Emi_1":
			dialog.text = "Is it not clear? Of course, one of the officers!\nLong story short, it is necessary to kill "+ GetSexPhrase("his", "her") +". For the cause...";
			link.l1 = "Well, try it...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog_3");
		break;
		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			dialog.text = "Come on, buddy, empty your pockets.";
			link.l1 = "What?!";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "Come on, quickly, without talking. I don't like this...";
			link.l1 = "This is a trap!! And " + pchar.questTemp.different.FackWaitress.Name + ", is she working with you, right?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "Paired, paired... Turn out your pockets, or I'll stab you!";
			link.l1 = "The hell with it! I'll kill anyone for my pockets myself...";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "Take it, you brat! But you won't get away with it that easily...";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "Of course it won't do, who's arguing? Well, goodbye, my friend. And remember, you're not so handsome that the waitresses will throw themselves at you on the spot. You'll be smarter from now on!";
			link.l1 = "That's for sure!..";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "Well, as you know...";
			link.l1 = "I know, I know, buddy...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = "Here I am! Did you miss me, handsome?";
			link.l1 = "I didn't have time...";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "Well, then let's not waste any time!";
			link.l1 = "Heh, I agree!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = "Hello. My name is " + GetFullName(npchar) + ". I'm the captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Acc")) + " '" + npchar.Ship.name + "'.";
			link.l1 = "Great! I finally found you.";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "Found?!";
			link.l1 = "Yeah. In general, I brought you logbook. Which you left at the portmaster from " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + ".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "Devil, so that's where I 'planted' it! Yes, this loss almost led to a mutiny on the ship...";
			link.l1 = "Well, all's well that ends well. Take your magazine and let's talk about my fee for the work.";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "I haven't started a new magazine yet, I was just going to, so I'll pay the maximum of what I can afford. " + FindRussianMoneyString(sti(npchar.quest.money)) + "and some of my personal jewelry.";
				link.l1 = "Well, not bad. Take your magazine.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Hmm, you know, I've already started a new magazine. However, I still need the old magazine, I need to move everything to the new one. So I can pick it up for " + FindRussianMoneyString(sti(npchar.quest.money)) + ". and some of my personal jewelry.";
					link.l1 = "Well, that's settled. Take back your magazine!";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "So I started a new magazine already. And I transferred all the records of the old one from memory there, sat and wrote for two days. So I just don't need the old magazine anymore. And I can't pay anything for it.";
					link.l1 = "Nothing at all? That I was chasing you for nothing?";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "Thank you. Well, have a nice day, "+ GetSexPhrase("buddy", "girlfriend") +".";
			link.l1 = "The same to you...";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Dat"));
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);

			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+drand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterReputation(pchar, 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "Heh, if you took it, you have to be quick.";
			link.l1 = "Um, that's also true... Well, take your magazine just like that.";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Dat"));
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader("Caiman_PortManPortmansBook_Delivery");

			AchievementsCounter_genquests(1);

			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "Welcome to the deck of my ship. To be honest, I was already scared - I thought it was One-eyed Steed Hunter who decided to hunt me...";
				link.l1 = "No, buddy, I'm kind today. I was looking for you to help.";
			}
			else
			{
				dialog.text = "Welcome to my deck! What did you want?";
				link.l1 = "I was looking for you, buddy. Barely caught up...";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "Was looking for? And why?";
			link.l1 = "You forgot your logbook at the " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + " port authority. I have the logbook! That's why I was looking for you.";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Damn, so that's where I lost it!.. This is a valuable service, my friend, there are no words. I almost lost my captain's status... Thank you very much.";
				link.l1 = "How about a reward?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Damn, so that's where I lost it!.. Thank you, of course, but the fact is that you've been looking for me for a long time and I've already started a new one. However, I need to move something from there, so I'll take the magazine from you. But I can't pay much...";
					link.l1 = "How much can you do?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "Damn, so that's where I lost it!.. Thank you, of course, but the fact is that you've been looking for me for a long time and I've already started a new one. I transferred the old recordings from memory, so I don't need it.";
					link.l1 = "What, you don't need an old logbook at all?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "I'm ready to pay you back " + FindRussianMoneyString(sti(npchar.quest.money)) + " and give me some of your personal jewelry, too. That's all I can afford.";
			link.l1 = "Well, all right. Here's your logbook.";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "Thanks again. Goodbye, my friend, and be healthy.";
			link.l1 = "And good health to you.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывёт до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);

			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+drand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterReputation(pchar, 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "Absolutely, my friend, you've been looking for me for too long you had to hurry up.";
			link.l1 = "Heh, I should have kept the logbook, then I wouldn't have been used. Anyway, take your logbook for free, I don't need it either.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывёт до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);

			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "It seems that everything has already been decided.";
			link.l1 = "Yes, that's right...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "Greetings. What do you need on my ship?";
			link.l1 = "Just like that, I wanted to exchange news. Maybe you have something for sale...";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "Nothing is for sale, and I have no news. And in general, to be honest, your presence on my deck is undesirable. Have you made yourself clear, I hope?";
			link.l1 = "Yes, it's much clearer... Well, goodbye, buddy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "I told you there's nothing for you to do here!";
			link.l1 = "I see...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = "Why did you attack us?!!";
			link.l1 = "I must return the ship to its owner.";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "Which owner?! I am the owner!";
			link.l1 = "No, it's not like that. Who owns the ship - I don't know, but I know that the ship was stolen from the parking lot of one of the ports. I must put it back in place.";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "The devil! Well, all is not lost for me yet. I'll still try to send you to the next world...";
			link.l1 = "Well, try...";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------- ночное бдение в церкви --------------------------------
		case "ChurchBerglar":
			dialog.text = "Wow! What are you doing here?!";
			link.l1 = "I'm guarding the church.";
			link.l1.go = "ChurchBerglar_1";
		break;
		case "ChurchBerglar_1":
			dialog.text = "Heh, well, wow... And how are you doing?";
			link.l1 = "It looks like there is.";
			link.l1.go = "ChurchBerglar_2";
		break;
		case "ChurchBerglar_2":
			dialog.text = "I'm sorry, of course, "+ GetSexPhrase("my friend", "girlfriend") +", but you can't leave here. I'm really sorry, you shouldn't have taken on this guard...";
			link.l1 = "Ha! But I'm not sorry. Robbing churches is too much. So I will send you to your forefathers without any remorse.";
			link.l1.go = "ChurchBerglar_fight";
		break;
		case "ChurchBerglar_fight":
			LAi_LocationFightDisable(&locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------- поиск кэпов, дача квеста горожанином --------------------------------
		//========= квесты мужиков ===========
		case "SCQ_man":
			/*dialog.text = LinkRandPhrase("Hello, Captain. I want to ask you to help me.",
				"Captain! Would you do me a favor? The fact is, I need help.",
				"Captain, I'm asking for your help!");
			link.l1 = 
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("What's the matter with you?", "State the essence of the problem. Maybe I can help.");
			link.l2.go = "SCQ_man_1";*/
			dialog.text = "Hello, Captain. May I contact you?";
			link.l1 = RandPhraseSimple("I'm busy. Not today.", "I don't have time to listen to you at the moment.");
			link.l1.go = "SCQ_exit";
			link.l2 = "What's the matter with you?";
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if(!CheckAttribute(sld, "questSeekCap")) sld.questSeekCap = 0;
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(npchar, "talker");
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			/*switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "A year ago, a captain undertook to deliver me" + XI_ConvertString("Colony" + SelectNotEnemyColony(NPChar) + "Acc") + But on board his ship, I was thrown into the hold and then sold into slavery. I got out of this mess with great difficulty, several times I was on the verge of life and death... Anyway, I want to remind my 'friend' that I'm still alive.";
					link.l1 = "What do you mean? Describe exactly what you want.";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "The fact is that my wife was kidnapped. One captain, a pirate, was rumored to be courting her here as best he could. At one time, his wife did not even leave the house, he was so annoying. I tried to involve the city authorities in this problem, to no avail. And so we waited, it's called...";
					link.l1 = "What did you wait for?";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "You know, I'm looking for my countryman, with whom three years ago we went here from the Old World in search of a new life. It so happened that we lost each other on the road. But recently I found out that my countryman has become a merchant captain! I've been trying to find him, but I can't handle it on my own.";
					link.l1 = "Why? A lot of captains, including me, can take you anywhere.";
					link.l1.go = "SCQ_Friend";
				break;
			}*/
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "The fact is that they teach me Latin in the local church, but I have no one to practice with in my free time...";
					link.l1 = "Learning Latin is commendable, but what does it have to do with me?";
					link.l1.go = "SCQ_ProverkaZnaniy";
				break;
				case "1":
					dialog.text = "The fact is that they teach me Latin in the local church, but I have no one to practice with in my free time...";
					link.l1 = "Learning Latin is commendable, but what does it have to do with me?";
					link.l1.go = "SCQ_ProverkaZnaniy";
				break;
				case "2":
					dialog.text = "The fact is that they teach me Latin in the local church, but I have no one to practice with in my free time...";
					link.l1 = "Learning Latin is commendable, but what does it have to do with me?";
					link.l1.go = "SCQ_ProverkaZnaniy";
				break;
			}
		break;
		//Латынь - Sinistra
		case "SCQ_ProverkaZnaniy":
			dialog.text = "I'm going to take the test soon, and I'm not even sure of my knowledge. Will you help me?";
			link.l1 = "Uh... And what should I do?";
			link.l1.go = "SCQ_ProverkaZnaniy_2";
			link.l2 = "I have nothing else to do...";
			link.l2.go = "SCQ_exit";
		break;
		
		case "SCQ_ProverkaZnaniy_2":
			dialog.text = "I will tell you a phrase in Latin, and you must repeat it after me without mistakes. I'll give you 16 seconds for that. If you manage to complete the task in less than 16 seconds, then I will increase your reward. Are you ready?";
			link.l1 = "Let's try it. Get started!";
			link.l1.go = "SCQ_ProverkaZnaniy_3";
			link.l2 = "I'm a captain, not a polyglot. Please forgive me.";
			link.l2.go = "SCQ_exit";
		break;
		
		case "SCQ_ProverkaZnaniy_3":
			Log_info("You need to repeat the text in 16 seconds");
			SetShowTimer(16.0);
			DoQuestCheckDelay("SCQ_Zachet_Skorostrel", 8.0);
			DoQuestCheckDelay("SCQ_Zachet_VremyVishlo", 15.6);
			pchar.StudentZachet = npchar.id;
			int Phrase;
			Phrase = rand(23);
			Link.l1.edit = 1;
			Link.l1 = "";
			link.l1.go = "SCQ_ProverkaZnaniy_4";
			if (Phrase == 0)
			{
				dialog.text = "aktum atke tractatum visema";
			break;
			}
			if (Phrase == 1)
			{
				dialog.text = "Abeunt Studio in mores fiat";
			break;
			}
			if (Phrase == 2)
			{
				dialog.text = "kunkta supersilio moventis";
			break;
			}
			if (Phrase == 3)
			{
				dialog.text = "desies reheartia placebitum";
			break;
			}
			if (Phrase == 4)
			{
				dialog.text = "et fabula partem veris abet";
			break;
			}
			if (Phrase == 5)
			{
				dialog.text = "omo omini lopus est dongrat";
			break;
			}
			if (Phrase == 6)
			{
				dialog.text = "letum non omnia finit denov";
			break;
			}
			if (Phrase == 7)
			{
				dialog.text = "memento kuya pulvis espunir";
			break;
			}
			if (Phrase == 8)
			{
				dialog.text = "nec sutor ultra crepidam s";
			break;
			}
			if (Phrase == 9)
			{
				dialog.text = "omnis ars imitatio es natur";
			break;
			}
			if (Phrase == 10)
			{
				dialog.text = "porta di itinari longissima";
			break;
			}
			if (Phrase == 11)
			{
				dialog.text = "reheartio est mater studiorum";
			break;
			}
			if (Phrase == 12)
			{
				dialog.text = "Ciro do venintibus ossa sapit";
			break;
			}
			if (Phrase == 13)
			{
				dialog.text = "silentium est aurum nikhil kur";
			break;
			}
			if (Phrase == 14)
			{
				dialog.text = "sudore et sanguine periculum";
			break;
			}
			if (Phrase == 15)
			{
				dialog.text = "Tempus edax rerum veritas ne";
			break;
			}
			if (Phrase == 16)
			{
				dialog.text = "te amo est verum turbinem encore";
			break;
			}
			if (Phrase == 17)
			{
				dialog.text = "usus es optimus magister patri";
			break;
			}
			if (Phrase == 18)
			{
				dialog.text = "ut tensio sik vis poena negoti";
			break;
			}
			if (Phrase == 19)
			{
				dialog.text = "Vinum verba ministerium meridim";
			break;
			}
			if (Phrase == 20)
			{
				dialog.text = "ansia philosophi anima bellum";
			break;
			}
			if (Phrase == 21)
			{
				dialog.text = "annus oribilis pluvialis mundi";
			break;
			}
			if (Phrase == 22)
			{
				dialog.text = "ignis et akya kausa sitio ubi";
			break;
			}
			if (Phrase == 23)
			{
				dialog.text = "Ingustis Amisi appliance camera";
			break;
			}
		break;
		
		case "SCQ_ProverkaZnaniy_4":
			if ("aktum atke tractatum visema" == GetStrSmallRegister(dialogEditStrings[1]) || "Abeunt Studio in mores fiat" == GetStrSmallRegister(dialogEditStrings[1]) || "kunkta supersilio moventis" == GetStrSmallRegister(dialogEditStrings[1]) || "desies reheartia placebitum" == GetStrSmallRegister(dialogEditStrings[1]) 
				|| "et fabula partem veris abet" == GetStrSmallRegister(dialogEditStrings[1]) || "omo omini lopus est dongrat" == GetStrSmallRegister(dialogEditStrings[1]) || "letum non omnia finit denov" == GetStrSmallRegister(dialogEditStrings[1]) || "memento kuya pulvis espunir" == GetStrSmallRegister(dialogEditStrings[1])
				|| "nec sutor ultra crepidam s" == GetStrSmallRegister(dialogEditStrings[1]) || "omnis ars imitatio es natur" == GetStrSmallRegister(dialogEditStrings[1]) || "porta di itinari longissima" == GetStrSmallRegister(dialogEditStrings[1]) || "reheartio est mater studiorum" == GetStrSmallRegister(dialogEditStrings[1])
				|| "Ciro do venintibus ossa sapit" == GetStrSmallRegister(dialogEditStrings[1]) || "silentium est aurum nikhil kur" == GetStrSmallRegister(dialogEditStrings[1]) || "sudore et sanguine periculum" == GetStrSmallRegister(dialogEditStrings[1]) || "Tempus edax rerum veritas ne" == GetStrSmallRegister(dialogEditStrings[1])
				|| "te amo est verum turbinem encore" == GetStrSmallRegister(dialogEditStrings[1]) || "usus es optimus magister patri" == GetStrSmallRegister(dialogEditStrings[1]) || "ut tensio sik vis poena negoti" == GetStrSmallRegister(dialogEditStrings[1]) || "Vinum verba ministerium meridim" == GetStrSmallRegister(dialogEditStrings[1])
				|| "ansia philosophi anima bellum" == GetStrSmallRegister(dialogEditStrings[1]) || "annus oribilis pluvialis mundi" == GetStrSmallRegister(dialogEditStrings[1]) || "ignis et akya kausa sitio ubi" == GetStrSmallRegister(dialogEditStrings[1]) || "Ingustis Amisi appliance camera" == GetStrSmallRegister(dialogEditStrings[1]))
			{
				Dialog.text = "Excellent, you speak Latin well, Captain. Now I am absolutely sure that I will be able to pass the test! Here is your reward, "+ sti(iMoney) +" piastres.";
				Link.l1 = "It wasn't difficult. I wish you good luck!";
				Link.l1.go = "SCQ_Proverka_Znani_Final";
				
				Event("QuestDelayExit", "sl", "", 0);
				DeleteAttribute(pchar, "showTimer");
				ClearAllLogStrings();
				
				AddMoneyToCharacter(pchar, sti(iMoney));
				if (!CheckAttribute(pchar, "questTemp.SCQ_Zachet_Skorostrel"))
				{
					Dialog.text = "UNBELIEVABLE! You speak Latin perfectly well! Now I am motivated to take the test, and I will definitely succeed! Thank you, my friend. Here is your reward, "+ sti(iMoney) +" piastres and one master key.";
					TakeNItems(PChar, "Lockpick", 1);
					Log_info("You got a master key");
					PlaySound("Interface\important_item.wav");
				}
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "Commerce", 30);
				break;
			}
			else
			{
				Dialog.text = "No! Not right! You are such an illiterate captain, I shouldn't have asked you.";
				Link.l1 = "Well, get out.";
				Link.l1.go = "SCQ_Proverka_Znani_Final";
				
				Event("QuestDelayExit", "sl", "", 0);
				DeleteAttribute(pchar, "showTimer");
				ClearAllLogStrings();
			}
		break;
		
		case "SCQ_Proverka_Znani_Final":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			LAi_SetCitizenType(npchar);
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(pchar, "StudentZachet");
			DeleteAttribute(pchar, "questTemp.SCQ_Zachet_Skorostrel");
		break;
		
		case "SCQ_Proverka_Znani_VremyVishlo":
			Log_info("You didn't make it");
			dialog.text = "You can't even connect two words. I shouldn't have asked you...";
			link.l1 = "Well, get out.";
			link.l1.go = "SCQ_Proverka_Znani_Final";
		break;
		
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = "I want you to find him and send him to the next world. I want revenge so much that I just can't eat...";
			link.l1 = "I see... I think I can help you on occasion. Tell me the name of the captain and the ship he sails on.";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "I'm sorry, I'm not interested.";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "The captain's name is " + npchar.quest.SeekCap.capName + ". Goes to " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " with the name '" + npchar.quest.SeekCap.shipName + "'. I'll pay you for this job " + FindRussianMoneyString(sti(npchar.quest.money)) + " and all my personal jewelry.";
			link.l1 = "I see. Well, I'll be more attentive while traveling in the Caribbean. If I meet this cap, he's screwed...";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "I won't lift a finger for such money. Look for the fool elsewhere.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "Phew, that's what I've been longing to hear!.. Oh, I can already eat! I should have a snack...";
			link.l1 = "Come on, buddy. As soon as I get the job done, I'll find you here in the city.";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "Okay, I'll be waiting for you at the local church. Then I'll pay you back.";
			link.l1 = "Good.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = "My relative inaction has led to sad results. That bastard kidnapped my wife and took her on his ship to sea. I'm asking you to find this scoundrel!";
			link.l1 = "Hmm, well, why would I quarrel with my colleagues?";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = "I am not rich, but I will gladly give everything I have! If you release my wife and bring her to me, then I will pay you " + FindRussianMoneyString(sti(npchar.quest.money)) + " and I'll give you all my personal jewelry.";
			link.l1 = "Hmm, well, I'm ready to get on with this case. What is the name of this loving cap, what kind of ship does he have? Yes, and what is your wife's name?";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "No, buddy, for such money, I won't take on this case. I'm sorry...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "Her name is " + npchar.quest.SeekCap.name + ". The bastard captain's name is " + npchar.quest.SeekCap.capName + ", he swims on " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " with name '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "Well-known human waste goods are floating, buddy. And the captains go...";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "Yes, yes, of course, I'm sorry! I'm not a sailor, so you know...";
			link.l1 = "It's okay, don't worry. Anyway, now wait for me with the search results.";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "Thank you very much! I'll be waiting for you at the local church. But I'm begging you - hurry up. I am very afraid for my wife...";
			link.l1 = "I'll do everything I can. Wait.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("xia", "as"));
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = "The fact is that my countryman has not acquired real estate here. His home is his ship. Therefore, it is very difficult for me to catch him, he is constantly on the move. And I can't afford to waste time on useless travel, I have to earn my living.";
			link.l1 = "If you don't have money, then there's nothing I can do to help you...";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "I can pay you " + FindRussianMoneyString(sti(npchar.quest.money)) + " for the job and I'll give you all my personal jewelry. That's all I can afford at the moment.";
			link.l1 = "The amount suits me, I'm ready to take up this case. By the way, you can come to me as a passenger, then you will not have to go to your countryman when he is found.";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "It's too little for me. So look for someone else for this case.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "No, I think I'll stay here. I don't know how long the search will last, and I may just not have enough money. And here I have a job.";
			link.l1 = "I understand. Well, now tell me who your friend is and what kind of ship he has.";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "His name is " + npchar.quest.SeekCap.capName + ". As far as I know, he has " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")) + " with the name '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "I see. Well, as soon as I meet your countryman, I will definitely tell him that you are looking for him.";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "Thank you. I will be waiting for your arrival at the local church. I guess I'll need to give the money back after the job is done.";
			link.l1 = "Of course. Well, have a good day, wait for the result of the search.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ate", "la"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("", "a"));
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = "Hello, Captain. Are there any results on my case?";
			link.l1 = "Remind me, what do you have there?";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "By the look of you, I guess I've finally been avenged. Is that so?";
					link.l1 = "Exactly. " + npchar.quest.SeekCap.capName + "dead, but his " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + "at the bottom.";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "You've found my wife! Is it true?!";
					link.l1 = "Really. She's on my ship as a passenger. You can take it if " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + "and there is your wife...";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "Hello, Captain. Have you found my countryman?";
					link.l1 = "Yes, I found him. He told me that you are waiting for him here. So everything turned out well.";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "What, you forgot that I hired you to take revenge on a captain named" + npchar.quest.SeekCap.capName + "for the year I spent in slavery?!";
					link.l1 = "I haven't forgotten anything.. I'm doing it, wait.";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "I don't believe my ears! Have you forgotten that you promised me to find and free my wife? She was kidnapped by a pirate named " + npchar.quest.SeekCap.capName + "!";
					link.l1 = "I haven't forgotten about your wife. It's just that the search has not yet brought results. It's not that simple, wait...";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "Wait... Have you forgotten about your promise to find my countryman, a merchant captain named " + npchar.quest.SeekCap.capName + "?";
					link.l1 = "I haven't forgotten, but haven't found him yet. Wait...";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "Excellent, I was not mistaken about you! So, as we agreed, here are your " + FindRussianMoneyString(sti(npchar.quest.money)) + "and jewelry. Thank you for your hard work.";
			link.l1 = "Hmm, you're welcome...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+drand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "My God, you literally brought me back to life! Please get yours " + FindRussianMoneyString(sti(npchar.quest.money)) + "and jewelry. And know that we will pray for you for the rest of your life!";
			link.l1 = "Pray, I don't mind.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+drand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);
		break;
		case "SCQR_manFriend":
			dialog.text = "Great!.. Here's what I promised you-" + FindRussianMoneyString(sti(npchar.quest.money)) + "and jewelry. And thank you, Captain.";
			link.l1 = "You're welcome, buddy. Goodbye...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+drand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);
		break;
		//========= квесты баб ===========
		/*case "SCQ_woman":
			dialog.text = LinkRandPhrase("Hello, Captain. I wanted to ask you a favor.",
				"Captain! Help the woman, be so kind...",
				"Captain, do not refuse."+ GetSexPhrase("the lady", "to me") +"help.");
			link.l1 = RandPhraseSimple("I'm busy, beauty, not today!", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + "but I don't have time at the moment...");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("What's the matter with you, " + GetAddress_FormToNPC(NPChar) + "?", "State the essence of the problem, " + GetAddress_FormToNPC(NPChar) + ". I will try to help you.");
			link.l2.go = "SCQ_woman_1";
		break;*/
		case "SCQ_woman":
			dialog.text = "Hello, Captain. May I contact you?";
			link.l1 = RandPhraseSimple("I'm busy, beauty, not today!", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + ", but I don't have time at the moment...");
			link.l1.go = "SCQ_exit";
			link.l2 = "What's the matter with you, " + GetAddress_FormToNPC(NPChar) + "?";
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			/*switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "My husband is engaged in commerce - delivers goods to merchants all over the district. So, he went to sea more than three months ago, and still hasn't returned!";
					link.l1 = "Do you think something happened to him?";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+ GetSexPhrase("Captain, I look at you and see a brave captain, an excellent thug.", "Captain, I see you are a strong and brave woman, you will shut any man up.") +"...";
					link.l1 = "What are you talking about, " + GetAddress_FormToNPC(NPChar) + "?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "Captain, help me, I beg you! My husband got caught by pirates! Can you save him?";
					link.l1 = "Wait, I don't really understand who got to whom...";
					link.l1.go = "SCQ_Pirates";
				break;
			}*/
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "The thing is, I'm very bored and I have no one to have fun with. Maybe... Will you play hide-and-seek with me?";
					link.l1 = "Hide-and-seek? And what are the rules of the game?";
					link.l1.go = "SCQ_Prytki";
				break;
				case "1":
					dialog.text = "The thing is, I'm very bored and I have no one to have fun with. Maybe... Will you play hide-and-seek with me?";
					link.l1 = "Hide-and-seek? And what are the rules of the game?";
					link.l1.go = "SCQ_Prytki";
				break;
				case "2":
					dialog.text = "The fact is that I'm very bored and I have no one to have fun with. Maybe... Will you play hide-and-seek with me?";
					link.l1 = "Hide-and-seek? And what are the rules of the game?";
					link.l1.go = "SCQ_Prytki";
				break;
			}
		break;
		
		//Прятки - Sinistra
		case "SCQ_Prytki":
			dialog.text = "You close your eyes and count to five, and I hide within the city limits. If you find me, then I promise that you will not leave without a reward.";
			link.l1 = "Well, let's play, hehe.";
			link.l1.go = "SCQ_Prytki_1";
			link.l2 = "No, I'm not going to play these childish games... You'd better find someone else.";
			link.l2.go = "SCQ_Prytki_Net";
		break;
		
		case "SCQ_Prytki_Net":
			DialogExit();
			
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(npchar, "talker");
		break;
		
		case "SCQ_Prytki_1":
			dialog.text = "Great, now close your beautiful eyes and start counting.";
			link.l1 = "One... two... three...";
			link.l1.go = "SCQ_Prytki_2";
			pchar.DevushkaVPrytki = npchar.id;
		break;
		
		case "SCQ_Prytki_2":
			DialogExit();
			
			SetLaunchFrameFormParam("We close our eyes for a moment...", "SCQ_Prytki_VremyPoshlo", 0, 2.5);
			LaunchFrameForm();
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			sld = CharacterFromID(pchar.DevushkaVPrytki);
			sld.fixteleport = true;
			if (rand(1) == 0)
			{
				pchar.DvP = PlaceCharacter(sld, RandPhraseSimple("goto", "patrol"), "random_must_be");
			}
			else
			{
				pchar.DvP = PlaceCharacter(sld, "reload", "random_must_be");
			}
			DeleteAttribute(sld, "talker");
			LAi_SetStayType(sld);
			if(InterfaceStates.EnabledQuestsMarks)
			{
				sld.quest.questflag.model = "questionmarkB";
			}
		break;
		
		case "SCQ_Prytki_Dengi":		
			dialog.text = "Oh, hee-hee. And you are good detective, captain, so be it, here are yours "+ sti(iMoney) +" piastres.";
			link.l1 = "Thank you, beautiful, I was glad to spend time with you. Goodbye.";
			link.l1.go = "SCQ_Prytki_Dengi_Final";
			
			Event("QuestDelayExit", "sl", "", 0);
			PChar.quest.SCQ_Prytki_PokinuliZonu.over = "yes";
			DeleteAttribute(pchar, "showTimer");
			DeleteAttribute(pchar, "DvP");
			DeleteAttribute(pchar, "BlockingTalker");
			ClearAllLogStrings();
			
			AddMoneyToCharacter(pchar, sti(iMoney));
			AddCharacterExpToSkill(pchar, "Sneak", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "SCQ_Prytki_Dengi_Final":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			LAi_SetCitizenType(npchar);
			UnmarkCharacter(npchar);
			InterfaceStates.Buttons.Save.enable = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "SCQ_Prytki_Trah":
			dialog.text = "Oh, hee-hee. And you are good detective, captain. Let's rent a room in the tavern, I'll reward you properly.";
			link.l1 = "Well, let's go.";
			link.l1.go = "SCQ_Prytki_Trah_2";
			link.l2 = "I'm sorry, girl, but I just remembered that I have unfinished business. I have to go.";
			link.l2.go = "SCQ_Prytki_Dengi_Final";
			
			Event("QuestDelayExit", "sl", "", 0);
			PChar.quest.SCQ_Prytki_PokinuliZonu.over = "yes";
			DeleteAttribute(pchar, "showTimer");
			DeleteAttribute(pchar, "BlockingTalker");
			ClearAllLogStrings();
			UnmarkCharacter(npchar);
			
			AddCharacterExpToSkill(pchar, "Sneak", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "SCQ_Prytki_Trah_2":
			DoQuestReloadToLocation(npchar.city+"_tavern_upstairs", "quest", "quest4", "SCQ_Prytki_V_Komnate");
			ChangeCharacterAddressGroup(npchar, npchar.city+"_tavern_upstairs", "quest", "quest3");
		break;
		
		case "SCQ_Prytki_Trah_3":
			dialog.text = "Ah, Captain, I can't wait to be in your warm embrace...";
			link.l1 = "Come here, baby...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "SCQ_Prytki_Trah_4";
			AddDialogExitQuest("PlaySex_1");
			
			AddCharacterHealth(pchar, 5);
			LAi_SetCurHPMax(pchar);
			ChangeCharacterReputation(pchar, -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fencing", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);			
			LAi_SetStayType(npchar);
			npchar.lifeday = 0;
			
			InterfaceStates.Buttons.Save.enable = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "SCQ_Prytki_Trah_4":
			dialog.text = "It was great!";
			link.l1 = "I'm happy, pussy. I liked it too.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "SCQ_Prytki_Ooops_Eto_Lovushka":
			dialog.text = "";
			link.l1 = "Well, here we are alone... So what kind of reward were you talking about?";
			link.l1.go = "SCQ_Prytki_Ooops_Eto_Lovushka_2";
			npchar.lifeday = 0;
		break;
		
		case "SCQ_Prytki_Ooops_Eto_Lovushka_2":
			DialogExit();
			DoQuestCheckDelay("SCQ_Prytki_V_Komnate_Ooops_Eto_Lovushka", 1.2);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(PChar, "reload", "reload1");
		break;
		
		case "SCQ_Prytki_Ooops_Eto_Lovushka_3":
			dialog.text = "Hey, "+GetSexPhrase("smelly mammoth", "bunny")+", give away everything valuable that you have. Otherwise you'll regret it.";
			link.l1 = "Ah, that's how it is... I didn't expect this... Well, you asked for it!";
			link.l1.go = "SCQ_Prytki_Ooops_Eto_Lovushka_4";
		break;
		
		case "SCQ_Prytki_Ooops_Eto_Lovushka_4":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("Bandit_Prytki_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SCQ_Prytki_V_Komnate_Final");
			LAi_SetFightMode(pchar, true);
		break;

		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = "I don't know, but I really hope he's just busy with work. Although he could have sent a message, he knows that I'm worried!";
			link.l1 = "The sea is restless now, anything can happen...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Here! You know what I'm talking about. By the look of you "+ GetSexPhrase("Captain brave", "the brave girl") +"That's why I wanted to ask you to find my husband. I am ready to pay you for this " + FindRussianMoneyString(sti(npchar.quest.money)) + "and I'll give you my jewelry.";
			link.l1 = "Good. If I meet your husband at sea or anywhere else, I will inform him of your concern. And tell me your husband's name and what kind of ship he has.";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "I'm not interested in such money. Unfortunately, I have to refuse...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "His name is " + npchar.quest.SeekCap.capName + ". And he works for " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " with the name '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "I see. Well, now wait. And try to stay mostly in the church, so that I don't look for you around the city...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = ""+ GetSexPhrase("What I mean, my dear, is that I want to hire you for your intended purpose, so to speak...", "I want you to help me. I hope that you will understand me as a woman. ") +"I was rather annoyed by one captain, I wish he would die.";
			link.l1 = "Oh ho ho! Oh, my God! And what did he do to you, this wretch?";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "That bastard tricked me. He pretended to like me, even courted me. And it turned out that he needed something from my husband! And when this crook got a loan, it suddenly turned out that he didn't mean anything like that...";
			link.l1 = "Hmm, maybe he did?";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "Do you think I'm a fool?! Can't tell the difference between courtship and idle chatter?";
			link.l1 = "No, what are you...";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "He just took advantage of me, that bastard! I will never forgive him for this!..";
			link.l1 = "Hmm... Сan you cool off? Well, a day or two will pass, and everything will change...";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "Will change?! "+ GetSexPhrase("You're a moralist, not a pirate.", "Apparently, you have never been in such a situation! Well, yes, who would take the risk... And I'm just a weak woman...") +"!";
			link.l1 = ""+ GetSexPhrase("Oh, come on! ", "") +"I just want to know how serious your intentions are.";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "Damn it, "+ GetSexPhrase("you just don't know what the revenge of a rejected woman is.", "you're a woman, and you should understand what it's like to be rejected! I want revenge.") +"!..";
			link.l1 = ""+ GetSexPhrase("That's right, somehow it didn't happen.", "Well, you know, some people will just cry and that's it.") +"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+ GetSexPhrase("Consider yourself lucky. A woman rejected and deceived in her expectations is a fury, a devil in a skirt! There is nothing that can soften her anger.", "But I'm not like that. And there is nothing that can soften my anger.") +"!\nSo I want you to kill him yourself. And before he dies, he needs to know who organized all this...";
			link.l1 = "Hmm, I don't even know what to say... And how much are you willing to pay for it?";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "That's all I have. I'll give you my jewelry and " + FindRussianMoneyString(sti(npchar.quest.money)) + "! Will it suit you?";
			link.l1 = "Well, I'm interested in this. Tell me, who is your abuser, what ship is he the captain of?";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = ""+ GetSexPhrase("Perhaps I will show male solidarity. ", "") +"Sorry, without me...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "This scoundrel's name is " + npchar.quest.SeekCap.capName + ", he is the captain " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Acc")) + " with the name '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "Consider your order accepted for execution, " + GetAddress_FormToNPC(NPChar) + ", and wait for me at the local church. I hope that now you will let go at least a little...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("en", "on"));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("", "a"));
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = "I'll explain it to you now. The fact is, my husband, a completely ordinary man, was captured by pirates! They killed everyone, spared no one...";
			link.l1 = "So the captain dared to resist. If they had surrendered, no one would have been harmed.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "Maybe, but my husband has absolutely nothing to do with it. He was just a passenger on this ship. So, to save his life, he had to say that he was fabulously rich. The pirates spared him, and did not even throw him into the hold.";
			link.l1 = "How do you know?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "My husband managed to send me a letter where he says that everything is fine with him. He's being held in a cabin, not like the other prisoners.";
			link.l1 = "And what are you going to do? It can't last that long. Sooner or later, the pirates will figure him out.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "You're a pirate too, aren't you? Yes, yes, I know... I beg you, help us, save my husband! In the letter, he described the pirate ship and named the captain. It will be easy enough for you to find him!";
			link.l1 = "It's not as easy as you think. All the prisoners are the rightful prize of the cap who captured the ship. And I can't do it in a short time.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "But you can try! Besides, there is time to search. My husband is far from a fool, he called himself a merchant from the Old World, so the pirates do not demand money for him immediately - it is very far to go after them. If you release him, then I will give you everything I have!";
			link.l1 = "And what do you have?";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "A little bit, " + FindRussianMoneyString(sti(npchar.quest.money)) + "and all my jewelry... But I will pray for your soul for the rest of my life!";
			link.l1 = "Yeah, really a little bit... Oh well, I'm ready. to help you on occasion.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "I'm sorry, but it's too little for me to attack. to his colleague, a member of the Brethren.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "Thank you, thank you!!";
			link.l1 = "If everything works out, then you will thank me, but for now it's not worth it. Tell me your husband's name and everything you know about these pirates.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = "My husband's name is " + GetFullName(forName) + ". The pirate captain's name is " + npchar.quest.SeekCap.capName + ", he trades on " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " with the name '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "I see. Well, now expect and hope that I will be lucky with the search. Try to be in the church so that I can find you there.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("", "a"));
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "Oh, Captain, I'm so glad to see you! Tell me quickly, what have you learned about my case?";
			link.l1 = "Hmm, remind me, " + GetAddress_FormToNPC(NPChar) + ", what kind of case are we talking about?";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "Ah, Captain, I received a letter from my husband! In it, he writes that you have found him.";
					link.l1 = "Yes, that's right, " + GetAddress_FormToNPC(NPChar) + ". Your husband, " + npchar.quest.SeekCap.capName + ", alive and well. He just worked hard, so to speak...";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "What do you say, Captain? Did you do what I asked you to do? Captain " + npchar.quest.SeekCap.capName + "dead?";
					link.l1 = "Yes, he's dead, " + GetAddress_FormToNPC(NPChar) + ". Before he died, he found out who caused his death. The last thing he heard in this life was your name.";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "You have freed my husband after all! I beg you, tell me, is that so?!!";
					link.l1 = "Yes, he is on my ship now. You can take it if " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + "and there is your husband...";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "Have you forgotten that you promised me to find my husband? His name is " + npchar.quest.SeekCap.capName + "!";
					link.l1 = "Oh, yes, of course... I haven't forgotten anything. I just haven't been able to find him yet.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "I didn't understand something! You forgot that you have to send to the next world my abuser, a captain named " + npchar.quest.SeekCap.capName + "?!";
					link.l1 = "Come on, " + GetAddress_FormToNPC(NPChar) + ", no way. Your order is in progress, expect...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "My God, Captain, have you forgotten that you promised to rescue my husband from captivity?!";
					link.l1 = "I haven't forgotten anything. I'm working on it. Wait, " + GetAddress_FormToNPC(NPChar) + " " + npchar.lastname + ".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "My God, how grateful I am to you! Oh, by the way, here are yours " + FindRussianMoneyString(sti(npchar.quest.money)) + ". And thanks again!";
			link.l1 = "Hmm, you're welcome...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+drand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "Great! Well, here are yours " + FindRussianMoneyString(sti(npchar.quest.money)) + "and jewelry. Goodbye.";
			link.l1 = "Goodbye...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+drand(8));
			TakeNItems(pchar, "jewelry14", rand(3));
			TakeNItems(pchar, "jewelry13", rand(3));
			TakeNItems(pchar, "jewelry10", rand(3));
			TakeNItems(pchar, "jewelry15", rand(3));
			TakeNItems(pchar, "jewelry16", rand(3));
			TakeNItems(pchar, "jewelry18", rand(3));
			TakeNItems(pchar, "jewelry6", rand(3));
			TakeNItems(pchar, "jewelry7", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);
		break;
		case "SCQR_womanPirates":
			dialog.text = "Of course it's him!!! God, Captain, how grateful I am to you! Here are yours " + FindRussianMoneyString(sti(npchar.quest.money)) + ". I will pray for you every day as long as I live!";
			link.l1 = "It's nice, pray...";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+drand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Greetings to my colleague. What did you want"+ GetSexPhrase(", my friend", "Oh, my friend.") +"?";
					link.l1 = "Your name is " + GetFullName(npchar) + ", isn't that right?";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "Yes, that's right!";
			link.l1 = "Then you're out of luck. I'm going to tell you one name now, and you try to remember this person. " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ". Do you remember?";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "Hmm, I remember...";
			link.l1 = "Well, he's very offended with you, buddy. So it's time to pay off for selling a free man into slavery.";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "Pay off?! What are you talking about?";
			link.l1 = "That I'm going to kill you right here.";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "Think about it, "+ GetSexPhrase("my friend", "girlfriend") +", who are you trying for! This is a completely insignificant human being. He belongs on the cane plantations!";
			link.l1 = "Well, it's not for you to allocate places. So you'll have to answer for what you've done!";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "Ho! Well, I'll answer as best I can!";
			link.l1 = "Come on, come on...";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = "What do you want on my deck?";
			link.l1 = "I want to ask you, do you do any passenger hauling?";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "What's it to you?";
			link.l1 = "I'm just asking...";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "Just like that... listen, get out of here while I give you the opportunity. I don't like you!";
			link.l1 = "Okay, okay, don't get all worked up. I'm already leaving...";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "We've already talked, don't push yourself!";
			link.l1 = "I'm not pushing it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Greetings to my colleague! You wanted something, my friend?";
			link.l1 = "I wanted to find out if you took from " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " a woman named " + GetFullName(sld) + "?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "Heh, that's right, she's in my cabin! You're good, you little devil!.. Why are you asking?";
			link.l1 = "Buddy, this lady is married. You kidnapped a married woman!";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "So what? I like her, and that's it. And I'm not going to let some ragamuffin interfere in our relationship just because he's her husband, you see!..";
			link.l1 = "Let me say that the Brethren does not encourage such tricks.";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "Are you trying to read morals to me here? The Brethren has nothing to do with this case, so your conversations won't lead to anything. She's mine, period!";
			link.l1 = "Don't get excited, I was just wondering... Goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "We have already talked about women. I don't want to discuss this anymore!";
			link.l1 = "Okay...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "I am glad to welcome a colleague on my deck! What did you want to discuss with me, "+ GetSexPhrase("my friend", "girlfriend") +"?";
			link.l1 = "I wanted  to find out if you took a woman from " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " named " + GetFullName(sld) + "?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "Heh, that's right, she's in my cabin! You're good, you little devil!.. Why are you asking?";
			link.l1 = "Buddy, this lady is married. You kidnapped a married woman!";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "So what? I like her, and that's it. And I'm not going to let some ragamuffin interfere in our relationship just because he's her husband, you see!..";
			link.l1 = "Let me say that the Brethren does not encourage such tricks.";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "Are you trying to read morals to me here? The Brethren has nothing to do with this case, so your conversations won't lead to anything. She's mine, period!";
			link.l1 = "Don't get excited, I was just wondering... Anyway, bye, buddy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "What do you need, you rascal?!!";
			link.l1 = "I'm here for the woman that you stole from your husband. Remember " + XI_ConvertString("Colony"+npchar.quest.cribCity) + "! Her name is " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "The devil!! You won't see her as your ears!";
			link.l1 = "Ha, you idiot!! I see my ears in the mirror! And I'll cut yours off now...";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "girl_"+(rand(7)+1); //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = "Who are you?";
			link.l1 = "Hello. I'm following you on behalf of your husband. Now that you're free, I need to take you to him.";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "Isn't this a dream?! Is it true?!";
			link.l1 = "The purest truth, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "Glory to the Almighty God!!! I'm ready, let's get out of here quickly!";
			link.l1 = "Okay, " + GetAddress_FormToNPC(NPChar) + ", get ready to go home to your husband.";
			link.l1.go = "exit";
			//уберём жену из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = "Hello! I am glad to welcome the captain, a colleague, so to speak, on land...";
			link.l1 = TimeGreeting() + "And I found you on business.";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "I'm listening to you carefully.";
			link.l1 = "The fact is that your countryman, with whom you went here from the Old World, is looking for you. " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ". Do you know this name?";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "Ha, of course! And where does he live?";
			link.l1 = "In " + XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat") + ". I offered him to come with me, but he refused. He asks you to stop by his place.";
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = "Of course I will do it. Thank you very much!.. You know, by the look of you, I'd say you're a pirate!";
			link.l1 = "That's right. But I am kind today, so you have nothing to worry about. Have a nice day.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "Is everything okay, no problem? I'm sorry, I'm a little worried...";
			link.l1 = "It's all right, buddy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting() + ". What do you need from me? I'm just a merchant captain, and...";
			link.l1 = "I know, buddy. Don't be so nervous, they say it's bad for your health. I'm here on business.";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "What's the case?";
			link.l1 = "Your countryman is looking for you" + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "Do you know someone like that?";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "Oh, oh, I found it after all! Very good... I'm sorry for the rude reception, you know, I sinfully thought that you were a pirate.";
			link.l1 = "That's right. But you're not in any danger yet. I was asked to give you a message, which I did.. Your countryman, by the way, lives and works in " + XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat") + ".";
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "Wow!.. You-"+ GetSexPhrase("a noble man", "the noble girl") +". Thank you!";
			link.l1 = "You're welcome. Goodbye and be well, buddy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = "Hello. Did you want something?";
			link.l1 = "Your name is " + GetFullName(npchar) + ", isn't that right?";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "Yes, it's me.";
			link.l1 = "It sounds silly, of course, but your wife asked me to tell you that she is very worried about you.";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "Ha! Well, that's understandable... Actually, I'm so wrapped up with work that I'm not up to it right now. Lucrative offers follow one after another, I can't miss out on a possible benefit just because my wife is worried.";
			link.l1 = "That's for sure, but you could at least text her that you're okay.";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "Yes, you're right. I will write to her immediately!.. Thank you so much for participating in our family affairs!";
			link.l1 = "You're welcome, buddy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = "Hello. To what do I owe the honor of seeing you on my ship?";
			link.l1 = "Your name is " + GetFullName(npchar) + ", isn't that right?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "Yes, it's me.";
			link.l1 = "It sounds silly, of course, but your wife asked me to tell you that she is very worried about you.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "Ugh, damn it! And I, frankly, was scared - I thought it was the famous prize hunter - One-Eyed Steed Hunter followed me. Well, it's a good thing I made a mistake...\nYou know, I got so caught up in my work I can't deal with it right now. Lucrative offers follow one after the other, I can't miss out on a possible benefit just because my wife is worried.";
			link.l1 = "That's for sure, but you could at least text her that you're okay.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "Yes, you're right. I will definitely do it at the first port on unloading... Thank you so much for participating in our family affairs!";
			link.l1 = "You're welcome, buddy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "Once again, accept my thanks...";
			link.l1 = "It's not worth it, it's okay.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = "Glad to see you in this town, Captain. Do you need something from me?";
			link.l1 = ""+ GetSexPhrase("You know, Captain... Phew, I don't even know how to say it!", "Yes, you do.") +"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+ GetSexPhrase("Tell it like it is.", "I wonder what it is?") +"";
			link.l1 = ""+ GetSexPhrase("Hmm, that's what I'll do... In general, ", "") +"I have a question for you. Do you know a lady named " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "Heh, well, yes, I do. I had the misfortune, so to speak, to communicate with her. A silly fool, I can tell you...";
			link.l1 = "Hmm... So, this silly fool hired me to kill you"+ GetSexPhrase(" , my friend. That's it..", "") +".";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "Well, this is just ridiculous...";
			link.l1 = ""+ GetSexPhrase("If it wasn't so sad... I'm sorry, but for yours", "There's nothing funny about it. For yours") +"there is a reward for the head. And I intend to get it.";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "Ho ho!.. Are you serious, Captain?";
			link.l1 = ""+ GetSexPhrase("No, my friend...", "I didn't even think about it!") +"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+ GetSexPhrase("What kind of friend are you, you idiot?! You can't even call yourself a captain. So, a henchman at the beck and call of a quarrelsome fury", "Damn it! One feisty fury hired another! What kind of things are going on?") +"!";
			link.l1 = ""+ GetSexPhrase("Is that so?!", "You used her for your own selfish purposes, so it's not surprising that she decided to take revenge.") +"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+ GetSexPhrase("Well, what did you want me to call you? Whatever you call it, the essence won't change...", "Women's solidarity, right?!") +"";
			link.l1 = ""+ GetSexPhrase("", "You know, I guess that's the same thing. ") +"Get your blade out!";
			link.l1.go = "RevengeCap_7";
			link.l2 = "You know... Live for now. I don't want to stain the streets of this town with your blood right here. We'll meet again!";
			link.l2.go = "exit";
			NextDiag.TempNode = "RevengeCap_6lf";
		break;
		case "RevengeCap_6lf":
			dialog.text = GetSexPhrase("Ah! .. Defender of oppressed girls! Of course, I remember you. What do you need?", "Ah! .. The employer of a quarrelsome fury? What is needed?");
			link.l1 = GetSexPhrase("I came to kill you, you scoundrel.", "The evil fury wants you dead, you bastard. Die!");
			link.l1.go = "RevengeCap_7";
			link.l2 = "Nothing. Go about your business.";
			link.l2.go = "exit";
			NextDiag.TempNode = "RevengeCap_6lf";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачёта в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "I've already had a conversation with you."+ GetSexPhrase("Get out, you scoundrel", "Get out, you wretch.") +"...";
			link.l1 = ""+ GetSexPhrase("Scoundrel", "The evil one") +"?! All right...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = "Glad to see you on my deck, Captain. Why have you come?";
			link.l1 = "I have a question for you. Do you know a lady named " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "Heh, well, yes, I do. I had the misfortune, so to speak, to communicate with her. A silly fool, I can tell you...";
			link.l1 = "Heh, so this silly fool hired me to kill you."+ GetSexPhrase(", my friend. That's it..", "") +".";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "Hee hee... Captain, don't make me laugh. If you have nothing else to do with me, then goodbye.";
			link.l1 = "Well, goodbye. But keep in mind what I told you..";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "Absolutely, Captain, how else?!";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачёта в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "I don't want to talk about this topic anymore, Captain. It's ridiculous.";
			link.l1 = "Well, as you know...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = "What the hell is going on?! Why did you attack my ship?!";
			link.l1 = "On behalf of "+ GetSexPhrase("a certain lady, ", "woman") +" by name " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ". Is this person familiar to you?";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "The devil!!! I can't believe..."+ GetSexPhrase("", "One evil fury hired another!") +"";
			link.l1 = ""+ GetSexPhrase("But you have to.", "It's time for you to answer for your despicable deeds!") +"";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "Well, I'm not going to die that easily. Thanks for the conversation, it gave me more strength."+ GetSexPhrase("But the henchman", "And a girlfriend") +"I still want to send this fury to the next world!";
			link.l1 = "Try it, what else can I say?";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight";
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Glad to see you on my deck. Is there anything I can do to help you?";
			link.l1 = "Probably, yes. I'm looking for a man named " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "This man is my prisoner, and I plan to get a good ransom for him.";
			link.l1 = "I want to get it.";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "I'm sorry, but it's impossible. If that's all, then I'm asking you to leave my ship.";
			link.l1 = "All right, Captain, whatever you say.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "PiratesCapCap_exit":
			dialog.text = "We have already talked about my prisoner. Nothing has changed.";
			link.l1 = "I see...";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Greetings, Captain. Is there anything I can help you with?";
			link.l1 = "Probably, yes. I'm looking for a man named " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "This man is my prisoner, and I plan to get a good ransom for him.";
			link.l1 = "I want to get it.";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "I'm sorry, but that's not possible.";
			link.l1 = "It's a pity...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "The devil! What the hell?!!";
			link.l1 = "I need your prisoner, by name " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "Ha! Well, no, only over my dead body...";
			link.l1 = "As you wish.";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+1); //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = "Who are you?";
			link.l1 = "I'm the captain " + GetFullName(pchar) + ", don't worry, I came to pick you up in order to take you to your wife.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "Damn it, isn't this a dream?!";
			link.l1 = "I assure you, this is not a dream... Well, it's done, now let's get out of here.";
			link.l1.go = "exit";
			//уберём мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//несчастный мушкетёр
		case "OffMushketer":
			dialog.text = "Greetings, "+ GetSexPhrase("guest", "wonderful guest") +". What did you want here?";
			link.l1 = "To get acquainted. My name is Captain " + GetFullName(pchar) + ".";
			link.l1.go = "OffM_1";
		break;
		case "OffM_1":
			dialog.text = "Glad to meet you, Captain. How can I help you?";
			link.l1 = "Oh, nothing special... And you look like a military man. Are you still in the service?";
			link.l1.go = "OffM_2";
		break;
		case "OffM_2":
			dialog.text = "Not anymore, I'm fired.";
			link.l1 = "I see. And who were you in the army?";
			link.l1.go = "OffM_4";
		break;
		case "OffM_4":
			dialog.text = "A Musketeer. I was the best marksman in the regiment!";
			link.l1 = "Ha, I need people like that. Would you like to join my team as an officer?";
			link.l1.go = "OffM_5";
		break;
		case "OffM_5":
			dialog.text = "Thanks for the offer, but I have to decline.";
			link.l1 = "Tell me, why? If it's not a secret, of course...";
			link.l1.go = "OffM_6";
		break;
		case "OffM_6":
			dialog.text = "It's all about the mental trauma. I can't take up arms!";
			link.l1 = "It's all strange. But how did you fight in the army?";
			link.l1.go = "OffM_7";
		break;
		case "OffM_7":
			dialog.text = "You see, I got an English musket in my day, which is a lot of money. Two guns, an upgraded breech, allowing me to charge faster. In general, a real work of art, the work of a master.\n"+
				"And I've become so attached to this weapon that I don't recognize anything else.";
			link.l1 = "And where is this miracle musket now?";
			link.l1.go = "OffM_8";
		break;
		case "OffM_8":
			dialog.text = "Ehh, it hurts even to remember... When I sailed here from the Old World, we were attacked by pirates. I wanted to open fire on them, and believe me, I would have killed a lot of these thugs. But our team attacked me and pinned me down!..";
			link.l1 = "Trust me, they did the right thing. At least you're still alive.";
			link.l1.go = "OffM_9";
		break;
		case "OffM_9":
			dialog.text = "Alive, but without my musket! And what kind of life is this!..";
			link.l1 = "Well, maybe there's another one like that...";
			link.l1.go = "OffM_10";
		break;
		case "OffM_10":
			dialog.text = "Is there any? Hmm, listen, if you find my double-barrel musket, then I'll join you as an officer. I promise.";
			link.l1 = "Well, I get you. And who took over your ship?";
			link.l1.go = "OffM_11";
		break;
		case "OffM_11":
			dialog.text = "It was a couple of years ago, and I've been struggling ever since. I didn't see who those pirates were, I was lying tied up with a bag on my head. The team was screaming about some kind of arrow, but I don't know what it is.";
			link.l1 = "Yeah, the situation... Well, as they say, we will look for it. If I come across your musket, I will definitely bring it here.";
			link.l1.go = "OffM_12";
		break;
		case "OffM_12":
			dialog.text = "Thank you. I'll be looking forward to it.";
			link.l1 = "Good.";
			link.l1.go = "exit";
			pchar.questTemp.mushket2x2 = true;
			AddQuestRecord("SeekDoubleMushket", "1");
			NextDiag.TempNode = "OffM_result";
		break;

		case "OffM_result":
			dialog.text = "Did you find my musket?";
			if (CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = "Yes, my friend, I found it. Here it is, a double-barrel musket, there is no other like it.";
				link.l1.go = "OffM_result_1";
			}
			else
			{
				link.l1 = "Not yet. But I'm doing it.";
				link.l1.go = "exit";
			}
		break;
		case "OffM_result_1":
			dialog.text = "Great! Well, life is just beginning!";
			link.l1 = "Good. Now I am waiting for the fulfillment of your promise to become my officer.";
			link.l1.go = "OffM_result_2";
			TakeItemFromCharacter(pchar, "mushket2x2");
			Npchar.quest.OfficerPrice = sti(pchar.rank)*300;
		break;
		case "OffM_result_2":
			dialog.text = "My word is ironclad. I'm ready. Just let's discuss the amount of my fee. For my faithful service, I want to receive " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice)) + "per month.";
			link.l1 = "Don't you think it's too much?";
			link.l1.go = "OffM_trade";
			link.l1 = "Well, okay, I agree.";
			link.l1.go = "OffM_Ok";
		break;
		case "OffM_trade":
			dialog.text = "No, I'm worth a lot more.";
			link.l1 = "Well, okay, I agree.";
			link.l1.go = "OffM_Ok";
		break;
		case "OffM_Ok":
			Npchar.quest.OfficerPrice.add = sti(pchar.rank)*1000;
			dialog.text = "Good. But that's not all. I demand a lump sum, so to speak. I've been out of work, so I have to pay my debts. I think that " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice.add)) + " will suit me.";
			link.l1 = "What?!!";
			link.l1.go = "OffM_Ok_1";
		break;
		case "OffM_Ok_1":
			dialog.text = "And nothing else... In general, decide.";
			if (sti(pchar.money) < sti(Npchar.quest.OfficerPrice.add))
			{
				link.l1 = "I don't have enough money.";
				link.l1.go = "OffM_noMoney";
			}
			else
			{
				link.l1 = "It's very expensive for me.";
				link.l1.go = "OffM_noMoney";
				link.l2 = "Okay, I agree.";
				link.l2.go = "OffM_Ok_3";
			}
			NextDiag.TempNode = "OffM_TWO";
		break;
		case "OffM_noMoney":
			dialog.text = "So come as soon as you get rich. Good luck.";
			link.l1 = "Thank you...";
			link.l1.go = "exit";
		break;
		case "OffM_Ok_3":
			dialog.text = "Well, now it's a completely different matter! I am ready to serve you faithfully.";
			link.l1 = "Great. Welcome to the team.";
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			AddQuestRecord("SeekDoubleMushket", "3");
			CloseQuestHeader("SeekDoubleMushket");
			pchar.questdata.NaitiMushket = 1;
			AddMoneyToCharacter(pchar, -sti(Npchar.quest.OfficerPrice.add));
			npchar.perks.list.Gunman = "1";
			AddItems(npchar, "bullet", 50);
			AddItems(npchar, "GunPowder", 50);
			npchar.IsMushketer = true;
			Npchar.CanTakeMushket = true;
			npchar.model = "MusketeerEnglish_2";
			// Прописка всех моделей для кирас. -->
        	npchar.HeroModel = "MusketeerEnglish_2,MusketeerEnglish_2_1,MusketeerEnglish_2_2,MusketeerEnglish_2_3,MusketeerEnglish_2_4,MusketeerEnglish_2_5,MusketeerEnglish_2,MusketeerEnglish_2,MusketeerEnglish_2";
	        // Прописка всех моделей для кирас. <--
			npchar.model.animation = "mushketer";
			GiveItem2Character(npchar, "mushket2x2");
			npchar.IsMushketer.LastGunID = -1;
			npchar.equip.gun = "mushket2x2";
			EquipCharacterByItem(NPChar, "mushket2x2");
			npchar.IsMushketer.MushketID = "mushket2x2";
			npchar.MusketerDistance = 10.0;
			npchar.isMusketer = true;
			npchar.isMusketer.weapon = true;
			npchar.greeting = "Gr_questOfficer";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			LAi_MethodDelay("FrameGiveMushket",0.1);
			DialogExit();
		break;
		case "OffM_TWO":
			dialog.text = "Well, how are you doing financially? Let me remind you that I want to " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice.add)) + " one-time allowance and " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice)) + "monthly earnings.";
			if (sti(pchar.money) < sti(Npchar.quest.OfficerPrice.add))
			{
				link.l1 = "No, I won't pull it yet...";
				link.l1.go = "OffM_noMoney";
			}
			else
			{
				link.l1 = "It's very expensive for me.";
				link.l1.go = "OffM_noMoney";
				link.l2 = "Okay, I agree.";
				link.l2.go = "OffM_Ok_3";
			}
			NextDiag.TempNode = "OffM_TWO";
		break;
	}
}


void GetPerlShore()
{
	switch (rand(5))
	{
		case 0:
			pchar.questTemp.Sharp.PearlAreal = "Mein";
			pchar.questTemp.Sharp.PearlAreal.Island = "Beliz";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore_ship2";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_8";
			pchar.questTemp.Sharp.PearlAreal.add = ". It's near Belize.";
			break;
		case 1:
			pchar.questTemp.Sharp.PearlAreal = "Mein";
			pchar.questTemp.Sharp.PearlAreal.Island = "Cumana";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore18";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_8";
			pchar.questTemp.Sharp.PearlAreal.add = ". It's near Cumana.";
			break;
		case 2:
			pchar.questTemp.Sharp.PearlAreal = "Dominica";
			pchar.questTemp.Sharp.PearlAreal.Island = "Dominica";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore26";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_3";
			break;
		case 3:
			pchar.questTemp.Sharp.PearlAreal = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Island = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore56";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
			break;
		case 4:
			pchar.questTemp.Sharp.PearlAreal = "Caiman";
			pchar.questTemp.Sharp.PearlAreal.Island = "Caiman";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore17";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
			break;
		case 5:
			pchar.questTemp.Sharp.PearlAreal = "StLucia";
			pchar.questTemp.Sharp.PearlAreal.Island = "StLucia";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore65";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";		//ЕСТЬ ли локатор Quest_ship_1 на СантаЛюсии?
			break;
	}
	pchar.questTemp.Sharp.PearlAreal.terms = rand(5) + 5; //сроки
	pchar.questTemp.Sharp.PearlAreal.qtyShips = rand(6) + 6; //кол-во тартан ловцов
	pchar.questTemp.Sharp.PearlAreal.SmallPearlQty = 0; //для итогового подсчёта
	pchar.questTemp.Sharp.PearlAreal.BigPearlQty = 0;
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаём кэпов
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_" + npchar.index, "", "man", "man", Rank, iNation, -1, true));
	switch (npchar.quest.SeekCap)
	{
		case "manSlave":
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
		break;
		case "manRapeWife":
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
		break;
		case "manFriend":
			SetCaptanModelByEncType(sld, "trade");
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
		break;
		case "womanHasband":
			SetCaptanModelByEncType(sld, "trade");
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
		break;
		case "womanRevenge":
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
		break;
		case "womanPirates":
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "Sinking Percent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "Sinking Percent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
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
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	npchar.quest.gem = GenQuestCitizen_GenerateGem(); //камешки
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	Log_TestInfo("The Wanted Cap" + sld.id + " out of: " + sld.city + " and headed to: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "Galleon_red"; break; //стояла модель кораблекрушенца ranger
		case "womanHasband": sld.mapEnc.worldMapShip = "Galleon_red"; break; //стояла модель кораблекрушенца ranger
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city)) + 1; //дней доехать даём с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 2;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestCitizen_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";
		break;
		case 1:
			itemID = "jewelry2";
		break;
		case 2:
			itemID = "jewelry3";
		break;
		case 3:
			itemID = "jewelry4";
		break;
		case 4:
			itemID = "jewelry5";
		break;
		case 5:
			itemID = "jewelry17";
		break;
	}
	return itemID;
}
