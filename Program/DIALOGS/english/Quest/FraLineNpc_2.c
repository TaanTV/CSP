// диалоговый файл №2 на фр. линейку
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	float locx, locy, locz;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = "Nothing to talk about.";
			link.l1 = "Okay...";
            link.l1.go = "exit";

//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
            //Квест №1, сопровождение Леграна.
            if (pchar.questTemp.State == "Fr1Legran_toLeMaren")// квест №1, базар с бандиами
            {
    			dialog.text = "Hey, "+ GetSexPhrase("buddy","girlfriend") +"! We need to talk to your boyfriend. Step aside and don't interfere - you'll be healthier...";
    			link.l1 = "Hmm, I think it's better for you to get out of the way. And take care of your ears!";
    			link.l1.go = "Step_F1_1";
            }
            //Квест №2, доставка письма в Кюрасао.
            if (pchar.questTemp.State == "Fr2Letter_Arrest")// квест №2, базар с охраной при аресте
            {
    			dialog.text = "Hand over your weapons! And don't try to resist!";
    			link.l1 = "Well, have it your way. And only because Curacao is friendly with Tortuga...";
    			link.l1.go = "Step_F2_1";
            }
            if (pchar.questTemp.State == "Fr2Letter_PrisonTalk")// квест №2, базар с тюремщиком
            {
    			dialog.text = "Are you sitting, feeding bedbugs? Tomorrow you will be fed royally, as sentenced to the gallows, and it's already being built, hehe!";
    			link.l1 = "Well, it's unlikely that you'll get anything from this...";
    			link.l1.go = "Step_F2_2";
            }
            if (pchar.questTemp.State == "Fr2Letter_VisitGovernor")// квест №2, базар с фантомом губера в тюрьме
            {
    			dialog.text = "Hello, Captain.";
    			link.l1 = "Monsieur Stuyvesant... By what fates?!";
    			link.l1.go = "Step_F2_8";
            }
            if (pchar.questTemp.State == "Fr2Letter_SeekProblems")// квест №2, базар с кэпом галеона, абордаж
            {
    			dialog.text = ""+ GetSexPhrase("Damn ladron","Damn girl") +"!";
    			link.l1 = "Be quiet, Spanish dog! I'll ask you a few questions. If you answer the truth, you will live.";
    			link.l1.go = "Step_F2_12";
            }
			if (npchar.id == "AnnaDeLeiva")// квест №3, донна Анна в спальне
            {
    			dialog.text = "God! What happened? Did you come from Bertrand? What was that noise?";
    			link.l1 = "Madam, I don't know if this is sad news for you or not, but I was forced to kill your spouse. We don't have time to worry and faint, we need to run immediately! Governor-General of Tortuga Bertrand d'Ogeron is waiting for you.";
    			link.l1.go = "Step_F3_1";
            }
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_toHavana")// квест №5, Инесс
            {
    			dialog.text = ""+ GetSexPhrase("Senor","Senorita") +", who are you? And what do you need in my house?";
    			link.l1 = "Senora, I have arrived here on behalf of Donna Anna, your friend. As far as I know, you informed her of some danger...";
    			link.l1.go = "Step_F5_1";
            }
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_SeekHoseBrothers")
            {
    			dialog.text = "Hurry up, "+ GetSexPhrase("senor","senorita") +". I assure you, Donna Anna's life is hanging by a thread...";
    			link.l1 = "Everything will be fine, dear Ines, don't worry.";
    			link.l1.go = "exit";
            }
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_GoodWork")
            {
    			dialog.text = "Well, Captain, what's the news?";
    			link.l1 = "Everything is fine, there are no more problems with Donna Anna's relatives...";
    			link.l1.go = "Step_F5_4";
            }
			if (npchar.id == "Captain_1" || npchar.id == "Captain_2")//квест №6, базар с кэпами
            {
    			dialog.text = ""+ GetSexPhrase("Monsieur","Mademoiselle") +", we need to sail to Cumana. God forbid, we'll be late - and there won't be any real money! You don't know our captain...";
    			link.l1 = "Hmm, who doesn't know Francois Olone? The famous filibuster...";
    			link.l1.go = "exit";
            }
			if (npchar.id == "RockBrasilian" && pchar.questTemp.State == "Fr7RockBras_toSeekPlace")//квест №7, базар с Бразильцем.
            {
    			dialog.text = NPCStringReactionRepeat("Wow! Who dared to do such a thing?!", "Well, let's continue our conversation. So who are you, hero of our time?", "Shall we continue? So who are you?", "Hmm, let's end our conversation. Who are you?", "block", 0, npchar, Dialog.CurrentNode);
    			if (LAi_group_GetTarget(pchar) <= 0)
				{
					link.l1 = HeroStringReactionRepeat("I dared. My name is " + GetFullName(pchar)+". I came to get you out of here.", "Let's continue... My name is " + GetFullName(pchar)+", I follow you.", "My name is "+GetFullName(pchar)+", I'm here for you.", "Let's finish, no question. My name is " + GetFullName(pchar)+", I follow you.", npchar, Dialog.CurrentNode);
    				link.l1.go = "Step_F7_1";
				}
				else
				{
					link.l1 = "Now is not the time to talk, we need to get rid of everyone in this place!";
    				link.l1.go = "Step_F7_Late";
				}
				// --> типа опоздал...
				if (GetQuestPastDayParam("questTemp") > 8)
				{
    				dialog.text = "Who are you...?";
    				link.l1 = "I'm here for you, I was sent by d'Ogeron...";
    				link.l1.go = "Step_F7_8";
				}
				else SaveCurrentQuestDateParam("questTemp"); //чтобы не глюкнуло во время боя
				// <-- типа опоздал...
            }
			if (npchar.id == "RockBrasilian" && pchar.questTemp.State == "empty")//квест №7, базар с Бразильцем в резиденции дОжерона.
            {
    			dialog.text = "Captain, I haven't had a chance to thank you yet.";
    			link.l1 = "It's all right, Captain Rock...";
    			link.l1.go = "Step_F7_5";
            }
			if (npchar.id == "CaptainGay")//квест №8, базар с кэпом Геем.
            {
    			dialog.text = "Who are you?";
    			link.l1 = "It doesn't matter who I am. Greetings from John Morris. He really wants to get to know your logbook.";
    			link.l1.go = "Step_F8_1";
            }
		break;
//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Спасение трёх горожан. Квест №1 **********************************
 		case "Step_F1_1":
			dialog.text = "You asked for it! Say goodbye to life...";
			link.l1 = "Oh, you don't take care of your ears...";
			link.l1.go = "Step_F1_2";
		break;
 		case "Step_F1_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Legran");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Fr1Legran_afterFightBandits");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Арест ГГ у Стэвезанта. Квест №2 **********************************
 		case "Step_F2_1":
			bDisableCharacterMenu = true; //закрываем Ф2
			LAi_SetPlayerType(pchar);
            DoReloadCharacterToLocation("Villemstad_prison",  "goto", "goto9");
			//StoreEquippedMaps(pchar); // ugeen
			pchar.MapsAtlasCount = 0;
			SetTempRemoveParam(pchar, "items");
			pchar.questTemp.money = sti(pchar.money)/2;
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MAPS_ITEM_TYPE);
			pchar.money = 0;
			DeleteAttribute(pchar, "items");
			DoQuestCheckDelay("Fr2Letter_intoPrison_1", 20);
			AddQuestRecord("Fra_Line_2_DelivLetter", "2");
			AddQuestUserData("Fra_Line_2_DelivLetter", "sSex", GetSexPhrase("official envoy","official envoy"));
            DialogExit();
		break;
 		case "Step_F2_2":
			dialog.text = "So, so, what are you talking about?";
			link.l1 = "That you will watch my execution for free. But you'll be a few rounds richer if Stuyvesant searches the captain's cabin on my ship by tomorrow.";
			link.l1.go = "Step_F2_3";
		break;
 		case "Step_F2_3":
			dialog.text = "Why do you need this?";
			link.l1 = "So that he can get acquainted with my papers, ship's log, and so on. Then he will understand that I am really of the Governor-General's of Tortuga messenger.";
			link.l1.go = "Step_F2_4";
		break;
 		case "Step_F2_4":
			dialog.text = "Ah, I see... Well, I can arrange that, one of the officers of Stuyvesant is my father-in-law.";
			link.l1 = "Come on, you won't regret it. Listen, do you know why I was captured? I can't understand anything...";
			link.l1.go = "Step_F2_5";
		break;
 		case "Step_F2_5":
			dialog.text = "Pirates, all of them... And you look like you're a privateer.";
			link.l1 = "So I didn't argue... Okay, listen, don't waste any time, get down to business. Otherwise, I will definitely be hanged for nothing.";
			link.l1.go = "Step_F2_6";
		break;
 		case "Step_F2_6":
			dialog.text = "Okay. I promise you that your ship's papers will get to Stuyvesant. Well, then pray that these papers are convincing\n"+
				          "Well, my father-in-law will take a few rounds from your utensils himself. Do you mind?";
			link.l1 = "Of course not! Well, don't waste your time, my friend.";
			link.l1.go = "Step_F2_7";
		break;
 		case "Step_F2_7":
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10);
            DialogExit();
			DoQuestCheckDelay("Fr2Letter_intoPrison_3", 10);
		break;
 		case "Step_F2_8":
			dialog.text = "Don't be silly, Captain, everything has been clarified\n"+
				          "One of my officers decided to check your cabin. We found a French letter of marque, read the ship's log and everything fell into place\n"+
						  "That's right, you really are a filibuster in the service of France. I'm not apologizing, because that's the order. You are dismissed, Captain.";
			link.l1 = "Very glad. It would be stupid to die for nothing.";
			link.l1.go = "Step_F2_9";
		break;
 		case "Step_F2_9":
			dialog.text = "Everything that was confiscated from you will be returned to you. Give my best wishes to Bertrand. And be careful on the way back-there's been a hell of a lot going on near the island lately.";
			link.l1 = "What exactly, sir?";
			link.l1.go = "Step_F2_10";
		break;
 		case "Step_F2_10":
			dialog.text = "Nothing good, Captain, nothing good... Oh well, you don't care about that. Goodbye.";
			link.l1 = "Goodbye, Monsieur Governor-General.";
			link.l1.go = "exit";
			bDisableCharacterMenu = false; //открываем Ф2
			AddDialogExitQuestFunction("FrLine_HoverGoOnPrison");
		break;

 		case "Step_F2_12":
			dialog.text = "Never have I, " + GetFullName(npchar) + ", a Spanish privateer, given up on ladron! I've sunk twenty ships in the vicinity of Curacao, so you can't intimidate me. It's better to accept death, but keep your honor!";
			link.l1 = "Well, accept death, if that's what you want. I found out everything needed...";
			link.l1.go = "Step_F2_13";
		break;
 		case "Step_F2_13":
			AddQuestRecord("Fra_Line_2_DelivLetter", "5");
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			pchar.questTemp.State = "Fr2Letter_NiceResult";
			DialogExit();
		break;
//********************************* Похищение донны Анны. Квест №3 **********************************
 		case "Step_F3_1":
			dialog.text = "Jose is dead... God knows, I didn't want that... He found the letter I wrote to him and locked me in here...";
			link.l1 = "I know, senora, I guessed it... I ask you to follow me. Be careful, madam...";
			link.l1.go = "Step_F3_2";
		break;
 		case "Step_F3_2":
			pchar.questTemp.State = "Fr3TakeAnna_HavanaOut";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition.l1 = "location";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition.l1.location = "Cuba2";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition = "Fr3TakeAnna_DelivShip";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
//********************************* Проблемы донны Анны. Квест №5 **********************************
 		case "Step_F5_1":
			dialog.text = "Yes, it is, "+ GetSexPhrase("senor","senorita") +". Donna de Leyva is in mortal danger! The Governor-General of Havana, Francisco Oregon y Gascon, undertook an investigation into this matter and found out all the circumstances of Donna Anna's flight to Tortuga\n"+
				          "Everything he learned, he told the relatives of the murdered Don Jose. And Don Jose Ramirez de Leyva is a descendant of an ancient Castilian family. According to the laws of honor, Donna Anna must pay for her infidelity.";
			link.l1 = "They can't get to Tortuga...";
    		link.l1.go = "Step_F5_2";
		break;
 		case "Step_F5_2":
			dialog.text = "You are mistaken, "+ GetSexPhrase("senor","senorita") +". Don Jose's cousins have already arrived here. I've seen them, and believe me, they're real thugs. When a Castilian nobleman takes revenge, he is not afraid of the devil himself!";
			link.l1 = "Well, I don't promise them the devil, but I can seem like myself. Can you tell me where I can find them?";
    		link.l1.go = "Step_F5_3";
		break;
 		case "Step_F5_3":
			dialog.text = "Yesterday they went to the jungle, they are not in the city. Apparently, they are establishing relations with smugglers in order to secretly enter the Trading Floor.";
			link.l1 = "We need to catch them in the jungle! If they make it back to the city in time, I'll have to fight the entire Spanish garrison. Thank you, dear Ines. I never believed into female friendship, but you, a brave woman, convinced me otherwise. Goodbye.";
    		link.l1.go = "exit";
			pchar.questTemp.State = "Fr5AnnaHant_SeekHoseBrothers";
			AddQuestRecord("Fra_Line_5_KillAnnaHanters", "3");
			AddQuestUserData("Fra_Line_5_KillAnnaHanters", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("Fra_Line_5_KillAnnaHanters", "sSex1", GetSexPhrase("en","on"));

			npchar.LifeDay = 1; // уберём нпс
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			locations[FindLocation("Mayak10")].DisableEncounters = true; //энкаутеры закроем
			LAi_LocationDisableOfficersGen("Mayak10", true); //офицеров не пускать
			Pchar.quest.Fr5Anna_InShore.win_condition.l1 = "location";
			Pchar.quest.Fr5Anna_InShore.win_condition.l1.location = "Mayak10";
			Pchar.quest.Fr5Anna_InShore.win_condition = "Fr5Anna_InShore";
		break;
 		case "Step_F5_4":
			dialog.text = "Phew, that's very good. Now Donna Anna can breathe easy...";
			link.l1 = "I suppose so.";
    		link.l1.go = "exit";
		break;
//********************************* Вызволение Рока Бразильца. Квест №7 **********************************
 		case "Step_F7_1":
    		if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "I am glad and happy, "+ GetSexPhrase("buddy","girlfriend") +". But I do not know you, maybe you can tell me who sent you here?";
				link.l1 =  "None other than Monsieur Bertrand d'Ogeron. I suppose you know who it is... All right, now let's get out of here to the ship, they're waiting for us on Tortuga. Can you hold a gun?";
    			link.l1.go = "Step_F7_2";
			}
			else
			{
				dialog.text = "I am very glad...";
				link.l1 = "We'll talk later, we need to deal with everyone here...";
    			link.l1.go = "Step_F7_Late";
			}
		break;
 		case "Step_F7_2":
    		if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "Alas, no. The local holy fathers broke my arms...";
				link.l1 =  "This is bad... Then follow me closely - we will break through.";
    			link.l1.go = "Step_F7_3";
			}
			else
			{
				dialog.text = "Alas, no...";
				link.l1 = "We'll talk later, we need to deal with everyone here!";
    			link.l1.go = "Step_F7_Late";
			}
		break;
 		case "Step_F7_3":
			dialog.text = "Okay, whatever you say. I don't have much choice...";
			link.l1 = "Then go ahead, corsair! And keep up.";
    		link.l1.go = "Step_F7_4";
		break;
 		case "Step_F7_4":
			bDisableFastReload = false;
			AddQuestRecord("Fra_Line_7_RockBras", "2");
			AddQuestUserData("Fra_Line_7_RockBras", "sSex", GetSexPhrase("ate","la"));
			Pchar.quest.Fr7RockBras_DelivShip.win_condition.l1 = "location";
			Pchar.quest.Fr7RockBras_DelivShip.win_condition.l1.location = "Cuba1";
			Pchar.quest.Fr7RockBras_DelivShip.win_condition = "Fr7RockBras_DelivShip";
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
 		case "Step_F7_5":
			dialog.text = "Listen, I want to thank you for saving my life. I can't help you with money - I have to contribute a fair amount to the treasury of France\n"+
				          "But I can give you something that means a lot more to a corsair than money.";
			link.l1 = "I will not refuse, especially since I am very interested...";
    		link.l1.go = "Step_F7_6";
		break;
		case "Step_F7_6":
            dialog.text = "Anyway, listen to me carefully... There is a dungeon under the city of Fort de France in Martinique. In this dungeon, I have hidden one very valuable and necessary thing for our brother..\n"+
				          "I won't say what it is, you'll see... Anyway, I'm giving you what you'll find there.";
			link.l1 = "However, an unusual gift, to put it bluntly... Well, anyway, you don't look a gift horse in the mouth. Goodbye, Rock, get well...";
            link.l1.go = "Step_F7_7";
        break;
		case "Step_F7_7":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "none", "", "", "", 6.0);
			DeleteAttribute(npchar, "RebirthPhantom");
         	npchar.LifeDay = 0; // уберём нпс
			pchar.GenQuestRandItem.FortFrance_Dungeon = true;
			pchar.GenQuestRandItem.FortFrance_Dungeon.randitem3 = "cirass5";
			DialogExit();
        break;
 		case "Step_F7_8":
			dialog.text = "You're late... They've been torturing me all this week... Now... nothing can save me anymore... uh-uh...";
			link.l1 = "Damn it, he's dead!";
    		link.l1.go = "Step_F7_9";
		break;
 		case "Step_F7_9":
			bDisableFastReload = true;
			LAi_KillCharacter(npchar);
			DeleteAttribute(npchar, "RebirthPhantom");
         	npchar.LifeDay = 0; // уберём нпс
			pchar.questTemp.State = "Fr7RockBras_RockIsAgony";
			DialogExit();
		break;
 		case "Step_F7_Late":
			bDisableFastReload = true;
			LAi_ActorWaitDialog(npchar, pchar);
			DialogExit();
		break;
//********************************* Объехать трёх корсаров. Квест №8 **********************************
        case "Step_F8_1":
            dialog.text = "Yeah, this bastard can't come after me himself and sends his henchmen! I hope your soul, before going to hell, will have time to whisper to him what awaits everyone who dares...";
            link.l1 = "Tired. Let's get busy, Captain...";
            link.l1.go = "Step_F8_2";
        break;
 		case "Step_F8_2":
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("PortRoyal_tavern", "reload2_back", true);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CanFightCurLocation");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	}
}
