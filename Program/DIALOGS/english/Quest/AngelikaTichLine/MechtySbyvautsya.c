void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	ref _location;
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
		
////////////////////////////////////////////////////////////////////////////////////////////////
// Анжелика Тич: "Dreams come true"			Авторы: Nikk и Sinistra
////////////////////////////////////////////////////////////////////////////////////////////////			
		
		case "First time":
			dialog.text = "";
			link.l1 = "Becky, this room is going to turn into a cell soon.";
			link.l1.go = "Rebekka_v_komnate_2";
		break;
		
		case "Rebekka_v_komnate_2":
			dialog.text = "Don't start, I already know how our conversation will end again.";
			link.l1 = "I was at the port, there's a ship from Havana. Military... A new commandant has arrived, who has been appointed to take our father's place. I managed to talk to him and describe with all directness the difficult situation in which we found ourselves.";
			link.l1.go = "Rebekka_v_komnate_3";
		break;
		
		case "Rebekka_v_komnate_3":
			dialog.text = "I don't think it was very tactful of you. It was worth inviting him to dinner first, after all, this house would soon become his home. We would show the rooms, solve the issue of furniture and some things.";
			link.l1 = "We'll have more time! The commandant kindly granted a postponement for four whole months. Four damn months to find a match for you, and I'll be calm about your fate, sister.";
			link.l1.go = "Rebekka_v_komnate_4";
		break;
		
		case "Rebekka_v_komnate_4":
			dialog.text = "Here you go, this time you had a shorter preface than ever before before you got to the point.";
			link.l1 = "There are enough candidates on the ship. Notable young officers are also present at the parade! A couple of those who got off the first boat are very good-looking. Let's go make our presence known before they hide in their barracks burrows from the midday heat.";
			link.l1.go = "Rebekka_v_komnate_5";
		break;
		
		case "Rebekka_v_komnate_5":
			dialog.text = "Look out for someone and you're for yourself...";
			link.l1 = "";
			link.l1.go = "Rebekka_v_komnate_5_1";
		break;
		
		case "Rebekka_v_komnate_5_1":
			dialog.text = "";
			link.l1 = "No, I plan to finally leave this hole as soon as I get you into safe hands. Have I been mastering the art of navigation and learning to read maps for nothing over the past few years? I'll get a job as a navigator on a ship, go on an adventure. Ha ha! I have a better chance of becoming a navigator than these illiterate young aristocrats who get seasick from just looking at the deck.";
			link.l1.go = "Rebekka_v_komnate_6";
			locCameraFromToPos(1.00, 3.50, 9.00, false, -15.00, -5.70, 38.25);
		break;
		
		case "Rebekka_v_komnate_6":
			dialog.text = "Angelica, one of these illiterate young aristocrats is probably my future husband, doesn't it seem so? And you'd rather go to meet death than adventure. You're a woman and...";
			link.l1 = "Hey! The blood of Tichy flows in me, not Remedios! Don't forget who my real father is.";
			link.l1.go = "Rebekka_v_komnate_7";
		break;
		
		case "Rebekka_v_komnate_7":
			dialog.text = "Of course I remember. My mermaid stepmother, who traded her legs for a voice, has told this story more than once, how you have not set foot on solid ground for almost a year, rushing around the archipelago in search of prey.";
			link.l1 = "Really, how fun it is. If you tell our parable to your future cavalier in the same words, he will surely appreciate not only your beauty, but also your sharpness of mind.";
			link.l1.go = "Rebekka_v_komnate_8";
		break;
		
		case "Rebekka_v_komnate_8":
			dialog.text = "You started this conversation yourself.";
			link.l1 = "I'll finish it. Catch up.";
			link.l1.go = "Rebekka_v_komnate_9";
		break;
		
		case "Rebekka_v_komnate_9":
			DialogExit();
			EndQuestMovie();
			bDisableCharacterMenu = false;
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
			
			SetQuestHeader("AT_Mechty_Sbivautsya");
			AddQuestRecord("AT_Mechty_Sbivautsya", "0.1");
			
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			
			PChar.quest.At_pr_Rebekka_gulyat.win_condition.l1 = "location";
			PChar.quest.At_pr_Rebekka_gulyat.win_condition.l1.location = "LaVega_town";
			PChar.quest.At_pr_Rebekka_gulyat.function = "At_pr_Rebekka_gulyat";
			
			sld = CharacterFromID("Edward Mansfield")
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
			
			//Испанский губернатор
			sld = GetCharacter(NPC_GenerateCharacter("AT_pr_LaVegaIspanski_Gubernator", "SpaOfficer1", "man", "man", 15, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, 100, 100, 100, "blade20", "howdah", 500);
			sld.name	= "Aurelio";
			sld.lastname	= "Serrano";
			sld.SaveItemsForDead = true;
			sld.Dialog.Filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "LaVegaIspanski_Gubernator";
			LAi_SetHuberType(sld);
			LAi_SetImmortal(sld, true);
			DeleteAttribute(sld, "items");
			AddMoneyToCharacter(sld, 12345);
			GiveItem2Character(sld, "blade19");
			EquipCharacterByItem(sld, "blade19");
			GiveItem2Character(sld, "BackPack2");
			GiveItem2Character(sld, "talisman6");
			AddItems(sld, "jewelry4", 30);
			ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
			
			//Торговец на улице (продолжение квеста)
			FreeSitLocator("LaVega_town", "protector2");
			sld = GetCharacter(NPC_GenerateCharacter("Gasten_Kotes", "shipowner_13", "man", "man", 1, SPAIN, -1, false));
			FantomMakeCoolFighter(sld, 1, 10, 10, "blade3", "", 10);
			sld.name	= "Gasten";
			sld.lastname	= "Cats";
			SetCharacterPerk(sld, "Trader");
			SetCharacterPerk(sld, "BasicCommerce");
			SetSPECIAL(sld, 6, 4, 8, 8, 10, 6, 7);
			SetShipSkill(sld, 27, 45, 21, 14, 18, 21, 13, 9, 28);
			TakeNItems(sld, "potion1", -10);
			TakeNItems(sld, "potion2", -10);
			sld.Dialog.Filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "Torgovets_1";
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "LaVega_town", "merchant", "merchant3");
			sld.talker = 5;
			
			//Девушка на улице (продолжение квеста)
			sld = GetCharacter(NPC_GenerateCharacter("AT_pr_devushka_na_rynke", "CitizenWom_2", "woman", "woman", 10, SPAIN, -1, false));
			if(InterfaceStates.EnabledQuestsMarks)
			{
				sld.quest.questflag.model = "exclamationmarkY";
			}
			sld.name	= "Sofia";
			sld.lastname	= "de la Piedad";
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "LaVega_town", "merchant", "mrcActive3");
			
			//Какой-то мужик со шляпой
			sld = CharacterFromID("Old Friend")
			sld.Dialog.Filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "man_shlyapa";
			DeleteAttribute(sld, "talker");
		break;
		
		case "LaVegaIspanski_Gubernator":
			dialog.text = "Senorita Remedios? We have discussed everything with you. My decision stands, you have nothing to worry about.";
			link.l1 = "My sister insisted that I invite you to a family dinner.";
			link.l1.go = "LaVegaIspanski_Gubernator_2";
		break;
		
		case "LaVegaIspanski_Gubernator_2":
			dialog.text = "Hmm, thank you. I think I'll be busy for the next few days, but I'll definitely accept the offer.";
			link.l1 = "Wonderful. I'm not distracting you anymore.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LaVegaIspanski_Gubernator_3";
		break;
		
		case "LaVegaIspanski_Gubernator_3":
			dialog.text = "You again?";
			link.l1 = "I'm leaving now.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LaVegaIspanski_Gubernator_3";
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_1":
			sld = CharacterFromID(pchar.ATP_MirJitId)
			dialog.text = "(to a civilian) We went out for a walk with my sister, maybe you need some help?";
			link.l1 = "";
			link.l1.go = "Rebekka_s_mirnymi_jitelyami_1_1";
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(CharacterFromID("AT_pr_Rebekka"), CharacterFromID(pchar.ATP_MirJitId));
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_1_1":
			DialogExit();
			StartInstantDialog(pchar.ATP_MirJitId, "ATP_1_1", "Common_citizen.c");
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_2":
			sld = CharacterFromID(pchar.ATP_MirJitId)
			dialog.text = "(to a civilian) "+sld.name+"Thank you for the compliment.";
			link.l1 = "";
			link.l1.go = "Rebekka_s_mirnymi_jitelyami_2_1";
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(CharacterFromID("AT_pr_Rebekka"), CharacterFromID(pchar.ATP_MirJitId));
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_2_1":
			DialogExit();
			StartInstantDialog(pchar.ATP_MirJitId, "ATP_2_1", "Common_citizen.c");
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_3":
			sld = CharacterFromID(pchar.ATP_MirJitId)
			dialog.text = "(smiles sheepishly)";
			link.l1 = "";
			link.l1.go = "Rebekka_s_mirnymi_jitelyami_3_1";
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(CharacterFromID("AT_pr_Rebekka"), CharacterFromID(pchar.ATP_MirJitId));
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_3_1":
			DialogExit();
			StartInstantDialog(pchar.ATP_MirJitId, "ATP_3_1", "Common_citizen.c");
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_4":
			sld = CharacterFromID(pchar.ATP_MirJitId)
			dialog.text = "No, Angelica, it was quite stuffy yesterday morning.";
			link.l1 = "";
			link.l1.go = "Rebekka_s_mirnymi_jitelyami_4_1";
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(CharacterFromID("AT_pr_Rebekka"), pchar);
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_4_1":
			DialogExit();
			StartInstantDialog(pchar.ATP_MirJitId, "ATP_4_1", "Common_citizen.c");
		break;
		
		case "man_shlyapa":
			dialog.text = "Good afternoon! What can I do for you?";
			link.l1 = "Hello! You have a wonderful hat.";
			link.l1.go = "exit";
			NextDiag.TempNode = "man_shlyapa";
		break;
		
		case "Torgovets_1":
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "attack_break_1", "pchar_back_to_player", 0.1);
			StartQuestMovie(true, true, true);
			dialog.text = "Senorita, I can't let you go on loan, you're not from the locals, but tomorrow you'll board a passing ship and only you were seen.";
			link.l1 = "";
			link.l1.go = "Torgovets_2";
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("AT_pr_devushka_na_rynke"));
			locCameraToPos(-38.00, 7.00, 20.00, true);
		break;
		
		case "Torgovets_2":
			DialogExit();
			StartInstantDialog("AT_pr_devushka_na_rynke", "Torgovets_3", "Quest\AngelikaTichLine\MechtySbyvautsya.c");
		break;
		
		case "Torgovets_3":
			dialog.text = "But I'm not asking for a loan, I'll pay two-thirds of the price right now, I can work out the rest - to help you or your spouse.";
			link.l1 = "";
			link.l1.go = "Torgovets_4";
			sld = CharacterFromID("AT_pr_devushka_na_rynke")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Gasten_Kotes"));
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Gasten_Kotes"));
			
			locCameraSleep(true);
		break;
		
		case "Torgovets_4":
			DialogExit();
			StartInstantDialog("Gasten_Kotes", "Torgovets_5", "Quest\AngelikaTichLine\MechtySbyvautsya.c");
		break;
		
		case "Torgovets_5":
			dialog.text = "I don't really have a lot of work, I do everything perfectly on my own, and I'm not married. I can offer you two thirds of the goods...";
			link.l1 = "";
			link.l1.go = "Torgovets_6_1";
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("AT_pr_devushka_na_rynke"));
		break;
		
		case "Torgovets_6_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "merchant", "mrcActive3", "", -1);
			DoQuestFunctionDelay("AT_pr_Torgovets_6_2", 1.0);
		break;
		
		case "Torgovets_6_3":
			dialog.text = "";
			link.l1 = "Gasten-lis, don't you see, the senorita has a difficult fate imprinted on her face, without looking at her youth. Show compassion.";
			link.l1.go = "Torgovets_7";
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = CharacterFromID("AT_pr_devushka_na_rynke")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "Torgovets_7":
			dialog.text = "What would you understand about people, dear Angelica, if you couldn't see a scoundrel in your stepfather, may he rest in peace.";
			link.l1 = "Careful, Fox, you know I can get angry over a mere trifle.";
			link.l1.go = "Torgovets_8";
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = CharacterFromID("AT_pr_devushka_na_rynke")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "Torgovets_8":
			dialog.text = "First, change your skirt for trousers before making threats. There is no longer a commandant standing behind you, ready to cover up all your antics. This is good advice, don't take it as an insult.";
			link.l1 = "I also have something under my skirt, it's called a carcass, let me show you how I can take care of myself, at the same time I'll give you good advice: defend yourself!";
			link.l1.go = "Torgovets_9";
		break;
		
		case "Torgovets_9":
			dialog.text = "Don't be stupid.";
			link.l1 = "Defend yourself, or change your trousers for a skirt!";
			link.l1.go = "Torgovets_10";
		break;
		
		case "Torgovets_10":
			DialogExit();
			
			LAi_SetActorType(pchar);
			AddQuestRecord("AT_Mechty_Sbivautsya", "0.2");
			Log_info("We need to teach the scoundrel a lesson! Follow him!");
			
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1);
			chrDisableReloadToLocation = true;
			
			sld = CharacterFromID("AT_pr_devushka_na_rynke")
			LAi_SetActorType(sld);
			
			PChar.quest.AT_pr_Draka_s_Kotesom.win_condition.l1 = "location";
			PChar.quest.AT_pr_Draka_s_Kotesom.win_condition.l1.location = "LaVega_ExitTown";
			PChar.quest.AT_pr_Draka_s_Kotesom.function = "AT_pr_Draka_s_Kotesom";
			
			DoQuestFunctionDelay("AT_pr_Torgovets_10_1", 1.0);
		break;
		
		case "Rebekka_posle_draki":
			dialog.text = "Stop it! You almost killed him!";
			link.l1 = "I just showed our friend what a tongue is worth when it's longer than a sword.";
			link.l1.go = "Rebekka_posle_draki_2";
			
			sld = characterFromId("Gasten_Kotes");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			//LAi_ActorAnimation(sld, "kneeling_2", "", 2.4);
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
		break;
		
		case "Rebekka_posle_draki_2":
			dialog.text = "Well done, now help me bandage him up, and come up with an excuse for yourself if you don't want to be arrested. ";
			link.l1 = "Don't worry, everything will be fine. When this fox broke into the jungle, the soldiers almost tore their bellies looking at this sight, and the scratch will heal in a couple of hours. I'm more concerned about who this girl is, where she's from. I'll go and look for her.";
			link.l1.go = "Rebekka_posle_draki_3";
		break;
		
		case "Rebekka_posle_draki_3":
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			pchar.questTemp.AnjelikaTichPrologue2 = "ATP2";
			AddQuestRecord("AT_Mechty_Sbivautsya", "0.3");
			
			PChar.quest.AT_pr_Oba_ischezaut.win_condition.l1 = "ExitFromLocation";
			PChar.quest.AT_pr_Oba_ischezaut.win_condition.l1.location = PChar.location;
			PChar.quest.AT_pr_Oba_ischezaut.function = "AT_pr_Oba_ischezaut";
		
			sld = characterFromId("AT_pr_Rebekka");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromId("Gasten_Kotes"), "", -1);
			
			sld = CharacterFromID("AT_pr_devushka_na_rynke")
			if(InterfaceStates.EnabledQuestsMarks)
			{
				sld.quest.questflag.model = "exclamationmarkY";
			}
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, "LaVega_town", "goto", "goto2");
			sld.dialog.filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "Sofia_1";
			
			DialogExit();
		break;
		
		case "Sofia_1":
			dialog.text = "";
			link.l1 = "Excuse me, senorita, may I accompany you?";
			link.l1.go = "Sofia_2";
			UnmarkCharacter(npchar);
		break;
		
		case "Sofia_2":
			dialog.text = "Of course... My name is Sofia, Sofia de la Piedad, until recently. You really shouldn't have treated the master so harshly.";
			link.l1 = "The gentleman has long deserved to be treated like this. But yes, the dog is with him. I have been Angelica Remedios since quite a long time ago. The adopted daughter of the former commandant of this colony abandoned by all Christian saints.";
			link.l1.go = "Sofia_3";
		break;
		
		case "Sofia_3":
			dialog.text = "And now? Is your stepfather being transferred to another duty station?";
			link.l1 = "He died a little over a month ago, a rather ridiculous death, had an argument with one of his subordinates. My stepsister and I had no other relatives left here, and we found ourselves on our own.";
			link.l1.go = "Sofia_4";
		break;
		
		case "Sofia_4":
			dialog.text = "I'm sorry. It seems that you and I have a similar problem.";
			link.l1 = "It seemed so to me right away. I assume you came down from the warship that docked this morning, but obviously without your father or husband accompanying you.";
			link.l1.go = "Sofia_5";
		break;
		
		case "Sofia_5":
			dialog.text = "Yes, I was recently married to a military man. We got married hastily at the insistence of my parents, as my husband was waiting for a business trip here to the New World. He left Europe for Havana via Sierra Leone, and two weeks later I was put on a merchant ship going straight to these parts\n"+
							"So I ended up in Havana even earlier, and when I waited, I found out that as soon as they sailed from the coast of Africa, the ship was seized with fever, and my husband was among those who did not survive it.";
			link.l1 = "Your parents married you, so it was a marriage of convenience?";
			link.l1.go = "Sofia_6";
		break;
		
		case "Sofia_6":
			dialog.text = "I didn't even know whether to grieve or rejoice, I didn't want to marry this man and barely knew him, but I don't have anyone else, and most importantly, I have no means of livelihood left. The captain kindly agreed to take me back to Europe, provided that upon arrival my parents would pay for my trip, but what can I live on now?"+
							"Besides, before we return, we still have to stay here for a couple of days and visit Porto Bello, I think that's what he said.";
			link.l1 = "My childhood and youth were not calm, I would probably treat such events as an adventure, but it must be hard for you to break away from a measured life and find yourself in such an abyss of trouble. But it seems that luck has smiled on you after all, we can help each other.";
			link.l1.go = "Sofia_7";
		break;
		
		case "Sofia_7":
			dialog.text = "It's not worth it, talking to you has already helped me feel better...";
			link.l1 = "No objections. I have some things hidden in a grotto nearby. I can't sell or exchange them, but they will definitely help you.";
			link.l1.go = "Sofia_8";
		break;
		
		case "Sofia_8":
			dialog.text = "What's wrong with them, are they cursed?";
			link.l1 = "Ha ha! No, of course not, but I bet their former owner has been cursed a fair amount more than once. Wait here, I'll be back soon, but don't say a word to anyone.";
			link.l1.go = "Sofia_9";
		break;
		
		case "Sofia_9":
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("AT_Mechty_Sbivautsya", "1");
			
			PChar.quest.AT_MS_PodskazkaGrot.win_condition.l1 = "location";
			PChar.quest.AT_MS_PodskazkaGrot.win_condition.l1.location = "Shore32";
			PChar.quest.AT_MS_PodskazkaGrot.function = "AT_MS_PodskazkaGrot";
			
			PChar.quest.AT_pr_Grot.win_condition.l1 = "location";
			PChar.quest.AT_pr_Grot.win_condition.l1.location = "Hispaniola_Grot";
			PChar.quest.AT_pr_Grot.function = "AT_pr_Grot";
			
			pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry6 = 10;
			pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry17 = 5;
			pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry12 = 15;
			pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry3 = 10;
			pchar.GenQuestBox.Hispaniola_Grot.box1.items.potionwine = 2;
			pchar.GenQuestBox.Hispaniola_Grot.box1.items.spyglass1 = 1;
		
			DialogExit();
		break;
		
		case "Rebekka_v_grote_1":
			dialog.text = "Oh, Angelica!";
			link.l1 = "Becky? What are you doing here? ";
			link.l1.go = "Rebekka_v_grote_2";
			locCameraToPos(3.80, 2.70, -4.00, true);
		break;
		
		case "Rebekka_v_grote_2":
			dialog.text = "I'm sniffing out what you're doing here. You've been acting strangely lately, bullying everyone, constantly running off into the woods, then here to the coast.";
			link.l1 = "So you keep an eye on me from time to time. Look, I can't follow your example and stay locked up all day, and our fort makes me sick. I'm tired of catching the stares of local soldiers, listening to their primitive compliments and jokes.";
			link.l1.go = "Rebekka_v_grote_3";
			locCameraSleep(true);
		break;
		
		case "Rebekka_v_grote_3":
			dialog.text = "I understand. But it's not just that, is it? See\n"+
							"It looks like these are Arcadio's things? That soldier who broke into our house demanding my hand, and the ring is the one he tried to give me before you pushed him out.";
			link.l1 = "It looks like it. Yes.";
			link.l1.go = "Rebekka_v_grote_4";
		break;
		
		case "Rebekka_v_grote_4":
			dialog.text = "When I found out that he was found dead on the shore, I offered prayers to the intercessor mother that she had rid us of this vile man, and you hid his things here? How did you get them? You killed him!";
			link.l1 = "No! Of course not... um... Yes, I was walking outside the city as usual and came across some people. Pirates, or smugglers, I don't know, they're definitely not local, and Arcadio was with them. Of course, I got out of there quickly before I was noticed, and later, when I returned, I found him dead, searched his pockets and ran away.";
			link.l1.go = "Rebekka_v_grote_5";
		break;
		
		case "Rebekka_v_grote_5":
			dialog.text = "And you hid what you found in them here so that no one would find it and think that you stabbed him?";
			link.l1 = "Of course.";
			link.l1.go = "Rebekka_v_grote_6";
		break;
		
		case "Rebekka_v_grote_6":
			dialog.text = "Oh, I wish I could believe you, but today... Senor Cotes, if the sword had grazed him a little to the right, who knows...";
			link.l1 = "It's a carcass, not a sword.";
			link.l1.go = "Rebekka_v_grote_7";
		break;
		
		case "Rebekka_v_grote_7":
			DialogExit();
			
			LAi_SetActorType(pchar);
			DoQuestFunctionDelay("AT_pr_Strelba_is_pushki", 1.3);
		break;
		
		case "Rebekka_v_grote_8":
			dialog.text = "Are they shooting? The fort is firing.";
			link.l1 = "No, I would have recognized the fort's guns. It seems to be a sound from the sea. Let's go faster!";
			link.l1.go = "Rebekka_v_grote_9";
		break;
		
		case "Rebekka_v_grote_9":
			dialog.text = "Are you crazy, but what if the city was attacked? Let's stay here, it'll be safe here.";
			link.l1 = "";
			link.l1.go = "Rebekka_v_grote_10";
		break;
		
		case "Rebekka_v_grote_10":
			DialogExit();
			
			LAi_SetActorType(pchar);
			DoQuestFunctionDelay("AT_pr_Strelba_is_pushki_4", 1.3);
		break;
		
		case "Rebekka_v_grote_11":
			dialog.text = "";
			link.l1 = "And this is the fort shooting. Damn, Rebecca, how did we get here in time with you.";
			link.l1.go = "Rebekka_v_grote_12";
		break;
		
		case "Rebekka_v_grote_12":
			dialog.text = "I hope our guys will fight back, no matter who attacks them.";
			link.l1 = "";
			link.l1.go = "Rebekka_v_grote_13";
		break;
		
		case "Rebekka_v_grote_13":
			DialogExit();
			LAi_SetActorType(pchar);
			locCameraSleep(false);
			SetLaunchFrameFormParam("Evening has come...", "", 0, 2.3);
			LaunchFrameForm();
			DoQuestFunctionDelay("AT_pr_Piraty_v_grote", 2.3);
		break;
		
		case "Pirate_v_grote_1":
			dialog.text = "Oh, who's hiding here? Lucky we got away from ours.";
			link.l1 = "How are you here? Stop! Don't come any closer! I won't let you!";
			link.l1.go = "Pirate_v_grote_2";
		break;
		
		case "Pirate_v_grote_2":
			dialog.text = "Look at that, the mouse has been cornered. Let's attack, let's check if they're telling the truth...";
			link.l1 = "Becky, run!";
			link.l1.go = "Pirate_v_grote_3";
		break;
		
		case "Pirate_v_grote_3":
			DialogExit();
			EndQuestMovie();
			
			sld = characterFromId("AT_pr_Rebekka");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=2; i++)
				{
				sld = CharacterFromID("AT_pr_Piraty_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//стравливаем
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "AT_pr_Pobeda_v_grote");
		break;
		
		case "Stoim_na_pirse":
			dialog.text = "Angelica! You won't believe it, but I'm damn glad to see you alive and well.";
			link.l1 = "Who attacked us? Did we fight back? Where are the survivors?";
			link.l1.go = "Stoim_na_pirse_2";
		break;
		
		case "Stoim_na_pirse_2":
			dialog.text = "Pirates. The whole garrison was defeated, someone managed to escape into the jungle, or, like me, to sit in hiding, but there was no one left here, the last ones crossed over to that bark.";
			link.l1 = "Why do they need our fort, there's nothing to profit from here?";
			link.l1.go = "Stoim_na_pirse_3";
		break;
		
		case "Stoim_na_pirse_3":
			dialog.text = "It looks like they're going to use it as a transit point. Their teams landed and headed inland. I heard mention of Santo Domingo, there is a powerful fortress there, not comparable to ours, but if they manage to attack the city from land, the garrison of the fort will not even have time to come to the rescue before the city is plundered.";
			link.l1 = "They could have landed in any of the bays.";
			link.l1.go = "Stoim_na_pirse_4";
		break;
		
		case "Stoim_na_pirse_4":
			dialog.text = "I do not know their motives, but listen, you know about maritime navigation, right? There are several sailors left on the barge, of course they can guide the ship along the coast, but captain and navigator were in the city, and they were not spared, and we need the best route to avoid reefs, shoals. We have to get to Santo Domingo before the pirates.";
			link.l1 = "My stepfather hired teachers for me, but I never personally steered the ship... And where is Rebecca, did she also go up on the bark?";
			link.l1.go = "Stoim_na_pirse_5";
		break;
		
		case "Stoim_na_pirse_5":
			dialog.text = "I haven't seen her since the siege, since she bandaged my shoulder.";
			link.l1 = "She hasn't returned to the city? Becky was supposed to be here just a few minutes before me. Oh no, I can't sail now, I need to find her.";
			link.l1.go = "Stoim_na_pirse_6";
		break;
		
		case "Stoim_na_pirse_6":
			dialog.text = "We can't wait either, it's not even about having time to warn the governor about the attack, we have enemy ships at our side and there are still people on them who can land here at any moment.";
			link.l1 = "No, I still can't.";
			link.l1.go = "Stoim_na_pirse_7";
		break;
		
		case "Stoim_na_pirse_7":
			dialog.text = "Look, if Rebecca ran into pirates, they most likely took her with them as a hostage, and if she managed to hide in the woods, she will inevitably return here. In any case, we need to get to Santo Domingo as soon as possible. Then we have a chance to find your sister at the walls of the city, or the local governor-general will equip a detachment to recapture our fort, and she can safely return."+ 
							"If you stay here, you will definitely not help anyone, except to entertain this pack of murderers before you die.";
			link.l1 = "The devil... I wish she'd stayed with me. But I might not be able to handle it. Good. Okay, I'm swimming, but give me a minute.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Stoim_na_pirse_8";
		break;
		
		case "Stoim_na_pirse_8":
			dialog.text = "I don't see anyone else here.";
			link.l1 = "Yes, she's nowhere to be found. We're sailing.";
			link.l1.go = "Stoim_na_pirse_9";
		break;
		
		case "Stoim_na_pirse_9":
			DialogExit();
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(sld, "reload", "reload1_back", "AT_pr_Stoim_na_pirse_9", -1);
			
			sld = GetCharacter(NPC_GenerateCharacter("AT_pr_OfficerRezid", "sold_spa_7", "man", "man", 10, SPAIN, -1, true));
			ChangeCharacterAddressGroup(sld, "SantoDomingo_town", "officers", "Reload3_1");
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "AT_pr_Officer_u_rezidenta";
			sld.talker = 5;
			
			sld = CharacterFromID("LaVega_tavernkeeper")	//Возвращаем тавернщику его родной диалог
			sld.Dialog.Filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First time";
		break;
		
		case "AT_pr_Officer_u_rezidenta":
			dialog.text = "Young lady, wait! Where to?";
			link.l1 = "I am a messenger from Fort La Vega with an urgent message to the governor.";
			link.l1.go = "AT_pr_Officer_u_rezidenta_2";
		break;
		
		case "AT_pr_Officer_u_rezidenta_2":
			sld = CharacterFromID("SantoDomingo_Mayor")
			dialog.text = "I see. I would have let you through, but His Lordship is not in his place. Senor " + GetFullName(sld)+" left for the Admiralty.";
			link.l1 = "Is he out of town? Then I need the commandant of the local garrison, or the man whom the governor left in his place.";
			link.l1.go = "AT_pr_Officer_u_rezidenta_3";
		break;
		
		case "AT_pr_Officer_u_rezidenta_3":
			dialog.text = "Is this your first assignment as an ambassador? The Admiralty is that big gray building over there that I'm doomed to look at all day. Go through the arch and turn right. There's also a bank right in front of the door you need.";
			link.l1 = "Thank you.";
			link.l1.go = "AT_pr_Officer_u_rezidenta_4";
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
		break;
		
		case "AT_pr_Officer_u_rezidenta_4":
			DialogExit();
			
			pchar.questTemp.AnjelikaTichPrologue3 = "ATP3";
		break;
		
		case "ATpr_SD_Gubernator_1":
			dialog.text = "";
			link.l1 = "I finally got to you.";
			link.l1.go = "ATpr_SD_Gubernator_2";
		break;
		
		case "ATpr_SD_Gubernator_2":
			dialog.text = "What's the urgency, and who let you in here like this?";
			link.l1 = "I am one of the few survivors of the La Vega colony. We were attacked by Buccaneers, first they fired at the fort from the sea, then they landed on the shore and massacred there.";
			link.l1.go = "ATpr_SD_Gubernator_3";
		break;
		
		case "ATpr_SD_Gubernator_3":
			dialog.text = "Can I trust you?";
			link.l1 = "I have people on the ship who will tell me the same thing, and when I introduced myself to the secretary at the entrance, he confirmed that he knew my stepfather.";
			link.l1.go = "ATpr_SD_Gubernator_4";
		break;
		
		case "ATpr_SD_Gubernator_4":
			dialog.text = "You haven't introduced yourself to me, however, it's not important. Did any of the survivors communicate with these pirates? What are their demands?";
			link.l1 = "As far as I know, none. Part of the pirate team stayed in the harbor on ships, some went hiking through the jungle. They are coming here, and since we are talking here, and everything is quiet in the city, it means that we managed to circumnavigate the island by water before them.";
			link.l1.go = "ATpr_SD_Gubernator_5";
		break;
		
		case "ATpr_SD_Gubernator_5":
			DialogExit();
			StartInstantDialog("ATpr_SD_Off_Guber_2", "ATpr_SD_Gubernator_6", "Quest\AngelikaTichLine\MechtySbyvautsya.c");
		break;
		
		case "ATpr_SD_Gubernator_6":
			dialog.text = "How many can there be?";
			link.l1 = "We saw only two ships, with a total capacity of 300-400 people. No one else was seen on the way here, so there was probably no landing in the bays.";
			link.l1.go = "ATpr_SD_Gubernator_7";
		break;
		
		case "ATpr_SD_Gubernator_7":
			dialog.text = "I cannot redirect the entire garrison from the fort to reinforce the city. We don't know their plans, perhaps they will attack from several sides, if at all.";
			link.l1 = "";
			link.l1.go = "ATpr_SD_Gubernator_8";
			LAi_SetActorType(npchar);
		break;
		
		case "ATpr_SD_Gubernator_8":
			DialogExit();
			StartInstantDialog("SantoDomingo_Mayor", "ATpr_SD_Gubernator_9", "Quest\AngelikaTichLine\MechtySbyvautsya.c");
		break;
		
		case "ATpr_SD_Gubernator_9":
			dialog.text = "I think a couple of squads with muskets will be enough. If there are warships in the raid, it is better to send them to the lighthouse and to the nearest cape to control the approaches.";
			link.l1 = "I have a request, Senor Governor. I absolutely must be there, at the place of the expected attack from the land. My sister might be with them.";
			link.l1.go = "ATpr_SD_Gubernator_10";
		break;
		
		case "ATpr_SD_Gubernator_10":
			dialog.text = "You're a girl, you don't need to be there. However, I can't forbid you, but know that it won't be safe for you there.";
			link.l1 = "Don't worry about me, I'll be able to take care of myself.";
			link.l1.go = "ATpr_SD_Gubernator_11";
		break;
		
		case "ATpr_SD_Gubernator_11":
			DialogExit();
			StartInstantDialog("ATpr_SD_Off_Guber_1", "ATpr_SD_Gubernator_12", "Quest\AngelikaTichLine\MechtySbyvautsya.c");
		break;
		
		case "ATpr_SD_Gubernator_12":
			dialog.text = "Wait outside the city gates. Defense will be organized there in the very near future. The landscape and the jungle will not allow you to approach from anywhere else.";
			link.l1 = "Thank you.";
			link.l1.go = "ATpr_SD_Gubernator_13";
			LAi_SetActorType(npchar);
		break;
		
		case "ATpr_SD_Gubernator_13":
			DialogExit();
			StartInstantDialog("SantoDomingo_Mayor", "ATpr_SD_Gubernator_14", "Quest\AngelikaTichLine\MechtySbyvautsya.c");
		break;
		
		case "ATpr_SD_Gubernator_14":
			dialog.text = "";
			link.l1 = "May I...?";
			link.l1.go = "ATpr_SD_Gubernator_15";
		break;
		
		case "ATpr_SD_Gubernator_15":
			dialog.text = "Yes, you can go.";
			link.l1 = "";
			link.l1.go = "ATpr_SD_Gubernator_16";
			LAi_SetActorType(npchar);
		break;
		
		case "ATpr_SD_Gubernator_16":
			DialogExit();
			
			PChar.quest.ATpr_OboronaSD.win_condition.l1 = "location";
			PChar.quest.ATpr_OboronaSD.win_condition.l1.location = "SantoDomingo_ExitTown";
			PChar.quest.ATpr_OboronaSD.win_condition = "ATpr_OboronaSD";
		break;
		
		case "ATpr_SD_Koten_1":
			dialog.text = "There you are! I see it's all over, but I've already run around half the city and as soon as I heard the sounds of gunfire, I immediately knew where to look for you.";
			link.l1 = "Rebecca is not here...";
			link.l1.go = "ATpr_SD_Koten_2";
		break;
		
		case "ATpr_SD_Koten_2":
			dialog.text = "I'm sorry.";
			link.l1 = "You knew it, and I knew it. I just wanted to see the horror and confusion on their faces when they die here under the walls.";
			link.l1.go = "ATpr_SD_Koten_3";
		break;
		
		case "ATpr_SD_Koten_3":
			dialog.text = "All is not lost yet. Listen, the crew on the ship has organized a council. We decided whether we should stay here or try our luck and return to La Vega, and at the same time offered to choose a captain for ourselves by a general vote.";
			link.l1 = "Hmm... And what did you decide?";
			link.l1.go = "ATpr_SD_Koten_4";
		break;
		
		case "ATpr_SD_Koten_4":
			dialog.text = "We decided that captain would have the last word. Are you with us?";
			link.l1 = "With you, of course. But first you need to look at the governor, in the end, thanks to us, the attack on the city did not come as a surprise. I'm counting on a reward that will allow us to exist for a while.";
			link.l1.go = "ATpr_SD_Koten_5";
		break;
		
		case "ATpr_SD_Koten_5":
			dialog.text = "That would be more than fair. Then I suggest we don't delay, and then welcome aboard, Madam Captain.";
			link.l1 = "";
			link.l1.go = "ATpr_SD_Koten_6";
		break;
		
		case "ATpr_SD_Koten_6":
			dialog.text = "Also, I did a little revision on the ship. I found the right outfit for you. Where has it been seen that a captain walks around the deck in a skirt?";
			link.l1 = "";
			link.l1.go = "ATpr_SD_Koten_6_1";
		break;
		
		case "ATpr_SD_Koten_6_1":
			dialog.text = "Here, try it on.";
			link.l1 = "Turn around, I'll change my clothes...";
			link.l1.go = "ATpr_SD_Koten_6_3";
		break;
		
		/*case "ATpr_SD_Koten_6_2":
			DialogExit();
			SetLaunchFrameFormParam("A minute of changing clothes...", "ATpr_Pereodevaemsya", 0, 2.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 1);
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
		break;*/
		
		case "ATpr_SD_Koten_6_3":
			LAi_Fade("", "");
			dialog.text = "";
			link.l1 = "Not bad, not bad. It will go for the first time. Thank you, Gasten.";
			link.l1.go = "ATpr_SD_Koten_7";
			//SetLaunchFrameFormParam("A minute of changing clothes", "", 0, 2.0);
			//LaunchFrameForm();
			//WaitDate("", 0, 0, 0, 0, 1);
			
			PlaySound("Interface\important_item.wav");
			Log_info("You got a new suit");
		break;
		
		case "ATpr_SD_Koten_7":
			dialog.text = "We're in the same boat now. No matter how much the governor pays, now I'm also penniless, but the commercial vein is not a tray on the square, it's not so easy to knock it out of me with a broadside, and having a ship together we won't be lost.";
			link.l1 = "Yes, it's not a bad idea to start with freight. Fishing in the surrounding waters is definitely not for me. Okay, Senor Cotes, about our plans for the future - later, we still need to get to the residence today.";
			link.l1.go = "ATpr_SD_Koten_8";
			Log_info("Gasten has become your officer");
			PlaySound("interface\notebook.wav");
		break;
		
		case "ATpr_SD_Koten_8":
			DialogExit();
			
			sld = CharacterFromID("Gasten_Kotes")
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			ChangeCharacterReputation(sld, 20);
			sld.loyality = MAX_LOYALITY;
			LAi_SetCurHPMax(sld);
			LAi_SetImmortal(sld, false);
			sld.HalfImmortal = true;
			
			AddSimpleRumour("Pirates captured the Spanish colony of La Vega, and at the same time attempted to attack Santo Domingo. However, they did not succeed, they were all killed at the walls of the city.", PIRATE, 10, 1);
			AddSimpleRumour("Terrible news, pirates have staged a massacre in our colony of La Vega, they say, they did not spare anyone. Thank God, retribution has already overtaken them, all the scoundrels died under the walls of Santo Domingo in an unsuccessful attempt to take the city from the land.", SPAIN, 10, 1);
			pchar.questTemp.AnjelikaTichPrologue6 = "ATP6";
			SetTimerCondition("ATpr_Jiteli_Uspokoilis", 0, 0, 1, false);
			DeleteAttribute(pchar, "questTemp.AnjelikaTichPrologue5");
			DeleteAttribute(pchar, "MaxSailing");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			RemoveCharacterEquip(pchar, SUIT_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "suit_2");
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "gate_back", "");
			pchar.questTemp.AnjelikaTichPrologue4 = "ATP4";
			LocatorReloadEnterDisable("SantoDomingo_town", "Reload3_back", false);
			chrDisableReloadToLocation = false;
			
			sld = CharacterFromID("SantoDomingo_Mayor")
			sld.Dialog.Filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "ATpr_SD_Gubernator_20";
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "SantoDomingo_townhall", "sit", "sit1");
		break;
		
		case "ATpr_SD_Gubernator_20":
			dialog.text = "Here you are. I have already been informed about the successfully repulsed attack. I don't have much time, so let's get right to the point.";
			link.l1 = "Of course. I dare to hope...";
			link.l1.go = "ATpr_SD_Gubernator_21";
		break;
		
		case "ATpr_SD_Gubernator_21":
			dialog.text = "...For some reward for your courage and your duty to the crown. So, your performance has been rated at 15,000 piastres. That's only half of what you're getting right now. I was also informed that the ship on which the refugees arrived belonged to one José Carpio, and from that day on is under your command. Right?";
			link.l1 = "It seems like that's the case. I was chosen as captain by a general vote of the team members.";
			link.l1.go = "ATpr_SD_Gubernator_22";
		break;
		
		case "ATpr_SD_Gubernator_22":
			AddMoneyToCharacter(pchar, 30000);
			GiveItem2Character(PChar, "ATpr_pismo");
			dialog.text = "Amazing. However, that is why the second part of the funds is also given to you personally. Use them to restore the ship in order, complete the crew and go to Havana, report to his Grace Francisco Oregon-i-Gascon - Governor-General of the Spanish colonies of the Caribbean archipelago about what happened. No one can do this better than the direct participants in the events, and on my behalf give this report. The rest of the funds will be your reward.";
			link.l1 = "What fate awaits La Vega? Are there plans to regain control of the settlement?";
			link.l1.go = "ATpr_SD_Gubernator_23";
		break;
		
		case "ATpr_SD_Gubernator_23":
			dialog.text = "You will have the opportunity to ask this question personally to His Excellency. I have no right to make such large-scale decisions.";
			link.l1 = "In that case, I also have a personal interest in getting to Havana as soon as possible.";
			link.l1.go = "ATpr_SD_Gubernator_24";
		break;
		
		case "ATpr_SD_Gubernator_24":
			dialog.text = "It's good to hear. I'm not detaining you anymore.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("ATpr_VosstanovimGorod");
		break;
		
		case "Pirat_Guber":
			dialog.text = "Did you have the courage, woman, to appear here, or was it stupidity that did not allow you to see the changes around you?";
			link.l1 = "My name is Angelica Teach, and I'm here precisely because there have been some changes around.";
			link.l1.go = "Pirat_Guber_2";
		break;
		
		case "Pirat_Guber_2":
			dialog.text = "Is that so? Explain it.";
			link.l1 = "Luckily, I was in Santo Domingo when your men made a failed attempt to enter. Rumors have spread throughout the city that Spain has put a bounty on two young ladies, the daughters of the commandant of this fort, and I have every intention of getting them.";
			link.l1.go = "Pirat_Guber_3";
		break;
		
		case "Pirat_Guber_3":
			dialog.text = "Do you think if I had them, I would give them away?";
			link.l1 = "I think you need a mediator in the negotiations. Spaniards won't let you get within cannon shot of any of their settlements.";
			link.l1.go = "Pirat_Guber_4";
		break;
		
		case "Pirat_Guber_4":
			dialog.text = "They have no reason to do this. It wasn't my people who attacked the colony. I just took advantage of the moment and occupied the abandoned fortification. An advantageous place, I note, it would be foolish to neglect it. English and French caravans are constantly scurrying around here, and in good weather you can even see the shores of Tortuga.";
			link.l1 = "Also, what about the sisters?";
			link.l1.go = "Pirat_Guber_5";
		break;
		
		case "Pirat_Guber_5":
			dialog.text = "You can take your guys and scour the island, but I'm willing to bet that if they're alive, they'll come on their own. Or you can hand out shovels and give the order to check the burial ground outside the city. You won't find them with me.";
			link.l1 = "No one would have set a reward for the dead.";
			link.l1.go = "Pirat_Guber_6";
		break;
		
		case "Pirat_Guber_6":
			dialog.text = "So I can't help you with anything.";
			link.l1 = "I'll come back here on occasion.";
			link.l1.go = "Pirat_Guber_7";
		break;
		
		case "Pirat_Guber_7":
			DialogExit();
			
			AddQuestRecord("AT_Mechty_Sbivautsya", "5");
			sld = CharacterFromID("Edward Mansfield")
			sld.Dialog.Filename = "Mayor/EdwardMansfield.c";
			sld.dialog.currentnode = "First Time";
		break;
		
		case "Ispa_Guber":
			dialog.text = "";
			link.l1 = "I have arrived on behalf of the Senor Governor of Santo Domingo with a report on recent events in Hispaniola.";
			link.l1.go = "Ispa_Guber_2";
			TakeItemFromCharacter(pchar, "ATpr_pismo");
		break;
		
		case "Ispa_Guber_2":
			sld = CharacterFromID("SantoDomingo_Mayor")
			dialog.text = "I already have information about what happened. Rumors fly faster than the wind in these parts, you know, but of course I'll read the official report. Accept this as payment for timely delivery.";
			link.l1 = "Senor "+GetFullName(sld)+" has already given me a reward in advance.";
			link.l1.go = "Ispa_Guber_3";
			AddMoneyToCharacter(pchar, 5000);
		break;
		
		case "Ispa_Guber_3":
			dialog.text = "Consider this to cover additional costs.";
			link.l1 = "I won't mind, I'm in a difficult position right now. In this regard, I have a question, not so much of a state, but of a personal nature. What fate awaits the colony lost by Spain? It has been my home for a long time.";
			link.l1.go = "Ispa_Guber_5";
		break;
		
		case "Ispa_Guber_5":
			dialog.text = "We cannot make hasty decisions on this issue. But I can tell you for sure that Spain will not just leave the bloody robbery that the pirates committed. Sooner or later, the Spanish flag will be raised again in La Vega and justice will prevail! Now I'm going to ask you to leave me, I have to work.";
			link.l1 = "Thank you, Your Excellency!";
			link.l1.go = "Ispa_Guber_6";
		break;
		
		case "Ispa_Guber_6":
			DialogExit();
			
			AddQuestRecord("AT_Mechty_Sbivautsya", "6");
			CloseQuestHeader("AT_Mechty_Sbivautsya");
			sld = CharacterFromID("spa_guber")
			sld.Dialog.Filename = "Common_Governor.c";
			sld.dialog.currentnode = "First Time";
		break;
	}
}
