// это всякая мелочь по изабелле: кэп брига, брат, офицер при аресте и пр.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
			dialog.text = "Buenos dias, senor! Aren't you captain of that ship that's in the roadstead?";
			link.l1 = "Are you captain of the Five Wounds of Christ?";
			link.l1.go = "ShipToDomingoTavenr_2";
			link.l2 = "No, it's not me.";
			link.l2.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ShipToDomingoTavenr_2":
			dialog.text = "That's the one, sir.  Damn the storm!  My brig won't be at sea for a long time.  Carramba!  And I, as a sin, took a passenger.  How he swears, Mother of God!"+
				          "He promises to skin me, but I won't plug all the cracks in the bottom with my ass.  He desperately needs to go to San Juan, and not a single ship goes there. The lord is noble, noble, I would be glad to serve him, but I can't!";
			link.l1 = "Is your passenger by any chance Don Miguel de Valdez? I could take him to San Juan.";
			link.l1.go = "ShipToDomingoTavenr_3";
		break;

		case "ShipToDomingoTavenr_3":
            NextDiag.TempNode = "ShipToDomingoTavenr_Temp";
			dialog.text = "Yes, sir! Exactly! Don Miguel de Valdez!  Oh, senor, God bless you!";
			link.l1 = "Well, please make him happy and send him to my ship. I'll be waiting for him at the port.";
			link.l1.go = "exit";
			Pchar.quest.Romantic_Brother.win_condition.l1           = "location";
        	Pchar.quest.Romantic_Brother.win_condition.l1.location  = "Cumana_town";
        	Pchar.quest.Romantic_Brother.win_condition              = "Romantic_Brother";
        	Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
        	AddQuestRecord("Romantic_Line", "6");
			npchar.LifeDay = 2;
            SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;

		case "ShipToDomingoTavenr_Temp":
            NextDiag.TempNode = "ShipToDomingoTavenr_Temp";
            dialog.text = "Oh, senor, God bless you!";
			link.l1 = "Everything happens. We'll settle up.";
			link.l1.go = "exit";
		break;
		// братан Изабеллы
		case "Romantic_Brother_1":
            NextDiag.TempNode = "Romantic_Brother_2";
            dialog.text = "Good afternoon! You are captain " + GetFullName(Pchar)+"? I am Don Miguel de Valdez. I'm heading to San Juan.";
			link.l1 = "Welcome aboard, Don Miguel. Yes, I am captain " + GetFullName(Pchar)+". I hope the trip will be pleasant for you.";
			link.l1.go = "Step_1";
		break;
		case "Step_1":
			AddQuestRecord("Romantic_Line", "7");
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Sailing", 40);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddPassenger(pchar, NPChar, false);
			SetCharacterRemovable(NPChar, false);
            Pchar.quest.Romantic_Brother_port.win_condition.l1           = "location";
        	Pchar.quest.Romantic_Brother_port.win_condition.l1.location  = "SanJuan_town";
        	Pchar.quest.Romantic_Brother_port.win_condition              = "Romantic_Brother_port";
            // немного весёлой жизни
            TraderHunterOnMap();
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Romantic_Brother_2":
            NextDiag.TempNode = "Romantic_Brother_2";
            dialog.text = "Thanks for the help!";
			link.l1 = "Believe me, this is not a burden to me at all.";
			link.l1.go = "exit";
		break;

		case "Romantic_Brother_port_1":
            NextDiag.TempNode = "Romantic_Brother_2";
            dialog.text = "Thank you. Now let's go visit my sister.";
			link.l1 = "Please. Of course.";
			link.l1.go = "Step_2";
		break;
		case "Step_2":
			RemovePassenger(pchar, NPChar);
            Pchar.quest.Romantic_Brother_House.win_condition.l1           = "location";
        	Pchar.quest.Romantic_Brother_House.win_condition.l1.location  = "SanJuan_houseSp6";
        	Pchar.quest.Romantic_Brother_House.win_condition              = "Romantic_Brother_House";
            chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "houseSp6", "", "goto", "goto4", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Romantic_Brother_Thanks":
            NextDiag.TempNode = "Romantic_Brother_Thanks";
            dialog.text = "Captain, thank you very much for the service rendered. It's great that you ended up in Cumana. We can't expect help from Salvator...";
			link.l1 = "Never mind, Miguel. Everything is fine. The main thing is for your sister to be happy...";
			link.l1.go = "Step_3";
		break;
		case "Step_3":
            dialog.text = "We look forward to seeing you tonight, Captain.";
			link.l1 = "I will definitely be there, Miguel.";
			link.l1.go = "exit";
		break;
		//разборки Сальватора с братом
		case "TalkNearHouse_1":
            dialog.text = "Scammer! You're the one who stole my sister's money on fake bills! A thief and a murderer!";
			link.l1 = "Yes, it's me! I needed the money like hell! And you hold your tongue, puppy, or I'll cut it off for you quickly! And your sister too...";
			link.l1.go = "TalkNearHouse_2";
		break;
		case "TalkNearHouse_2":
            dialog.text = "If you don't get hung up before that, you scoundrel! They won't stand on ceremony with people like you here! You'll be behind bars tomorrow!";
			link.l1 = "You chose your own destiny, puppy!";
			link.l1.go = "TalkNearHouse_3";
		break;
		case "TalkNearHouse_3":
			DialogExit();
			AddDialogExitQuest("Romantic_DeadBrother_1");
		break;
		//офицер в доме Сальватора при аресте
		case "ArrestInHome_2":
			ref rColony = GetColonyByIndex(FindColony("SanJuan"));
			if (sti(rColony.HeroOwn))
			{
				dialog.text = "Captain ?!.. I'm sorry, we've been informed that there is a murderer here!";
				link.l1 = "Relax. The killer just slipped away. If you hadn't tried to detain me...";
				link.l1.go = "ArrestInHome_5";
			}
			else
			{
				dialog.text = "Captain " + GetFullName(pchar) + ", In the name of the law, you are under arrest!";
				link.l1 = "Officer, this scoundrel Salvator Olevares is the real killer. He ruined his wife with forged bills!";
				link.l1.go = "ArrestInHome_3";
			}
		break;
		case "ArrestInHome_3":
			dialog.text = "Do you have proof? Where are these bills?";
			if (CheckCharacterItem(pchar, "Order"))
			{
				link.l1 = "I have them, officer!";
				link.l1.go = "ArrestInHome_Have";
			}
			else
			{
				link.l1 = "Miguel talked about them, I heard it myself...";
				link.l1.go = "ArrestInHome_NotHave";
			}
		break;
		case "ArrestInHome_Have":
			dialog.text = "Okay, let's figure it out. I believe they will be accepted for consideration. In the meantime, hand over your weapons and follow me!";
			link.l1 = "Surrender to mercy?! No, I have serious doubts that everything will be considered correctly.";
			link.l1.go = "ArrestInHome_4";
		break;
		case "ArrestInHome_4":
			dialog.text = "In that case, Captain, I will be forced to use force.";
			link.l1 = "And in this case, I will be forced to resist illegal arrest.";
			link.l1.go = "FightInHouse";
		break;

		case "ArrestInHome_NotHave":
			dialog.text = "Captain, your testimony will be heard by the commandant. Now hand over your weapons and follow me!";
			link.l1 = "Carramba, it seems that my business is bad - I have nothing but my word!";
			link.l1.go = "ArrestInHome_4";
		break;
		case "ArrestInHome_4":
			dialog.text = "This will be decided by the court... Hand over your weapons immediately!";
			link.l1 = "Hmm... No, Officer, I'd rather leave. And I don't advise you to try to stop me...";
			link.l1.go = "FightInHouse";
		break;

		case "FightInHouse":
			DialogExit();
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation("SanJuan_houseSp6")], false);
			AddQuestRecord("Romantic_Line", "10");
		break;

		case "ArrestInHome_5":
			dialog.text = "I'm sorry, but I couldn't know it was you. I'm sorry again...";
			link.l1 = "Come on, I'll try to catch up with this scoundrel. Well, you're free!";
			link.l1.go = "exit";
			AddQuestRecord("Romantic_Line", "31");
		break;
		//засада в доме Сальватора, диалог с наёмным убийцей
		case "AmbushBandit":
			dialog.text = "So-so... It seems that we have waited...";
			link.l1 = "Did you wait for me? And who do I have the honor to talk to?";
			link.l1.go = "AmbushBandit_1";
		break;
		case "AmbushBandit_1":
			dialog.text = "We've been waiting for you, dear, you...";
			link.l1 = "How nice it is when someone is waiting for you...";
			link.l1.go = "AmbushBandit_fight";
		break;
		case "AmbushBandit_fight":
			LAi_LocationFightDisable(&locations[FindLocation("SanJuan_houseSp6")], false);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Romantic_Line", "12");
		break;
		//абордаж брига, где Изабеллу типа держат
		case "BrigAbordage":
			dialog.text = "Damn it! Why the hell did you attack my ship?!!";
			link.l1 = "You have two problems, Captain: you contacted the wrong person and took the wrong one on board.";
			link.l1.go = "BrigAbordage_1";
		break;
		case "BrigAbordage_1":
			dialog.text = "Express yourself more clearly...";
			link.l1 = "I'm picking up Isabella Olevares and you're telling me where Salvator is. In this case, you stay alive.";
			link.l1.go = "BrigAbordage_2";
		break;
		case "BrigAbordage_2":
			dialog.text = "Otherwise?";
			link.l1 = "Otherwise I'll kill you right now, you scoundrel!";
			link.l1.go = "BrigAbordage_3";
		break;
		case "BrigAbordage_3":
			dialog.text = "Well, we'll see who kills who...";
			link.l1 = "Hmm, the previous fight wasn't enough for you? Well, let's see...";
			link.l1.go = "BrigAbordage_4";
		break;
  		case "BrigAbordage_4":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("Romantic_TaklInCabinBrig");
            pchar.quest.Romantic_BrigDieHard.over = "yes";
			pchar.quest.Romantic_AfterBrigSunk.over = "yes";
            Island_SetReloadEnableGlobal("PortoBello", true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//засада в Порто Белло
		case "AmbushPotroBello":
			dialog.text = "Finally, we've been waiting! Greetings to captain of the brig 'Enthusiastic'. Where's the lady?";
			link.l1 = "Isabella?";
			link.l1.go = "AmbushPotroBello_1";
		break;
		case "AmbushPotroBello_1":
			dialog.text = "Yeah, Isabella.";
			link.l1 = "On my ship.";
			link.l1.go = "AmbushPotroBello_2";
		break;
		case "AmbushPotroBello_2":
			dialog.text = "So bring her here... Or wait, don't - we'd better go to your ship ourselves and strangle her quietly. She shouldn't be walking around the city.";
			link.l1 = "Why bring her here from San Juan?";
			link.l1.go = "AmbushPotroBello_3";
		break;
		case "AmbushPotroBello_3":
			dialog.text = "It's not for you to decide, buddy...";
			link.l1 = "Hmm, that's right, this is Salvator's case. And where is Salvator himself? Doesn't he want to say goodbye to his wife?";
			link.l1.go = "AmbushPotroBello_4";
		break;
		case "AmbushPotroBello_4":
			dialog.text = "He's not here, he's gone on business. So we do our job-and we're free.";
			link.l1 = "Understood... And where is Salvator doing? How do I find him?";
			link.l1.go = "AmbushPotroBello_5";
		break;
		case "AmbushPotroBello_5":
			dialog.text = "Salvator finds those he needs on his own, and only Salvator knows where Salvator is now... Hey, you're being nosy about something!";
			link.l1 = "That's right, I'm not captain of the brig 'Enthusiastic', but captain who sent the brig 'Enthusiastic' to the bottom...";
			link.l1.go = "AmbushPotroBello_6";
		break;
		case "AmbushPotroBello_6":
			dialog.text = "It should have been so stupid! That's it, buddy, it's time for you to die...";
			link.l1 = "Thank you, but I think I'll stay until then...";
			link.l1.go = "AmbushPotroBello_7";
		break;
		case "AmbushPotroBello_7":
			LAi_LocationFightDisable(&locations[FindLocation("PortoBello_houseF2")], false);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Romantic_TalkPortoBello");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//доставка Изабеллы Росите в Белиз
		case "Rosita":
			dialog.text = "Welcome to my house, senor. Who are you?";
			link.l1 = "Hello, senora. My name is Captain " + GetFullName(pchar) + ", I guess my name won't tell you anything.";
			link.l1.go = "Rosita_1";
		break;
		case "Rosita_1":
			dialog.text = "Yes, I don't know it. So to what do I owe the honor of seeing you in my house?";
			link.l1 = "Senora, I am acting on behalf of your cousin, Isabella Olevares.";
			link.l1.go = "Rosita_2";
		break;
		case "Rosita_2":
			dialog.text = "Continue, senor.";
			link.l1 = "Senora Isabella has expressed a desire to come to you, and I have gladly fulfilled this request of hers.";
			link.l1.go = "Rosita_3";
		break;
		case "Rosita_3":
			dialog.text = "My God, Captain, did you really bring Isabella here alive and unharmed?!";
			link.l1 = "That's right, senora. She is on my ship and is now preparing to land.";
			link.l1.go = "Rosita_4";
		break;
		case "Rosita_4":
			dialog.text = "Ah, senor, I do not even know how to thank you! A chain of tragic misfortunes befell Isabella, she lost her father and brother, and her husband disappeared! You can't imagine...";
			link.l1 = "Not at all, senora, I know all this. Tell me, has Salvator Olevares appeared at your place?";
			link.l1.go = "Rosita_5";
		break;
		case "Rosita_5":
			dialog.text = "No, he wasn't here, he disappeared without a trace. Why are you asking about him, Captain?";
			link.l1 = "I think it would be better if Isabella tells you everything herself. I have made sure that your house is safe for Isabella and I will send her to you now. Take care of her, senora, she's been through a lot lately...";
			link.l1.go = "Rosita_6";
		break;
		case "Rosita_6":
			dialog.text = "Thank you for everything you have done for Isabella, senor " + pchar.name + ". I will pray for you...";
			link.l1 = "Okay, Senora Rosita, I won't mind - pray.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rosita_after";
            Pchar.quest.Romantic_BelizCityTalk.win_condition.l1 = "location";
            Pchar.quest.Romantic_BelizCityTalk.win_condition.l1.location = "Beliz_town";
            Pchar.quest.Romantic_BelizCityTalk.win_condition = "Romantic_BelizCityTalk";
			//снимем прерывания на засады на всякий случай
			pchar.quest.Romantic_AmbushInHouse.over = "yes";
			pchar.quest.Romantic_AmbushInPortoBello.over = "yes";
		break;
		case "Rosita_after":
			dialog.text = "Captain" + GetFullName(pchar) + ", I'm glad to see you.";
			link.l1 = "Likewise, senora.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rosita_after";
		break;
		//Росита переживает, что Изабелла пропала
		case "BackRosita":
			dialog.text = "Oh, it's you, Captain " + pchar.name + ". How timely! Thank God he sent you!";
			link.l1 = "What happened, Rosita? Was Salvator here?";
			link.l1.go = "BackRosita_1";
		break;
		case "BackRosita_1":
			dialog.text = "No, Salvator was not there. But something happened to Isabella! She's gone!";
			link.l1 = "How did she disappear? When?";
			link.l1.go = "BackRosita_2";
		break;
		case "BackRosita_2":
			dialog.text = "Yesterday morning she went to the market with a maid, and no one has seen her since!";
			link.l1 = "Senora Rosita, I'm going on a search right now!";
			link.l1.go = "BackRosita_3";
		break;
		case "BackRosita_3":
			dialog.text = "May St. Francis help you!";
			link.l1 = "Okay...";
			link.l1.go = "exit";
			NextDiag.TempNode = "BackRosita_after";
			pchar.RomanticQuest = "SeekIsabella";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1 = "locator";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.locator_group = "quest";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.locator = "detector1";
			pchar.quest.SeekIsabella_exitTown.function = "SeekIsabella_exitTown";
			AddQuestRecord("Romantic_Line", "21");
			//миортвая служанка
			sld = GetCharacter(NPC_GenerateCharacter("ServantGirl", "girl_6", "woman", "towngirl", 5, SPAIN, 30, false));
			LAi_SetActorType(sld);
			LAi_ActorSetLayMode(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_ExitTown", "goto", "goto17");
			locations[FindLocation("Beliz_ExitTown")].DisableEncounters = true; //энкаутеры запретим
			//охранник Изабеллы в шахте
            sld = GetCharacter(NPC_GenerateCharacter("Bandit", "officer_6", "man", "man", 35, PIRATE, -1, true));
            FantomMakeCoolFighter(sld, 35, 85, 75, "topor2", "pistol3", 60);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			ChangeCharacterAddressGroup(sld, "Beliz_Cave_2", "goto", "goto4");
			LAi_LocationDisableOfficersGen("Beliz_Cave_2", true); //офицеров не пускать
			LAi_LocationDisableMonstersGen("Beliz_Cave_2", true); //монстров не генерить
			pchar.quest.Romantic_BanditIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.Romantic_BanditIsDead.win_condition.l1.character = "Bandit";
			pchar.quest.Romantic_BanditIsDead.win_condition = "Romantic_BanditIsDead";
		break;
		case "BackRosita_after":
			dialog.text = "Have you found Isabella?!";
			link.l1 = "Not yet, senora, I'm looking for...";
			link.l1.go = "exit";
		break;
		//если Изабелла погибла где-нить при похищении
		case "IsabellaIsDead_Beliz":
			dialog.text = "Captain, have you found Isabella?";
			link.l1 = "Yes, Rosita, I found it. But on the way to the city, we were attacked and Isabella died...";
			link.l1.go = "IsabellaIsDead_Beliz_1";
			NextDiag.TempNode = "IsabellaIsDead_Beliz_after";
		break;
		case "IsabellaIsDead_Beliz_1":
			dialog.text = "I can't believe it... She was hoping so much for you! God rest her soul...";
			link.l1 = "Rosita, I'm dying of grief!!";
			link.l1.go = "exit";
		break;
		case "IsabellaIsDead_Beliz_after":
			dialog.text = "Captain, I don't want to see you, goodbye.";
			link.l1 = "Goodbye, Rosita...";
			link.l1.go = "exit";
		break;
		//после спасения Изабеллы в пещере
		case "SavedIsabella":
			dialog.text = "Isabella!!";
			link.l1 = "Rosita!";
			link.l1.go = "SavedIsabella_1";
		break;
		case "SavedIsabella_1":
			dialog.text = "You're okay! Thank the Lord!";
			link.l1 = "Now, and always, and forever...";
			link.l1.go = "SavedIsabella_2";
		break;
		case "SavedIsabella_2":
			dialog.text = "What happened? Where have you been? And where is Kanchita?";
			link.l1 = "Rosita, Salvator kidnapped me. And Kanchita is dead-my husband killed her...";
			link.l1.go = "SavedIsabella_3";
		break;
		case "SavedIsabella_3":
			dialog.text = "Bastard! We need to report everything to the governor so that he immediately arrests Salvator!";
			link.l1 = "Salvator is dead too. My guardian angel found me and rescued me from captivity... Salvator attacked him too, but was killed in front of my eyes.";
			link.l1.go = "SavedIsabella_4";
		break;
		case "SavedIsabella_4":
			dialog.text = "Isabella, is this nightmare finally over?";
			link.l1 = "Yes, Rosita, it's over...";
			link.l1.go = "SavedIsabella_5";
		break;
		case "SavedIsabella_5":
			dialog.text = "Once again, your faithful knight solved all the problems... Isabella, you are very lucky to have such an admirer!";
			link.l1 = "Ah, cousin, it really is! Rosita, I'll tell you about other news later, but for now, let's not delay my savior.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SavedIsabella_after";
			AddDialogExitQuest("Romantic_DelivToRosita_2");
		break;
		case "SavedIsabella_after":
			dialog.text = "Captain, you really are a real man!";
			link.l1 = "Hmm, Rosita, thanks for the compliment...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SavedIsabella_after";
		break;
		//Нападения на ГГ и Изабеллу в церкви
		case "AmbushInChurch":
			dialog.text = "Captain, greetings from Salvator!";
			link.l1 = "Salvator is dead, calm down...";
			link.l1.go = "AmbushInChurch_1";
		break;
		case "AmbushInChurch_1":
			dialog.text = "Unfortunately, the fun is paid for, cap, and only the customer can cancel everything...";
			link.l1 = "I repeat once again: Salvator is dead! Is nothing sacred to you? It's a wedding in the temple of God!";
			link.l1.go = "AmbushInChurch_2";
		break;
		case "AmbushInChurch_2":
			dialog.text = "That's it, the time for talking is over...";
			link.l1 = "Argh!..";
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_fightInChurch_1");
		break;
		//базар с Роситой после убийства Изабеллы
		case "IsabellaIsDead":
			dialog.text = "Captain " + GetFullName(pchar) + ", glad to see you. What's the news? Have you married Isabella yet?";
			link.l1 = "The news couldn't be worse, Rosita. Isabella is dead, she was murdered in the church right on the altar. There were too many attackers...";
			link.l1.go = "IsabellaIsDead_1";
		break;
		case "IsabellaIsDead_1":
			dialog.text = "Oh, my God, poor Isabella!! She suffered so much, she was so unlucky with her husband\n"+
				          "Then you came along and I thought that her fate had finally changed for the better. But you can't escape fate, apparently...";
			link.l1 = "Oh, Rosita, how hard it is for me!..";
			link.l1.go = "IsabellaIsDead_2";
		break;
		case "IsabellaIsDead_2":
			dialog.text = "I understand you, Captain... I'm sorry, I have to notify all my relatives - we need to put on mourning...";
			link.l1 = "Yes, Rosita, I understand...";
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			NextDiag.TempNode = "IsabellaIsDead_after";
		break;
		case "IsabellaIsDead_after":
			dialog.text = "Captain, what did you want?";
			link.l1 = "Nothing, Rosita, I just wanted to visit my Isabella's cousin...";
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsDead_after";
		break;
		//базар с Роситой, если ГГ отбился в церкви
		case "IsabellaIsMyWife":
			dialog.text = "Senior " + pchar.name + ", glad to see you! We're related now!";
			link.l1 = "Yes, Senora Rosita. We got married to Isabella...";
			link.l1.go = "IsabellaIsMyWife_1";
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = "That's fine, Captain. Isabella deserves more than that scoundrel Salvator!";
			link.l1 = "I completely agree with you. And I don't even want to think about Salvatore, I sent him to his forefathers and I'm very satisfied with that...";
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = "Senior " + pchar.name + ", you are a real knight! Take care of Isabella... By the way, if you have problems with her, quarrel, for example, then you are always welcome to come to me - I will be glad to help.";
			link.l1 = "Okay, Cousin Rosita...";
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
		break;
		case "IsabellaIsMyWife_after":
			dialog.text = "Nice to see you, cousin " + pchar.name + "!";
			link.l1 = "Likewise, Senora Rosita.";
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
		break;
		//семейная жизнь ГГ
		case "IsabellaIsWife":
			dialog.text = NPCStringReactionRepeat("Hello, cousin. I'm so glad to see you! How is Isabella?",
				"Are you coming to see me again, cousin? We just talked.",
				"Cousin, what is it again?! You won't hear anything new from me!",
				"Listen, Captain, if you are such a bore at home, then I feel sorry for my poor cousin Isabella!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Hello, Cousin Rosita. Isabella is fine.",
				"Yes, that's right, just now... Excuse me, Rosita, I won't distract you...",
				"Yes? Well, okay then...",
				"No, Rosita, at home I am an angel in the flesh...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("IsabellaIsWife_1", "none", "none", "none", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "IsabellaIsWife";
		break;
		case "IsabellaIsWife_1":
			dialog.text = "Is there something you wanted to ask me, Captain?";
			link.l1 = "No, Rosita, I just came to check on you.";
			link.l1.go = "exit";
			if (pchar.RomanticQuest == "over")
			{
				link.l2 = "Rosita, I don't even know how to say it... Isabella has closed the door in the house and won't let me in!";
				link.l2.go = "HorseCheck";
				break;
			}
			if (pchar.RomanticQuest == "TheDoosIsClosed")
			{
				link.l2 = "Rosita, I don't even know how to say it... Isabella has closed the door in the house and won't let me in!";
				link.l2.go = "TheDoosIsClosed";
			}
			sld = characterFromID("Isabella");
			if (CheckAttribute(sld, "angry")) //если Изабелла сидит на ангри
			{
				if (sld.angry.name == "NewLife_Budget_Pay")
				{
					link.l3 = "You know, Rosita, I had money problems here and Isabella was very offended by me...";
					link.l3.go = "Budget";
				}
				if (sld.angry.name == "NewLife_KnowPirates")
				{
					link.l4 = "Can you imagine, Rosita, Isabella somehow found out that I didn't completely quit privateering, as I promised before the wedding...";
					link.l4.go = "KnowPirates";
				}
				if (sld.angry.name == "NewLife_Present")
				{
					link.l5 = "Rosita, here's the deal... In general, Isabella is very sulky at me, she does not want to communicate with her husband. That's it!";
					link.l5.go = "Present";
				}
			}
		break;
		case "TheDoosIsClosed":
			dialog.text = "Understood... You must have committed a serious offense, Captain. Have you been away from home for a long time?";
			link.l1 = "Hmm, well, how to say it... In general, yes. But I'm a sailor, Rosita, and my job is to go to sea all the time.";
			link.l1.go = "TheDoosIsClosed_1";
		break;
		case "TheDoosIsClosed_1":
			dialog.text = "I understand, Captain... Well, I can handle this case. Go home, everything will be fine...";
			link.l1 = "Rosita, you are just a miracle!";
			link.l1.go = "TheDoosIsClosed_2";
		break;
		case "TheDoosIsClosed_2":
			dialog.text = "Don't over-praise me, " + pchar.name + ". I would advise you to come to your senses and be at home more often.";
			link.l1 = "Cousin, I will definitely do just that. Goodbye...";
			link.l1.go = "exit";
			AddQuestRecord("Romantic_Line", "30");
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			pchar.RomanticQuest = "OpenTheDoosOfHouse";
		break;

		case "Budget":
			dialog.text = "What, such debts?";
			link.l1 = "Yes, Rosita. Isabella asked me several times to pay off the debt, but, as luck would have it, I didn't have any money then.";
			link.l1.go = "Budget_1";
		break;
		case "Budget_1":
			dialog.text = "Hmm, bad... Well, I'll tell you what you need to do. Bring her emeralds as a gift: a ring, a necklace and just a stone. She loves these stones very much and I think she will melt...";
			link.l1 = "I think I'll do it! Thank you, Rosita. Goodbye.";
			link.l1.go = "exit";
		break;

		case "KnowPirates":
			dialog.text = "Hmm, cousin, I'm sorry for the question, but 'not really' - how is that?";
			link.l1 = "Well, you know, they attack me themselves, but what can I do? Attack, of course!";
			link.l1.go = "KnowPirates_1";
		break;
		case "KnowPirates_1":
			dialog.text = "Hmm, I see... So you, Captain, have absolutely nothing to do with it?";
			link.l1 = "That's right, cousin, the exact definition of my involvement in piracy!";
			link.l1.go = "KnowPirates_2";
		break;
		case "KnowPirates_2":
			dialog.text = "Clear... Well, the only advice I can give is to appease Cousin Isabella.";
			link.l1 = "Yes, please, but with what?";
			link.l1.go = "KnowPirates_3";
		break;
		case "KnowPirates_3":
			dialog.text = "Different stones and more. For example, I would give you a sapphire, a diamond, a ruby, a large pearl, and a gold ring with a ruby in addition...";
			link.l1 = "Hmm, that's a thought!.. Thank you, Rosita, I will do so, cousin! Goodbye...";
			link.l1.go = "exit";
		break;

		case "Present":
			dialog.text = "What happened?";
			link.l1 = "Oh, nothing special... I decided to give her a gift here, but I couldn't find anything suitable.";
			link.l1.go = "Present_1";
		break;
		case "Present_1":
			dialog.text = "Hmm, it's okay... Cousin, there's something you're not telling me.";
			link.l1 = "Yes, I was running around and forgot that I had already offered her a gift... In general, I offered it again. And so four times...";
			link.l1.go = "Present_2";
		break;
		case "Present_2":
			dialog.text = "You've had too much, Captain! Who's going to put up with this?!";
			link.l1 = "It's clear that I overdid it, but what should I do now?";
			link.l1.go = "Present_3";
		break;
		case "Present_3":
			dialog.text = "Do this: finally give her a gift. Take three gold nuggets and five silver bars. I think Isabella will melt...";
			link.l1 = "Oh, Cousin Rosita, what would I do without you! I'll run to look for gold and silver. Goodbye...";
			link.l1.go = "exit";
		break;

		case "HorseCheck":
			dialog.text = "Yes, I know that. And I want to tell you the following, Captain - your marriage is terminated unilaterally.";
			link.l1 = "What kind of business is this? Didn't the Pope himself terminate it?";
			link.l1.go = "HorseCheck_1";
		break;
		case "HorseCheck_1":
			dialog.text = "The marriage is de facto dissolved, you will never see Isabella again.";
			link.l1 = "I don't understand anything, but what is it being done?";
			link.l1.go = "HorseCheck_2";
		break;
		case "HorseCheck_2":
			dialog.text = "Don't you know? Well, then I'll tell you what's the matter.";
			link.l1 = "Yes, be so kind.";
			link.l1.go = "HorseCheck_3";
		break;
		case "HorseCheck_3":
			dialog.text = "You should have run around the brothels less, my dear! Isabella can forgive a lot, but never treason!";
			link.l1 = "Damn!! And who told her? I was slandered!";
			link.l1.go = "HorseCheck_4";
		break;
		case "HorseCheck_4":
			dialog.text = "There is no need to be hypocritical, the information received by Isabella is more than reliable. Goodbye, Captain...";
			link.l1 = "Eh... Goodbye, Rosita...";
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			NextDiag.TempNode = "HorseCheck_Bue";
			CloseQuestHeader("Romantic_Line");
			pchar.questdata.IstoriyaIzabely = 1;
		break;
		case "HorseCheck_Bue":
			dialog.text = "I don't want to talk to you anymore.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "HorseCheck_Bue";
		break;
	}
}
