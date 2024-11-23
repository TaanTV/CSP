
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int Rank = sti(pchar.rank) - 4 + MOD_SKILL_ENEMY_RATE*3;
	if (Rank < 1) Rank = 1;
	int Sila = 70 + MOD_SKILL_ENEMY_RATE*3 * 3;
	int DopHP = 60 + MOD_SKILL_ENEMY_RATE*3 * 12;
	int Bonus = sti(pchar.rank);
	if (Bonus <= 6) Bonus = 1;
	if (Bonus >= 7 && Bonus <= 12) Bonus = 1.2;
	if (Bonus >= 13) Bonus = 1.5;
	int Plata1 = 10000 + 1800 * sti(pchar.rank) * Bonus;
	int Plata2 = 20000 + 2000 * sti(pchar.rank) * Bonus;
	int Plata3 = Plata2 * 2;
	pchar.PDM_NK_Plata1.Money = 10000 + 1800 * sti(pchar.rank) * Bonus;
	pchar.PDM_NK_Plata2.Money = 20000 + 2000 * sti(pchar.rank) * Bonus;

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":							//Автор Sinistra
			dialog.text = "Hey, "+ GetSexPhrase("guy", "girl") +"! This is my table, and I'm not looking for company.";
			link.l1 = "But you've already FOUND it. So let's talk.";
			link.l1.go = "Octavio_1_1";
			link.l2 = "I don't want to bother you. Goodbye.";
			link.l2.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\Octavio Lambrini.wav");
		break;

		case "Octavio_1_1":
			dialog.text = "What? Do you dare to bother Octavio Lambrini? Who do you think you are?";
			if (pchar.name == "Peter" && pchar.lastname == "Blood")
			{
				link.l1 = "Yes, in front of you, " + GetFullName(pchar)+". The captain, the noble robber, the doctor and the savior of Bridgetown from the Spaniards. And the name 'Lambrini' doesn't mean anything to me.";
				link.l1.go = "Octavio_1_2";
			}
			if (pchar.name == "Whisper")
			{
				link.l2 = "Yes, I'm in front of you, "+pchar.name+". The captain, a noble robber, a time traveler who has been to the very heart of the Inquisition. And the name 'Lambrini' doesn't mean anything to me.";
				link.l2.go = "Octavio_1_2";
			}
			if (pchar.lastname == "Sharp")
			{
				link.l3 = "My name is " + GetFullName(pchar)+" - I am "+ GetSexPhrase("son", "daughter") +" of the famous pirate, Nicholas Sharp. And the name 'Lambrini' doesn't mean anything to me.";
				link.l3.go = "Octavio_1_2";
			}
			if (pchar.name == "Charles" && pchar.lastname == "de Mor")
			{
				link.l4 = "Yes, in front of you, " + GetFullName(pchar)+". A nobleman, a captain, the savior of the world from the sinister Kukulkan. And the name 'Lambrini' doesn't mean anything to me.";
				link.l4.go = "Octavio_1_2";
			}
			if (pchar.lastname == "Hauk")
			{
				link.l6 = "Yes, in front of you, " + GetFullName(pchar)+". Captain, "+ GetSexPhrase("noble robber", "noble robber") +" and the one who sent the Black Pearl to the bottom. And the name 'Lambrini' doesn't mean anything to me.";
				link.l6.go = "Octavio_1_2";
			}
			if (pchar.lastname == "Cortez")
			{
				link.l7 = "My name is " + GetFullName(pchar)+" - I am a descendant of the famous conquistador discoverer, Hernan Cortez. And the name 'Lambrini' doesn't mean anything to me.";
				link.l7.go = "Octavio_1_2";
			}
			if (pchar.name == "Angelica" && pchar.lastname == "Teach")
			{
				link.l1 = "My name is " + GetFullName(pchar)+" - I am the daughter of a famous pirate, Blackbeard. And the name 'Lambrini' doesn't mean anything to me.";
				link.l1.go = "Octavio_1_2";
			}
			if (sti(pchar.reputation) > 80)
			{
				link.l8 = "My name is " + GetFullName(pchar)+". Everyone knows that I am a man of honor, and I can be trusted. And the name 'Lambrini' doesn't mean anything to me.";
				link.l8.go = "Octavio_1_2_DB";
			}
			if (sti(pchar.reputation) < 20)
			{
				link.l8 = "My name is " + GetFullName(pchar)+". And just the mention of my name makes everyone tremble and run in different directions. And the name 'Lambrini' doesn't mean anything to me.";
				link.l8.go = "Octavio_1_2_DB";
			}
			link.l9 = "I "+pchar.name+", captain and "+ GetSexPhrase("mercenary", "mercenary") +". I don't remember you.";
			link.l9.go = "Octavio_1_2_ostalnoe";
		break;

		case "Octavio_1_2":
			if (pchar.name == "Peter" && pchar.lastname == "Blood")
			{
				dialog.text = "So YOU're the doctor who saved the whole city from those Spaniards! Unbelievable! If you're really as good as they say you are, then we can have a conversation.";
			}
			if (pchar.name == "Whisper")
			{
				dialog.text = "So it was YOU who annoyed de Souza that the whole of Santiago was on its ears! Not bad! If you're really as good as they say you are, then we can have a chat.";
			}
			if (pchar.lastname == "Sharp")
			{
				dialog.text = ""+ GetSexPhrase("Son", "Daughter") +" of Nicholas Sharp? Not bad! I knew your father a long time ago, when the Lambrini had just settled on this island. Your father was a good man. If you're half as good as he is, we can have a conversation.";
			}
			if (pchar.name == "Charles" && pchar.lastname == "de Mor")
			{
				dialog.text = "Have you been to Tenochtitlan and defeated God himself? Unbelievable! If you're really as good as they say you are, then we can have a conversation.";
			}
			if (pchar.lastname == "Hauk")
			{
				dialog.text = "" + GetFullName(pchar)+"? Here in Trinidad? Anchor down my throat! If you are really as good as they say about you, then you can have a conversation.";
			}
			if (pchar.lastname == "Cortez")
			{
				dialog.text = "Native blood of Hernan Cortez? Not bad! Your ancestor was a great man, and if you're half as good as he is, we can have a conversation.";
			}
			if (pchar.name == "Angelica" && pchar.lastname == "Teach")
			{
				dialog.text = "Edward Teach's native blood? Not bad! Your father is a great man, and if you're half as good as he is, we can have a conversation.";
			}
			link.l1 = "What are you doing?";
			link.l1.go = "Octavio_1_3";
		break;

		case "Octavio_1_2_ostalnoe":
			dialog.text = "This is your problem, "+ GetSexPhrase("boy", "girl") +". The Lambrini family is well known in these islands. You'd better stay away from us.";
			link.l1 = "Okay, I'll come back later when I'm more "+ GetSexPhrase("known", "known") +". (Low or high reputation required)";
			link.l1.go = "exit";
		break;

		case "Octavio_1_2_DB":
			dialog.text = ""+GetFullName(pchar)+"? Yes, I've heard a lot about you. If you are really as good as they say about you, then you can have a conversation.";
			link.l1 = "What are you doing?";
			link.l1.go = "Octavio_1_3";
		break;

		case "Octavio_1_3":
			dialog.text = "My family and I are doing business all over the Caribbean archipelago. Our profits are great because we avoid paying onerous taxes on our shipments. Some people call us smugglers.";
			link.l1 = "You mentioned your family - who are they?";
			link.l1.go = "Octavio_1_4";
		break;

		case "Octavio_1_4":
			dialog.text = "Ah! Family is a very important issue for Lambrini. We came to the New World from Sicily forty years ago. Back then, my father was in charge of our actions here. After he died, I became the head of the family. Now I work with my sons, Fabio and Emilio, and my nephew, Cesario.";
			link.l1 = "I'm looking for a job. Do you have any suggestions?";
			link.l1.go = "Octavio_1_5";
		break;

		case "Octavio_1_5":
			dialog.text = "Yes. There is a problem that you can help us with.";
			link.l1 = "I'm listening.";
			link.l1.go = "Octavio_1_6";
		break;

		case "Octavio_1_6":
			dialog.text = "We are smugglers. And although most of the coast guard doesn't mind dealing with us, an honest man among them can cause a lot of trouble. Yes, it is quite possible to negotiate with most of them. But one is an exception. This guy, Arcadio de Galvez, owns a beautiful ship called the El Tiburon. And this bastard doesn't take bribes! So we can't do our business next to Maracaibo.";
			link.l1 = "And you want me to "+ GetSexPhrase("got rid of", "got rid of") +"from him?";
			link.l1.go = "Octavio_1_7";
			link.l2 = "I'm not interested in this, Octavio. If you're half as cool as you say you are, you can handle this guy on your own. Goodbye.";
			link.l2.go = "exit";
		break;

		case "Octavio_1_7":
				dialog.text = "It's not that important. Kill him, pin him to your bowsprit, feed the sharks, feed the British, or bribe him- it doesn't matter. But we can't ignore a piece as delicious as Maracaibo. Just deal with this guy somehow.";
			if (pchar.name == "Peter" && pchar.lastname == "Blood")
			{
				dialog.text = "It's not that important. Kill him, pin him to your bowsprit, feed the sharks, feed the British, or bribe him- it doesn't matter. But we can't ignore a piece as delicious as Maracaibo. Other smugglers avoid Maracaibo. They are afraid of the Spaniards-and with good reason. If you really beat the Spaniards in Barbados, then you'll get rid of this guy all the more easily.";
			}
			if (pchar.name == "Whisper")
			{
				dialog.text = "It's not that important. Kill him, pin him to your bowsprit, feed the sharks, feed the British, or bribe him- it doesn't matter. But we can't ignore a piece as delicious as Maracaibo. Other smugglers avoid Maracaibo. They are afraid of the Spaniards-and with good reason. If you really were able to annoy de Souza, then you'll get rid of this guy all the more easily.";
			}
			if (pchar.lastname == "Sharp")
			{
				dialog.text = "It's not that important. Kill him, pin him to your bowsprit, feed the sharks, feed the British, or bribe him- it doesn't matter. But we can't ignore a piece as delicious as Maracaibo. Other smugglers avoid Maracaibo. They are afraid of the Spaniards-and with good reason. But if you are half as "+ GetSexPhrase("cunning", "cunning") +" as your father was, you will cope with him.";
			}
			if (pchar.name == "Charles" && pchar.lastname == "de Mor")
			{
				dialog.text = "It's not that important. Kill him, pin him to your bowsprit, feed the sharks, feed the British, or bribe him- it doesn't matter. But we can't ignore a piece as delicious as Maracaibo. Other smugglers avoid Maracaibo. They are afraid of the Spaniards-and with good reason. If you really were able to defeat Kukulkan, then you can deal with this guy all the more easily.";
			}
			if (pchar.lastname == "Hauk")
			{
				dialog.text = "It's not that important. Kill him, pin him to your bowsprit, feed the sharks, feed the British, or bribe him- it doesn't matter. But we can't ignore a piece as delicious as Maracaibo. Other smugglers avoid Maracaibo. They are afraid of the Spaniards-and with good reason. If you really sank the Black Pearl, then you'll get rid of this guy all the more easily.";
			}
			if (pchar.lastname == "Cortez")
			{
				dialog.text = "It's not that important. Kill him, pin him to your bowsprit, feed him to the sharks, burn him at the stake, or bribe him- it doesn't matter. But we can't ignore a piece as delicious as Maracaibo. Other smugglers avoid Maracaibo. They are afraid of the Spaniards-and with good reason. You have the blood of a great conquistador in you, if you are at least half the same "+ GetSexPhrase("cunning", "cunning") +"like him, you can deal with this guy all the more easily.";
			}
			if (pchar.name == "Angelica" && pchar.lastname == "Teach")
			{
				dialog.text = "It's not that important. Kill him, pin him to your bowsprit, feed him to the sharks, burn him at the stake, or bribe him - it doesn't matter. But we can't ignore a piece as delicious as Maracaibo. Other smugglers avoid Maracaibo. They are afraid of the Spaniards-and with good reason. You have the blood of Edward Teach in you, if you are at least half the same "+ GetSexPhrase("cunning", "cunning") +"like him, you can deal with this guy all the more easily.";
			}
			if (sti(pchar.reputation) > 80 || sti(pchar.reputation) < 20)
			{
				dialog.text = "It's not that important. Kill him, pin him to your bowsprit, feed the sharks, feed the British, or bribe him- it doesn't matter. But we can't ignore a piece as delicious as Maracaibo. Other smugglers avoid Maracaibo. They are afraid of the Spaniards-and with good reason. If your name is really " + GetFullName(pchar)+", then you'll get rid of this guy all the more easily.";
			}
			link.l1 = "How much?";
			link.l1.go = "Octavio_1_8";
			link.l2 = "I'm not interested in this, Octavio. If you're half as cool as you say you are, you can handle this guy on your own. Goodbye.";
			link.l2.go = "exit";
		break;

		case "Octavio_1_8":
			dialog.text = "" + Plata1 + " gold. And know that no one bargains with Lambrini!";
			link.l1 = ""+ GetSexPhrase("I agree", "I agree") +".";
			link.l1.go = "Octavio_1_9";
			link.l2 = "I'm not interested in this, Octavio. If you're half as cool as you say you are, you can handle this guy on your own. Goodbye.";
			link.l2.go = "exit";
		break;

		case "Octavio_1_9":
			dialog.text = "Yo-ho, "+ GetSexPhrase("boy", "girl") +"! Few words, a lot of business. Now I will not give a centime for the life of this de Galvez. Go-and come back when you take care of him.";
			if (pchar.name == "Peter" && pchar.lastname == "Blood")
			{
				dialog.text = "Yo-ho, boy! You speak like a true doctor. Few words, a lot of business. Now I will not give a centime for the life of this de Galvez. Go-and come back when you take care of him.";
			}
			if (pchar.name == "Whisper")
			{
				dialog.text = "Yo-ho, the girl with purple hair! You sound like a true Whisperer. Few words, a lot of business. Now I will not give a centime for the life of this de Galvez. Go-and come back when you take care of him.";
			}
			if (pchar.lastname == "Sharp")
			{
				dialog.text = "Yo-ho, "+ GetSexPhrase("boy", "girl") +"! Yes, you remind me of your father, the true Sharp. Few words, a lot of business. Now I will not give a centime for the life of this de Galvez. Go-and come back when you take care of him.";
			}
			if (pchar.name == "Charles" && pchar.lastname == "de Mor")
			{
				dialog.text = "Yo-ho, "+ GetSexPhrase("boy", "girl") +"! You speak like a true nobleman. Few words, a lot of business. Now I will not give a centime for the life of this de Galvez. Go-and come back when you take care of him.";
			}
			if (pchar.lastname == "Hauk")
			{
				dialog.text = "Yo-ho, "+ GetSexPhrase("boy", "girl") +"! You sound like a true legendary Hawk. Few words, a lot of business. Now I will not give a centime for the life of this de Galvez. Go-and come back when you take care of him.";
			}
			if (pchar.lastname == "Cortez")
			{
				dialog.text = "Yo-ho, "+ GetSexPhrase("boy", "girl") +"! You sound like a true Hernan Cortez. Few words, a lot of business. Now I will not give a centime for the life of this de Galvez. Go-and come back when you take care of him.";
			}
			if (pchar.name == "Angelica" && pchar.lastname == "Teach")
			{
				dialog.text = "Yo-ho, girl! You sound like a true Blackbeard. Few words, a lot of business. Now I will not give a centime for the life of this de Galvez. Go-and come back when you take care of him.";
			}
			if (sti(pchar.reputation) > 80 || sti(pchar.reputation) < 20)
			{
				dialog.text = "Yo-ho, "+ GetSexPhrase("boy", "girl") +"! You speak like true " + GetFullName(pchar)+". Few words, a lot of business. Now I will not give a centime for the life of this de Galvez. Go-and come back when you take care of him.";
			}
			link.l1 = "See you later, Octavio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_1_10_EsheRaz";

			sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Anto2", "SpaOfficer2", "man", "man", Rank, SPAIN, -1, false));	//ВТОРОЙ
			sld.name = "Antonio";
			sld.lastname = "de Galvez";
			FantomMakeCoolFighter(sld, Rank, Sila, Sila, "blade30", "pistol2", DopHP);
			sld.SaveItemsForDead = true;
			sld.greeting = "GR_Spainguard";
			if (pchar.rank <= 9)
			{
				FantomMakeCoolSailor(sld, SHIP_NAVY, "El Tiburon", CANNON_TYPE_CULVERINE_LBS16, 100, 100, 100);
			}
			if (pchar.rank >= 10 && pchar.rank <= 14)
			{
				FantomMakeCoolSailor(sld, SHIP_POSTILLIONEN, "El Tiburon", CANNON_TYPE_CULVERINE_LBS16, 100, 100, 100);
			}
			if (pchar.rank >= 15 && pchar.rank <= 19)
			{
				FantomMakeCoolSailor(sld, SHIP_DEBRACKW, "El Tiburon", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
			}
			if (pchar.rank >= 20 && pchar.rank <= 25)
			{
				FantomMakeCoolSailor(sld, SHIP_CECILIA, "El Tiburon", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
			}
			if (pchar.rank >= 26 && pchar.rank <= 32)
			{
				FantomMakeCoolSailor(sld, SHIP_AGAMEMNON, "El Tiburon", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
			}
			if (pchar.rank >= 33)
			{
				FantomMakeCoolSailor(sld, SHIP_ZEVENPROVINCIEN, "El Tiburon", CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
			}
			sld.ship.Crew.Morale = Sila;								//Мораль
			ChangeCrewExp(sld, "Sailors", Sila);						//Матросы
			ChangeCrewExp(sld, "Cannoners", Sila);					//Канониры
			ChangeCrewExp(sld, "Soldiers", Sila);						//Солдаты
			sld.DontRansackCaptain = true; 							//Квестовые не сдаются
			sld.SinkTenPercent = false; 								//Уходит с повреждениями
			sld.SaveItemsForDead = true;							//Сохранить предметы после смерти
			sld.DontClearDead = true;								//не убирать труп через 200с
			sld.AnalizeShips = true;
			Group_FindOrCreateGroup("PDM_el_tib");					//Название группы
			Group_SetType("PDM_el_tib", "war");						//Тип поведения
			Group_AddCharacter("PDM_el_tib", "PDM_CL_Anto2");		//Добавить капитана

			Group_SetGroupCommander("PDM_el_tib", "PDM_CL_Anto2");
			Group_SetTaskAttack("PDM_el_tib", PLAYER_GROUP);
			Group_SetAddress("PDM_el_tib", "Maracaibo", "quest_ships", "reload_fort1");	//Установить местоположение
			Group_LockTask("PDM_el_tib");

//			PChar.quest.PDM_CL_Antonio_Ubit.win_condition.l1 = "NPC_Death";
//			PChar.quest.PDM_CL_Antonio_Ubit.win_condition.l1.character = "PDM_CL_Antonio";
//			PChar.quest.PDM_CL_Antonio_Ubit.win_condition = "PDM_CL_Antonio_Ubit";

			PChar.quest.PDM_CL_Antonio_Ubit2.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_CL_Antonio_Ubit2.win_condition.l1.character = "PDM_CL_Anto2";
			PChar.quest.PDM_CL_Antonio_Ubit2.win_condition = "PDM_CL_Antonio_Ubit";

			pchar.questTemp.PDM_CL_Ishem = "Ishem";

			SetQuestHeader("PDM_Clan_Lambrini");
			AddQuestRecord("PDM_Clan_Lambrini", "1");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("", "a"));
		break;

		case "Octavio_1_10_EsheRaz":
			dialog.text = "Well, "+ GetSexPhrase("boy", "girl") +" - did you kill that worm, de Galvez?";
			link.l1 = "I'll rip out his eyes, don't doubt it. But there's a time for everything.";
			link.l1.go = "Octavio_1_11_EsheRaz";
		break;

		case "Octavio_1_11_EsheRaz":
			dialog.text = "Then I'll give you time, "+ GetSexPhrase("boy", "girl") +", but remember - Lambrini are not very patient.";
			link.l1 = "Be sure - I won't keep you waiting long. Goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_1_10_EsheRaz";
		break;

		case "Antonio_1_1":
			dialog.text = "What did you want, "+ GetSexPhrase("senor", "senorita") +"?";
			link.l1 = "Your name is Arcadio de Galvez - and you are from the coast guard?";
			link.l1.go = "Antonio_1_2";
		break;

		case "Antonio_1_2":
			dialog.text = "Yes. And who are you?";
			link.l1 = "My name is " + GetFullName(pchar)+".";
			link.l1.go = "Antonio_1_3";
		break;

		case "Antonio_1_3":
			dialog.text = "Yes, yes, I've heard something about you... Why are you here?";
			link.l1 = "The Lambrini family sends greetings to you! (attack)";
			link.l1.go = "Antonio_Bitva";
			link.l2 = "Someone wants to kill you. (betray Lambrini)";
			link.l2.go = "Antonio_1_4";
			link.l3 = "I have to go.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Antonio_1_1";
		break;

		case "Antonio_Bitva":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("SPAIN_CITIZENS", LAI_GROUP_PLAYER, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Octavio_2_1":
			dialog.text = "Well, "+ GetSexPhrase("boy", "girl") +" - I hope you finished that worm, de Galvez?";
			link.l1 = "Yes. The poor bastard begged me for mercy, but his pleas were in vain.";
			link.l1.go = "Octavio_2_2";
		break;

		case "Octavio_2_2":
			dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway. Here are your " + Plata1 + ". And all my problems are over.";
			if (sti(pchar.reputation) > 80)
			{
				dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway-of course, because everyone talks about you as an honest person. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (sti(pchar.reputation) < 20)
			{
				dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway-of course, because everyone talks about you as a ruthless person. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.name == "Peter" && pchar.lastname == "Blood")
			{
				dialog.text = "Ha, boy! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway, of course, because you are the savior of Bridgetown from the Spaniards. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.name == "Whisper")
			{
				dialog.text = "Ha, girl! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway, of course, because you messed up de Souza himself. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.lastname == "Sharp")
			{
				dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway - of course, because you are "+ GetSexPhrase("son", "daughter") +" of Nicholas Sharp, the great pirate. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.name == "Charles" && pchar.lastname == "de Mor")
			{
				dialog.text = "Ha, boy! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway-of course, because you defeated Kukulkan himself. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.lastname == "Hauk")
			{
				dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway - of course, because you are the one who sank the Black Pearl. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.lastname == "Cortez")
			{
				dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway, of course, because you have the blood of Hernan Cortez, the great conquistador. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.name == "Angelica" && pchar.lastname == "Teach")
			{
				dialog.text = "Ha, girl! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway, of course, because you have the blood of Blackbeard, the great pirate. Here are your " + Plata1 + ". And all my problems are over.";
			}
			link.l1 = "Yes, now no one will stop you from trading in Maracaibo, Octavio. Goodbye.";
			link.l1.go = "exit";
			sld = CharacterFromID("PDM_Octavio_Lambrini");
			sld.lifeday = 0;
			AddMoneyToCharacter(pchar, sti(Plata1));
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, SPAIN, -6);
			AddCharacterExpToSkill(pchar, "Leadership", 130);
			AddCharacterExpToSkill(pchar, "FencingLight", 130);
			AddCharacterExpToSkill(pchar, "Fencing", 130);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 130);
			AddCharacterExpToSkill(pchar, "Pistol", 130);
			AddCharacterExpToSkill(pchar, "Fortune", 130);
			AddCharacterExpToSkill(pchar, "Sneak", 130);
			AddCharacterExpToSkill(pchar, "Sailing", 130);
			AddCharacterExpToSkill(pchar, "Accuracy", 130);
			AddCharacterExpToSkill(pchar, "Cannons", 130);
			AddCharacterExpToSkill(pchar, "Grappling", 130);
			AddCharacterExpToSkill(pchar, "Defence", 130);
			AddCharacterExpToSkill(pchar, "Repair", 130);
			NextDiag.TempNode = "Octavio_2_3_EsheRaz";
			CloseQuestHeader("PDM_Clan_Lambrini");
			pchar.questdata.ClanLambrini = 1;
		break;

		case "Octavio_2_3_EsheRaz":
			dialog.text = "A, "+pchar.name+"! I congratulate you on getting rid of this worm, de Galvez! I'm heading to Maracaibo soon to sign contracts with profitable clients.";
			link.l1 = "Good luck!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_2_3_EsheRaz";
		break;

		case "Antonio_1_4":
			dialog.text = "And what of it? If you wanted to surprise me, it didn't work out. Lambrini wants to kill me, but like the rest of the smugglers, they wouldn't mind.";
			link.l1 = "I came to you with an offer. What would you say if I provided to you an opportunity to catch or sink Lambrini's ship?";
			link.l1.go = "Antonio_1_6";
			link.l2 = "Well, then, goodbye.";
			link.l2.go = "exit";
		break;

		case "Antonio_1_6":
			dialog.text = "I would give my right hand for this. But this is not possible, alas. He has already bribed, it seems, every customs officer in the Caribbean. What can I do alone?";
			link.l1 = "Lambrini offered me to help him get rid of you. He is sure that he cannot cope with you alone...";
			link.l1.go = "Antonio_1_7";
		break;

		case "Antonio_1_7":
			dialog.text = "If you work for smugglers, then you and I have nothing to talk about, "+ GetSexPhrase("senor", "senorita") +"...";
			link.l1 = "Uh, wait - you didn't even listen to me. I can tell Lambrini that I drowned your ship. After that, sooner or later he will sail here, thinking that he is no longer in danger. And you can waylay him in the bay, or near it.";
			link.l1.go = "Antonio_1_8";
		break;

		case "Antonio_1_8":
			dialog.text = "Curious... This plan may work, "+ GetSexPhrase("senor", "senorita") +" "+pchar.name+". And if it works, I will ensure that the senor governor generously rewards you!";
			link.l1 = "And how much do you think a Lambrini head might be worth?";
			link.l1.go = "Antonio_1_9";
		break;

		case "Antonio_1_9":
			dialog.text = "I guess it's about " + Plata2 + ". Our income has dropped a lot lately because of the smugglers.";
			link.l1 = "I think that " + Plata2 + " is a sufficient fee. So I'll tell Octavio Lambrini that you're done... When he gets here, we'll grab him here. What could be simpler?";
			link.l1.go = "Antonio_1_10";
		break;

		case "Antonio_1_10":
			dialog.text = "As soon as you tell Lambrini I'm dead - come back to me immediately, I'll be waiting for you at the church from 9 am to 1 pm. We'll figure out what to do next.";
			link.l1 = "Take care of yourself, senor. Good luck!";
			link.l1.go = "Antonio_1_11";
			NextDiag.TempNode = "Antonio_1_12";
		break;

		case "Antonio_1_11":
			sld = CharacterFromID("PDM_Octavio_Lambrini");
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_3_1";
			DeleteAttribute(pchar, "questTemp.PDM_CL_Ishem");
			PChar.quest.PDM_CL_Antonio_Ubit.over = "yes";
			AddQuestRecord("PDM_Clan_Lambrini", "4");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("PDM_Clan_Lambrini", "sSex2", GetSexPhrase("xia", "as"));

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Antonio_1_12":
			dialog.text = "As soon as you inform Lambrini of my death - immediately return to me, I will wait for you at the church from 9 am to 2 pm. We'll figure out what to do next.";
			link.l1 = "Take care of yourself, senor. Good luck!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_1_12";
		break;

		case "Octavio_3_1":
			dialog.text = "Well, "+ GetSexPhrase("boy", "girl") +" - I hope you killed that worm, de Galvez?";
			link.l1 = "Yes. The poor bastard begged me for mercy, but his pleas were in vain.";
			link.l1.go = "Octavio_3_2";
		break;

		case "Octavio_3_2":
			dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway. Here are your " + Plata1 + ". And all my problems are over.";
			if (sti(pchar.reputation) > 80)
			{
				dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway-of course, because everyone talks about you as an honest person. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (sti(pchar.reputation) < 20)
			{
				dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway-of course, because everyone talks about you as a ruthless person. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.name == "Peter" && pchar.lastname == "Blood")
			{
				dialog.text = "Ha, boy! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway, of course, because you are the savior of Bridgetown from the Spaniards. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.name == "Whisper")
			{
				dialog.text = "Ha, girl! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway, of course, because you messed up de Souza himself. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.lastname == "Sharp")
			{
				dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway - of course, because you are "+ GetSexPhrase("son", "daughter") +" of Nicholas Sharp, the great pirate. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.name == "Charles" && pchar.lastname == "de Mor")
			{
				dialog.text = "Ha, boy! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway-of course, because you defeated Kukulkan himself. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.lastname == "Hauk")
			{
				dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway - of course, because you are the one who sank the Black Pearl. Here are your " + Plata1 + ". And all my problems are over.";
			}
			if (pchar.lastname == "Cortez")
			{
				dialog.text = "Ha, "+ GetSexPhrase("boy", "girl") +"! You should have brought his head as proof. That would be a nice souvenir. But I believe you anyway, of course, because you have the blood of Hernan Cortez, the great conquistador. Here are your " + Plata1 + ". And all my problems are over.";
			}
			link.l1 = "Yes, now no one will stop you from trading in Maracaibo, Octavio. Goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_3_3_EsheRaz";
			sld = CharacterFromID("PDM_Octavio_Lambrini");
			sld.lifeday = 0;
			AddMoneyToCharacter(pchar, sti(Plata1));
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, SPAIN, 6);
			AddCharacterExpToSkill(pchar, "Sneak", 160);
			AddCharacterExpToSkill(pchar, "Sailing", 100);

			PChar.quest.PDM_CL_Ubrat_Lodku.win_condition.l1 = "ExitFromLocation";
			PChar.quest.PDM_CL_Ubrat_Lodku.win_condition.l1.location = PChar.location;
			PChar.quest.PDM_CL_Ubrat_Lodku.function = "PDM_CL_Ubrat_Lodku";
			AddQuestRecord("PDM_Clan_Lambrini", "5");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("", "a"));
		break;

		case "Octavio_3_3_EsheRaz":
			dialog.text = "A, "+pchar.name+"! I congratulate you on getting rid of this worm, de Galvez! I'm heading to Maracaibo soon to sign contracts with profitable clients.";
			link.l1 = "Good luck!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_3_3_EsheRaz";
		break;

		case "Antonio_2_1":
			dialog.text = ""+TimeGreeting()+", "+ GetSexPhrase("senor", "senorita") +" "+pchar.name+". How did it go?";
			link.l1 = "Octavio Lambrini believed in your death, most likely he is already on his way here to Maracaibo.";
			link.l1.go = "Antonio_2_2";
		break;

		case "Antonio_2_2":
			dialog.text = "Excellent. Smugglers like to hang out at the tavern, you need to go in there and see if he showed up there.";
			link.l1 = "Okay, I'll look for him at the tavern.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_2_3_EsheRaz";

			PChar.quest.PDM_CL_PVT.win_condition.l1 = "location";		//Вход в локацию
			PChar.quest.PDM_CL_PVT.win_condition.l1.location = "Maracaibo_tavern";
			PChar.quest.PDM_CL_PVT.win_condition = "PDM_CL_PVT";

			sld = GetCharacter(NPC_GenerateCharacter("PDM_Octavio_Lambrini", "barmen_3", "man", "man", 10, PIRATE, -1, false));
			sld.name	= "Octavio";
			sld.lastname	= "Lambrini";
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_4_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			FreeSitLocator("Maracaibo_tavern", "sit_base2");  // очистим стул
			FreeSitLocator("Maracaibo_tavern", "sit_front2");  // очистим стул
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_front2");

			pchar.LambriniPGG = SelectRandomPGG("woman", "YokoDias");

			if (pchar.LambriniPGG == "")
			{
				pchar.LambriniPGG = "PDM_CL_Pokupatel";
				if(pchar.name == "Victoria")
				{
					sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Pokupatel", "PGG_Cirilla_7", "woman", "YokoDias", 10, PIRATE, -1, false));
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Pokupatel", "PGG_Victori_8", "woman", "YokoDias", 10, PIRATE, -1, false));
				}
				sld.name	= "Marilisa";
				sld.lastname	= "Rinn";
			}
			else sld = CharacterFromID(pchar.LambriniPGG);

			sld.PGGAi.DontUpdate = true;
			sld.PGGAi.Task.SetSail = true;
			DeleteAttribute(sld, "PGG_warrior");
			DeleteAttribute(sld, "PGG_trader");

			SaveOldDialog(sld);
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_1_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_base2");

			AddQuestRecord("PDM_Clan_Lambrini", "6");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("", "a"));
		break;

		case "Antonio_2_3_EsheRaz":
			dialog.text = "Well, "+ GetSexPhrase("senor", "senorita") +", did you see Lambrini at the tavern?";
			link.l1 = "Not yet, I was just going there.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_2_3_EsheRaz";
		break;

		case "Pokupatel_1_1":
			dialog.text = "What do you want? Can't you see I'm busy?";
			link.l1 = "I'm sorry, I didn't mean to you're in the way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pokupatel_1_1";
		break;

		case "Octavio_4_1":
			dialog.text = "(we are eavesdropping on Octavio, he is currently conducting a dialogue with his prospective client)...Why then?";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_1";

			sld = CharacterFromID(pchar.LambriniPGG);
			if (sld.location == "None") FreeSitLocator("Maracaibo_tavern", "sit_base2");  // очистим стул
			DoQuestCheckDelay("PDM_CL_PVT", 0.0);
		break;

		case "Pokupatel_2_1":
			sld = characterFromID(pchar.LambriniPGG);
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_2";
			DialogExit();
			DoQuestFunctionDelay("PDM_CL_Pokupatel_Speech", 0);
		break;

		case "Pokupatel_2_2":
			dialog.text = "I want to sell something that no trader on this island will buy. There is a dream goods in my hold! Sandal mountains, just think, ah.";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_3";
		break;

		case "Pokupatel_2_3":
			sld = characterFromID("PDM_Octavio_Lambrini");
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_4";
			DialogExit();
			DoQuestFunctionDelay("PDM_CL_Octavio_Speech", 0);
		break;

		case "Pokupatel_2_4":
			npchar.lifeday = 0;
			dialog.text = "I know you can be dealt with. We will be waiting for you at a place called Guajira Bay.";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_5";
		break;

		case "Pokupatel_2_5":
			sld = characterFromID(pchar.LambriniPGG);
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_6";
			DialogExit();
			DoQuestFunctionDelay("PDM_CL_Pokupatel_Speech", 0);
		break;

		case "Pokupatel_2_6":
			dialog.text = "I will definitely come, baby.";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_7";
		break;

		case "Pokupatel_2_7":
			sld = characterFromID("PDM_Octavio_Lambrini");
			LAi_CharacterDisableDialog(sld);
			sld = characterFromID(pchar.LambriniPGG);

			LAi_CharacterDisableDialog(sld);
			DoQuestFunctionDelay("PDM_CL_Pokupatel_Uhodit", 1.5);
			sld = CharacterFromID("PDM_CL_Antonio3");
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_5_1";
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddQuestRecord("PDM_Clan_Lambrini", "7");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("", "a"));
		break;


		case "Antonio_5_1":
			dialog.text = ""+ GetSexPhrase("Senor", "Senorita") +" "+pchar.name+", you are back. Have you seen anything interesting?";
			link.l1 = "Yes, Lambrini is already in the city and feels very comfortable. I managed  overhear his conversation with captain, who is going to sell an illegal and expensive goods - sandal. Maybe we should go to the tavern and grab Lambrini, the warm one?";
			link.l1.go = "Antonio_5_2";
		break;

		case "Antonio_5_2":
			dialog.text = "No! We'll let him make the deal. They will all gather in the bay, along with the valuable goods, thinking that they are not in danger. That's when we show up and arrest everyone. Have you been able to find out where they are going to do their dark deeds?";
			link.l1 = "Lambrini was talking about Guajira Bay.";
			link.l1.go = "Antonio_5_3";
			Pchar.GenQuest.Hunter2Pause = true;
		break;

		case "Antonio_5_3":
			dialog.text = "Great! We'll round up the jungle side and catch them off guard.";
			link.l1 = "On your way!";
			link.l1.go = "Antonio_J_1";
		break;

		case "Antonio_J_1":
			DialogExit();

			LocatorReloadEnterDisable("Shore37", "reload1_back", true);
			LocatorReloadEnterDisable("Shore37", "boat", true);

			sld = CharacterFromID("PDM_CL_Antonio3");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore37", "officers", "reload1_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			for (i=1; i<=2; i++)	//испанцы
			{
				sTemp = "sold_spa_"+(rand(7)+1);
				sld = GetCharacter(NPC_GenerateCharacter("SraDruzya_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, Rank, 30, 30, "blade10", "", 20);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "Shore37", "reload",  "reload1_back");
			}

			for (i=3; i<=6; i++)	//пираты м контрабандисты 1
			{
				sTemp = "pirate_"+(rand(24)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_PirVrag_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, Rank, 30, 30, "blade10", "", 20);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
				ChangeCharacterAddressGroup(sld, "Shore37", "goto",  "goto5");
			}

			for (i=7; i<=10; i++)	//пираты м контрабандисты 2
			{
				sTemp = "pirate_"+(rand(24)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_PirVrag_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, Rank, 30, 30, "blade10", "", 20);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
				ChangeCharacterAddressGroup(sld, "Shore37", "goto",  "goto6");
			}

			for (i=11; i<=14; i++)	//пираты м контрабандисты 3
			{
				sTemp = "pirate_"+(rand(24)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_PirVrag_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, Rank, 30, 30, "blade10", "", 20);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
				ChangeCharacterAddressGroup(sld, "Shore37", "reload",  "sea");
			}

			DoQuestReloadToLocation("Shore37", "goto", "goto1", "PDM_CL_Na_Plyaj");
			AddGeometryToLocation("Shore37", "smg");
			pchar.location.from_sea = "Shore37";

			sld = GetCharacter(NPC_GenerateCharacter("PDM_Octavio_Lambrini", "barmen_3", "man", "man", 10, PIRATE, -1, false));
			LAi_SetActorType(sld);
			sld.name	= "Octavio";
			sld.lastname	= "Lambrini";
			FantomMakeCoolFighter(sld, Rank, 80, 80, "blade33", "pistol2", 250);
			LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
			ChangeCharacterAddressGroup(sld, "Shore37", "goto", "goto7");

			sld = CharacterFromID(pchar.LambriniPGG);
			LAi_SetActorType(sld);

			sld.LambiniAsoleda = GetGeneratedItem("blade38");
			GiveItem2Character(sld, sld.LambiniAsoleda);
			EquipCharacterByItem(sld, sld.LambiniAsoleda);

			GiveItem2Character(sld, "pistol1");
			EquipCharacterByItem(sld, "pistol1");

			sld.BackupHP = LAi_GetCharacterMaxHP(sld);
			LAi_SetHP(sld, sti(sld.BackupHP) + 1000, sti(sld.BackupHP) + 1000);
			//LAi_SetHP(sld, 100, 100);
			SetCharacterPerk(sld, "Sliding");
			sld.perks.list.AgileMan = "1";
			ApplayNewSkill(sld, "AgileMan", 0);

			sld.SPECIAL.Agility = 10;
			sld.SPECIAL.Intellect = 10;
			sld.SPECIAL.Endurance = 10;
			sld.SPECIAL.Luck = 10;

			//FantomMakeCoolFighter(sld, Rank, 90, 90, "blade38", "pistol4", 500);

			LAi_SetCheckMinHP(sld, 1, true, "LambriniPGG_CheckHP");
			/*
			AddMoneyToCharacter(sld, 100000);
			AddItems(sld, "jewelry1", rand(20)+20);
			AddItems(sld, "jewelry2", rand(20)+20);
			AddItems(sld, "jewelry3", rand(20)+20);
			AddItems(sld, "jewelry4", rand(20)+20);
			AddItems(sld, "jewelry5", rand(20)+20);
			AddItems(sld, "suit_3", 1);
			AddItems(sld, "indian5", 1);
			sld.SaveItemsForDead = true;*/
			LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
			ChangeCharacterAddressGroup(sld, "Shore37", "goto", "goto7");
		break;

		case "Antonio_6_1":
			dialog.text = "We're here. And there are our labrinians... I can't believe we're going to put an end to this soon. Lead the squad, we're behind you.";
			link.l1 = "Go ahead!";
			link.l1.go = "Antonio_6_2";
		break;

		case "Antonio_6_2":
			DialogExit();

			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "enc01", "enc01_03", "PDM_CL_Na_Plyaj_2", -1);
		break;

		case "Pokupatel_6_1":
			dialog.text = "What are you doing here?";
			link.l1 = "Something illegal seems to be going on here.";
			link.l1.go = "Pokupatel_6_2";
		break;

		case "Pokupatel_6_2":
			dialog.text = "No, no, "+ GetSexPhrase("senor", "senorita") +". My friends and I are just relaxing by the sea.";
			link.l1 = "What are you telling me! I'm not blind! Follow us - you are arrested and the goods are confiscated!";
			link.l1.go = "Pokupatel_6_3";
		break;

		case "Pokupatel_6_3":
			dialog.text = "I'll gut you!";
			link.l1 = "First, I will release my inner beast!";
			link.l1.go = "Pokupatel_6_4";
		break;

		case "Pokupatel_6_4":
			DialogExit();

			AddDialogExitQuest("MainHeroFightModeOn");

			for (i=3; i<=14; i++)	//пираты м контрабандисты
			{
				sld = CharacterFromID("PDM_CL_PirVrag_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
			}
			for (i=19; i<=27; i++)	//испанцы 1
			{
				sTemp = "sold_spa_"+(rand(7)+1);
				sld = GetCharacter(NPC_GenerateCharacter("SraDruzya_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, Rank, 28, 28, "blade10", "", 16);
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "Shore37", "goto", "goto4");
				sld.lifeday = 0;
			}
			for (i=1; i<=2; i++)	//испанцы 2
			{
				sld = CharacterFromID("SraDruzya_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				sld.lifeday = 0;
			}

			sld = CharacterFromID("PDM_Octavio_Lambrini");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");

			sld = CharacterFromID(pchar.LambriniPGG)
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");

			sld = CharacterFromID("PDM_CL_Antonio3");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			LAi_group_SetRelation("PDM_CL_PirVrag_Status", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("PDM_CL_PirVrag_Status", LAI_GROUP_PLAYER, false);
			//LAi_group_SetCheck("PDM_CL_PirVrag_Status", "PDM_CL_Finish");
		break;

		case "Antonio_8_1":
			string OctavioDead = "";
			if(LAi_IsDead(CharacterFromID("PDM_Octavio_Lambrini")))	OctavioDead = "";

			dialog.text = "I can't believe we did it! You can go back to the city, and my people will sort out this mess. " + OctavioDead;

			OctavioDead = "Octavio Lambrini is dead, ";
			if(!LAi_IsDead(CharacterFromID("PDM_Octavio_Lambrini")))	OctavioDead = "Octavio Lambrini has been arrested, ";
			link.l1 = OctavioDead + "what about the reward?";
			link.l1.go = "Antonio_8_2";
		break;

		case "Antonio_8_2":
			pchar.LambriniPGGPlata = Plata2/2;
			string addPlata = "";
			if(!LAi_IsDead(CharacterFromID("PDM_Octavio_Lambrini")))
			{
				pchar.LambriniPGGPlata = Plata2;
				AddMoneyToCharacter(pchar, sti(Plata2*2));
				addPlata = "But since we managed to catch the bastard alive, I'll double your fee out of my own pocket! As a result, " + Plata3 + " gold. Who knows, maybe after a couple of weeks in prison, Octavio will tell us how to catch the rest of his criminal family. "
			}
			else	AddMoneyToCharacter(pchar, sti(Plata2));
			dialog.text = "Yes, of course, the governor has allocated you " + Plata2 + " gold. "+addPlata+"I am giving this money to you personally. Goodbye!";
			link.l1 = "Thank you, Antonio. Good luck to you!";
			link.l1.go = "LambriniPGG_1_5";

			LocatorReloadEnterDisable("Shore37", "reload1_back", false);
			LocatorReloadEnterDisable("Shore37", "boat", false);
			ChangeCharacterNationReputation(pchar, SPAIN, 8);
			ChangeCharacterReputation(pchar, 5);
		break;

		case "LambriniPGG_1_1":
			dialog.text = RandSwear()+"A load of sandal is not worth our lives. We surrender!";
			link.l1 = "In that case, you must surrender your sword, Captain.";
			link.l1.go = "LambriniPGG_1_2";

			for (i=3; i<=14; i++)	//пираты м контрабандисты прячут оружие, испанцы - нет
			{
				sld = CharacterFromID("PDM_CL_PirVrag_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			sld = characterFromID("PDM_Octavio_Lambrini");
			LAi_SetStayTypeNoGroup(sld);
		break;

		case "LambriniPGG_1_2":
			for (i=3; i<=14; i++)	//пираты м контрабандисты
			{
				sld = CharacterFromID("PDM_CL_PirVrag_"+i);
				LAi_SetActorTypeNoGroup(sld);
			}
			sld = characterFromID("PDM_Octavio_Lambrini");
			LAi_SetActorTypeNoGroup(sld);
			sld.LifeDay = 0;
			dialog.text = RandSwear()+"You can't imagine how expensive it cost me!";
			link.l1 = "I won't repeat it twice. ";
			link.l1.go = "LambriniPGG_1_3";
		break;

		case "LambriniPGG_1_3":
			TakeItemFromCharacter(npchar, npchar.LambiniAsoleda);
			GiveItem2Character(pchar, npchar.LambiniAsoleda);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			Log_Info("You got Asoleda!");
			PlaySound("interface\important_item.wav");

			dialog.text = RandSwear()+"(gives Asoled) Here, choke on it!";
			link.l1 = "What's next, Antonio?";
			link.l1.go = "LambriniPGG_1_4";

			PChar.quest.LambriniPGG_RemoveFromShore.win_condition.l1 = "ExitFromLocation";
			PChar.quest.LambriniPGG_RemoveFromShore.win_condition.l1.location = PChar.location;
			PChar.quest.LambriniPGG_RemoveFromShore.function = "LambriniPGG_RemoveFromShore";
		break;

		case "LambriniPGG_1_4":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Antonio4", "SpaOfficer2", "man", "man", Rank, SPAIN, 0, false));
			sld.name = "Antonio";
			sld.lastname = "de Galvez";
			sld.greeting = "GR_Spainguard";
			string sBlade = GetGeneratedItem("blade40");
			GiveItem2Character(sld, sBlade);
			EquipCharacterbyItem(sld, sBlade);
			ChangeCharacterAddressGroup(sld, "Shore37", "goto", "goto7");
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			//sld = CharacterFromID("PDM_CL_Antonio3");
			sld.dialog.currentnode   = "Antonio_8_1";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "LambriniPGG_1_5":
			DialogExit();
			sld = CharacterFromID(pchar.LambriniPGG);
			sld.dialog.currentnode   = "LambriniPGG_1_6";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "LambriniPGG_1_6":
			dialog.text = "This is your showdown with Octavio, and I had nothing to do with it. Let me go! Maybe the name " + GetFullName(npchar)+ " will tell you something? I am a well-known person in these waters! It's better not to cross my path.";
			link.l1 = "";
			link.l1.go = "LambriniPGG_1_7";
		break;

		case "LambriniPGG_1_7":
			DialogExit();
			sld = CharacterFromID("PDM_CL_Antonio4");
			sld.dialog.currentnode   = "LambriniPGG_1_8";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "LambriniPGG_1_8":
			dialog.text = "You've been doing business with a criminal, which means you're with him for the same thing! We will take you to the prison under Fort Maracaibo, and then the court will decide your fate.";
			link.l1 = "";
			link.l1.go = "LambriniPGG_1_9";
		break;

		case "LambriniPGG_1_9":
			LAi_SetActorTypeNoGroup(npchar);
			DialogExit();
			sld = CharacterFromID(pchar.LambriniPGG);
			sld.dialog.currentnode   = "LambriniPGG_1_10";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "LambriniPGG_1_10":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_SetHP(npchar, sti(npchar.BackupHP) + 100, sti(npchar.BackupHP) + 100);
			dialog.text = "(he whispers to you) Antonio is too decent, for him the law is above all, it is unlikely that he can be persuaded, but what about you? I can see that you are "+ GetSexPhrase("not one of those right boys", "a 'bad' girl") +". Help me out of this mess, and I'll reward you. In addition to the sword, you will take all my treasure!";
			link.l1 = "I'm not interested in this. Criminals belong behind bars.";
			link.l1.go = "LambriniPGG_1_11";
			link.l2 = "Treasure, you say... I'll figure something out.";
			link.l2.go = "LambriniPGG_1_12";
		break;

		case "LambriniPGG_1_11":
			dialog.text = RandSwear()+RandSwear()+RandSwear()+RandSwear()+RandSwear()+"Damn you! Well, never mind, I'll get out and take revenge on all of you!";
			link.l1 = "Well, well.";
			link.l1.go = "exit";
			AddQuestRecord("PDM_Clan_Lambrini", "9");
			CloseQuestHeader("PDM_Clan_Lambrini");
			pchar.questdata.ClanLambrini = 1;
			AddQuestUserData("PDM_Clan_Lambrini", "sName", GetFullName(npchar));
			PGG_ChangeRelation2MainCharacter(CharacterFromID(pchar.LambriniPGG), -200); //сильно обиделась
			SetTimerCondition("LambriniPGG_Freedom", 0, 0, 30, false); //Посидит месяц в тюрьме без кача и потом выйдет
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fencing", 200);
			AddCharacterExpToSkill(pchar, "Pistol", 200);
		break;

		case "LambriniPGG_1_12":	//Запустить таймер в 10 дней на возврат диалога коменданту потом то же, что и в комменте выше	
			dialog.text = "You won't regret it! Just please hurry up, I don't want to go to the gallows!";
			link.l1 = "Okay.";
			link.l1.go = "LambriniPGG_1_13";
			AddQuestRecord("PDM_Clan_Lambrini", "8");
			AddQuestUserData("PDM_Clan_Lambrini", "sName", GetFullName(npchar));
		break;

		case "LambriniPGG_1_13":
			DialogExit();
			SetTimerCondition("LambriniPGG_Late", 0, 0, 3, false);//Три дня чтобы прийти в тюрьму
			pchar.LambriniPGGInPrison = true;
			//sld = CharacterFromID("MaracaiboJailOff");
			//SaveOldDialog(sld);
			//sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			//sld.dialog.currentnode   = "LambriniPGG_1_14";
		break;

		case "LambriniPGG_1_14"://Запустить таймер в 10 дней на возврат диалога коменданту потом то же, что и в комменте выше
			dialog.text = "You won't regret it! Just please hurry up, I don't want to go to the gallows!";
			link.l1 = "Okay.";
			link.l1.go = "exit";
			DialogExit();
			//RestoreOldDialog(npchar);
		break;

		case "LambriniPGG_2_1":
			LocatorReloadEnterDisable(pchar.location.from_sea, "reload1_back", true);
			LocatorReloadEnterDisable("Maracaibo_exittown", "reload1_back", true);
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			dialog.text = GetSexPhrase("My savior!", "My savior!")+" Unless, of course, you're the one who dropped me off here.";
			link.l1 = "Since this is my handiwork, I need to get out. So what about the treasure?";
			link.l1.go = "LambriniPGG_2_2";
		break;

		case "LambriniPGG_2_2":
			dialog.text = "My trunk should still be here in Maracaibo. Get a room at the tavern.";
			link.l1 = "To the tavern, so to the tavern.";
			link.l1.go = "exit";

			PChar.quest.LambriniPGG_Tavern.win_condition.l1 = "location";
			PChar.quest.LambriniPGG_Tavern.win_condition.l1.location = "Maracaibo_tavern_upstairs";
			PChar.quest.LambriniPGG_Tavern.function = "LambriniPGG_Tavern";
		break;

		case "LambriniPGG_2_3":
			chrDisableReloadToLocation = true;
			dialog.text = "And here is the chest. We were lucky that the soldiers didn't have time to find him.";
			link.l1 = "Okay, open it. Let's see what's in there.";
			link.l1.go = "LambriniPGG_2_4";
		break;
		case "LambriniPGG_2_4":
			GiveItem2Character(pchar, "Chest_quest");
			Log_Info("You got a strange chest");
			PlaySound("interface\important_item.wav");
			dialog.text = "There is a problem with this. I don't have a key.";
			link.l1 = "So why do I need a locked chest?";
			link.l1.go = "LambriniPGG_2_5";
		break;
		case "LambriniPGG_2_5":
			TakeNItems(PChar, "Lockpick", 3);
			Log_Info("You got the lockpicks");
			PlaySound("interface\important_item.wav");
			dialog.text = "You can unlock it with lockpicks. Here, look. I bought them from Octavio Lambrini, but I never had time to use them.";
			link.l1 = "Okay, give them here, I'll figure it out already.";
			link.l1.go = "LambriniPGG_2_6";
		break;
		case "LambriniPGG_2_6":
			dialog.text = "Well, I think we both fulfilled our part of the agreement...";
			link.l1 = "So be it, you can go.";
			link.l1.go = "LambriniPGG_2_7";
			link.l2 = "Since we are in the bedroom, and there is such a soft bed here... Shall we test its strength?";
			link.l2.go = "LambriniPGG_2_8";
		break;
		case "LambriniPGG_2_7":
			PGG_ChangeRelation2MainCharacter(CharacterFromID(pchar.LambriniPGG), 30);
			chrDisableReloadToLocation = false;
			dialog.text = "Well, I have to go. Now we need to get our ship back somehow, maybe we'll see you again. Good luck to you.";
			link.l1 = "And to you.";
			link.l1.go = "LambriniPGG_2_10";

			string finalWords = ".";
			if (CheckAttribute(npchar, "bonusEnergy"))	finalWords = "And you have a lot of nerve! I agree.";

			AddQuestRecord("PDM_Clan_Lambrini", "11");
			CloseQuestHeader("PDM_Clan_Lambrini");
			pchar.questdata.ClanLambrini = 1;
			AddQuestUserData("PDM_Clan_Lambrini", "sName", GetFullName(npchar));
			AddQuestUserData("PDM_Clan_Lambrini", "sContinue", finalWords);

			DeleteAttribute(pchar, "LambriniPGGInPrison");
			SetTimerCondition("LambriniPGG_Freedom", 0, 0, 7, false);//Через неделю вернётся в строй
			//DeleteAttribute(npchar, "PGGAi.DontUpdate");
			//DeleteAttribute(npchar, "PGGAi.Task.SetSail");
			//DeleteAttribute(pchar, "LambriniPGG");

			LocatorReloadEnterDisable(pchar.location.from_sea, "reload1_back", false);
			LocatorReloadEnterDisable("Maracaibo_exittown", "reload1_back", false);
		break;
		case "LambriniPGG_2_8":
			dialog.text = "You have a lot of nerve! I agree.";
			link.l1 = "";
			link.l1.go = "LambriniPGG_2_9";
		break;
		case "LambriniPGG_2_9":
			PGG_ChangeRelation2MainCharacter(CharacterFromID(pchar.LambriniPGG), 200);
			pchar.GenQuest.BrothelCount = 0;
            AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddCharacterExpToSkill(npchar, "Leadership", 100);
            AddCharacterExpToSkill(pchar, "Fencing", 100);// утрахала
            AddCharacterExpToSkill(npchar, "Fencing", 100);
            AddCharacterExpToSkill(pchar, "Pistol", 100);
            AddCharacterExpToSkill(npchar, "Pistol", 100);
            AddCharacterHealth(pchar, 10);
            AddCharacterHealth(npchar, 10);
   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "LambriniPGG_2_7";
			DialogExit();
		break;

		case "LambriniPGG_2_10":
			RestoreOldDialog(npchar);
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
		break;
	}
}
