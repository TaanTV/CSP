void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	ref _location;
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			pchar.quest.SharpAfterTreasure.win_condition.l1          = "location";
			pchar.quest.SharpAfterTreasure.win_condition.l1.location = "Shore57";
			pchar.quest.SharpAfterTreasure.function                  = "SharpAfterTreasure";
			dialog.text = "So you're the thief who stole my map.";
			link.l1 = "What the...!? What are you talking about? This is the first time I've seen you, how could I steal something from you?";
			link.l1.go = "2";

			NextDiag.TempNode = "First time";
		break;

		case "2":
			dialog.text = "Of course. She was just lying on the road, and you picked her up. And the other half, too, judging by the fact that you got here. That's how I believed it.";
			link.l1 = "Look, I have no idea why you think I stole your map, but you're wrong. By the way, how did you get here yourself?";
			link.l1.go = "3";
		break;

		case "3":
			dialog.text = "I've just been following you since I found out that you stole from me.";
			link.l1 = "How did you know that I stole the map? Just wondering.";
			link.l1.go = "4";
		break;

		case "4":
			dialog.text = "That's enough! I was going to gut you, not talk, and now I'm going to do it!";
			link.l1 = "Damn...";
			link.l1.go = "Exit_fight";
		break;

//grotto - dialog 2

		case "5":
			LAi_SetCurHPMax(npchar);
			LAi_SetPlayerType(PChar);
			dialog.text = "You're a tough little devil. Why did you stop? Let's get this over with!";
			link.l1 = "If I wanted to kill you, I would have done it already. What I really want to know is why you thought I stole your map. And what makes you think she's yours at all?";
			link.l1.go = "6";
		break;

		case "6":
			dialog.text = "Okay, I'll answer. Not so long ago, I met a strange man who gave me half of this damn map, explaining that he promised my father he would do it. One morning shortly after that, someone stole my map while I was struggling with a hangover in some lousy tavern. I questioned the locals very aggressively, and finally found a man who told me that he saw you talking to the innkeeper and waving something that looked very much like a piece of a map. I thought that you stole my map, and that now you're looking for the other half. So I decided to let you find her and see where she takes you.";
			link.l1 = "Cleverly. But you were wrong about one thing - although I was really looking for the other half of the map, it was, as far as I understand, your half. I had already received mine by that time, and in the same way as you did yours. I actually bought your half from that innkeeper, for absolutely crazy money, by the way. Remind me to thank him from the bottom of my heart for selling stolen goods without a discount.";
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = "But if it's true, then it turns out that you are mine...";
			link.l1 = "She is the one. At your service, dear brother. It's a pity that we happened to meet thanks to such a stupid coincidence, but I'm glad to see you anyway.";
			link.l1.go = "8";
			link.l2 = "Your sister. I'm afraid I'm going to have to kill you now-I have no desire to share my treasures with anyone but me, and, again, me. It's time to end our family meeting.";
			link.l2.go = "Exit kill";
		break;

		case "8":
			dialog.text = "Hmm... Actually, come to think of it, none of this seems like a coincidence. I think that's exactly what our father planned-that we would have to find each other to get here. He probably hadn't planned the theft or the fight, but otherwise it all fits together. Especially the fact that he left each of us half a map with the other's name on it.";
			link.l1 = "Yes, it looks like you're right. I wonder if he wanted us to do something special with all that gold. It is unlikely that he just left it to us for embezzlement, although this is also possible...";
			link.l1.go = "9";
		break;

		case "9":
			dialog.text = "I don't know, maybe he wanted to... But I know why he collected this wealth himself. You see, the man who gave me my half of the map also gave me my father's diary. It seems that my father had a dream - to create a new state in the Caribbean, free from petty wars and greedy governors of the Old World, capable of building a better future for its citizens. He called it Libertania. This money was intended for its creation.";
			link.l1 = "Libertania, you say... A beautiful dream. I wonder if he is getting closer to her incarnation? Besides raising a hefty pile of money, of course.";
			link.l1.go = "10";
			link.l2 = "This money, like everyone else in this world, is destined for my wallet. Anyone who thinks otherwise either gets out of my way or dies. Since you're unlikely to get out of the way, I'll have to kill you.";
			link.l2.go = "Exit kill";
		break;

		case "10":
			dialog.text = "He didn't just get close, he almost did, but his enemies made sure people forgot. 20 years ago, he assembled a powerful fleet to take over the colonies, but one of his men betrayed all his plans to the enemy.\nHis father's fleet was intercepted by the combined forces of England, France and Holland, and destroyed in heavy fighting. Our father died in that battle, and the colonial Powers went to great lengths to make him look like a simple pirate who was justly punished. But he seems to have foreseen it, and arranged for you and I to grow up safe, far from each other, and inherit his treasure and his dreams when we grow up and his affairs are safely forgotten.";
			link.l1 = "Yes, these channels did a great job. All my life, I was sure that my father was just a famous pirate... Wait, you said 'inherited his dreams'-do you think he wanted us to...";
			link.l1.go = "11";
		break;

		case "11":
			dialog.text = "Of course! He put so much effort into getting us to meet here and find his treasures and diary-he probably wanted us to finish what he started, make his dream come true. And this dream is worth it! I do not know if I can do it, I do not even know if it is even possible, but I will damn well try! And you?";
			link.l1 = "Libertania... It sounds great, even if it's impossible madness. I'm with you, brother! I'll meet you at sea. I'll just take my half of the treasure now.";
			link.l1.go = "Exit grotto continue";
			link.l2 = "You don't seriously hope to just throw out the colonial authorities from the archipelago, with all their money, ships and influence, do you? No, I don't want to take any part in this madness. Squander your half of the treasure as you please, and I'll take mine.";
			link.l2.go = "Exit half";
			link.l3 = "I should have killed you right away, then I wouldn't have to listen to this nonsense. It's time to fix this mistake!";
			link.l3.go = "Exit kill";
		break;

//grotto - dialog 3

		case "12":
			dialog.text = "You know, it's nice to suddenly realize that you have a family...";
			link.l1 = "Yes... listen, how do they create new countries in general?";
			link.l1.go = "13";
		break;

		case "13":
			dialog.text = "Honestly, I have no idea... But I have someone in mind who is knowledgeable in this matter. In his diary, my father often mentions a certain Robert Staffordshire-he seems to have been my father's main adviser in matters of state. I made inquiries about him - it turns out that he is still in good health, and lives on Isla Mona. I do not know if he will help us, but this is our best chance. I think we should meet with him.";
			link.l1 = "I agree. If he helped his father, maybe he will help us too.";
			link.l1.go = "14";
		break;

		case "14":
			dialog.text = "Then I will go ahead and arrange a meeting. We will be waiting for you at the Isla Mona Tavern.";
			link.l1 = "Agreed.";
			link.l1.go = "Exit grotto end";
		break;

//after advisor quest done

		case "16":
			dialog.text = "He's right, you can handle captains better than me. I will make excellent arrangements with merchants and usurers, I have often dealt with them.";
			link.l1 = "I agree, I trust your experience.";
			link.l1.go = "17";
		break;

		case "17":
			dialog.text = "Then I will start preparing for departure right now. We still have a lot to do. I'll be back in two weeks, but there may be delays.";
			link.l1 = "Take care of yourself. I would really hate to lose you.";
			link.l1.go = "18";
		break;

		case "18":
			dialog.text = "How nice of you, Beatrice. I didn't think you cared much about that...";
			link.l1 = "I care, and more than you think. Good luck.";
			link.l1.go = "Exit";
		break;

//boss killed rant

		case "19":
			dialog.text = "I'm in charge here now. Do you have any objections?";
			link.l1 = "...";
			link.l1.go = "20";
		break;

		case "20":
			dialog.text = "...No? That's what I thought. Now listen up, and tell the others. I'm calling a council of free captains here at my new residence in two weeks. I'll keep the reason for this to myself for now, but believe me, it's really important.";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//at pirate meeting - autodialog 2

		case "21":
			dialog.text = "You're here, fine. I'm not a great speaker, and I'm not going to torture you with long speeches.\nAs you probably know, my father, Nicholas Sharp, tried 20 years ago to create Liberty on these islands - a new, free state. Free from the greedy exploiters of the Old World, free from their petty wars, the whole point of which is to get a king a little glory and gold. As you again may know, his father was defeated - one of his associates betrayed him, and as a result his fleet was destroyed. But what you probably don't know is how damn close Dad was to success. I am just as close to realizing his dream, and I have taken every precaution not to repeat his mistakes, but I cannot do it alone.\nI need you - free men with your ships to fight those who dare to command you, to impose their laws and their wars. I'm not asking you to die under the fire of their forts - no, what I need from you is far less dangerous, but equally important to victory. I need you to disrupt their trade, drown their convoys, attack their patrols. I need you to become privateers of freedom.\nI ask a lot, but the reward, the freedom you can have is truly invaluable. So I ask you - follow me into the beautiful new world that we will create!";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//at pirate meeting

		case "22":
			dialog.text = "You doubt Beatrice, that her dreams are real. I'll tell you, if there's anyone in this room who can make dreams come true, it's her. You're hesitating. I can understand you - such decisions are not easy to make. But think about this: the chance to change the world is a damn rare thing. Very few people ever get that chance, and no one ever gets it twice. All this, here and now, is our chance. What to do with it is up to you and only you. But I know one thing - I won't miss my chance even for all the gold in the world! I've made my choice, now it's your turn!";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//at pirate meeting - autodialog 2

		case "23":
			dialog.text = "Gentlemen, you will not regret your decision. Now listen, we have a lot to discuss...";
			link.l1 = "...";
			link.l1.go = "23_exit";
		break;

		case "23_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("captains_long_speak");
		break;

		case "24":
			dialog.text = "(Several hours have passed) ...Now you know what to do, gentlemen. Do this, and the victory will be ours. You can go now.";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//after pirate meeting

		case "25":
			dialog.text = "Well, well, Beatrice. You really did it! Congratulations!";
			link.l1 = "We did it, Blaze, we did it. If it wasn't for your great speech, they wouldn't have followed me.";
			link.l1.go = "26";
		break;

		case "26":
			dialog.text = "Well, if you insist. So... What do you propose to do now, dear stepsister?";
			link.l1 = "Actually, I have a couple of interesting ideas, if you're not too busy...";
			link.l1.go = "27";
		break;

		case "27":
			dialog.text = "I will be happy to discuss these ideas. In private...";
			link.l1 = "Ha, that's right, sir! In my cabin or yours?";
			link.l1.go = "28";
		break;

		case "28":
			dialog.text = "Something tells me that this residence, which, by the way, is now yours, should have at least one bedroom.";
			link.l1 = "That's right! I suggest we find it immediately and use it for its intended purpose!";
			link.l1.go = "Exit";
		break;
//exits

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_fight":
			NextDiag.CurrentNode = "5";
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetCheckMinHP(NPChar, 1, true, "Sharp_Prologue_CheckHP");
			LAi_SetImmortal(NPChar, false);
			DialogExit();
		break;

		case "Exit grotto continue":
			NextDiag.CurrentNode = "hired";
			DialogExit();
			//pchar.questTemp.HiringOfficerIDX = NPChar.index;
			SetCompanionIndex(pchar, -1, sti(NPChar.index));
			Npchar.CanTakeMushket = true;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // Контузия
			LAi_SetImmortal(NPChar, false);
			sld.greeting = "Gr_Officer";
			sld.rank = 5;
			SetSelfSkill(sld, 20, 20, 20, 20, 20);
			SetShipSkill(sld, 20, 20, 20, 25, 20, 20, 20, 20, 20);
			SetSPECIAL(sld, 6, 6, 8, 5, 8, 8, 8);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			sld.quest.meeting = true;
			NPChar.Payment = true;

			_location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 50000;
			//_location.box1.items.icollection = 1;
			//_location.box1.items.indian1 = 1;
			_location.box1.items.indian7 = 1;
			//_location.box1.items.chest = 1;
			_location.box1.items.jewelry1 = 10+rand(5);
			_location.box1.items.jewelry2 = 10+rand(5);
			_location.box1.items.jewelry3 = 10+rand(5);
			_location.box1.items.jewelry4 = 5+rand(5);
			_location.box1.items.jewelry6 = rand(25);
			_location.box1.items.jewelry7 = rand(50);
			_location.box1.items.jewelry10 = rand(25);
			_location.box1.items.jewelry14 = rand(25);
			_location.box1.items.jewelry15 = rand(5);
			_location.box1.items.jewelry18 = rand(50);
			chrDisableReloadToLocation = false;

			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 8);
		break;

		case "Exit kill":
			LAi_SetWarriorType(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetPlayerType(PChar);
			LAi_SetImmortal(NPChar, false);
			DialogExit();

			_location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 150000;
			_location.box1.items.icollection = 1;
			_location.box1.items.indian1 = 1;
			_location.box1.items.indian7 = 1;
			_location.box1.items.chest = 1;
			_location.box1.items.jewelry1 = 20+rand(5);
			_location.box1.items.jewelry2 = 20+rand(5);
			_location.box1.items.jewelry3 = 20+rand(5);
			_location.box1.items.jewelry4 = 11+rand(5);
			_location.box1.items.jewelry6 = rand(50);
			_location.box1.items.jewelry7 = rand(100);
			_location.box1.items.jewelry10 = rand(50);
			_location.box1.items.jewelry14 = rand(50);
			_location.box1.items.jewelry15 = rand(10);
			_location.box1.items.jewelry18 = rand(100);

			pchar.quest.sharpxitFromCave.win_condition.l1 = "NPC_Death";
			pchar.quest.sharpxitFromCave.win_condition.l1.character ="Sharp_Sibling";
			pchar.quest.sharpxitFromCave.function = "sharpxitFromCave";

		break;

		case "Exit half":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			_location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 70000;
			//_location.box1.items.icollection = 1;
			_location.box1.items.indian1 = 1;
			_location.box1.items.indian7 = 1;
			_location.box1.items.chest = 1;
			_location.box1.items.jewelry1 = 10+rand(5);
			_location.box1.items.jewelry2 = 10+rand(5);
			_location.box1.items.jewelry3 = 10+rand(5);
			_location.box1.items.jewelry4 = 5+rand(5);
			_location.box1.items.jewelry6 = rand(25);
			_location.box1.items.jewelry7 = rand(50);
			_location.box1.items.jewelry10 = rand(25);
			_location.box1.items.jewelry14 = rand(25);
			_location.box1.items.jewelry15 = rand(5);
			_location.box1.items.jewelry18 = rand(50);

			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 8);
			chrDisableReloadToLocation = false;
		break;

		case "Exit grotto end":
			AddDialogExitQuest("Grotto end");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
