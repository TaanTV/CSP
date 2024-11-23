
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp, i;

	string NodeName = Dialog.CurrentNode;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.location == "SanAugustineResidence")
			{
				dialog.text = "What did you want? Don't keep me for nothing, I'm busy.";
				link.l1 = "Sorry, I just dropped by to you.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "When I'm not at my residence, I'm not averse to talking, in principle... What did you want?";
				link.l1 = "I just wanted  to find out if everything is in order in the City.";
				link.l1.go = "NRes_1";
			}
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				pchar.questTemp.LSC = "AdmiralFoundHero";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = "Ah, here you are. It's good that you came to me. I don't like people running away from me, and even in such a storm...";
					link.l1 = "I don't intend to run from anyone. My name is " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
					PChar.quest.LSC_admiralOwnFind.over = "yes";
				}
				else
				{
					dialog.text = "Ah, here you are. I've been waiting for you to come to me.";
					link.l1 = "Greetings. My name is " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
				break;
			}
			//квестовые ноды по главной линейке
			if (pchar.questTemp.LSC == "toAdmNarvalRing" && CheckCharacterItem(pchar, "DOjeronRing"))
			{
				link.l4 = "Admiral, I have important information for you. Um, it seems to me...";
				link.l4.go = "NarvalRing_1";
			}
			if (pchar.questTemp.LSC == "NarvalDestroyed")
			{
				link.l4 = "I did everything, the Narwhal clan has been destroyed. Cut out everyone at the root, no one left!";
				link.l4.go = "DestrNarval_1";
			}
			if (pchar.questTemp.LSC == "toAdmiralBarmenDead")
			{
				link.l4 = "Admiral, I wanted to talk about the murder of Hill Brunner.";
				link.l4.go = "BarmenDead_1";
			}
			if (pchar.questTemp.LSC == "fromMechanicToAdmiral")
			{
				link.l4 = "Admiral, I wanted to talk to you.";
				link.l4.go = "CasperDead_1";
			}
			//дополнительные квестовые ноды
			//муж Элис Тейлор
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC != "AdmiralIsWaiting" && pchar.questTemp.LSC.ElisHusband == "toElis")
			{
				link.l5 = "Admiral, please tell me what Maxim Taylor has done here?";
				link.l5.go = "ELTHusb_begin";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiral")
			{
				link.l5 = "Admiral, I wanted to help Maxim Taylor.";
				link.l5.go = "ELTHusb_SF";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiralGood")
			{
				link.l5 = "Admiral, I found out something about the circumstances of that Taylor case.";
				link.l5.go = "ELTHusb_good";
			}
			//квест со скелетом Декстера
			if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && pchar.questTemp.LSC != "AdmiralIsWaiting" && pchar.questTemp.LSC.lostDecster == "toAdmiral")
			{
				link.l6 = "Admiral, I have a little question for you about Leighton Dexter.";
				link.l6.go = "LostDecster";
			}
			//поиск товаров на корвет
			if (pchar.questTemp.LSC == "toSeekGoods")
			{
				link.l8 = "Listen, I'm looking for some goods here. Could you help me out?";
				link.l8.go = "SeekGoods";
			}
			//найм команды
			if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
			{
				link.l8 = "Admiral, a storm is coming...";
				link.l8.go = "SeekCrew";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NRes_1":
			dialog.text = "Yes, everything is fine. I'm glad you care so much about our City. You are "+ GetSexPhrase("good citizen", "good citizen") +".";
			link.l1 = "Glad to do my best, Admiral!";
			link.l1.go = "exit";
		break;

		case "FT_1":
			dialog.text = "Very good, "+ GetSexPhrase("buddy", "girlfriend") +", just wonderful... And my name is " + GetFullName(npchar) + ", I am the admiral of this City of Abandoned Ships!";
			link.l1 = "Ha, but I heard about you! You're the pirate captain who went out for the prize on the Horror of Main and disappeared. So that's where you're going!";
			link.l1.go = "FT_1_1";
		break;
		case "FT_1_1":
			dialog.text = "Yes, I am still remembered in the Caribbean... See how it turned out. For two days we chased the Spanish galleon, and on the night of the third day we found ourselves here... Damn, my whole team went down, only me, Workman and Faure could get out.";
			link.l1 = "I'm sorry...";
			link.l1.go = "FT_1_2";
		break;
		case "FT_1_2":
			dialog.text = "To tell the truth, shit was the command back then. So, you don't have to grieve too much, especially since it's a thing of the past... Well, that's not what we're talking about right now!";
			link.l1 = "Tell me what you need. I'm listening carefully, " + npchar.name + ".";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "So that's it! From the moment you got from the sea to the deck of our island, you have become a citizen, and now bound by the law of the city. Do you understand that?";
			link.l1 = "Quite. And what kind of Law is it, how can I get acquainted with it?";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "I am introducing you to the Law at this particular moment. It's not stamped on the tablets, because we have a hard time with the stone, haha... And the Law essentially consists of the following points "+
				"All citizens of the City of Abandoned Ships have the right to life. This right is provided by the militia garrison, which is at the disposal of the Admiral, that is, at my disposal... By the way, don't you want to join the police?";
			link.l1 = "We'll see there. First you need to settle in, get settled here somehow, and then solve such issues.";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "You look like "+ GetSexPhrase("strong guy", "strong girl") +". Who was you in the Big world?";
			link.l1 = "Yes, you know, I wandered... I was a free captain, just like you, in general.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Understood... But now, actually, I don't care about that. Be you Spanish before you get here or French, angel or a devil - everyone is equal here. Now you have become a citizen of the citiy with own rights, the most important of which is the right to life!";
			link.l1 = "Yes, not bad. Universal justice. By the way, there are rumors in the Caribbean about some kind of Island of Justice. I suppose this is your City.";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "No, it can't be. The way from here is ordered... Well, let's continue. So, that's it with the rights, now about your responsibilities. First: You cannot attempt the lives of the citizens of the City. If you kill someone, I will kill you. Is that clear?";
			link.l1 = "Hmm, I see...";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "A small nuance. We have two communities here in the City, the so-called Narwhal and Casper clans. In general, people gathered there who find the life of a decent person like a bone in their throat. We have allocated them two ships for permanent deployment - the barque San Gabriel and the galleon Velasco. These ships are isolated, so the clans do not interfere with the life of the City\n"+
				"So, citizens should not go inside these ships - it is dangerous for their lives. The internal premises of these courts have been transferred to the ownership of the clans, and they have their own laws in this territory. So don't go in there or blame yourself. Is that clear?";
			link.l1 = "Understood.";
			link.l1.go = "FT_7_1";
		break;
		case "FT_7_1":
			dialog.text = "Let's move on. Secondly, it is forbidden to build ships, rafts and other watercraft. It's impossible to get out of here anyway, and you can't destroy the City.";
			link.l1 = "And that's understandable.";
			link.l1.go = "FT_7_2";
		break;
		case "FT_7_2":
			dialog.text = "Third: the death penalty is imposed for theft in the City. If you get caught digging"+ GetSexPhrase("eat", "eat") +" in someone else's chest - you automatically lose your citizenship and become an outlaw. And this means that you no longer have the right to live...";
			link.l1 = "Sounds great... Well, that's clear. What's next?";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "And the fourth thing: all the material resources that got into the City belong to the City.";
			link.l1 = "Hmm, but more on this point, please.";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "Heh, well, what's not clear here? For example, you, as an individual, got to the City. And notice, immediately became its citizen! Here is your property, as tangible assets, become the property of the City. So all yours is now ours in common!";
			link.l1 = "Wait! I disagree with this scenario!";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			if (pchar.questTemp.LSC == "AdmiralFoundHero")
			{
				dialog.text = "Here"+ GetSexPhrase("weirdo man", "weirdo") +"! Your consent is not required, we just take it, and that's it... But I have some good news. As a rightfully citizen of the City, you get a 1/50 share!";
				link.l1 = "From my own property!!";
				link.l1.go = "FT_11";
				pchar.money = makeint(sti(pchar.money) / 50);
			}
			else
			{
				dialog.text = "And no one is asking for your consent. Actually, the Law obliges to include the former owner of the good among the shareholders in the division. But since you violated the Law, namely, you did not reveal to me on time upon arrival in the City, this paragraph of the Law in relation to you loses its force. That is, you don't get anything.";
				link.l1 = "I don't like this very much!";
				link.l1.go = "FT_12";
				pchar.money = 0;
			}
		break;
		case "FT_11":
			dialog.text = "Exactly! Well, you're starting to understand... Actually, you don't need all this stuff here, but it will be nice for all of us...";
			link.l1 = "I don't like this very much!";
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = "You're not first, "+ GetSexPhrase("buddy", "girlfriend") +", who doesn't like it. But trust me, it's all in your best interest. The sooner you get rid of everything that connects you to the big world, the sooner you will join our measured life.You can go crazy like that, it happens. And, I'll tell you, we don't stand on ceremony with such people - a load on the neck, and to the bottom!";
			link.l1 = "Yes, justice is coming...";
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = "For rudeness, I'm depriving you of weapons, and in general I'll clean your pockets! And keep in mind that next time, if I don't like you, I'll just kill you.";
			link.l1 = "Oh... Well, we'll have to put up with it. It seems like I have no other choice.";
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = "That's right. And I don't advise you to look for him, it's forbidden by Law!";
			link.l1 = "I remember...";
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = "Well, that's great... And now you're free and you can move around the City as you like. Do whatever you want, enjoy life in the City.";
			link.l1 = "That's what I'll do, Chad.";
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			if (npchar.chr_ai.type == LAI_TYPE_ACTOR) LAi_SetLSCoutTypeNoGroup(npchar);
			AddDialogExitQuestFunction("LSC_admiralTakeAll");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//базар с ГГ, если сам не пришёл к адмиралу
		case "FoundHero":
			npchar.quest.meeting = "1";
			NextDiag.TempNode = "First time";
			pchar.questTemp.LSC = "AdmiralNotFoundHero";
			dialog.text = "Yeah, that means you're a survivor in the last storm. Tell me, "+ GetSexPhrase("buddy", "girlfriend") +", why the hell should I be looking for you all over the City? Don't you know our rules?";
			link.l1 = "Greetings. What are the orders?";
			link.l1.go = "FoundHero_1";
		break;
		case "FoundHero_1":
			dialog.text = "You want to say that you didn't know that you need to come to me as soon as you get to the City?";
			link.l1 = "Didn't know...";
			link.l1.go = "FoundHero_2";
		break;
		case "FoundHero_2":
			dialog.text = "Ignorance of the Law does not absolve from responsibility! Now tell me who you are.";
			link.l1 = "I'm sorry for being late, I haven't studied The Laws of the City. I hope it will be better from now on... My name is " + GetFullName(pchar) + ".";
			link.l1.go = "FT_1";
		break;

		//ГГ принёс амулет нарвалов
		case "NarvalRing_1":
			dialog.text = "I'm all ears.";
			link.l1 = "I've been in the cabin of the corvette 'Protector' recently, and quite by chance found an interesting item...";
			link.l1.go = "NarvalRing_2";
		break;
		case "NarvalRing_2":
			dialog.text = "What is the subject? Speak quickly, don't delay!";
			link.l1 = "This is a ring. Here it is, take a look.";
			link.l1.go = "NarvalRing_3";
		break;
		case "NarvalRing_3":
			dialog.text = "Ho ho, it's a narwhal amulet! So, where did you find it?";
			link.l1 = "In the cabin 'Protector'.";
			link.l1.go = "NarvalRing_4";
			TakeItemFromCharacter(pchar, "DOjeronRing");
			BackItemName("DOjeronRing");
			BackItemDescribe("DOjeronRing");
			ref itm;
			itm = ItemsFromID("DOjeronRing");
			itm.picIndex = 2;
			itm.picTexture = "ITEMS_9";
		break;
		case "NarvalRing_3":
			dialog.text = "Do you know that the murder of policeman and carpenter Andre Labor was committed there?";
			link.l1 = "Heard...";
			link.l1.go = "NarvalRing_4";
		break;
		case "NarvalRing_4":
			dialog.text = "Well, your find clearly shows who did it... And you are familiar with 'Narwhals'?";
			link.l1 = "No, Chad. They don't let anyone in. A little something - they immediately attack without talking.";
			link.l1.go = "NarvalRing_5";
		break;
		case "NarvalRing_5":
			dialog.text = "Yes, it's true. They can do whatever they want on their territory. They have their own laws there. Do you know how the clans came to be formed?";
			link.l1 = "Tell me, please. I'd love to hear it.";
			link.l1.go = "NarvalRing_6";
		break;
		case "NarvalRing_6":
			dialog.text = "Hmm, good... The fact is that along with ordinary people, all sorts of scum get into the City. They cannot live with the rest of the world, which is why it was decided to give such people two ships as property. By that time, two groups of thugs had formed, and they formed the Narwhal and Casper clans.";
			link.l1 = "Understood... What should I do now? After all, it turns out that the narwhals are involved in the murder of an official representative of the government!";
			link.l1.go = "NarvalRing_7";
		break;
		case "NarvalRing_7":
			dialog.text = "It's time to get rid of the Narwhal clan, they are tired of their frostbite.";
			link.l1 = "The right decision, Admiral!";
			link.l1.go = "NarvalRing_8";
		break;
		case "NarvalRing_8":
			dialog.text = "Without a doubt! And I'm entrusting it to you.";
			link.l1 = "Hmm, what are you charging?";
			link.l1.go = "NarvalRing_9";
		break;
		case "NarvalRing_9":
			dialog.text = "Destruction of 'narwhals', "+ GetSexPhrase("buddy", "girlfriend") +". Who better to do this job than you? It's thanks to you that we found out the truth!";
			link.l1 = "Damn! I somehow didn't count on such a plot twist...";
			link.l1.go = "NarvalRing_10";
		break;
		case "NarvalRing_10":
			dialog.text = "No way, I'm scared? You're a pirate cap, what's the matter with you?!";
			link.l1 = "There are many of them. And even though I was a pirate captain, but not a suicide.";
			link.l1.go = "NarvalRing_11";
		break;
		case "NarvalRing_11":
			dialog.text = "Ah, well, we'll decide that. I'm giving you three of my people to help you.";
			link.l1 = "Well, that makes a difference. I agree.";
			link.l1.go = "NarvalRing_12";
		break;
		case "NarvalRing_12":
			dialog.text = "Great! So go to Velasco right now and work there properly. My men will be waiting for you on the Velasco.";
			link.l1 = "Okay, Chad, I'll do everything in the best possible way.";
			link.l1.go = "NarvalRing_13";
		break;
		case "NarvalRing_13":
			AddQuestRecord("ISS_MainLine", "12");
			pchar.questTemp.LSC = "toDestoyAllNarval";
			int idxMent;
			pchar.questTemp.LSC.qtyOfficers = 0;
			string sOffName;
			for (i=1 ; i<=3; i++)
			{
				idxMent = GetCharacterIndex("Ment_" + i);
				if (idxMent != -1)
				{
					ChangeCharacterAddressGroup(&characters[idxMent], "LostShipsCity_town", "officers", "officer_"+i);
					characters[idxMent].Dialog.CurrentNode = "OffNarval";
					characters[idxMent].cityTape = "quest"; //тип нпс
					LAi_SetStayTypeNoGroup(&characters[idxMent]);
					pchar.questTemp.LSC.qtyOfficers = sti(pchar.questTemp.LSC.qtyOfficers) + 1;
				}
			}
			pchar.quest.NavalEnterOfficers.win_condition.l1 = "location";
			pchar.quest.NavalEnterOfficers.win_condition.l1.location = "VelascoShipInside1";
			pchar.quest.NavalEnterOfficers.function = "NavalEnterOfficers";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//клан Нарвал уничтожен
		case "DestrNarval_1":
			dialog.text = "Well, that's good. How are my people?";
			iTemp = 0;
			for (i=1 ; i<=3; i++)
			{
				if (GetCharacterIndex("Ment_" + i) != -1)
				{
					iTemp++;
				}
			}
			if (iTemp == 0)
			{
				link.l1 = "Everyone died, unfortunately. I'm really sorry...";
				link.l1.go = "DestrNarval_Bad";
			}
			else
			{
				if (iTemp == sti(pchar.questTemp.LSC.qtyOfficers))
				{
					link.l1 = "Yes, everything is fine. Everyone is alive and well, I'm returning them to you safely.";
					link.l1.go = "DestrNarval_Ok";
				}
				else
				{
					link.l1 = "There are losses, but not all were killed. I'm returning the survivors.";
					link.l1.go = "DestrNarval_BadOk";
				}
				DeleteAttribute(pchar, "questTemp.LSC.qtyOfficers");
			}
		break;
		case "DestrNarval_Bad":
			dialog.text = "Yeah, it's sad... However, the task is completed, the narwhals are destroyed, and this is the main thing. So it's all right.";
			link.l1 = "Well, yes, everything is fine, as they say...";
			link.l1.go = "DestrNarval_Bad1";
		break;
		case "DestrNarval_Bad1":
			dialog.text = "Well, great. I'm not holding you up anymore, you can go.";
			link.l1 = "Hmm... Well, thank you, Admiral...";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTavernNarvalDestroyed";
			AddQuestRecord("ISS_MainLine", "16");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
		break;
		case "DestrNarval_Ok":
			dialog.text = "Great! For a job well done, I'll probably give you some money. One hundred thousand gold! Take them, they're yours.";
			link.l1 = "Hmm, I don't need money here yet, but thank you anyway.";
			link.l1.go = "DestrNarval_Ok1";
			AddQuestRecord("ISS_MainLine", "14");
			AddMoneyToCharacter(pchar, 100000);
		break;
		case "DestrNarval_Ok1":
			dialog.text = "You're welcome! Well, I'm not detaining you anymore, so you can go about your business in peace.";
			link.l1 = "Hmm... All right.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTavernNarvalDestroyed";
		break;
		case "DestrNarval_BadOk":
			dialog.text = "Well, yes, it's a little unpleasant... Well, anyway, it was a massacre, not an easy walk on the deck. All in all, I'm glad that everything ended well. I want to give you some money for your work. Ten thousand gold!";
			link.l1 = "Well, money is not really needed here... But thanks anyway.";
			link.l1.go = "DestrNarval_Ok1";
			AddQuestRecord("ISS_MainLine", "15");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
			AddMoneyToCharacter(pchar, 10000);
		break;
		//подслушивание в погребке
		case "Interception":
			sld = characterFromId("Blaze");
			bool bOk = false;
			float fAng;
			GetCharacterAy(sld, &fAng);
			if (fAng > -1.35 && fAng < -0.28) bOk = true;
			if (fAng > 1.8 && fAng < 2.9) bOk = true;
			if (sti(sld.questTemp.LSC.itemState) && bOk)
			{
				dialog.text = "Glad to see you, Admiral.";
				link.l1 = "How's the Casper clan doing?'";
				link.l1.go = "Interception_1";
				sld.questTemp.LSC = "InterceptionOk";
				sld.questTemp.LSC.knowMechanic = true; //флаг ГГ знает о Механике
			}
			else
			{
				dialog.text = "Glad to see you, Admiral.";
				link.l1 = "Quiet... It seems that there is someone behind bars. We'll talk somewhere else.";
				link.l1.go = "exit";
				sld.questTemp.LSC = "InterceptionYouSeen";
				AddDialogExitQuestFunction("LCS_EndScriptInterception");
			}
		break;
		case "Interception_1":
			sld = characterFromId("Blaze");
			dialog.text = "Not bad. Especially after you crushed the competition.";
			link.l1 = "Hehe... You know, but everything happened by itself. I just pointed my finger at them, so to speak "+ NPCharSexPhrase(sld, "to this idiot", "to this insolent girl") +"...";
			link.l1.go = "Interception_2";
		break;
		case "Interception_2":
			sld = characterFromId("Blaze");
			dialog.text = ""+ NPCharSexPhrase(sld, "Which idiot", "What kind of insolent girl") +"?";
			link.l1 = "This new citizen " + GetFullName(sld) + ". You probably heard that one policeman and our carpenter were killed. So, this new citizen brought narwhals amulet and told me that found it at the murder scene. Although it is sewn with white threads, I did not deal with this case for a long time, as an opportunity turned up to carry out my long-planned plan without incurring suspicion. I sent this 'hero' for disassembly, gave "+ NPCharSexPhrase(sld, "him", "her") +" more people from the police to help.";
			link.l1.go = "Interception_4";
		break;
		case "Interception_4":
		sld = characterFromId("Blaze");
			dialog.text = "Well, that's what 'hore' done for you – that's fine. But I hope you didn't enter "+ NPCharSexPhrase(sld, "him", "her") +" in the course of our affairs?";
			link.l1 = "No, I don't trust "+ NPCharSexPhrase(sld, "him", "her") +". On the Mainland, he was a privateer captain, and such people should always be feared. It's one thing to use "+ NPCharSexPhrase(sld, "him", "her") +" in our own interests, and the other is to connect them to our business.";
			link.l1.go = "Interception_5";
		break;
		case "Interception_5":
			dialog.text = "By the way, about our case. A lot of things have already been collected, my guys can't wait to spend their share in the brothels of the Caribbean. When will we start making preparations to sail from this damn place?";
			link.l1 = "It's too early, I haven't raised enough money yet.";
			link.l1.go = "Interception_6";
		break;
		case "Interception_6":
			dialog.text = "Carramba, my chests are bursting with money and valuables! Is everything not enough for you?!!";
			link.l1 = "Don't raise your voice at me – I'll rip out your adam's apple!..";
			link.l1.go = "Interception_7";
		break;
		case "Interception_7":
			dialog.text = "Sorry, Admiral, this won't happen again...";
			link.l1 = "Look at me! Now listen carefully. Maybe there's enough money to visit brothels and buy some kind of shack, but I have completely different plans on the Mainland. I want to become governor, and for that I have to go to London and give money there right and left without counting! Do you understand now?";
			link.l1.go = "Interception_8";
		break;
		case "Interception_8":
			dialog.text = "Understood. But you also understand us. We've been working with you for so long, collecting valuables and money, and we haven't even started building a ship yet! I have a hard time keeping people under control.";
			link.l1 = "And we won't be able to start construction, because our carpenter was killed. You can tell your people that.";
			link.l1.go = "Interception_9";
		break;
		case "Interception_9":
			dialog.text = "Well, yes, and they collect drawings of ships and tools for construction from me... And what should I do now? Maybe we should force a Mechanic?";
			link.l1 = "I'm against it. This madman is unreliable, and with his delusional speeches he will mess up anyone's brains. By the way, do your people not communicate with him?";
			link.l1.go = "Interception_10";
		break;
		case "Interception_10":
			dialog.text = "No, I'm strictly following this. The mechanic does not get out of his kennel.";
			link.l1 = "Okay... So you'll tell your people that we'll start building the ship as soon as a new carpenter appears. Hehe, the next lumberjack will be lucky...";
			link.l1.go = "Interception_11";
		break;
		case "Interception_11":
			dialog.text = "Will you let him live?";
			link.l1 = "I'll leave it, because that's the Law! Ha ha! Well, I think that's how we'll sort out the current problems.";
			link.l1.go = "Interception_12";
		break;
		case "Interception_12":
			dialog.text = "I think everything will be fine.";
			link.l1 = "Excellent. Go to the clan and keep your finger on the pulse.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LCS_EndScriptInterception");
		break;

		case "BarmenDead_1":
			dialog.text = "I'm all ears.";
			link.l1 = "I think there should be an investigation.";
			link.l1.go = "BarmenDead_2";
		break;
		case "BarmenDead_2":
			dialog.text = "Hmm, good idea. Maybe you can go to the murder scene now and find something that will point us to the perpetrator? Don't you want to?";
			link.l1 = "Maybe I'll go!";
			link.l1.go = "BarmenDead_3";
		break;
		case "BarmenDead_3":
			dialog.text = "Go, "+ GetSexPhrase("my friend", "girlfriend") +", and search properly. Only this time I won't be so gullible... Do you understand me?";
			link.l1 = "Hmm, not really...";
			link.l1.go = "BarmenDead_4";
		break;
		case "BarmenDead_4":
			dialog.text = "Now, before deciding to punish someone, I will conduct my own inquiry.";
			link.l1 = "Yeah, I get it now. An inquest is what I want. Will you inform me about the progress of the investigation?";
			link.l1.go = "BarmenDead_5";
		break;
		case "BarmenDead_5":
			dialog.text = "It's unlikely. And anyway, I don't really understand your zeal. Were you friends and comrades with Hill? What connects you?";
			link.l1 = "Nothing special. We just talked to him...";
			link.l1.go = "BarmenDead_6";
		break;
		case "BarmenDead_6":
			dialog.text = "If that's the case, then don't get into it. You're an empty place in the City. Don't take on too much, you might overdo it. Is that clear?";
			link.l1 = "Understood, Admiral.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toSeekOldCitizen";
			AddQuestRecord("ISS_MainLine", "27");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ate", "la"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("xia", "as"));
			AddQuestUserData("ISS_MainLine", "sSex2", GetSexPhrase("", "la"));
			pchar.quest.LSC_SaveSesilGalard.win_condition.l1          = "location";
			pchar.quest.LSC_SaveSesilGalard.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_SaveSesilGalard.function                  = "LSC_SaveSesilGalard";
		break;
		//замочили касперов
		case "CasperDead_1":
			dialog.text = "What a coincidence! Well, tell me, what happened on the San Gabriel?";
			link.l1 = "Well, remember, you told me to investigate the murder of Hill Brunner on my own?";
			link.l1.go = "CasperDead_2";
		break;
		case "CasperDead_2":
			dialog.text = "Did I say that? Are you crazy about?!";
			link.l1 = "Well, you didn't instruct me to do this, but you didn't forbid it either. So I, with your permission, went to look for evidence. I came on 'San Gabriel'.";
			link.l1.go = "CasperDead_3";
		break;
		case "CasperDead_3":
			dialog.text = ""+ GetSexPhrase("Idiot", "Oh my gosh") +"! Didn't I tell you not to go in there?";
			link.l1 = "No, you said they have their own laws on the San Gabriel. I didn't know that these laws are so bloodthirsty! Anyway, they attacked me, so I had to defend myself...";
			link.l1.go = "CasperDead_4";
		break;
		case "CasperDead_4":
			dialog.text = "So what?";
			link.l1 = "I defended myself. The Casper clan no longer exists... Just like the Narwhal clan, though. The city is now free of scoundrels of all stripes!";
			link.l1.go = "CasperDead_5";
		break;
		case "CasperDead_5":
			dialog.text = "I can't believe...";
			link.l1 = "Why believe? You can check it out.";
			link.l1.go = "CasperDead_6";
		break;
		case "CasperDead_6":
			dialog.text = "Yes you are "+ GetSexPhrase("some kind of devil", "a real devil") +"! You slaughtered two clans!";
			link.l1 = "I dare say one of them is on your direct orders.";
			link.l1.go = "CasperDead_7";
		break;
		case "CasperDead_7":
			dialog.text = "Oh... Did you find someone on the San Gabriel? Except for the Caspers, of course.";
			link.l1 = "Yes. A man named Henrik Wedeker sent his regards to you.";
			link.l1.go = "CasperDead_8";
		break;
		case "CasperDead_8":
			dialog.text = "So the Mechanic is alive...";
			link.l1 = "What's going to happen to him? He didn't attack me, well, I didn't touch him...";
			link.l1.go = "CasperDead_9";
		break;
		case "CasperDead_9":
			dialog.text = "Hmm, not touched... That's what, "+ GetSexPhrase("'cool Walker'", "cool girl") +"! You really tired me out with your antics. I'm very angry with you right now and I'm thinking about sending you to the bottom with a load around your neck!";
			link.l1 = ""+ GetSexPhrase("Admiral, I won't do this anymore!..", "I actually did the work of your police idlers. The 'Caspers' are criminals, and I...") +"";
			link.l1.go = "CasperDead_10";
		break;
		case "CasperDead_10":
			dialog.text = "Shut up, "+ GetSexPhrase("half-wit", "cheeky girl") +"! Only because I want to end this string of murders. Whoever is to blame for this, I don't want to conduct any further investigations. Let's assume that the Caspers are to blame for everything, and let's put an end to this. Is that clear to you?";
			link.l1 = "Yes, Admiral.";
			link.l1.go = "CasperDead_11";
		break;
		case "CasperDead_11":
			dialog.text = "Okay. You must understand that now there are no exceptions in the City. There are no more clans, so now there are no territories that are not covered by the Law of the City. Is that clear to you?";
			link.l1 = "Yes, Admiral.";
			link.l1.go = "CasperDead_12";
		break;
		case "CasperDead_12":
			dialog.text = "If you lay a finger on anyone else...";
			link.l1 = "Admiral, I know the Law. The right to life for citizens is all very right.";
			link.l1.go = "CasperDead_13";
		break;
		case "CasperDead_13":
			dialog.text = "Well, look at me!.. Tell Vedeker to sit on the San Gabriel and sniff into a tube. If he wanders around the city and scares people with his nonsense, I'll throw him behind bars!Anyway, I'd better send someone from the police to him. You're free.";
			link.l1 = "Thank you, Admiral! Honestly, I wanted the best...";
			link.l1.go = "CasperDead_14";
		break;
		case "CasperDead_14":
			dialog.text = "Get out!!";
			link.l1 = "Goodbye, Chad.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "seekMillionAndHalf";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Let's see. What kind of goods are we talking about?",
				"You already asked about this.",
				"Already asked...",
                "You already asked me about these goods. I don't know anything!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I need gunpowder and weapons.",
				"yeah... Sorry, I forgot .",
                "Oh, yeah.",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Why?";
			link.l1 = "Necessary, Admiral...";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Your shenanigans with Vedeker won't do you any good! You must comply with the food of the City Law.";
			link.l1 = "I do. There is nothing in the Law prohibiting the search for weapons or gunpowder.";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "I am withdrawing all weapons and gunpowder from newly arriving ships. Everything is in my warehouse at the residence.";
			link.l1 = "Can you share it?";
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = "Why on earth would that be? To my question, why do you need this, you did not give an answer. What if you want to put a barrel of gunpowder somewhere and then blow it up?";
			link.l1 = "Come on, Admiral, I'm not crazy.";
			link.l1.go = "SeekGoods_5";
		break;
		case "SeekGoods_5":
			dialog.text = "For the safety of the City, I am seizing gunpowder and weapons. You won't get anything.";
			link.l1 = "Clear...";
			link.l1.go = "SeekGoods_6";
		break;
		case "SeekGoods_6":
			dialog.text = "You know, you've become popular among the citizens. If it weren't for this circumstance, I think I would have fed you to those creatures that are swarming under the city.";
			link.l1 = "Have you seen them, these creatures?";
			link.l1.go = "SeekGoods_7";
		break;
		case "SeekGoods_7":
			dialog.text = "No one saw them. And those who saw them looked at them for the last time in their lives.";
			link.l1 = "I saw them, Admiral...";
			link.l1.go = "SeekGoods_8";
		break;
		case "SeekGoods_8":
			dialog.text = "Yes? Where?";
			link.l1 = "At the bottom.";
			link.l1.go = "SeekGoods_9";
		break;
		case "SeekGoods_9":
			dialog.text = "Oh... Now I know for sure that you shouldn't even go near gunpowder. Communication with a Mechanic has a detrimental effect on your psyche.I'm watching you. Keep in mind, as soon as you make the slightest mistake, I will send you to Tartarus, to prison. Do you understand me?";
			link.l1 = "I understand, Admiral...";
			link.l1.go = "SeekGoods_10";
		break;
		case "SeekGoods_10":
			dialog.text = "Now go, I'm not detaining you.";
			link.l1 = "Okay, Chad. But you shouldn't be so...";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "57");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
			pchar.questTemp.LSC.additional.powder = true; //флаг на дачу квеста ментом
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("So what?",
				"We've already talked about this.",
				"I don't want to hear anything about it!",
                "Get out!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("There is reason to believe that this storm will be very strong. Admiral, the city may collapse.",
				"yeah... Sorry, I forgot .",
                "As you know...",
				"Good, good...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "Well, you're crazy after all...";
			link.l1 = "I'm completely sober, Chad. But you should open your eyes and admit, first of all to yourself, that things are bad.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "What?!!";
			link.l1 = "You know better than most what a City is. He's holding on to something! You're putting people's lives at risk by forbidding them to try to sail away from here.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "You can also talk to me about the City! The mechanic is a competent person, but a coward and an alarmist. We've seen so many storms here that his theories are already ridiculous. I told him to keep his thoughts to himself...";
			link.l1 = "And he holds it... Listen to me, Chad, it's not a storm coming here, it's a real storm...";
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = "How do you know?";
			link.l1 = "Henrik said. He has a device that predicts storms.";
			link.l1.go = "SeekCrew_5";
		break;
		case "SeekCrew_5":
			dialog.text = "I've heard enough of this nonsense from the Mechanic. That's what, "+ GetSexPhrase("buddy", "girlfriend") +", I'll tell you. And I advise you to remember this well, because this is the last time I'm warning you.Since I am the admiral here, I will decide when we leave the City. Is that clear?";
			link.l1 = "Chad, I don't pretend to be an admiral. I will not hide it, I used to want ... But now it's a matter of life and death.";
			link.l1.go = "SeekCrew_6";
		break;
		case "SeekCrew_6":
			dialog.text = "I used to want? Hmm, I knew you wouldn't calm down...";
			link.l1 = "Admiral, that's not what we're talking about. We need to save our skins, and there is a way! All your plans will remain unfulfilled if Vedeker is right.";
			link.l1.go = "SeekCrew_7";
		break;
		case "SeekCrew_7":
			dialog.text = "Heh, tell me more about my plans!Well, thank you for the informative conversation. And now you can be free. And don't you dare scare the citizens, or I'll unscrew your head! Keep in mind that I'm not going to tolerate you anymore.";
			link.l1 = "Well, I did everything I could. It's a pity that you're not listening to me...";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "60");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("xia", "as"));
		break;
		//финальный диалог
		case "fightTalking":
			dialog.text = "Your time is up. Are you ready to death?";
			link.l1 = "Um.. well, I wasn't prepared actually...";
			link.l1.go = "fightTalking_1";
		break;
		case "fightTalking_1":
			dialog.text = "You have a couple of seconds.";
			link.l1 = "Where's Vedeker?";
			link.l1.go = "fightTalking_2";
		break;
		case "fightTalking_2":
			dialog.text = "You used them incorrectly.";
			link.l1 = "Oh, it's a pity...";
			link.l1.go = "fightTalking_3";
		break;
		case "fightTalking_3":
			LAi_LocationFightDisable(loadedLocation, false);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorTypeNoGroup(NPChar);
			//LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuestFunction("LSC_figtInResidence");
            DialogExit();
		break;

		//освободить мужа Элис Тейлор
		case "ELTHusb_begin":
			dialog.text = NPCStringReactionRepeat("What's it to you?",
				"I've already said it all.",
				"It seems like we've cleared everything up.",
                "Well fools, but you, "+ GetSexPhrase("buddy", "girlfriend") +"!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Hmm... Well, I'm interested.",
				"Yes, yes, I remember.",
                "Of course.",
				"And that's right, such a fool. Why do I ask the same thing - I don't understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_begin_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_begin_1":
			dialog.text = "Don't be interested anymore. It's none of your business.";
			link.l1 = "Well, I'm a citizen of the City, so to speak...";
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = "It's all. I don't want to talk about this cretin anymore!";
			link.l1 = "Okay, Admiral, whatever you say.";
			link.l1.go = "exit";
		break;

		case "ELTHusb_SF":
			dialog.text = "Well, take him a bottle of wine...";
			link.l1 = "Heh, you can do that. I'm the only one who wants to help free him.";
			link.l1.go = "ELTHusb_SF_1";
		break;
		case "ELTHusb_SF_1":
			dialog.text = "No, "+ GetSexPhrase("buddy", "" + pchar.name + "") +", this is not going to happen! That's enough, the whole City is already tired of him. He'll rot in his cage.";
			link.l1 = "Did you decide to kill him?";
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = "I have the right to do this!But no, he just got a life sentence.";
			link.l1 = "Damn, what did he do? Admiral, tell me, please.";
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = "Okay, I'll tell you. Although I don't understand why you need it.This brave man put a knife to my throat and demanded to let him go home to Plymouth immediately.";
			link.l1 = "Listen, he was drunk and doesn't remember anything. Will you get into the situation and forgive him?";
			link.l1.go = "ELTHusb_SF_4";
		break;
		case "ELTHusb_SF_4":
			dialog.text = "No, let's not hope for that. And by the way, I notified his wife, Alice. A drunkard and a rowdy should be in jail! The toothpick he was waving around here doesn't bother me.";
			link.l1 = "Hmm, and I also think that his knife is like a mosquito bite for you.";
			link.l1.go = "ELTHusb_SF_5";
		break;
		case "ELTHusb_SF_5":
			dialog.text = "But what puzzles me is that he doesn't control himself when drunk. What if tomorrow, after another visit to the tavern, he decides to set fire to some ship? In general, Taylor needs to be isolated from society.";
			link.l1 = "Damn, it looks like you're right...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.ElisHusband = "toWaitress";
			AddQuestRecord("ISS_ElisHusband", "7");
		break;

		case "ELTHusb_good":
			dialog.text = "You're already tired...";
			link.l1 = "Listen, Gilles Barou sent Taylor to you for a heart-to-heart talk.";
			link.l1.go = "ELTHusb_good_1";
		break;
		case "ELTHusb_good_1":
			dialog.text = "Is that so?";
			link.l1 = "Yeah. Gilles Barou promised me to talk to you and apologize for the bad joke.";
			link.l1.go = "ELTHusb_good_2";
		break;
		case "ELTHusb_good_2":
			dialog.text = "Well, that changes things a bit, please, I'll give Taylor another chance to settle down.";
			link.l1 = "Admiral, I think this is a very good decision.";
			link.l1.go = "ELTHusb_good_3";
		break;
		case "ELTHusb_good_3":
			dialog.text = "I'll send a policeman to Gabriel's Tartarus, and you can visit Alice and tell her that I'm releasing Maxim.";
			link.l1 = "Great! I will do that. Thank you, Admiral...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.ElisHusband = "toElisGood";
			AddQuestRecord("ISS_ElisHusband", "10");
			sld = characterFromId("MaximTailor");
			ChangeCharacterAddress(sld, "none", "");
		break;
		//квест со скелетом Декстера
		case "LostDecster":
			dialog.text = "About whom?!";
			link.l1 = "Leighton Dexter.";
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = "Hmm... Well, ask your question.";
			link.l1 = "Where did he go? No one knows. And you seemed to be friends...";
			link.l1.go = "LostDecster_2";
		break;
		case "LostDecster_2":
			dialog.text = "Well, I'll tell you.Playton Dexter turned out to be a very greedy man. He bit off more than he could swallow. That's why he's being punished.";
			link.l1 = "How is it, punished? Where is he now?";
			link.l1.go = "LostDecster_3";
		break;
		case "LostDecster_3":
			dialog.text = "He's guarding my money.";
			link.l1 = "Is this a punishment?";
			link.l1.go = "LostDecster_4";
		break;
		case "LostDecster_4":
			dialog.text = "Did I satisfy your curiosity in some way?";
			link.l1 = "Hmm... Well, in a way.";
			link.l1.go = "LostDecster_5";
		break;
		case "LostDecster_5":
			dialog.text = "Okay. And now you satisfy mine. Why are you asking about Leighton?";
			link.l1 = "Admiral, nothing special. Idle curiosity, nothing more. I'm exploring the City, getting to know people...";
			link.l1.go = "LostDecster_6";
		break;
		case "LostDecster_6":
			dialog.text = "Understood. Regarding Dexter, I hope you understand that he is busy. Therefore, you don't have to look for him to get acquainted.";
			link.l1 = "Okay, Admiral, whatever you say. Thanks for the conversation.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.lostDecster = "seekBox";
			AddQuestRecord("LSC_findDekster", "5");
		break;

	}
}
