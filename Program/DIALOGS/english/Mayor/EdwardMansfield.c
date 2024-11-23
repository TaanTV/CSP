// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting() + "! I'am "+ GetFullName(NPChar) + ", the new viceroy in this hellhole. Unfortunately, to call to order the local rabble is quite difficult, but the threat from them to the Spanish colonies will no longer be.";
					Link.l1 = "Glad to see you. I am the captain " + GetFullName(Pchar) + ". I have to go now.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting() + ". I'm busy, I have a lot to do. I need to control the mood of the locals in order to stop the threat to Spain's colonies.";
					Link.l1 = "I won't bother you.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("Do you have a case for me? No? Then "+ GetSexPhrase("get out of here!","please don't distract me.") +"",
	                         "I think I've made myself clear...", "Although I've made myself clear, but you keep distracting me!",
	                         "Hmm, you're a bit "+ GetSexPhrase("humpty, mon cher","cheeky, girl") +"...", "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("I'm already leaving.",
	                                               "Yes, " + npchar.name + ", quite clearly.",
	                                               "I'm sorry, " + npchar.name + "...",
	                                               "Ai, ai...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
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
							link.l2 = "I'm on the trail, but I need money - 30,000 piastres to lure a rat out of a hole.";
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
							link.l1 = "Yes, I killed this Viking, oh, and he was fierce. Usually all conversations are started as if they smell death, but this one was growling, just foaming at the mouth.";
							link.l1.go = "pirateVikingQuest_final";
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
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
			dialog.text = "No, of course not. Do I look like an idiot? I will not refund the deposit in any case. But I need proof that the slaves they're giving him are my party. And you'll just find those who offered him a new deal, and you'll get your 10,000 piastres. The rest is my concern. Well, are you ready?";
			link.l1 = "I'll take it! And who could it be? Do you have any thoughts?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "No. It's unclear who to look for, it's unclear where, and for only 10,000 - sorry, I won't take it.";
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
			dialog.text = "Thirty thousand, you say? That's a lot of money... I can only give you 5,000 piastres, I don't have any more right now. But if you decide to run away with them, I'll find them and hang them on the nearest fence! Such jokes won't work with me.";
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
			dialog.text = "Of course, here is the promised reward. But don't rush, I want to assign you one more case. Pfiefer is a man from Norman Vigo's team who rides the lugger Septima. I'm sure Norman Vigo is the informant, even though he's one of ours. He was recently seen in the waters of the island, your job is to send the rat to the sea devil. The first time you didn't let me down, so now I want to entrust this case to you. I will pay 15,000 piastres. Agree?";
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
			dialog.text = "We know-we know. My people watched the fight and have already reported to me how well you managed. Well, you did your job properly, here is the promised reward of 15,000 piastres. And thank you, you helped me a lot.";
			link.l1 = "Everything is fine, I'm glad to help! And now I have things to do, I've already delayed here. See you later!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			pchar.questdata.TravlyaKrys = 1;
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;

		//********************* Английская линейка *********************
 		case "EngLine_quests":
			dialog.text = "I'm listening to you, Captain.";
			link.l1 = "I have arrived to you on behalf of the Governor-General of Jamaica, Sir Thomas Madiford.";
			link.l1.go = "Step_1";
  		break;
 		case "Step_1":
			dialog.text = "I'm listening carefully.";
			link.l1 = "Sir Thomas Madiford asks you to assemble a privateer squadron, lead it and attack the Dutch outpost in the Caribbean - the city of Curacao.";
			link.l1.go = "Step_2";
  		break;
 		case "Step_2":
			dialog.text = "Hmm... And what is the reason for this decision? I admit, it looks strange. The British do not attack the Dutch. Yes, the states have contradictions in trade expansion, but they extend to the Indian Ocean. There is a New World here.";
			link.l1 = "Sir, another trade war has broken out between England and Holland. Moreover, the British navy attacked the Dutch off the coast of Europe, but was repulsed.";
			link.l1.go = "Step_3";
  		break;
 		case "Step_3":
			dialog.text = "Understood. Thank you for the information. I didn't know that.";
			link.l1 = "So, I am waiting for your consent to the expedition.";
			link.l1.go = "Step_4";
  		break;
 		case "Step_4":
			dialog.text = ""+ GetSexPhrase("My friend, I","I") +" cannot give you a positive answer to the request of the Governor General of Jamaica.";
			link.l1 = "Now I think your answer is very strange.";
			link.l1.go = "Step_5";
  		break;
 		case "Step_5":
			dialog.text = "Nothing strange. My real name is Edward Mansvelt. I'm Dutch.";
			link.l1 = "But you are an English privateer, and you enjoy the patronage of Sir Thomas Madiford. It seems unreasonable to me to refuse his request so categorically.";
			link.l1.go = "Step_6";
  		break;
 		case "Step_6":
			dialog.text = "Anything can seem to you. I do have an English letter of marque, but this does not mean that I will cut the throats of my compatriots. The right to choose actions is always mine. I have answered you, I have nothing more to say. Goodbye.";
			link.l1 = "Well, if you have nothing more to say, then goodbye.";
			link.l1.go = "exit";
            NextDiag.TempNode = "First time";
            AddQuestRecord("Eng_Line_2_Talking", "3");

            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")
			{
				pchar.questTemp.State = "after_talks_with_pirates";
			}
  		break;
 		case "No_Mansfield_first_time":
			dialog.text = "Good afternoon, my name is Alistair Goode. After Mansfield's death, I was chosen to lead the Buccaneers.";
			link.l1 = "Let's get to know each other, Alistair.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "I don't have time to talk to you right now. Come back later.";
			link.l1 = "I'm already leaving.";
			link.l1.go = "exit";
  		break;
		//********************* Голландская линейка *********************
  		case "HolLine3_WormEngPlans":
			dialog.text = "What brought you to me?";
			link.l1 = "I have arrived to you on behalf of the Governor-General of Curacao, Peter Stuyvesant.";
			link.l1.go = "Step_H3_1";
        break;
 		case "Step_H3_1":
			dialog.text = "Very good. What does Governor General Stuyvesant want from me?";
			link.l1 = "Edward, the British have attacked the Netherlands, another trade war has begun.";
			link.l1.go = "Step_H3_2";
  		break;
 		case "Step_H3_2":
			dialog.text = "Sad news, I have business in Port Royal...";
			link.l1 = "Here is the package from Stuyvesant, please read it.";
			link.l1.go = "Step_H3_3";
  		break;
 		case "Step_H3_3":
			dialog.text = "So, let's see... Hmm, he asks me to inform him about what Madiford wants to do in the Caribbean as part of participating in the war.";
			link.l1 = "That's right. Knowing this is a vital necessity for Dutch settlements.";
			link.l1.go = "Step_H3_4";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
  		break;
 		case "Step_H3_4":
			dialog.text = "The thing is, I do not know anything about Madiford's plans for this war. I have a different order of business with him, politics has nothing to do with it.";
			link.l1 = "And what should I say to Stuyvesant? That you don't know anything and can't help your homeland in a difficult hour?";
			link.l1.go = "Step_H3_5";
  		break;
 		case "Step_H3_5":
			dialog.text = "No need for pretentious expressions, "+ GetSexPhrase("young man","girl") +", I know who I am. But I really don't know anything about Madiford's plans. However, here's what I'll tell you. "+
                          "Just last week, a certain messenger from Madiford came to me, who persuaded me to organize an expedition to Curacao. Naturally, I refused. Morgan, Jackman and John Morris also refused. "+
                          "It turns out that the famous rascal Thomas Madiford tried to open hostilities against the Netherlands with the help of pirates. Heather, what else can you say...";
			link.l1 = "It turns out that Madiford is planning to attack Curacao?";
			link.l1.go = "Step_H3_6";
  		break;
 		case "Step_H3_6":
			dialog.text = "He can plan an attack on Curacao, but he is unlikely to carry out this event. He does not have enough strength for such an operation, he was not trying to attract corsairism from a good life. "+
                          "And in general, the most reliable protection of Port Royal from the same Spaniards is the constant presence of a certain number of pirates on the Jamaica raid. So no, Curacao is too much for him right now.";
			link.l1 = "Well, everything is clear, there is no need to fear an attack...";
			link.l1.go = "Step_H3_7";
  		break;
 		case "Step_H3_7":
			dialog.text = "I would not think so categorically. The fact is that since there was an attempt to attract corsairs to the attack, it means that Madiford still has an order to open hostilities. So there will definitely be no peace here between England and Holland. "+
                          "Here's what I suggest you do-go immediately to Port Royal to Henry Morgan.";
			link.l1 = "To Henry Morgan, Admiral of the Corsairs?";
			link.l1.go = "Step_H3_8";
  		break;
 		case "Step_H3_8":
			dialog.text = "Yes, that's right. And don't worry, he didn't become an admiral without my participation. To be precise, it was I who gave him this title. Ask him to help you on my behalf.";
			link.l1 = "And will it help?";
			link.l1.go = "Step_H3_9";
  		break;
 		case "Step_H3_9":
			dialog.text = "If he can help, he will do it.";
			link.l1 = "Edward, would you write me a letter for Morgan so that he would believe my words?";
			link.l1.go = "Step_H3_10";
  		break;
 		case "Step_H3_10":
			dialog.text = "No, it's not necessary. It is unlikely that anyone in their right mind will mislead Morgan, such a person will not live long. He'll believe you.";
			link.l1 = "Edward Mansveld, you are a true son of your Fatherland. Thank you for your help!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
    		pchar.questTemp.State = "WormEnglPlans_toMorgan";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "2");
    		QuestSetCurrentNode("Henry Morgan", "HolLine3_fromMansfield");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
            LAi_SetHuberStayType(characterFromId("Henry Morgan"));
          break;


// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Get out","Get out") +"out of here!", "Get out of my house!");
			link.l1 = "Oh-oh-oh...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "You shouldn't bother me, remember that.";
        			link.l1 = "I got it, Edward, I won't do it anymore.";
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
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
