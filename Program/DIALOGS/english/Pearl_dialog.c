
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "There's nothing to talk about!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// ==> глава поселения
		case "HeadMan":
			NextDiag.TempNode = "HeadMan";
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Welcome to our fishing. I am glad to see the subject of " + NationNameGenitive(sti(npchar.nation)) + ". May I know your name?";
				link.l1 = "My name is " + GetFullName(pchar) + ". I am the captain of my own ship.";
				link.l1.go = "HeadMan_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Glad to see you back at my house. Are you on business?",
					"You again? We've already talked it over, Captain.",
					"Captain, is there anything else you need?",
					"Captain, I ask you not to distract me!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("No, " + GetAddress_FormToNPC(NPChar) + ", just dropped by to see you...",
					"Yes, of course.",
					"No, " + GetAddress_Form(NPChar) + "I'm sorry...",
					"Okay...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			//-------- жемчужный генератор Шарпа ------------
			if (pchar.questTemp.Sharp != "begin" && pchar.questTemp.Sharp != "over" && pchar.questTemp.Sharp.SeekSpy == "begin")
			{
				link.l2 = "Tell me, are the pearl fishermen who fish in the Caribbean under your command?";
				link.l2.go = "SharpSeekSpy";
			}
			if (pchar.questTemp.Sharp.SeekSpy == "alwaysKnow")
			{
				link.l2 = "I have arrived for the reward, senor.";
				link.l2.go = "SharpSeekSpy_10";
			}
		break;
		// <------- жемчужный генератор Шарпа
		case "SharpSeekSpy":
			dialog.text = "In our. Why are you asking?";
			link.l1 = "It must be hard for them, among such rampant piracy. A certain Captain Sharp is known among the corsairs...";
			link.l1.go = "SharpSeekSpy_1";
		break;
		case "SharpSeekSpy_1":
			dialog.text = "He is also known among pearl fishermen, "+ GetSexPhrase("my friend","girl") +". This is a real scourge for us!It feels like he just has nothing to do but chase after our tartans! And somehow, the scoundrel finds out who is fishing where.";
			link.l1 = "Yes, he knows a lot about hunters, it's a fact...";
			link.l1.go = "SharpSeekSpy_2";
		break;
		case "SharpSeekSpy_2":
			dialog.text = "We are taking all precautions, but it is useless. Apparently, someone is informing him about our plans.Listen, you started this conversation for a reason. You know something about this case.";
			link.l1 = "Just what I already said. Everyone in the Caribbean knows Captain Sharp...";
			link.l1.go = "SharpSeekSpy_3";
		break;
		case "SharpSeekSpy_3":
			dialog.text = "Clear. Well, I want to offer you a job, since you are aware of our misfortunes.";
			link.l1 = "And what kind of work? Eliminate Sharp?";
			link.l1.go = "SharpSeekSpy_4";
		break;
		case "SharpSeekSpy_4":
			dialog.text = "No, it's too easy. Moreover, it is ineffective. After all, the scoundrel who leaks information about our place of work will simply find another 'sharp', and our tartans will be robbed again.";
			link.l1 = "Logical.";
			link.l1.go = "SharpSeekSpy_5";
		break;
		case "SharpSeekSpy_5":
			dialog.text = "I want you to find this rat among us.";
			link.l1 = "Understood. Now let's discuss the fee...";
			link.l1.go = "SharpSeekSpy_6";
		break;
		case "SharpSeekSpy_6":
			dialog.text = "Hmm, well, let's discuss it. So, I could offer you pearls and money, but I will offer something, in my opinion, more interesting for you. This is a set of weapons. It includes a breton pistol, a Spanish rapier, a Reitar coinage and an officer's cuirass! Believe me, one cuirass is worth a lot!";
			link.l1 = "Heh, how tempting everything is...";
			link.l1.go = "SharpSeekSpy_7";
		break;
		case "SharpSeekSpy_7":
			dialog.text = "And add to this the rat god that I will give you right now, in advance, agree!";
			link.l1 = "Damn me! Of course I agree!";
			link.l1.go = "SharpSeekSpy_8";
			link.l2 = "No, I think I'll refuse.";
			link.l2.go = "SharpSeekSpy_8over";
		break;

		case "SharpSeekSpy_8":
			dialog.text = "Then I'm waiting for good news from you, Captain! You can report and receive the promised reward from any of the elders of the two pearl fishing settlements, they will be aware of our agreement.";
			link.l1 = "I understand. I'm starting the search immediately.";
			link.l1.go = "SharpSeekSpy_9";
		break;
		case "SharpSeekSpy_9":
			GiveItem2Character(pchar, "indian11");
			pchar.questTemp.Sharp.SeekSpy = "seekSpy";
            SetQuestHeader("SharpPearl_SeekSpy");
            AddQuestRecord("SharpPearl_SeekSpy", "1");
			AddQuestUserData("SharpPearl_SeekSpy", "sSex", GetSexPhrase("","a"));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "SharpSeekSpy_8over":
			dialog.text = "Strange. You come to me, talk about Sharp, and then you turn down the job. All this is suspicious, I'm afraid I can't let you go.";
			link.l1 = "What?!..";
			link.l1.go = "SharpSeekSpy_8fight";
		break;
		case "SharpSeekSpy_8fight":
			pchar.questTemp.Sharp.SeekSpy = "over";
			LAi_group_Attack(npchar, pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "SharpSeekSpy_10":
			dialog.text = "Well, I know who you are. Well, tell me what you've managed to dig up.";
			link.l1 = "I found the person from yours who leaked information about your tartans to Sharp. This is Emilio Garcia.";
			link.l1.go = "SharpSeekSpy_11";
		break;
		case "SharpSeekSpy_11":
			dialog.text = "Can you prove it?";
			link.l1 = "Yes. I managed to track him down and overtake him in the cave of San Juan del Norte Bay just at the time of the conversation with Sharp's confidant. I killed both of them.";
			link.l1.go = "SharpSeekSpy_12";
		break;
		case "SharpSeekSpy_12":
			dialog.text = "Understood... Well, I believe you. Your reward for the work done is a set of combat ammunition. Is that right?";
			link.l1 = "Exactly, sir.";
			link.l1.go = "SharpSeekSpy_13";
		break;
		case "SharpSeekSpy_13":
			dialog.text = "Then please get it. It's all yours from now on.";
			link.l1 = "Very glad that I could turn out to be useful. Goodbye, senor.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "blade22");
			GiveItem2Character(pchar, "pistol5");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "topor2");
			pchar.questTemp.Sharp.SeekSpy = "over";
            AddQuestRecord("SharpPearl_SeekSpy", "5");
			AddQuestUserData("SharpPearl_SeekSpy", "sSex", GetSexPhrase("","a"));
			CloseQuestHeader("SharpPearl_SeekSpy");

			//zagolski. битва в бухте
			pchar.quest.sharp_pre.win_condition.l1 = "location";
			if (pchar.curIslandId == "Beliz") pchar.quest.sharp_pre.win_condition.l1.location = "Shore9";
			else pchar.quest.sharp_pre.win_condition.l1.location = "Shore55";			
			pchar.quest.sharp_pre.function = "sharp_pre";

		break;
		// >------- жемчужный генератор Шарпа
		case "HeadMan_1":
			dialog.text = "May I know what you are doing in this wilderness?";
			link.l1 = "I'm exploring the territories, maybe this knowledge will be useful to me in the future.";
			link.l1.go = "HeadMan_2";
		break;
		case "HeadMan_2":
			dialog.text = "So you areresearcher. Well, that's great. I want to bring you up to date on the current state of things.";
			link.l1 = "I'm listening carefully.";
			link.l1.go = "HeadMan_3";
		break;
		case "HeadMan_3":
			dialog.text = "Pearl crafts currently belong to " + NationNameGenitive(sti(npchar.nation)) + ", so no one can buy or sell pearls here.";
			link.l1 = "Understood.";
			link.l1.go = "HeadMan_4";
		break;
		case "HeadMan_4":
			dialog.text = "If you try to break into my chests, punishment will befall you immediately.";
			link.l1 = "This is also understandable.";
			link.l1.go = "HeadMan_5";
		break;
		case "HeadMan_5":
			dialog.text = "Well, that's great. Please accept my assurances of sincere affection for you, " + GetAddress_Form(NPChar) + ".";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
		break;
		// ==> часовой у поселения
		case "GuardMan":
			NextDiag.TempNode = "GuardMan";
			dialog.text = NPCStringReactionRepeat("Hello! Let me introduce myself, my name is " + GetFullName(npchar) + ". My task is to warn the pearl fishing settlement of a possible attack. Pirates, you know... And who are you?",
				"Greetings again!",
				"I stand here alone all day, it's boring, there's no one to talk to...",
                "Oh, damn it, a nice outlet in the outfit!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("My name is " + GetFullName(pchar) + ". I'm the captain, inspecting these lands.",
				"And I like you too...",
                "I understand.",
				"Heh...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("GuardMan_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;

		case "GuardMan_1":
			dialog.text = "If you are in our settlement, then welcome.";
			link.l1 = "Thanks, buddy.";
			link.l1.go = "GuardMan_2";
		break;
		case "GuardMan_2":
			chrDisableReloadToLocation = false;
			npchar.quest.TalkOk = true; //флаг разговор состоялся, все ОК.
			LAi_SetCitizenTypeNoGroup(npchar);
			DialogExit();
		break;

		case "GuardManAllarm":
			dialog.text = "Alarm!! It's a pirate!!!";
			link.l1 = "The Devil! I should have killed you...";
			link.l1.go = "GuardManAllarm_1";
		break;
		case "GuardManAllarm_1":
			chrDisableReloadToLocation = false;
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
		break;
		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("Greetings! My name is " + GetFullName(npchar) + ". How can I help you?",
				"Greetings again!",
				"In our wilderness, visitors are very rare...",
                "Eh, it's nice to chat with a new person! Otherwise, these muzzles are already sickened.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nothing special...",
				"And I like you too...",
                "I understand.",
				"Heh...", npchar, Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
			if (pchar.questTemp.Sharp.SeekSpy == "seekSpy")
			{
				link.l2 = LinkRandPhrase("Listen, your boss assigned me something here... Anyway, do you know if anyone meets pirates here?",
					"Do you know, buddy, who has connections with pirates here?",
					"I have a question for you, my friend. Who have you noticed here in connection with pirates?");
				link.l2.go = "PearlMan_Sharp_1";
			}
			if (CheckAttribute(pchar, "questTemp.Kuali_1") && PChar.location == "Pearl_town_2")
			{
				link.l2 = "Buddy, I'm looking for a person who communicated with the local aborigines from their village.");
				link.l2.go = "Kuali_Poiski_1";
			}
		break;
		case "Kuali_Poiski_1":
			dialog.text = "Yes, we all communicate with them, they work for us, those who were smart enough not to pretend to be great warriors.";
			link.l1 = "Exactly, one of these warriors asked me to return his club, it must be very valuable to him. Not as a weapon, he could have made himself a new stick.";
			link.l1.go = "Kuali_Poiski_2";
		break;
		case "Kuali_Poiski_2":
			dialog.text = "Ah, you need this for Perez, but you're late, we kicked him out.";
			link.l1 = "Did he sail away from these places?";
			link.l1.go = "Kuali_Poiski_3";
		break;
		case "Kuali_Poiski_3":
			dialog.text = "This is unlikely, it's not that no one would take him on the ship, I was careful to approach him. He did a lot of business with these Indians. He took away a great value from one of them. You've got it right - for the locals, she is not just a cudgel. And then he boasted that he seduced the wife of the tribe, can you imagine?";
			link.l1 = "Who is the wife of the tribe?";
			link.l1.go = "Kuali_Poiski_4";
		break;
		case "Kuali_Poiski_4":
			dialog.text = "Their woman, surely you've seen her, if you was there. She's covered in feathers and trinkets. A wife to all young men until they find a worthy peer. Such wonderful traditions, there's nothing you can do.";
			link.l1 = "Is that a prostitute?";
			link.l1.go = "Kuali_Poiski_5";
		break;
		case "Kuali_Poiski_5":
			dialog.text = "Not, not. A wife, just like that. You can't ride up to her on a lame goat. So we thought Perez was lying that she was so-and-so, and then he began to scab like a plague and rot alive. Her husbands sent her a spell, no other way. We kicked him out. The devil knows, suddenly the infection will spread to everyone, and they no longer approached his servant.";
			link.l1 = "Does he still have a house here?";
			link.l1.go = "Kuali_Poiski_6";
		break;
		case "Kuali_Poiski_6":
			dialog.text = "I wouldn't advise you to go there. I would like to burn it, but the commandant is afraid that the fire will spread to his roof.";
			link.l1 = "I'll try. The Indian promised me some kind of life, maybe this is a talisman against this kind of trouble.";
			link.l1.go = "Kuali_Poiski_7";
		break;
		case "Kuali_Poiski_7":
			dialog.text = "Heh. Just don't come near me again once you've been there.";
			link.l1 = "Okay, I won't.";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.Kuali_1");
			pchar.GenQuestBox.PearlTown2_Hut1.box1.items.mineral6 = 15;
			pchar.GenQuestBox.PearlTown2_Hut1.box1.items.jewelry11 = 1;
			pchar.GenQuestBox.PearlTown2_Hut1.box1.items.jewelry12 = 10;
			pchar.GenQuestBox.PearlTown2_Hut1.box1.items.bullet = 8;
			pchar.GenQuestBox.PearlTown2_Hut1.box1.items.GunPowder = 8;
			pchar.GenQuestBox.PearlTown2_Hut1.box1.items.indian2 = 1;
			
			pchar.GenQuestRandItem.PearlTown2_Hut1.randitem1 = "Peres_Kluch";
			
			PChar.quest.Peres_Kluch.win_condition.l1 = "item";
			PChar.quest.Peres_Kluch.win_condition.l1.item = "Peres_Kluch";
			PChar.quest.Peres_Kluch.win_condition = "Peres_Kluch";
			AddQuestRecord("Kuali", "2");
		break;
		
		case "PearlMan_1":
			dialog.text = "We're mining pearls, serving to " + NationNameGenitive(sti(npchar.nation)) + ", that's it...";
			link.l1 = "Yes, I'm aware...";
			link.l1.go = "exit";
			link.l2 = "Listen, is it possible to buy some of these trinkets from the manufacturer, so to speak, eh?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "No, no way!!! For stealing even one small pearl, death!";
				link.l1 = "Heh, the rules here are cruel...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "We have a tough case with this, you can easily lose your head. I don't do this, but I can advise you to contact the local Indians who work with us. They have somewhere to run in case of anything, they will be more daring than us...";
				link.l1 = "I see, well, thank you.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("What are you doing, on your head "+ GetSexPhrase("sick? Get out of here, asshole","sick? Get out of here, you fool") +"!",
				""+ GetSexPhrase("What?!! You haven't eaten too much henbane, you idiot","What?!! Have you eaten too much henbane, you fool") +"?! Get out of here with your questions...",
				""+ GetSexPhrase("Are you out of your mind, dear? What pirates?! With us?!! Would you get out of here, you little fool","Are you out of your mind, dear? What pirates?! With us?!! You should get out of here, honey") +"...");
			link.l1 = RandPhraseSimple("Don't be rude...", "What kind of expressions?!");
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Paleface","White squaw") +" wants to talk?",
				"You again, "+ GetSexPhrase("paleface","white squaw") +".",
				""+ GetSexPhrase("Paleface likes to talk. He looks like a squaw.","The white squaw likes to talk.") +"",
                "The spirits brought pale faces to me"+ GetSexPhrase("his brother","my sister") +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.",
				"Yes, it's me again.",
                "Very poetic.",
				"Nice to see you too.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "Tell me why you came.";
			link.l1 = "Nothing special, I wanted to listen to you...";
			link.l1.go = "exit";
			link.l2 = "Do you have any pearls for sale?";
			link.l2.go = "IndPearlMan_2";
			if (pchar.questTemp.Sharp.SeekSpy == "seekSpy")
			{
				link.l3 = "Listen, my red-skinned friend! I'm looking for a man among the pearl fishers here. Will you help me?";
				link.l3.go = "IndPearlMan_Sharp_1";
			}
		break;
		//жемчужный генератор Шарпа, поиски осведомителя
		case "IndPearlMan_Sharp_1":
			dialog.text = "What is the pale-face looking for? Tell me...";
			link.l1 = "Yes, you see, there is a suspicion that one of your people is telling someone where you will be fishing in the Caribbean Sea.";
			link.l1.go = "IndPearlMan_Sharp_2";
		break;
		case "IndPearlMan_Sharp_2":
			dialog.text = "I know what he wants"+ GetSexPhrase("paleface","white squaw") +"...";
			link.l1 = "What?";
			link.l1.go = "IndPearlMan_Sharp_3";
		break;
		case "IndPearlMan_Sharp_3":
			dialog.text = "Listen to me, "+ GetSexPhrase("paleface brother","white squaw") +", I won't say much. There is a man here, his name is Emilio Garcia. He was seen in a cave in one bay.";
			link.l1 = "Which bay?";
			link.l1.go = "IndPearlMan_Sharp_4";
		break;
		case "IndPearlMan_Sharp_4":
			dialog.text = "You call it the San Juan del Norte Bay. Emilio often comes there at night, where he talks to a white man whose name no one knows, and his eyes are like a rattlesnake.";
			link.l1 = "Why doesn't anyone know the name?";
			link.l1.go = "IndPearlMan_Sharp_5";
		break;
		case "IndPearlMan_Sharp_5":
			dialog.text = "Because he didn't name it.";
			link.l1 = "Ah, I see. Well, thank you, my red-skinned brother.";
			link.l1.go = "IndPearlMan_Sharp_6";
		break;
		case "IndPearlMan_Sharp_6":
			dialog.text = "Let the your path be straight.";
			link.l1 = "And thanks for that. Goodbye...";
			link.l1.go = "exit";
			pchar.questTemp.Sharp.SeekSpy = "toLaVega";
            AddQuestRecord("SharpPearl_SeekSpy", "2");
			AddQuestUserData("SharpPearl_SeekSpy", "sName", npchar.name);
			pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1 = "location";
			pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1.location = "Shore55";
			pchar.quest.SharpSeekSpy_loginSpy.function = "SharpSeekSpy_loginSpy";
		break;
		//продажа жемчуга
		case "IndPearlMan_2":
			if (!CheckAttribute(npchar, "quest.pearl")) npchar.quest.pearl = rand(1);
			if (sti(npchar.quest.pearl) == 0 || CheckAttribute(pchar, "quest.PearlToShore_ForSale.id"))
			{
				dialog.text = "Why should I untie my tongue before "+ GetSexPhrase("pale face","pale face") +"? No.";
				link.l1 = "Do you have anything to say? Well, as you know...";
				link.l1.go = "exit";
			}
			else
			{
				bOk = false;
				int num = FindNearCharacters(npchar, 5.0, -1.0, -1.0, 1.0, false, true);
				if(num > 0)
				{
					for(int i = 0; i < num; i++)
					{
						iTemp = chrFindNearCharacters[i].index;
						if (iTemp == GetMainCharacterIndex()) continue;
						sTemp = characters[iTemp].id;
						if (findsubstr(sTemp, "FightMan" , 0) != -1)
						{
							bOk = true;
							break;
						}
					}
				}
				if (bOk)
				{
					dialog.text = "I have tears of the gods. And the paleface man barks like a dog, everyone hears, everyone wants to kick. I'm leaving...";
					link.l1 = "What?";
					link.l1.go = "IndPearlMan_4";
				}
				else
				{
					dialog.text = "I have tears of the gods. Come to the big water nearby, I'll be there until the first moon.";
					link.l1 = "Understood. The nearest bay, until midnight. I will definitely come.";
					link.l1.go = "IndPearlMan_3";
				}
			}
		break;
		case "IndPearlMan_3":
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
            NextDiag.CurrentNode = "IndPearlMan_Sale";
			LAi_SetActorTypeNoGroup(NPChar);
			if (npchar.location == "Pearl_town_2")
			{
				LAi_ActorRunToLocation(NPChar, "reload", "reload1", "Shore51", "goto", "goto1", "PearlToShore_ForSale", 10.0);
			}
			else
			{
				LAi_ActorRunToLocation(NPChar, "reload", "reload1", "Shore49", "goto", "goto1", "PearlToShore_ForSale", 10.0);
			}
			pchar.quest.PearlToShore_ForSale.idx = npchar.index;
			npchar.quest.Pearl.bigQty = rand(30) + 10;
			npchar.quest.Pearl.smallQty = rand(60) + 20;
			chrDisableReloadToLocation = true;
			DialogExit();
		break;
		case "IndPearlMan_4":
			npchar.LifeDay = 0;
			LAi_group_Attack(NPChar, Pchar);
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			LAi_SetActorType(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 10.0);
			DialogExit();
		break;

		case "IndPearlMan_Sale":
			dialog.text = "You "+ GetSexPhrase("came","came") +"...";
			link.l1 = "Well, yes, but what is the price?";
			link.l1.go = "IndPearlMan_Sale_1";
		break;
		case "IndPearlMan_Sale_1":
			dialog.text = "Ten for a big tear, five for a small one.";
			link.l1 = "I'll take it, how much do you have?";
			link.l1.go = "IndPearlMan_Sale_2";
			link.l2 = "No, I won't take it, I changed my mind.";
			link.l2.go = "IndPearlMan_Sale_Out";
		break;
		case "IndPearlMan_Sale_2":
			dialog.text = npchar.quest.Pearl.bigQty + " for big, " + npchar.quest.Pearl.smallQty + " for small.";
			link.l1 = "Okay, I'll take it all!";
			link.l1.go = "IndPearlMan_Sale_3";
		break;
		case "IndPearlMan_Sale_3":
			int iTemp = (sti(npchar.quest.Pearl.bigQty)*10) + (sti(npchar.quest.Pearl.smallQty)*5);
			if (sti(pchar.money) >= iTemp)
			{
				dialog.text = "The spirits smiled at me, I'm happy...";
				link.l1 = "Goodbye, buddy...";
				AddMoneyToCharacter(pchar, -iTemp);
				TakeNItems(pchar, "jewelry11", sti(npchar.quest.Pearl.bigQty));
				TakeNItems(pchar, "jewelry12", sti(npchar.quest.Pearl.smallQty));
			}
			else
			{
				dialog.text = "You "+ GetSexPhrase("should","should") +" me " + iTemp + " money. You have no money, I have no tears of the gods. Goodbye.";
				link.l1 = "Oh, it's a pity...";
			}
			link.l1.go = "IndPearlMan_Sale_Out";
		break;
		case "IndPearlMan_Sale_Out":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			DialogExit();
			LAi_SetActorType(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", -1);
		break;

		case "CitizenNotBlade":
			dialog.text = "Captain, what nonsense! Put away your weapons before you cause trouble!";
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Don't worry, I'm already removing...");
			link.l1.go = "exit";
		break;
	}
}
