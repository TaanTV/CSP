// Джекмен в Шарп-Тауне
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
					if (npchar.angry.name == "BlueBird_1") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
	
	if (!CheckAttribute(NPChar,"AbelQuestLetter") && CheckCharacterItem(pchar,"letter_1") && Items[GetItemIndex("letter_1")].describe == "itmdescr_Andre_Abel_Quest_Letter_2")
	{
		Dialog.CurrentNode = "Andre_Abel_Quest_Jackman_Dialog_7";
		NPChar.AbelQuestLetter = true;
	}
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(NPChar.quest.meeting == "0")		//Самый первый диалог
			{
				dialog.text = "Aha! "  + GetFullName(pchar)+"! I knew you'd show up sooner or later! What could have brought you to me?";
				NPChar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue7_Jackman"))	//Sinistra Пролог Анжелика тич
				{
					dialog.text = "So, so... Rumor has it that a certain impostor appeared on the archipelago, who, hiding behind a false name, undertook to turn her affairs around.";
					link.l1 = "Angelica Teach is my real name.";
					link.l1.go = "ATpr_F1";
					break;
				}
				if (!CheckAttribute(pchar, "questTemp.Vstuplenie_v_Bratstvo"))
				{
					link.l14 = "I came here for a reason. I was told that you need me.";
					link.l14.go = "Vstuplenie_v_Bratstvo_1";
				}
				if (CheckAttribute(pchar, "questTemp.Jackman_Zadanie"))
				{
					link.l14 = "Jackman, I'm looking for a job here...";
					link.l14.go = "Jackman_Zadanie";
				}
				link.l89 = "I have a question for you, Jackman.";
				link.l89.go = "Vopros";
				link.l99 = HeroStringReactionRepeat("Uh, I forgot why did I come to you. But if I remember, I'll come back. See you later, Jackman.",
												   "Of course, Jackman. I'm already leaving.",
												   "I'm sorry, Jackman. I'm already leaving.",
												   "Oh...", npchar, Dialog.CurrentNode);
				link.l99.go = "exit";
			}
			else							//Уже знакомы
			{
				dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Do you have a case for me? No? Then get out of here!","Ha, " + pchar.name + "! Do you have business with me? No? Then don't distract me.") +"",
							 "I think I've made myself clear.", "Although I've made myself clear, but you keep distracting me!",
							 "So, this already looks like rudeness, it tired me.", "repeat", 3, npchar, Dialog.CurrentNode);
				NextDiag.TempNode = "First time";
				if (!CheckAttribute(pchar, "questTemp.Vstuplenie_v_Bratstvo"))
				{
					link.l14 = "I came here for a reason. I was told that you need me.";
					link.l14.go = "Vstuplenie_v_Bratstvo_1";
				}
				if (CheckAttribute(pchar, "questTemp.Jackman_Zadanie"))
				{
					link.l14 = "Jackman, I'm looking for a job here...";
					link.l14.go = "Jackman_Zadanie";
				}
				link.l89 = "I have a question for you, Jackman.";
				link.l89.go = "Vopros";
				link.l99 = HeroStringReactionRepeat("Uh, I forgot why did I come to you. But if I remember, I'll come back. See you later, Jackman.",
												   "Of course, Jackman. I'm already leaving.",
												   "I'm sorry, Jackman. I'm already leaving.",
												   "Oh...", npchar, Dialog.CurrentNode);
				link.l99.go = "exit";
			}
		break;
		
		case "I_know_you_good":			//Очень хорошо друг друга знаем
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", glad to see you! Why are you here?",
                         "Well, what else do you want?", "How long will this last? If you have nothing to do, don't distract others!",
                         "You "+ GetSexPhrase("good caper","good girl") +", so live for now. But I don't want to communicate and talk with you anymore.", "repeat", 1, npchar, Dialog.CurrentNode);
			if (!CheckAttribute(pchar, "questTemp.Vstuplenie_v_Bratstvo"))
			{
				link.l14 = "I came here for a reason. I was told that you need me.";
				link.l14.go = "Vstuplenie_v_Bratstvo_1";
			}
			if (CheckAttribute(pchar, "questTemp.Jackman_Zadanie"))
			{
				link.l14 = "Jackman, I'm looking for a job here...";
				link.l14.go = "Jackman_Zadanie";
			}
			link.l89 = "I have a question for you, Jackman.";
			link.l89.go = "Vopros";
			link.l99 = HeroStringReactionRepeat("Yes, actually, I just looked in, to check. There is nothing on the case.",
                                               "Nothing, just like that...",
                                               "Okay, Jackman, I'm sorry...",
                                               "Damn it, I finished playing!!!", npchar, Dialog.CurrentNode);
			link.l99.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		case "Jackman_Zadanie":		//Здесь берём пиратские задания
			dialog.text = "I don't have any errands for you right now.";
			link.l1 = "Okay, Jackman, I'll come back later.";
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "begin" && !CheckAttribute(pchar, "QuestTemp.AndreAbelQuest"))	//Начало Пиратской Линейки: Найти Гудли
			{
				if(CheckAttribute(NPChar, "notQuestLine"))
				{
					dialog.text = "It is rumored that you are in great favor with the English authorities. Has the letter of marque stopped generating income?! I will not cooperate with you, the risk of being hanged as a result of your work is too great. Don't ask...";
					link.l1 = "Clear... Yes, actually, I just asked. Just in case...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "I don't have a job. But if you are not busy with anything, then go to Puerto Principe - look for Captain Goodley there. He usually always has something.";
					link.l1 = "What kind of job does he have?";
					link.l1.go = "PL_Q1_2";
					//LockQuestLine(characterFromId("eng_guber")); // лочим английскую линейку
				}
			}
			if(sti(pchar.rank) >= 10 && !CheckAttribute(PChar, "questTemp.pirateVikingQuest"))	//Квест Осколок Прошлого
			{
				dialog.text = "There's a job for you. Not only did you use your sword, but your mind, I'm told. Listen. A Scandinavian appeared in our waters a couple of years ago, either a Dane or a Swede, it doesn't matter. He called himself Ragnar. His ship is just a sight to behold and the crew consists entirely of Normans. And it seems like everything is fine, he pirates little by little, earns pennies for bread, but he does not contribute a share to the common pot, he is rude to the governors, he sells prizes in general, it is not known where. Do you understand what the conversation is about?";
				link.l1 = "I understand, he needs to be punished so that he becomes an example for everyone. Where can I find this Viking?";
				link.l1.go = "pirateVikingQuest_2";
				link.l2 = "I don't like this conversation. Goodbye...";
				link.l2.go = "exit";
				pchar.questTemp.pirateVikingQuest = "0";
			}
			if(CheckAttribute(PChar, "questTemp.pirateVikingQuest") && pchar.questTemp.pirateVikingQuest == "7" && npchar.city == pchar.questTemp.pirateVikingQuest.City)
			{
				dialog.text = "I see you with the news?"
				link.l1 = "Yes, I killed this Viking, oh, and he was fierce. Usually all conversations are started as if they smell death, but this one was growling, just foaming at the mouth.";
				link.l1.go = "pirateVikingQuest_final";
			}
		break;
		case "Vopros":			//Вопросы по поводу заданий
			dialog.text = RandPhraseSimple("Well, ask it.", "What do you want?");
			link.l1 = "No questions...";
			link.l1.go = "exit";
			//поиски шебеки Синяя Птица
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = "Listen, Jackman, here's the deal... In general, did you have a Blue Bird in the port of Chebec?";
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.BlueBird == "weWon")
			{
				link.l1 = "Imagine, I've cought xebec 'Blue Bird'!";
				link.l1.go = "BlueBird_6";
			}
			//пиратская линейка
			if (pchar.questTemp.piratesLine == "KillLoy_toJackman")
			{
				link.l1 = "I'm looking for my friend Edward Law, Alexus said you have him.";
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toTavernAgain")
			{
				dialog.text = ""+ GetSexPhrase("What do you need?! I'm not in the mood to answer your questions!","What do you need, " + pchar.name + "? I'm very busy right now...") +"";
				link.l1 = "It seems that you and I have a common cause - Edward Law.";
				link.l1.go = "PL_Q3_2";
			}
			if (CheckAttribute(pchar,"questTemp.piratesLine.T1") && pchar.questTemp.piratesLine.T1 == "KillLoy_GoodWork" && !CheckAttribute(npchar, "quest.PQ3"))
			{
				dialog.text = "You returned! And not empty-handed!";
				link.l1 = "Ready to inform you that Edward Law died with horror in his eyes and your name in his ears.";
				link.l1.go = "PL_SEAWOLF";
			}
			if(CheckAttribute(pchar, "questTemp.piratesLine") && pchar.questTemp.piratesLine == "waiting_Q6") 
			{
				dialog.text = "Oh, who do I see?! I can't believe my eyes!";
				link.l1 = "Morgan sent to tell you that Captain Goodley is dead.";
				link.l1.go = "PL_Q6_1";
			}
			if(CheckAttribute(pchar, "questTemp.piratesLine") && pchar.questTemp.piratesLine == "PL_Q6_AfterBattle") 
			{
				dialog.text = "John has already told me about your operation with "+ GetSexPhrase("twin","twin") +". Did you manage to find out anything specific?";
				link.l1 = "We managed to talk, and that's all. He is was in too much of a hurry. I guess he was afraid of blurt out something unnecessary.";
				link.l1.go = "PL_Q6_after_1";
			}
			if (pchar.questTemp.piratesLine == "Panama_backToShip")
			{
				dialog.text = "Ah, glad to see you, " + pchar.name + ". Well, what do you say?";
				link.l1 = "Do you know what Morgan did in Panama?";
				link.l1.go = "PL_Q8";
			}
			//жемчужный генератор Шарпа
			if (pchar.questTemp.Sharp == "begin")
			{
				link.l1 = "Listen, there are rumors about pearl fishing in the Caribbean. Have you heard anything about this?";
				link.l1.go = "SharpPearl_1";
			}
			//поиски супер-мушкета
			if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l2 = "Listen, Jackman, does the word 'arrow' mean anything to you? Maybe one of your guys is called that, or is the pirate ship called that?";
				link.l2.go = "Mushket";
			}
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "I'm here about your prisoner.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Hello Jackman, I'm here about your errand.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "I'm here about your prisoner.";
					link.l1.go = "CapComission6";
				}
			}
		break;
		//Начало Пиратской Линейки
		case "Vstuplenie_v_Bratstvo_1":
			dialog.text = "Really? I need YOU? I think it's rather the opposite, isn't it? Listen to me, "+GetSexPhrase("son","girl")+", I've heard about your exploits here. You're showing promise, as I've been told. Perhaps you can become a legend soon! But that will only happen after someone cuts off your head. Understand, "+pchar.name+", lone wolves do not live long, especially pirates. As long as you don't have any friends, you have every chance of finding your throat slit before you have time to squeak. Now do you understand me?";
			link.l1 = "No. Not a single word. Repeat it again, this time in "+LinkRandPhrase("English", "French", "Dutch")+", okay?";
			link.l1.go = "Vstuplenie_v_Bratstvo_2";
		break;
		case "Vstuplenie_v_Bratstvo_2":
			dialog.text = "Listen, "+GetSexPhrase("son","girl")+", you're annoying asshole, but I like you. And that's the only reason I didn't order the guys to throw you into the sea with a ball tied to your leg. Now listen to me carefully. We who have joined the Brethren can live peacefully on this island, and no one will come here - neither the British, nor the French, nor the bloodthirsty Spaniards. Do you know why? Because if they come here, we'll send them straight to hell! Look overboard one day in clear weather and you'll see how many ships are resting at the bottom of this bay. This is all our job. Do you want to know how? It's just that we don't fight among ourselves until we get rid of the real threat, and we always know what's going on where. I have friends and pals everywhere, and with their help I know everything that is going on here, I keep an eye on every man, woman or child on these islands. I meet with my captains and tell them who paid for their lives and who didn't. I tell them where the fatter merchants sail, and where the Royal Navy plays its games. We help each other, and we don't break the laws of the Brethren.";
			link.l1 = "Clear. And you want me to attach to your organization?";
			link.l1.go = "Vstuplenie_v_Bratstvo_3";
		break;
		case "Vstuplenie_v_Bratstvo_3":
			dialog.text = "We call ourselves the Brethren. And we are sea brothers. To be honest, "+GetSexPhrase("guy","girl")+", I don't really care if you're with us or not. But if you're with us, I swear to you, you'll live much longer. And when trouble catches up with you, you'll know where to go.";
			link.l1 = "What do I owe you in return?";
			link.l1.go = "Vstuplenie_v_Bratstvo_4";
		break;
		case "Vstuplenie_v_Bratstvo_4":
			dialog.text = "Not so much, trust me. First of all, you must let me know if these bums are plotting something against us. And sometimes I'll give you some errands. See, it's nothing special. Unless sometimes you have to take a couple of forts, or capture a battleship. The usual pirate business, you know. Damn it, "+GetSexPhrase("guy","girl")+", you'll love it!";
			link.l1 = "So... So what do I get in this case? I join your Brethren in order to get some notorious protection from incomprehensible enemies, and in return I owe rob, betray governors, sink ships, ruin cities and get drunk with all sorts of unwashed pirates? Well, how can I refuse. I'm with you, Jackman. Where should I sign?";
			link.l1.go = "Vstuplenie_v_Bratstvo_6";
			link.l2 = "Hmm, the offer is tempting. Let me think about it for a while.";
			link.l2.go = "Vstuplenie_v_Bratstvo_5";
		break;
		case "Vstuplenie_v_Bratstvo_5":
			dialog.text = "Think as much as you want. But do it somewhere else. Can't you see that I'm busy? Come on, get out of here.";
			link.l1 = "Uh... See you later, Jackman.";
			link.l1.go = "exit";
		break;
		case "Vstuplenie_v_Bratstvo_6":
			dialog.text = "Great! Yes, and learn to talk like a real pirate, and what kind of snot is this: 'Would you be so kind...'! Ugh! Welcome to the Brethren, Captain. I'll tell the guys you're on board. They won't touch you now. But remember, Morgan is not sailing with us, so don't yawn. If he wants to get rid of you, he won't be afraid to get in the way of the Brethren. Now swim, "+pchar.name+". I don't have any errands for you right now. Let's! Get off!";
			link.l1 = "Goodbye, Jackman. I'll look in another time when you have less to do.";
			link.l1.go = "exit";
			pchar.questTemp.Vstuplenie_v_Bratstvo = true;
			pchar.questTemp.Jackman_Zadanie = true;
		break;
		//Sinistra. Пролог Анжелика Тич
		case "ATpr_F1":
			dialog.text = "Now I have no doubt about it, you are just a copy of your mother.";
			link.l1 = "Did you know my mother?";
			link.l1.go = "ATpr_F2";
			DeleteAttribute(pchar, "questTemp.AnjelikaTichPrologue7_Jackman");
		break;
		case "ATpr_F2":
			dialog.text = "Yes, everyone knew her. There was an important goose walking here, the chosen one of Blackbeard, no less. She hissed at everyone, tried to set her own rules, but no one dared to touch her.";
			link.l1 = "It looks like it really was her.";
			link.l1.go = "ATpr_F3";
		break;
		case "ATpr_F3":
			dialog.text = "Then old Edward took her away from here, and when he got tired of her, he dropped her off with his young daughter, somewhere on a desert island. That's why I least expected to see you here.";
			link.l1 = "He dropped us off at Hispaniola, less than a day later we reached the nearest settlement.";
			link.l1.go = "ATpr_F4";
		break;
		case "ATpr_F4":
			dialog.text = "Frankly, those long-ago events don't bother me much, tell me why you came now?";
			link.l1 = "Out of curiosity. I'm already leaving.";
			link.l1.go = "exit";
		break;

		//Blackthorn. Квест викинга
		case "pirateVikingQuest_2":
			dialog.text = "Somewhere. If he knew where he lived, he would go out to sea himself, he would not look at old wounds and age. You are a savvy person, you'll figure it out. One condition is that this Ragnar and his entire team must go to fish food, and I will not offend with gold.";
			link.l1 = "Wait for the news. And about the revocation of patents, if there is any news, let me know. Sometimes, " + GetFullName(npchar)+".";
			link.l1.go = "exit";

			pchar.questTemp.pirateVikingQuest = "1";
			pchar.questTemp.pirateVikingQuest.City = npchar.city;
			pchar.questTemp.pirateVikingQuest.Areal = GetArealByCityName(pchar.questTemp.pirateVikingQuest.City);
			pchar.questTemp.pirateVikingQuest.Name = GetFullName(npchar);
			pchar.LastHearedViking = npchar.city;
			AddQuestRecord("pirateVikingQuest", "1");
			AddQuestUserData("pirateVikingQuest", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateVikingQuest.City + "Gen"));
			AddQuestUserData("pirateVikingQuest", "sName", pchar.questTemp.pirateVikingQuest.Name);
		break;
		case "pirateVikingQuest_final":
			CloseQuestHeader("pirateVikingQuest");
			pchar.questdata.OskolokProshlogo = 1;
			TakeNItems(pchar, "chest", 3);
			Log_Info("You got the credit chests");
			dialog.text = "Yeah, I read it once. A berserker in sight. It's like a piece of the past. Here, take the award, you deserve .";
			pchar.questTemp.pirateVikingQuest = "end";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
		break;

		//********************* пиратка, направление на квест №1 *********************
		case "PL_Q1_2":
			dialog.text = "Yes, you can ask him when and how.";
			link.l1 = "I see...";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "toFirstQuest";
			AddQuestRecord("Pir_Line_0_Waiting", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("QuestPirate1", "officer_9", "man", "man", 20, PIRATE, -1, true));
			sld.name = "Captain";
			sld.lastname = "Goodley";
			sld.city = "PuertoPrincipe";
			sld.location	= "PuertoPrincipe_town";
			sld.location.group = "goto";
			sld.location.locator = "goto7";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "PiratesMan1";
			sld.greeting = "Gr_EvilPirate";
			sld.talker = 8; //начать диалог
			sld.TiedItems.itm1.model = "HandsItems\meet";
			sld.TiedItems.itm1.locator = "Saber_hand";
			sld.TiedItems.itm2.model = "HandsItems\cup";
			sld.TiedItems.itm2.locator = "Saber_hand";
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		break;
		//********************* пиратка, квест №3, поиски Лоу *********************
		case "PL_Q3_1":
			dialog.text = "A friend?! Ho! Hey guys! Go ahead!!!";
			link.l1 = "Did not understand!..";
			link.l1.go = "PL_Q3_fight";
		break;
		case "PL_Q3_fight":
			LAi_LocationFightDisable(&Locations[FindLocation("Pirates_townhall")], false);
			chrDisableReloadToLocation = true; // закрыть выход из локации.
            for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("QuestPir_"+i, "pirate_"+i, "man", "man", 100, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 100, 100, 100, "topor2", "pistol3", 100);
            	LAi_SetWarriorType(sld);
				LAi_SetImmortal(sld, true);
            	sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
                LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
               	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
            }
            LAi_group_SetLookRadius("PIRATE_CITIZENS", 100);
            LAi_group_SetRelation("PIRATE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("PIRATE_CITIZENS", LAI_GROUP_PLAYER, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "PL_Q3_2":
			dialog.text = "Law?! What's your deal with Law?";
			link.l1 = "I have no business with Law. He annoyed Morgan in some way, and I was assigned to settle this conflict. Now do you understand why I'm looking for him?";
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = "Hmm. Did he screw up Morgan too? I can't say that I'm very upset about this. But this scoundrel stole my brig!";
			link.l1 = "Yes, I know, the master at the shipyard told me everything.";
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = "Yeah, that's a goose! He's got sawdust all over his brain! It's necessary to figure out that I'm going to write letters to him! Yes, a hare can jump from my residence to his kennel in two jumps! And he hobbled off the next day! He wanted to get money for the fact that the brig missed.When my guys threw this planer out the door, I told him so: If there is no 'Sea Wolf', I will let the skin down alive and wrap the money in it! To make it easier to carry.";;
			link.l1 = "But he's a very good master, only it hurts to be distracted...";
			link.l1.go = "PL_Q3_5";
		break;
		case "PL_Q3_5":
			dialog.text = "Yes, I did it in a hurry. I won't touch it, no one in their right mind throws away such masters. But I'm just furious that my ship was stolen! And let Alexus tremble a little, he will be smarter next time. " +
				"So you're saying you want to kill Edward Law. As you understood, I wish it too. I want the thief to know what he's dying for... So that he knows - they don't get away with Jackman! And so that everyone knows it! That's it!!! Therefore, I want to ask you to let Law know that death came to him from me, not from Morgan, but from ME! I think you understand me.";
			link.l1 = "Okay, he'll hear it before he dies. Jackman, answer me one question.";
			link.l1.go = "PL_Q3_6";
		break;
		case "PL_Q3_6":
			dialog.text = "Which one?";
			link.l1 = "Why did you say that about Morgan? You're supposed to be friends.";
			link.l1.go = "PL_Q3_7";
		break;
		case "PL_Q3_7":
			dialog.text = "Hmm, friends... Well, I'll answer if you understand... Brethren, Gentlemen of Fortune, treasures, women, glory!  Familiar words, right? When we are young and naive, the romance of these words beckons us like moths beckoned by a candle flame... and we obediently fly towards him. " +
				"But people are all different, some of us are circling around, not daring to approach, someone is burned and flies away, someone recklessly burns, not calculating their strength. And someone whose nerves are as strong as a ramrod is reborn in this fire, and carries it on his skin, burning everything around. Hmm, I see you don't understand what I mean... Have you heard , probably the expression: 'man is a wolf to man'? So, we are all a wolf pack... "+"The pack will take prey much larger than a lone wolf. But the pack is led by the leader, who always gets a bigger piece of prey and a sweeter wolf. All wolves obey him, but wait... They're waiting for him to make a mistake! Because every wolf wants a bigger piece of prey and a sweeter wolf... That's the kind of romance.";
			link.l1 = "Hmm, I wish I hadn't asked. Moths, wolves... Whoever is stronger is right. I was and I will remain lone wolf. And let me get less than the pack, but "+ GetSexPhrase("I'll choose the wolf I want","I'll do what I decide") +".";
			link.l1.go = "PL_Q3_8";
		break;
		case "PL_Q3_8":
			dialog.text = "Ha ha ha, well run, ox"+ GetSexPhrase("k","chica") +"-a loner! And come back with the loot!";
			link.l1 = "Wait, I'll be there soon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Pir_Line_3_KillLoy", "12");
			pchar.questTemp.piratesLine = "KillLoy_2toTavernAgain";
		break;
		//после поисков Лоу
		case "PL_SEAWOLF":
			NextDiag.TempNode = "I_know_you_good";
			npchar.quest.PQ3 = true;
			int chComp;
			bool bOk = false;
			for (int i=0; i<=COMPANION_MAX; i++)
        	{
				chComp = GetCompanionIndex(pchar, i);
                if(chComp != -1 && RealShips[sti(characters[chComp].ship.type)].Name == "BrigSW1")
        		{
					bOk = true;
					break;
				}
			}
			if (bOk)
			{
				dialog.text = "These are the words I've been waiting for. I see that my brig also managed to grab it! Well done. You have proved that you are a Wolf! I respect such people!";
				link.l1 = "I am a free captain, Jackman. But your words are an honor to me!";
				link.l1.go = "PL_SEAWOLF_2";
				link.l2 = "Your words are an honor to me, Jackman! Do you want the Sea Wolf back? I think I can bring him back. I think he meant a lot to you.";
				link.l2.go = "PL_SEAWOLF_3";
				
			}
			else
			{
				dialog.text = "These are the words I've been waiting for. Well, thank you, "+ GetSexPhrase("buddy","girlfriend") +". As a reward for your efforts, I give you 20 thousand piastres!";
				link.l1 = "Thank you, Jackman! This money will be useful to me.";
				link.l1.go = "exit";
				AddMoneyToCharacter(pchar, 20000);
				AddQuestRecord("Pir_Line_3_KillLoy", "20");
				AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("","a"));
			}
		break;
		case "PL_SEAWOLF_2":
			pchar.questTemp.BrigSW_gift = true;
			dialog.text = "Therefore, with a pure heart, I give you the 'Sea Wolf', own it by right! I wish I had "+ GetSexPhrase("such a guy","such a dashing girl") +"How are you, in your team!";
			link.l1 = "Thank you from the bottom of my heart, Jackman!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "19");
		break;
		case "PL_SEAWOLF_3":
			dialog.text = "Unexpected! I didn't expect such an offer... I agree, after all, 'Wolf' holds an important place in my heart. But I can't let you go without a gift for that. Here, take it. You can't even imagine what kind of work it cost me to get it at the time, but now I'm giving it to you with a clear conscience. Use it!"; //Также, отдаю тебе один из своих кораблей. Просто так, в знак хорошего отношения.
			link.l1 = "Thank you from the bottom of my heart, Jackman!";
			link.l1.go = "exit";
			GiveItem2Character(pchar,"mushket6");
			log_info("Jackman gave you his tower blunderbuss!");
			int chComp1;
			ref swchar;
			if (RealShips[sti(pchar.ship.type)].Name == "BrigSW1")
			{
				DeleteAttribute(pchar, "ship");
				pchar.ship.name = "";
				pchar.ship.type = SHIP_NOTUSED;
			}
			else
			{
				for (int x=1; x<=COMPANION_MAX; x++)
				{
					chComp1 = GetCompanionIndex(pchar, x);
					if(chComp1 != -1 && RealShips[sti(characters[chComp1].ship.type)].Name == "BrigSW1")
					{
						swchar = &characters[chComp1];
						RemoveCharacterCompanion(PChar, swchar);
						AddPassenger(PChar, swchar, false);
						//swchar.ship.type = GenerateShipTop(SHIP_MIRAGE, true, swchar);
						break;
					}
				}
			}
			/*SetBaseShipData(swchar);
			swchar.ship.name = "Mirage";
			ref VeryRealShip = GetRealShip(sti(swchar.Ship.Type));
			DeleteAttribute(VeryRealShip,"EmblemedSails");
			DeleteAttribute(VeryRealShip,"shipsails");
			VeryRealShip.ship.upgrades.sails = 3;
			
			SetShipBermudeTuningSpeedRate(swchar);
			SetShipBermudeTuningTurnRate(swchar);
			SetShipBermudeTuningWindAgainstSpeed(swchar);
			SetShipBermudeTuningCapacity(swchar);
			SetShipBermudeTuningMaxCrew(swchar);
			SetShipBermudeTuningHP(swchar);
			SetShipBermudeTuningMastMultiplier(swchar);
			VeryRealShip.Tuning.CuBot = true;
			
			VeryRealShip.MaxCaliber = 20;
			VeryRealShip.Tuning.Cannon = true;
			VeryRealShip.CannonsQuantity = 22;
			swchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
			
			SetCharacterGoods(swchar, GOOD_BALLS, 200);
			SetCharacterGoods(swchar, GOOD_GRAPES, 400);
			SetCharacterGoods(swchar, GOOD_KNIPPELS, 200);
			SetCharacterGoods(swchar, GOOD_BOMBS, 400);;
			SetCharacterGoods(swchar, GOOD_FOOD, 1000);
			SetCharacterGoods(swchar, GOOD_MEDICAMENT, 500);
			SetCharacterGoods(swchar, GOOD_POWDER, 2000);
			SetCharacterGoods(swchar, GOOD_WEAPON, 300);
			
			SetCrewQuantityFull(swchar);
			AddCrewMorale(swchar, 100);
			ChangeCrewExp(swchar, "Sailors", 100);
			ChangeCrewExp(swchar, "Cannoners", 100);
			ChangeCrewExp(swchar, "Soldiers", 100);*/
			AddQuestRecord("Pir_Line_3_KillLoy", "19_2");
			AddQuestUserData("Pir_Line_3_KillLoy", "sSex2", GetSexPhrase("","a"));
		break;
		
		//********************* пиратка, квест №6. двойник *********************
		case "PL_Q6_1":
			dialog.text = "That's it, then... The news is not pleasant... And how did it happen?";
			link.l1 = "I killed him at Morgan's residence... You see, the story here is so unpleasant. On his instructions, I removed John Avory's , but it turned out that this was Morgan's confidant.";
			link.l1.go = "PL_Q6_2";
		break;
		case "PL_Q6_2":
			dialog.text = "Is Avory dead too?";
			link.l1 = "Yeah... In general, in the end, Goodley refused to admit at Morgan's confrontation that he was the one who hired me for Avory. It's good that Henry found out something beforehand, and I didn't have to prove that I'm not a camel.";
			link.l1.go = "PL_Q6_3";
		break;
		case "PL_Q6_3":
			dialog.text = "Ha, well done! Don't you know that you also captured Sid Bonnet, one of my caps, and handed him over to Spaniards?";
			link.l1 = "Me?!!";
			link.l1.go = "PL_Q6_4";
		break;
		case "PL_Q6_4":
			dialog.text = "Yes, that's what the rumors are. That's why I was a little taken aback to see you here.";
			link.l1 = "The Devil!! That's not enough yet!";
			link.l1.go = "PL_Q6_5";
		break;
		case "PL_Q6_5":
			dialog.text = "Go to Cozumel Bay, north of Belize. John Leeds is standing by the bay on the frigate Antwerp, he has problems with the crew there. I think it will be very interesting for you to visit him...";
			link.l1 = "Okay, Jackman, I'll do it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "2");
			AddQuestUserData("Pir_Line_6_Jackman", "sSex", GetSexPhrase("","a"));
			pchar.questTemp.piratesLine = "PL6Brother_toSantaCatalina";
			//ставим Джона Лидса в залив Косумель
			sld = GetCharacter(NPC_GenerateCharacter("JohnLids", "officer_10", "man", "man", 30, sti(pchar.nation), -1, true));
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, "Antwerpen", CANNON_TYPE_CULVERINE_LBS24, 80, 60, 60);
			sld.name = "John";
			sld.lastname = "Leeds";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "First time";
			sld.DeckDialogNode = "JohnLids";
			sld.Abordage.Enable = false;
			sld.AnalizeShips = true;
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true;
			sld.Ship.Mode = "Pirate";
			sld.greeting = "Gr_MiddPirate";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			Group_AddCharacter("LidsGroup", "JohnLids");
			Group_SetGroupCommander("LidsGroup", "JohnLids");
			Group_SetAddress("LidsGroup", "Beliz", "quest_ships", "Quest_ship_11");
			Group_SetTaskNone("LidsGroup");
		break;

		case "PL_Q6_after_1":
			dialog.text = "It's bad. There's some kind of trail behind you, it's full of curiosities. So far, luck is on your side, but if you stumble, then it's over! Morgan won't help you.";
			link.l1 = "I understand. "+ GetSexPhrase("Twin","'Sister'") +" clearly knew something... We must try to find out who is behind all this.";
			link.l1.go = "PL_Q6_after_2";
		break;
		case "PL_Q6_after_2":
			dialog.text = "True. Well, it's good that you dropped by to see me, clarified some important details, so to speak. Now go to Morgan, tell him about your "+ GetSexPhrase("m double","th 'sister'") +".";
			link.l1 = "Yes, it would be nice... Tell me, Jackman, what did you think when you heard that I handed over Sid Bonnet to Spaniards?";
			link.l1.go = "PL_Q6_after_3";
		break;
		case "PL_Q6_after_3":
			dialog.text = "Hmm, but you don't want to know that... You're just lucky that Leeds locked up "+ GetSexPhrase("twin","'sister'") +" at Belize, and "+ GetSexPhrase("that man","that girl") +", that passed Bonnet, couldn't appear here as soon as you.";
			link.l1 = "Understood. So you're really lucky.";
			link.l1.go = "exit";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "5");
			pchar.questTemp.piratesLine = "PL_Q6_AfterBattle_2";//фикс повторных диалогов на ту же тему
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_begin");
			sld = characterFromId("Henry Morgan");
			LAi_SetHuberTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
		break;


		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = "I've heard, but I don't really know anything about it. Our beloved and respected Captain Sharp specializes in these fields! He's a big pearl lover, ha ha ha!";
			link.l1 = "Where can I find him, this Sharp?";
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
		break;
		case "SharpPearl_2":
			dialog.text = "I don't know. Captain Sharp is the elusive Joe. Although you needed it.In general, you need to look for him in brothels.";
			link.l1 = "Thank you, Jackman.";
			link.l1.go = "exit";
		break;

        //********************** поиски Синей птицы ***********************
        case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat("Mmm, the famous has become a trough, needless to say... And why do you need this xebec?",
				"We've already talked about this xebec.",
				"The same thing again?",
                "What?! Again?! Well, I've had enough...", "repeat", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes, you see, one group of comrades is very interested in her...",
				"Yes, Jackman, that's right.",
                "Hmm, I got the notes mixed up, sorry...",
				"Ouch!..", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
  		break;
		case "BlueBird_2":
			dialog.text = "Hehe, aren't they merchants? And then I heard that they get a lot from this 'Blue Bird'.";
			link.l1 = "Merchants are really interested in this xebec. But, you know, I like that kind of 'feathered one' you can't get away from. Is this an ideal privateer sailboat in its essence!";
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = "Ha, that's right! You're not the first one to aim at her from the Brethren, but no one has caught her yet. As for me, I personally am not interested in this 'bird' - it's too small for serious business.";
			link.l1 = "Jackman, so you know where xebec is?";
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = "No, of course not. I saw it in the surrounding waters, but I did not enter the port.";
			link.l1 = "Can you share your thoughts on where to look?";
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = "No, I've already thought about it. Not a single sound thought.";
			link.l1 = "Understood. Well, thanks for that too, buddy.";
			link.l1.go = "exit";
		break;

		case "BlueBird_6":
			dialog.text = NPCStringReactionRepeat("Hmm, congratulations. Great luck, damn it! Well done.",
				"Congratulations again.",
				"I've already heard that...",
                "Ha, you're a braggart, "+ GetSexPhrase("buddy","girlfriend") +", what the Caribbean has not seen yet!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thank you, Jackman. A kind word and a cat is pleased...",
				"Thanks again, Jackman.",
                "Oh, yeah...",
				"Proud of it!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
        //********************** Английская линейка ***********************
 		case "EngLine_quests":
			dialog.text = "Glad to see an English privateer on my island. Tell me what you need.";
			link.l1 = "I have a job for you. The customer is the Governor-General of Jamaica.";
			link.l1.go = "Step_1";
  		break;

 		case "Step_1":
			dialog.text = "Very interesting, go on.";
			link.l1 = "Madiford needs an attack on Curacao, and we will not be hindered by the wealth of the merchants of this city. There are now many Protestant merchants in Curacao who refused to try on the inquisitorial 'Spanish boot' and left Spain and Portugal for Holland. And where there are merchants, there is a lot of gold. I suggest combining business with pleasure.";
			link.l1.go = "Step_2";
  		break;

 		case "Step_2":
			dialog.text = "Heh... It sounds tempting, but I will refuse.";
			link.l1 = "And what is the reason for the failure?";
			link.l1.go = "Step_3";
  		break;

 		case "Step_3":
			dialog.text = "The fact is that besides merchants with their gold, there are many Dutch soldiers in Curacao with their muskets and cannons in the embrasures of the fort.";
			link.l1 = "Spanish soldiers don't scare you much...";
			link.l1.go = "Step_4";
  		break;

 		case "Step_4":
			dialog.text = "The only thing that scares me is the condition of my liver. But, you see, it's a sacred thing to open the belly of a Spaniard, and I won't recruit many people to bleed a Dutchman. So without me.";
			link.l1 = "Maybe you'll think about it?";
			link.l1.go = "Step_5";
  		break;

 		case "Step_5":
			dialog.text = "I have said my word. And give Madiford my regards.";
			link.l1 = "As you know. Have a nice day.";
			link.l1.go = "exit";

            AddQuestRecord("Eng_Line_2_Talking", "4");
            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")   {pchar.questTemp.State = "after_talks_with_pirates";}
            NextDiag.TempNode = "First time";
  		break;

 		case "Lets_go_bussines":
			dialog.text = "Glad to see you, " + pchar.name + ". By what fate on Bermudes?";
			link.l1 = "I'm on business. Morgan and I are attacking Belize, will you take part in the case?";
			link.l1.go = "Step_6";
  		break;

 		case "Step_6":
            if (GetCompanionQuantity(pchar) != 4)
            {
    			dialog.text = "Heh, my corvette is on the raid, the team is manned, I'm ready.";
    			link.l1 = "Then we will act immediately!";
    			link.l1.go = "Step_7";
            }
            else
            {
    			dialog.text = "You have a set without me, so without me this time.";
    			link.l1 = "Well, as you know, be healthy.";
    			link.l1.go = "exit";
                NextDiag.TempNode = "First time";
            }
  		break;

 		case "Step_7":
			AddQuestRecord("Eng_Line_3_Morgan", "4");
            LAi_SetActorType(npchar);
            LAi_ActorSetStayMode(npchar);
            ChangeCharacterAddressGroup(npchar, "Pirates_townhall", "goto", "governor1");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 10, false);
            Fantom_SetBalls(npchar, "pirate");
            npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
            pchar.questTemp.CompanionQuantity = makeint(sti(pchar.questTemp.CompanionQuantity) + 1);
            pchar.questTemp.CompanionQuantity.Jackman = true;
            NextDiag.TempNode = "Have_hot_bussines";
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

  		break;

	 	case "Have_hot_bussines":   // Если геймеру вдруг захочется ещё пообщаться, не знаю, сможет ли. Но на всякий случай.
			dialog.text = "Damn it, time is working against us!";
            link.l1 = "Let's hurry up!";
			link.l1.go = "exit";
            NextDiag.TempNode = "Have_hot_bussines";
  		break;

	 	case "Gold_found_in_fort":    // Нода разговора в форте Куманы
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman") && !IsCompanion(characterFromID("Jackman")))
    		{
            	dialog.text = "You saw everything - my corvette was sunk by the damn Spaniards! But it doesn't matter, the team almost completely got away with it and we continued to fight on land\n"+
                              "And the compensation for our labors will be gold. Heh, the damn Spaniards tried to hide the gold. But you were right, the gold was here. More than three tons of gold is ours!!!"+
                              "I say this, but my soul sings. I would have said such words for ages.";
            }
            else
            {
    			dialog.text = "Damn Spaniards, they tried to hide the gold. But you were right, the gold was here. More than three tons of gold are ours!!!"+
                              "I say this, but my soul sings. I would have said such words for ages.";
            }
            link.l1 = "And I would have listened for ages!";
			link.l1.go = "Step_8";
        break;

	 	case "Step_8":
			dialog.text = "Haha... You are a good corsair, " + GetFullName(pchar) + ". I wish you good luck, "+ GetSexPhrase("friend","girlfriend") +". "+
                          "My thugs are rushing home after a good job. Know that Bermudes is always happy to see you.";
			link.l1 = "See you again!";
			link.l1.go = "Step_9";
        break;

	 	case "Step_9":
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
        break;
        //********************** Голландская линейка ***********************
 		case "HolLine8_quest":
			dialog.text = "I'm listening to you, why did you come to me?";
			link.l1 = "I have arrived here on business, I'm looking for a pirate who tried to sell an unusual Bible.";
			link.l1.go = "Step_H8_1";
  		break;
 		case "Step_H8_1":
			dialog.text = "Damn, there was something... I can't remember... But someone was definitely bragging about a rare book, saying that it was Christian...";
			link.l1 = "So what?";
			link.l1.go = "Step_H8_2";
  		break;
 		case "Step_H8_2":
			dialog.text = "Nothing. I don't remember, there was a glimpse of the conversation... And we didn't have time for the Bible -we were having fun in a brothel, after all!";
			link.l1 = "Hmm, which brothel?";
			link.l1.go = "Step_H8_3";
  		break;
 		case "Step_H8_3":
			dialog.text = "What's in Fort de France.";
			link.l1 = "Understood... Thank you, Jackman.";
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_8_SeekBible", "3");
			pchar.questTemp.State = "SeekBible_toFFBrothel";
			NextDiag.TempNode = "First time";
  		break;
		//********************* Французская линейка *********************
        case "FraLine8_talk":
            dialog.text = "Wow, captain " + GetFullName(pchar) + " granted! I am very glad! Spit it out - I can see that you can't wait to tell me something interesting.";
            link.l1 = "In general, I will not offer anything particularly interesting. It is only necessary to refuse to participate in the upcoming war between England and Holland.";
            link.l1.go = "Step_F8_1";
        break;
        case "Step_F8_1":
            dialog.text = "Yeah, really nothing interesting. Moreover, I wasn't going to get involved in this case myself. Touching the Dutch is a stupidity that only a complete idiot would do. So your patrons made you take an extra detour.";
            link.l1 = "Not superfluous. At least I found out about your neutrality from you personally, not from a third party.";
            link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count)+1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "5");
        break;
		//********************* Пиратская линейка *********************
		case "PL_Q8_deck":
			dialog.text = "You're wasting your time on my deck. We need to go to Porto Bello urgently!";
			link.l1 = "Yes, I remember...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = "Hmm, you're wasting your time again, I don't understand you...";
			link.l1 = "It's okay, don't worry, Jackman.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;

		case "PL_Q8":
			dialog.text = "I know, of course...";
			link.l1 = "What do you say about this?";
			link.l1.go = "PL_Q8_1";
		break;
		case "PL_Q8_1":
			dialog.text = "I won't say anything. Anyway, I'm giving up on privateering. So don't bother me with these things anymore.";
			link.l1 = "Damn, how is that?!";
			link.l1.go = "PL_Q8_2";
		break;
		case "PL_Q8_2":
			dialog.text = "That's it! Anyway, I've told you my word!";
			link.l1 = "Hmm, I see...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Panama_inEngland";
		break;
		//поиски супер-мушкета
		case "Mushket":
			dialog.text = "Hmm, there is such a vessel - a very good brig, perhaps the best in the archipelago. Only it's not driven by my man, but by a psycho named Albert Sievert. If I had figured him out right away, I would never have allowed Master Alexus to build such a boat for him.";
			link.l1 = "What's wrong with him? I need to find him.";
			link.l1.go = "Mushket_1";
			DeleteAttribute(pchar, "questTemp.mushket2x2");
		break;
		case "Mushket_1":
			dialog.text = "I'm not an assistant here - he's on his own. Rumor has it that he is saving up gold to return to Europe. I wanted to put him on the case, but he sent two of my messengers to the bottom, and I stopped looking for him. And, of course, he stopped coming to Bermudes.But to other ports too - his brig is too noticeable, so he drags an anchor along the bays, and changes all the goods for gold from smugglers. So, none of my people associate with him, if I find out, I'll personally anchor him.";
			link.l1 = "Yeah... Can you recommend something?";
			link.l1.go = "Mushket_2";
		break;
		case "Mushket_2":
			dialog.text = "There was a man who went with this Sievert in a couple. But something didn't stick, either Sievert left him overboard or vice versa. They're both the same, otherwise they probably wouldn't have. This little tavern in Porto Bello now holds, Rolando Pizarro's name is, or simply - Fox. He may know the locations of parking lots. And besides, look for that brig at sea, you'll never mistake it for anyone. Just be careful - he's really crazy...";
			link.l1 = "Clear. Well, thank you, Jackman.";
			link.l1.go = "exit";
			pchar.questTemp.mushket2x2_stid = true;
			AddQuestRecord("SeekDoubleMushket", "2");
		break;

		//*************************** Квест "Orion fluyt accompaniment"Орион"" **********************
        case "Andre_Abel_Quest_Jackman_Dialog_1":
			dialog.text = "What do you need from me, " + pchar.name + "?";
			link.l1 = "I'm on business, Jackman...";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_2";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_2":
			dialog.text = "Tell me what your case is.";
			link.l1 = "I don't even know how to start... Anyway, I think you remember a merchant named Andre Abel?";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_3";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_3":
			dialog.text = "Abel?! Ha-ha... Well, has this rascal come to his senses?! Did you bring my share of him?";
			link.l1 = "No, I didn't. Thanks to your efforts, he's completely broke right now, and he's asking you to stop harassing him. He's even thinking of shutting down the business altogether.";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_4";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_4":
			dialog.text = "Who's going to stop me from chasing him? You?! Do you think I do not know that he has changed ships and is now stuck in Port-au-Prince?! Have you decided that you can cheat me?!Keep it short, even if he doesn't hope to escape. I won't rest until I get everything I'm owed.";
			link.l1 = "Well, it's up to you, of course."+ GetSexPhrase(" Just don't forget that the Earth is round and the sea is big...","") +"";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_5";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_5":
			dialog.text = ""+ GetSexPhrase("What did you say?! Are you trying to threaten me in my own residence?! Guys, come on, throw this young man the hell out of here!","Well, of course I do, and who else! Is that all you have, or do you want to say something else?") +"";
			link.l1 = ""+ GetSexPhrase("What are you, Jackman? What are the threats? I just reminded you that everything is the will of Providence.","That's it. Come on, Jackman.") +"";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_6";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoFunctionReloadToLocation("Pirates_town", "reload", "reload3", "Andre_Abel_Quest_After_First_Jackman_Dialog");
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_7":
			dialog.text = "You again? If you didn't bring me money from Abel, it's better to turn around the overstay right away and don't piss me off.";
			link.l1 = "Not money, but a letter from Morgan.";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_8";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_8":
			dialog.text = "Hmm, a letter from Morgan? Well, give it here!";
			link.l1 = "Hold...";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_9";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_9":
			dialog.text = "The devil! That Abel again?! Well, let him live for now, I have more important things to do.";
			link.l1 = "That's great.";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_10";
			TakeItemFromCharacter(PChar, "letter_1");
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_10":
			dialog.text = "Just pass it on "+ GetSexPhrase("to your friend","to him") +"that I do not forgive offenses! So don't let him catch my eye if he wants to live..."+ GetSexPhrase("Now get lost, along with your Abel!","") +"";
			link.l1 = "I will pass everything as it is. "+ GetSexPhrase("Have a nice stay","Bye, Jackman") +".";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_11";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_11":
			DialogExit();
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("Andre_Abel_Quest", "22");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","a"));
			PChar.QuestTemp.Andre_Abel_Quest_Complete = true;
		break;

		//*************************** Генератор "The Captain's order is a Ransom" **********************
		case "CapComission1":
			dialog.text = "Ho-ho. Do you think I have only one prisoner? Name who exactly do you have in mind?";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Is there one?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Was. I sold it to that damn Barbadian planter, Colonel Bishop, who stopped by last week.";
				link.l1 = "Damn it...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, finally. I was thinking of selling it to that damn Barbadian planter, I'm supposed to have it in a week or two... Did you bring a buy back?";
				link.l1 = "Listen, Jackman, here's the deal... In general, I don't have enough money. But I'm ready towork out.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "It's good that I didn't sell it. Here's the money-150,000 gold. Where can I pick it up?"
					link.l2.go = "CapComission2_3";
				}
			}
		break;

		case "CapComission2_1":
			dialog.text = "You've been wandering for too long... By the way, how does this slave get to you? I remember paying a ransom to his relatives.";
			link.l1 = "Yes, I came on behalf of these relatives.";
			link.l1.go = "CapComission2_11";
		break;

		case "CapComission2_11":
			dialog.text = "Well, you'r late - what can I do?";
			link.l1 = "Listen, how much did you sell for, if it's not a secret?";
			link.l1.go = "CapComission2_12";
		break;

		case "CapComission2_12":
			dialog.text = "Uh, it's not a secret, of course, but I won't tell you. Otherwise you'll laugh, ha-ha-ha-ha... Well, goodbye.";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;

		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Hmm-hmm... I have something to do... I don't even know how to start... In general, we need to sink one arrogant pirate.";
				link.l1 = "Isn't it possible to remove it in the jungle?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Well, " + pchar.name + ", you know that's not how things are done. Come with the money and you'll get your pickle, hehe.";
				link.l1 = "Well, see you later.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Well, you know, that's not how serious things are done... I don't need his death, I need to discourage those who are too zealous from gaping at my part of the prey. Although, if he goes to the octopuses, I won't be upset.";
			link.l1 = "Why don't you send your people after him?";
			link.l1.go = "CapComission2_2_2";
		break;

		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Hmm... In general, a certain " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " convinced some of the pirates that our hiding place is near " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + " there is also their share. They recently weighed anchor on two ships '" + pchar.GenQuest.CaptainComission.ShipName1 + "' and '" + pchar.GenQuest.CaptainComission.ShipName2 + "' went to " + sLoc + ". Do you understand now why I can't entrust this matter to my people?";
			link.l1 = "Understood. And how much time do I have?";
			link.l1.go = "CapComission2_2_3";
		break;

		case "CapComission2_2_3":
			dialog.text = "I think 12-15 days, no more. It is important to me that they do not have time to get to the cache, otherwise there will be no point in drowning them with valuable cargo on board. They'd better bring him here.";
			link.l1 = "Okay, I'm taking this case. I'll try to make it.";
			link.l1.go = "CapComission2_2_4";
		break;

		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips";
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";
			DialogExit();
		break;

		case "CapComission2_3":
			dialog.text = "Don't worry. My men will bring him aboard for you. Who is he to you?";
			link.l1 = "Nobody. I'm running an errand for his relative.";
			link.l1.go = "CapComission2_31";
		break;

		case "CapComission2_31":
			dialog.text = "Ah, that's good. I was already upset that I had sold out by setting such a low price for your man. Ha ha ha ha... Well, goodbye.";
			link.l1 = "Have a nice day.";
			link.l1.go = "CapComission2_32";
		break;

		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			DialogExit();
		break;

		case "CapComission3":
			dialog.text = "So, " + GetFullName(pchar) + ", did you sink my buddy to the bottom? Heh heh heh...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "No. I didn't have time to catch up with them. And I didn't come across them on the way back.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")
			{
				link.l1 = "Yes, as agreed - sent him to feed the sharks.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;

		case "CapComission4":
			dialog.text = "Damn! Caught - not caught, what difference does it make now? Well, what do you propose next?";
			link.l1 = "Maybe you have some simpler errand?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Listen, Jackman, give me this prisoner cheaper...";
			link.l2.go = "CapComission4_2";
		break;

		case "CapComission4_1":
			dialog.text = "No.";
			link.l1 = "...Well, then have a nice stay...";
			link.l1.go = "CapComission4_3";
		break;

		case "CapComission4_2":
			dialog.text = "Cheaper?!! I just lost my hiding place because of your slowness! And now I can give it up for more! Take it for 200,000 if you want.";
			link.l1 = "It's expensive... Goodbye...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Damn it, keep your money.";
				link.l2.go = "CapComission4_5";
			}
		break;

		case "CapComission4_3":
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","la"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;

		case "CapComission4_4":
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;

		case "CapComission4_5":
			dialog.text = "You can take the starving one...";
			link.l1 = "Have a nice stay.";
			link.l1.go = "CapComission4_6";
		break;

		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission5":
			dialog.text = "Ho ho! That's a job! Take your baby and be healthy.";
			link.l1 = "Thank you. Have a nice stay.";
			link.l1.go = "CapComission5_1";
		break;

		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission6":
			dialog.text = "Did you bring a buy back? After all, I wasn't joking when I said I would sell it to the planters.";
			link.l1 = "Listen, "+ NPChar.name +", here's the deal... In general, I don't have enough money. But I'm ready towork out.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "It's good that I didn't sell it. Here's the money-150,000 gold. Where can I pick it up?"
				link.l2.go = "CapComission2_3";
			}
		break;

		// ============== Грабёж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery in broad daylight!!! What is going on?! Well, wait, "+ GetSexPhrase("buddy","girlfriend") +"...", "Hey, what are you doing there?! No way, you decided to rob me? Well, then you're finished...", "Wait, where are you going? You are a thief! Well, consider that you have sailed, bitch...");
			link.l1 = LinkRandPhrase("Devil!!", "Carramba!!", "Oh, damn!");
			link.l1.go = "PL_Q3_fight";
		break;

		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Get out","Get out") +"out of here!", "Get out of my house!");
			link.l1 = "Ah...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "You shouldn't distract me from the case with empty appeals. From now on, the result may be more deplorable...";
        			link.l1 = "I got it.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("You've really tired me out, no communication.", "I don't want to communicate with you, so you better not bother me.");
			link.l1 = RandPhraseSimple("Well, as you know...", "Hmm, well...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "I hope you won't bore me with empty conversations in the future, otherwise I'll have to kill you. I admit, it will be very unpleasant for me.";
        			link.l1 = "Jackman, you can be sure I won't...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Pirates_town","reload","reload3");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================

		// ======================== Чёрные паруса ===============>>>>>>>>>>>>>>>
		case "Jackman_Defeated":
			sld = CharacterFromID("gatri_temp");
			sld.location.locator = "goto6";

			dialog.text = "Come to mock me?";
			link.l1 = "Not at all. I'm just curious, why did Guthrie let you live?";
			link.l1.go = "Jackman_Defeated_1";
		break;
		case "Jackman_Defeated_1":
			dialog.text = "This sly bitch wants to use me as a puppet ruler. She knows that the Brethren will crumble when they hear about my death, because they certainly will not go after a woman"+ GetSexPhrase(".","... no offense.") +" Even if she is as harsh as Guthrie. But this way she can manage everything, through me.";
			link.l1 = "And are you satisfied with this arrangement?";
			link.l1.go = "Jackman_Defeated_2";
		break;
		case "Jackman_Defeated_2":
			dialog.text = "You're asking! Yes, I'll smash this whore against the wall at the first opportunity! Don't think Jackman has given up, I'll get mine back.";
			link.l1 = "I advise you to keep your voice down, otherwise you will reveal all your plans to Guthrie. Well, goodbye.";
			link.l1.go = "Jackman_Defeated_exit";
		break;
		case "Jackman_Defeated_exit":
			npchar.Dialog.Filename = "Mayor\Jackman.c";
			NextDiag.CurrentNode = "I_know_you_good";
            DialogExit();

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_3_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;
		// <<<<<<<<<<<<============= Чёрные паруса =============================
	}
}
