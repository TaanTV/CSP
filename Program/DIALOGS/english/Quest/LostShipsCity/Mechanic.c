
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	string sTemp;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Hello! So you are "+ GetSexPhrase("the hero who managed", "the heroine who managed") +"get through to me?";
			link.l1 = "Yes, that's me.";
			link.l1.go = "FT_1";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
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
			dialog.text = LinkRandPhrase("Yes you are a thief!!! Violation of the Law of the City!", "Wow! As soon as I looked at it, you went straight into the chest with your head!", "Police! They're robbing!!! Hold "+ GetSexPhrase("him, he violated", "her, she violated") +"The Law!");
			link.l1 = "Ah, the devil!!!";
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = "Oh, so that's how it is?! Are you going to rummage through the chests?! Now the citizens and the police will tear you up like an old rag!";
			link.l1 = "What a fool!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you should hide your weapon. And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the weapon away.", "serious man"+ GetSexPhrase("girl", "...") +"...");
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
				dialog.text = NPCharSexPhrase(NPChar, "Careful on turns, "+ GetSexPhrase("buddy", "girlfriend") +", when you run with a gun in your hand. I can get nervous...", "I don't like when "+ GetSexPhrase("men", "all sorts") +" walk in front of me with weapons at the ready. It scares me...");
				link.l1 = RandPhraseSimple("Understood.", "I'm removing.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;


		case "FT_1":
			dialog.text = "Good, very good... Please identify yourself, "+ GetSexPhrase("my esteemed friend", "beautiful Amazon") +".";
			link.l1 = "My name is captain " + GetFullName(pchar) + ". And you, as far as I can tell, are Henrik Wedeker, nicknamed the Mechanic.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "That's right!.. And how do we know me?";
			link.l1 = "Oh, better not ask, it's a long story...";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Still, I would listen. You see, for a long time I was deprived of communication with normal people. The 'Caspers' - and they tried not to communicate with me. By the way, about the Casper clan. Did you put them all down?";
			link.l1 = "Every single one. And before that, I killed whole Narwhal clan.";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Hehe, so the City is now devoid of robbers? Well, I take off my hat, as they say, and now please tell me why you performed these impressive feats.";
			link.l1 = "How can I tell you... You see, I got to this island, investigating the death of Teaser Dan. Well, now I want to get out of here.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Teaser Dan? Did you know Teaser?";
			link.l1 = "I didn't have a chance to meet personally, but I can say that he got safely to the Mainland. Unfortunately, he was killed by agents of the Dutch West India Company.";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "Sorry. You know, it was I who built him the raft on which he went from here to the ocean.";
			link.l1 = "Yes?! And how did he get to you through the Casper?";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "He often sailed on the Fernando Diffindur. On one of these swims, I was on my platform, preparing a dive...";
			link.l1 = "Dive?";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "Yes... I'll explain later. So, we got to know each other, talked, and I did everything so that he would sail away from here and tell people about this island.";
			link.l1 = "Although he got to the goal, it was the stories about the City that caused his death. The Dutch West India Company believes that huge wealth is concentrated in the City, and their sudden appearance on the market could bring down prices. In this case, commerce will go to hell.";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "Clear. So, Teaser still kept his promise to me to the end, even despite the threat to his life. Damn it, it's a pity that he died!";
			link.l1 = "It's a pity, of course. You know, so many good people have died lately that I'm already tired of regret...";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = "Well, let's not talk about sad things. You know, this Dutch company of yours is right about the values of the City. There are a lot of things here. And even more - under water...";
			link.l1 = "Seriously? And how do you know?";
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = "I saw it with my own eyes... Well, that, again, is later. Now tell me, "+ GetSexPhrase("my friend", "sweet girl") +", what's going on in the City and why you came to me.";
			link.l1 = "Admiral Chad Capper is in charge of the city. The citizens of the city live according to the food of the Law, one of which prohibits the construction of any swimming facilities. Well, I accidentally found out about Mechanic and decided to talk to you at any cost. That's all, actually...";
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = "Chad Capper firmly holds the reins of the City, as before...";
			link.l1 = "Well, I wouldn't say that securely. Two clans are destroyed one after the other, and citizens are being killed. People are unhappy with the admiral and his militia, because it is their responsibility to ensure security!";
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = "You know, "+ GetSexPhrase("my friend", "girl") +"I wouldn't be surprised at all if it turns out that the admiral is behind everything that is happening in the City anyway.";
			link.l1 = "Well, not really. Now I'm playing my game. And the proof of this is the absence of the Casper clan on the barque San Gabriel.";
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = "Hmm, the 'caspers' acted in conjunction with the Capper, so I have to agree with you... Well, thanks to you, life in the City has changed significantly...";
			link.l1 = "Right! And now I propose the election of an admiral. I want to stand for this position.";
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = "What choices, "+ GetSexPhrase("my friend", "girl") +"! We need to save our lives before it's too late...";
			link.l1 = "What are you talking about?";
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			dialog.text = "Do you know why they call me Mechanic?";
			link.l1 = "I know. You have come up with a way to attach the ships of the City to each other. Anyway, as far as I've heard, making something like that is not a problem for you.";
			link.l1.go = "FT_17";
		break;
		case "FT_17":
			dialog.text = "Okay. You probably realize that I know more about the City than any other resident. Besides, now I'm not making assumptions, I'm saying everything absolutely precisely, since I studied the structure of the City of Abandoned Ships under water.";
			link.l1 = "Under water?";
			link.l1.go = "FT_18";
		break;
		case "FT_18":
			dialog.text = "Yes. A few years ago, I made a suit for breathing underwater. I went underwater in this suit many times while I had the opportunity. And I'll tell you what - the city will surely be destroyed by a strong storm.";
			link.l1 = "As far as I know, storms are not uncommon here...";
			link.l1.go = "FT_19";
		break;
		case "FT_19":
			dialog.text = "Here you are too! Don't argue with me, it's a matter of life and death!";
			link.l1 = "Good, good... So what were you saying about breathing underwater?";
			link.l1.go = "FT_20";
		break;
		case "FT_20":
			dialog.text = "I went underwater, studied the reefs. So, the city is supported by only three ships that are hooked on the reefs. The rest of the ships are simply linked to these three! Do you understand what this means?";
			link.l1 = "Well, it's unpleasant to realize that... And what happens if the City breaks away? Are we going to drift?";
			link.l1.go = "FT_21";
		break;
		case "FT_21":
			dialog.text = "Nothing like that! Everything will go down, because the ships of the City are not afloat. No one will survive, as the destruction of the City will take place in a storm, and a very strong storm.";
			link.l1 = "Some kind of apocalypse... And when will that happen?";
			link.l1.go = "FT_22";
		break;
		case "FT_22":
			dialog.text = "I don't know. I'm a scientist, not a medium at all, it can happen in any storm.";
			link.l1 = "Hmm... And what should I do?";
			link.l1.go = "FT_23";
		break;
		case "FT_23":
			dialog.text = "I can help you if you help me.";
			link.l1 = "Interesting suggestion. Tell me more about it, please.";
			link.l1.go = "FT_24";
		break;
		case "FT_24":
			dialog.text = "The fact is that I have a ship afloat. A couple of years ago, a ship of unprecedented design washed up to the City in a storm, there is an interesting marking on the market: 'Baltimore Shipyards', but this is nonsense, Baltimore is just a rundown village on the shore! Where did the shipyards come from? The design and technical characteristics of the ship are simply incredible! I learned from scraps of the ship's log that this was the clipper Ariel, home port of Boston. I was there, a bustling commercial port and I did not see such ships there. There were a couple of minor holes and broken rigging, nothing serious. We managed to patch it up pretty quickly. While I had the opportunity...";
			link.l1 = "There are a lot of strange things going on here in the New World. Undead, ancient Indian gods, aliens from other times... Maybe this is one of them. You have already mentioned several times about some lost opportunity...";
			link.l1.go = "FT_25";
		break;
		case "FT_25":
			dialog.text = "Ah, well, this is an opportunity to go underwater in my suit. The fact is that there are hefty creatures under the water that walk along the bottom and eat everything they can. So I'm not risking going down now. I'm a scientist, not a fighter...";
			link.l1 = "Understood. So, I owe to do it?";
			link.l1.go = "FT_26";
		break;
		case "FT_26":
			dialog.text = "First you have to buy a clipper from me. Then get something from the bottom, without which we will not be able to free the ship from the ships that are squeezing it.";
			link.l1 = "Buy?! Hmm, aren't you interested in getting out of here and saving your own skin? After all, in the event of the apocalypse you predict, you will die too!";
			link.l1.go = "FT_27";
		break;
		case "FT_27":
			dialog.text = "Well, I don't know exactly when the disaster will happen. Besides, I see that you are "+ GetSexPhrase("a brave and active person", "a brave and active girl") +", and you will be quite able to fulfill my conditions. Moreover, I'm not asking for much, just one and a half million for a clipper and the opportunity to go underwater once.";
			link.l1 = "One and a half million?! Did I hear correctly?";
			link.l1.go = "FT_28";
		break;
		case "FT_28":
			dialog.text = "No, that's right.";
			link.l1 = "But I don't have enough money!";
			link.l1.go = "FT_29";
		break;
		case "FT_29":
			dialog.text = "Well, money is not a problem here, "+ GetSexPhrase("my friend", "" + pchar.name + "") +". Look for it, and I think you can easily find the amount I need, since the City is literally stuffed with valuables. In addition, you can borrow from Augusto Brahms, he willingly lends up to a million coins.";
			link.l1 = "Heh, there are all sorts of bad rumors about him... They say he's a warlock.";
			link.l1.go = "FT_30";
		break;
		case "FT_30":
			dialog.text = "Well, that's where you go too. Look, I'm a scientist, obscurantism is alien to me... Anyway, I'll give you the opportunity to go down the water, and there's even more money!";
			link.l1 = "Yes, but there are also some creatures living there!";
			link.l1.go = "FT_30_1";
		break;
		case "FT_30_1":
			dialog.text = "But you've dealt with the Casper, and you can handle this problem... Well, why are you timid?! As if it wasn't you who just put down a whole horde of thugs...";
			link.l1 = "Okay, I agree.";
			link.l1.go = "FT_31";
		break;
		case "FT_31":
			dialog.text = "Well, that's great! I'm waiting for you with money, "+ GetSexPhrase("my friend", "lady") +", and this is only the first question. Now you need to go to Chad Capper, tell him that I'm free, so to speak... But no elections! Otherwise, he will kill you.";
			link.l1 = "I realized that the election is not worth it.";
			link.l1.go = "FT_32";
		break;
		case "FT_32":
			dialog.text = "They just won't happen, that's all... In general, tell Chad hello from me, notify him about the destruction of the 'Casper'. I don't think he'll be happy about it, but it needs to be done.";
			link.l1 = "Why?";
			link.l1.go = "FT_33";
		break;
		case "FT_33":
			dialog.text = "But he'll find out anyway if he hasn't found out yet. Therefore, it would be good to notify him on behalf of the hero of the occasion, so to speak. You need to be very careful with Chad, otherwise...";
			link.l1 = "What else?";
			link.l1.go = "FT_34";
		break;
		case "FT_34":
			dialog.text = "Otherwise he will kill you, "+ GetSexPhrase("my friend", "dear") +". It's not worth angering the admiral, and you did it. Chad had dealings with the Caspers, and I heard in conversations that he was preparing to sail out of Town with them.";
			link.l1 = "Interesting... Why doesn't he let the others in?";
			link.l1.go = "FT_35";
		break;
		case "FT_35":
			dialog.text = "So that no one finds out about the city before the deadline set by the Child.";
			link.l1 = "Understood... Well, I got it all. Bye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CheckMillion";
			pchar.questTemp.LSC = "fromMechanicToAdmiral";
			Npchar.quest.money = 0; //счётчик бабла, отданного Механику
			AddQuestRecord("ISS_MainLine", "40");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("", "a"));
			AddQuestUserData("ISS_MainLine", "sSex2", GetSexPhrase("en", "on"));
		break;

		//проверка миллиона
		case "CheckMillion":
			dialog.text = "Well, how's it going with my money?";
			if (sti(pchar.money) < 20000)
			{
				link.l1 = "I've not collected yet.";
				link.l1.go = "CheckMillion_noMoney";
			}
			else
			{
				link.l1 = "Something is available. I'm ready to give you a certain amount.";
				link.l1.go = "OffM_GiveMoney";
			}
			NextDiag.TempNode = "CheckMillion";
		break;
		case "CheckMillion_noMoney":
			dialog.text = "Well, try hard, I think you will succeed.";
			link.l1 = "I think so too.";
			link.l1.go = "exit";
		break;
		case "OffM_GiveMoney":
			dialog.text = "How much?";
			link.l1 = "";
			Link.l1.edit = 6;
			link.l1.go = "OffM_GiveMoney_1";
		break;
		case "OffM_GiveMoney_1":
			iTemp = sti(dialogEditStrings[6]);
			if (iTemp <= 0)
			{
				dialog.text = "Are you kidding?";
				link.l1 = "Hmm, sorry, I mistaken..";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Hmm, you don't have enough money with you, unfortunately. Let's not be silly...";
				link.l1 = "Um... All right.";
				link.l1.go = "exit";
				break;
			}
			Npchar.quest.money = sti(Npchar.quest.money) + iTemp;
			AddMoneyToCharacter(pchar, -iTemp);
			if (sti(Npchar.quest.money) < 1500000)
			{
				dialog.text = "Well, great! Now you have given me " + FindRussianMoneyString(iTemp) + ", in total you have brought me " + FindRussianMoneyString(sti(Npchar.quest.money)) + ". You just need to get more " + FindRussianMoneyString(1500000 - sti(Npchar.quest.money)) + ".";
				link.l1 = "I will continue the search.";
				link.l1.go = "exit";
				AddQuestRecord("ISS_MainLine", "41");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
				AddQuestUserData("ISS_MainLine", "iMoney1", sti(Npchar.quest.money));
				AddQuestUserData("ISS_MainLine", "iMoney2", 1500000 - sti(Npchar.quest.money));
			}
			else
			{
				dialog.text = "Well, it's done. I have received the required amount, now the clipper is yours.";
				link.l1 = "Very good. What's next?";
				link.l1.go = "FreeCorvett";
			}
		break;
		//освобождние корвета
		case "FreeCorvett":
			dialog.text = "Now the ship needs to be released. The fact is that it is located on the outer ring of the island's ship junk and is squeezed by debris from all sides.";
			link.l1 = "Well, how do I do it?";
			link.l1.go = "FreeCorvett_1";
		break;
		case "FreeCorvett_1":
			dialog.text = "I have already prepared everything. I have a winch on the platform, to which I have attached the debris around the clipper. So it's only necessary to activate the mechanism - and voila, the ship is free!";
			link.l1 = "Sounds great. What's the catch?";
			link.l1.go = "FreeCorvett_2";
		break;
		case "FreeCorvett_2":
			dialog.text = "Yes, there really is a catch. I dropped the gear from the winch mechanism into the water. This gear needs to be retrieved from the bottom.";
			link.l1 = "So... If my memory serves me correctly, you said that you have a suit for breathing underwater. Is that where I'm going to go down to the bottom?";
			link.l1.go = "FreeCorvett_3";
		break;
		case "FreeCorvett_3":
			dialog.text = "Yes, that's right. I would have done it myself a long time ago, but I'm very afraid. There are these huge creatures there!..";
			link.l1 = "Have you seen them?";
			link.l1.go = "FreeCorvett_4";
		break;
		case "FreeCorvett_4":
			dialog.text = "I saw it, and, to be honest, I wet myself out of fear... So I didn't see it in detail. In general, of course, there is nothing surprising that this voracious population exists under the City.";
			link.l1 = "Well, maybe they're harmless? How do you know that they are voracious?";
			link.l1.go = "FreeCorvett_5";
		break;
		case "FreeCorvett_5":
			dialog.text = "So they live by what is thrown overboard by the residents of the City! That's the only reason these creatures have settled here.";
			link.l1 = "Understood... Well, I'm ready.";
			link.l1.go = "FreeCorvett_6";
		break;
		case "FreeCorvett_6":
			dialog.text = "So let me tell you how to use the suit. The suit is fueled by the compressed air that you breathe. Air lasts for 6 minutes of uninterrupted breathing underwater. During this time you should have time to surface. If that doesn't happen, you're done. Is that clear?";
			link.l1 = "Clearly that I'm limited in my time underwater. The rest is unclear.";
			link.l1.go = "FreeCorvett_7";
		break;
		case "FreeCorvett_7":
			dialog.text = "And this is the main thing you need to remember. Now you can go to the platform, the suit is there, filled with air for one dive. I think you can figure out how to put it on easily. Remember that you can dive only during the day, from ten to nineteen o'clock. After use, put the suit back where you took it. Good luck in the underwater world!";
			link.l1 = "Thank you...";
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor";
			pchar.questTemp.LSC = "toUnderwater";
			pchar.questTemp.LSC.immersions = 0; //количество совершенных погружений
			pchar.questTemp.LSC.immersions.model = pchar.model; //запомним модельку ГГ
			pchar.questTemp.LSC.immersions.animation = pchar.model.animation;
			pchar.questTemp.LSC.immersions.pay = true; //оплачено
			pchar.questTemp.LSC.immersions.pinion = false; //флаг найденной шестерёнки
			AddQuestRecord("ISS_MainLine", "42");
			pchar.Ship.Type = GenerateShipExt(SHIP_CLIPPER, false, pchar);
			SetBaseShipData(pchar);
			pchar.Ship.name = "Ariel";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
			SetCharacterGoods(pchar, GOOD_BALLS, 0);
			SetCharacterGoods(pchar, GOOD_GRAPES, 0);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 0);
			SetCharacterGoods(pchar, GOOD_BOMBS, 0);
			SetCharacterGoods(pchar, GOOD_SAILCLOTH, 0);
			SetCharacterGoods(pchar, GOOD_PLANKS, 0);
			SetCharacterGoods(pchar, GOOD_POWDER, 0);
			SetCharacterGoods(pchar, GOOD_FOOD, 0);
			SetCharacterGoods(pchar, GOOD_WEAPON, 0);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 0);
			SetCrewQuantity(pchar, 0);
			AddSimpleRumourCityTip("You know, a Mechanic has appeared in the City. And they say that he is the oldest resident! Wow...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Have you heard about Henrik Wedeker? That's how it is! It turns out that he was kept locked up on the San Gabriel for many years.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that the new-old resident of the City, a certain Henrik Wedeker, is a very capable person.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("And I don't believe that this Mechanic is so important to the City. How long have we lived without him, we will live even more...", "LostShipsCity", 10, 1, "LSC", "");
			// нулим предметы в каюте
			ref loc;
			int n;
			if (Pchar.SystemInfo.CabinType != "")
			{
				loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; //"My_Cabin"

				for (n = 1; n <= 4; n++)
				{
					sTemp = "box" + n;
					DeleteAttribute(loc, sTemp + ".items");
					loc.(sTemp).items = "";
					loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
					loc.(sTemp).money = 0;
				}
			}
			loc = &locations[FindLocation("My_Deck")];
			for (n = 1; n <= 4; n++)
			{
				sTemp = "box" + n;
				DeleteAttribute(loc, sTemp + ".items");
				loc.(sTemp).items = "";
				loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
				loc.(sTemp).money = 0;
			}
		break;
		//
		case "takeArmor":
			dialog.text = "Well, how are you doing?";
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				link.l1 = "Getting ready to dive. I'll let you know how it went later.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "I need to go down to the bottom again. I did not have time to do everything I wanted.";
				link.l1.go = "DeepAgain";
				if (CheckCharacterItem(pchar, "Pinion"))
				{
					link.l2 = "I found the gear, here it is!";
					link.l2.go = "FoundPinion";
				}
			}
		break;

		case "DeepAgain":
			dialog.text = "I don't mind, the suit is always at your disposal. Just for each dive I have to charge you 30,000 piastres. So the money first.";
			link.l1 = "Do you need money again? I've brought you one and a half million!";
			link.l1.go = "DeepAgain_1";
		break;
		case "DeepAgain_1":
			dialog.text = "This money is the payment for the ship and for one dive. I didn't promise to sell you the suit, I'm keeping it. I'm renting it out to you. Depreciation and all that...";
			link.l1 = "What is the depreciation?";
			link.l1.go = "DeepAgain_2";
		break;
		case "DeepAgain_2":
			dialog.text = "Equipment wear, didn't you know about it? In general, it is useless to argue. Thirty thousand and you're going to the sea devil for a rendezvous. No money, no diving.";
			link.l1 = "Well, not bad...";
			link.l1.go = "DeepAgain_3";
		break;
		case "DeepAgain_3":
			dialog.text = "I don't understand what you're complaining about. I'm giving you the opportunity to earn a lot more. After all, there are a lot of valuables at the bottom. If you went down there for a walk, then excuse me... In general, you need to be more efficient there, at the bottom.";
			link.l1 = "Clear...";
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor2";
		break;

		case "takeArmor2":
			dialog.text = "Well, how are you?";
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				link.l1 = "Gathering my strength for another dive.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "I want to go down to the bottom again.";
				link.l1.go = "DeepAgain2";
				if (CheckCharacterItem(pchar, "Pinion"))
				{
					link.l2 = "I found the gear, here it is!";
					link.l2.go = "FoundPinion";
				}
			}
			if (sti(pchar.questTemp.LSC.immersions.pinion))
			{
				link.l3 = "That's it, I'm done with dives. I'm not interested in the more underwater realm.";
				link.l3.go = "endImmersion";
			}
		break;

		case "DeepAgain2":
			dialog.text = "Have you prepared the money?";
			if (sti(pchar.money) >= 30000)
			{
				link.l1 = "Yes, ready to pay.";
				link.l1.go = "DeepAgain2_1";
			}
			else
			{
				link.l1 = "Not yet... But I will definitely get them.";
				link.l1.go = "exit";
			}
		break;
		case "DeepAgain2_1":
			dialog.text = "Great! Come back tomorrow, I'll get the suit ready for work.";
			link.l1 = "Okay.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -30000);
			SaveCurrentQuestDateParam("questTemp.LSC.immersions");
			NextDiag.TempNode = "readyArmor";
		break;
		case "readyArmor":
			if (GetQuestPastDayParam("questTemp.LSC.immersions") > 0)
			{
				dialog.text = "Everything is fine, the suit is serviceable and filled with air. In general, everything is ready for the dive. Good luck.";
				link.l1 = "Thank you.";
				link.l1.go = "exit";
				pchar.questTemp.LSC.immersions.pay = true; //оплачено
				NextDiag.TempNode = "takeArmor2";
			}
			else
			{
				dialog.text = "The suit is not ready to work. Come back tomorrow.";
				link.l1 = "Okay.";
				link.l1.go = "exit";
			}
		break;

		case "FoundPinion":
			dialog.text = "Great! Let's get her quickly...";
			link.l1 = "Yes, of course.";
			link.l1.go = "FoundPinion_1";
		break;
		case "FoundPinion_1":
			dialog.text = "Well, now I can do the restoration of the winch mechanism. Tell me, will you be diving again?";
			link.l1 = "Yes, I want to examine the bottom in more detail.";
			link.l1.go = "FoundPinion_deep";
			link.l2 = "No, I'm not interested in the underwater kingdom anymore.";
			link.l2.go = "endImmersion";
			TakeItemFromCharacter(pchar, "Pinion");
			pchar.questTemp.LSC.immersions.pinion = true; //нашёл шестерёнку
			AddQuestRecord("ISS_MainLine", "44");
		break;
		case "FoundPinion_deep":
			dialog.text = "Well, sound idea. My terms you know - 30 thousand coins for each dive. Go ahead.";
			link.l1 = "Okay.";
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor2";
		break;

		case "endImmersion":
			dialog.text = "Well, whatever you say. Then I'm canning the suit.";
			link.l1 = "As you know.";
			link.l1.go = "endImmersion_1";
		break;
		case "endImmersion_1":
			dialog.text = "Now that I have everything I need, I will repair the winch mechanism that will free your clipper. It will take me a certain amount of time. You should not rest on your laurels yet, but it is worth carrying out a number of important preparatory activities.";
			link.l1 = "What do you mean?";
			link.l1.go = "endImmersion_2";
		break;
		case "endImmersion_2":
			dialog.text = "First, provide the ship with everything you need. The whole set of ammunition, food, weapons... Well, it's not for me to teach you. Take everything you find to the San Gabriel, and I'll handle the transfer of this stuff to the ship myself.";
			link.l1 = "I got it, I'll try to do everything.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.immersions");
			AddQuestRecord("ISS_MainLine", "45");
			pchar.questTemp.LSC = "toSeekGoods";
			NextDiag.TempNode = "takeGoods";
		break;
		//комплектование корвета товарами
		case "takeGoods":
			NextDiag.TempNode = "takeGoods";
			dialog.text = "Greetings. Well, how are things going with filling the hold of the clipper?";
			npchar.quest.LSC.Balls = false;
			npchar.quest.LSC.Grapes = false;
			npchar.quest.LSC.Knippels = false;
			npchar.quest.LSC.Bombs = false;
			npchar.quest.LSC.Sailcloth = false; //магазин
			npchar.quest.LSC.Planks = false; //магазин
			npchar.quest.LSC.Powder = false;
			npchar.quest.LSC.Food = false; //магазин
			npchar.quest.LSC.Weapon = false;
			npchar.quest.LSC.Medicament = false;
			iTemp = 0;
			npchar.quest.LSC.s0 = "";
			npchar.quest.LSC.s1 = "";
			if (GetCargoGoods(pchar , GOOD_BALLS) >= 100)
			{
				npchar.quest.LSC.Balls = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Balls;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " balls, ";
			if (GetCargoGoods(pchar , GOOD_GRAPES) >= 100)
			{
				npchar.quest.LSC.Grapes = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Grapes;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " grapeshot, ";
			if (GetCargoGoods(pchar , GOOD_KNIPPELS) >= 100)
			{
				npchar.quest.LSC.Knippels = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Knippels;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " knippels, ";
			if (GetCargoGoods(pchar , GOOD_BOMBS) >= 100)
			{
				npchar.quest.LSC.Bombs = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Bombs;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " bombs, ";
			if (GetCargoGoods(pchar , GOOD_SAILCLOTH) >= 50)
			{
				npchar.quest.LSC.Sailcloth = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Sailcloth;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " canvas, ";
			if (GetCargoGoods(pchar , GOOD_PLANKS) >= 50)
			{
				npchar.quest.LSC.Planks = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Planks;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " planks, ";
			if (GetCargoGoods(pchar , GOOD_POWDER) >= 200)
			{
				npchar.quest.LSC.Powder = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Powder;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " gunpowder, ";
			if (GetCargoGoods(pchar , GOOD_FOOD) >= 200)
			{
				npchar.quest.LSC.Food = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Food;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " food, ";
			if (GetCargoGoods(pchar , GOOD_WEAPON) >= 50)
			{
				npchar.quest.LSC.Weapon = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Weapon;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " weapons, ";
			if (GetCargoGoods(pchar , GOOD_MEDICAMENT) >= 50)
			{
				npchar.quest.LSC.Medicament = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Medicament;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " medicines, ";
			if (iTemp < 10)
			{
				if (iTemp == 0)
				{
					link.l1 = "I haven't got anything yet, but I'm trying.";
				}
				else
				{
					sTemp = npchar.quest.LSC.s0;
					npchar.quest.LSC.s0 = strcut(sTemp, 0, (strlen(sTemp)-2));
					sTemp = npchar.quest.LSC.s1;
					npchar.quest.LSC.s1 = strcut(sTemp, 0, (strlen(sTemp)-2));
					link.l1 = "There is already something. Managed to get " + npchar.quest.LSC.s1 + ". It remains to get " + npchar.quest.LSC.s0 + ".";
				}
				link.l1.go = "takeGoods_again";
			}
			else
			{
				link.l1 = "Everything you need for swimming is in my hold.";
				link.l1.go = "TakeCrew";
				DeleteAttribute(pchar, "questTemp.LSC.Balls");
				DeleteAttribute(pchar, "questTemp.LSC.Grapes");
				DeleteAttribute(pchar, "questTemp.LSC.Knippels");
				DeleteAttribute(pchar, "questTemp.LSC.Bombs");
				DeleteAttribute(pchar, "questTemp.LSC.Sailcloth");
				DeleteAttribute(pchar, "questTemp.LSC.Planks");
				DeleteAttribute(pchar, "questTemp.LSC.Powder");
				DeleteAttribute(pchar, "questTemp.LSC.Food");
				DeleteAttribute(pchar, "questTemp.LSC.Weapon");
				DeleteAttribute(pchar, "questTemp.LSC.Medicament");
				DeleteAttribute(pchar, "questTemp.LSC.additional");
			}
		break;
		case "takeGoods_again":
			dialog.text = "Well, good luck. And try not to delay this case.";
			link.l1 = "It's in my best interest.";
			link.l1.go = "exit";
		break;
		//Набор команды
		case "TakeCrew":
			dialog.text = "Fine, "+ GetSexPhrase("my friend", "my dear") +", everything is already placed in the hold of your clipper. Now you need to recruit a team from the residents of the City. You know, we can't handle the ship alone.";
			link.l1 = "Heh, wasn't it possible to say this before? I ran around  whole City in search of goods for the ship, at the same time I could dial a command.";
			link.l1.go = "TakeCrew_1";
		break;
		case "TakeCrew_1":
			dialog.text = "Well, first of all, the admiral would hardly like it. And secondly, I wasn't in a hurry. But now things are taking a very bad turn.";
			link.l1 = "What do you mean?";
			link.l1.go = "TakeCrew_2";
		break;
		case "TakeCrew_2":
			dialog.text = "You see, I've been living for so many years waiting for the storm that will destroy the City, that I'm sick of waiting in ignorance. Not so long ago, I made a device that shows the approach of storms. I called it the 'stormometer'! It's an interesting thing, you know...";
			link.l1 = "Like everything you do... So, what about the bad turn of affairs?";
			link.l1.go = "TakeCrew_3";
		break;
		case "TakeCrew_3":
			dialog.text = "Oh, yeah... So, my stormometer shows that not just a storm is moving towards the City, but a real storm. I don't even know what power it is - the device is off the scale.";
			link.l1 = "It turns out that the time has come?";
			link.l1.go = "TakeCrew_4";
		break;
		case "TakeCrew_4":
			dialog.text = "That's right, "+ GetSexPhrase("my friend", "" + pchar.name + "") +". I can say with a very high probability that the city will be destroyed now. So hurry up.";
			link.l1 = "Okay, I'll do that. By the way, did you manage to free the clipper?";
			link.l1.go = "TakeCrew_5";
		break;
		case "TakeCrew_5":
			dialog.text = "Not yet, but I tried the winch, it is fully ready. Make arrangements with the people, let them arrive here, and I will ferry them to the ship. We need at least fifteen people to sail. As soon as you collect the required amount, immediately run here. Upon your arrival on the San Gabriel, we will use the winch and release the clipper.";
			link.l1 = "Okay, I get you. I'll start making arrangements.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TakeCrewNew";
			AddQuestRecord("ISS_MainLine", "59");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("en", "on"));
			pchar.questTemp.LSC = "toSeekPeopleInCrew";
			pchar.questTemp.LSC.crew = 0; //количество уговорённых людей.
			AddDialogExitQuestFunction("LSC_SmallStormIsBegin");
		break;
		//приём народа в команду
		case "TakeCrewNew":
			if (sti(pchar.questTemp.LSC.crew) > 0)
			{
				dialog.text = "You haven't recruited enough people to swim yet. In total, they came to me " + FindRussianPeoplesString(sti(pchar.questTemp.LSC.crew), "Acc") + ". Go on, and I ask you - quickly...";
			}
			else
			{
				dialog.text = "You haven't talked anyone into joining your team yet. Hurry up!";
			}
			link.l1 = "Okay.";
			link.l1.go = "exit";
		break;
		//разговор в тюрьме
		case "inPrison":
			dialog.text = "Aha, here you are!";
			link.l1 = "Right! Came to rescue you.";
			link.l1.go = "inPrison_1";
		break;
		case "inPrison_1":
			dialog.text = "Well, thanks, I didn't expect it... But it's all for nothing.";
			link.l1 = "How to understand?";
			link.l1.go = "inPrison_2";
		break;
		case "inPrison_2":
			dialog.text = "I am locked in this cell, and the guards took the key to the admiral. It was his order to the commandant. I can't get out of this cage.";
			if (CheckCharacterItem(pchar, "key_mechanic"))
			{
				link.l1 = "The Admiral is no more, I have butchered him. He had this key with him. That one?";
				link.l1.go = "inPrison_3_alt";
			}
			link.l2 = "The Admiral is no more, I have butchered him. But I didn't find any key... I'll come back and look!";
			link.l2.go = "inPrison_3";
		break;
		case "inPrison_3":
			dialog.text = "Late, "+ GetSexPhrase("my friend", "" + pchar.name + "") +". The storm is gaining strength.";
			link.l1 = "I'll make it!";
			link.l1.go = "inPrison_4";
		break;
		case "inPrison_4":
			dialog.text = "No, it's unlikely. And it's not worth risking the clipper and the lives of so many people who are already on it. Listen to what you need to do...";
			link.l1 = "Henrik, I'll make it in time and set you free.";
			link.l1.go = "inPrison_5";
		break;
		case "inPrison_5":
			dialog.text = "I've decided that I'm staying. I will check, as they say, with my own eyes, the correctness of my theory. It is a big deal for a scientist to see with his own eyes the realization of his predictions.Besides, maybe I was wrong, and the city will withstand the onslaught of the elements. Then those who remain here will start a new life, without the clans and the admiral.";
			link.l1 = "Are you sure?";
			link.l1.go = "inPrison_6";
		break;
		case "inPrison_6":
			dialog.text = "Yes, I decided so. Now listen to what you have to do to get on your clipper.";
			link.l1 = "I'm listening.";
			link.l1.go = "inPrison_7";
		break;
		case "inPrison_7":
			dialog.text = "Go to the second mast of the Fernado Diffindura, from there to the ship is just around the corner. I managed to use the winch before the arrest and pulled apart the ships surrounding the clipper. Now you can easily break away from the City.The storm is gaining strength, I'm afraid it's not going to be easy for you right now... When exiting Tartarus, you must clearly imagine where to go - to the right from here. Otherwise, you will die in this chaos. I repeat once again that you must move towards the second mast of the Fernando Diffindura.";
			link.l1 = "I got it, thank you... Maybe we should try to open the damn cage after all?";
			link.l1.go = "inPrison_8";
		break;
		case "inPrison_8":
			dialog.text = "Goodbye, it was a pleasure doing business with you. Now my fate is not your concern...";
			link.l1 = "Goodbye, Henrik Wedeker. I wish you to survive this storm.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("ISS_MainLine", "67");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся", "as"));
			AddDialogExitQuestFunction("LSC_BigStormIsBegin");
		break;
		case "inPrison_3_alt":
			dialog.text = "The one. Let's get him over here, quickly.";
			TakeItemFromCharacter(pchar, "key_mechanic");
			link.l1 = "Hold on. What's next?";
			link.l1.go = "inPrison_4_alt";
		break;
		case "inPrison_4_alt":
			dialog.text = "Go to the second mast of the Fernado Diffindura, from there to the ship is just around the corner. I managed to use the winch before the arrest and pulled apart the ships surrounding the clipper. Now you can easily break away from the City.The storm is gaining strength, I'm afraid it's not going to be easy for you right now... When exiting Tartarus, you must clearly imagine where to go - to the right from here. Otherwise, you will die in this chaos. I repeat once again that you must move towards the second mast of the Fernando Diffindura.";
			link.l1 = "I got it. Thank you.";
			link.l1.go = "inPrison_5_alt";
		break;
		case "inPrison_5_alt":
			dialog.text = "I'll be right behind you. I hope we don't drown.";
			link.l1 = "Me too... Me too...";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("ISS_MainLine", "71");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
			//офицер
			ref sld = GetCharacter(NPC_GenerateCharacter("Mechanic1", "CCS_Mechanic", "man", "man", 30, SPAIN, -1, true));
			sld.name = "Henrik";
			sld.lastname = "Vedeker";
			sld.greeting = "Gr_questOfficer";
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			// Прописка всех моделей для кирас. -->
         	sld.HeroModel = "CCS_Mechanic,CCS_Mechanic_1,CCS_Mechanic_2,CCS_Mechanic_3,CCS_Mechanic_4,CCS_Mechanic_5,CCS_Mechanic,CCS_Mechanic,CCS_Mechanic";
        	// Прописка всех моделей для кирас. <--
			sld.quest.meeting = true;
			SetSelfSkill(sld, 30, 30, 30, 30, 99);
			SetShipSkill(sld, 55, 50, 60, 45, 65, 100, 50, 90, 50);
			SetSPECIAL(sld, 6, 10, 9, 10, 10, 8, 10);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "LightRepair");
			SetCharacterPerk(sld, "InstantRepair");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "Carpenter");
			SetCharacterPerk(sld, "Builder");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			TakeNItems(sld, "talisman7", 1);
			EquipCharacterbyItem(sld, "talisman7");
			sld.quest.OfficerPrice = sti(pchar.rank)*350;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.HalfImmortal = true;  // Контузия
			sld.loyality = MAX_LOYALITY;
			pchar.VedekerDiscount = true;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			AddDialogExitQuestFunction("LSC_BigStormIsBegin");
		break;
	}
}
