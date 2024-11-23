// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question, " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Are we going to ask questions again?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yes, really for the third time...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "BlackLabel_toLaVega")
			{
				link.l1 = "Tell me, buddy, does Edward Law live in your town?";
				link.l1.go = "PL_Q2_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = "Buddy, I'm back to you... Tell me, where did Edward Law go? I need him urgently...";
				link.l1.go = "PL_Q3_1";
			}
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_LeFrancuaTaverna_1")) //Квест "Strange things are happening in the archipelago"
			{
				link.l1 = "I am interested in whether a black frigate named 'Mephisto' entered the bay?";
				link.l1.go = "PKM_SvtvA_1";
			}

			//-->ОЗГ
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if (pchar.questTemp.Headhunter == "vector_barmen")
				{
					link.l1 = "Good afternoon. I was sent by your friend, one of the smugglers. He said that you are looking for a person to do some kind of task.";
					link.l1.go = "Barmen_check";
					break;
				}

				if (npchar.city == "LeFransua" && pchar.questTemp.Headhunter == "barmen_wait")
				{
					link.l1 = "Good afternoon, " + npchar.name + ". It's me again. What do you say about your assignment?";
					link.l1.go = "Barmen_check";
					break;
				}
				if (pchar.questTemp.Headhunter == "hunt_carlos_yes")
				{
					link.l1 = "Good afternoon, " + npchar.name + ". I have good news. Carlos the Cashier is destroyed.";
					link.l1.go = "Endtaskhunt_1";
				}
				if(pchar.questTemp.Headhunter == "next_task_2" && GetQuestPastDayParam("pchar.questTemp.Headhunter_next_task_2") > 9)
				{
					link.l1 = "Good afternoon, " + npchar.name + ". I'm here, as we agreed. Did you get any useful information?";
					link.l1.go = "Givetaskhunt_2";
				}
				if (pchar.questTemp.Headhunter == "hunt_houm_yes")
				{
					link.l1 = "Good afternoon, " + npchar.name + ". I managed to send Hannibal Holm to fish food, even though it wasn't easy.";
					link.l1.go = "Endtaskhunt_2";
				}
				if(pchar.questTemp.Headhunter == "next_task_3" && GetQuestPastDayParam("pchar.questTemp.Headhunter_next_task_3") > 14)
				{
					link.l1 = "Hello, " + npchar.name + ". I hope I'm on time?";
					link.l1.go = "Givetaskhunt_3";
				}
				if (pchar.questTemp.Headhunter == "hunt_rat_yes1")
				{
					link.l1 = "I have arrived with good news, " + npchar.name + ". I managed to lure the Rat out. I cought his ship, and sent him himself to Davy Jones.";
					link.l1.go = "Endtaskhunt_3";
				}
				if (pchar.questTemp.Headhunter == "hunt_rat_yes2")
				{
					link.l1 = "I have arrived with good news, " + npchar.name + ". I managed to lure the Rat out. I sent him to Davy Jones along with his ship.";
					link.l1.go = "Endtaskhunt_3";
				}
				if(pchar.questTemp.Headhunter == "next_task_4" && GetQuestPastDayParam("pchar.questTemp.Headhunter_next_task_4") > 17)
				{
					link.l1 = "Greetings, " + npchar.name + ". Here I am. What's the news?";
					link.l1.go = "Givetaskhunt_4";
				}
				if (pchar.questTemp.Headhunter == "hunt_halen_yes")
				{
					link.l1 = "Martin van Halen will no longer disturb the peace of the inhabitants of Le Francois, " + npchar.name + ".";
					link.l1.go = "Endtaskhunt_4";
				}
				if(pchar.questTemp.Headhunter == "hunt_ja_yes")
				{
					link.l1 = "Good afternoon, " + npchar.name + ". He's really kind today. The Ja Preston gang is done for good.";
					link.l1.go = "Endtaskhunt_5";
				}
			}
		break;
		//Квест "Strange things are happening in the archipelago"
		case "PKM_SvtvA_1":
			dialog.text = "Are these crazy? Yes, they were here, but I would not advise you to contact them. The ponies had a fight with some guy here, so in an instant they painted him a new smile, I didn't even have time to blink.";
			link.l1 = "Thanks for the warning, but I need to find them.";
			link.l1.go = "PKM_SvtvA_2";
		break;
		case "PKM_SvtvA_2":
			dialog.text = "I can't help you here - these guys have gone somewhere. But I heard that the church from Fort de France was interested in the guys in red robes. You should go there and find out about everything there.";
			link.l1 = "I will do that. Thank you, my friend!";
			link.l1.go = "exit";
			AddQuestRecord("PKM_Animists", "7");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_LeFrancuaTaverna_1");
			pchar.questTemp.PKM_SvtvA_FortFranceChurch_1 = "Church1";
		break;
		
		//пиратка, квест №2, чёрная метка для Лоу
		case "PL_Q2_1":
			dialog.text = NPCStringReactionRepeat("How can he not live? He lives very much.",
				"I already told you that he lives.",
				"Lives, lives...",
                ""+ GetSexPhrase("Tired", "Tired") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("How do I find it, can you tell me?",
				"Yes, yes, I understand...",
                "Understood.",
				"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q2_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q2_2":
			dialog.text = "Why not tell me? I'll tell you, "+ GetSexPhrase("to a good person", "to such a beautiful girl") +" and it's nice to prompt.It's quite easy to find it. You need to leave the tavern, turn right and go all the way. The clapboard house is Edward Law's house.";
			link.l1 = "Thank you, buddy!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_2_BlackLabel", "2");
		break;
		//пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat("Uh, "+ GetSexPhrase("you're late, buddy", "you're late, girlfriend") +". He's gone out of town, completely gone.",
				"I already told you that Law left the city.",
				"He's gone, he's gone...",
                "Oh, and what are you like"+ GetSexPhrase("annoying", "annoying") +"!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Where did he go?",
				"Yes, I remember.",
                "Yes, "+ GetSexPhrase("I forgot", "I forgot") +"...",
				"I understand, I'm leaving...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = "Who knows?  I sold everything urgently and left... The main thing is that he didn't take the barrel, but asked for it. Put aside a cask of Jamaican rum for me, he says. He must have been in a hurry. Well, never mind, I've already attached the barrel...";
			link.l1 = "Wait a minute with your barrel. You'd better tell me where to look for him now?";
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = "Oh, I don't know... They say he went to buy a ship. You ask the people, maybe someone saw something, maybe someone knows something. And I don't know, because he didn't come to me for a keg. And there was a good barrel...";
			link.l1 = "Understood... Thank you, my friend.";
			link.l1.go = "exit";
		break;

		case "Barmen_check":
			if (IsEquipCharacterByItem(Pchar, "patent_eng") || IsEquipCharacterByItem(Pchar, "patent_fra") || IsEquipCharacterByItem(Pchar, "patent_spa") || IsEquipCharacterByItem(Pchar, "patent_hol"))
			{
				dialog.text = "You do not belong to the Brethren - you are a patented privateer. I can't trust you, I'm sorry.";
				link.l1 = "Oh, it's a pity!";
				link.l1.go = "exit";
				CloseQuestHeader("Headhunt");
				pchar.questdata.Kondotier = 1;
				pchar.questTemp.Headhunter = "end_quest";
				break;
			}
			if (sti(Pchar.Rank) < 5)
			{
				dialog.text = "Ahem... I have a job, but I'm afraid you won't be able to do it. Don't be offended, I just don't want you to die senselessly. Come back later when you have more experience.";
				link.l1 = "Understood. Well, I'll look you up later.";
				link.l1.go = "exit";
				pchar.questTemp.Headhunter = "barmen_wait";
				break;
			}
			/* if (sti(Pchar.Rank) > 12)
			{
				dialog.text = "Um... I'm sorry, but I've already found someone to do this job. So don't blame me, Captain.";
				link.l1 = "Clear. So it's not fate. Goodbye.";
				link.l1.go = "exit";
				pchar.questTemp.Headhunter = "end_quest";
				break;
			} */
			dialog.text = "You are very timely! I need a captain like you. Let me tell you the essence of the problem, and then we will proceed directly to the task.";
			link.l1 = "I'm listening to you carefully, "+ npchar.name +".";
			link.l1.go = "barmen_history";
		break;

		case "barmen_history":
			dialog.text = "In general, the story is as follows. As you probably know, every hunter and Buccaneer settlement has its own chapter. Edward Mansfield runs La Vega, Sawkins runs Puerto Principe, Morgan's right-hand man Jackman runs Bermudes, and Bartholomew Rogers runs ours. Each head of the settlement is known and respected in the Brethren and has held his posts for a long time, but everything has its beginning and its end. The peaceful existence in our settlement has also come to an end. A gang of notorious scoundrels and thugs decided to take advantage of the situation and take Le Francois into their own hands.  They not only intimidate fishermen and settlers by collecting tribute from them, but also force them to do more... decent people, deduct their profits to them!These worthy people can't do anything... Do you understand, Captain? And our head, Bartholomew Rogers, either does not see this, or prefers not to see it - it is unclear to me, but it is quite obvious that despite the complaints received, he did not take any action. Moreover, he accused the discontented people of trying to beg for a reduction in deductions to the treasury of the Brethren. Morgan is far away and busy with political intrigues in Port Royal, Mansfield is not interested in anything but his buccaneers, Sawkins is mired in strife within the Brethren, and Jackman does not care about anything at all, except the completeness of his a purse! Thus, we were all left to be torn to pieces by a bunch of dirty crooks.\n Moreover, these worthy people are sure that everything that is happening is just the beginning, the first step towards the redistribution of influence in Martinique. The next one will be the displacement of Rogers himself, and then it is unknown.";
			link.l1 = "Um... And why don't these worthy people you're talking about send a messenger to Morgan to inform the Admiral about the outrage that's going on here?";
			link.l1.go = "barmen_history_1";
		break;

		case "barmen_history_1":
			dialog.text = "Eh, "+ GetSexPhrase("sir", "miss") +", if only it were that simple. Morgan doesn't care what's going on in our godforsaken settlement right now. They tried to attract his attention more than once, but there was no result, so decent people, oppressed by scoundrels, decided to act independently. They are looking for a man, a pirate, who has no fame in the Brethren, and they are ready to pay him adequately.";
			link.l1 = "I take it we are already moving directly to discussing my role in the planned campaign?";
			link.l1.go = "barmen_history_2";
		break;

		case "barmen_history_2":
			dialog.text = "Yes, that's right. Since the heads of the pirates are inactive, and there is no way to put up with the current state of affairs, it was decided to answer the scoundrels in their own language. To find and destroy the whole gang one by one, that's why I'm looking for the right person. Are you ready to get involved in this case? The payment will be generous, I guarantee you.";
			link.l1 = "That is, as I understand it, I have to be some kind of bounty hunter?";
			link.l1.go = "barmen_history_3";
		break;

		case "barmen_history_3":
			dialog.text = "That's right. You're not afraid of the sight of blood, are you? Especially if this blood is fully paid for, and not only in gold.";
			link.l1 = "Can I find out the amount of the reward before I give my consent?";
			link.l1.go = "barmen_history_4";
		break;

		case "barmen_history_4":
			dialog.text = "Absolutely. Dear and worthy people, about whom I have told you for so long, offer as a reward to the one who tracks down and sends all the scoundrels to hell, a sum of money in the amount of one hundred thousand piastres and a magnificent set of weapons and equipment, which includes a Thanat, a musket, an exclusive spyglass, an officer's cuirass and a rat god. What do you say?";
			link.l1 = "Yes, the reward is substantial. I think I'll take this case.";
			link.l1.go = "barmen_history_5";
			link.l2 = "Is that all? Do you want me to stand up to a gang that has taken over an entire settlement, for these pennies and pathetic trinkets?! Look for the fool elsewhere.";
			link.l2.go = "exit_quest";
		break;

		case "exit_quest":
			dialog.text = "Sorry. It looks like I was wrong about you. Then let's forget about this conversation.";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "end_quest";
			pchar.questdata.Kondotier = 1;
			CloseQuestHeader("Headhunt");
		break;

		case "barmen_history_5":
			dialog.text = "Great! I am very glad that you agreed. In addition to the aforementioned remuneration for all the work, I am supposed to give you some kind of reward for each of the gang members individually, in order to at least partially compensate for your overhead costs, the guys rarely get together, and attacking them in this case would be too risky. Therefore, you will hunt them down one by one.";
			link.l1 = "Well, let's get down to business. Tell us in more detail, what do you know about this gang? Maybe there will be some tips?";
			link.l1.go = "barmen_history_6";
		break;

		case "barmen_history_6":
			dialog.text = "Of course. It will be extremely difficult and dangerous to cope with them, even in this way, because you will be provided with all possible assistance in terms of information. Through my humble persona, you will receive information about the whereabouts of the villains and eliminate them separately, not only mercenaries and pirate captains, but also completely strange personalities who trade their dark deeds in our murky waters. They are headed by a certain Ja Preston. It is rumored that he is captain of the elusive frigate Acheron, the scourge of Caribbean traders that has been on everyone's lips lately. And I have every reason to believe that this is exactly the case.";
			link.l1 = "It turns out that the list of victims will be long...";
			link.l1.go = "barmen_history_7";
		break;

		case "barmen_history_7":
			dialog.text = "Yes. Although in fact he is even bigger – after all, many have their own ships with full crews of desperate thugs, and one of them – his name won't tell you anything yet – is at all a person close to the authorities, with very, very serious connections. But, again, they can be caught singly. Ponies are constantly moving around the Caribbean, so tracking them down is not the easiest thing to do. But there are a lot of sailors and a lot of rum in my tavern, which means that I have a lot of drunken, chatty sailors, hehe... So I can help you with something.";
			link.l1 = "Well, so far everything is clear to me. You don't have to name your 'worthy people' anymore, but I'm much more interested in my future victims.";
			link.l1.go = "Givetaskhunt_1";
		break;

		case "Givetaskhunt_1":
			SelectCarlosCity();
			dialog.text = "Well, then let's get started. The first person you need to track down is Carlos Cashier, he is a mercenary, and as far as I know, he is currently in the city. " + pchar.questTemp.Headhunter.Cityname + ". I'm ready to bet my tavern against a leaky hat: you can easily find this scoundrel either in a tavern or in a brothel - now he must be spending the stolen money on swill and girls. He killed a man who refused to pay him here in the settlement, and this, by the way, was the last straw. When you meet with him, try to arrange everything so that it looks like a duel - you don't want problems with the authorities, do you? For the sake of saving his skin, the Cashier will do anything – but play on his pride, insult and force him to accept the challenge, and do not reveal your intentions – you will scare him off once, then you will not find a link he owns well, but remember – whatever you do, do not expect fair play from him, this is a mercenary, not a noble.";
			link.l1 = "Well, then I won't waste any time. I'm on my way!";
			link.l1.go = "Givetaskhunt_1_1";
			pchar.questTemp.Headhunter = "hunt_carlos";
			pchar.questTemp.Headhunter.Chance = rand(1);
			CreateCarlos();
		break;

		case "Givetaskhunt_1_1":
			dialog.text = "I wish you good luck. And one more thing: for any question related to this case, please contact me only. Decent people... whom you and I are helping, we would like to keep our names secret, in case of unforeseen circumstances.";
			link.l1 = "I got it. See you soon, " + npchar.name + "!";
			link.l1.go = "exit";
            AddQuestRecord("Headhunt", "1");
			AddQuestUserData("Headhunt", "sCity", pchar.questTemp.Headhunter.Cityname);
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("", "a"));
		break;

		case "Endtaskhunt_1":
			dialog.text = "Great! There is one less scoundrel in this world. We have prepared compensation for your efforts here. Take five thousand in cash and this chest of gold. Come back in ten days-I should have information that can help you find the next scoundrel.";
			link.l1 = "Thanks for the gold! And see you in ten days.";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "next_task_2";
			SaveCurrentQuestDateParam("pchar.questTemp.Headhunter_next_task_2");
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "chest", 1);
			Log_Info("You got a credit chest");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Headhunt", "3");
		break;

		case "Givetaskhunt_2":
			if (IsEquipCharacterByItem(Pchar, "patent_eng") || IsEquipCharacterByItem(Pchar, "patent_fra") || IsEquipCharacterByItem(Pchar, "patent_spa") || IsEquipCharacterByItem(Pchar, "patent_hol"))
			{
				dialog.text = "You no longer belong to the Brethren - you are now a patented privateer. I can't trust you, I'm sorry.";
				link.l1 = "Oh, it's a pity!";
				link.l1.go = "exit";
				CloseQuestHeader("Headhunt");
				pchar.questdata.Kondotier = 1;
				pchar.questTemp.Headhunter = "end_quest";
				break;
			}
			pchar.questTemp.Headhunter.Chance = rand(4);
			pchar.questTemp.Headhunter.Chance1 = rand(1);
			SelectHoumCity();
			dialog.text = "Yes. As I said before, you can learn anything from drunken sailors. I recently managed to learn something about Hannibal Holm. He is a former slave, cunning, treacherous and ruthless. They say he eats the hearts of his enemies according to the wild customs of his tribe... br-r-r. So here. He recently attacked a Dutch trading caravan carrying silver. Many good Yasineists presented themselves to the Lord in that fierce battle. And now he is hiding from the Dutch in the English colonies. More precisely, alas, I can not say – ask in the ports about his ship – 'Deadhead'. This is a noticeable hefty vessel – I'm sure it will be difficult to miss it, I think the Hill has already bought a place in the sun from the British for the captured silver, so the authorities will cover it – be ready.";
			link.l1 = "The task is clear. I'm lifting the anchor!";
			link.l1.go = "Givetaskhunt_2_1";
		break;

		case "Givetaskhunt_2_1":
			pchar.questTemp.Headhunter = "Houm";
			AddQuestRecord("Headhunt", "4");
			//Log_Info("Home in is in "+pchar.questTemp.Headhunter.Cityname+"");
			DialogExit();
		break;


		case "Endtaskhunt_2":
			dialog.text = "Excellent. I'm glad I didn't make a mistake about you. Here is your reward. Come see me in two weeks - my colleagues and I are currently collecting information on the third scoundrel.";
			link.l1 = "Okay. I'll be there in two weeks.";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "next_task_3";
			SaveCurrentQuestDateParam("pchar.questTemp.Headhunter_next_task_3");
			AddMoneyToCharacter(pchar, 10000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("You got the credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Headhunt", "9");
		break;

		case "Givetaskhunt_3":
			dialog.text = "Glad to see you, " + pchar.name + ". The next case is dangerous anyway. Moreover, here you will have to act more with cunning than with a sword.";
			link.l1 = "Well, I wouldn't say that the previous two 'cases' were like an easy walk... I'm listening to you carefully.";
			link.l1.go = "Givetaskhunt_3_1";
		break;

		case "Givetaskhunt_3_1":
			if (IsEquipCharacterByItem(Pchar, "patent_eng") || IsEquipCharacterByItem(Pchar, "patent_fra") || IsEquipCharacterByItem(Pchar, "patent_spa") || IsEquipCharacterByItem(Pchar, "patent_hol"))
			{
				dialog.text = "You no longer belong to the Brethren - now you are a patented privateer. I can't trust you, I'm sorry.";
				link.l1 = "Oh, it's a pity!";
				link.l1.go = "exit";
				CloseQuestHeader("Headhunt");
				pchar.questdata.Kondotier = 1;
				pchar.questTemp.Headhunter = "end_quest";
				break;
			}
			dialog.text = "The next client is Mathias Green, better known as the Rat. He's a nasty guy, looks like a harmless trader, but he's already got dozens of missing ships on his conscience. They just disappear, and then rumors spread through the taverns that this very 'Rat' got to them. Moreover, rumors with an accurate description of the cargo, and the ships themselves, this scoundrel hides perfectly, but does not forget to start rumors about his adventures every time - he is vain, a scoundrel. Only those who have been on them and seen the holds with their own eyes can know in such detail the amount of cargo and the description of the missing ships... Do you understand where I'm going? Moreover, he leaves no living witnesses.";
			link.l1 = "Anything about the location of this... Can you tell the rats?";
			link.l1.go = "Givetaskhunt_3_2";
		break;

		case "Givetaskhunt_3_2":
			dialog.text = "Unfortunately, not much. I can't even tell which ship he's on-the rat often changes vessels, covering his tracks. I can only name the ports from which the last three missing ships left, and to the disappearance of which, as we believe, the Rat is involved – maybe it's worth finding out more about the circumstances that preceded the sad events of these cities: Willemstad, on Curacao, Cartagena, on the Main, and Port of Spain, on the island Trinidad and Tobago.";
			link.l1 = "That's something! I think it's time for me to hit the road.";
			link.l1.go = "Givetaskhunt_3_3";
		break;

		case "Givetaskhunt_3_3":
			dialog.text = "Take these inconspicuous clothes - they will help you move stealthily in enemy cities, and before you leave, I want to give you some tips. Mathias is a cunning beast, try to understand him, what and how he hunts. Let the Rat make a move when you overtake him. If you show aggression, the authorities may consider your actions a gratuitous attack, because it is unlikely that this creature walks under the Jolly Roger in the open. Lure him out with what he is interested in, and beat him when he is sure that he has won, but remember one more thing: A rat, even cornered, can be deadly. That's probably all, Captain. Good hunting.";
			link.l1 = "Thanks for the clarification. Wait for me with good news.";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "Rat";
			pchar.questTemp.Headhunter.count = 0;
			pchar.questTemp.Headhunter.countC = 0;
			pchar.questTemp.Headhunter.countV = 0;
			pchar.questTemp.Headhunter.countP = 0;
			AddQuestRecord("Headhunt", "11");
			TakeNItems(pchar, "suit_1", 1);
			Log_Info("You got the rags");
			PlaySound("interface\important_item.wav");
		break;

		case "Endtaskhunt_3":
			dialog.text = "Great job, " + pchar.name + ". I sincerely admire you. Not only do you know how to fight, but you are also very cunning. Deceiving a Rat is more than a difficult task. Also, you've dealt with it. Here is your money and a small gift, come in fifteen or twenty days - I think by this time enough information will have been collected about the whereabouts of another scoundrel.";
			link.l1 = "Thank you! I will be there at the specified time. Good luck!";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "next_task_4";
			SaveCurrentQuestDateParam("pchar.questTemp.Headhunter_next_task_4");
			AddMoneyToCharacter(pchar, 20000);
			TakeNItems(pchar, "chest", 2);
			TakeNItems(pchar, "Totem_"+(rand(9)+1), 1);
			Log_Info("You got the credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Headhunt", "25");
		break;

		case "Givetaskhunt_4":
			if (IsEquipCharacterByItem(Pchar, "patent_eng") || IsEquipCharacterByItem(Pchar, "patent_fra") || IsEquipCharacterByItem(Pchar, "patent_spa") || IsEquipCharacterByItem(Pchar, "patent_hol"))
			{
				dialog.text = "You no longer belong to the Brethren-you are now a patented privateer. I can't trust you, I'm sorry.";
				link.l1 = "Oh, it's a pity!";
				link.l1.go = "exit";
				CloseQuestHeader("Headhunt");
				pchar.questdata.Kondotier = 1;
				pchar.questTemp.Headhunter = "end_quest";
				break;
			}
			dialog.text = "There is news. This time, by the way, the information is very clear. We found out where the fourth member of the gang, the Dutchman Martin van Halen, will be in the near future. He is due to arrive from another pirate raid in Willemstad within a week. You need to go to Curacao...";
			link.l1 = "Well, you don't have to waste time wandering around the archipelago like last time. That's good.";
			link.l1.go = "Givetaskhunt_4_1";
		break;

		case "Givetaskhunt_4_1":
			dialog.text = "Wait, Captain, that's not all. Martin van Halen is not just a pirate, but a privateer in the service of Holland, in addition, he is a member of Stevesant himself. He covers up for the rest of the scoundrels and provides them with connections at the very top of society. This vjunosh is arrogant and arrogant, but at the same time very careful. I do not think that he will succumb to any tricks, perhaps, in this case he will have to act simply by brute force. But be careful - if you attack Halen in the open, you will have to fight with the entire garrison of Willemstad.";
			link.l1 = "Okay, I'll take that into account. See you later, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "hunt_halen";
			AddQuestRecord("Headhunt", "26");
			SetFunctionTimerCondition("Headhunter_HalenOver", 0, 0, 10, false);
		break;

		case "Endtaskhunt_4":
			dialog.text = "I'm glad. Damn it, I'm glad you agreed to help us. You are truly an irreplaceable person, " + pchar.name + ". Here is your reward - money and a gift. And...";
			link.l1 = "Wait, " + npchar.name + ". We have problems. More precisely, I have problems. So far, it's just me. Ja Preston somehow found out about WHO was destroying his people. In Willemstad, hirelings sent by them tried to kill me.";
			link.l1.go = "Endtaskhunt_4_1";
			AddMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			TakeNItems(pchar, "Totem_"+(rand(9)+1), 1);
			Log_Info("You got the credit chests");
			PlaySound("interface\important_item.wav");
		break;

		case "Endtaskhunt_4_1":
			dialog.text = "Oh my God, really... Did he find out? That's it, then we're finished. These... Were the killers from Ja? How did you know that he was the one who sent them? What did they look like?";
			link.l1 = "Heh... Before they attacked me, they sent their regards to me... from Ja Preston. Did they look like? All in black, with hats and headscarves on their faces.";
			link.l1.go = "Endtaskhunt_4_2";
		break;

		case "Endtaskhunt_4_2":
			dialog.text = "Yes. These are his people. There is no doubt about it. And I was already beginning to hope...";
			link.l1 = "" + npchar.name + ", calm down. So far, Jah has sent them only after my soul, and I can quite stand up for myself. The fact that you are still alive means that he does not yet know about your participation, and those very 'worthy people' you were talking about.";
			link.l1.go = "Endtaskhunt_4_3";
		break;

		case "Endtaskhunt_4_3":
			dialog.text = "It won't be long.";
			link.l1 = "Without a doubt. He's going to find out who was behind all this. A preemptive strike must be launched immediately. It's time to end this business – stop chasing the mutts, Ja himself must be in line, otherwise our chances of survival go down to the waterline. We just need to get to Preston!";
			link.l1.go = "Endtaskhunt_4_4";
		break;

		case "Endtaskhunt_4_4":
			dialog.text = "I have information about a certain Miko Pistollero – this is a mulatto Indian, Ja's right hand man. Accurate information could not be gathered, but he was last seen on the west bank of the Main. I assume that he is now in one of the settlements of pearl fishermen, that's all I know. You may be able to learn more from Pistolero himself when you find him. Ja Preston -as usual: elusive.";
			link.l1 = "There is enough information. I'm going on the road immediately. And you, " + npchar.name + ", I advise you to be extremely careful, close doors and windows tightly at night, and do not go outside the city gates. I would really hate to lose my employer... Until the promised payment.";
			link.l1.go = "Givetaskhunt_5";
		break;

		case "Givetaskhunt_5":
			dialog.text = "Thank you for your concern... I will follow your recommendations. Regarding Pistolero. He's not much of a swordsman, but he's a great shot. He never leaves his four-barrel pistol. The masterly handling of this weapon gave him his nickname. Be careful-he can turn you into a sieve before you have time to draw the blade.";
			link.l1 = "And you haven't seen such menacing ones... Wait for my return and take care of yourself, " + npchar.name + "!";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "hunt_miko";
			AddQuestRecord("Headhunt", "33");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("en", "on"));
			CreateMiko();
		break;

		case "Endtaskhunt_5":
			dialog.text = "Uv-f... Finally, you can take a deep breath. " + pchar.name + ", I and all the residents of Le Francois will never forget what you have done for us. Know that you will always be welcome here. Accept this money and this set of ammunition, as agreed, thank you very much again. You have no idea what you have done for us. Come to me more often - I will always have the best rum for you.";
			link.l1 = "Come on already, " + npchar.name + ", make me blush! I just executed the terms of our agreement... And thanks for the ammunition, it will be very useful to me. And money, of course, too.";
			link.l1.go = "Endtaskhunt_5_1";
			AddMoneyToCharacter(pchar, 100000);
			TakeNItems(pchar, "blade28", 1);
			TakeNItems(pchar, "mushket", 1);
			TakeNItems(pchar, "spyglass5", 1);
			TakeNItems(pchar, "cirass4", 1);
			TakeNItems(pchar, "indian11", 1);
		break;

		case "Endtaskhunt_5_1":
			dialog.text = "Good luck to you, " + pchar.name + ". May the wind always be fair for you! I hope you won't forget the old innkeeper, and you'll stop by at least once in a while.";
			link.l1 = "Absolutely, " + npchar.name + "! We'll see each other again. See you later!";
			link.l1.go = "exit";
			AddQuestRecord("Headhunt", "39");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Headhunt");
			pchar.questdata.Kondotier = 1;
			pchar.questTemp.Headhunter = "end_quest_full";
		break;
		//<--ОЗГ
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

