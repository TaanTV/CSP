// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "Do you have business with me? No? Then "+ GetSexPhrase("get out of here", "please don't distract me.") +"";
			link.l1 = "I'm already leaving.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = "Richard, I heard that you are gathering people for an action against the Spaniards. I wanted to take part in this.";
				link.l1.go = "PL_Q7_1";
			}


			if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
			{
				link.l2 = "Can you find a job for me?";
				link.l2.go = "pirateStartQuest";
			}
			else
			{
				if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many") && npchar.city == pchar.questTemp.pirateStartQuest.City)
				{
					link.l2 = "I'm on the trail, but I need the money - 30,000 piasters to lure a rat out of its hole.";
					link.l2.go = "pirateStartQuest_many";
				}
				if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0 && npchar.city == pchar.questTemp.pirateStartQuest.City)
				{
					link.l2 = "Look at what kind of letter I found on the corpse of one of the smugglers.";
					link.l2.go = "pirateStartQuest_info_1";
				}
				if(pchar.questTemp.pirateStartQuest == "5" && npchar.city == pchar.questTemp.pirateStartQuest.City)
				{
					link.l2 = "The job is done. Norman Vigo and his tub went to the sea devil.";
					link.l2.go = "pirateStartQuest_final";
				}
			}
			if(sti(pchar.rank) >= 10 && !CheckAttribute(PChar, "questTemp.pirateVikingQuest"))
			{
				link.l3 = "Is there any interesting case for me?";
				link.l3.go = "pirateVikingQuest";
			}
			else
			{
				if(pchar.questTemp.pirateVikingQuest == "7" && npchar.city == pchar.questTemp.pirateVikingQuest.City)
				{
					dialog.text = "I see you with the news?"
					link.l1 = "Yes, I K, oh, and he was fierce. Usually all conversations are started as if they smell death, but this one was growling, just foaming at the mouth.";
					link.l1.go = "pirateVikingQuest_final";
				}
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//Blackthorn. Квест викинга
		case "pirateVikingQuest":
			dialog.text = "There's a job for you. Not only did you use your sword, but your mind, I'm told. Listen. A Scandinavian appeared in our waters a couple of years ago, either a Dane or a Swede, it doesn't matter, he called himself Ragnar. His ship is just a sight to behold and the crew consists entirely of Normans. And it seems like everything is fine, he pirates little by little, earns pennies for bread, but he does not contribute a share to the common pot, he is rude to the governors, he sells prizes in general, it is not known where. Do you understand what the conversation is about?";
			link.l1 = "I understand, you need to punish him so that he becomes an example. That's just not according to the laws of the Brethren like that. Well, the pirate has gone too far, so let someone whisper to the authorities where he lives. And no one will make any claims against us, honest corsairs.";
			link.l1.go = "pirateVikingQuest_1";
			link.l2 = "I don't like this conversation. Goodbye...";
			link.l2.go = "exit";
			pchar.questTemp.pirateVikingQuest = "0";
		break;
		case "pirateVikingQuest_1":
			dialog.text = "Laws of Brethren, Code, pirate honor... Pfft... It's a childish prank. You also remember the Libertalia that Sharp tried to build. Ha ha! Here we have a balance of power, the authorities turn a blind eye to our business, if we do not interfere with their business. And what if peace is signed in Europe? So the patents will be revoked, and all the brave privateers will become criminals in an instant. And the punitive squadrons will arrive. To catch you and me. And captains like this Viking spoil the reputation of all of us. Are you smart?";
			link.l1 = "I understand, you gave me food for thought. Where can I find this Viking?";
			link.l1.go = "pirateVikingQuest_2";
		break;
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

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hmm... a job, you say? And it's even very good that you came to me. I just need someone from the outside. I need to find out something in the neighboring settlement, and my guys are known there like crazy. I don't promise a lot of money, but something will fall over.";
			link.l1 = "That's nice. What's the deal?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Sorry, I won't risk a penny. Goodbye...";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "And the thing is this - about a month ago I conspired with the captain of the schooner Sentblue to deliver 200 slaves to sell them to a planter from a neighboring settlement. The deadlines have already become tight, and the customer is nervous, and yesterday I was informed that this schooner was seen in the waters of the island. But!.. The captain didn't show up. And today the planter demanded to return the deposit and said that the slaves were offered to him elsewhere - although more expensive, but the whole lot at once.";
			link.l1 = "So what? I owe to get 200 slaves in a matter of days, so that you don't lose the deposit? And all this for pennies?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "No, of course. Do I look like an idiot? I won't return the deposit anyway. But I need proof that the slaves he's been given are my party. And you just find the ones who offered him a new deal, and you get your 10,000 piastres. The rest is my concern. So, you do?";
			link.l1 = "I'll take it! And who could it be? Do you have any thoughts?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "No. I'm sorry, I don't know who, I don't know where and I only charge 10,000.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "If I had even a hint, I would have done without your services. They would have been fishing for squid by nightfall. But I'm more interested in something else - how did they find out about the Sentblue cargo and about my customer? It all worked out very quickly for them. Are you smart?";
			link.l1 = "Yes, clearly someone is peddling information.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Here! So I'm looking for him. Therefore, quietly slaughtering competitors and returning slaves is not the main thing in this case. I need an informant, or rather, his head on a spit. Now do you understand why none of my people should know about this assignment? Until I find out who is selling the information, I will suspect everyone. And I really don't want that...";
			link.l1 = "Understood... So, we will act quietly and not raise a wave. I'm going on a search.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Thirty thousand, you say? That's a lot of money... I can only give you 5,000 piastres, that's all I have right now. But if you want to run away with them, I will find them and hang them on the nearest fence! With me, such jokes will not work.";
			link.l1 = "Give me five thousand...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Here you go. I'm waiting for the search results.";
			link.l1 = "Everything will be fine.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Great news! I was sure you could handle it. I got some very interesting information.";
			link.l1 = "I've done my job. I want to get my ten thousand.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Of course, here is the promised reward. But don't rush, I want to entrust you with another case. Pfiefer is a man from the Norman Vigo team who rides the Septim lugger. I'm sure Norman Vigo is the informant, even though he's one of ours. He was recently seen in the waters of the island, your job is to send the rat to the sea devil. The first time you didn't let me down, so now I'm going to leave it to you. 15,000 piastres. Deal?";
			link.l1 = "I'll take it! Consider the traitor Norman Vigo already dead.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "You know what, I don't want to get involved in this... And there's no time. I'm sorry, but I'll pass.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			pchar.questdata.TravlyaKrys = 1;
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "We know-we know. My people watched the fight and have already reported to me how well you managed. Well, you did your job properly, Here is the promised reward of 15,000 piastres. And thanks to you, great help me.";
			link.l1 = "Everything is fine, I'm glad to help! And now I have things to do, I've already delayed here. See you later!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			pchar.questdata.TravlyaKrys = 1;
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;

		//пиратка, квест №7
		case "PL_Q7_1":
			dialog.text = "Tell me your name.";
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "PL_Q7_2";
		break;
		case "PL_Q7_2":
			dialog.text = "Hehe, not"+ GetSexPhrase("are you Morgan's henchman, buddy", "are you Morgan's girlfriend, huh") +"?";
			link.l1 = "I work for Henry, what does it have to do with "+ GetSexPhrase("henchman", "'girlfriend'") +"?";
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = "And despite the fact that you are not suitable for me. Hey, on watch! Come on, everyone over here! Bring down that six...";
			link.l1 = "Why are you doing this?";
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			pchar.questTemp.piratesLine = "Soukins_FightinResidence";
			for (i=1; i<=5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("questPirate_"+i, "pirate_"+i, "man", "man", 25, PIRATE, 10, true));
				FantomMakeCoolFighter(sld, 25, 70, 70, "blade26", "pistol6", 20);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;
		case "PL_Q7_5":
			dialog.text = "What the hell are you doing barging in here uninvited?!! Ah, I think I know you... Hey, on watch, come on, everyone over here! Bring down "+ GetSexPhrase("this henchman", "this Morgan litter") +"!";
			link.l1 = "Hey, hey, what's up?!";
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			pchar.questTemp.piratesLine = "Soukins_FightinResidence";
			for (i=1; i<=5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("questPirate_"+i, "pirate_"+i, "man", "man", 25, PIRATE, 10, true));
				FantomMakeCoolFighter(sld, 25, 70, 70, "blade26", "pistol6", 20);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;
		//пиратка, квест №8
		case "PL_Q8_deck":
			dialog.text = "And how did Morgan manage to put it"+ GetSexPhrase("such a blockhead", "girl") +" to command a squadron? I can't imagine...";
			link.l1 = "Hmm, you shouldn't do that, Richard.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = "There you go again. That's what I'm talking about!";
			link.l1 = "Don't worry about me.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;

		case "PL_Q8_deck_2":
			dialog.text = "So what are you doing on my deck again? Do you think if you successfully stormed Porto Bello, you'll be able to walk here in peace?";
			link.l1 = "...";
			link.l1.go = "PL_Q8_deck_3";
		break;
		case "PL_Q8_deck_3":
			dialog.text = "Listen, you should get out of here... I have nothing to talk about with you. Everything will be decided in Panama, let everyone there show what they are capable of.";
			link.l1 = "What are you talking about?";
			link.l1.go = "PL_Q8_deck_4";
		break;
		case "PL_Q8_deck_4":
			dialog.text = "I'm not going to give you a report, you're not my friend. So get the hell out of here.";
			link.l1 = "Okay, goodbye. If you don't want to talk...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_5";
			npchar.DeckDialogNode = "PL_Q8_deck_5";
		break;
		case "PL_Q8_deck_5":
			dialog.text = "I don't want to talk to you!";
			link.l1 = "Hmm, well, that's understandable...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_5";
			npchar.DeckDialogNode = "PL_Q8_deck_5";
		break;
		//в бухте Дарьенский залив
		case "Shore48":
			dialog.text = "Well, we got to the bay. Now we need to move through the jungle. My people and I are ready, we can go ahead.";
			link.l1 = "Okay, I get it.";
			link.l1.go = "Shore48_1";
		break;
		case "Shore48_1":
			LAi_LocationFightDisable(&Locations[FindLocation("Shore48")], false);
			chrDisableReloadToLocation = false;
			LAi_SetWarriorTypeNoGroup(npchar);
			NextDiag.TempNode = "Shore48_over";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Shore48_over":
			dialog.text = "What are we waiting for? Come on, move your ass to Panama!!";
			link.l1 = "Hmm, that's for sure...";
			link.l1.go = "exit";
		break;
		//после штурма у стен Панамы
		case "PQ8_exitTown":
			dialog.text = "What do you need?";
			link.l1 = "Listen, I know you won't like to hear this, but Morgan ordered me to kill you when we were walking through the jungle.";
			link.l1.go = "PQ8_exitTown_1";
		break;
		case "PQ8_exitTown_1":
			dialog.text = "And you think I'll believe you?";
			link.l1 = "You may not believe it, but it's true.";
			link.l1.go = "PQ8_exitTown_2";
		break;
		case "PQ8_exitTown_2":
			dialog.text = "You've climbed more than once into my business, messed up my plans. You are Morgan's puppy. And now you want to take a look at me, or what?";
			link.l1 = "Fuck you, Richard... You idiot!";
			link.l1.go = "PQ8_exitTown_3";
		break;
		case "PQ8_exitTown_3":
			dialog.text = "Of course I'll go... To Panama. But you won't enter the city. So get out of here while you're safe...";
			link.l1 = "The Devil!..";
			link.l1.go = "exit";
			LAi_warrior_DialogEnable(npchar, false);
		break;
	}
}
