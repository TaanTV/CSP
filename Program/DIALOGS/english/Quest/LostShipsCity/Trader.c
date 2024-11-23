
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = "Damn storm! Although it has already begun to decline... I understand that you are "+ GetSexPhrase("new citizen", "new citizen") +" of the City.";
					link.l1 = "Captain " + GetFullName(pchar) + ", in person. And the storm doesn't matter!";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Ah, well, you came to me. I understand that you are "+ GetSexPhrase("new citizen", "new citizen") +" of the City.";
					link.l1 = "Captain " + GetFullName(pchar) + ", in person.";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Would you like to buy or sell something?";
				link.l1 = "Show me what you have there.";
				link.l1.go = "Trade_exit";
				//квест получения карты -->
				if (!CheckAttribute(npchar, "quest.takeMap"))
				{
					link.l2 = "Buddy, I heard you have a map of the city. You know, I could really use it right now. Cause I'm running around here like a blind kitten...";
					link.l2.go = "tekeMap_begin";
				}
				if (CheckAttribute(npchar, "quest.takeMap") && npchar.quest.takeMap == "mapIsToken" && !CheckCharacterItem(pchar, "map_LSC"))
				{
					link.l2 = "Buddy, are you crazy by any chance? Such money for a lousy piece of paper, proudly called a city map?";
					link.l2.go = "tekeMap_off";
				}
				if (CheckAttribute(npchar, "quest.takeMap") && npchar.quest.takeMap == "discount")
				{
					link.l2 = "Listen, buddy, " + npchar.quest.takeMap.name + " she asked me to talk to you again about the map of the City.";
					link.l2.go = "tekeMap_on";
				}
				//<-- квест получения карты
				link.l3 = "Thank you, not interested.";
				link.l3.go = "exit";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(pchar, "questTemp.LSC.goods.trader"))
				{
					link.l8 = "Listen, I want to buy something special from you.";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(pchar, "questTemp.LSC.goods.trader") && sti(pchar.questTemp.LSC.goods.trader))
				{
					link.l8 = "I'm about to buy those goods that you promised me.";
					link.l8.go = "SeekGoodsOk";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Listen, we have a serious conversation. I'm recruiting a team.";
					link.l8.go = "SeekCrew";
				}
				NextDiag.TempNode = "First time";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FS_1":
			dialog.text = "How do you know what's wrong and what's not? Okay, I'm in a bad mood today. My name is " + GetFullName(npchar) + ", I am the owner of this store. Let's get to know each other.";
			link.l1 = "We will.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "Great! And my name is " + GetFullName(npchar) + ", I am the owner of this store. Let's get to know each other.";
			link.l1 = "We will.";
			link.l1.go = "exit";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date") || npchar.quest.takeMap == "changePrice")
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar);
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Why the hell are you climbing into my trunk! Don't you know the law of the City? Well, now you'll find out...", "Hey, citizen, what are you doing? The law forbids you to do that! I'll punish you...", "Wait, where are you going? We have a thief in Town!! Well, now hold on...");
			link.l1 = LinkRandPhrase("Devil!!", "Carramba!!", "Oh, damn!");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = "Oh, so that's how it is?! Are you going to rummage through the chests?! Now the citizens and the police will tear you up like an old newspaper!";
			link.l1 = "What a fool!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you should take weapons away. And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the weapon away.", "Listen, what are you, like d'Artagnan, running around here, waving your sword? Put away your weapon, it doesn't suit your face "+ GetSexPhrase("serious man", "girl") +"...");
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this city, I ask you not to walk with a naked blade here.", "You know, as a citizen of this city, I ask you not to walk with a naked blade here.");
				link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be Careful on turns, "+ GetSexPhrase("buddy", "girlfriend") +", when you run with a gun in your hand. I can get nervous...", "I don't like when "+ GetSexPhrase("men", "all sorts") +" walk in front of me with weapons at the ready. It scares me...");
				link.l1 = RandPhraseSimple("Understood.", "I'm removing.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = "Always at your service, "+ GetSexPhrase("buddy", "" + pchar.name + "") +". Order it!";
			link.l1 = "Listen, I haven't seen such goods in your assortment yet. These are bombs, knipels, gunpowder, food, canvas, planks, medicines...";
			link.l1.go = "SeekGoods_1";
		break;
		case "SeekGoods_1":
			dialog.text = "Well, from what you told, here the price is only food and canvas, planks and medicines. Nobody needs the rest.";
			link.l1 = "Do you have anything?";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "I can sell you food. It's quite expensive.";
			link.l1 = "I need 20 centners. How much will it cost?";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "Thirty-five thousand coins.";
			link.l1 = "How much?! And with a discount?";
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = "I'm sorry, but there's no discount. I'll throw you canvas and planks for 5,000 gold. All in all, if you want to buy all this, prepare 40 grand.";
			if (sti(pchar.money) >= 40000)
			{
				link.l1 = "I'm ready to pay.";
				link.l1.go = "SeekGoods_5";
			}
			else
			{
				link.l1 = "I don't have enough money.";
				link.l1.go = "SeekGoods_notMoney";
			}
		break;
		case "SeekGoods_notMoney":
			dialog.text = "Well, come back when they are.";
			link.l1 = "Okay.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.goods.trader = true;
		break;

		case "SeekGoods_5":
			dialog.text = "Great, "+ GetSexPhrase("buddy", "" + pchar.name + "") +". Where do you want to unload all this?";
			link.l1 = "Listen, send it all to San Gabriel. The Caspers aren't there anymore, if you don't know...";
			link.l1.go = "SeekGoods_6";
		break;
		case "SeekGoods_6":
			dialog.text = "I'm aware. I'll do everything.";
			link.l1 = "Thank you, buddy.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "46");
			AddMoneyToCharacter(pchar, -40000);
			AddCharacterGoods(pchar, GOOD_FOOD, 200);
			AddCharacterGoods(pchar, GOOD_PLANKS, 50);
			AddCharacterGoods(pchar, GOOD_SAILCLOTH, 50);
			pchar.questTemp.LSC.goods.trader = false;
		break;

		case "SeekGoodsOk":
			dialog.text = "Got the money?";
			if (sti(pchar.money) >= 40000)
			{
				link.l1 = "Yes. And ready to pay.";
				link.l1.go = "SeekGoods_5";
			}
			else
			{
				link.l1 = "Not yet...";
				link.l1.go = "SeekGoods_notMoney";
			}
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("Which command?",
				"We've already talked about this.",
				"This has already been discussed, I repeat for the second time.",
                "That's enough, I'm tired...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("To my ship. I'm leaving town.",
				"yeah... Sorry, I forgot .",
                "As you know...",
				"Well, okay...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "Heh, you're going to go far... You know you're breaking the Law of the City, right?";
			link.l1 = "I know. But I'm saving my life. The fact is that the City will be destroyed by an impending storm.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Well, don't go to a fortune teller either...";
			link.l1 = "Don't you believe me?";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "No, I don't believe it. And I don't want to talk about it anymore.";
			link.l1 = "Hmm... Whatever you want.";
			link.l1.go = "exit";
		break;
		//квест получения карты Города
		case "tekeMap_begin":
			dialog.text = "I understand, it's always like this with new citizens...";
			link.l1 = "So, do you have a map?";
			link.l1.go = "tekeMap_begin_1";
		break;
		case "tekeMap_begin_1":
			dialog.text = "Yes, you were not deceived.";
			link.l1 = "Buddy, I need it.";
			link.l1.go = "tekeMap_begin_2";
		break;
		case "tekeMap_begin_2":
			dialog.text = "Well, buy it. As usual, it is available among other goods.";
			link.l1 = "I understand!";
			link.l1.go = "First time";
			npchar.quest.takeMap = "firstGiveMap";
		break;
		case "tekeMap_off":
			dialog.text = "You didn't understand . Not for the paper, but for what is painted on it.In general, if you don't like it, don't buy it. What problems?";
			link.l1 = "I need this map. But it's too expensive!!!";
			link.l1.go = "tekeMap_off_1";
		break;
		case "tekeMap_off_1":
			dialog.text = "Dear, I'm not haggling. Do you want to run around the City like a fool? If you don't, give me money. I have nothing more to say to you about this.";
			link.l1 = "But I really need this map! Please give in the price.";
			link.l1.go = "tekeMap_off_2";
		break;
		case "tekeMap_off_2":
			dialog.text = ""+ GetSexPhrase("Buddy", "Girlfriend") +", charity is done in the church, and I have a business. So don't even ask - it's useless.";
			link.l1 = "Oh, shit!..";
			link.l1.go = "exit";
			npchar.quest.takeMap = "notTrade"; //поговорили о том, что не торгуется
		break;
		case "tekeMap_on":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				dialog.text = "Okay, I'll lower the price, so be it...";
				link.l1 = "Thank you! And how much will you ask for it now?";
				link.l1.go = "tekeMap_on_1";
			}
			else
			{
				dialog.text = "I'm not aware. " + npchar.quest.takeMap.name + "she hasn't told me anything yet.";
				link.l1 = "I probably haven't had time yet. I'll come back later, and we'll talk about this topic there.";
				link.l1.go = "exit";
			}
		break;
		case "tekeMap_on_1":
			dialog.text = "Let's carry out the sales procedure in the indicated form. I don't like amateur performances.";
			link.l1 = "Okay, whatever you say.";
			link.l1.go = "exit";
			npchar.quest.takeMap = "changePrice"; //снизить цену
		break;

	}
}
