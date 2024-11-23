void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar = GetMainCharacter();
	string sName = PChar.name + " " + PChar.lastname;

	int iBricks = sti(PChar.BuildingColony.Blocks);
	int iPlanks = sti(PChar.BuildingColony.Planks);
	int iMahogany = sti(PChar.BuildingColony.Mahogany);
	int iEbony = sti(PChar.BuildingColony.Ebony);
	int iSlaves = sti(PChar.BuildingColony.Slaves);
	int iFood = sti(PChar.BuildingColony.Food);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What can I do for you, "+GetSexPhrase("Herr kapitan", "fraulein")+" " + sName + "?";
			if(PChar.ColonyBuilding.Stage != "3" && PChar.ColonyBuilding.Action != true)
			{
				link.l1 = "I think I'm interested in your services.";
				link.l1.go = "Building";
			}
			link.l2 = "I just wanted to see you.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Hi1":
			dialog.text = "Guten Tag, "+GetSexPhrase("herr kapitan", "fraulein")+" " + sName + "! You won't believe what happened to me!";
			link.l1 = "Hello, Mr. Zalpfer, I did not expect to see you here, what are you doing here?";
			link.l1.go = "Hi";
			NextDiag.TempNode = "First time";
		break;

		case "Hi":
			dialog.text = "It's all Morgan! Ya, only HE, the only one who listened to me and realized the genius of my inventions, which now serve for the benefit of the Crown of England!\n"+
							"I am currently working on a new project that will allow me to build an entire city in the shortest possible time. It will outshine all the other colonies of the Caribbean archipelago, ya! I'm telling you exactly! And maybe the whole world, who knows..."
			link.l1 = "Is that so? Interesting enough.";
			link.l1.go = "First time";
		break;

		case "Building":
			dialog.text = "What exactly would you like?";

			if(PChar.ColonyBuilding.Stage == "0")
			{
				link.l1 = "I would like to start building a colony.";
				link.l1.go = "ColonyBuilding";
			}

			if(PChar.ColonyBuilding.Stage == "1")
			{
				link.l2 = "I would like to expand my colony, which bears the name '" + PChar.ColonyBuilding.ColonyName + "'.";
				link.l2.go = "ColonyModification";
			}

			if(PChar.ColonyBuilding.Stage == "2")
			{
				link.l3 = "I wanted to strengthen my colony, build a fort to guard it.";
				link.l3.go = "ColonyFortBuildingNoNo";
			}

			link.l4 = "Sorry, but I have to go. Things are waiting.";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "ColonyBuilding":
	    	if(CheckAttribute(pchar, "VedekerDiscount"))//Скидка от Ведекера.
	    	{
				NPChar.NeedMoney = (1500000 * MOD_SKILL_ENEMY_RATE)/2;
	    		dialog.text = "Hmm... Well. I think first we need to explore the uninhabited islands for suitability for the construction of a colony. In addition, my work, of course, is not free, and the payment will be "+(1500000*MOD_SKILL_ENEMY_RATE*3)+" piastres. Besides, you have a competent technician with you. Together with him, we will be able to significantly reduce the cost of money to about "+NPChar.NeedMoney+" piastres, if, of course, he helps me. What do you say?";
	    	}
	    	else
	    	{
				NPChar.NeedMoney = 1500000 * MOD_SKILL_ENEMY_RATE;
		    	dialog.text = "Hmm... Well. I think first we need to explore the uninhabited islands for suitability for the construction of a colony. In addition, my work, of course, is not free, and the payment will be "+(1500000*MOD_SKILL_ENEMY_RATE*3)+" piastres. What do you say?";
		    }

			if(sti(PChar.money) >= sti(NPChar.NeedMoney))
			{
				link.l1 = "I agree.";
				link.l1.go = "ColonyBuilding_1";
			}
			else
			{
				link.l2 = "I don't have enough money yet.";
				link.l2.go = "exit";
			}

			link.l3 = "Sorry, I have to go.";
			link.l3.go = "exit";
		break;

		case "ColonyBuilding_1":
			AddMoneyToCharacter(PChar, -sti(NPChar.NeedMoney));
			dialog.text = "Then we need to survey the uninhabited islands as soon as possible.";
			link.l1 = "I will try to sail as soon as possible!";
			link.l1.go = "ColonyBuilding_exit";
			PChar.BuildingColony.Blocks = 500;
			PChar.BuildingColony.Planks = 1000;
			PChar.BuildingColony.Mahogany = 500;
			PChar.BuildingColony.Ebony = 250;
			PChar.BuildingColony.Slaves = 200;
			PChar.BuildingColony.Food = 400;
		break;

		case "ColonyBuilding_2":
			dialog.text = ""+GetSexPhrase("Herr kapitan", "Fraulein")+". After carefully examining this island, I came to the conclusion that this is exactly the place where the construction of the colony should begin. The scouts have found signs of some deposits, and this may be economically beneficial for the colony, ya. In addition, it has the most fertile soil of all the islands we have visited.";
			link.l1 = "Do you think, Albrecht, that I will grow pineapples with coffee there? I'm a corsair, not a farmer!";
			link.l1.go = "ColonyBuilding_2_1";
		break;

		case "ColonyBuilding_2_1":
			dialog.text = "Ya?! And how are you going to get food for the inhabitants of the colony? Famously firing their cannons at passing ships, demanding food? In that case, everyone will either starve to death, or any of the powers will get their hands on you for such recklessness!";
			link.l1 = "Be careful, Albrecht.. Well, I got excited a little bit!";
			link.l1.go = "ColonyBuilding_2_2";
		break;

		case "ColonyBuilding_2_2":
			dialog.text = "And you don't teach me my business. I'm not teaching you how to cut throats.";
			link.l1 = "Cough.. What's next?";
			link.l1.go = "ColonyBuilding_3";
			AddDialogExitQuest("ColonyBuildingCayman");
		break;

		case "ColonyBuilding_3":
			dialog.text = "Now I will need some goods needed to build a colony. Bricks - " + FloatToString(iBricks,0) + " pcs., planks - " + iPlanks + " pcs., mahogany - " + iMahogany + " pcs., ebony - " + iEbony + " pcs., food - " + iFood + " pcs., and " + iSlaves + " slaves. As soon as all the goods are delivered, we will start construction, ya!";
			link.l1 = "Okay.";
			link.l1.go = "exit";

			NextDiag.TempNode = "ColonyBuilding_4";
		break;

		case "ColonyBuilding_4":
			dialog.text = "What did you want, Captain?";
			if(sti(PChar.BuildingColony.Blocks) == 0 && sti(PChar.BuildingColony.Planks) == 0 && sti(PChar.BuildingColony.Mahogany) == 0 && sti(PChar.BuildingColony.Ebony) == 0 && sti(PChar.BuildingColony.Slaves) == 0 && sti(PChar.BuildingColony.Food) == 0)
			{
				dialog.text = "I am happy to inform you, "+ GetSexPhrase("Herr kapitan", "fraulein") +", that all necessary goods have been delivered. We are starting construction! According to my calculations, the construction will take a little more than a month.";
				link.l1 = "This is good news! I will look forward to the completion of the construction.";
				link.l1.go = "exit";
				AddDialogExitQuest("ColonyBuilding_1");
				NextDiag.TempNode = "ColonyBuilding_6";
			}
			else
			{
				link.l1 = "I would like to give you the necessary goods.";
				link.l1.go = "ColonyBuilding_5";
				NextDiag.TempNode = "ColonyBuilding_4";
			}
		break;

		case "ColonyBuilding_5":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchColonyBuilding(false, false);
		break;

		case "ColonyBuilding_6":
			dialog.text = "Ah, it's you, "+ GetSexPhrase("Herr kapitan", "fraulein") +"! Construction is in full swing, ya!";
			link.l1 = "See you later.";
			link.l1.go = "exit";
		break;

		case "ColonyBuilding_7":
			dialog.text = "Guten Tag, "+ GetSexPhrase("herr kapitan", "fraulein") +"! I am pleased to inform you that the construction of your colony has been completed! If you need my services again, you can find me at your settlement.";
			link.l1 = "Excellent, Mr. Zalpfer. And now, if you'll excuse me, things are waiting.";
			pchar.questTemp.colonystate = sti(pchar.questTemp.colonystate) + 1;
			UnlockAchievement("AchBuildColony", 1);
			link.l1.go = "exit";
			NextDiag.TempNode = "ColonyBuilding_8";
			AddDialogExitQuest("ColonyBuilding_3");
		break;

		case "ColonyBuilding_exit":
			AddDialogExitQuest("ColonyBuilding");
			PChar.ColonyBuilding.Architector = NPChar.id;
			NextDiag.TempNode = "ColonyBuilding_8";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ColonyBuilding_8":
			dialog.text = "Guten Tag, " + sName + ". Did you want something?";
			link.l1 = "No, nothing. See you later.";
			link.l1.go = "exit";
		break;

		//---------------------------------------------------------------------------------------------------------

		case "ColonyModification":
			dialog.text = "Hmm... This is a completely solvable task. But you have to understand, it will cost you a lot of money. First, we need to meet at a nearby cove and discuss all the details of the upcoming construction.";
			link.l1 = "Okay, see you later.";
			link.l1.go = "ColonyModification_exit";
		break;

		case "ColonyModification_1":
			dialog.text = "Here you are, "+ GetSexPhrase("herr kapitan", "fraulein") +". Well, let's get started. Before we begin our construction, we must decide on the architecture of the future city and its buildings.";
			link.l1 = "Hmm... Let's see...";
			link.l1.go = "ColonyModification_6";
			NextDiag.TempNode = "ColonyModification_5";
		break;

		case "ColonyModification_2":
			AddQuestRecord("ColonyBuilding", "8");
			dialog.text = "Excellent, Captain. And, I want to inform you right away that I will need the following goods for construction - bricks - " + iBricks + " pcs., planks - " + iPlanks + " pcs., mahogany - " + iMahogany + " pcs., ebony - " + iEbony + " pcs., food - " + iFood + " pcs., and " + iSlaves + " slaves. When all this is delivered, we will start construction.";
			link.l1 = "I will try to deliver everything needed as soon as possible.";
			link.l1.go = "ColonyModification_3";
			LAi_SetPlayerType(PChar);
			LAi_SetStayType(CharacterFromID("Builder"));
		break;

		case "ColonyModification_3":
			dialog.text = "What did you want, Captain?";
			if(sti(PChar.BuildingColony.Blocks) == 0 && sti(PChar.BuildingColony.Planks) == 0 && sti(PChar.BuildingColony.Mahogany) == 0 && sti(PChar.BuildingColony.Ebony) == 0 && sti(PChar.BuildingColony.Slaves) == 0 && sti(PChar.BuildingColony.Food) == 0)
			{
				dialog.text = "I am happy to inform you, "+ GetSexPhrase("Herr kapitan", "fraulein") +" that all the necessary goods have been delivered and that we are starting construction. According to my calculations, the construction will take a little more than a month and a half, ya!";
				link.l1 = "I will look forward to the completion of the construction.";
				link.l1.go = "exit";
				AddDialogExitQuest("ColonyModification_2");
				NextDiag.TempNode = "ColonyBuilding_6";
			}
			else
			{
				link.l1 = "I would like to give you the necessary goods.";
				link.l1.go = "ColonyBuilding_5";
				NextDiag.TempNode = "ColonyModification_3";
			}
		break;

		case "ColonyModification_4":
			dialog.text = "I am pleased to inform you that the colony is expanding " + PChar.ColonyBuilding.ColonyName + " completed! It was a pleasure working with you, "+ GetSexPhrase("Herr kapitan", "fraulein") +". I think I'll stay here for a while longer. If you want to find me again, I'll be at the port.";
			link.l1 = "Thank you, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.colonystate = sti(pchar.questTemp.colonystate) + 1;
			UnlockAchievement("AchBuildColony", 2);
			NextDiag.TempNode = "First time";
			AddDialogExitQuest("ColonyModification_4");
			PChar.quest.BuilderToTownhall.win_condition.l1 = "ExitFromLocation";
			PChar.quest.BuilderToTownhall.win_condition.l1.location = PChar.location;
			PChar.quest.BuilderToTownhall.win_condition = "BuilderToTownhall";
		break;

		case "ColonyModification_5":
			dialog.text = "It's you, "+ GetSexPhrase("Herr Kapitan", "fraulein") +" " + sName + "? Shall we discuss the construction details again?";
			link.l1 = "Yes, I want to define the architecture of the city and buildings once again.";
			link.l1.go = "ColonyModification_6";
			link.l2 = "No, I just wanted to visit you.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ColonyModification_5";
		break;

		case "ColonyModification_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchColonyBuilding(true, true);
		break;

		case "ColonyModification_exit":
			PChar.quest.ColonyModification_5.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyModification_5.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyModification_5.win_condition = "ColonyModification_5";

			LAi_SetCitizenType(NPChar);
			AddDialogExitQuest("ColonyModification");
			NextDiag.TempNode = "ColonyBuilding_8";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//---------------------------------------------------------------------------------------------------------

		case "ColonyBuilding_Dominica":
			dialog.text = "It's too risky to be between the islands of France and England - everyone will not miss the chance to make such a tasty morsel their own, and you will find yourself among two fires!";
			link.l1 = "Perhaps you are right. We need to explore further...";
			link.l1.go = "exit";
			AddDialogExitQuest("ColonyBuildingDominica");
		break;

		case "ColonyBuilding_Terks":
			dialog.text = "No, no, Turks is too close to the place of refuge of the damned pirates, and it would be madness to build a colony under their noses, ya!";
			link.l1 = "Perhaps you are right. We need to explore further...";
			link.l1.go = "exit";
			AddDialogExitQuest("ColonyBuildingTerks");
		break;

		//---------------------------------------------------------------------------------------------------------

		case "ColonyFortBuildingNoNo":
			dialog.text = "Hmm... I don't want to upset you, "+ GetSexPhrase("Herr Kapitan", "Fraulein") +", but the terrain of the island does not allow the construction of a fortification. I can offer you the construction of a kind of security base - it will allow you to have an impressive garrison capable of repelling any rival, and also create favorable conditions for putting up good protection of the coastline. In addition, the creation of a security base will close all approaches to the colony from land, which will significantly strengthen protection in this case, that is, when trying to attacks by enemy units on your city from the land. What do you think, "+GetSexPhrase("herr", "frau")+"Captain?";
			link.l1 = "The colony must be protected. Therefore, we should discuss the details of building a protective base in more detail.";
			link.l1.go = "ColonyFortBuilding";
			link.l2 = "Sorry, I have to go.";
			link.l2.go = "exit";
		break;

		case "ColonyFortBuilding":
			if(CheckAttribute(pchar, "VedekerDiscount"))
			{
				NPChar.NeedMoney = (1000000 * MOD_SKILL_ENEMY_RATE)/2;
				dialog.text = "I will be happy to help you, ya! But it will cost you a lot of money. For my work, I want to receive "+Sti(NPChar.NeedMoney)+"gold.";
			}
			else
			{
				NPChar.NeedMoney = 1000000 * MOD_SKILL_ENEMY_RATE;
			    dialog.text = "I will be happy to help you, ya! But it will cost you a lot of money. For my work, I want to receive "+Sti(NPChar.NeedMoney)+"gold.";
			}
			if(sti(PChar.money) >= Sti(NPChar.NeedMoney))
			{
				link.l1 = "I agree.";
				link.l1.go = "ColonyFortBuilding_1";
			}
			else
			{
				link.l2 = "I don't have enough money yet.";
				link.l2.go = "exit";
			}
			link.l3 = "Sorry, I have to go.";
			link.l3.go = "exit";
		break;

		case "ColonyFortBuilding_1":
			dialog.text = "Excellent, "+ GetSexPhrase("herr kapitan", "fraulein") +"! Meet me at a place called 'A deserted beach' - that's where the foundation of our security structure will be laid.";
			link.l1 = "See you later.";
			link.l1.go = "ColonyFortBuilding_to_port";
			AddDialogExitQuest("ColonyFortBuilding_1");
		break;

		case "ColonyFortBuilding_2":
			dialog.text = "Excellent, "+ GetSexPhrase("herr kapitan", "fraulein") +"! Meet me at a place called 'A deserted beach'.";
			link.l1 = "See you later.";
			link.l1.go = "ColonyFortBuilding_to_port";
		break;

		case "ColonyFortBuilding_3":
			AddMoneyToCharacter(PChar, -sti(NPChar.NeedMoney));
			dialog.text = "For construction, we will need the following goods: Bricks - " + iBricks + " pcs., planks - " + iPlanks + " pcs., mahogany - " + iMahogany + " pcs., ebony - " + iEbony + " pcs., food - " + iFood + " pcs., and " + iSlaves + " slaves.";
			link.l1 = "I will try to deliver everything needed as soon as possible.";
			link.l1.go = "ColonyFortBuilding_to_start_transfer_goods";
			AddDialogExitQuest("ColonyFortBuilding_4");
		break;

		case "ColonyFortBuilding_4":
			dialog.text = "What did you want, "+ GetSexPhrase("herr kapitan", "fraulein") +"?";
			if(sti(PChar.BuildingColony.Blocks) == 0 && sti(PChar.BuildingColony.Planks) == 0 && sti(PChar.BuildingColony.Mahogany) == 0 && sti(PChar.BuildingColony.Ebony) == 0 && sti(PChar.BuildingColony.Slaves) == 0 && sti(PChar.BuildingColony.Food) == 0)
			{
				dialog.text = "I am pleased to inform you, captain, that all the necessary goods have been delivered. We are starting the construction of the base! If nothing supernatural happens, then in a month and a half at this place you will see a completely different picture, ya.";
				link.l1 = "Okay, sir " + GetFullName(NPChar) + ".";
				link.l1.go = "exit";
				AddDialogExitQuest("ColonyFortBuilding_5");
				NextDiag.TempNode = "ColonyFortBuilding_5";
			}
			else
			{
				link.l1 = "I would like to give you the necessary goods.";
				link.l1.go = "ColonyBuilding_5";
				NextDiag.TempNode = "ColonyFortBuilding_4";
			}
		break;

		case "ColonyFortBuilding_5":
			dialog.text = "Ah, it's you, "+ GetSexPhrase("Herr kapitan", "fraulein") +"! Construction is in full swing!";
			link.l1 = "See you later.";
			link.l1.go = "exit";
		break;

		case "ColonyFortBuilding_6":
			dialog.text = "The creation of a security base for your colony is complete! It was a pleasure working with you, "+ GetSexPhrase("Herr kapitan", "fraulein") +". I'm going home.";
			link.l1 = "Thank you for your work, Mr. Zalpfer.";
			link.l1.go = "exit";
			pchar.questTemp.colonystate = sti(pchar.questTemp.colonystate) + 1;
			UnlockAchievement("AchBuildColony", 3);
			NextDiag.TempNode = "First Time";
			AddDialogExitQuest("ColonyFortBuilding_7");
		break;

		case "ColonyFortBuilding_to_port":
			LAi_SetCitizenType(NPChar);
			NextDiag.TempNode = "ColonyBuilding_8";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ColonyFortBuilding_to_start_transfer_goods":
			NextDiag.TempNode = "ColonyFortBuilding_4";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ForSlave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("I'm so tired - I'm just falling off my feet.", "I can't live like this anymore!"), RandPhraseSimple("This job is too hard for me.", "The overseers have already left no living place on my skin!"));
			link.l1 = RandPhraseSimple("Sorry, buddy.", "I feel sorry for you.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ForSlave";
		break;

		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this city, I ask you not to walk with a naked blade here.", "You know, as a citizen of this city, I ask you not to walk with a naked blade here.");
				link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful on turns, "+GetSexPhrase("buddy", "girlfriend")+", when you run with a gun in your hand. I can get nervous...", "I don't like it when"+GetSexPhrase("men", "girls")+" they walk in front of me with weapons at the ready. It scares me...");
				link.l1 = RandPhraseSimple("Understood.", "I'm removing.");
			}
			link.l1.go = "exit";
		break;

	}
}
