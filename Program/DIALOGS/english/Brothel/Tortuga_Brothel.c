// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions, "+ GetSexPhrase("young man", "young lady") +"?", "What do you want, "+ GetSexPhrase("handsome", "pretty woman") +"?"), "More questions?", "Hee-hee, the third time a day the same thing - questions...",
                          ""+ GetSexPhrase("Hmm, can you choose some beauty for yourself? And then I already have a very definite opinion about you...", "Hmm, maybe you will choose some kind of beauty for yourself? We don't keep boys, hee-hee...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "Hmm, nothing..."), "No...",
                      "Yeah, it's really the third time... Sorry.", "Not now... Another time...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//==> Голл. №3, узнаем о Пеьере Пикардийце.
            if (pchar.questTemp.State == "WormEnglPlans_WormPicarder")
            {
                link.l1 = "Listen, don't you have Pierre Picardy in your establishment?";
                link.l1.go = "Step_H3_1";
			}
            // ==> квест Аззи.
            if (CheckAttribute(pchar, "questTemp.Azzy.AddSpecial"))
            {
                dialog.text = "What do you want, "+ GetSexPhrase("sir", "miss") +"?";
    			Link.l1 = "Azzi sent me to you. He told me...";
    			Link.l1.go = "Step_1";
            }
            if (pchar.questTemp.Azzy == "HowToKnowAzzy" && !CheckAttribute(pchar, "questTemp.Azzy.AddSpecial"))
            {
                dialog.text = NPCStringReactionRepeat("What do you want, "+ GetSexPhrase("sir", "miss") +"?", "You again?", "Again on the same issue?", "Well, what else?", "block", 0, npchar, Dialog.CurrentNode);
    			Link.l1 = HeroStringReactionRepeat("Listen, I urgently need to find Azzie!", "Yes, it's me again! I need Azzie.", "Again on the same issue.", "The same thing. I need Azzi.", npchar, Dialog.CurrentNode);
    			Link.l1.go = DialogGoNodeRepeat("Step_15", "none", "none", "none", npchar, Dialog.CurrentNode);
            }
            if (pchar.questTemp.Azzy == "DestrContract")
            {
                dialog.text = "Oh, who do I see?!";
    			Link.l1 = "Me, Margarita. But this time I came with a specific offer.";
    			Link.l1.go = "Step_17";
            }
            if (pchar.questTemp.Azzy == "2DestrContract")
            {
                dialog.text = "You again?";
    			Link.l1 = "Me again. How about calling Azzie?";
    			Link.l1.go = "Step_20";
            }
			//жемчужный генератор Шарпа
			if (pchar.questTemp.Sharp == "seekSharp" && GetNpcQuestPastDayWOInit(npchar, "quest.SharpTime") > 7 && !LAi_IsDead(&characters[GetCharacterIndex("Sharp")]))
			{
				link.l1 = "Listen, " + npchar.name + ", I'm looking for Sharp. Do you know where he is?";
				link.l1.go = "SharpPearl_1";
				SaveCurrentNpcQuestDateParam(npchar, "quest.SharpTime");
			}
            // <== Проверяем поле состояния квестов.
		break;
		//==>Голландская линейка, квест №3.
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat("Not now, but it will be today for sure.", ""+ GetSexPhrase("handsome", "pretty") +", you"+ GetSexPhrase("asked", "asked") +"have you already told me about Pierre", "Is it about Pierre again?", "Listen, "+ GetSexPhrase("my darling", "my darling") +", stop talking about Pierre already. Take a look around, have fun...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("How do you know?", "Yes, exactly...", "Hmm, again...", "This is mandatory, but unfortunately not now...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = ""+ GetSexPhrase("My darling", "My darling") +", don't I know?! There hasn't been a day since his return when he hasn't shown up at my place. And every day he takes a new girl, even though I double the tariffs for such inconstancy. So if you want to catch him, then just wait.";
			link.l1 = "Thanks, but I think I'll run.";
			link.l1.go = "exit";
            pchar.questTemp.Talks.Brothel = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "11");
        break;
		//==> Квест Аззи
        case "Step_1":
			dialog.text = "Sorry to interrupt... Tell me your name.";
			Link.l1 = "My name is " + GetFullName(pchar) + ".";
			Link.l1.go = "Step_2";
		break;
        case "Step_2":
			dialog.text = "I've been waiting for you, "+ GetSexPhrase("handsome", "pretty") +". Azzie notified me that I have to do something for you.";
			Link.l1 = "Yes, that's right. I don't even know how to say this 'something'...";
			Link.l1.go = "Step_3";
		break;
        case "Step_3":
			dialog.text = "Why is there such confusion? You know who I am. You know who Azzie is.";
			Link.l1 = "Azzie said you're a witch!";
			Link.l1.go = "Step_4";
		break;
        case "Step_4":
			dialog.text = "And pretty good, I can admit... And who are you, Azzie, that he cares so much about you?";
			Link.l1 = ""+ GetSexPhrase("Familiar", "Familiar") +"it's just...";
			Link.l1.go = "Step_5";
		break;
        case "Step_5":
			dialog.text = "Ah, I see... I thought you were a serious person in our hierarchy. And you're just passing by "+ GetSexPhrase("touched", "touched") +"\n"+
                     "Let's get down to business, "+ GetSexPhrase("handsome", "pretty") +". Azzie said that I have to fix your body for certain needs. What do you want?";
			Link.l1 = ""+ GetSexPhrase("Hmm, you know, first of all, I would invite you to the tavern for a cocktail... Are you free tonight?", "Hmm, I want a lot... Everything, and as much as possible!") +"";
			Link.l1.go = "Step_6";
		break;
        case "Step_6":
			dialog.text = ""+ GetSexPhrase("Don't even dream about it, I'm not interested in you. I will play tricks with my friend Azzi when there is Azzi HIMSELF", "A lot is not a conversation") +"\n"+
                     "In general, let's be quick and to the point. I can make you stronger, more agile, increase your perception, charm, stamina or intelligence\n"+
                     "So how should I change your body?";
			Link.l1 = "So that I could be stronger, more agile, more receptive, more charismatic, smarter - in general, I want the whole set.";
			Link.l1.go = "Step_7";
		break;
        case "Step_7":
			dialog.text = "The whole set will not work.";
			Link.l1 = "How is this not going to work?! "+ GetSexPhrase("Not only did she not heat the bathhouse for the good fellow, she did not put him to bed, she also cheats! Azzi said...", "Azzi said...") +"";
			Link.l1.go = "Step_8";
		break;
        case "Step_8":
			dialog.text = "Listen to me carefully, "+ GetSexPhrase("good fellow", "darling") +"! In order to make you stronger, I need to attach new big muscles to your body\n"+
                     "In order to make you more agile, I need to change your tendons to more elastic ones\n"+
                     "In order to make you more resilient, I need to replace your ligaments with other, very strong ones\n"+
                     "And so on for each item. If you do everything at once, then nothing will really work at all. The exception is luck - it is just a reasonable combination of different body characteristics that allows you to get out of various difficult situations with honor. That is, to be lucky\n"+
                     "So don't be stupid, choose one thing. As long as I'm kind...";
			Link.l1 = "I see, so I "+ GetSexPhrase("should", "should") +"choose?";
			Link.l1.go = "Step_9";
		break;
        case "Step_9":
			dialog.text = "Exactly. Tell me, what is the characteristic of your body to increase?";
            Link.l1 = "Power";
			Link.l1.go = "Strength";
            Link.l2 = "Perception";
			Link.l2.go = "Perception";
            Link.l3 = "Reaction";
			Link.l3.go = "Agility";
            Link.l4 = "Leadership";
			Link.l4.go = "Charisma";
            Link.l5 = "Learning ability";
			Link.l5.go = "Intellect";
			Link.l6 = "Endurance";
			Link.l6.go = "Endurance";
            Link.l7 = "Luck";
			Link.l7.go = "Luck";
		break;
        case "Strength":
			dialog.text =  "Strength, good choice. Well, we prepare the muscles - and we will change them. I guess there's no point in postponing, let's get started right now.";
			Link.l1 = "Getting to what?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_S, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_S, 1);
			}
		break;
        case "Perception":
			dialog.text =  "Perception, very good. Well, we are preparing new sensory organs - and we will change them. I guess there's no point in postponing, let's get started right now.";
			Link.l1 = "Getting to what?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_P, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_P, 1);
			}
		break;
        case "Endurance":
			dialog.text =  "Tolerance, good. Well, we are preparing heavy-duty bundles - and we will change them. I guess there's no point in postponing, let's get started right now.";
			Link.l1 = "Getting to what?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_E, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_E, 1);
			}
		break;
        case "Charisma":
			dialog.text =  "Charm? Hmm, good choice, "+ GetSexPhrase("handsome", "pretty") +"! Well, we are preparing a pretty face with "+ GetSexPhrase("courageous", "irresistible") +" facial features - and we will change them. I guess there's no point in postponing, let's get started right now.";
			Link.l1 = "Getting to what?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_C, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_C, 1);
			}
		break;
        case "Intellect":
			dialog.text =  "Intelligence is a good choice. Well, we are preparing new good brains - and we will change them. Don't be afraid, your memory will stay with you. I guess there's no point in postponing, let's get started right now.";
			Link.l1 = "Getting to what?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_I, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_I, 1);
			}
		break;
        case "Agility":
			dialog.text =  "Dexterity, good. Well, we are preparing new superelastic ligaments - and we will change them. I guess there's no point in postponing, let's get started right now.";
			Link.l1 = "Getting to what?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_A, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_A, 1);
			}
		break;
        case "Luck":
			dialog.text =  "Do you want to be"+ GetSexPhrase("lucky pirate", "lucky pirate") +"? And correctly. Well, we are preparing everything new - muscles, ligaments, tendons, eyes, ears - in general, everything. Each is not with outstanding characteristics, but very much nothing. I guess there's no point in postponing, let's get started right now.";
			Link.l1 = "Getting to what?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_L, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_L, 1);
			}
		break;
        case "Step_10":
			dialog.text =  "How to what? For the operation, "+ GetSexPhrase("handsome", "pretty woman") +". We're going to cut you up! Ha ha ha!!";
			Link.l1 = "I don't like all this...";
			Link.l1.go = "Step_11";
		break;
        case "Step_11":
			dialog.text =  "Don't be afraid, there will be no pain. So, we'll quickly change your liver, trim the folds...";
			Link.l1 = "And what, I'm also watching this "+ GetSexPhrase("should", "should") +"?!";
			Link.l1.go = "Step_12";
		break;
        case "Step_12":
			dialog.text =  ""+ GetSexPhrase("What a hypocritical corsair you are", "What a hypocritical pirate you are") +". So many people to the other world "+ GetSexPhrase("sent", "sent") +"and you're afraid of your own blood.";
			Link.l1 = "Listen, witch, I'm not afraid of anything or anyone! So be careful what you say. And I'm afraid for my sanity, you can go crazy - to look at such things!";
			Link.l1.go = "Step_13";
		break;
        case "Step_13":
			dialog.text =  "Okay, let's do everything under anesthesia, ha ha ha! Here, drink the infusion. You will wake up in exactly two days - your order will be completed. And keep in mind that from now on I don't know you.";
			Link.l1 = "Oh, where has our family been! Give me your poison. And be careful with me there...";
			Link.l1.go = "exit";
			AddDialogExitQuest("Azzy_PlusSkill");
		break;
        case "NotPosblAdd":
			dialog.text =  "Let's see what you have... No, "+ GetSexPhrase("handsome", "pretty woman") +", I don't have a decent replacement. Sorry, stocks are limited, and it's a sin for you to complain about what you have... Choose something else.";
			Link.l1 = "Hmm, I am "+ GetSexPhrase("flattered", "flattered") +"... So, can I think about the choice again?";
			Link.l1.go = "Step_9";
		break;
        case "Step_15":
			dialog.text =  "I do not know who you are talking about.";
			Link.l1 = "Stop bullying me! I need Azzie. How can I find him?";
			Link.l1.go = "Step_16";
		break;
        case "Step_16":
			dialog.text =  "Don't shout at the whole city, "+ GetSexPhrase("sir", "madam") +"! Azzi cannot be found, personally I will only be able to see him on Walpurgis Night. I can't help you with anything.";
			Link.l1 = "Damn witch!";
			Link.l1.go = "exit";
		break;
        case "Step_17":
			dialog.text =  "It's interesting to listen.";
			Link.l1 = "I suggest you summon Azzi with the help of three Toltec crystal skulls.";
			Link.l1.go = "Step_18";
		break;
        case "Step_18":
			dialog.text =  "Hmm, I've heard about these things. They are used by Toltecs for mystical rituals. But to summon a demon, you need another item-a strange thing.";
			Link.l1 = "I know about that. So are you ready to perform the ritual?";
			Link.l1.go = "Step_19";
		break;
        case "Step_19":
			dialog.text =  "I can do it if you have these items. But I will keep these items later as payment for my work.  Also, demons don't like to be pulled around for something else. So you can disappear forever...";
			Link.l1 = "Don't worry about Azzie, I have his promise not to touch me if he calls. And I'm leaving the items to you.";
			Link.l1.go = "Step_20";
		break;
        case "Step_20":
			dialog.text =  "I am ready to perform the ritual. Do you have the items?";
            if (CheckCharacterItem(pchar, "sculMa1") && CheckCharacterItem(pchar, "sculMa2") && CheckCharacterItem(pchar, "sculMa3") && CheckCharacterItem(pchar, "indian22"))
            {
    			Link.l1 = "Yes, I have them. Get started right now!";
    			Link.l1.go = "Step_22";
            }
            else
            {
    			Link.l1 = "No, I'm looking.";
    			Link.l1.go = "Step_21";
            }
		break;
        case "Step_21":
			dialog.text =  "If you find it, come and we'll do everything.";
			Link.l1 = "Understood, I will search.";
			Link.l1.go = "exit";
			pchar.questTemp.Azzy = "2DestrContract";
		break;
        case "Step_22":
			dialog.text =  "So let's get started! Ha ha ha (chanting a spell)";
			Link.l1 = "Eh, what a clumsy language...";
			Link.l1.go = "Step_23";
		break;
        case "Step_23":
            TakeItemFromCharacter(pchar, "sculMa1");
            TakeItemFromCharacter(pchar, "sculMa2");
            TakeItemFromCharacter(pchar, "sculMa3");
            TakeItemFromCharacter(pchar, "indian22");
            pchar.questTemp.Azzy = "3DestrContract";
            DeleteAttribute(pchar, "questTemp.Azzy.Oliver")
            ChangeCharacterAddressGroup(characterFromId("Azzy"), pchar.location, "goto", "goto2");
            DoQuestCheckDelay("Azzy_IsFree", 2.0);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
		break;
		// капитан Шарп, грабёж жемчужных промыслов
		case "SharpPearl_1":
			if (drand(1) || bBettaTestMode)
			{
				if (sti(pchar.questTemp.Sharp.brothelChance) < 9)
				{	//футболим геймера в город
					pchar.questTemp.Sharp.City = GetSharpCity();
					pchar.questTemp.Sharp.City.rumour = true; //флаг дачи слуха
					dialog.text = "As far as I know, Captain Sharp went to " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + ".";
					link.l1 = "Heh! Thank you, " + npchar.name + ". You've helped me a lot!";
					link.l1.go = "exit";
					pchar.questTemp.Sharp = "toSharp_going"; //в бордели больше не заходить
					pchar.questTemp.Sharp.count = 0; //счетчик нулим для след. раза
					pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
					pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
					ReOpenQuestHeader("SharpPearl");
					AddQuestRecord("SharpPearl", "1");
					AddQuestUserData("SharpPearl", "sCity", XI_ConvertString("Colony" + npchar.city + "Voc"));
					AddQuestUserData("SharpPearl", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
					if (GetIslandByCityName(pchar.questTemp.Sharp.City) != pchar.questTemp.Sharp.City)
					{
						AddQuestUserData("SharpPearl", "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.questTemp.Sharp.City) + "Voc"));
					}
					//запускаем энкаунтер Шарпа на карте
					group_DeleteGroup("Sharp_Group");
					sld = characterFromId("Sharp");
					string sGroup = "Sharp_Group";
					Group_FindOrCreateGroup(sGroup);
					Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
					Group_LockTask(sGroup);
					Group_AddCharacter(sGroup, sld.id);
					Group_SetGroupCommander(sGroup, sld.id);
					sld.mapEnc.type = "trade";
					sld.mapEnc.worldMapShip = "quest_ship";
					sld.mapEnc.Name = "Brig 'Sharp Bearer'";
					string sColony= SelectAnyColony(npchar.city); //колония, откуда плывёт Шарп
					int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sColony), GetArealByCityName(pchar.questTemp.Sharp.City)) + 1; //дней доехать даём с запасом
					Map_CreateTrader(sColony, pchar.questTemp.Sharp.City, sld.id, daysQty);
					Log_TestInfo("The sharp-bearer is installed from  " + sColony + " in " + pchar.questTemp.Sharp.City);
				}
				else
				{	//чудо, Шарп здесь, в борделе!
					dialog.text = "I know. He's resting at my place. I can call Sharp if you need him urgently.";
					link.l1 = "Do me a favor, " + npchar.name + "...";
					link.l1.go = "SharpPearl_2";
				}
			}
			else
			{
				dialog.text = "I don't know, I haven't had it for a long time.";
				link.l1 = "Understood... Well, thank you, " + npchar.name + ".";
				link.l1.go = "exit";
			}
		break;
		case "SharpPearl_2":
			dialog.text = "Bartalomew-yu-sha! Come to me, dear, someone is asking for you here!";
			link.l1 = "Heh, and you hold Sharp in high esteem, I see...";
			link.l1.go = "SharpPearl_3";
		break;
		case "SharpPearl_3":
			chrDisableReloadToLocation = true;
			pchar.questTemp.Sharp.count = 0; //счётчик нулим для след. раза
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
			pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
			sld = &characters[GetCharacterIndex("Sharp")];
			sld.dialog.currentnode = "BrothelSharp";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

