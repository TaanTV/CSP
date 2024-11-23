// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog, "Links");

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

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Paleface one", "White Squaw") +" wants to talk?", 
				"You again, "+ GetSexPhrase("paleface", "white squaw") +".", 
				""+ GetSexPhrase("Paleface likes to talk. He looks like a squaw.", "White squaw likes to talk.") +"",
                "The spirits brought to me paleface"+ GetSexPhrase("brother", "sister") +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.", 
				"Yes, it's me again.",
                "Very poetic.", 
				"Nice to see you too.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
			
			/*if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hello, white brother. Do you want to say Indian?";
				link.l1 = "Greetings, son of the jungle. I'm glad to see you, but it's time for me to continue my journey.";
				link.l1.go = "exit";
				link.l2 = "Yes. I've heard that you can buy interesting things from you. Don't you have anything to sell?";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}*/
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Tell me why you came.";
			link.l1 = "Nothing special, I wanted to listen to you...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Paleface", "White Squaw") +" wants to talk?", 
				"You again, yalanaui?", 
				""+ GetSexPhrase("Paleface", "White Squaw") +" likes to talk.",
                "The spirits brought pale faces to me"+ GetSexPhrase("his brother", "my sister") +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.", 
				"Yes, it's me again.",
                "Very poetic.", 
				"Nice to see you too.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+", I listen to you, "+ GetSexPhrase("son of the sea", "daughter of the sea") +".", "What do you want, " + npchar.name+", "+ GetSexPhrase("paleface", "white squaw") +"?", "My ears are open to your words, stranger.");
			/*if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("I have something for you. Do you want to see it?", "Do you want me to show you something interesting? You'll like it...", "I have something that will please you, child of the jungle... Do you want to take a look?");
				link.l1.go = "gift";
			}*/
			link.l9 = "Nothing special, I just wanted to listen to you...";
			link.l9.go = "exit";
		break;
		
		case "Shoko_1":
			dialog.text = "Ahau, yalanaui.";
			link.l9 = "Hello, beautiful. My name is "+pchar.name+". What's your name?";
			link.l9.go = "Shoko_2";
		break;
		
		case "Shoko_2":
			dialog.text = "Shoko.";
			link.l9 = "Can you tell me something about your people, Shoko?";
			link.l9.go = "Shoko_3";
		break;
		
		case "Shoko_3":
			dialog.text = "Lilachil pel ukuchu lutilili, chin tu kult.";
			link.l9 = "This is very interesting. Can I bargain with someone here?";
			link.l9.go = "Shoko_4";
		break;
		
		case "Shoko_4":
			dialog.text = "Dolin vaughan hinch of pain. Bash kulyuchu nahau?";
			link.l9 = "Uh, okay... I'll ask someone else. Bye!";
			link.l9.go = "exit";
			NextDiag.TempNode = "ShokoAgain";
		break;
		
		case "ShokoAgain":
			dialog.text = "Ahau, yalanaui. Mache esh.";
			link.l9 = "I'm glad to see you too.";
			link.l9.go = "exit";
			NextDiag.TempNode = "ShokoAgain";
		break;
		
		case "Chani_1":
			dialog.text = "Capono bambule, gucho. I am Chani, daughter of Chaka Bakir, shaman of the Shaganumbi tribe.";
			link.l1 = "My name is " + GetFullName(pchar)+", I am captain of the ship '" + PChar.Ship.Name + "'. I accidentally gone into these lands, getting acquainted with local traditions.";
			link.l1.go = "Chani_2";
		break;
		
		case "Chani_2":
			dialog.text = "Since you are captain, then you are a big man. It's not convenient for me to ask this, but we need your help, yalanaui.";
			link.l1 = "How can I help you?";
			link.l1.go = "Chani_3";
			link.l2 = "I'm sorry, but I'm not up to your problems right now.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Chani_1";
		break;
		
		case "Chani_3":
			dialog.text = "White people collect tribute from us, force us to give them our pearls. They ask for a little, and we gave them as much as they asked. But recently a very important man came here, Manuel de Moreno, who brought with him a large army and demanded that we collect 800 large pearls.\nWe gave everything we had, but it wasn't enough. We still owe Manuel de Moreno 500 big pearls, but we have nothing else. Otherwise, he promised to level our village.\nPlease, Captain, help us pay this tribute, and in return I promise you an elixir of Ish-Chel's Tears that will help improve your health.";
			link.l1 = "Okay, I'll find these 500 large pearls and bring them to you.";
			link.l1.go = "Chani_4";
			if (sti(pchar.items.jewelry11) >= 500)
			{
				link.l1 = "I have 500 large pearls with me. Now your village will be safe.";
				link.l1.go = "Chani_Zhemchug2";
			}
			link.l2 = "I'm very sorry for your village, but I can't help.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Chani_1";
		break;
		
		case "Chani_4":
			dialog.text = "Thank you, yalanaui. You have a kind heart. I'll be waiting for you.";
			link.l1 = "As soon as I collect the right amount, I'll come back to you.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chani_Zhemchug";
			npchar.quest.takePearls = "seek";
			npchar.quest.takePearls.Qty = 0; //кол-во жемчужин
			
			SetQuestHeader("ShamanChani");
			AddQuestRecord("ShamanChani", "1");
		break;
		
		case "Chani_Zhemchug":
			dialog.text = "Glad to see you, yalanaui.";
			link.l1 = "Chani, I want to give you my pearls.";
			link.l1.go = "Chani_Zhemchug2";
			link.l2 = "It's time for me....";
			link.l2.go = "exit";
			NextDiag.TempNode = "Chani_Zhemchug";
		break;
		
		case "Chani_Zhemchug2":
			iTemp = GetCharacterItem(pchar, "jewelry11");
			npchar.quest.takePearls.Qty = sti(npchar.quest.takePearls.Qty) + iTemp;
			DeleteAttribute(pchar, "items.jewelry11");
			if (sti(npchar.quest.takePearls.Qty) < 500)
			{
				dialog.text = "Let's count. Now you have "+ GetSexPhrase("eu", "if") +" " + FindRussianQtyString(iTemp) + " big pearls. In total, you will receive "+ GetSexPhrase("eu", "if") +" " + FindRussianQtyString(sti(npchar.quest.takePearls.Qty)) + " big pearls. You have to bring more " + FindRussianQtyString(500 - sti(npchar.quest.takePearls.Qty)) + ".";
				link.l1 = "I see. I'll be back soon with new pearls, Chani.";
				link.l1.go = "exit";
				AddQuestRecord("ShamanChani", "2");
				AddQuestUserData("ShamanChani", "iQty", 500 - sti(npchar.quest.takePearls.Qty));
			}
			else
			{
				dialog.text = "Thank the gods! You proved, "+pchar.name+", that our village is your home too. Now I am sure that the Indians will be safe.";
				link.l1 = "I am very glad to hear this, Chani.";
				link.l1.go = "Chani_12";
				ChangeCharacterReputation(pchar, 1);
				AddQuestRecord("ShamanChani", "3");
			}
		break;
		
		case "Chani_12":
			dialog.text = "I want to give you our valuable gift, Tears of Ish-Chel. He will help you to improve your health if you feel unwell.";
			link.l1 = "This is a very valuable gift, thank you.";
			link.l1.go = "Chani_13";
			GiveItem2Character(PChar, "potion7");
			Log_info("The shaman gave you Tears of Ish-Chel");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "Chani_13":		
			dialog.text = "Come visit us again, in the future I will find a job for you.";
			link.l1 = "I will certainly look in. See you later!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chani_21";
			SetTimerCondition("CSP_Chani_2quest", 0, 0, 14, false);
		break;
		
		case "Chani_21":		
			dialog.text = "Welcome to our village, yalanaui. You wanted something?";
			link.l1 = " I was just passing by. See you later!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chani_21";
			if (CheckAttribute(pchar, "quest.Chani_2quest"))
			{
				dialog.text = "You returned, gucho. You're very timely. I need your help.";
				link.l1 = "And what is it this time?";
				link.l1.go = "Chani_22";
			}
		break;
		
		case "Chani_22":		
			dialog.text = "Tagana, one of our strongest warriors. I sent him with a task, and never seen him again.";
			link.l1 = "Can I be more specific? Where did you send Tagana and what did he have? ";
			link.l1.go = "Chani_23";
		break;
		
		case "Chani_23":		
			dialog.text = "He needed to go far away, to foreign lands, to find there a very necessary ";
			link.l1 = "I could search for him. Although, if he went alone, it's more likely that he died in a wild.";
			link.l1.go = "Chani_24";
		break;
		
		case "Chani_24":		
			dialog.text = "Tagana is too smart to become prey for predatory animals.";
			link.l1 = "Is he smart enough for people? Perhaps he became the prey of the patrol.";
			link.l1.go = "Chani_25";
		break;
		
		case "Chani_25":		
			dialog.text = "The soldiers with their thunder spears wouldn't even notice Tagana, he's like a jaguar stalking through the foliage.";
			link.l1 = "And what kind of task did Tagana have?";
			link.l1.go = "Chani_26";
		break;
		
		case "Chani_26":		
			dialog.text = "He had to get a special decoction from the cannibals, which I need for a voodoo ritual to protect the village.";
			link.l1 = "And if I get this decoction?";
			link.l1.go = "Chani_28";
			if (sti(pchar.items.StrangePotion) >= 1)
			{
				link.l1 = "I have this strange decoction with me. I came across aggressive savages in the jungle, one of them had this flask with him. I think they caused the loss of your Tagana.";
				link.l1.go = "Chani_30";
			}
			link.l2 = "I'm very sorry for Tagan, but I can't help.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Chani_21";
		break;

		case "Chani_28":
			dialog.text = "If you get this decoction for me, I promise that I will faithfully serve you and go where you go.";
			link.l1 = "All right, Chani. If I find the right decoction, I'll come back to you.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chani_29";
			AddQuestRecord("ShamanChani", "4");
			PChar.quest.CSP_Chani_PoiskOtvara.win_condition.l1 = "item";
			PChar.quest.CSP_Chani_PoiskOtvara.win_condition.l1.item = "StrangePotion";
			PChar.quest.CSP_Chani_PoiskOtvara.win_condition = "CSP_Chani_PoiskOtvara";
			pchar.questTemp.СhaniJidkost = "СhaniJidkost";
		break;
		
		case "Chani_29":
			dialog.text = "Glad to see you, gucho. Will you accept decoction?";
			link.l1 = "Not yet, Chani, but I will definitely find it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chani_29";
			if (sti(pchar.items.StrangePotion) >= 1)
			{
				link.l1 = "Here, take a look, I think this is what you're looking for. I picked up him from the corpse of a cannibal.";
				link.l1.go = "Chani_30";
			}
		break;
		
		case "Chani_30":		
			dialog.text = "Great! Give me some time to perform the village protection rite, and I'll join you on a trip on your big canoe.";
			link.l1 = "Well, I'll wait for you, Chani.";
			link.l1.go = "Chani_31";
			DeleteAttribute(pchar, "quest.Chani_2quest");
			DeleteAttribute(pchar, "questTemp.СhaniJidkost");
			AddItems(pchar, "StrangePotion", -1);
			Log_info("You gave away a strange liquid.");
		break;
				
		case "Chani_31":
			DialogExit();
			
			sld = CharacterFromID("Chani");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetShipRemovable(sld, true);
			SetCharacterRemovable(sld, true);
			sld.HalfImmortal = true;
			sld.location = "None";
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			
			AddQuestRecord("ShamanChani", "6");
			CloseQuestHeader("ShamanChani");
			pchar.questdata.ShamankaChani = 1;
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen			
		case "CitizenNotBlade":
			dialog.text = RandPhraseSimple("Put away your weapons, yalanaui, until we force you to do it!", "Don't tempt fate, paleface! Put away your saber!");
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Don't worry, I'm already putting away...");
			link.l1.go = "exit";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Theif!";
			link.l1 = "Shut up you fool...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
