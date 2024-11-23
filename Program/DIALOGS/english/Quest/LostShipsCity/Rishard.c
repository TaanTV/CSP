// Ришард Шамбон - контрабандист
#include "DIALOGS\english\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "I don't want to talk to you. You attack civilians for no reason, provoke them into a fight. Go away!";
				link.l1 = "Um...";
				link.l1.go = "exit";
				break;
			}
			// --> кольцо
			if (GetNpcQuestPastDayParam(npchar, "quest_date") >= 1 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "Oh! Here you are, "+ GetSexPhrase("guy", "girl") +". And I already decided to find you myself. I need you "+ GetSexPhrase("I need a friend", "I need a girlfriend") +"";
				link.l1 = "You seem suspiciously friendly today, Richard. Well, I'm listening to you.";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Well, what do you want? To be honest, I'm not in the mood. Anyway, I've forgotten the last time I had it.";
				link.l1 = "Is it that bad, buddy?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, " + GetFullName(pchar)+"! "+TimeGreeting()+"! You wanted something?";
				link.l1 = LinkRandPhrase("Can you tell me something interesting?", "What's new on the island lately?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a couple of questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "I just decided to find out how you're doing. See you again!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting": // первая встреча
			dialog.text = "Is it bad? No, it's not bad. I'm just a little out of sorts. So what did you want?";
			link.l1 = "Yes, just to get acquainted. I've been here recently, walking around the Island, talking to people.";
			link.l1.go = "meeting_1";
		break;

		case "meeting_1":
			dialog.text = "Yes? Well okay. I am Richard Chambon. I used to trade all sorts of valuable goods, including forbidden ones, but for the last ten years I've been doing nothing but picking through the insides of shipwrecks, looking for all sorts of junk and exchanging it for food and gold.";
			link.l1 = "And I am " +GetFullName(pchar)+", captain of his own ship...";
			link.l1.go = "meeting_2";
		break;

		case "meeting_2":
			dialog.text = "You probably wanted to say Former captain, hehe?";
			link.l1 = "Well, yes... Former";
			link.l1.go = "meeting_4";
		break;

		case "meeting_4":
			dialog.text = "Ah... I've already thought about it... Okay, "+ GetSexPhrase("buddy", "girlfriend") +"I'd rather have a rum...";
			link.l1 = "Good luck. It was nice chatting. See you again!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Can you tell me something interesting?", "What's new on the island lately?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a couple of questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

		// Кольцо
		case "ring":
			dialog.text = "Why, was I any different before? Come on, I've had days without a mood - who doesn't have them! Tell me better: there are rumors around the Island that you are an outstanding fighter. Is that so?";
			link.l1 = "I don't know who is there and what he says about what kind of fighter I am. However, I know which end to hold the sword from, if that's what you're asking.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;

		case "ring_1":
			dialog.text = "Clear. I see the rumors don't lie... Listen, "+pchar.name+", do you remember how I once told you about the outer ring? About the fact that you can rummage around and find valuable things there?";
			link.l1 = "Yes, you're all talking about this outer ring here... And the same thing.";
			link.l1.go = "ring_2";
		break;

		case "ring_2":
			dialog.text = "And what else can we say about him, haha! Okay. Enough with the introductions, I'll get to the point. (lowering his voice) I managed to find one well-preserved ship near the outer rim. It stands apart from the others among the reefs, and very evenly, which is a considerable rarity. The ship is large - pinnace. He came to us recently, two months ago or a little more. So far, none of the other residents have discovered him, so there is a chance to make a good profit by digging into his hold and cabins.";
			link.l1 = "Fine, I'm glad for you. Well, what does that have to do with me? Or do you want to invite me along for company?";
			link.l1.go = "ring_3";
		break;

		case "ring_3":
			dialog.text = "Exactly! Listen further. The nose of this pinnace is shattered. Those damn crabs got into the hold through the gap in the hull and made a real nest there. While they are inside, it will not work to get on the ship, because I can't imagine how to climb onto the deck from the water on a smooth side - I can't handle crabs with dogs - I admit, I have never been distinguished by talents in fencing, and in recent years I have not touched weapons at all - there was no need. That's why I came to you.";
			link.l1 = "So you're suggesting that I kill the crabs inside this ship, right?";
			link.l1.go = "ring_4";
		break;

		case "ring_4":
			dialog.text = "Well, yes. We make an agreement with you: I show the way to the ship, and you eliminate the crabs. Everything found on the ship will go to the two of us. It's only fair - I found the ship, you made a way.";
			link.l1 = "No, buddy, I'm not interested in your offer. Fighting in the hold of a half-submerged ship with a flock of crabs for dubious trophies is not for me. Look for "+ GetSexPhrase("another risky guy", "someone else") +", who will drag chestnuts out of the fire for you.";
			link.l1.go = "ring_exit";
			link.l2 = "Interesting... I have long wanted to visit the outer ring. It's a deal! I'll deal with the crabs.";
			link.l2.go = "ring_5";
		break;

		case "ring_exit":
			dialog.text = "You shouldn't do that... The outer rim ships are full of all sorts of stuff... Moreover, no one has been on this ship yet. Okay, that's up to you. Be...";
			link.l1 = "Bye, buddy...";
			link.l1.go = "exit";
		break;

		case "ring_5":
			dialog.text = "I'm glad I didn't make a mistake about you, "+ GetSexPhrase("buddy", "girlfriend") +". I have a feeling that we will find a lot of interesting things there...";
			link.l1 = "Let's see. How many crabs are in the hold, do you know?";
			link.l1.go = "ring_6";
		break;

		case "ring_6":
			dialog.text = "It seemed to me four, or five... Well, that's about it.";
			link.l1 = "Let's manage. When will we leave?";
			link.l1.go = "ring_7";
		break;

		case "ring_7":
			dialog.text = "Come on tomorrow - you and I should prepare first. Stock up on medicinal potions, rummage in chests or look in the store, rum will do - there is poison in the jaws of crabs. It doesn't hurt to be careful. We'll meet at eight in the morning on the 'oblique deck'. Do you know where it is?";
			link.l1 = "No. Explain it.";
			link.l1.go = "ring_8";
		break;

		case "ring_8":
			dialog.text = "There is a piece of an old ship sticking out of the water behind the San Augustine. His nose went under the water, and the stern is lifted up - that's why it's called the 'oblique deck'. You can only get there by swimming. The most convenient way is to enter the water from the San Augustine under the suspension bridge, and go around the ship from either side. From there we will swim to the outer ring.";
			link.l1 = "Okay. See you tomorrow!";
			link.l1.go = "ring_9";
		break;

		case "ring_repeat":
			dialog.text = "At eight o'clock on the 'oblique deck'...";
			link.l1 = "Yes, yes, I remember...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;

		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;

		case "ring_10":
			dialog.text = "Yeah, here you are, "+ GetSexPhrase("buddy", "girlfriend") +". Ready to chop crab salad?";
			link.l1 = "Of course!";
			link.l1.go = "ring_11";
		break;

		case "ring_11":
			dialog.text = "Very good. Now turn your head towards the outer ring and look: do you see these two shipwrecks sticking out of the water?";
			link.l1 = "Um... Yes, I see it.";
			link.l1.go = "ring_12";
		break;

		case "ring_12":
			dialog.text = "Now look at the outer ring between them. Do you see the galleon in the ring with the bow up? He's looking right at us. Take a closer look.";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;

		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;

		case "ring_13":
			dialog.text = "";
			link.l1 = "I think I see it... Yes! There it is!";
			link.l1.go = "ring_13a";
		break;

		case "ring_13a":
			dialog.text = "We're going there. We sail straight, without turning anywhere, in the direction of this galleon. As soon as we reach the ring, then I will show you the way, you will need to get to the other side. The entrance to the hold of my ship is through a gap in the bow. I'll tell you right away: I'm not going in there until you've cleaned all the crabs.";
			link.l1 = "We already agreed on this yesterday, I remember. You show the ship, I destroy the crabs. Have you sailed?";
			link.l1.go = "ring_14";
		break;

		case "ring_14":
			dialog.text = "Let's go! You go ahead, I'll follow you!";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;

		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			AddQuestRecord("LSC_Ring", "3");
		break;

		case "ring_15":
			dialog.text = "Heh, you did great!";
			link.l1 = "Someone told me about 'four or five' crabs... Can you remind me who it was?";
			link.l1.go = "ring_16";
		break;

		case "ring_16":
			dialog.text = ""+ GetSexPhrase("Buddy", "Girlfriend") +", I didn't climb into the hold to count them. I looked outside, through the gap, and counted exactly that many. So I had no intention of lying to you.";
			link.l1 = "Okay. Let's inspect the hold, or something...";
			link.l1.go = "ring_17";
		break;

		case "ring_17":
			dialog.text = "Of course! That's why we came here, isn't it?";
			link.l1 = "Exactly! Let's not waste any time...";
			link.l1.go = "ring_18";
		break;

		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;

		case "ring_wait":
			dialog.text = "Wait, "+ GetSexPhrase("buddy", "girlfriend") +", I haven't looked at everything I wanted yet. Do a better search, maybe you'll find something else.";
			link.l1 = "Okay...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;

		case "ring_19":
			dialog.text = "Nothing special yet. It is a pity that there are no particularly valuable goods: there are food in barrels, copra in boxes. Although there was a box with bottles of expensive wine. What about you?";
			link.l1 = "Nothing special either. A few crates were of interest, the rest-as you said, corned beef and copra.";
			link.l1.go = "ring_20";
		break;

		case "ring_20":
			dialog.text = "It won't be enough... Let's go upstairs, search the deck and cabins.";
			link.l1 = "Let's go.";
			link.l1.go = "ring_21";
		break;

		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
/* 			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			} */
		break;

		case "ring_22":
			dialog.text = "Damn it! Just look at this! The damned crab scum has crawled onto the deck! How did they manage it?!";
			link.l1 = "Don't be a coward! Stay here and don't move, don't attract their attention. I'm going to deal with these creatures now...";
			link.l1.go = "ring_23";
		break;

		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;

		case "ring_24":
			dialog.text = "Wow! It's not for nothing that they told about you that you are great with weapons. If I were alone, I would have jumped overboard a long time ago...";
			link.l1 = "Listen, how did you become a smuggler in the past, huh? Or have you always been running away from everyone?";
			link.l1.go = "ring_25";
		break;

		case "ring_25":
			dialog.text = ""+ GetSexPhrase("Buddy", "Girlfriend") +"first of all, I was younger, stronger and more desperate then. Secondly, I am not a mercenary to participate in wars - I am a smuggler, and we have always tried to avoid clashes with soldiers. Thirdly, I was more into sails and tiller than swords and pistols. And fourthly, after ten years of quiet life on the Island, I have completely softened up, so don't judge me harshly. Let's take a look around the deck. It seems that before getting here, this ship was in a serious battle - look - holes from the balls in the sides and deck, barrels of gunpowder at the guns...";
			link.l1 = "You're right. The ship was under fire, that's obvious. Okay, let's look for something interesting.";
			link.l1.go = "ring_26";
		break;

		case "ring_26":
			dialog.text = "Uh-huh. And we need to look for entrances to the interior.";
			link.l1 = "That's it, don't waste any time. If you meet a crab, call for help.";
			link.l1.go = "ring_27";
		break;

		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;

		case "ring_28":
			dialog.text = "And again, nothing significant... I found a couple of interesting little things, and that's it. But this is normal - there are usually no valuables on the decks. All the best things are in the cabins. Over there is the entrance to captain's cabin. Let's go and rummage there...";
			link.l1 = "Look carefully - the devil knows what might be hiding there. Maybe I'd better go "+ GetSexPhrase("first", "first") +"?";
			link.l1.go = "ring_29";
		break;

		case "ring_29":
			dialog.text = "Let's go, "+pchar.name+". It's not all the time for me to hide behind your back. And really, it's a shame...";
			link.l1 = "Well, let's go...";
			link.l1.go = "ring_30";
		break;

		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладём журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;

		case "ring_31":
			dialog.text = "I think I was lucky - there were no crabs or any other filth. And now let's turn this whole cabin upside down-I swear on my honor, I'm already starting to get angry: except for two dozen doubloons and all sorts of worthless little things, I haven't found anything yet!";
			link.l1 = "Don't start. You said it right - all valuables are stored in captain's cabin. We are looking for it!";
			link.l1.go = "ring_32";
		break;

		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;

		case "ring_33":
			dialog.text = "Haha! As I thought! I know the habits of these merchants - to arrange hiding places and hide the ship's treasury there! The captain of this pinnace was a cunning rascal, but you can't fool me! Look what I've managed to get! You never would have found that cache alone!";
			link.l1 = "Come on, show me!";
			link.l1.go = "ring_34";
		break;

		case "ring_34":
			dialog.text = "Forty thousand piastres, two chests of doubloons, a bag of emeralds and a bunch of jewelry! The owner was rich... Okay, at least this will pay for our hard work, although I was hoping for more. We divide it fraternally, in half, as agreed.";
			link.l1 = "Excellent, Richard. At least we've earned something!";
			link.l1.go = "ring_35";
		break;

		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You got the chest");
			Log_Info("You got 25 emeralds");
			Log_Info("You have received a collection of jewelry");
			PlaySound("interface\important_item.wav");
			dialog.text = "Well, what each of us found in the hold and on the deck, we'll keep for ourselves. Okay? Was there anything useful in the chests and cupboards?";
			link.l1 = "A few Indian trinkets, amulets, papers, and other small things.";
			link.l1.go = "ring_36";
		break;

		case "ring_36":
			dialog.text = "Take it for yourself. In the end, you executed the most dangerous job.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочёл журнал
			{
				link.l1 = "Okay. But I found something else in your line, cache seeker. There was a ship's log on the table. The story contained in it is very sad... but now it concerns us in some ways: somewhere in the hold there is a whole box of gold hidden! Read it yourself!";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "Okay. But I found something else - logbook of captain of this ship.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "Okay, I don't mind this arrangement, hehe. Well, is it time to go back?";
					link.l1.go = "ring_37";
				}
			}
		break;

		case "ring_37":
			dialog.text = "Yes. Don't tell anyone about the ship - let it be our secret. Of course, no one needs copra here, but the food will be useful to us. You won't need to buy from the admiral.";
			link.l1 = "Okay, let's do it. Hopefully, others won't find this ship soon. Let's go!";
			link.l1.go = "ring_cabin_exit";
		break;

		case "ring_38":
			dialog.text = "Are you his "+ GetSexPhrase("read", "read") +"?";
			link.l1 = "Not yet...";
			link.l1.go = "ring_39";
		break;

		case "ring_39":
			dialog.text = "Then let's read! It may contain important information. And it's just interesting to know why this ship ended up here. Read it!";
			link.l1 = "Hmm. Okay, let's read it now...";
			link.l1.go = "ring_40";
		break;

		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;

		case "book_wait":
			dialog.text = ""+ GetSexPhrase("Read", "Read") +"? What does it say?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочёл журнал
			{
				link.l1 = "It says this here... The story is very sad... But now it concerns us in some ways. In general, this is in your line, the seeker of hiding places: somewhere in the hold there is a whole box of gold hidden! Read it yourself!";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "Wait. I'll read it now and tell you...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;

		case "ring_41":
			dialog.text = "What are you doing?! "+pchar.name+", I am this... I don't read well. You'd better tell me in detail what it says, huh?";
			link.l1 = "Long story short: this pinnace crossed the Caribbean Sea from Southern Main towards New Spain. The captain married an Indian princess from the tribes of the lower Orinoco, and she showed him where their people made sacrifices to the gods...";
			link.l1.go = "ring_42";
		break;

		case "ring_42":
			dialog.text = "";
			link.l1 = "The sacrifices were in the form of gold nuggets. Our brave captain, of course, plundered this gold reserve, and together with the executive officer and the quartermaster, he carried it secretly from the crew into the hold of the ship, put it in one of the boxes and sprinkled with copra...";
			link.l1.go = "ring_43";
		break;

		case "ring_43":
			dialog.text = "";
			link.l1 = "But, apparently, the robbery of the sacred Indian place did not go unnoticed: the ship fell into a dead calm, fresh water began to run out, a fever epidemic broke out on the ship, pirates attacked. The sailors blamed the Indian woman, captain's wife, for everything and demanded to throw her overboard. Cap, of course, refused, and the team started a riot...";
			link.l1.go = "ring_44";
		break;

		case "ring_44":
			dialog.text = "";
			link.l1 = "The captain lost this fight. The last recordings - he locked himself in the cabin with the Indian woman, firing back, and the enraged sailors broke down the door. A storm was approaching on the horizon... Apparently, it was he who brought the pinnace here. It is clear how the tragedy ended: the girl was shot, and captain, of course, was killed by rioters.";
			link.l1.go = "ring_45";
		break;

		case "ring_45":
			dialog.text = "Hmm. It's really sad. But you're not kidding? Is there a whole box of gold hidden in the hold? I can't believe my ears! But which one is it? Let's go down to the hold! I will go through every bale, every barrel!";
			link.l1 = "Let's go. I can't wait to start searching too.";
			link.l1.go = "ring_seek_gold";
		break;

		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;

		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;

		case "ring_46":
			dialog.text = "Haha! We found him! It really is there! Just look at what a huge pile! A whole box! There must be at least five thousand bars here! I've never seen such a pile of gold!";
			link.l1 = "Congratulations, companion. Our venture seems to have been a phenomenal success... What are we going to do with the gold?";
			link.l1.go = "ring_47";
		break;

		case "ring_47":
			dialog.text = "Like what? We'll split it in half!";
			link.l1 = "This is understandable. Where are you going to keep it? Are you going to leave it here, or are you going to drag it where?";
			link.l1.go = "ring_48";
		break;

		case "ring_48":
			dialog.text = "Ha! Of course, I'll hide everything in my hiding places, which no one will ever find. I can hide it! Let's put half of the gold in a barrel now - that will be my share. And before the sun rises, I'll take her off this ship, and you do with your share what you see fit. But it's better to hide it too, otherwise it will suddenly disappear - you will blame me for this. But I must say right away: I am an honest man in my own way, and I will not even dare to encroach on your share. And here are the others who will come here... they may find it by accident.";
			link.l1 = "Okay. I'll decide what to do with my gold. Let's put your share in the barrel...";
			link.l1.go = "ring_49";
		break;

		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Two hours have passed..."+ NewStr() +"Gold is divided!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;

		case "ring_50":
			dialog.text = "That's it... Thank you, "+pchar.name+". It wouldn't have worked out without you. Now you can be puzzled by the construction of tartans to sail to the archipelago... Oh, okay. I won't think about it today, I still have a lot of work to do - to move my gold to safe places. Bye, "+ GetSexPhrase("buddy", "girlfriend") +", I wish you to dispose of your share successfully!";
			link.l1 = "Bye, Richard. It's been a nice day. See you later!";
			link.l1.go = "ring_51";
		break;

		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Questions? Oh, come on, if you need it so much...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Would you like to get out of here?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Have you ever wanted to join one of the clans? For example, to the narwhals?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "So you can find a lot of interesting things on the ships of the outer ring?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions asked. I'm sorry...";
			link.l10.go = "exit";
		break;

		case "ansewer_1":
			dialog.text = "Ten years ago, my comrades and I constantly made crossings between the Island and Cuba on a well-equipped tartan. We kept the location of the Island a secret - we brought bull carcasses here and exchanged fresh meat for goods from the holds of dead ships and gold. It was a time! There was always a shortage of food here - mostly crackers and corned beef, so they paid for juicy meat with spices that cost a fortune in Europe! In one flight, I earned so much that I could buy up all the whores of Tortuga for eternal use, but everything comes to an end, and our well-fed life has come to an end. The weather has changed in these parts - storms have become more frequent and more severe, and it was increasingly dangerous to get to the Island. Some of my colleagues withdrew from the case, but I and a dozen brave men continued to travel until we were eventually smashed on the reefs two miles from the Island. How I got here by swimming through a stormy sea, I still can't figure it out myself. That's how I became one of the people I used to trade with.";
			link.l1 = "Interesting story...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;

		case "ansewer_2":
			dialog.text = "Ha! I'm getting out of here, damn it! But not now. What should I do in Cuba? I don't have any friends left, and I don't have a lot of money either. As soon as I find a ship with a rich cargo on the outer ring, or a bunch of gold doubloons, I will immediately start building a boat.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;

		case "ansewer_3":
			dialog.text = "Why? So that then, like a fool, two days later, you can stand guard at attention, chasing everyone who decides to come to the San Gabriel? And they are not eager to take strangers to themselves. They are hereditary islanders, like you... And the Negroes are no better than them. No, I'd rather be on my own.";
			link.l1 = "Clear...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;

		case "ansewer_4":
			dialog.text = "Of course! That's all the islanders live on. Do you know when there's a holiday on the Island? When a new ship comes to us. But in any case, there are still a lot of unexplored and undiscovered tubs in the outer ring, in the holds of which you can find valuable goods and gold, but the difficulty is that it is almost impossible to walk along the outer ring - everything is at random, and if you get confused or slip and fall unsuccessfully, you can fall into such a place, You can't get out of there on your own. And then you're finished. A lot of people have already disappeared like that.";
			link.l1 = "Hmm... interesting.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов

//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, huh? You're a thief!", "Wow! A little bit I looked, and you immediately went into the chest with your head!", "You decided to rummage through the chests?! You won't get away with it!");
			link.l1 = "Ah, the devil!!!";
			link.l1.go = "fight";
		break;

		case "Woman_FackYou":
			dialog.text = "Oh, so that's how it is?! Did you decide to rummage through the chests?! You won't get away with it!";
			link.l1 = "What a fool!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you should hide your weapon. And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the weapon away.", "Listen to what you're like "+ GetSexPhrase("d'Artagnan", "abnormal") +"Are you running around here, waving your sword? Put away your weapon, it doesn't suit your face "+ GetSexPhrase("serious man", "beautiful girl") +"...");
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this city, I ask you not to walk with a naked blade here.", "You know, as a citizen of this city, I ask you not to walk with a naked blade here.");
				link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful on turns, "+ GetSexPhrase("buddy", "girl") +", when running with a gun in your hands. I can get nervous...", "I don't like when "+ GetSexPhrase("men", "girls") +", walk in front of me with weapons at the ready. It scares me...");
				link.l1 = RandPhraseSimple("Understood.", "I'm removing.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
