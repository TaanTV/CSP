
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;
	int Shit, i;
	ref refStore;
	ref sld;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "First time":
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				if ((sti(pchar.Ship.Type) != SHIP_NOTUSED) && !CheckCharacterPerk(pchar, "UnlimitedContra"))
				{
					if (GetCompanionQuantity(pchar) > 1 && GetBaseHeroNation() != PIRATE)
					{
						dialog.text = NPCStringReactionRepeat("Listen, they clearly told you at the tavern to come with one ship. Get out and get rid of your squadron.",
							"You should get out of here. Otherwise we'll hand you over to the patrol ourselves.",
							"Come on, get in the boat and get out.",
							"You've tired me out...", "block", 1, npchar, Dialog.CurrentNode);
						link.l1 = HeroStringReactionRepeat("Okay, okay, I'll be right back on the flagship.",
							"Don't swear, I'll just run to the port authority, hand over the extra ships, and immediately go back.",
							"Eh-h, it was not possible to cheat...",
							"Yes, I'm persistent!", npchar, Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
						break;
					}
					//редкостная хрень, но по-другому не работает-класс корабля ГГ считается отдельно от компаньонов, и всё тут
					int iClass, ipClass;
					ipClass = 4-sti(RealShips[sti(pchar.ship.type)].Class);
					iClass = 3;//т.к. не пройдёт по числу кораблей в любом случае
					if (GetBaseHeroNation() == PIRATE)
					{
						ipClass = sti(ipClass)-1;
						int iChIdx;
						// поиск старшего класса компаньонов
						for (i=0; i<COMPANION_MAX; i++)
						{
							iChIdx = GetCompanionIndex(GetMainCharacter(), i);
							if (iChIdx>=0)
							{
								sld = GetCharacter(iChIdx);
								iClass = GetCharacterShipClass(sld);
							}
						}
					}
					if (sti(ipClass) > 0 || 3 - sti(iClass) > 0)
					{
						dialog.text = NPCStringReactionRepeat("Didn't they tell you not to show up on such a conspicuous vessel? You should have brought a couple more mans with you. Get out and come on a smaller ship.",
							"You should get out of here. Otherwise we'll hand you over to the patrol ourselves.",
							"Come on, get in the boat and get out.",
							"You've tired me out...", "block", 1, npchar, Dialog.CurrentNode);
						link.l1 = HeroStringReactionRepeat("Okay, okay, I'll change the boat.",
							"Don't get mad, I'll be right there-one foot here, the other there.",
							"Eh-h, it was not possible to cheat...",
							"Yes, I'm persistent!", npchar, Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
						break;
					}
				}
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("Hey, what are you doing here, "+ GetSexPhrase("buddy", "girlfriend") +"?",
                                          RandSwear() + "What do you want here?!");
				Link.l1 = RandPhraseSimple("Relax, man, I brought goods!", "What are you looking at? I brought goods!");
				Pchar.quest.Contraband.Counter = 0; // не торговали
				if ((Pchar.Location == Pchar.location.from_sea) && (sti(pchar.Ship.Type) != SHIP_NOTUSED))
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
				{
					Link.l2 = "I'm here by order of the governor of " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "! I order you to lay down your weapons and follow me-you are under arrest!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true) //если заплатил, то разговаривают, иначе посылают
				{
					dialog.Text = RandPhraseSimple("Yeah, finally!!! Here you are, otherwise we've been waiting for quite a while. Come on, we're leaving.", "Move it, there are patrols everywhere. We need to get out of here faster!");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "I'm here by order of the governor of " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "! I order you to lay down your weapons and follow me-you are under arrest!";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "And who are you? We agreed to deliver one passenger, not a crowd.";
						Link.l1 = "Oops...";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("Who are you? We agreed to deliver the passenger, not captain.", "Get out! Don't come until you get rid of your ship.");
						Link.l1 = "Oh, damn...";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень...
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
							dialog.Text = "Patrol! We don't know you, you don't know us.";
							Link.l1 = "Yeah...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("Thanks for the help. We will not forget this. Let's go.", "Well done! You fought well.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "I'm on my way.";
					Link.l2.go = "Exit";
					
					//поместим Грея в локацию.
					refStore = CharacterFromID("Abracham_Gray");
					ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
					refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
					refStore.dialog.CurrentNode = "Travel_talkStart";
					//поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
					PChar.GenQuest.contraTravel.ship = true;
					PChar.quest.Munity = "";  // признак выхода с палубы

					SetLaunchFrameFormParam("It's gone" + sti(Pchar.GenQuest.contraTravel.destination.days) + " days " + NewStr() + "The deck of the smugglers' ship.",
																	"Reload_To_Location", 0.1, 5.0);
											bQuestCheckProcessFreeze = true;
					WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
					bQuestCheckProcessFreeze = false;
					MakeCloneShipDeck(refStore, true); // подмена палубы
					SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
					AddDialogExitQuest("LaunchFrameForm");
					AddCharacterExpToSkill(Pchar, "Sneak", 50);
				}
				else
				{
					if (CheckAttribute(NPChar, "ContrabandInterruption")) // если таможня уже бежит
					{
						if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
						{
							if (chrDisableReloadToLocation)
							{
								dialog.Text = RandSwear()+ "Patrol! We don't know you, you don't know us!";
								Link.l1 = "Exactly!";
								Link.l1.go = "Exit";
								break;
							}
							dialog.Text = RandPhraseSimple("Thanks for the help. We will not forget this. Let's go.", "Well done! You fought well.");
							ChangeContrabandRelation(PChar, 5);
							DeleteAttribute(PChar, "GenQuest.contraTravel.PatrolFight");
							ContrabandInterruptionSetStatus(false);
							AddCharacterExpToSkill(Pchar, "Sneak", 50);
							Link.l2 = "I'm on my way.";
							Link.l2.go = "Exit";
							break;
						}
					}
					else
					{
						dialog.Text = "Listen, get out of here! If you break the deal, we'll gut you!";
						Link.l1 = "I think I still have something to sell.";
						Link.l1.go = "Exchange1";
						Link.l2 = RandPhraseSimple("Do you dare threaten me, dog?", "You'll choke on your words, you rascal!");
						Link.l2.go = "Exit_fight";
						Link.l3 = "Come on, I know what business is. See you later.";
						Link.l3.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "On your back, or what? Where is your ship?";
			Link.l1 = RandPhraseSimple("At first I wanted to make sure there's no catch here.", "I didn't want to risk the ship. I prefer to look at everything with my own eyes first.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "The deal is off!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "We are honest people, and we do not live by deception. Bring your ship, but be careful - so that the coastal patrol does not follow you.";
			Link.l1 = "Good. Wait for me here.";
			Link.l1.go = "Exit";
		break;

		case "Exit_fight":
			//DeleteAttribute(Pchar, "quest.Contraband");
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
			DeleteAttribute(Pchar, "quest.Contraband.price1");
			DeleteAttribute(Pchar, "quest.Contraband.price2");
			DeleteAttribute(Pchar, "quest.Contraband.price3");
			DeleteAttribute(Pchar, "quest.Contraband.price4");
			DeleteAttribute(Pchar, "quest.Contraband.price5");
			DeleteAttribute(Pchar, "quest.Contraband.price6");
			DeleteAttribute(Pchar, "quest.Contraband.price7");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX1");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX2");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX3");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX4");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX5");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX6");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX7");
			DeleteAttribute(Pchar, "quest.Contraband.sum");
			DeleteAttribute(Pchar, "quest.Contraband.ChooseGoodsQty");
			DeleteAttribute(Pchar, "quest.Contraband.ChooseGoodsID");

			AddSimpleRumourCity("Have you heard? Recently, a patrol raided smugglers in the bay. And what would you think? The captain, who was shipping goods to local buyers, managed to get away! " +
				"Dashing guys turned out to be on his team - the whole patrol squad was put down. And our locals have disappeared into the water. So nothing but corpses was found in the bay - neither the goods, nor the hiding place, nor the smugglers themselves. That's how these crooks have their fishing organized!", Pchar.quest.contraband.City, 3, 5, "");

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			//#20190121-01
			//LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			//#20190121-01
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Exit_Cancel":
			DeleteAttribute(Pchar, "quest.Contraband");
			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Cancellation":
			if (sti(Pchar.quest.Contraband.Counter) == 0)
			{
				dialog.Text = "Cancelled? Are you kidding?";
				Link.l1 = "Absolutely serious.";
				Link.l1.go = "Cancellation_1";
			}
			else
			{
				dialog.Text = "Well, that's fine. We've traded well enough as it is.";
				Link.l1 = "Exactly!";
				Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = "Dog! You can't fool us like that! You will pay for this with your head!";
					Link.l1 = "But that's unlikely!";
					Link.l1.go = "Exit_fight";
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "You can't get away with this!";
					Link.l1 = "Go bark somewhere else, dogs!";
					Link.l1.go = "Exit_cancel";
				}
			}
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "You're going to regret this!";
				Link.l1 = "Well, well!";
				Link.l1.go = "Exit_cancel";
			}
		break;

		case "GenQuestKillContraband_1":
			//счётчик подстав по "metro"...
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //репу контры вниз
			}
			dialog.Text = "You're going to answer to us now for such a setup!";
			Link.l1 = "Then you will all die. I have a clear order - in case of resistance, do not take the living!";
			Link.l1.go = "Exit_fight";
		break;

		case "Exchange":
			// сама торговля -->
			if(FindFirstContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
			{
				dialog.Text = "Well, what are you doing here? You don't have anything to sell! Everything you have in your hold can be bought in the city!";
				Link.l1 = "Bad luck.";
				Link.l1.go = "Exit";
			}
			else
			{
				// установим окружение -->
				if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
				{
					if(drand(11) == 3)
					{
						dialog.Text = "Well, well... I think we'll pick up your goods for free. You're hardly going to complain to the authorities.";
						Link.l1 = "Well, try it!";
						Link.l1.go = "Exit_fight";
										break;
					}
					// море и солдаты на суше НЕЗАВИСИМЫ!!!
					if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < dRand(12))
					{
						SetCoastalGuardPursuit();
					}
					// при убегании от патруля на карту - корабли трём
					SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// если в порту сидим, спим, то 2 день

					Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
					Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
				}
				// установим окружение <--
				dialog.Text = RandPhraseSimple("So, what kind of cargo do you want to sell?",
																	"What are you selling?");
				Link.l1 = "Well, let's see.";
				Link.l1.go = "Exchange1";
				if (sti(Pchar.quest.Contraband.Counter) == 0)
				{
					Link.l99 = "I think I've changed my mind.";
					Link.l99.go = "Cancellation";
				}
			}
		break;

		case "Exchange1":
			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId),  sti(pchar.FindContrabandGoods.StoreIdx));
		break;

		case "Finish_exit":
			// таможня на суше
			if(GetSummonSkillFromName(pchar, "Sneak") < Rand(120) && !CheckAttribute(pchar, "quest.Contraband.InterruptionGot"))
			{
				Pchar.GenQuest.contraTravel.PatrolFight = true;
				Pchar.quest.Contraband.InterruptionGot = true;
				DoQuestCheckDelay("Rand_ContrabandInterruption", 0.1);
				ContrabandInterruptionSetStatus(true);
			}
			if (!CheckAttribute(pchar, "quest.Contraband.SneakGot"))
			{
				pchar.quest.Contraband.SneakGot = true;
				AddCharacterExpToSkill(Pchar, "Sneak", 100);
				SetTimerCondition("ContraСlearGot", 0, 0, 1, false);
			}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -1);

			CloseQuestHeader("Gen_Contraband");

			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
			DeleteAttribute(Pchar, "quest.Contraband.price1");
			DeleteAttribute(Pchar, "quest.Contraband.price2");
			DeleteAttribute(Pchar, "quest.Contraband.price3");
			DeleteAttribute(Pchar, "quest.Contraband.price4");
			DeleteAttribute(Pchar, "quest.Contraband.price5");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX1");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX2");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX3");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX4");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX5");
			DeleteAttribute(Pchar, "quest.Contraband.sum");
			DeleteAttribute(Pchar, "quest.Contraband.ChooseGoodsQty");
			DeleteAttribute(Pchar, "quest.Contraband.ChooseGoodsID");

			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
		break;
	}
}
