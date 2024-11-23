
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);						// 						АВТОРЫ И БЛАГОДАРНОСТИ
	makearef(Link, Dialog.Links);						// Оригинальная идея квеста				    			 - Акелла
	makearef(NextDiag, NPChar.Dialog);					// Написанный с нуля код и переосмысление квеста 	 	 - Sinistra
														// Новая модель и текстура для "Witches" 				 - Domovoy
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First_time":
			dialog.text = "Greetings, "+ GetSexPhrase("sir", "lady")+". My name is Bartholomew Ulster. By the way, have you seen Maria Carle, the girl from the tavern? She's disappeared somewhere...";
			link.l1 = "No, I do not know who she is, much less where she is. But you have an English accent-tell me, how did you get here?";
			link.l1.go = "Bartolom";
			link.l2 = "I don't know. Maybe you should look in the tavern - it would be logical.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First_time";
			PlayVoice("Kopcapkz\Voices\Queste_videli_Mariu.wav");
			UnmarkCharacter(npchar);
		break;

		case "Bartolom":
			dialog.text = "I'm sorry, but I can't talk to you right now. I need to find Maria!";
			link.l1 = "In that case, see you later.";
			link.l1.go = "PoraVTavernu";
		break;

		case "PoraVTavernu":
			SetQuestHeader("PDM_Ohota_na_vedmu");
			AddQuestRecord("PDM_Ohota_na_vedmu", "1");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "a"));

			sld = CharacterFromID("PDM_Isp_sekr_guber");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back", "PDM_ONV_BARTO_Ischezni", -1);

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Carla", "Witch", "woman", "woman", 10, SPAIN, -1, false));
			LAi_SetImmortal(sld, true);
			sld.name = "Maria";
			sld.lastname = "Carle";
			sld.city = "Beliz";
			ChangeCharacterAddressGroup(sld, "Beliz_tavern", "waitress", "stay2");
			LAi_SetWaitressType(sld);
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "First_Carla_1";
			
			sld = CharacterFromID("Beliz_waitress");
			sld.model	= "girl_6";			

			DialogExit();
		break;

		case "First_Carla_1":
			dialog.text = "What are you looking for here, "+ GetSexPhrase("handsome", "beauty")+"? Pleasure, I suppose? My name is Maria Carle, or Merry Maria, as most men in this city call me. And what is your name, "+ GetSexPhrase("senor", "senorita")+"?";
			link.l1 = "You can call me "+pchar.name+", dear. But I suppose there's another man in town who's looking for pleasure. I saw him in the square - he looks like he can't wait to meet you.";
			link.l1.go = "First_Carla_2";
			PlayVoice("Kopcapkz\Voices\PDM\Spain\Catalina.wav");
		break;

		case "First_Carla_2":
			dialog.text = "What? Bartholomew? But I thought he was... Oh, it doesn't matter... You know what, "+ GetSexPhrase("handsome", "beauty")+" - I just remembered that I'm a little busy today. But we'll do whatever we want to do another time-when I'm more at ease. You have very nice legs, by the way.";
			link.l1 = "E... Thank you. I'll probably check in on you later.";
			link.l1.go = "First_Carla_Uhodit";
		break;

		case "First_Carla_Uhodit":
			AddQuestRecord("PDM_Ohota_na_vedmu", "2");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "a"));

			//bDisableFastReload = true;
			LocatorReloadEnterDisable("Beliz_town", "reload3_back", true);
			LocatorReloadEnterDisable("Beliz_town", "reloadR1", true);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload1", true);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload2", true);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload3", true);
			LocatorReloadEnterDisable("Beliz_townhall", "reload2", true);
			LocatorReloadEnterDisable("Beliz_townhall", "reload1_back", true);

			sld = CharacterFromID("PDM_ONV_Carla");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorRunToLocator(sld, "reload", "reload1_back", "PDM_ONV_Clara_Ischezni", -1);

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Sin", "SpaOfficer1", "man", "man", 100, SPAIN, -1, false));
			sld.name = "Sinistra";
			sld.lastname = "";
			sld.greeting = "GR_Spainguard";
			sld.city = "Beliz";
			FantomMakeCoolFighter(sld, 100, 100, 100, "blade27", "pistol6", 0);
			LAi_SetHP(sld, 1.0, 1.0);
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, "Beliz_town", "reload", "reload3_back");
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "OfficerGuard";
			
			PChar.quest.PDM_ONV_Vkomnate.win_condition.l1 = "location";
			PChar.quest.PDM_ONV_Vkomnate.win_condition.l1.location = "Beliz_TownhallRoom";
			PChar.quest.PDM_ONV_Vkomnate.win_condition = "PDM_ONV_Vkomnate";

			PChar.quest.PDM_ONV_Vzaimno.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_ONV_Vzaimno.win_condition.l1.character = "PDM_ONV_Sin";
			PChar.quest.PDM_ONV_Vzaimno.win_condition = "PDM_ONV_Vzaimno";

			DialogExit();
		break;

		case "OfficerGuard":
			dialog.text = "Sorry, "+ GetSexPhrase("senor", "senorita")+", but I'm not supposed to let anyone in.";
			link.l1 = "Whatever you say, officer. Goodbye!";
			link.l1.go = "OfficerGuard_Cod";
			NextDiag.TempNode = "OfficerGuard_Again";
		break;

		case "OfficerGuard_Cod":
			AddQuestRecord("PDM_Ohota_na_vedmu", "3");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "a"));
			LocatorReloadEnterDisable("Beliz_town", "reloadR1", false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "OfficerGuard_Again":
			dialog.text = "Sorry, "+ GetSexPhrase("senor", "senorita")+", but I'm not supposed to let anyone in.";
			link.l1 = "Whatever you say, officer. Goodbye!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OfficerGuard_Again";
		break;

		case "Soldat15":
			dialog.text = ""+ GetSexPhrase("Senor", "Senorita")+", please talk to the governor.";
			link.l1 = "Thank you, soldier, I will do so.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Soldat15";
		break;

		case "RazgovorSGuberom":
			dialog.text = "";
			link.l1 = "Senor Governor! Please forgive me for entering here, but I found suspicious activity in your residence and decided to show curiosity. In one of the rooms I found the corpse...";
			link.l1.go = "RazgovorSGuberom_2";
			locations[FindLocation("Beliz_TownhallRoom")].id.label = "TownhallRoom";	//возвращает работников в спальни
		break;

		case "RazgovorSGuberom_2":
			dialog.text = "Strange things are happening here, Captain. My right-hand man, my secretary, was found dead in his room. Someone strangled him right in bed, his hands were clenched at his throat, and his eyes were bulging. But there are no traces of rope or fingers on the neck. I do not know what all this means. This is a terrible tragedy.";
			link.l1 = "What a strange story. But how did it happen that an Englishman became your secretary?";
			link.l1.go = "RazgovorSGuberom_3";
		break;

		case "RazgovorSGuberom_3":
			dialog.text = "(addressing the guards) Leave us.";
			link.l1 = "";
			link.l1.go = "RazgovorSGuberom_4";
		break;

		case "RazgovorSGuberom_4":
			dialog.text = "The British government exiled him. They made false accusations against him. He was a very noble man with a wonderful character. We met fifteen years ago in Europe. He was a young diplomat then, and we met at court. One of my agents crossed paths with him in Port Royal. He was thrown out on the street after being accused of embezzlement. Stripped of his title, he agreed to become my secretary.";
			link.l1 = "I think I've met him. Bartholomew, you say? It seems that in the square, he was looking for a girl from a tavern named Maria Carle.";
			link.l1.go = "RazgovorSGuberom_5";
			sld = CharacterFromID("PDM_ONV_SoldatGub_1");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorGoToLocator(sld, "goto", "goto3", "PDM_ONV_STRAJIschezni", 3);
			sld = CharacterFromID("PDM_ONV_SoldatGub_2");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorGoToLocator(sld, "goto", "goto3", "PDM_ONV_STRAJIschezni", 3);
		break;

		case "RazgovorSGuberom_5":
			dialog.text = "The girl from the tavern? It's very strange. He was a noble man, as I said, he could have nothing in common with a woman of such reputation.";
			link.l1 = "Senor Governor, what do you think about his death? Who could have killed him?";
			link.l1.go = "RazgovorSGuberom_6";
		break;

		case "RazgovorSGuberom_6":
			dialog.text = "These are the intrigues of the enemies of the Spanish crown, I suppose. But I can't name anyone in particular...";
			link.l1 = "I hope, Senor Governor, this mystery can be solved. But I have important things to do, and if you'll let me, I'll go.";
			link.l1.go = "RazgovorSGuberom_6_1";
		break;

		case "RazgovorSGuberom_6_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "officers", "reload1_2", "", -1);
			DoQuestFunctionDelay("PDM_ONV_NaRabotu", 2.6);
		break;

		case "RazgovorSGuberom_7":
			dialog.text = "Actually, yes, "+ GetSexPhrase("senor", "senorita")+" "+pchar.name+". You said poor Bartholomew was looking for a tavern girl named Maria Carle, right? Won't you bring her to me? I could send for her, but that would cause a wave of rumors. Maybe you could handle this case more delicately. I decided to take the investigation under my personal control.";
			link.l1 = "Okay, senor Governor, if I find her, of course I'll bring her here.";
			link.l1.go = "RazgovorSGuberom_COD";
			link.l2 = "I'm sorry, but this job is not for me.";
			link.l2.go = "OtkazOtZadaniya";
			NextDiag.TempNode = "RazgovorSGuberom_Again";
		break;
		
		case "OtkazOtZadaniya":
			dialog.text = "It's a pity, then I dare not detain you.";
			link.l1 = "Goodbye!";
			link.l1.go = "OtkazOtZadaniya_2";
			NextDiag.TempNode = "RazgovorSGuberom_AgainOtkaz";
		break;
		
		case "OtkazOtZadaniya_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			
			LocatorReloadEnterDisable("Beliz_Townhall", "reload1_back", false);
			LocatorReloadEnterDisable("Beliz_Townhall", "reload3", true);
			PChar.quest.PDM_ONV_VernutBezZadaniya.win_condition.l1 = "location";
			PChar.quest.PDM_ONV_VernutBezZadaniya.win_condition.l1.location = "Beliz_town";
			PChar.quest.PDM_ONV_VernutBezZadaniya.win_condition = "PDM_ONV_VernutBezZadaniya";
			CloseQuestHeader("PDM_Ohota_na_vedmu");			
			pchar.questdata.OhotaNaVedmu = 1;			
			sld = CharacterFromID("PDM_ONV_Sin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;
		
		case "RazgovorSGuberom_AgainOtkaz":
			dialog.text = "I'll ask you to leave my office, I have a lot of work to do.";
			link.l1 = "I'm already leaving.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RazgovorSGuberom_AgainOtkaz";
		break;

		case "RazgovorSGuberom_Again":
			dialog.text = "I have already given you a task, "+ GetSexPhrase("senor", "senorita")+". What else did you want to ask?";
			link.l1 = "I forgot, Senor Governor. I'm going to look for the girl Maria. Goodbye!";
			link.l1.go = "exit";
			NextDiag.TempNode = "RazgovorSGuberom_Again";
		break;

		case "RazgovorSGuberom_COD":
			LocatorReloadEnterDisable("Beliz_Townhall", "reload1_back", false);
			LocatorReloadEnterDisable("Beliz_Townhall", "reload3", true);

			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition.l1 = "location";
			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition.l1.location = "Beliz_town";
			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition = "PDM_ONV_SVOBODA_URA";

			AddQuestRecord("PDM_Ohota_na_vedmu", "5");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex1", GetSexPhrase("xia", "as"));
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex2", GetSexPhrase("en", "on"));
			sld = CharacterFromID("PDM_ONV_Sin");
			ChangeCharacterAddressGroup(sld, "none", "", "");

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "RazgovorSViktorom_1":
			dialog.text = "Who are you, "+ GetSexPhrase("guy", "girl")+"? And what the hell do you want?";
			link.l1 = "I thought that you are a merchant who may need an escort... But it looks like I'm wrong.";
			link.l1.go = "RazgovorSViktorom_2";
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_PortoBello");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_SanJuan");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Maracaibo");
			UnmarkCharacter(npchar);
		break;

		case "RazgovorSViktorom_2":
			dialog.text = "Yes, "+ GetSexPhrase("buddy, you made a mistake", "honey, you made a mistake")+". I am Silino Sav, an unemployed boatswain. Yesterday, a brainless idiot offered me a job as a lumberjack. Do you know what happened to him?";
			link.l1 = "Understood... But let's sit over a mug of rum and you tell me your story.";
			link.l1.go = "RazgovorSViktorom_3";
		break;

		case "RazgovorSViktorom_3":
			ChangeCharacterAddressGroup(pchar, PChar.location, "sit", "sit_front2");
			LAi_SetSitType(pchar);
			LAi_SetSitType(npchar);
			locCameraTarget(PChar)
            locCameraFollow();
			dialog.text = "I'll tell you what happened to me - but this is not an interesting fairy tale that is told to children. It all happened because of that damned witch that captain picked up in Havana. I'll tell you, if he hadn't gotten involved with that witch, he'd be alive now. But he was always too stubborn. He could out-argue the devil himself, our good old Miguel\n"+
							"But after this woman came on board, he changed. Yes, he has changed. He dried up like a dried roach. We told him not to take this woman with him - it is considered among sailors that a woman is on board, this is unfortunate... When there's a woman on board, expect trouble\n"+
							"And because of this Maria Carle...";
			link.l1 = "Wait! Did you say her name was Maria Carle? This woman is wanted by the Governor of Belize. He thinks she might be involved in the murder!";
			link.l1.go = "RazgovorSViktorom_4";
		break;

		case "RazgovorSViktorom_4":
			dialog.text = "Yes, the governor is right. That damn witch killed our captain. He was dead as a dead cod when we reached Santiago. We had just entered the port when we found him dead on the deck. We rushed to look for the cursed witch, but she mysteriously disappeared. And now I'm an unemployed boatswain. The bludgeon first mate exactly fulfilled the last will of captain, and sold our tub, and donated all the money to the Church.";
			link.l1 = "What an infernal fiend is this woman! She's already killed two people. She must be stopped.";
			link.l1.go = "RazgovorSViktorom_5";
		break;

		case "RazgovorSViktorom_5":
			dialog.text = "Good luck captain in finding her!";
			link.l1 = "I will definitely find her. See you later!";
			link.l1.go = "RazgovorSViktorom_COD";
			NextDiag.TempNode = "RazgovorSViktorom_Again";
		break;

		case "RazgovorSViktorom_COD":
			sld = CharacterFromID("PDM_ONV_Viktor_Martos");
			sld.lifeday = 0;

			AddQuestRecord("PDM_Ohota_na_vedmu", "11");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "a"));

			ChangeCharacterAddressGroup(pchar, PChar.location, "tables", "stay2");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Carla", "Witch", "woman", "woman", 10, SPAIN, -1, false));
			sld.city = "Santiago";
			ChangeCharacterAddressGroup(sld, "Santiago_tavern", "goto", "goto4");
			LAi_SetWaitressType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.name = "Maria";
			sld.lastname = "Carle";
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "Carla_Final_1";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "RazgovorSViktorom_Again":
			dialog.text = "Good luck captain in finding her!";
			link.l1 = "I will definitely find her. See you later!";
			link.l1.go = "exit";
			NextDiag.TempNode = "RazgovorSViktorom_Again";
		break;

		case "Carla_Final_1":
			dialog.text = "Oh dear! What are you doing tonight? Or right now?";
			link.l1 = "Brazen witch! Do you allow yourself to continue your unholy pursuits and incline honest Spaniards to serve the devil!? I have been ordered to bring you to justice!";
			link.l1.go = "Carla_Final_2";
			PlayVoice("Kopcapkz\Voices\PDM\Carla.wav");
		break;

		case "Carla_Final_2":
			dialog.text = "W-what are you saying, "+ GetSexPhrase("senor", "senorita")+"? I don't know about any crimes.";
			link.l1 = "Do you think you can prove your innocence by denying the obvious? I have a witness - Bosun Silino Sav. He's ready to testify that you're a witch.";
			link.l1.go = "Carla_Final_5";
			link.l2 = "I have a witness - bosun Silino Sav. Miguel Cuenda died on his ship near Santiago! And we'll find out what a disgusting role your sorcery played in the terrible death of Bartholomew Ulster in Havana. And... No, I changed my mind. I will find justice for you right here in this city. The Inquisition will listen to me-and my words will be enough to punish you.";
			link.l2.go = "NaKoster_2";
		break;

		case "Carla_Final_5":
			dialog.text = "I know that Miguel's death was my fault... But I couldn't help it-I had to get rid of that bastard Bartholomew. But when he finally uttered his curse, I realized that it was over. Miguel was doomed. I loved him...";
			link.l1 = "Wait. I didn't understand anything. What kind of curse? Loved who?";
			link.l1.go = "Carla_Final_6";
		break;

		case "Carla_Final_6":
			dialog.text = "Bartholomew Ulster cast a death spell on Miguel. I tried to save Miguel all the way to Santiago, but... In vain. My strength just wasn't enough to dispel his powerful magic. I was just a student who was not destined to surpass the teacher.";
			link.l1 = "So you admit that you are a witch?";
			link.l1.go = "Carla_Final_7";
		break;

		case "Carla_Final_7":
			dialog.text = "Yes. Bartholomew Ulster was my mentor in the art of divination. He noticed this Gift in me when I was only fourteen. Then I was just a silly girl who didn't understand what she was doing. I wasn't pretty, but he told me how to win men's hearts, and I became just a cheap prostitute. He used me to pry secrets from clients, he put me through every humiliation I could imagine. I just couldn't live anymore - he was too strong..\n"+
							"But when I met Miguel, I thought I had an opportunity... I fell in love with this brave captain... but Bartholomew said that if I tried to escape, he would tell the priests that I was a witch and they would burn me at the stake. I told Miguel everything. And he decided that we should kill Ulster. My Gift was too weak to handle it magically, and I'm just a weak woman. But Miguel gave me faith.";
			link.l1 = "But how did you get through the guards?";
			link.l1.go = "Carla_Final_8";
		break;

		case "Carla_Final_8":
			dialog.text = "It was the simplest. I put a sleeping potion in their drink... and they fell asleep like babies. After that, we sneaked into the bedroom of this monster in human form.  But he didn't sleep, as we had hoped. I think he put a guard formula on the door, which woke him up. Miguel rushed at him, but the bastard managed to use magic. The wounded Miguel fought with the sorcerer and strangled him with a pillow in the end\n"+
							"I tried to save Miguel all the way to Santiago. But when he fell dead on the deck, I had to escape from the ship. The crew was furious-I was the only woman on the ship whom captain wouldn't let touch a finger. While we were sailing, they became angry like a pack of wild dogs.";
			link.l1 = "And then what happened?";
			link.l1.go = "Carla_Final_10";
		break;

		case "Carla_Final_10":
			dialog.text = "I didn't know what to do. All I wanted was to escape from my past. When I arrived here, I didn't have any money, and I went back to the only thing I know...";
			link.l1 = "The only important thing about this is that you are a witch. Therefore, I will hand you over to the Inquisition.";
			link.l1.go = "NaKoster_2";
			link.l2 = "I don't think you've committed any crime, Maria. You are free.";
			link.l2.go = "Carla_Final_11";
		break;

		case "Carla_Final_11":
			dialog.text = "Oh, "+ GetSexPhrase("senor", "senorita")+" - you are very noble. I'll tell you what. Everyone believes that witchcraft is an occupation objectionable to God. But I'll tell you that it's just a Gift, or a Skill, like any other...";
			link.l1 = "";
			link.l1.go = "Carla_Final_12";
		break;

		case "NaKoster_2":
			dialog.text = "As you wish, "+ GetSexPhrase("senor", "senorita")+". My life means nothing to me anymore-I have not seen mercy, I have not gained love -it would be strange to count on justice.";
			link.l1 = "Don't try to soften me up, you damned witch! You will burn in the fire!";
			link.l1.go = "NaKoster_COD";
			NextDiag.TempNode = "NaKoster_Again";
		break;

		case "Carla_Final_12":
			dialog.text = "And accept my gift. Good luck will accompany you from this day on.";
			link.l1 = "I wish you good luck, Maria! See you later.";
			link.l1.go = "Dobro_Final";
			NextDiag.TempNode = "Carla_Final_Again";
			LAi_SetHP(pchar,LAi_GetCharacterMaxHP(pchar)+40,LAi_GetCharacterMaxHP(pchar)+40);
			PlaySound("Interfaceew_level.wav");
			Log_info("The witch has cast a spell on you.");
			Log_info("Your health has increased by 40 forever.");
		break;

		case "Dobro_Final":
			AddQuestRecord("PDM_Ohota_na_vedmu", "12");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("PDM_Ohota_na_vedmu");
			pchar.questdata.OhotaNaVedmu = 1;
			ChangeCharacterReputation(pchar, 3);
			AddCharacterExpToSkill(pchar, "Fortune", 300);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Carla_Final_Again":
			dialog.text = "Thank you, "+ GetSexPhrase("kind senor", "kind senorita")+"I will not forget your generosity!";
			link.l1 = "Good luck to you, Maria!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Carla_Final_Again";
			PlayVoice("Kopcapkz\Voices\PDM\Carla.wav");
		break;

		case "NaKoster_COD":
			pchar.questTemp.PDM_ONV_OhotaNaVedmu = true;

			AddQuestRecord("PDM_Ohota_na_vedmu", "13");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "а"));

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NaKoster_Again":
			dialog.text = "My life is worth nothing anymore... But I won't spend even a minute of her remaining time talking to you.";
			link.l1 = "You will burn in the fire, you vile witch!";
			link.l1.go = "exit";
			NextDiag.TempNode = "NaKoster_Again";
		break;

		case "Inqizitor_1":
			dialog.text = "... this city is mired in sin! But soon we will free people from the dark snares of Satan with the fire and will of our Lord! Uh... what do you want, "+ GetSexPhrase("my son", "my daughter") +"?";
			link.l1 = "Holy Father, I know there is a witch here named Maria, a former harbor prostitute. With her dark art, she has already killed two people - Captain Miguel Cuenda, and the good hidalgo Bartholomew, who died before he could repent. He was Don Francisco's servant. I pray to God that the Holy Inquisition will punish her for her sinful deeds.";
			link.l1.go = "Inqizitor_2";
			PlayVoice("Kopcapkz\Voices\PDM\Zaharia Marlow-02.wav");
		break;

		case "Inqizitor_2":
			dialog.text = "Ah, may your soul be eternally blessed for your righteous deed, "+ GetSexPhrase("my son", "my daughter") +". We will take care of this witch.";
			link.l1 = "I hope so, Holy Father. Have a nice day.";
			link.l1.go = "KAZN";
			AddBonusEnergyToCharacter(pchar, 25);
			PlaySound("Interfaceew_level.wav");
			Log_info("Your energy has increased by 25 forever.");
		break;

		case "KAZN":
			DoQuestReloadToLocation("Santiago_town", "officers", "reload8_2", "PDM_ONV_KaznVedmi");
			TavernWaitDate("wait_night");
		break;
	}
}
