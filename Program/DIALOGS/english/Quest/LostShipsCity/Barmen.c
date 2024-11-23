#include "DIALOGS\english\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	if (CheckAttribute(pchar, "ReturnToLSC") && !CheckAttribute(NPChar, "MetAgain"))
	{
		NPChar.MetAgain = true;
		dialog.text = "Captain, did you survive? I can't believe my eyes!";
		link.l1 = "As you can see..."
		link.l1.go = "MetAgain1";
		return;
	}
	if (HasSubStr(NodeName, "TradeGoods_"))
	{
		npchar.GoodType = strcut(NodeName, findsubstr(NodeName, "_" , 0)+1, strlen(NodeName)-1);
		Dialog.CurrentNode = "TradeCheck";
	}

	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = "I don't want to talk to you! You attacked my fellow citizens!";
				link.l1 = "As you know..."
				link.l1.go = "exit";
				break;
			}

			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = "Was your ship the last to crash? Well, welcome! I run a tavern here, my name is " + GetFullName(npchar) + ". You're very lucky, "+ GetSexPhrase("buddy", "girlfriend") +"!";
					link.l1 = "Yes, I was just fatally lucky!.. My name is " + GetFullName(pchar) + ". I was a captain...";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.Text = "Ah, so it was your ship that crashed last? Well, welcome! I run a tavern here, my name is " + GetFullName(npchar) + ". So come on in, if you'll need...";
					Link.l1 = "Okay, " + npchar.name + ". Nice to meet you, so to speak... And my name is " + GetFullName(pchar) + ".";
					Link.l1.go = "First time";
				}
			}
			else
			{
				//базар в винном погребе
				if (pchar.questTemp.LSC == "toWineCellarGone" && npchar.location.locator == "stay1")
				{
					dialog.Text = "Ah, there you are!";
					link.l4 = "Exactly! Now I would like to listen to you.";
					link.l4.go = "TizerCellar";
					PChar.quest.LSC_returnBarmen.over = "yes"; //снимаем таймер на опоздание, разговор состоялся
					break;
				}
				//после завала Хилла Брюннера
				if (pchar.questTemp.LSC == "barmenIsDead" && !CheckAttribute(npchar, "quest.HillNB_1"))
				{
					dialog.Text = "I'm listening to you carefully.";
					link.l4 = "What the hell are you doing here? Where's Brunner?";
					link.l4.go = "NB_1";
					pchar.questTemp.LSC = "barmenIsDeadYouKnow";
					break;
				}
				if (pchar.questTemp.LSC == "barmenIsDeadYouKnow" || pchar.questTemp.LSC == "toAdmiralBarmenDead")
				{
					if (!CheckAttribute(npchar, "quest.HillNBB_1"))
					{
						dialog.Text = "I'm listening to you carefully.";
						link.l4 = "Well, it looks like Hill is really dead...";
						link.l4.go = "NBB_1";
						break;
					}
				}
				//убийство Армо
				sld = characterFromId("LSCwaitress");
				if (sld.lastname == "Prescott" && !CheckAttribute(npchar, "quest.Armo"))
				{
					dialog.Text = "Armo was killed... First Hill Brunner, now Armo. This tavern is an ominous place.";
					link.l4 = "Was there nothing you could have done to stop it?";
					link.l4.go = "ADied_1";
					npchar.quest.Armo = true;
					break;
				}
				//==> штатый диалог
				dialog.Text = LinkRandPhrase("Hey, " + GetAddress_Form(NPChar) + "! " + PChar.name + "! " + TimeGreeting() + ".",
                                    "Oh, I'm glad to see new citizen in our city...",
                                    "Glad to see you at my tavern. Why did you send?");
				Link.l1 = "I hope you can answer a few questions.";
				Link.l1.go = "int_quests";
				link.l2 = "I need to spend the night.";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I would listen the latest gossip...");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(pchar, "ReturnToLSC"))
				{
					link.l4 = "I brought goods. Would you like to take a look?"
					link.l4.go = "TradeGoods";
				}
				Link.l99 = "Alas, I'm already leaving, " + npchar.name + ". See you later.";
				Link.l99.go = "exit";
				//==>> квесты
				if (pchar.questTemp.LSC == "AfterAdmiral" && GetQuestPastDayParam("questTemp.LSC") > 3)
				{
					link.l4 = "Buddy, we agreed with you that you would think about Teaser Dan...";
					link.l4.go = "Tizer";
				}
				if (pchar.questTemp.LSC == "toWineCellarLate")
				{
					link.l4 = "Listen, I've not found this wine cellar yet...";
					link.l4.go = "TizerCellarLate";
				}
				if (pchar.questTemp.LSC == "toDiffindoor" && CheckCharacterItem(pchar, "letter_LSC"))
				{
					link.l4 = "I examined 'Diffindur' and found a Teaser's chest. Among other things, there was also a very interesting letter in it...";
					link.l4.go = "TizerCellarOk_1";
				}
				if (pchar.questTemp.LSC == "afterFightInProtector")
				{
					link.l4 = "Listen, here's the thing...";
					link.l4.go = "AfterProtector_1";
				}
				if (pchar.questTemp.LSC == "toAdmNarvalRing" && CheckCharacterItem(pchar, "DOjeronRing"))
				{
					link.l4 = "I did as you said. I have the Narwhal ring.";
					link.l4.go = "NarvalRing_1";
				}
				if (pchar.questTemp.LSC == "toTavernNarvalDestroyed")
				{
					link.l4 = "You know, it worked out!";
					link.l4.go = "AfterNarvalDesrt_1";
				}
				if (pchar.questTemp.LSC == "waitInterception" && GetQuestPastDayParam("questTemp.LSC") > 2 && GetHour() < 20)
				{
					link.l4 = "Well, how are you? Did you find out what you were planning?";
					link.l4.go = "Interception";
				}
				if (pchar.questTemp.LSC == "InterceptionLate")
				{
					link.l4 = "Listen, I couldn't came in your cellar by midnight. So I didn't see anyone and I didn't hear anything.";
					link.l4.go = "InterceptionLate";
				}
				if (pchar.questTemp.LSC == "InterceptionYouSeen")
				{
					link.l4 = "You know, exactly at midnight I was in your cellar. The admiral and some other guy were going to talk, but they noticed me and left. So I didn't hear anything .";
					link.l4.go = "InterceptionYouSeen";
				}
				if (pchar.questTemp.LSC == "waitInterceptionResult")
				{
					link.l4 = "Buddy, did you find out anything about our case?";
					link.l4.go = "Result";
				}
				if (pchar.questTemp.LSC == "InterceptionOk")
				{
					link.l4 = "You know, your cellar is a really good place to eavesdrop on conversations. I've waited for Chad.";
					link.l4.go = "InterceptionOk";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Listen, I'm looking for some goods.";
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Listen, we have a serious conversation. I'm recruiting a team.";
					link.l8.go = "SeekCrew";
				}
			}
		break;

		case "FS_1":
			dialog.text = "You are lucky "+ GetSexPhrase("guy", "girl") +", captain, you just don't understand it yet. If you came to the City about five hours ago - you would never have been able  get out of the water.";
			link.l1 = "I am the sailor, I swim well...";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "It doesn't mean anything when it comes to the waters around the City! It's just that the storm has subsided, and that's what gave you a chance.";
			link.l1 = "I see...";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//крутим время
		case "room":
   			if (chrDisableReloadToLocation) //кто-то должен подойти к ГГ.
			{
				dialog.text = "I don't think you should be sleeping right now. Trust me...";
				link.l1 = "Okay.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "You can sleep on the bed that is on the upper tier. When should I wake you up?";
			if(!isDay())
			{
				link.l1 = "In the morning.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "By nightfall.";
				link.l1.go = "hall_night_wait";
				link.l2 = "The next morning.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "Changed my mind. I'll do without sleep.";
			link.l3.go = "exit";
		break;
		case "hall_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		case "hall_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//вопросы
		case "int_quests":
			dialog.text = "I'm listening to you carefully, "+ GetSexPhrase("buddy", "" + pchar.name + "") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "Of course, your weather is just amazing!!";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Listen, what kind of island is this?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "How did I get here?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Is it really impossible to get out of here? How many ships are there around, is it really impossible to put together one whole?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "How the hell do you live here?";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6"))
			{
				link.l6 = "Listen, did you know Teaser Dan?";
				link.l6.go = "ansewer_6";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l7") && pchar.questTemp.LSC == "AdmiralIsWaiting" && CheckCharacterItem(pchar, "keyQuestLSC"))
			{
				link.l7 = "Listen, do you know what Diffindur is?";
				link.l7.go = "ansewer_7";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l8"))
			{
				link.l8 = "What kind of clans live in the City?";
				link.l8.go = "ansewer_8";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l9"))
			{
				link.l9 = "Listen, all the locks on the keys are locked. Where can I get at least one?";
				link.l9.go = "ansewer_9";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l10"))
			{
				link.l10 = "And who is Augusto Brahms?";
				link.l10.go = "ansewer_10";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l11"))
			{
				link.l11 = "I'm not getting used to the City. Isn't there some kind of map or something?";
				link.l11.go = "ansewer_11";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l12") && CheckActiveQuest("LSC_findDekster"))
			{
				link.l12 = "Listen, do you know who Leighton Dexter is?";
				link.l12.go = "ansewer_12";
			}
			link.l20 = "No questions asked. Sorry, buddy...";
			link.l20.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = "That's nothing! It's been worse. Storms are common here.";
			link.l1 = "I see...";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "This storm will end tomorrow evening. We're supposed to check in with the admiral on arrival, so if you don't show up before the storm is over, he'll find you himself.";
			link.l1 = "Admiral?";
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = "Chad Capper, "+ GetSexPhrase("buddy", "" + pchar.name + "") +". Don't mess with this case, my advice to you!";
			link.l1 = "Clear.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = "This is the City of Abandoned Ships, "+ GetSexPhrase("buddy", "girlfriend") +". If you came here, then forget about everything you've lived with earlier. You can't get out of here, unfortunately...";
			link.l1 = "The Devil!!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "I don't know, I need to ask you how you got here. You're captain, you own your ship. I don't know anything, I was sitting in my cabin, suddenly there were screams, then the cracking of the hull... That's it.";
			link.l1 = "And didn't see anything?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Then I saw, of course, this seascape, so to speak. But how our cap managed to come here, I have no idea. He died. Actually, few people escape after a crash, so you're lucky.";
			link.l1 = "Yeah...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Ha!!! And why are you so smart? There were attempts, but all failed. It turns out that people take materials and simply spoil them. The City is seriously suffering from this, as it reduces its stability. If you release any ship, then the island begins to move, all the passages break down, the cabins get up in a different way, in general, it goes sideways. Therefore, it is now prohibited by our Law. And it's been a long time!";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4":
			dialog.text = "Yes, it's fine. Although, you know, I'm sick to death of everything... In general, the City lives on the basis of the Law. You'd better find out about its main food from Admiral Capper.";
			link.l1 = "Who is this admiral?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "This, "+ GetSexPhrase("buddy", "" + pchar.name + "") +", the so-called head of local government, Chad Capper is his name. They say that he used to be a pirate, so you shouldn't bully him without doing something.";
			link.l1 = "No one is going to... Do you really have elections, and citizens choose an admiral?";
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = "Well, there were elections once, but now it is no longer relevant. Chad is doing a good job, no one wants to change anything. No one wants to anymore...";
			link.l1 = "What does 'already' mean?";
			link.l1.go = "ansewer_4_3";
		break;
		case "ansewer_4_3":
			dialog.text = "Before 'already' there were citizens who wanted to become an admiral. But now they are not with us.";
			link.l1 = "Did they sail away from here?";
			link.l1.go = "ansewer_4_4";
		break;
		case "ansewer_4_4":
			dialog.text = "Well, I could say that they sailed to the bottom...";
			link.l1 = "Understood.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = "I knew. He lived with us for several months, then died. It's a pity, he was a good guy.";
			link.l1 = "That's not it!";
			link.l1.go = "ansewer_6_1";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_6_1":
			dialog.text = "He was a bad guy?";
			link.l1 = "That's not what I'm talking about! It looks like he somehow made it to the Mainland...";
			link.l1.go = "ansewer_6_2";
		break;
		case "ansewer_6_2":
			dialog.text = "The devil!!! It can't be!..";
			link.l1 = "Maybe. However, this, in the end, did not bring him happiness, he became a beggar...";
			link.l1.go = "ansewer_6_3";
		break;
		case "ansewer_6_3":
			dialog.text = "Damn! Heck!! Heck!!! Is it really possible...?";
			link.l1 = "What are you talking about?";
			link.l1.go = "ansewer_6_4";
		break;
		case "ansewer_6_4":
			dialog.text = "You know what, "+ GetSexPhrase("buddy", "" + pchar.name + "") +", I'll tell you what: don't tell anyone about this! If the admiral finds out that someone has broken the Law, and even succeeded in doing so... In general, this messenger will not be well.";
			link.l1 = "Hmm, I don't understand...";
			link.l1.go = "ansewer_6_5";
		break;
		case "ansewer_6_5":
			dialog.text = "You'll understand later. In the meantime, for your own sake, do as I say. Don't mention the name of Teaser! Understood?";
			link.l1 = "Understood.";
			link.l1.go = "ansewer_6_6";
		break;
		case "ansewer_6_6":
			dialog.text = "Okay. In the meantime, I'll think about this news of yours...";
			link.l1 = "All right, have a look.";
			link.l1.go = "int_quests";
			AddQuestRecord("ISS_MainLine", "4");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		case "ansewer_7":
			dialog.text = "This is the fluyt 'Fernando Diffindur', a lost place.";
			link.l1 = "Please explain...";
			link.l1.go = "ansewer_7_1";
			NextDiag.(NodePrevName).l7 = true;
		break;
		case "ansewer_7_1":
			dialog.text = "This fluyt was supposed to go down - it's literally split in half. However, it somehow stays on the surface, it seems to have caught on the reefs. In general, this ship stands alone, no one lives there and will not live there.";
			link.l1 = "Why?";
			link.l1.go = "ansewer_7_2";
		break;
		case "ansewer_7_2":
			dialog.text = "Such ships, when they start to leave the water, sink in a few seconds. So you have to be crazy to spend time there.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_8":
			dialog.text = "There are such in our City. You know, there are always those who can't live in peace. That's what they are - the clans...";
			link.l1 = "Hmm, how do I understand?";
			link.l1.go = "ansewer_8_1";
			NextDiag.(NodePrevName).l8 = true;
		break;
		case "ansewer_8_1":
			dialog.text = "Well, convicts and pirates gather in these clans... In general, criminal elements, the dregs of society.";
			link.l1 = "What is this, and do you consider me to be garbage? I'm a pirate!";
			link.l1.go = "ansewer_8_2";
		break;
		case "ansewer_8_2":
			dialog.text = "No, you're not a normal pirate, you are a pirate captain. Here, you have not enough scoundrels of all stripes in the team?";
			link.l1 = "Well, it was enough, to be honest.";
			link.l1.go = "ansewer_8_3";
		break;
		case "ansewer_8_3":
			dialog.text = "That's what I mean... In general, we gave them two ships so that they could stay there and not interfere with the rest of the citizens. The admiral and his militia keep them in check, otherwise it would be a complete nightmare here.";
			link.l1 = "Well, do conflicts happen with them?";
			link.l1.go = "ansewer_8_4";
		break;
		case "ansewer_8_4":
			dialog.text = "There were, of course, but now everything is quiet. But keep in mind that you shouldn't go inside their ships!";
			link.l1 = "Understood. Well, thanks for the information.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_9":
			dialog.text = "Wherever you want, take it there. This is a personal matter for everyone, no one will help you with this.";
			link.l1 = "Oh, I explained it well, there are no words...";
			link.l1.go = "ansewer_9_1";
			NextDiag.(NodePrevName).l9 = true;
		break;
		case "ansewer_9_1":
			dialog.text = "Well, what can I tell you? All chests are locked with locks of three difficulty levels. If a simple key can be found even on the street, then the rest is much more difficult. After all, it is in chests with good locks that people hide really valuable things\n"+
				"Even if you get the keys, keep in mind that others have such keys. If you want to hide something securely, then it's better to look for chests further away, outside the City.";
			link.l1 = "Well, it's already more or less clear. Thank you.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_10":
			dialog.text = "Ha! If I knew, "+ GetSexPhrase("buddy", "" + pchar.name + "") +", who is Augusto Brahms... In fact, I don't even want to know.";
			link.l1 = "Please explain.";
			link.l1.go = "ansewer_10_1";
			NextDiag.(NodePrevName).l10 = true;
		break;
		case "ansewer_10_1":
			dialog.text = "Hmm, no one even knows how he got here, but you want me to explain something to you. He lends money, but it's better to stay away from him"+ GetSexPhrase(", buddy", "") +".";
			link.l1 = "I didn't understand anything...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_11":
			dialog.text = "Ask Eric Yost at the store. He should have one.";
			link.l1 = "Thanks, buddy.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l11 = true;
		break;
		case "ansewer_12":
			dialog.text = "I know, but why do you need it?";
			link.l1 = "Hmm, it's just interesting...";
			link.l1.go = "ansewer_12_1";
			NextDiag.(NodePrevName).l12 = true;
		break;
		case "ansewer_12_1":
			dialog.text = "You shouldn't dig into this case, "+ GetSexPhrase("buddy", "" + pchar.name + "") +", trust me.";
			link.l1 = "Tell me, my friend. We'll see if it's worth it or not.";
			link.l1.go = "ansewer_12_2";
		break;
		case "ansewer_12_2":
			dialog.text = "Well, okay... In general, Dexter was a pirate before entering the City. Just like Capper, by the way. And somehow their relationship didn't work out right away. Dexter soon disappeared. That's all I can tell you.";
			link.l1 = "Yes, not much... But anyway, thank you, " + npchar.name + ".";
			link.l1.go = "int_quests";
		break;

		// ------------------ квесты ------------------
		//бармен забивает стрелу в винном погребе
		case "Tizer":
			dialog.text = "Yes, yes, I've been thinking. But I can't talk about it here. Let's meet at my wine cellar after midnight.";
			link.l1 = "Where is this wine cellar of yours?";
			link.l1.go = "Tizer_1";
		break;
		case "Tizer_1":
			dialog.text = "Well, I call it the cellar out of habit, but in general it is one of the cabins here. We need to go to the main deck of the Finial and enter the quarterdeck from it.";
			link.l1 = "Understood. Well, that's settled.";
			link.l1.go = "Tizer_2";
		break;
		case "Tizer_2":
			dialog.text = "Don't stay too long, I won't be able to wait for you for a long time.";
			link.l1 = "Understood. I will definitely be there.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toWineCellar";
			AddQuestRecord("ISS_MainLine", "5");
		break;
		//бармен ругается, что ГГ не пришёл в погреб
		case "TizerCellarLate":
			dialog.text = "I know that, because I've been waiting for you there for an hour! Damn it, you can't be such frivolous in such a serious matter!";
			link.l1 = "Which one is so serious?";
			link.l1.go = "TizerCellarLate_1";
		break;
		case "TizerCellarLate_1":
			dialog.text = "I say again that I can't talk about this case with you in public! This is crazy!";
			link.l1 = "Okay, don't get all worked up. Let's try to meet again, since it's so necessary.";
			link.l1.go = "TizerCellarLate_2";
		break;
		case "TizerCellarLate_2":
			dialog.text = "Well, okay. I'll be waiting for you there, in the cellar, after midnight tonight. But this time, please come.";
			link.l1 = "Okay, I will definitely be there.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toWineCellar";
		break;
		//базар с барменом в погребе
		case "TizerCellar":
			dialog.text = "I hope you didn't tell anyone about Teaser Dan during this time?";
			link.l1 = "No, as we agreed.";
			link.l1.go = "TizerCellar_1";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.LSC_returnBarmen_2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_returnBarmen_2.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_returnBarmen_2.function = "LSC_returnBarmen_2";
		break;
		case "TizerCellar_1":
			dialog.text = "That's good. So, let me tell you the results of my thoughts on this matter.";
			link.l1 = "I'd love to hear it.";
			link.l1.go = "TizerCellar_2";
		break;
		case "TizerCellar_2":
			dialog.text = "You probably already know that the Law of the City prohibits building anything on which you can sail away from here. So, I just can't imagine how Teaser was able to build a kind of trough on the sly, and even successfully get to the Mainland on it.";
			link.l1 = "Unfortunately, I didn't get to see Teaser personally, otherwise, without a doubt, I found out all details of this case.";
			link.l1.go = "TizerCellar_3";
		break;
		case "TizerCellar_3":
			dialog.text = "Yes, it's a pity... Well, let's look at what we have. And we have a mystery that needs to be solved as quickly as possible. Before doing anything, it is necessary to understand in detail how Teaser was able to get out of here.";
			link.l1 = "And then what?";
			link.l1.go = "TizerCellar_4";
		break;
		case "TizerCellar_4":
			dialog.text = "If citizens find out that Teaser has reached the Mainland, then, no doubt, many will want to follow its example. But before you say anything about Teaser Dan, you need to have proof of your claims.";
			link.l1 = "But I'm...";
			link.l1.go = "TizerCellar_5";
		break;
		case "TizerCellar_5":
			dialog.text = "Your one word is not enough, "+ GetSexPhrase("buddy", "" + pchar.name + "") +", that's what I think. You should go to the fluyt 'Fernando Diffindur'. This place is extremely dangerous - the ship is cracked in half and it is unclear how it stays on the surface. However, it was there that Teaser Dan spent a lot of time. I think that's where we can find the key to the mystery of Teaser.";
			link.l1 = "How do I get there?";
			link.l1.go = "TizerCellar_6";
		break;
		case "TizerCellar_6":
			dialog.text = "Swim, the fluyt is not adjacent to the City directly. The closest to 'Diffindur', on the San Gabriel, don't go inside. This bark is the property of the Casper clan!";
			link.l1 = "Clear. Listen, can you give us a rough idea of what we're looking for on Diffindur?";
			link.l1.go = "TizerCellar_7";
		break;
		case "TizerCellar_7":
			dialog.text = "If I only knew! Let me remind you that we are looking for evidence that the unfortunate Teaser Dan managed to get to the Mainland.";
			if (CheckCharacterItem(pchar, "letter_LSC"))
			{
				link.l1 = "Hmm, you know, on 'Diffindure' I have already visited. And found a Teaser's chest. Among other things, there was also a very interesting letter in it...";
				link.l1.go = "TizerCellarOk_1";
			}
			else
			{
				link.l1 = "You know, I have a key that Teaser's friend gave me on the Mainland. Dan ordered to give this key to Teaser to the one who will go in search of the Island of Justice, that is, the City of Abandoned Ships.";
				link.l1.go = "TizerCellar_8";
			}
		break;
		case "TizerCellar_8":
			dialog.text = "Interesting, very interesting... However, this again proves nothing. Capper will listen to you, and then kill you in front of the rest of the citizens as troublemaker. And no one will say a word to him. The key? Yes, there are plenty of keys in the City, almost every chest is locked.";
			link.l1 = "Yes, that's right too.";
			link.l1.go = "TizerCellar_9";
		break;
		case "TizerCellar_9":
			dialog.text = "However, the key is already something. What did Teaser's friend say about him?";
			link.l1 = "That this is the 'Diffindur' key.";
			link.l1.go = "TizerCellar_10";
		break;
		case "TizerCellar_10":
			dialog.text = "Exactly! We are on the right track!Go to the Diffindur. I believe that there you will find an object to which this key will fit. Teaser, although he seemed to me to be a man with quirks, nevertheless he was far from a fool, apparently...";
			link.l1 = "Oh, maybe. But the fact that he was a good man is a fact.";
			link.l1.go = "TizerCellar_11";
		break;
		case "TizerCellar_11":
			dialog.text = "I agree! Well, let's not waste any time. I'm waiting for you with the results of the fluyt examination.";
			link.l1 = "I'll be there soon, buddy. Wait for it.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "6");
			pchar.questTemp.LSC = "toDiffindoor"; //флаг линейки ГПК
		break;

		case "TizerCellarOk_1":
			dialog.text = "What kind of letter is this?";
			link.l1 = "Read it yourself. Here you go.";
			link.l1.go = "TizerCellarOk_2";
			TakeItemFromCharacter(pchar, "letter_LSC");
		break;
		case "TizerCellarOk_2":
			dialog.text = "Well, well, very interesting... He writes: '...because we have been preparing for a long time and very seriously.'So he wasn't alone...";
			link.l1 = "Yes, apparently you're right.";
			link.l1.go = "TizerCellarOk_3";
		break;
		case "TizerCellarOk_3":
			dialog.text = "Hehe, without a doubt! I knew Teaser pretty well, he wouldn't have been able to build a leaky raft for anything in the world-his hands were growing out of the wrong place. But since he managed to get to the Mainland, it means that his assistant, of course, is an expert in ship building! Why, this is our carpenter, Andre Labor!! That's what, "+ GetSexPhrase("buddy", "captain") +", go to him. Talk to him quietly and peacefully, tell him about Teaser Dan. Otherwise, he doesn't even know that this tramp has reached the Mainland after all!";
			link.l1 = "Is this necessary? After all, Teaser letter is already proof of my words.";
			link.l1.go = "TizerCellarOk_4";
		break;
		case "TizerCellarOk_4":
			dialog.text = "It's already better, but, nevertheless, it's completely unclear how Teaser managed to pull off such a thing. I don't think we should demand the repeal of a provision of the Law without having a specific offer in return.";
			link.l1 = "Why? As soon as we lift the ban on building ships, we will do it right away. There we will decide what and how to build.";
			link.l1.go = "TizerCellarOk_5";
		break;
		case "TizerCellarOk_5":
			dialog.text = "It's not that simple, "+ GetSexPhrase("buddy", "" + pchar.name + "") +". We must give people hope and purpose, not the right to destroy the City as they wish. With the repeal of the provision of the Law, we must immediately adopt a new one, on the construction of ONE ship for ALL!";
			link.l1 = "Hmm, maybe you're right...";
			link.l1.go = "TizerCellarOk_6";
		break;
		case "TizerCellarOk_6":
			dialog.text = "And you also need to remember that the admiral is unlikely to stand, listen to you and scratch his turnips in confusion. Demanding the repeal of the provision of the Law, which was introduced by Capper and is zealously enforced by him, is a big risk. We have to convince the admiral that we are right, and it will not be easy to do this, I think.";
			link.l1 = "Why is it not easy?";
			link.l1.go = "TizerCellarOk_7";
		break;
		case "TizerCellarOk_7":
			dialog.text = "Hmm, how can I tell you... Sometimes I find myself thinking that the Admiral doesn't really want to get out of here.";
			link.l1 = "Hmm, interesting...";
			link.l1.go = "TizerCellarOk_8";
		break;
		case "TizerCellarOk_8":
			dialog.text = "In general, all these are my conjectures, we will return to them later. Now find Andre Labor and carefully find out everything about his involvement in Teaser case.";
			link.l1 = "Okay, I'll do that.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toAndreLabor"; //флаг линейки ГПК
			AddQuestRecord("ISS_MainLine", "7");
			pchar.questTemp.LSC.checkBoxes = true; //шмалять по открытым сундукам ежесуточно
		break;

		case "AfterProtector_1":
			dialog.text = "What happened?";
			link.l1 = "Hmm... Well, in general, I talked to carpenter, this Andre Labor, and he asked me to go to the cabin of the corvette 'The protector'. I went there, well, I was waiting for him, I didn't even think anything like that... And this Andre brought a policeman to talk to me! I had to send everyone to the next world.";
			link.l1.go = "AfterProtector_2";
		break;
		case "AfterProtector_2":
			dialog.text = "The devil! It's a must! Well, now you're finished... listen, be so kind, don't tell me that I put you up to it. They'll kill you anyway, but I can still live...";
			link.l1 = "Behave like a man! No one will kill me, because no one knows that it was done myself. They didn't have time to tell the Admiral about me.";
			link.l1.go = "AfterProtector_3";
		break;
		case "AfterProtector_3":
			dialog.text = "Are you sure about this?";
			link.l1 = "The policeman said so himself.";
			link.l1.go = "AfterProtector_4";
		break;
		case "AfterProtector_4":
			dialog.text = "It's getting better, although I don't see any point in calming down. The admiral is far from being a fool, he will figure you out.";
			link.l1 = "And what do you suggest?";
			link.l1.go = "AfterProtector_5";
		break;
		case "AfterProtector_5":
			dialog.text = "Hmm, I think we should write everything off to one of the clans.";
			link.l1 = "Which one?";
			link.l1.go = "AfterProtector_6";
		break;
		case "AfterProtector_6":
			dialog.text = "For the Narwhal clan, they will be weaker.";
			link.l1 = "How do I do this? I can't come to Chad and say, 'It's not me, it's all narwhals!'";
			link.l1.go = "AfterProtector_7";
		break;
		case "AfterProtector_7":
			dialog.text = "All members of the Narwhal clan have an amulet with the image of an inverted five-pointed star. Get the amulet and take it to the Admiral. Tell him that you found it at the scene of the murder of a policeman and a carpenter.";
			link.l1 = "So how do I find this ring?";
			link.l1.go = "AfterProtector_8";
		break;
		case "AfterProtector_8":
			dialog.text = "In the bow of the galleon Velasco there is a cabin in which the narwhals store all sorts of nonsense. It's a kind of back room for them. Wait for one of them there, and when the narwhal appears, kill him.";
			link.l1 = "Understood. Well, that's what I'll do.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "10");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("en", "on"));
			pchar.questTemp.LSC = "toKillOneNarval";
			pchar.quest.LSC_KillOneNarval.win_condition.l1 = "locator";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.location = "VelascoShipInside1";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.locator = "reload2";
			pchar.quest.LSC_KillOneNarval.function = "LSC_KillOneNarval";
		break;

		case "NarvalRing_1":
			dialog.text = NPCStringReactionRepeat("Great! Now go to the admiral and tell him that you found it in the 'Protector' cabin.",
				"I got it. It's not for me, but for the Admiral to show it.",
				"Look, this isn't funny anymore. Go to the admiral!",
                "You're dumb, though...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Understood.",
				"Yes, of course...",
                "Yeah, definitely!",
				"Yes, such a dumb. I'm always doing the same thing. What I'm counting on is unclear...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

		case "AfterNarvalDesrt_1":
			dialog.text = "Come on!";
			link.l1 = "Exactly! With the help of the amulet, I managed  to prove to Capper that narwhals committed the murder of a policeman. The Admiral believed me and sent me to destroy them all. Which I did.";
			link.l1.go = "AfterNarvalDesrt_2";
		break;
		case "AfterNarvalDesrt_2":
			dialog.text = "Well, that's great... Well, "+ GetSexPhrase("brother", "sister") +", you are entitled to a medal. Although, if you think about it properly, there is more harm from your act than good.";
			link.l1 = "How to understand?";
			link.l1.go = "AfterNarvalDesrt_3";
		break;
		case "AfterNarvalDesrt_3":
			dialog.text = "You see, before your 'feat' there was a balance in the City - 'caspers' were balanced by 'narwhals'. It's in the past now...";
			link.l1 = "Heh, you came up with the idea to set the narwhals up, and now you're not happy.";
			link.l1.go = "AfterNarvalDesrt_4";
		break;
		case "AfterNarvalDesrt_4":
			dialog.text = "Well, I'm not unhappy, I'm just expressing my thoughts. Besides, I was pretty scared then, I admit...";
			link.l1 = "Heh, well, yes, it was noticeable.";
			link.l1.go = "AfterNarvalDesrt_5";
		break;
		case "AfterNarvalDesrt_5":
			dialog.text = "What are you thinking of doing now? You are hero now.";
			link.l1 = "I don't know. It looks like I have got a respect from Chad. Actually, I'm starting to like it here. Maybe I'll sign up for the police...";
			link.l1.go = "AfterNarvalDesrt_6";
		break;
		case "AfterNarvalDesrt_6":
			dialog.text = "That's what, "+ GetSexPhrase("buddy", "" + pchar.name + "") +", you take a walk for now, but don't forget to visit me. I'm going to try to find out something here...";
			link.l1 = "What exactly?";
			link.l1.go = "AfterNarvalDesrt_7";
		break;
		case "AfterNarvalDesrt_7":
			dialog.text = "It's too early to talk about it.";
			link.l1 = "Okay, they'll come to you.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterception";
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
			AddQuestRecord("ISS_MainLine", "17");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
		break;

		case "Interception":
			dialog.text = "You know, I have a lot of strange things going on in my tavern. Sometimes I think that in reality everything is not the way it really is...";
			link.l1 = "What?";
			link.l1.go = "Interception_1";
		break;
		case "Interception_1":
			dialog.text = "I've become a philosopher, in a way, you know... Anyway, I suggest you do something. Do you remember where my wine cellar is?";
			link.l1 = "I remember, of course.";
			link.l1.go = "Interception_2";
		break;
		case "Interception_2":
			dialog.text = "So, be there before midnight today, stand by the grille behind the column and wait. Just turn around so that your shoulders are not visible from behind the column. You may be able to eavesdrop on a very interesting conversation that will influence your decision on what to do next.";
			link.l1 = "Whose conversation is it?";
			link.l1.go = "Interception_3";
		break;
		case "Interception_3":
			dialog.text = "The Admiral and another person. I've been wondering for a long time what they're talking about there periodically... Anyway, do it, and I think the situation will clear up in many ways.";
			link.l1 = "Okay, whatever you say.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toInterception";
			pchar.questTemp.LSC.itemState = false; //флаг нахождения в локаторе итем в таверне
			AddQuestRecord("ISS_MainLine", "18");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("en", "on"));
		break;

		case "InterceptionLate":
			dialog.text = "Yeah, it's not good enough, as they say... Well, now do what you want and live as you know.";
			link.l1 = "Hmm, I see... And who was the person the Admiral was supposed to meet?";
			link.l1.go = "InterceptionBadWork_1";
		break;
		case "InterceptionYouSeen":
			dialog.text = "Yeah, it's not good enough, as they say... Well, now do what you want and live as you know.";
			link.l1 = "Hmm, I see... And who was the man who talked to the admiral?";
			link.l1.go = "InterceptionBadWork_1";
		break;
		case "InterceptionBadWork_1":
			dialog.text = "This is the leader of the Casper clan, Casper Longman.";
			link.l1 = "Hehe, wow!..";
			link.l1.go = "InterceptionBadWork_2";
		break;
		case "InterceptionBadWork_2":
			dialog.text = "Somehow I accidentally bumped into them at the cellar grate when they were talking. I started watching them and realized that they secretly meet here from time to time. I'd like to hear what they're talking about...";
			link.l1 = "Well, maybe it's not too late? Let's wait for their next meeting.";
			link.l1.go = "InterceptionBadWork_3";
		break;
		case "InterceptionBadWork_3":
			dialog.text = "We'll wait, of course, but only I'll do everything myself now. It would be interesting to hear their conversation right now, after the narwhal massacre you staged. And now we'll have to wait...";
			link.l1 = "Hmm, I see. And how long to wait?";
			link.l1.go = "InterceptionBadWork_4";
		break;
		case "InterceptionBadWork_4":
			dialog.text = "That's as it turns out.";
			link.l1 = "Clear. Well, all right. I'll visit you from time to time.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterceptionResult";
			AddQuestRecord("ISS_MainLine", "21");
			SetTimerFunction("LSC_changeBarmen", 0, 0, 15);
		break;

		case "Result":
			dialog.text = NPCStringReactionRepeat("Not yet, but I'm trying. Wait.",
				"I already told you to keep waiting. Nothing new yet.",
				"For the third time, I repeat-wait.",
                "Not tired yet?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Good.",
				"Yes, yes, I understand.",
                "I understand, I will wait.",
				"Nah, I'm so persistent.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "InterceptionOk":
			sld = characterFromId("LSCMayor");
			if (sld.location == "FleuronTavern")
				dialog.text = "Keep your voice down, "+ GetSexPhrase("buddy", "girlfriend") +"! I've got the admiral here just chilling out... Well, did you manage to make out the conversation?";
			else
				dialog.text = "Did you overhear the conversation?";
			link.l1 = "Yes. It turns out that the admiral is going to leave the City himself!";
			link.l1.go = "InterceptionOk_1";
		break;
		case "InterceptionOk_1":
			dialog.text = "It can't be! He also adopted the point of the Law that prohibits even building ships!";
			link.l1 = "Well, he hasn't built it yet, but is just going to.";
			link.l1.go = "InterceptionOk_2";
		break;
		case "InterceptionOk_2":
			dialog.text = "It is impossible to do this in secret from other Citizens!";
			link.l1 = "It is possible. The Casper clan works for the Admiral. Anyway, you don't have to go far for a real example, Teaser Dan was able to.";
			link.l1.go = "InterceptionOk_4";
		break;
		case "InterceptionOk_4":
			dialog.text = "Yes, indeed... Well, I told you it would be important!";
			link.l1 = "Mmm, it couldn't be more important... Listen, the admiral mentioned some kind of Mechanic. Who is this?";
			link.l1.go = "InterceptionOk_5";
		break;
		case "InterceptionOk_5":
			dialog.text = "Hmm, I don't know...";
			link.l1 = "That's the devil!.. Listen, you've been living here for a long time, you should know everyone.";
			link.l1.go = "InterceptionOk_6";
		break;
		case "InterceptionOk_6":
			dialog.text = "What makes you think that this Mechanic of yours exists? Maybe you misunderstood what the admiral said?";
			link.l1 = "Maybe, but hardly... Listen, is there a citizen who already lived here before you came to the City?";
			link.l1.go = "InterceptionOk_7";
		break;
		case "InterceptionOk_7":
			dialog.text = "I find it difficult to answer something. It seems that no one is alive...";
			link.l1 = "Are you sure? Think about it properly.";
			link.l1.go = "InterceptionOk_8";
		break;
		case "InterceptionOk_8":
			dialog.text = "Okay, I'll think about it, but not now. I have to work, so come back tomorrow.";
			link.l1 = "Agreed.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterceptionResult";
			AddQuestRecord("ISS_MainLine", "23");
			SetTimerFunction("LSC_changeBarmen", 0, 0, 3);
		break;
		//смерть Брюннера
		case "NB_1":
			dialog.text = "Don't you know anything? Brunner is no more...";
			link.l1 = "How not?";
			link.l1.go = "NB_2";
			npchar.quest.HillNB_1 = true;
		break;
		case "NB_2":
			dialog.text = "He was found dead in the wine cellar of the tavern. Do you know that cabin aft where the wine barrels are? That's where they found him...";
			link.l1 = "Wow! Have you seen anyone? Has the killer been found?";
			link.l1.go = "NB_3";
		break;
		case "NB_3":
			dialog.text = "No, no one saw anything. Armo, our waitress, found him already dead. She went to the cellar when Hill stayed there for a long time, and so...";
			link.l1 = "Damn it!.. You're the innkeeper now, as I understand it.";
			link.l1.go = "NB_4";
		break;
		case "NB_4":
			dialog.text = "Yes. As soon as everything became known, the admiral called me and asked me to look into the Brunner case. Without a tavern, you see, there is no life...";
			link.l1 = "That's right... Well, good luck in your new place.";
			link.l1.go = "exit";
			if (pchar.questTemp.LSC == "barmenIsDeadYouKnow")
			{
				pchar.questTemp.LSC = "toArmo_BrunnerDead";
			}
			AddQuestRecord("ISS_MainLine", "24");
		break;

		case "NBB_1":
			dialog.text = "It can't be deader, "+ GetSexPhrase("buddy", "girlfriend") +".";
			link.l1 = "How did this happen?";
			link.l1.go = "NBB_2";
			npchar.quest.HillNBB_1 = true;
		break;
		case "NBB_2":
			dialog.text = "He was found dead in the wine cellar of the tavern. Do you know that cabin aft where the wine barrels are? That's where they found him...";
			link.l1 = "Have you seen anyone? Has the killer been found?";
			link.l1.go = "NB_3";
		break;
		//базар по убийству Армо
		case "ADied_1":
			dialog.text = "Where to! No one even saw it happen. She went to clean up in the bow of the tavern, where there is a bed. Suddenly we heard her scream. And that's it...";
			link.l1 = "What's next?";
			link.l1.go = "ADied_2";
		break;
		case "ADied_2":
			dialog.text = "Everyone ran there, and she was lying there with her throat cut. That's all, what is there to do?";
			link.l1 = "There is nothing to do here. Have you seen who it is? Although, I know. This is one of the 'caspers'.";
			link.l1.go = "ADied_3";
		break;
		case "ADied_3":
			dialog.text = "So they got out of control after all. Well, yes... And why did they kill her?";
			link.l1 = "It's all because of me. Devil, I'll never forgive myself!";
			link.l1.go = "exit";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("What exactly?",
				"You already asked about this.",
				"Already asked...",
                "You already asked me about these goods. I don't know anything!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I need bombs, knippels, food, gunpowder, weapons, medicines...",
				"yeah... Sorry, I forgot.",
                "Oh, yeah.",
				"Understood...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Sorry, we don't keep this.";
			link.l1 = "I understand, thank you.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("Which command?",
				"We've already talked about this.",
				"This has already been discussed, I repeat for the second time.",
                "That's enough, I'm tired...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("To the ship. I'm leaving town.",
				"yeah... Sorry, I forgot .",
                "As you know...",
				"Well, okay...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "And what is there on what?";
			link.l1 = "Yes. Otherwise, I wouldn't have called you .";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Yeah... You know, I think I'll say no. I'll wait for permission to do this, and the admiral will gather.";
			link.l1 = "You risk a lot by staying. A strong storm is coming to the City.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Well, not for the first time...";
			link.l1 = "Hmm... Well, whatever you want.";
			link.l1.go = "exit";
		break;
		case "MetAgain1":
			dialog.text = "The storm has spread so much, for the first time in years! We thought that the whole city would be torn off the rocks and drowned in the abyss.";
			link.l1 = "I was lucky in general, I sailed away in the midst of a storm. Barely made it to the ship.";
			link.l1.go = "MetAgain2";
		break;
		case "MetAgain2":
			dialog.text = "I don't know how much time has passed, but the storm suddenly subsided... And a complete calm, without a single gust of wind.";
			link.l1 = "And how are you here now, without power, without an admiral?";
			link.l1.go = "MetAgain3";
		break;
		case "MetAgain3":
			dialog.text = "You know, nothing much has changed, except that almost all the old customers are not here.";
			link.l1 = "Can I help you with something? After all, it turned out that way through my efforts.";
			link.l1.go = "MetAgain4";
		break;
		case "MetAgain4":
			dialog.text = "In general, there are certainly enough goods, but it would not hurt to have an influx from outside. I wouldn't mind buying some soggy food, wine, ale or rum. Anyway, it wouldn't hurt to have a normal meal here either, otherwise there's always one fish... We won't offend with money, you know. There were enough of them in the residence, and the Casper stash is also a little bit.";
			link.l1 = "I will help you as much as I can. If I'm anywhere near the Island, I'll definitely swim out to sell something.";
			link.l1.go = "MetAgain5";
		break;
		case "MetAgain5":
			dialog.text = "Thank you, Captain.";
			link.l1 = "You're welcome.";
			link.l1.go = "exit";
		break;
		case "TradeGoods":
			dialog.text = "So, what did you bring, Captain? There's plenty of room in the warehouses.";
			if (CheckAttribute(pchar, "Ship.Cargo.Goods.Food") && sti(pchar.Ship.Cargo.Goods.Food) > 0)
			{
				link.l1 = "Food in quantity "+pchar.Ship.Cargo.Goods.Food+" units";
				link.l1.go = "TradeGoods_1";
			}
			if (CheckAttribute(pchar, "Ship.Cargo.Goods.Wine") && sti(pchar.Ship.Cargo.Goods.Wine) > 0)
			{
				link.l2 = "Wine in quantity "+pchar.Ship.Cargo.Goods.Wine+" units";
				link.l2.go = "TradeGoods_2";
			}
			if (CheckAttribute(pchar, "Ship.Cargo.Goods.Ale") && sti(pchar.Ship.Cargo.Goods.Ale) > 0)
			{
				link.l3 = "Ale in quantity "+pchar.Ship.Cargo.Goods.Ale+" units";
				link.l3.go = "TradeGoods_3";
			}
			if (CheckAttribute(pchar, "Ship.Cargo.Goods.Rum") && sti(pchar.Ship.Cargo.Goods.Rum) > 0)
			{
				link.l4 = "Rum in quantity "+pchar.Ship.Cargo.Goods.Rum+" units";
				link.l4.go = "TradeGoods_4";
			}
			if (CheckAttribute(pchar, "Ship.Cargo.Goods.Fruits") && sti(pchar.Ship.Cargo.Goods.Fruits) > 0)
			{
				link.l5 = "Fruits in quantity "+pchar.Ship.Cargo.Goods.Fruits+" units";
				link.l5.go = "TradeGoods_5";
			}
			link.l99 = "I need to think about it.";
			link.l99.go = "exit";
		break;
		case "TradeCheck":
			switch (sti(npchar.GoodType))
			{
				case 1: dialog.text = "Food? And how much of this is for sale?"; break;
				case 2: dialog.text = "Wine? And how much of this is for sale?"; break;
				case 3: dialog.text = "Ale? And how much of this is for sale?"; break;
				case 4: dialog.text = "Rum? And how much of this is for sale?"; break;
				case 5: dialog.text = "Fruit? And how much of this is for sale?"; break;
			}
			Link.l1.edit = 1;
			link.l1 = "";
			link.l1.go = "TradeCheck2";
			link.l2 = "I need to think about it.";
			link.l2.go = "exit";
		break;
		case "TradeCheck2":
			npchar.amount = GetStrSmallRegister(dialogEditStrings[1]);
			string sGoodX
			switch (sti(npchar.GoodType))
			{
				case 1:	sGoodX = "Food"; break;
				case 2:	sGoodX = "Wine"; break;
				case 3:	sGoodX = "Ale"; break;
				case 4:	sGoodX = "Rum"; break;
				case 5:	sGoodX = "Fruits"; break;
			}
			npchar.amount = func_min(sti(npchar.amount), sti(pchar.Ship.Cargo.Goods.(sGoodX))); //фикс, нельзя продать больше, чем привёз
			npchar.amount = func_max(sti(npchar.amount),1);
			switch (sti(npchar.GoodType))
			{
				case 1:
					NPChar.sumtotal = sti(npchar.amount)*10;
					dialog.text = "I take food 50 per unit. Total, "+NPChar.sumtotal+" gold for "+npchar.amount+" units. Are you satisfied with the offer?"; 
				break;
				case 2: 
					NPChar.sumtotal = sti(npchar.amount)*150;
					dialog.text = "I take wine 50 per unit. Total, "+NPChar.sumtotal+" gold for "+npchar.amount+" units. Are you satisfied with the offer?"; 
				break;
				case 3: 
					NPChar.sumtotal = sti(npchar.amount)*40;
					dialog.text = "I take ale 50 per unit. Total, "+NPChar.sumtotal+" gold for "+npchar.amount+" units. Are you satisfied with the offer?";
				break;
				case 4: 
					NPChar.sumtotal = sti(npchar.amount)*20;
					dialog.text = "I take rum 50 per unit. Total, "+NPChar.sumtotal+" gold for "+npchar.amount+" units. Are you satisfied with the offer?";
				break;
				case 4: 
					NPChar.sumtotal = sti(npchar.amount)*20;
					dialog.text = "I take rum 50 per unit. Total, "+NPChar.sumtotal+" gold for "+npchar.amount+" units. Are you satisfied with the offer?";
				break;
				case 5: 
					NPChar.sumtotal = sti(npchar.amount)*50;
					dialog.text = "I take fruit 50 per unit. Total, "+NPChar.sumtotal+" gold for "+npchar.amount+" units. Are you satisfied with the offer?";
				break;
			}
			link.l1 = "Yes. It's a deal!";
			link.l1.go = "TradeCheck3";
			link.l2 = "I need to think about it.";
			link.l2.go = "exit";
		break;
		case "TradeCheck3":
			switch (sti(npchar.GoodType))
			{
				case 1:
					pchar.Ship.Cargo.Goods.Food = sti(pchar.Ship.Cargo.Goods.Food)-sti(npchar.amount);
				break;
				case 2: 
					pchar.Ship.Cargo.Goods.Wine = sti(pchar.Ship.Cargo.Goods.Wine)-sti(npchar.amount);
				break;
				case 3: 
					pchar.Ship.Cargo.Goods.Ale = sti(pchar.Ship.Cargo.Goods.Ale)-sti(npchar.amount);
				break;
				case 4: 
					pchar.Ship.Cargo.Goods.Rum = sti(pchar.Ship.Cargo.Goods.Rum)-sti(npchar.amount);
				break;
				case 5: 
					pchar.Ship.Cargo.Goods.Fruits = sti(pchar.Ship.Cargo.Goods.Fruits)-sti(npchar.amount);
				break;
			}
			dialog.text = "Nice to do business with you. Get it and sign it!";
			AddCharacterExpToSkill(pchar, "Commerce", sti(NPChar.sumtotal) / 2500.0);
			/*if (sti(NPChar.sumtotal) >= 15000)
			{
				int chestsamount = makeint(sti(NPChar.sumtotal)/15000);
				TakenItems(pchar, "Chest",chestsamount);
				NPChar.sumtotal = sti(NPChar.sumtotal)-(15000*chestsamount);
				log_info("Received credit chest in the amount of "+chestsamount+"pcs.");
			}*/
			AddMoneyToCharacter(pchar, sti(NPChar.sumtotal));
			link.l1 = "With you too. See you later!";
			link.l1.go = "exit";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
