
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iTermsValidity;

	int iNation;
	int LicenceValidity;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sTemp;

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "exit_over":
			npchar.lifeDay = 0;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "SCQ_exit":
			npchar.lifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			UnmarkCharacter(npchar);
			DialogExit();
		break;
		case "good_all":
			dialog.text = NPCStringReactionRepeat("Glad" + NPCharSexPhrase(npchar, "", "a") + " to see you again. Is there anything else you wanted?",
				"Oh, you again? We've already had a conversation today. Has something changed?",
				"Hmm, can you stop bothering me with nothing to do?!",
                "Brrr, your face is already making me sick...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("No, nothing like that...",
				"No, it's fine.",
                "Yes, of course, I'm sorry...",
				"Hmm, well, you're wrong, I have a good face. I'm proud of her!", npchar, Dialog.CurrentNode);
			link.l1.go = "Exit";
			NextDiag.TempNode = "good_all";
		break;
		case "All_disagree":
			npchar.lifeDay = 0;
			NextDiag.TempNode = "All_bye";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "All_bye":
			dialog.text = "I don't want to talk to you, goodbye.";
			link.l1 = "Heh, well, don't.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "All_bye";
		break;
		//================================== в Порт оф Спейне ======================================
		case "PortSpein":
			NextDiag.TempNode = "PortSpein";
			dialog.text = "Hello, Captain. Don't you want to talk about something that no doubt interests you?";
			link.l1 = "No, I don't want to.";
			link.l1.go = "exit_over";
			link.l2 = "How do you know what might interest me?";
			link.l2.go = "PortSpein_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "PortSpein_1":
			dialog.text = "Rumors, " +  GetAddress_Form(NPChar) + "The earth is full of them...";
			link.l1 = "Heh, come on, let's talk.";
			if (GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(pchar, "map_part1") == 0 && GetCharacterItem(pchar, "map_part2") == 0)
			{
				link.l1.go = "PortSpein_2";
			}
			else
			{
				link.l1.go = "PortSpein_2_pistol";
			}
		break;
		case "PortSpein_2":
			dialog.text = "I think you will be interested in one... a thing, so to speak.";
			link.l1 = "Undoubtedly.";
			link.l1.go = "PortSpein_3";
		break;

		case "PortSpein_2_pistol":
			dialog.text = "I think you will be interested in information about the location of a very necessary thing.";
			link.l1 = "Undoubtedly.";
			link.l1.go = "PortSpein_3_pistol";
		break;

		case "PortSpein_3":
			dialog.text = "Very good. But I have to be sure that this thing will get to the one who will be able to use it correctly - I promised this to one person. Therefore, I suggest you answer one question so that I can understand if you really are the one who I need. Do you agree?";
			link.l1 = "Heh... Well, I agree.";
			link.l1.go = "PortSpein_4";
			link.l2 = "Look for someone else and be sure of him. I'll pass.";
			link.l2.go = "All_disagree";
		break;

		case "PortSpein_3_pistol":
			dialog.text = "Very good. But I have to be sure that this thing will get to the one who will be able to use it correctly - I promised this to one person. Therefore, I suggest you answer one question so that I can understand if you really are the one who I need. Do you agree?";
			link.l1 = "Heh... Well, I agree.";
			link.l1.go = "PortSpein_4";
			link.l2 = "Look for someone else and be sure of him. I'll pass.";
			link.l2.go = "All_disagree";
		break;

		case "PortSpein_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "In that case, listen to the question. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortSpein_check";
		break;
		case "PortSpein_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Correct answer! You really are "+ GetSexPhrase("knowledgeable cap", "good at seamanship, girl") +".";
				link.l1 = "Heh, of course! Tell me what you have there.";
				if (GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(pchar, "map_part1") == 0 && GetCharacterItem(pchar, "map_part2") == 0)
				{
					link.l1.go = "PortSpein_ok";
				}
				else
				{
					link.l1.go = "PortSpein_ok_pistol";
				}
			}
			else
			{
				dialog.text = "The answer is incorrect. Maybe you'll think about it and tell me the right answer?";
				link.l1 = "Yes, I'll try again.";
				link.l1.go = "PortSpein_5";
				link.l2 = "No, I do not know the answer to this question.";
				link.l2.go = "PortSpein_6";
			}
		break;
		case "PortSpein_ok":
			dialog.text = "This is an old treasure map. They are said to have been hidden by Sir Walter Riley himself. I am giving it to you, according to the vow I made - to pass it from hand to hand to an experienced sailor. Good luck in your search!";
			link.l1 = "Well, I got you. We will look for it!";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
			GiveItem2Character(pchar, "map_full");
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "1");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
			CloseQuestHeader("QuestionsMessages");
		break;

		case "PortSpein_ok_pistol":
			dialog.text = "This is a great matchlock musket! But I don't have it, I just know where to get it. In the pirate settlement of La Vega, you need to go behind the house to the left of the gate - there is this weapon hidden in the ground. Good luck!";
			link.l1 = "Well, I got you. We will look for it!";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.LaVega_town = true;
			pchar.GenQuestRandItem.LaVega_town.randitem4 = "mushket";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "1_1");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
			CloseQuestHeader("QuestionsMessages");
		break;

		case "PortSpein_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Very good! Then I will repeat my question. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortSpein_check";
		break;
		case "PortSpein_6":
			dialog.text = "It's a pity, but in this case I can't give you what is meant for a good cap.But I am ready to listen to your answer at another time, if you can catch me. I'll be in town for a little more than a week.";
			link.l1 = "Well, if I find out the answer, I'll try again.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortSpein_again";
		break;
		case "PortSpein_again":
			dialog.text = "Ah, here you are again. Did you find out the answer?";
			link.l1 = "I think I found out.";
			link.l1.go = "PortSpein_5";
		break;
		//================================== Виллемстад: Найти пропавшего торговца ======================================
		case "Villemstad":
			NextDiag.TempNode = "Villemstad";
			dialog.text = "Hello, Captain. I wanted to ask you a favor.";
			link.l1 = RandPhraseSimple("What's the matter with you, " + GetAddress_FormToNPC(NPChar) + "?", "State the essence of the problem, " + GetAddress_FormToNPC(NPChar) + ". I will try to help you.");
			link.l1.go = "SCQ_Hasband";
			link.l2 = RandPhraseSimple("I'm busy, beauty, not today!", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + ", but I don't have time at the moment...");
			link.l2.go = "exit";
		break;
		case "SCQ_Hasband":
			dialog.text = "My husband is engaged in commerce - delivers goods to merchants all over the district. So, he went to sea more than three months ago, and still hasn't returned!";
			link.l1 = "Do you think something happened to him?";
			link.l1.go = "SCQ_Hasband_0";
		break;
		case "SCQ_Hasband_0":
			dialog.text = "I don't know, but I really hope he's just busy with work. Although he could have sent a message, he knows that I'm worried!";
			link.l1 = "The sea is restless now, anything can happen...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			dialog.text = "Here! You know what I'm talking about. By the look of you "+ GetSexPhrase("brave captain", "brave girl") +", that's why I wanted to ask you to find my husband. I'm willing to pay you 5,000 piastres and give you my jewels.";
			link.l1 = "Okay. If I meet your husband at sea or anywhere else, I will inform him of your concern. And tell me, what is your husband's name and what kind of ship does he have?";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "I'm not interested in such money. Unfortunately, I have to refuse...";
			link.l2.go = "exit";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "His name is Maurits Groen. And he works at a joint with the name 'Louise'. His ship was last seen south of the Main.";
			link.l1 = "Understood. Well, now wait. And try to stay mostly in the church so that I don't look for you in the city...";
			link.l1.go = "exit";
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			SetQuestHeader("SCQ_womanHasband");
			AddQuestRecord("SCQ_womanHasband", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("QuetionsVillemstad_MuzhTorgovets", "GrunMaurits", "man", "man", sti(PChar.rank), HOLLAND, -1, true));
			FantomMakeCoolSailor(sld, SHIP_SHNYAVA, "Louise", CANNON_TYPE_CULVERINE_LBS12, 30, 30, 30);
			sld.name = "Maurits";
			sld.lastname = "Groen";
			sld.dialog.filename   = "Quest\Questions.c";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			sld.Ship.Mode = "trade";
			Group_FindOrCreateGroup("QuetionsVillemstad_MuzhTorgovets_Ship");
			Group_SetType("QuetionsVillemstad_MuzhTorgovets_Ship", "pirate");
			Group_AddCharacter("QuetionsVillemstad_MuzhTorgovets_Ship", "QuetionsVillemstad_MuzhTorgovets");
			Group_SetGroupCommander("QuetionsVillemstad_MuzhTorgovets_Ship", "QuetionsVillemstad_MuzhTorgovets");
			int RandomLuiza;
			RandomLuiza = rand(2);
			if (RandomLuiza == 0)
			{ 
				Group_SetAddress("QuetionsVillemstad_MuzhTorgovets_Ship", "Maracaibo", "quest_ships", "Quest_ship_6");
			break;
			}
			if (RandomLuiza == 1)
			{ 
				Group_SetAddress("QuetionsVillemstad_MuzhTorgovets_Ship", "Caracas", "quest_ships", "Quest_ship_5");
			break;
			}
			if (RandomLuiza == 2)
			{ 
				Group_SetAddress("QuetionsVillemstad_MuzhTorgovets_Ship", "Cumana", "quest_ships", "Quest_ship_5");
			break;
			}
		break;
		case "HasbandCap_inDeck":
			dialog.text = "Hello. To what do I owe the honor of seeing you on my ship?";
			link.l1 = "Your name is Maurits Green, isn't it?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "Yes, it's me.";
			link.l1 = "This sounds silly, of course, but your wife asked me to tell you that she is very worried about you.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "Ugh, damn it! And to be honest, I was scared - I thought it was the famous prize hunter - One-eyed Steed Hunter followed me. Well, it's good that I made a mistake. You know, I'm so wrapped up with work that I'm not up to it right now. Lucrative offers follow one after another, I can't miss out on a possible benefit just because my wife is worried.";			
			link.l1 = "That's for sure, but you could at least text her that you're okay.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "Yes, you are right. I will definitely do it at the first port on unloading... Thank you so much for participating in our family affairs!";
			link.l1 = "You're welcome, buddy. I'll go then.";
			link.l1.go = "HasbandCap_inDeck_4";			
		break;
		case "HasbandCap_inDeck_4":
			dialog.text = "Wait, I want to share one thing with you. The fact is that my wife and I lived in Puerto Principe for a while, but then we had to move to Willemstad. And I'll tell you, it was one of the best decisions. I will never set foot in this hole again!";
			link.l1 = "Continue...";
			link.l1.go = "HasbandCap_inDeck_5";			
		break;
		case "HasbandCap_inDeck_5":
			dialog.text = "Well, I still have some things there, and one of them should certainly be useful"+ GetSexPhrase("such a captain", "such a brave girl captain") +"like you.";
			link.l1 = "What kind of thing is there that I will need?";
			link.l1.go = "HasbandCap_inDeck_6";			
		break;
		case "HasbandCap_inDeck_6":
			dialog.text = "It's not a bad spyglass. It is buried in the ground under the window of our former house in Puerto Principe, to the left of the tavern.";
			link.l1 = "Understood. Well, thank you and goodbye.";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			npchar.dialog.filename   = "Quest\Questions.c";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			AddQuestRecord("SCQ_womanHasband", "2");
			sld = characterFromId("QuetionsVillemstad");
			sld.dialog.filename = "Quest\Questions.c";
			sld.dialog.currentnode = "womanHasbandover";
			pchar.GenQuestRandItem.PuertoPrincipe_town = true;
			pchar.GenQuestRandItem.PuertoPrincipe_town.randitem1 = "spyglass3";
			PChar.quest.SCQ_Hasband_Truba.win_condition.l1 = "locator";
			PChar.quest.SCQ_Hasband_Truba.win_condition.l1.location = "PuertoPrincipe_town";
			PChar.quest.SCQ_Hasband_Truba.win_condition.l1.locator_group = "randitem";
			PChar.quest.SCQ_Hasband_Truba.win_condition.l1.locator = "randitem1";
			PChar.quest.SCQ_Hasband_Truba.win_condition = "SCQ_Hasband_Truba";
			DeleteAttribute(pchar, "questTemp.SCQ_Hasband_Luiza");
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "Once again, accept my thanks...";
			link.l1 = "It's not worth it, it's okay.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		
		//================================== Порт-о-Принс: Вызволение из плена мужа горожанки ======================================
		case "PortPax":
			NextDiag.TempNode = "PortPax";
			dialog.text = "Captain, help me, I beg you! My husband got caught by pirates! Can you save him?";		
			link.l1 = "Wait, I don't really understand who got to whom...");
			link.l1.go = "SCQ_Pirates";
			DeleteAttribute(npchar, "talker");
		break;
		case "SCQ_Pirates":
			dialog.text = "I'll explain it to you now. The fact is, my husband, a completely ordinary man, was captured by pirates! They killed everyone, spared no one...";
			link.l1 = "So captain dared to resist. If they had surrendered, no one would have been harmed.";
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
			dialog.text = "You're a pirate too, aren't you? Yes, yes, I know... I beg you, help us, save my husband! In the letter, he described the pirate ship and named captain. It will be easy enough for you to find him!";
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
			dialog.text = "A little, 5,000 piastres and all my jewels... but I will pray for your soul for the rest of my life!";
			link.l1 = "Yeah, really a little bit... Oh well, I'm ready to help you on occasion.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "I'm sorry, but it's too little for me to attack to his colleague, a member of the Brethren.";
			link.l2.go = "exit";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "Thank you, thank you!!";
			link.l1 = "If everything works out, then you will thank me, but for now it's not worth it. Tell me your husband's name and everything you know about these pirates.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			dialog.text = "My husband's name is Vincent Labbe. The pirate captain's name is Corey Ball, he trades on a schooner named Colossus. He was last seen near the uninhabited Turks Island.";
			link.l1 = "Clear. Well, now expect and hope that I will be able to catch him. Try to be in the church so that I can find you there.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			SetQuestHeader("SCQ_womanPirates");
			AddQuestRecord("SCQ_womanPirates", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortPax_KoriBoll", "officer_17", "man", "man", sti(PChar.rank), PIRATE, -1, true));
			FantomMakeCoolSailor(sld, SHIP_SCHOONERWAR, "Colossus", CANNON_TYPE_CULVERINE_LBS12, 30, 30, 30);
			sld.name = "Cory";
			sld.lastname = "Ball";
			sld.dialog.filename   = "Quest\Questions.c";
			sld.dialog.currentnode = "PiratesCap_Board";
			sld.AlwaysEnemy = true;
			sld.DontRansackCaptain = true;
			Group_FindOrCreateGroup("QuetionsPortPax_KoriBoll_Ship");
			Group_SetType("QuetionsPortPax_KoriBoll_Ship", "pirate");
			Group_AddCharacter("QuetionsPortPax_KoriBoll_Ship", "QuetionsPortPax_KoriBoll");
			Group_SetGroupCommander("QuetionsPortPax_KoriBoll_Ship", "QuetionsPortPax_KoriBoll");
			Group_SetAddress("QuetionsPortPax_KoriBoll_Ship", "Terks", "quest_ships", "Quest_ship_3");
			
			PChar.quest.SCQ_womanPirates_Potunul.win_condition.l1 = "Character_sink";
			PChar.quest.SCQ_womanPirates_Potunul.win_condition.l1.character = "QuetionsPortPax_KoriBoll";
			PChar.quest.SCQ_womanPirates_Potunul.win_condition = "SCQ_womanPirates_Potunul";
			PChar.quest.SCQ_womanPirates_Nashli.win_condition.l1 = "location";
			PChar.quest.SCQ_womanPirates_Nashli.win_condition.l1.location = "Terks";
			PChar.quest.SCQ_womanPirates_Nashli.win_condition = "SCQ_womanPirates_Nashli";
		break;
		case "PiratesCap_Board":
			dialog.text = "The devil! What the hell?!!";
			link.l1 = "I need your prisoner, named Vincent Labbe.";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "Ha! Well, no, only over my dead body...";
			link.l1 = "As you wish.";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("SCQ_womanPirates_afterCabinFight");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "womanPirates_Board":
			dialog.text = "Who are you?";
			link.l1 = "I am captain " + GetFullName(pchar) + ". Don't worry, I'm here to pick you up in order to take you to your wife.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "Damn it, isn't this a dream?!";
			link.l1 = "I assure you, this is not a dream... Well, it's done, now let's get out of here.";
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("QuetionsPortPax");
			sld.dialog.filename = "Quest\Questions.c";
			sld.dialog.currentnode = "womanPiratesover";
			AddQuestRecord("SCQ_womanPirates", "4");
		break;
		//================================== Сан-Хуан ======================================
		case "SanJuan":
			NextDiag.TempNode = "SanJuan";
			dialog.text = "Greetings, Captain. I want to offer you something.";
			link.l1 = "No, I'm not interested in that.";
			link.l1.go = "exit_over";
			link.l2 = "I'm listening to you carefully, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l2.go = "SanJuan_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "SanJuan_1":
			dialog.text = "I have one very necessary thing for captains, which, no doubt, will interest you.";
			link.l1 = "I am listening to you even more attentively. What is this thing?";
			link.l1.go = "SanJuan_2";
		break;
		case "SanJuan_2":
			dialog.text = "The document, I would say, came to me on occasion and under certain conditions. I have to hand it over to captain as soon as possible, who really needs it and deserves it.";
			link.l1 = "Is that so? Well, what is this mysterious document?";
			link.l1.go = "SanJuan_3";
		break;
		case "SanJuan_3":
			dialog.text = "I can only tell you this after you answer me one question.";
			link.l1 = "What's the other question?";
			link.l1.go = "SanJuan_4";
		break;
		case "SanJuan_4":
			dialog.text = "A question on general topics for caps. I have to be clear about who I'm dealing with.";
			link.l1 = "Well, ask your question on general topics.";
			link.l1.go = "SanJuan_5";
			link.l2 = "I don't want to answer any stupid questions.";
			link.l2.go = "All_disagree";
		break;
		case "SanJuan_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Very good. So, Captain, here's my question. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "SanJuan_check";
		break;
		case "SanJuan_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Great, "+ GetSexPhrase("captain", "girl") +"! That's exactly right!";
				link.l1 = "Well!.. So what is this mysterious document?";
				link.l1.go = "SanJuan_ok";
			}
			else
			{
				dialog.text = "No, "+ GetSexPhrase("captain", "girl") +", the answer is incorrect. I suggest you give the right answer after all.";
				link.l1 = "Repeat...";
				link.l1.go = "SanJuan_6";
				link.l2 = "No, I've had enough questions.";
				link.l2.go = "SanJuan_7";
			}
		break;
		case "SanJuan_ok":
			iNation = 5;
			LicenceValidity = 20;
			for (int i=0; i<4 ; i++)
			{
				if (GetRelation2BaseNation(i) == RELATION_ENEMY)
				{
					iNation = i;
					break;
				}
			}
			if (iNation == 5) //если со всеми в мире, то генерим лицензию случайной нации сроком 20 дней
			{
				iNation = rand(3);
			}
			GiveNationLicence(iNation, LicenceValidity + GetDaysContinueNationLicence(iNation));//фикс - продляю лицензию на весь срок, а не по сложным округлениям

			dialog.text = "This " + GetRusNameNationLicence(iNation) + " for a period of " + LicenceValidity + " days! I am pleased to present it to you.";
			link.l1 = "Wow, a pretty expensive document! Well, thank you, " + GetAddress_FormToNPC(NPChar) + ", for the service rendered. Goodbye.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
		break;
		case "SanJuan_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Fine. I consider it my duty to remind you of the question. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "SanJuan_check";
		break;
		case "SanJuan_7":
			dialog.text = "Well, that's enough, that's enough. Goodbye, "+ GetSexPhrase("captain", "girl") +"...";
			link.l1 = "I wish you all the best.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SanJuan_again";
		break;
		case "SanJuan_again":
			dialog.text = "I'm listening to you carefully, Captain. Did you really decide to try again and answer the question you asked?";
			link.l1 = "Yes, I think I know the correct answer.";
			link.l1.go = "SanJuan_6";
		break;
		//================================== Кумана ======================================
		case "Cumana":
			NextDiag.TempNode = "Cumana";
			dialog.text = "Greetings, Captain! I have a little business for you. Would you mind paying attention to me for a minute?";
			link.l1 = "No, I won't.";
			link.l1.go = "exit_over";
			link.l2 = "Yes, no problem, the minute is yours.";
			link.l2.go = "Cumana_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Cumana_1":
			dialog.text = "Very good. I wanted to offer you a small deal. I have a certain item that might interest you.";
			link.l1 = "Tell me what the item is and name the price.";
			link.l1.go = "Cumana_2";
		break;
		case "Cumana_2":
			dialog.text = "I will not take money for it, you will need to answer one question for me. If the answer is correct, the subject is yours.";
			link.l1 = "Very strange. Don't you need the money?";
			link.l1.go = "Cumana_3";
		break;
		case "Cumana_3":
			dialog.text = "Heh, everyone needs money, but in this deal, everything is decided by your knowledge. I don't want to explain the reasons for my behavior any further, just say yes or no.";
			link.l1 = "Hmm, I guess so. It became interesting.";
			link.l1.go = "Cumana_4";
			link.l2 = "No, no, and no again. Goodbye.";
			link.l2.go = "All_disagree";
		break;
		case "Cumana_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Heh, you've already answered one question correctly. And now the main event of the day! Listen to the question. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Cumana_check";
		break;
		case "Cumana_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Great! That's the right answer!";
				link.l1 = "It's clear... So what's this thing I'm now the happy owner of?";
				link.l1.go = "Cumana_ok";
			}
			else
			{
				dialog.text = "Very sorry, "+ GetSexPhrase("captain", "girl") +". I'm really sorry... The answer is wrong! Will you try again?";
				link.l1 = "I'll try!";
				link.l1.go = "Cumana_6";
				link.l2 = "No, perhaps...";
				link.l2.go = "Cumana_7";
			}
		break;
		case "Cumana_ok":
			dialog.text = "This is a statue that gives an extraordinary opportunity to better repair the ship. It is hidden in a bay near Porto Bello. This bay is called Chiriki Lagoon. Carefully inspect everything there, and do not be afraid to soak your feet. Good luck, Captain!";
			link.l1 = "You know, this is a really useful thing for cap. Thank you.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Shore46 = true;
			pchar.GenQuestRandItem.Shore46.randitem1 = "STATUE1";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "4");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
			CloseQuestHeader("QuestionsMessages");
		break;
		case "Cumana_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Well, then I remind you of the question! " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Cumana_check";
		break;
		case "Cumana_7":
			dialog.text = "Well, if you don't want to, whatever you want. Goodbye, Captain Dunno...";
			link.l1 = "What?";
			link.l1.go = "exit";
			NextDiag.TempNode = "Cumana_again";
		break;
		case "Cumana_again":
			dialog.text = "And what do you need from me?";
			link.l1 = "I want to try to answer your riddle again.";
			link.l1.go = "Cumana_6";
		break;
		//================================== Порт Рояль ======================================
		case "PortRoyal":
			NextDiag.TempNode = "PortRoyal";
			dialog.text = "Good afternoon, Captain. Listen, it seems to me that you are exactly the one who I need...";
			link.l1 = "But I don't think so.";
			link.l1.go = "exit_over";
			link.l2 = "What's the matter, " + GetAddress_FormToNPC(NPChar) + "?";
			link.l2.go = "PortRoyal_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "PortRoyal_1":
			dialog.text = "I want to offer you an exchange. The fact is that I have something that I don't need at all, but you will certainly need it.";
			link.l1 = "And what do you want in return?";
			link.l1.go = "PortRoyal_2";
		break;
		case "PortRoyal_2":
			dialog.text = "Nothing special. I want to know that this thing is in safe hands.";
			link.l1 = "Well, know that she will be in really good hands. You can be sure of that.";
			link.l1.go = "PortRoyal_3";
		break;
		case "PortRoyal_3":
			dialog.text = "I believe it willingly, but I'll check it anyway. Answer one of my questions and the thing is yours.";
			link.l1 = "Ask your question, there's nothing easier!";
			link.l1.go = "PortRoyal_4";
			link.l2 = "I'll manage somehow...";
			link.l2.go = "All_disagree";
		break;
		case "PortRoyal_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Well, the question is quite simple. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortRoyal_check";
		break;
		case "PortRoyal_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "I didn't even doubt that you would answer correctly.";
				link.l1 = "Of course, it couldn't be any other way. So, well, what's the thing that's already mine?";
				link.l1.go = "PortRoyal_ok";
			}
			else
			{
				dialog.text = "The answer is incorrect, "+ GetSexPhrase("captain", "girl") +". I need the right answer. Will you try again?";
				link.l1 = "Yes, I'll try again!";
				link.l1.go = "PortRoyal_6";
				link.l2 = "No, I don't want to play guessing games.";
				link.l2.go = "PortRoyal_7";
			}
		break;
		case "PortRoyal_ok":
			dialog.text = "This is a guards cuirass. You can find her in Jamaica in Portland Bay.";
			link.l1 = "Yes, this is a necessary thing in battle, "+ GetSexPhrase("and the girl certainly doesn't need it", "it will definitely come in handy for me") +". Thank you.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Shore36 = true;
			pchar.GenQuestRandItem.Shore36.randitem2 = "cirass3";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "5");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
			CloseQuestHeader("QuestionsMessages");
		break;
		case "PortRoyal_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Okay. I suppose I should remind you of the question. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortRoyal_check";
		break;
		case "PortRoyal_7":
			dialog.text = "If you don't want to, as you know. Hmm, but it looks like "+ GetSexPhrase("such a solid captain", "such a fighting girl") +"...";
			link.l1 = "What do you mean by that?";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_again";
		break;
		case "PortRoyal_again":
			dialog.text = "I didn't understand! What else do you need?";
			link.l1 = "I want to try to answer your riddle again.";
			link.l1.go = "PortRoyal_6";
		break;
		//================================== Сантьяго ======================================
		case "Santiago":
			NextDiag.TempNode = "Santiago";
			dialog.text = "Welcome to Santiago, Captain! I wanted to talk to you about a little matter. Do you mind?";
			link.l1 = "I don't want to talk.";
			link.l1.go = "exit_over";
			link.l2 = "Not at all. I am at your service.";
			link.l2.go = "Santiago_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Santiago_1":
			dialog.text = "Great! Then let's get started. The above-mentioned business essentially involves a deal, or an exchange, if you want...";
			link.l1 = "I want, I want an exchange! Let's change.";
			link.l1.go = "Santiago_2";
		break;
		case "Santiago_2":
			dialog.text = "K-heh, well, come on. So, I can offer you one, no doubt, the item you need. In return, I don't need anything from you, I just want to get an answer to one question I've asked.";
			link.l1 = "And what is this question?";
			link.l1.go = "Santiago_3";
		break;
		case "Santiago_3":
			dialog.text = "Of a general nature, according to your specifics. You see, I just want to check the level of your knowledge. This is a necessary condition. Do you agree?";
			link.l1 = "Hmm, although I don't understand why you need this, nevertheless, I agree.";
			link.l1.go = "Santiago_4";
			link.l2 = "Heh, the checker has found out! Get out of here before it's too late...";
			link.l2.go = "All_disagree";
		break;
		case "Santiago_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Wonderful! So, please listen to my question. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Santiago_check";
		break;
		case "Santiago_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Great, that's the right answer! Congratulations.";
				link.l1 = "Thanks for the congratulations, I am very pleased. And to make it doubly pleasant for me, let me listen a little bit about the subject of our deal...";
				link.l1.go = "Santiago_ok";
			}
			else
			{
				dialog.text = "Hmm, "+ GetSexPhrase("captain", "girl") +", this answer cannot suit me. He's wrong! Please try again...";
				link.l1 = "Of course I'll try.";
				link.l1.go = "Santiago_6";
				link.l2 = "No, I will refuse. I'm tired of it.";
				link.l2.go = "Santiago_7";
			}
		break;
		case "Santiago_ok":
			sTemp = GetConvertStr("itmname_pistol6", "ItemsDescribe.txt");
			dialog.text = "This is " + sTemp + "! You can find it in a grotto in Cuba, to get there, you need to go outside the city and walk through the jungle. But you must agree that such a weapon is a thing that you need to an extreme extent.";
			link.l1 = "Yeah, you can't argue with that. Well, we'll have to take a walk. Thank you and have a nice day.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Cuba_Grot = true;
			pchar.GenQuestRandItem.Cuba_Grot.randitem1 = "pistol6";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "6");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
			AddQuestUserData("QuestionsMessages", "sBladeName", sTemp);
			CloseQuestHeader("QuestionsMessages");
		break;
		case "Santiago_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Great! In that case, I'll remind you of it " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Santiago_check";
		break;
		case "Santiago_7":
			dialog.text = "Are you refusing? Are you tired of it?! Hmm, but the point of the question is your profession! However, I don't care about that, goodbye...";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Santiago_again";
		break;
		case "Santiago_again":
			dialog.text = "How can I help you?";
			link.l1 = "I want to answer your question.";
			link.l1.go = "Santiago_6";
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "Oh, Captain, I'm so glad to see you! Tell me quickly, what have you learned about my case?";
			link.l1 = "Hmm, remind me, " + GetAddress_FormToNPC(NPChar) + ", what kind of case are we talking about?";
			link.l1.go = "SCQ_womanResult_exit";
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "Have you forgotten that you promised me you'd find my husband? His name is Maurits Groen!";
					link.l1 = "Oh, yes, of course... I haven't forgotten anything, I just haven't managed to find him yet.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "I didn't understand something! You forgot that you have to send my abuser, a captain named " + npchar.quest.SeekCap.capName + "?!";
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
		case "womanHasbandover":
			dialog.text = "Ah, Captain, I received a letter from my husband! In it, he writes that you have found him.";
			link.l1 = "Yes, that's right, " + GetAddress_FormToNPC(NPChar) + ". Your husband, Maurits Groen, is alive and well. He just worked hard, so to speak...";
			link.l1.go = "SCQR_womanHasband";
		break;
		case "womanRevengeover":
			dialog.text = "What do you say, Captain? Did you do what I asked you to do? Captain " + npchar.quest.SeekCap.capName + "dead?";
			link.l1 = "Yes, he's dead, " + GetAddress_FormToNPC(NPChar) + ". Before he died, he found out who caused his death. The last thing he heard in this life was your name.";
			link.l1.go = "SCQR_womanRevenge";
		break;
		case "womanPiratesover":
			dialog.text = "You have freed my husband after all! I beg you, tell me, is that so?!!";
			link.l1 = "Yes, he is on my ship now. You can take him away if Vincent Labbe is your husband...";
			link.l1.go = "SCQR_womanPirates";
		break;

		case "SCQR_womanHasband":
			dialog.text = "My God, how grateful I am! By the way, here are your 5000 piastres and 10 emeralds. And thank you again!";
			link.l1 = "Hmm, you're welcome...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(PChar, "jewelry4", 10);
			pchar.questTemp.womanHasband_Nagrada = true;
			if (CheckAttribute(pchar, "questTemp.womanHasband_Nagrada") && CheckAttribute(pchar, "questTemp.womanHasband_Truba"))
			{
				CloseQuestHeader("SCQ_womanHasband");
				pchar.questdata.NaitiTorgovtsa = 1;
				DeleteAttribute(pchar, "questTemp.womanHasband_Nagrada");
				DeleteAttribute(pchar, "questTemp.womanHasband_Truba");
			}
		break;
		case "SCQR_womanPirates":
			dialog.text = "Of course it's him!!! God, Captain, I'm so grateful to you! I will pray for you every day as long as I live!";
			link.l1 = "It's nice, pray...";
			link.l1.go = "SCQR_womanPirates_2";
		break;		
		case "SCQR_womanPirates_2":
			dialog.text = "Here are your promised 5000 piastres and 10 sapphires. But that's not all. The point is, I know of one hidden item that would be useful to you.";
			link.l1 = "And what is this thing?";
			link.l1.go = "SCQR_womanPirates_3";
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(PChar, "jewelry1", 10);
		break;
		case "SCQR_womanPirates_3":
			dialog.text = "This is a magnificent costume, the latest in European fashion! It is hidden in a dungeon under the Tortuga, in one of the dead ends. You'll have to look for it.";
			link.l1 = "Let's look for it. A presentable appearance is very important for a captain. Thank you.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("QuetionsPortPax_MuzhPassajir");
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddQuestRecord("SCQ_womanPirates", "5");
			AddQuestUserData("SCQ_womanPirates", "sSex", GetSexPhrase("xia", "as"));
			
			pchar.GenQuestRandItem.Tortuga_Cave = true;
			pchar.GenQuestRandItem.Tortuga_Cave.randitem1 = "suit_2";
			PChar.quest.SCQ_Pirates_Kostum.win_condition.l1 = "locator";
			PChar.quest.SCQ_Pirates_Kostum.win_condition.l1.location = "Tortuga_Cave";
			PChar.quest.SCQ_Pirates_Kostum.win_condition.l1.locator_group = "randitem";
			PChar.quest.SCQ_Pirates_Kostum.win_condition.l1.locator = "randitem1";
			PChar.quest.SCQ_Pirates_Kostum.win_condition = "SCQ_Pirates_Kostum";
		break;
	}
}
