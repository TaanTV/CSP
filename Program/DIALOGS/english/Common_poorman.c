#include "DIALOGS\english\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Poorman\" + NPChar.City + "_Poorman.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // вызов диалога по городам <--

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				//если ГГ начал мочить бродяг -->
				if (pchar.questTemp.LSC == "PoorMurderBegin")
				{
					dialog.text = LinkRandPhrase("I heard that you killed beggars in other cities. Why are you doing this?",
						"I think I know who you are. Why are you killing us?",
						"What do you need from us? What have we done to you? Why kill harmless beggars?");
					link.l1 = LinkRandPhrase("It's all about money...", "I was promised a very big reward for this job!", "That's life... In general, it's all about self-interest, my friend.");
					link.l1.go = "exit";
					break;
				}
				//<-- если ГГ начал мочить бродяг
				//зачарованный город -->
				if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
				{
					dialog.text = "Well, the townspeople have dispersed in earnest. I don't care about that.";
					link.l1 = "I see...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
				{
					dialog.text = "Do you want to deal with this case? Well, as you know... I don't care.";
					link.l1 = "Very good.";
					link.l1.go = "exit";
					break;
				}
				//<-- зачарованный город
				dialog.text = LinkRandPhrase("Hello. My name is " + GetFullName(npchar) + ". I don't think it would be nice for you to meet me, but maybe you'll remember my name...",
					"Greetings, " + GetAddress_Form(NPChar) +  ". My name is " + GetFullName(npchar) + ".",
					"My name is " + GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + ". Glad to meet you.");
				link.l1 = RandPhraseSimple("Greetings.", "Hello.");
				link.l1.go = "First time";
				npchar.quest.meeting = "1";
			}
			else
			{
				//если ГГ начал мочить бродяг -->
				if (pchar.questTemp.LSC == "PoorMurderBegin")
				{
					dialog.text = LinkRandPhrase("I heard that you "+ GetSexPhrase("killed", "killed") +" beggars in other cities. Why are you doing this?",
						"I think I know who you are. Why are you killing us?",
						"What do you need from us? What have we done to you? Why kill harmless beggars?");
					link.l1 = LinkRandPhrase("It's all about money...", "I was promised a very big reward for this job!", "That's life... In general, it's all about self-interest, my friend.");
					link.l1.go = "exit";
					break;
				}
				//<-- если ГГ начал мочить бродяг
				dialog.text = NPCStringReactionRepeat("Oh, you see what it's come to...",
					"It's not easy to live by begging...",
					"I wish I could get out of poverty!",
					"You again?", "block", 1, npchar, Dialog.CurrentNode);
				//разговарием с нищими о наезде
				if (pchar.questTemp.LSC == "SignOnPoorMurder" || pchar.questTemp.LSC == "PoorIsGood")
				{
					if (CheckAttribute(pchar, "questTemp.LSC.qtyTalk.headPoormanId") && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id)
					{
						link.l1 = "I heard that you wanted to talk to me.";
						link.l1.go = "PoorHeadMan";
						npchar.quest.talk = true; //больше не говорить
						break;
					}
					if (!CheckAttribute(npchar, "quest.talk"))
					{
						if (!CheckAttribute(pchar, "questTemp.LSC.qtyTalk")) pchar.questTemp.LSC.qtyTalk = 0;
						pchar.questTemp.LSC.qtyTalk = sti(pchar.questTemp.LSC.qtyTalk) + 1; //инкремент на базары по душам
						if (sti(pchar.questTemp.LSC.qtyTalk) > 4) pchar.questTemp.LSC.qtyTalk = 4;
						switch (pchar.questTemp.LSC.qtyTalk)
						{
						case "1":
							link.l1 = "Listen, I'm very interested, are the beggars in the cities a gang of thugs or something?";
							npchar.quest.talk = true; //больше не говорить
							break;
						case "2":
							link.l1 = "Listen, I have a rather unusual case for you.";
							npchar.quest.talk = true; //больше не говорить
							break;
						case "3":
							link.l1 = "You know, I have a question for you. Very strange, at first glance...";
							npchar.quest.talk = true; //больше не говорить
							break;
						case "4":
							link.l1 = "I want to ask you a question, buddy.";
							break;
						}
						link.l1.go = "GoodTalk_" + pchar.questTemp.LSC.qtyTalk;
						break;
					}
				}
				//----------------------------------------------------------------
				link.l1 = HeroStringReactionRepeat("I see. Well, it's okay.",
					"It's understandable. You can't walk around with this money, go...",
					"Then you don't need to wipe your pants here, but do something about it.",
					"Yeah. Is it really "+ GetSexPhrase("tired", "tired") +"?", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("What do you need?", "What do you want?");
				link.l2.go = "Whants";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the city?", "Oh, I'd listen the latest gossip...");
				link.l3.go = "rumours_poor";
				// --------------- линейка ГПК ---------------
				if (CheckCharacterItem(pchar, "letter_LSC") && (pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id))
				{
					//нашёл письмо в сундуке Виллемстада
					if (pchar.questTemp.LSC == "CanFoundStuvesantKey")
					{
						link.l1 = "Listen, it seems to me that I found something very interesting at the Stuyvesant residence!";
						link.l1.go = "FoundLetter";
					}
					//базар о том, что нашёл причину заказа на нищих
					if (pchar.questTemp.LSC == "readyGoLSC" && GetCharacterFreeItem(pchar, "keyQuestLSC")==0)
					{
						link.l1 = "You know, I managed to solve this tangle!";
						link.l1.go = "GoLSC";
					}
				}
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("No, why immediately"+ GetSexPhrase("tired", "tired") +"? I'm not too busy like you"+ GetSexPhrase("myself", "myself") +"you see...",
				"Not "+ GetSexPhrase("tired", "tired") +", but in the order of "+ GetSexPhrase("tired", "tired") +". Although I am a beggar, I am also a human being.");
			link.l1 = "Heh, I see...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Hmm, " + GetAddress_Form(NPChar) +  " there are bad rumors about you. But I believe in people, even people like you. I ask you to give me money for food and drink, have mercy.",
					"Please, " + GetAddress_Form(NPChar) +  "! Do not ignore the unfortunate man, give him food...");
				link.l1 = RandPhraseSimple("I won't give you anything.", "You'll do fine.");
				link.l1.go = "exit";
				Link.l2 = "Okay. And how much money do you need?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("From you? Nothing.", "Nothing is needed, " + GetAddress_Form(NPChar) + "Thank you.");
				link.l1 = RandPhraseSimple("Hmm, okay.", "You're having a good life, buddy.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "I won't give up a penny, " + GetAddress_Form(NPChar) + ". As much as your purse and charity will allow you...";
			Link.l1.edit = 2;
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "It's a sin to laugh at sick people...";
				link.l1 = "Ha ha ha, what did you think, you fool, I'll give you money?!";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Thanks for " + FindRussianMoneyString(iTemp) + ", " + GetAddress_Form(NPChar) + ". I'll buy bread with this money...";
				link.l1 = "Come on, go get some food, tramp.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 100 && iTemp <= 1000)
			{
				dialog.text = "Thank you, " + GetAddress_Form(NPChar) + ". This money is enough for me for a week!";
				link.l1 = ""+ GetSexPhrase("I was glad", "I was glad") +"help.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Thank you, " + GetAddress_Form(NPChar) + ". I'll tell everyone about your kindness!";
				link.l1 = "Well, it's not necessary...";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, sti(iTemp/2000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 5000 && iTemp <= 50000)
			{
				dialog.text = "Thank you, dear " + GetAddress_Form(NPChar) + ". May the Lord protect you...";
				link.l1 = "Yes, the patronage of the Lord will certainly not hurt me!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), sti(iTemp/10000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 50000 && iTemp <= 100000)
			{
				dialog.text = "Thank you, " + GetAddress_Form(NPChar) + ". I wish you good luck!";
				link.l1 = "Thanks, buddy.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", sti(iTemp/5000));
				AddCharacterExpToSkill(pchar, "Fortune", sti(iTemp/5000));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 100000)
			{
				dialog.text = "Listen, " + GetAddress_Form(NPChar) + " Are you out of your mind? You give me " + FindRussianMoneyString(iTemp) + "! I won't take such money, I feel like there's some kind of catch here... Go away!";
				link.l1 = "Well, as you know...";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
			}
		break;
		//линейка ГПК, разговоры по душам с нищими после заказа
		case "GoodTalk_1":
			dialog.text = "K-heh, k-heh... What?!!";
			link.l1 = "Well, well, how can I tell you... In general, there are people here who have you as a bone in their throat.";
			link.l1.go = "GoodTalk_1_1";
		break;
		case "GoodTalk_1_1":
			dialog.text = "I don't even know what to say... "+ GetSexPhrase("By Myself", "By Myself") +"You probably understand that we are homeless people, the attitude towards us is dismissive.";
			link.l1 = "Enough to wish you dead?";
			link.l1.go = "GoodTalk_1_2";
		break;
		case "GoodTalk_1_2":
			dialog.text = "Death?! Nah, that's unlikely. Listen, what are you talking about? It scares me.";
			link.l1 = "Heh, and he's doing the right thing, which is scary. In general, you don't know who your well-wishers might be, as I understand it.";
			link.l1.go = "GoodTalk_1_3";
		break;
		case "GoodTalk_1_3":
			dialog.text = "I don't know, of course! You're with them "+ GetSexPhrase("communicated", "communicated") +".";
			link.l1 = ""+ GetSexPhrase("Communicated", "Communicated") +" I'm through a representative, so to speak. I'm interested in who's behind this... Well, be careful, friend.";
			link.l1.go = "GoodTalk_1_4";
		break;
		case "GoodTalk_1_4":
			dialog.text = "Yes, I will try now, although I have few opportunities for this.";
			link.l1 = "I understand. But I'm "+ GetSexPhrase("warned", "warned") +".";
			link.l1.go = "exit";
		break;

		case "GoodTalk_2":
			dialog.text = "Come on, state the point.";
			link.l1 = "You know, I'd really like to know who you've messed up so much that they just can't see you anymore?";
			link.l1.go = "GoodTalk_2_1";
		break;
		case "GoodTalk_2_1":
			dialog.text = "Can't they see? And who is it - us?";
			link.l1 = "All beggars on the islands in the Caribbean.";
			link.l1.go = "GoodTalk_2_2";
		break;
		case "GoodTalk_2_2":
			dialog.text = "I don't even know what to say... And what, did you really mess up?";
			link.l1 = "Yeah. So much so that they want you dead.";
			link.l1.go = "GoodTalk_2_3";
		break;
		case "GoodTalk_2_3":
			dialog.text = "Ho-oh, wow!.. Well, you "+ GetSexPhrase("yourself", "yourself") +"You probably understand that the harm we do to others is stink and fleas. If someone is ready to kill us because of this, then I don't understand anything in this life at all!";
			link.l1 = "So I'm saying that I don't understand the origins of such hatred.";
			link.l1.go = "GoodTalk_2_4";
		break;
		case "GoodTalk_2_4":
			dialog.text = "Sorry, but they are also completely unclear to me. I'm at a complete loss...";
			link.l1 = "Understood. Well, I'm sorry that "+ GetSexPhrase("distracted", "distracted") +"from business.";
			link.l1.go = "GoodTalk_2_5";
		break;
		case "GoodTalk_2_5":
			dialog.text = "Nothing. I wouldn't say I'm too busy...";
			link.l1 = "Well, nevertheless.";
			link.l1.go = "exit";
		break;

		case "GoodTalk_3":
			dialog.text = "I'm listening to you, ask.";
			link.l1 = "I'm here "+ GetSexPhrase("bumped", "bumped") +" with a rather unexpected circumstance... In general, the fact is that there are people in the Caribbean who are very unhappy with your brother.";
			link.l1.go = "GoodTalk_3_1";
		break;
		case "GoodTalk_3_1":
			dialog.text = "Yeah, I know who you are!";
			link.l1 = "Hmm, so who am I?";
			link.l1.go = "GoodTalk_3_2";
		break;
		case "GoodTalk_3_2":
			dialog.text = "You - "+ GetSexPhrase("that captain", "that") +", which finds out who hates us and supposedly wants us dead. Rumors have already spread among our brother.";
			link.l1 = "Yes, that's me. But I'm telling the truth without any 'ostensibly'. And I would recommend you to take all this seriously - a lot of money is being offered for this job.";
			link.l1.go = "GoodTalk_3_3";
		break;
		case "GoodTalk_3_3":
			dialog.text = "Anyway, one of us wants to talk to you about this topic.";
			link.l1 = "And who is this?";
			link.l1.go = "GoodTalk_3_4";
		break;
		case "GoodTalk_3_4":
			pchar.questTemp.LSC.qtyTalk.headPoormanId = GetPoorHeadManId(npchar);
			sld = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			dialog.text = "His name is " + GetFullName(sld) + ". He wanders in " + XI_ConvertString("Colony" + sld.city + "Voc") + ".";
			link.l1 = "Understood. Well, I guess I'll visit him on occasion.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_PoorsMurder", "3");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData("ISS_PoorsMurder", "sCity", XI_ConvertString("Colony" + sld.city + "Acc"));
			AddQuestUserData("ISS_PoorsMurder", "sName", GetFullName(sld));
		break;

		case "GoodTalk_4":
			dialog.text = "I'm listening to you.";
			link.l1 = "Who do you think might be interested in the disappearance of beggars?";
			link.l1.go = "GoodTalk_4_1";
		break;
		case "GoodTalk_4_1":
			sld = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			dialog.text = "I know you, but I can't answer your question. You need to go to " + XI_ConvertString("Colony" + sld.city + "Acc") + ", there you will find one of our own named " + GetFullName(sld) + ". He wanted to talk to you about it.";
			link.l1 = "Understood. I will do that.";
			link.l1.go = "exit";
		break;
		//основной бродяга
		case "PoorHeadMan":
			dialog.text = "If you are captain " + GetFullName(pchar) + ", then that's it.";
			link.l1 = "That's exactly my name.";
			link.l1.go = "PoorHeadMan_1";
		break;
		case "PoorHeadMan_1":
			dialog.text = "Well, that's good. As far as I could understand, you're trying to find out about the people we've really annoyed. And so much so that they are ready to kill us. Is everything right?";
			link.l1 = "Well, yes. I will only add that not to kill, but to hire a murderer.";
			link.l1.go = "PoorHeadMan_2";
		break;
		case "PoorHeadMan_2":
			dialog.text = "Hmm, this is a significant factor... And what was the name of the man who talked to you about it?";
			link.l1 = "Oliver Trust.";
			link.l1.go = "PoorHeadMan_3";
		break;
		case "PoorHeadMan_3":
			dialog.text = "This name is unfamiliar to me... In general, I have one thought.";
			link.l1 = "Explain.";
			link.l1.go = "PoorHeadMan_4";
		break;
		case "PoorHeadMan_4":
			dialog.text = "There was a story in Willemstad, Curacao, which, in my opinion, bears some resemblance to what happened to you. In general, we had one friend in misfortune who decided to settle with the Dutch, in Curacao. His name was Teaser Dan\n"+
				"So, he lived there for about a month, and after that time he caught the eye of Governor-General Peter Stuyvesant. Since then, Teaser began to have problems with the soldiers in the city, then with the commandant... As a result, he was kicked out of Willemstad, and nothing more is known about him.";
			link.l1 = "Hmm, and what does this have to do with my case?";
			link.l1.go = "PoorHeadMan_5";
		break;
		case "PoorHeadMan_5":
			dialog.text = "Listen further. We started to find out what was going on with Teaser, where he had gone, and found out something about Stuyvesant. Few people know about this, but Stuyvesant is the largest supplier of slaves to the New World from Africa!"+
				"He works closely with the Dutch West India Company, and they do this kind of thing -you'll be pumped.";
			link.l1 = "So what?";
			link.l1.go = "PoorHeadMan_6";
		break;
		case "PoorHeadMan_6":
			dialog.text = "And the fact that almost all of ours are former slaves. Do you think we're lazy and lazy? Nothing like that, it's just that by coincidence we had to go through this hell and lose our health. Whites are often given freedom here, as colonists are needed "+
				"But not every former slave can plow the land and uproot stumps after months spent in the hold of a galleon on the way here. And Stuyvesant, apparently, does not like former slaves who have not done anything useful.";
			link.l1 = "Hmm, it all sounds a bit far-fetched...";
			link.l1.go = "PoorHeadMan_7";
		break;
		case "PoorHeadMan_7":
			dialog.text = "Maybe, but that's all I know and can assume. I do not know any other haters of beggars, equally rich and influential. So if you want to know something about this case, then I think you need to look at the Willemstad residence.";
			link.l1 = "And what do I need to look?";
			link.l1.go = "PoorHeadMan_8";
		break;
		case "PoorHeadMan_8":
			dialog.text = "Papers, "+ GetSexPhrase("my friend", "my lady") +", business correspondence. Everything I've told you here is really far-fetched. It seems to me that there is something much more weighty behind the offer of this Trust than the usual dislike of anyone.";
			link.l1 = "Hmm, I think so too. Something is serious here, given the scope of the idea and the amount of the fee.";
			link.l1.go = "PoorHeadMan_9";
		break;
		case "PoorHeadMan_9":
			dialog.text = "Well, I said everything I wanted to say. Thank you for "+ GetSexPhrase("listened", "listened") +". If you find something worth your attention, contact me right away, we'll think about it... And thanks for not "+ GetSexPhrase("caused", "caused") +"no harm to us.";
			link.l1 = "You're welcome. Thank you for the information.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toVillemstadResidence";
			AddQuestRecord("ISS_PoorsMurder", "4");
			//сработает прерывание, чтобы показать геймеру, где нужный сундук
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1 = "locator";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.location = "Villemstad_TownhallRoom";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.locator_group = "box";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.locator = "private2";
			pchar.quest.LSC_enterStuvesantBox.function = "LSC_enterStuvesantBox";
		break;
		//базар с основным после нахождения письма
		case "FoundLetter":
			dialog.text = "Well, let's see what you have there...";
			link.l1 = "Here's the letter I got at the Stuyvesant residence. This is a correspondence between him and the Dutch West India Company. It clearly follows from it that it was this trading company that started the destruction of beggars.";
			link.l1.go = "FoundLetter_1";
		break;
		case "FoundLetter_1":
			dialog.text = "Uh-huh, I see...";
			link.l1 = "There is an island mentioned there. And luxury items. And for some reason, all this is fixated on tramps. Tell me, buddy, what's the matter here.";
			link.l1.go = "FoundLetter_2";
			TakeItemFromCharacter(pchar, "letter_LSC");
		break;
		case "FoundLetter_2":
			dialog.text = "Hmm, I don't even know how to say it... I believe that the mentioned island is the mythical Island of Justice, so popular among beggars.";
			link.l1 = "What?";
			link.l1.go = "FoundLetter_3";
		break;
		case "FoundLetter_3":
			dialog.text = "Well, tramps, you understand yourself, people are destitute - broken destinies, broken lives. And although there is no health, no housing, no money, but I want to believe in something good in the future. Most of our people believe in the existence of the so-called Island of Justice, often this belief saves their lives.";
			link.l1 = "Tell us more about this Island. Everything you know and what they say about you.";
			link.l1.go = "FoundLetter_4";
		break;
		case "FoundLetter_4":
			dialog.text = "They say that somewhere in the area there is an Island, but not of natural origin. So, law and justice reign on this island, life there is favorable to a good person. I don't believe much in it myself, there is no justice on earth...";
			link.l1 = "Hmm, but the letter says that this Island exists! Read for yourself: 'It turns out that the rumors about the island have a real basis...'";
			link.l1.go = "FoundLetter_5";
		break;
		case "FoundLetter_5":
			dialog.text = "Well, I don't know...";
			link.l1 = "Why did the rumors start at all? How did it all start?";
			link.l1.go = "FoundLetter_6";
		break;
		case "FoundLetter_6":
			dialog.text = "That's how it started with Teaser Dan. He was a little out of his mind - he had survived several shipwrecks. All our people told him not to go to Curacao, but he decided to live there all the same... In general, he claimed that he had lived on this Island for how many months, so he chatted up fairy tales.";
			link.l1 = "Hmm, and the Dutch West India Company believes that there are not such fairy tales... And where is Teaser now, you say?";
			link.l1.go = "FoundLetter_7";
		break;
		case "FoundLetter_7":
			dialog.text = "Missing. We couldn't find him. Disappeared without a trace.";
			link.l1 = "I remember you saying that he started having problems in Willemstad. He was kicked out of the city, it seems...";
			link.l1.go = "FoundLetter_8";
		break;
		case "FoundLetter_8":
			dialog.text = "Yes, that's right. After he caught the eye of Stuyvesant.";
			link.l1 = "Apparently, I have to head for Curacao again...";
			link.l1.go = "FoundLetter_9";
		break;
		case "FoundLetter_9":
			dialog.text = "Well, good luck with this! Thanks for the help, "+ GetSexPhrase("buddy", "" + pchar.name + "") +".";
			link.l1 = "Be healthy, buddy.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTalkStuvesant";
			pchar.questTemp.LSC.poorName = GetFullName(npchar));
			AddQuestRecord("ISS_PoorsMurder", "7");
			AddQuestUserData("ISS_PoorsMurder", "sName", pchar.questTemp.LSC.poorName);
			//снимаем прерывание на завал нищих, деньги уже не получить
			pchar.quest.ISS_Murder1.over = "yes";
			pchar.quest.ISS_Murder2.over = "yes";
			pchar.quest.ISS_Murder3.over = "yes";
			pchar.quest.ISS_Murder4.over = "yes";
			pchar.quest.ISS_Murder5.over = "yes";
			pchar.quest.ISS_Murder6.over = "yes";
			pchar.quest.ISS_Murder7.over = "yes";
			pchar.quest.ISS_Murder8.over = "yes";
			pchar.quest.ISS_Murder9.over = "yes";
			pchar.quest.ISS_Murder10.over = "yes";
			pchar.quest.ISS_Murder11.over = "yes";
			pchar.quest.ISS_Murder12.over = "yes";
			pchar.quest.ISS_Murder13.over = "yes";
			pchar.quest.ISS_Murder14.over = "yes";
			pchar.quest.ISS_Murder15.over = "yes";
			pchar.quest.ISS_Murder16.over = "yes";
			pchar.quest.ISS_Murder17.over = "yes";
		break;
		//базар с основным после завала Оливера Траста
		case "GoLSC":
            dialog.text = "Great! Well, tell me, what's the matter?";
            link.l1 = "You know, you were right in the assumption that you made at the very beginning of our communication. It's really about Teaser Dan and his Island.";
            link.l1.go = "GoLSC_1";
		break;
		case "GoLSC_1":
			dialog.text = "Please explain!";
			link.l1 = "I can't talk much yet. But I will say that the Island of Justice, about which Teaser talked so much, is not a fiction. It's true, and I'm gonna go there!";
			link.l1.go = "GoLSC_2";
		break;
		case "GoLSC_2":
			dialog.text = "I can't believe it!..";
			link.l1 = "There is also very bad news - Teaser Dan is dead.";
			link.l1.go = "GoLSC_3";
		break;
		case "GoLSC_3":
			dialog.text = "Ah, damn! It's a pity...";
			link.l1 = "Although I have never seen Teaser before, but it became clear to me what kind of person he was. It's really a pity.";
			link.l1.go = "GoLSC_4";
		break;
		case "GoLSC_4":
			dialog.text = "So you're going to try to find this Island? Then I'll give you Teaser's key.";
			link.l1 = "What is the key?";
			link.l1.go = "GoLSC_5";
		break;
		case "GoLSC_5":
			dialog.text = "I do not know for sure. Teaser gave it to me for safekeeping before he went to Curacao. He said that the Diffindur key, but I have no idea what it means.";
			link.l1 = "Mysterious key! It's interesting...";
			link.l1.go = "GoLSC_6";
		break;
		case "GoLSC_6":
			dialog.text = "According to his instructions, I have to give this key to whoever wants to find the Island. Teaser also said that this key should solve the problems of the new citizen of the Island. I have no idea what this means, but I am happy to comply with the request.";
			link.l1 = "Thanks, buddy. And goodbye.";
			link.l1.go = "exit";
			ChangeItemName("keyQuestLSC", "itmname_keyQuestLSC_Tizer");
			ChangeItemDescribe("keyQuestLSC", "itmdescr_keyQuestLSC_Tizer");
			sld = ItemsFromID("keyQuestLSC");
			DeleteAttribute(sld, "shown");
			GiveItem2Character(pchar, "keyQuestLSC");
		break;
	}
}

string GetPoorHeadManId(ref NPChar)
{
    ref ch;
	int n;
    string storeArray[30];	locations[n].private9.key = "key3";
	locations[n].private9.items.jewelry1 = 30;
    int howStore = 0;
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_poorman.c" && NPChar.id != ch.id && !CheckAttribute(ch, "quest.talk"))
		{
            storeArray[howStore] = ch.id;
            howStore++;
		}
    }
    if (howStore == 0) return "none";
    else return storeArray[rand(howStore-1)];
}
