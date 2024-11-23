
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":								//Автор Sinistra
			dialog.text = "Look who's here! The Great Pirate, the terror of the seas and oceans! Only, damn it, I forgot your name! Do you know who I am? I'm James Callow! I robbed the Spanish colony of San Juan and boarded the flagship of the French squadron! Am I not a monster? Don't you tremble at the sight of me?";
			link.l1 = "No. I am not a saint myself, and I also happened to rob something in my time.";
			link.l1.go = "Vstrecha_2";
			link.l2 = "Honestly, I am meek and soft. Sorry, but I would preferred to stampede for a while.";
			link.l2.go = "exit";
			if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue") && pchar.questTemp.AnjelikaTichPrologue == "ATP")
			{
				dialog.text = "I drink foam wave...";
				link.l1 = "...";
				link.l1.go = "Slushat_Pesnu_1";
				DeleteAttribute(link, "l2");
			}
			if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue") && pchar.questTemp.AnjelikaTichPrologue == "ATP" &&
					CheckAttribute(pchar, "questTemp.ATPNapelsy") && pchar.questTemp.ATPNapelsy == "Napelsy")
			{
				dialog.text = "He ripped open my belly... Coral reef... La-la-la-la-la!";
				link.l1 = "";
				link.l1.go = "exit";
				DeleteAttribute(link, "l2");
			}
		break;

		case "Vstrecha_2":
            dialog.text = "Great! You know, "+ GetSexPhrase("boy","girl") +", I "+ GetSexPhrase("I need such a person","I need such a person") +"like you. I'm planning an adventure that I don't want to get involved in alone. From what I've heard about you, I conclude that it's you that I need "+ GetSexPhrase("need","need") +". What do you say, "+ pchar.name +"?";
            link.l1 = "What kind of adventure are you planning, Jimmy?";
			link.l1.go = "Vstrecha_3";
		break;

		case "Vstrecha_3":
            dialog.text = "Do you believe in ghosts, "+ GetSexPhrase("buddy","girlfriend") +"? Do you believe in evil spirits that bring bad luck?";
			link.l1 = "I don't believe in this nonsense. Only children and the elderly believe that spirits can interfere with human life.";
			link.l1.go = "Ne_Veru_1";
            link.l2 = "I've heard stories about spirits and ghosts.";
			link.l2.go = "Vstrecha_4";
		break;

		case "Ne_Veru_1":
            dialog.text = "You are too young to understand such things, "+ GetSexPhrase("boy","girl") +". You would have more life experience, then you would understand that sometimes the stories that are told in taverns are not just fiction and bragging. In some cases, they are even too true.";
			link.l1 = "You know, it looks like you're not right in the head, James. I'd rather leave you here. Goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "VstrechNetAgain_1";
			npchar.lifeday = 0;
		break;

		case "Vstrecha_4":
			DialogExit();
			
			sld = CharacterFromID("James_Callow");
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "Vstrecha_4_1";
			LAi_Fade("PDM_Callow_sadis_na_stul", "");
		break;
		
		case "Vstrecha_4_1":
            dialog.text = "Well, I'll tell you: all these stories are true. There are things that I can't explain in any other way. I found one thing, and I swear it's cursed!";
            link.l1 = "Really? And what makes you believe that? Can you feel this spirit? Or does this curse appear to you at night and swear to its own malignity?";
			link.l1.go = "Vstrecha_5";
			LAi_CharacterPlaySound(NPChar, "GR_Jamescallow_FirstTime");
		break;

		case "Vstrecha_5":
            dialog.text = "This is not a reason for fun, "+ pchar.name +". Ever since I got hold of that damn idol, my luck has run out. First, I got caught in a storm near Cuba. Then I boarded a Spanish galleon. And do you know what I found in the hold? Bags. Empty bags. No gold, no silver, just those damn bags! Full holds of sacks!";
            link.l1 = "Ha! A poor catch. And then what?";
			link.l1.go = "Vstrecha_6";
		break;

		case "Vstrecha_6":
            dialog.text = "A day later, Armando de Mutil, a famous bounty hunter, spotted my ship and tried to capture me. It was his last day on this earth, but my ship was badly damaged in battle. I went to Bermuda to repair the ship, but the failures still haunted me.\n"+
							"Off the English coast, the coast guard noticed my sail on the horizon, and I had to give all my gold to the captain of the brig to buy my freedom. It was only then that I realized what was the reason for all these failures.";
            link.l1 = "And what is it?";
			link.l1.go = "Vstrecha_7";
		break;

		case "Vstrecha_7":
            dialog.text = "A month ago I met a poor old Indian. We were taking fresh water from a spring on one tiny islet. It was stuffed out of the trees. He was muttering something about insulting the great Huruk'tseli'oli and the vengeance that would follow. Mumbling, he was waving that pagan idol.\n"+
							"When I saw that the statue was made of pure gold and decorated with a large emerald, I tore it from the hands of an Indian.\n"+
							"No, I'm not as bad as you think... I gave him a few coins in return. But he didn't take them. He said the idol could only be a gift. Then he said he was giving me an idol 'along with evil in his heart' and another gift.\n"+
							"The Indian said that since I really want to get this idol, it will be mine forever, and I will never be able to get rid of it. I laughed in his face and cut off his head. I'm not afraid of God or the devil, but now I'm scared, "+ GetSexPhrase("buddy","girlfriend") +".";
            link.l1 = "Are you a head chopper for old Indians? Are you scared? Okay, stop messing with my head! Ha! Just throw this thing into the sea!";
			link.l1.go = "Vstrecha_8";
		break;

		case "Vstrecha_8":
            dialog.text = "Listen, "+ GetSexPhrase("buddy","girlfriend") +". I tried to sell it. I tried to lose him. It's not working out. The cursed idol returns to my cabin, my bag, my closet-returns to me wherever I am. The damn thing is following me! It's some kind of curse! You say you don't believe in curses-so can you help me?";
            link.l1 = "Hmmm... Maybe. Why don't you just give it to someone? The Indian said that an idol can only be presented.";
			link.l1.go = "Vstrecha_9";
		break;

		case "Vstrecha_9":
            dialog.text = "Because I can't give it away! It doesn't make any sense, but... This Indian shaman somehow... he increased my greed... I just... can't. I think it's part of that sneaky curse. I can't give it away! To think that I would give away such a thing and not make a profit... it's simple... It's unbearable! I think I'll just hang myself if I do this. But I have a plan...";
            link.l1 = "What's the plan?";
			link.l1.go = "Vstrecha_10"
		break;

		case "Vstrecha_10":
            dialog.text = "I know a man who will want to get this idol as soon as he sees it. This is my most dangerous enemy. And this, of course, will not be a non-profit business! If I know that Rogers has this thing in his hands, it will be the greatest joy of my life. But I can't do it myself. Rogers knows me too well. I have no doubt that he will not suspect anything if the gift comes from you.";
            link.l1 = "What do I get for this?";
			link.l1.go = "Vstrecha_11";
		break;

		case "Vstrecha_11":
            dialog.text = "My thanks. And I will accompany you on all your travels... at least for a while. The one who you must give away the idol is Bortolomew Rogers, he is the leader of the settlement of Le Francois, in Martinique. Will you help me, "+ GetSexPhrase("buddy","girlfriend") +"?";
			link.l1 = "Yes. I'll help you.";
			link.l1.go = "VstrechaDa_1";
            link.l2 = "No, it would be a waste of time.";
			link.l2.go = "VstrechaNet_1";
			LAi_SetSitType(npchar);
		break;

		case "VstrechaDa_1":
            dialog.text = "Thank you, "+ GetSexPhrase("brother","sister") +". Here, take this idol, not as a gift, but, on the contrary, in exchange for your promise to give it to my worst enemy, Bortolomew Rogers. Ugh... I hope it works and I won't find an idol under my pillow tomorrow. Take it to Rogers quickly, otherwise who knows? ";
            link.l1 = "See you later, brother.";
			link.l1.go = "CodDa_1";
			GiveItem2Character(PChar, "Cursed_idol");
			PlaySound("Interface\important_item.wav");
			Log_info("James gave you an idol");
			NextDiag.TempNode = "VstrechDaAgain_1";
		break;

		case "VstrechaNet_1":
			dialog.text = "In that case, damn you. May your body go to the sharks, and your soul to the devil!";
            link.l1 = "It's unlikely. Okay, don't get bored. And look, take good care of your little idol. Goodbye.";
			link.l1.go = "CodNet_1";
			NextDiag.TempNode = "VstrechNetAgain_1";
			npchar.lifeday = 0;
		break;

		case "CodDa_1":
			LAi_Fade("PDM_Callow_vstaem", "");
			
			SetQuestHeader("PDM_Cursed_Idol");
			AddQuestRecord("PDM_Cursed_Idol", "1");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("PDM_Cursed_Idol", "sSex1", GetSexPhrase("en","on"));

			sld = CharacterFromID("LeFransua_Mayor");   //ссылается на персонажа
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "none", "");

			sld = GetCharacter(NPC_GenerateCharacter("PDM_LeFransua_Mayor_Klon", "huber_fra", "man", "man", 30, PIRATE, -1, false));   //ссылается на клона
			sld.name	= "Bartholomew";
			sld.lastname	= "Rogers";
			sld.nation = PIRATE;
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetImmortal(sld, true);
			GiveItem2Character(sld, GUN_COMMON);
			GiveItem2Character(sld, BLADE_LONG);
			LAi_SetHuberType(sld);
			SetRandSPECIAL(sld);
			SetSelfSkill(sld, 90, 90, 90, 60, 70);
			sld.standUp = true; //вставать и нападать на врага
			ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "sit", "sit1");
			sld.Dialog.Filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "Rodjer_1";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CodNet_1":
            LAi_Fade("PDM_Callow_vstaem", "");
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "VstrechDaAgain_1":
			dialog.text = "Arrhh! Why are you wasting your time? Take the idol to Rogers before he brings you bad luck. I don't want to be the cause of your failures.";
            link.l1 = "Don't worry, brother. Rogers will have your little present very soon.";
			link.l1.go = "exit";
		break;

		case "VstrechNetAgain_1":
			dialog.text = "Arrgh! It's you! Get out of here before I rip your head off!";
            link.l1 = "Patience, patience, Jimmy. You're just throwing yourself off balance.";
			link.l1.go = "exit";
		break;

		case "Rodjer_1":
			dialog.text = "Hey! You're on my territory, "+ GetSexPhrase("boy","girl") +", so keep quiet here, or you'll be silent forever. Do you understand me?";
            link.l1 = "Hold your honor, Rogers. I know where I am.";
			link.l1.go = "Rodjer_2";
			LAi_CharacterPlaySound(NPChar, "GR_Prikusi_Yazik");
		break;

		case "Rodjer_2":
			dialog.text = "Fine, don't forget about it. What do you need, baby?";
            link.l1 = "I have a gift for you.";
			link.l1.go = "Rodjer_3";
		break;

		case "Rodjer_3":
			dialog.text = "Gift? Show it to me.";
            link.l1 = "This is an Indian idol. Here, take a look. It's a pretty trinket, isn't it?";
			link.l1.go = "Rodjer_4";
		break;

		case "Rodjer_4":
			dialog.text = "Who sent you?";
            link.l1 = "Nobody. I just decided to make a gift to someone who has the power in Le Francois.";
			link.l1.go = "RodjerDa_1";
			link.l2 = "Your old friend. He wanted to please you with this gift.";
			link.l2.go = "RodjerPodozren_1";
		break;

		case "RodjerPodozren_1":
			dialog.text = "I don't believe you, "+ GetSexPhrase("guy","girl") +". I don't have any friends who can send me a gift. But I have a lot of enemies who are ready to send me something dangerous. So you still insist that this is a gift from an old friend?";
            link.l1 = "Yes, because it's true.";
			link.l1.go = "RodjerPodozren_2";
			link.l2 = "No... But I want you to take this trinket.";
			link.l2.go = "RodjerDa_2";
		break;

		case "RodjerPodozren_2":
			dialog.text = "You are "+ GetSexPhrase("cheeky","cheeky") +", "+ GetSexPhrase("sucker","baby") +". Get out of here and take your present with you. You can give it to the whores in the tavern. Come back to me when you learn how to talk to the man who holds this city in his fist.";
            link.l1 = "...";
			link.l1.go = "RodjerCod_2";
			NextDiag.TempNode = "RodjerPokapoka_1";
			ChangeCharacterReputation(pchar, -4);
		break;

		case "RodjerDa_1":
			dialog.text = "Ha! You realized who runs this small town. And you decided to flatter me with this gift... I like it!";
            link.l1 = "Wow! You're literally reading my mind. But will you accept a gift from me?";
			link.l1.go = "RodjerDa_2";
		break;

		case "RodjerDa_2":
			dialog.text = "Come here... Arrgh! What a beautiful thing! Yes, I like it! What do you want in exchange for your gift? Tell me, and I'll do it! But before you ask, think carefully.";
			//link.l1 = "I know that pirates often leave captured ships here. I want to take one of them, and I need your permission. At the same time, can you tell me which one is in decent condition?";
			//link.l1.go = "RodjerVar_1";
			link.l1 = "I don't need anything.";
			link.l1.go = "RodjerVar_2";
			Log_info("You gave the idol to Rogers");
			TakeItemFromCharacter(pchar, "Cursed_idol");
		break;

		/*case "RodjerVar_1":
			dialog.text = "Unfortunately, "+ GetSexPhrase("guy","girl") +", I have nothing to offer you. But I'll take your trinket. Now, goodbye.";
			link.l1 = "Uh... See you later.";
			link.l1.go = "RodjerCod_1";
			NextDiag.TempNode = "RodjerPokapoka_1";
			ChangeCharacterReputation(pchar, -2);
		break;*/

		case "RodjerVar_2":
			dialog.text = "I don't believe you, "+ GetSexPhrase("guy","girl") +". Such gifts are not made for nothing... Take him back and get out of here. You're too "+ GetSexPhrase("stupid","stupid") +" to get me through. Get out!";
			link.l1 = "But...";
			link.l1.go = "RodjerCod_2";
			GiveItem2Character(PChar, "Cursed_idol");
			Log_info("Rogers gave you back the idol");
			NextDiag.TempNode = "RodjerPokapoka_1";
			ChangeCharacterReputation(pchar, 4);
		break;

		case "RodjerPokapoka_1":
			dialog.text = "What do you need?";
			link.l1 = "Nothing, I'm leaving.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RodjerPokapoka_1";
		break;

		/*case "RodjerCod_1":
			Pchar.quest.PDM_Callow_RodjerFin.win_condition.l1           = "Location";
        	Pchar.quest.PDM_Callow_RodjerFin.win_condition.l1.location  = "LaVega_Tavern";
        	Pchar.quest.PDM_Callow_RodjerFin.win_condition              = "PDM_Callow_RodjerFin";
			Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1           = "ExitFromLocation";
        	Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1.location  = PChar.location;
        	Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition              = "PDM_Callow_RodjerVozvrat";
			AddQuestRecord("PDM_Cursed_Idol", "2");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("","a"));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;*/

		case "RodjerCod_2":
			Pchar.quest.PDM_Callow_RodjerProdolg.win_condition.l1           = "Location";
			Pchar.quest.PDM_Callow_RodjerProdolg.win_condition.l1.location  = "LeFransua_town";
			pchar.quest.PDM_Callow_RodjerProdolg.function = "PDM_Callow_RodjerProdolg";
			AddQuestRecord("PDM_Cursed_Idol", "4");
			AddQuestUserData("PDM_Cursed_Idol", "sSex1", GetSexPhrase("en","on"));
			bDisableFastReload = true;
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], true);
			SetLocationCapturedState("LeFransua_town", true);
			SetCurrentTime(24, 0);

			sld = GetCharacter(NPC_GenerateCharacter("Pablo_Loco_Idol", "indsar1", "man", "man", 10, PIRATE, -1, false));
			sld.name = "Keruk";
			sld.lastname = "";
			sld.talker = 7;
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetStayType(sld);
			sld.dialog.filename   = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode   = "Pablo_Loco_Idol";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld,"LeFransua_town","goto","goto7");
			
			pchar.questTemp.PDM_PI_Skelety_v_more = true;

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Pablo_Loco_Idol":
			dialog.text = "I feel evil magic in you...";
			link.l1 = "What does this have to do with me? Maybe... Would you be interested in this golden statuette?";
			link.l1.go = "Pablo_Loco_Idol_2";
		break;

		case "Pablo_Loco_Idol_2":
			dialog.text = "Throw it away! Throw it away! Never touch this thing, never! These gold eaters, these who lived on Emuno - they made this thing! Never touch her! Huruk's anger is very great, it is the spirit of the smoking mountain. He, who throws stones at the heads of his own people, will destroy you too. Get rid of this evil thing before it kills you!";
			link.l1 = "What a nightmare... What did I get into?";
			link.l1.go = "Pablo_Loco_Idol_3";
			npchar.lifeday = 0;
		break;

		case "Pablo_Loco_Idol_3":
			DialogExit();
			
			sld = CharacterFromID("Pablo_Loco_Idol");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "houseK4", "none", "", "", "", -1);
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Pinki_Skelet", "skel3", "skeleton", "skeleton", sti(pchar.rank), PIRATE, -1, true));
			sld.name = "Pinkamina";
			sld.lastname = "Pie";
			FantomMakeCoolFighter(sld, sti(pchar.rank), 30, 30, "blade36", "", 25 + MOD_SKILL_ENEMY_RATE * 4);
			sld.SaveItemsForDead = true;
			sld.DontChangeBlade = true;
			sld.DeleteFood = true;
			LAi_LoginInCaptureTown(sld, true);
			AddMoneyToCharacter(sld, 5000);
			AddItems(sld, "jewelry2", 10);
			AddItems(sld, "jewelry5", 10);
			AddItems(sld, "jewelry17", 10);
			AddItems(sld, "mineral5", 3);
			sld.dialog.filename   = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode   = "FraOff_1";
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "reload",  "houseH7");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			for (i=4; i<=5; i++)
			{
				sTemp = "skel_"+(rand(3)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_skel_"+i, sTemp, "skeleton", "skeleton", sti(pchar.rank), PIRATE, -1, true));
				LAi_SetActorType(sld);
				LAi_LoginInCaptureTown(sld, true);
				sld.lifeday = 1;
				SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate")
				ChangeCharacterAddressGroup(sld, "LeFransua_town", "goto",  "goto"+i);
			}		
			for (i=10; i<=11; i++)
			{
				sTemp = "skel_"+(rand(3)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_skel_"+i, sTemp, "skeleton", "skeleton", sti(pchar.rank), PIRATE, -1, true));
				LAi_SetActorType(sld);
				LAi_LoginInCaptureTown(sld, true);
				sld.lifeday = 1;
				SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate")
				ChangeCharacterAddressGroup(sld, "LeFransua_town", "goto",  "goto"+i);
			}
			for (i=14; i<=17; i++)
			{
				sTemp = "skel_"+(rand(3)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_skel_"+i, sTemp, "skeleton", "skeleton", sti(pchar.rank), PIRATE, -1, true));
				LAi_SetActorType(sld);
				LAi_LoginInCaptureTown(sld, true);
				sld.lifeday = 1;
				SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate")
				ChangeCharacterAddressGroup(sld, "LeFransua_town", "goto",  "goto"+i);
			}
		break;

		case "FraOff_1":
			dialog.text = RandPhraseSimple("I like to play with walking meat. Especially when this meat splashes with a crimson fountain.", "I almost sewed myself a beautiful doublet made of human skin, only a couple of patches are missing, yours will just fit.");
			link.l1 = RandPhraseSimple("You made a mistake, my friend.", "Oh, you damned scum, get lost!");
			link.l1.go = "FraOff_Bitva_1";
		break;

		case "FraOff_Bitva_1":
			LAi_LocationFightDisable(loadedLocation, false); //Разрешаем оружие
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("PDM_Pinki_Skelet");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PDM_PI_Skelety");
			
			for (i=4; i<=5; i++)
			{
				sld = CharacterFromID("PDM_PI_skel_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_PI_Skelety");
			}		
			for (i=10; i<=11; i++)
			{
				sld = CharacterFromID("PDM_PI_skel_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_PI_Skelety");
			}			
			for (i=14; i<=17; i++)
			{
				sld = CharacterFromID("PDM_PI_skel_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_PI_Skelety");
			}
			
			PChar.quest.PDM_PI_PinkiSkelet.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_PI_PinkiSkelet.win_condition.l1.character = "PDM_Pinki_Skelet";
			PChar.quest.PDM_PI_PinkiSkelet.win_condition = "PDM_FraOff_Bitva_1_Posle";
			LAi_group_SetRelation("PDM_PI_Skelety", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("PDM_PI_Skelety", LAI_GROUP_PLAYER, false);
			LAi_group_SetLookRadius("PDM_PI_Skelety", 7.0);
			LAi_group_SetHearRadius("PDM_PI_Skelety", 2.0);
			LAi_group_SetSayRadius("PDM_PI_Skelety", 4.0);
			DialogExit();
		break;

		case "CollowNeRad_1":
			dialog.text = "Ah! Finally you are "+ GetSexPhrase("back","back") +". How are you? You did this?";
			link.l1 = "I have bad news for you. Rogers refused to take the idol.";
			link.l1.go = "CollowNeRad_2";
			LAi_CharacterPlaySound(NPChar, "GR_Jamescallow_FirstTime");
		break;
		
		case "CollowNeRad_2":
			DialogExit();
			
			sld = CharacterFromID("James_Callow");
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "CollowNeRad_2_1";
			LAi_Fade("PDM_Callow_sadis_na_stul", "");
		break;

		case "CollowNeRad_2_1":
			dialog.text = "The devil! The devil tear him apart! Why did he refuse to take it? I knew I shouldn't trust to "+ GetSexPhrase("such a sucker","such a fool") +" like you are! It's all because of your stupidity, "+ GetSexPhrase("guy","girl") +"!";
			link.l1 = "I'm not going to take insults, James. And I'm not one of the patient people.";
			link.l1.go = "CollowNeRad_3";
		break;

		case "CollowNeRad_3":
			dialog.text = "Arrgh! You're right. What are you going to do now? I'm not taking this damn thing back. What if we give the idol to someone else?";
			link.l1 = "Good idea... But who will we choose as the victim?";
			link.l1.go = "CollowNeRad_4";
			LAi_SetSitType(npchar);
		break;

		case "CollowNeRad_4":
			dialog.text = "People say that the usurer on Tortuga is crazy about gold and precious stones... Maybe he'll like our thing? What do you think?";
			//link.l1 = "No, I have a better idea - you just take your fucking idol and leave me alone. I'm already sick of this nonsense!";
			//link.l1.go = "CollowOchenNeRad_1";
			link.l1 = "Great! We'll just slip him the damn statue.";
			link.l1.go = "CollowNeRad_5";
		break;

		case "CollowNeRad_5":
			dialog.text = "You will have to offer it as a gift again... I hope he's more greedy than Rogers. I bet he'll take the bait.";
			link.l1 = "Don't worry, everything will be fine this time. I'll let him see the statue first, and then I'll talk business with him. The glitter of gold will dazzle him. After that, he will buy the idol for any money.";
			link.l1.go = "CollowNeRad_6";
		break;

		case "CollowNeRad_6":
			if (CheckCharacterItem(Pchar, "patent_fra"))
			{
				dialog.text = "That's exactly how it seems to me. But be "+ GetSexPhrase("careful","careful") +". If anything goes wrong, you'll have to make your way through the crowd of guards to get out of there.";
				link.l1 = "I hope it doesn't come to that.";
				link.l1.go = "CollowNeRad_7";
			}
			else
			{
				dialog.text = "That's exactly how it seems to me. But be "+ GetSexPhrase("careful","careful") +". If anything goes wrong, you'll have to make your way through the crowd of guards to get out of there.";
				link.l1 = "I'll take care of it. And if you have to kill one or two guards, it won't be the first time.";
				link.l1.go = "CollowNeRad_7";
			}
		break;

		case "CollowNeRad_7":
			dialog.text = "Then go, "+ GetSexPhrase("brother","sister") +". Good luck to you.";
			link.l1 = "See you later, brother. I'll be back soon.";
			link.l1.go = "CollowNeRad_8";
			NextDiag.TempNode = "VstrechEsheAgain_2";
		break;

		case "CollowNeRad_8":
			LAi_Fade("PDM_Callow_vstaem", "");

			pchar.questTemp.PDM_PI_Rostov = "PDM_PI_Rostov";

			AddQuestRecord("PDM_Cursed_Idol", "8");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("lya","las"));

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "VstrechEsheAgain_2":
			dialog.text = "Arrhh! Why are you wasting your time? Take the idol to the usurer on Tortuga before he brings you bad luck. I don't want to be the cause of your failures.";
            link.l1 = "Don't worry, brother. Your little gift will be on Tortuga very soon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "VstrechEsheAgain_2";
		break;

		case "Rostovshik_Fra_Off_1":
			dialog.text = "What a surprise, and our usurer is not as poor as he told us!";
			link.l1 = "";
			link.l1.go = "Rostovshik_Fra_Off_1a";
		break;

		case "Rostovshik_Fra_Off_1a":
			DialogExit();
			StartInstantDialog("Tortuga_usurer", "Rostovshik_Fra_Off_1b", "Quest\PDM\Cursed_Idol.c");
		break;

		case "Rostovshik_Fra_Off_1b":
			dialog.text = "I will refund everything, there will be money next week. I swear by my mother!";
            link.l1 = "Well, your business is none of my business.";
			link.l1.go = "Rostovshik_Fra_Off_1с";
		break;

		case "Rostovshik_Fra_Off_1с":
			DialogExit();
			StartInstantDialog("PDM_PI_Bandit_1", "Rostovshik_Fra_Off_1_1", "Quest\PDM\Cursed_Idol.c");
		break;

		case "Rostovshik_Fra_Off_1_1":
			dialog.text = "Stop! Cash on the barrel. If you're not going to give anything away, then we'll take it ourselves. Hey, GUYS, come here.";
            link.l1 = "We'll see about that!";
			link.l1.go = "Rostovshik_Mochilovo_1";
			pchar.questTemp.PDM_CI_RostBlago = "PDM_CI_RostBlago";
		break;

		case "Rostovshik_Fra_Off_3":
			dialog.text = "I missed you.";
			link.l1 = "Which one???";
			link.l1.go = "Rostovshik_Fra_Off_3_1";
		break;

		case "Rostovshik_Fra_Off_3_1":
			sld = characterFromID("Tortuga_usurer");
			ChangeCharacterAddressGroup(sld, "Tortuga_Town", "none", "");

			sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Skel_Rostov", "skel_2", "skeleton", "skeleton", 2, PIRATE, -1, true));
			sld.name = "The usurer";
			sld.lastname = "";
			ChangeCharacterAddressGroup(sld, "Tortuga_Bank", "barmen", "stay");
			sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandity_2", "skel4", "skeleton", "skeleton", 2, PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, "Tortuga_Bank", "reload", "reload2");

			DialogExit();
			StartInstantDialog("PDM_PI_Skel_Rostov", "Rostovshik_Fra_Off_3_2", "Quest\PDM\Cursed_Idol.c");
		break;

		case "Rostovshik_Fra_Off_3_2":
			dialog.text = "You can't escape from the cursed idol.";
			link.l1 = "AAAAA!!!";
			link.l1.go = "Rostovshik_Mochilovo_3";
		break;

		case "Rostovshik_Mochilovo_1":
			LAi_LocationFightDisable(loadedLocation, false); //Разрешаем оружие
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("PDM_PI_Bandit_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sTemp = "pirate_"+(rand(24)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandity_"+i, sTemp, "man", "man", 2, PIRATE, -1, true));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//стравливаем
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_Callow_poradomoy");
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, true);
			DialogExit();
		break;

		case "Rostovshik_Mochilovo_3":
			LAi_LocationFightDisable(loadedLocation, false); //Разрешаем оружие
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("PDM_PI_Bandit_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PDM_PI_Skel_Rostov");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PDM_PI_Bandity_2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//стравливаем
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_Callow_poradomoy");
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, true);
			DialogExit();
		break;

		case "Callow_POBEDA_1":
			dialog.text = "Ah! Finally you are "+ GetSexPhrase("back","back") +". How are you? Did you do it?";
            link.l1 = "Everything went smoothly this time. The usurer took the idol.";
			link.l1.go = "Callow_POBEDA_2";
			LAi_CharacterPlaySound(NPChar, "GR_Jamescallow_FirstTime");
		break;
		
		case "Callow_POBEDA_2":
			DialogExit();
			
			sld = CharacterFromID("James_Callow");
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "Callow_POBEDA_2_1";
			LAi_Fade("PDM_Callow_sadis_na_stul", "");
		break;

		case "Callow_POBEDA_2_1":
			dialog.text = "Agggh! What a relief! You can't imagine how much of a burden this has been for me.";
            link.l1 = "Now you are free from his influence. But, I remember that you promised to become my officer... How about this?";
			link.l1.go = "Callow_POBEDA_3";
			AddCharacterExpToSkill(pchar, "Leadership", 150);   	//добавить опыт к авторитету
			AddCharacterExpToSkill(pchar, "Fortune", 100);			//добавить опыт к удаче
			sld = CharacterFromID("Tortuga_usurer");   //возвращаем ростовщика, если на скелетах убили
			ChangeCharacterAddressGroup(sld, "Tortuga_Bank", "barmen", "stay");
		break;

		case "Callow_POBEDA_3":
			dialog.text = "I'm doing what I promised. Now I will swim with you, "+ GetSexPhrase("brother","sister") +".";
            link.l1 = "See you at sea, brother.";
			link.l1.go = "Callow_POBEDA_4";
		break;

		case "Callow_POBEDA_4":
			dialog.text = "";
			link.l1 = "(finishes the rum)";
			link.l1.go = "FINAL";
			sld = CharacterFromID("James_Callow");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.rank = 15;
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "ByWorker");
			LAi_SetHP(sld, 270.0, 270.0);
			SetSPECIAL(sld, 9,8,10,4,6,7,9);		//(Сила, Воспр, Выносл, Лидер, Обуч, Реак, Удача)
			SetSelfSkill(sld, 52, 60, 46, 38, 57);		//(ЛО, СО, ТО, пистолеты, фортуна)
			SetShipSkill(sld, 20, 10, 45, 40, 32, 10, 15, 16, 43);	//(лидер, торг, точн, пушки, навиг, ремонт, аборд, защита, скрыт)
			sld.greeting = "GR_Jamescallow";
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Payment = true;										//Оплата труда
			sld.quest.OfficerPrice = sti(pchar.rank)*500
			sld.OfficerWantToGo.DontGo = true;
			sld.reputation = 15;
			LAi_SetImmortal(sld, false);
			sld.HalfImmortal = true; 							    //Контузия
			sld.loyality = MAX_LOYALITY;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			LAi_SetActorType(npchar);   //делает нпс актёром
			ChangeCharacterAddressGroup(npchar, "LaVega_tavern", "tables", "stay1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3);  // идёт в определённый локатор.
		break;

		case "FINAL":
			LAi_Fade("PDM_Callow_vstaem", "");
		
			AddQuestRecord("PDM_Cursed_Idol", "10");
			CloseQuestHeader("PDM_Cursed_Idol");
			pchar.questdata.ProklyatyIdol = 1;
			sld = CharacterFromID("James_Callow");
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
			AddSimpleRumourToAllNations("On Tortuga, the usurer was found dead in the back room, the garrison doctor said that he died of fear. Unbelievable! And the walls are all daubed with images of a pagan idol.", 30, 1);
			DeleteAttribute(pchar, "questTemp.PDM_CI_RostBlago");
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Matros_preduprejdaet":
			dialog.text = "Captain! The dead are attacking!!!";
            link.l1 = "The Devil!";
			link.l1.go = "exit";
			AddDialogExitQuest("PDM_PI_Skelety_on_Ship_3");
		break;
	}
}
