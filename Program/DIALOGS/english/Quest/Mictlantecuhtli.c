
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arChestItems;
	string sBlade;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "I don't want to talk.";
			link.l1 = "Whatever you want.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//должок ростовщика ГПК
		case "ClimeUsurer":
			dialog.text = "You owe to my adept named Augusto Brahms!";
			link.l1 = "Me? Oh, well, yes, there was a case... Um, but I didn't know that he was your adept.";
			link.l1.go = "ClimeUsurer_1";
		break;
		case "ClimeUsurer_1":
			dialog.text = "Nevertheless, it is so. You should give " + FindRussianMoneyString(sti(pchar.questTemp.LSC_climeUsurer.qtyMoney )) + " to me immediately . Do you have enough money?";
			if (sti(pchar.money) >= sti(pchar.questTemp.LSC_climeUsurer.qtyMoney))
			{
				link.l1 = "Um, there are...";
				link.l1.go = "ClimeUsurer_yes";
			}
			else
			{
				link.l1 = "Somehow all this is unexpected... I didn't know that I would have to pay off so quickly.";
				link.l1.go = "ClimeUsurer_no";
			}
		break;
		case "ClimeUsurer_yes":
			dialog.text = "Okay. Then I'll let you go.";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LSC_climeUsurer.qtyMoney));
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("ClimeUsurer_haveMoney");
		break;
		case "ClimeUsurer_no":
			dialog.text = "Didn't know?!!Then you will stay in the temple of Sacrifice forever! One more skull, one less...";
			link.l1 = "How is this so?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClimeUsurer_noMoney");
		break;

		//в большом храме разговор перед боевкой
		case "InGreateTemple":
			dialog.text = "How dare you, mortal?!!";
			link.l1 = "Both are on!.. If I'm not mistaken, then you are the god of the dead.";
			link.l1.go = "InGreateTemple_1";
		break;
		case "InGreateTemple_1":
			dialog.text = "That's right, I've been watching you for a long time, your prowling around Tenochtitlan has been entertaining me. But now you've taken the subject of my cult, and it's not funny anymore...";
			link.l1 = "You see, dear God, I was ordered this very item by a certain Aztec, whose name is not accepted here.";
			link.l1.go = "InGreateTemple_2";
		break;
		case "InGreateTemple_2":
			dialog.text = "Montezuma? Haha, it won't calm down. Although, it can't be otherwise.. Well, you touched the jade skull, and this is a crime. But you managed to neutralize the guard, which consists of their heroes of the past, the Aztecs revered military valor more than anything else in the world. You have shown that you are a good warrior, "+ GetSexPhrase(""," despite the fact that you are a woman,") +" therefore, I will give you a chance to survive. Prove that you are a great warrior, and you can leave here.";
			link.l1 = "What I should do?";
			link.l1.go = "InGreateTemple_3";
		break;
		case "InGreateTemple_3":
			dialog.text = "Fight me. Let's get started!";
			link.l1 = "Nowhere to go...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Teno_fightInTemple");
		break;

		//в большом храме разговор после боевки
		case "WinInTemple":
			dialog.text = "Well, you proved that you deserve. Now you can leave here alive.";
			link.l1 = "Uv-f-f... If you want, I'll put the skull back in its place.";
			link.l1.go = "WinInTemple_1";
		break;
		case "WinInTemple_1":
			dialog.text = "No need, I have a lot of them. You can keep the skull, you deserve it.";
			link.l1 = "Thank you, dear God.";
			link.l1.go = "WinInTemple_2";
		break;
		case "WinInTemple_2":
			dialog.text = "Before you leave, I want to tell you who Montezuma is.";
			link.l1 = "Very interesting to listen to.";
			link.l1.go = "WinInTemple_3";
		break;
		case "WinInTemple_3":
			dialog.text = "This is Montezuma the Second, the last leader of the Aztec Empire. 150 years ago, he betrayed the gods of his people when he tried to negotiate with Spanish missionaries to convert to Christianity\n"+
				"We, the Aztec gods, did not forgive his betrayal and cursed Montezuma, although in the end almost all the gods had to go into limbo. I'm the only one left here.";
			link.l1 = "Excuse me, go where? To limbo?";
			link.l1.go = "WinInTemple_4";
		break;
		case "WinInTemple_4":
			dialog.text = "Gods live only when people worship them. If the gods are forgotten, then they have to go into limbo, the world of oblivion. I stayed on Earth only because now the entire Aztec people belong to me, because all the Aztecs were exterminated by the Spaniards, left without our help.. n"+
				"I have the power to make dead bodies live a new life. Having become the master of Tenochtitlan, I raise the deceased I need for service.. n"+
				"Montezuma is cursed, the passage to the kingdom of the dead is closed to him, and he is forced to walk forever along the shores of Lake Texcoco and mourn the fate of his people.";
			link.l1 = "So it's a ghost?!";
			link.l1.go = "WinInTemple_5";
		break;
		case "WinInTemple_5":
			dialog.text = "You could say that. Now you know who the Aztec is on the shores of Texcoco. And know that the jade skull has power over the dead, and can also help the cursed living, forgive me, warrior.";
			link.l1 = "Goodbye, dear Mitklan... Mictlan...";
			link.l1.go = "WinInTemple_6";
		break;
		case "WinInTemple_6":
			chrDisableReloadToLocation = false;
			ChangeCharacterAddress(npchar, "none", "");
			AddQuestRecord("Tenochtitlan", "4");
			AddQuestUserData("Tenochtitlan", "sSex", GetSexPhrase("","a"));
			DialogExit();
		break;

		case "Samil":
			dialog.text = "You are impressedme, mortal. No one has ever managed to defeat my earthly incarnation. Know that you see Yum Samil himself in the flesh!";
			link.l1 = "Yum... whom? I looked into this temple for valuables, but didn't find there absolutely nothing except an entire army of undead.";
			link.l1.go = "Samil_2";
			if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_1_man");
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_1_woman");
		break;

		case "Samil_2":
			dialog.text = "How many years have passed since mortals have already forgotten my name...";
			link.l1 = "I think it is very, very much. I've never heard about you.";
			link.l1.go = "Samil_3";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_2");
		break;

		case "Samil_3":
			dialog.text = "I believe this is the fate of all the gods of now-vanished civilizations. They are forgotten in the void, losing their strength due to the lack of an influx of strength from believers...";
			link.l1 = "...";
			link.l1.go = "Samil_4";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_3");
		break;

		case "Samil_4":
			dialog.text = "Well, let's not talk about sad things. You beat me and deserve a reward. I think this blade of the previous visitor will be useful to you.";
			link.l1 = "Thank you, Yum Samil.";
			link.l1.go = "Samil_5";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			log_info("You got a One-and-a-half Flamberge from Yum Samil");
			UnlockAchievement("AchUmSamil", 3);
			TakeNItems(pchar,"blade48",1);
			TakeNItems(pchar,"pistol9",1);
			TakeNItems(pchar,"talisman18",1);
			if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_4_man");
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_4_woman");
		break;

		case "Samil_5":
			dialog.text = "I think it's time to say goodbye. Tell people about this meeting. I don't want to be forgotten forever like everyone else... I can't ask you to worship either, our cultures are too different. Goodbye, warrior.";
			link.l1 = "I promise never to forget our meeting. Goodbye!";
			link.l1.go = "Samil_6";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Samil_5");
		break;

		case "Samil_6":
			chrDisableReloadToLocation = false;
			ChangeCharacterAddress(npchar, "none", "");
			pchar.quest.treasure_portal.win_condition.l1 = "locator";
			pchar.quest.treasure_portal.win_condition.l1.location = "Treasure_alcove";
			pchar.quest.treasure_portal.win_condition.l1.locator_group = "teleport";
			pchar.quest.treasure_portal.win_condition.l1.locator = "teleport6";
			pchar.quest.treasure_portal.win_condition = "treasure_portal";
			DialogExit();
		break;

		case "Uicilopochtli_F_0":
			dialog.text = "Greetings, mortal" + GetSexPhrase("th.","th.");
			link.l1 = "Ahem... Hello, Mictlan... Mictlan...";
			link.l1.go = "Uicilopochtli_F_1";
		break;

		case "Uicilopochtli_F_1":
			dialog.text = "What?! How dare you! I am Huitzilopochtli, the god of war, the most powerful warrior among men and gods, and Mictlantecutli is no match for me in strength and endurance. You insulted me, and for that you will suffer a painful death. Get ready to see what Huitzilopochtli is like in battle!";
			link.l1 = "Oh, damn...";
			link.l1.go = "Uicilopochtli_F_2";
		break;

		case "Uicilopochtli_F_2":
			dialog.text = "Haha, are you shaking? Is that so, is it impossible to make a joke? Ha ha ha! Calm down, I won't rush at you for touching the tile. Ha ha ha!";
			link.l1 = "Phew, thanks. To be honest, the fight with Mictlantecutli was enough for me...";
			link.l1.go = "Uicilopochtli_F_3";
		break;

		case "Uicilopochtli_F_3":
			dialog.text = "Yes, Miklukha is in his repertoire... He probably told you that the skull is a cult object that you can't touch? Yeah, but how is he going to perform rituals if you don't touch the skull? So you know - this character just wanted to add you to his collection. He loves the souls of fallen warriors, and here " + GetSexPhrase("such a master of the sword turned up","such a master of the sword turned up") + "like you.";
			link.l1 = "It's good that I managed to get out of that mess. I would not like to become the guardian of Tenochtitlan forever.";
			link.l1.go = "Uicilopochtli_F_4";
		break;

		case "Uicilopochtli_F_4":
			dialog.text = "And don't say - you would " + GetSexPhrase("died","died") + " out of boredom, haha! And it was high time for the 'dead god' to wipe his nose - he became so pompous after the fall of the Aztecs... While everyone is bored in limbo, he is walking around with his toys and has never looked in on us. Even Mictlancihuatl did not visit, the poor thing remained completely without male attention, can you imagine? And after all, I offered him: you have a whole army here, I say, let's arrange a massacre between them, have fun, break the bones? But he's still not there - you see, he's busy, Tenochtitlan needs to be guarded. Well, I was afraid that you " + GetSexPhrase("I came and killed all his guards","I came and killed all his guards") + "Ha ha!";
			link.l1 = "That's how... By the way... Don't be impertinent, dear god, but if all the gods except Mictlantecutli are in limbo, then how did you end up here?";
			link.l1.go = "Uicilopochtli_F_5";
		break;

		case "Uicilopochtli_F_5":
			dialog.text = "I won't count it, " + GetSexPhrase("buddy","darling") + ". Yes, I was stuck in limbo for a very long time and couldn't get out of there. But then you " + GetSexPhrase("arranged", "arranged") + " there is a mess with the spirits of Aztec warriors, and this brought back the Aztec military glory from oblivion and strengthened my strength as a god of war. At some point, I felt that I could move here and decided not to miss the moment because you " + GetSexPhrase("rendered","rendered") + " I need a service for which you are entitled to a reward. From now on, I allow you to perform the ritual of worshiping Huitzilopochtli!";
			link.l1 = "Hmm, thanks...";
			link.l1.go = "Uicilopochtli_F_6";
		break;

		case "Uicilopochtli_F_6":
			dialog.text = "You're not very happy, aren't you? It's okay, I'll explain everything to you now. The ritual of worship is that you make a sacrifice and ask to be given strength for future battles. And if you do everything right, then you get this power, namely, your blade gets better.";
			link.l1 = "Yeah, so you can upgrade my weapon?";
			link.l1.go = "Uicilopochtli_F_7";
		break;

		case "Uicilopochtli_F_7":
			dialog.text = "Yes, I can, if you perform the ritual. You didn't think that it was Mictlantecutli that made macuauitli so deadly? But let me just outline some limitations First - I will not improve the weapon beyond its engineering capabilities. I could have, but then it would have turned into a magical weapon of the gods and... well, such a blade in human hands has never done any good. But I am sure that you will still be able to feel the improvement of the second - at one time I can improve only one of the characteristics - reduce weight or increase the minimum or maximum damage. You will not be able to choose the characteristics and the amount of improvement - after all, worshipping God is an inaccurate science. But you will be able to perform many rituals on the same blade, and after a certain number of them, your weapon will improve to perfect condition.";
			link.l1 = "Sounds good. And what about the victims? Will you need many prisoners?";
			link.l1.go = "Uicilopochtli_F_8";
		break;

		case "Uicilopochtli_F_8":
			dialog.text = "No, I don't need your prisoners. I've never liked these customs. Screams, screams - they are good if the enemy makes them in a fair battle, and not when tied to the altar. I tried for a long time to explain to the Aztecs that human sacrifice is part of the Mictlantecutli, but it's no use - they really loved to cut people.  The ritual should consist of two parts. The first is the weapon of defeated enemies. For one ritual, you will need three other blades of the same quality as your weapon. The second is gold, in an amount equivalent to three times the value of the blade. I don't really need it, it's just a tradition, and there's no way without it. Are there shamans in your people? They probably won't even talk to you without gold, right?";
			link.l1 = "Hehe, yes, you can't argue with that.";
			link.l1.go = "Uicilopochtli_F_9";
		break;

		case "Uicilopochtli_F_9":
			dialog.text = "So I'm trying not to seem like a black sheep... In general, you collect this stuff, put it on the altar, turn to me - and if everything is fine, I will take the victim and improve the blade equipped by you. And don't worry, if something goes wrong - for example, the sacrifice on the altar will not be enough or your blade will have nowhere to improve - I will not cheat, I will tell everything as it is, and everything on the altar will remain with you.";
			link.l1 = "Understood. And how should I be treated?";
			link.l1.go = "Uicilopochtli_F_10";
		break;

		case "Uicilopochtli_F_10":
			dialog.text = "Yes, just ask from the bottom of your heart, haha! In the end, it's a mutually beneficial deal-you get better weapons, and I get worship, fueling my divine powers. So come, don't be shy."
			link.l1 = "Well, thank you for this opportunity, dear God. I'll look in on occasion.";
			link.l1.go = "Uicilopochtli_exit";
			LAi_SetStayType(NPChar);
		break;

		case "Uicilopochtli_exit":
			NPChar.dialog.currentnode = "Uicilopochtli_default";
			DialogExit();
		break;

		case "Uicilopochtli_default":
			dialog.text = "Greetings, mortal" + GetSexPhrase("th.","th.");
			link.l1 = "O great god of war Huitzilopochtli! I present to you as a gift the weapons of the enemies I defeated and ask you to give me strength for future battles!";
			link.l1.go = "Uicilopochtli_improve";

			if (CheckAttribute(pchar,"ScamFanActive") && CheckAttribute(pchar,"KnowScam") && !CheckAttribute(pchar,"ScamDestroyed"))
			{
				link.l2 = "Hello, Huitzilopochtli. Sorry to bother you, but I have a problem here...";
				link.l2.go = "Uicilopochtli_fan_1";
			}

			link.l3 = "Hello, Huitzilopochtli. I'm just saying hello " + GetSexPhrase("I came in...", "I came in...");
			link.l3.go = "Uicilopochtli_exit";
		break;

		case "Uicilopochtli_improve":
			sBlade = GetCharacterEquipByGroup(PChar, BLADE_ITEM_TYPE);
			if (sBlade == "")
			{
				dialog.text = "I wouldn't mind, but you didn't equip the blade" + GetSexPhrase(".","a.");
				link.l1 = "Exactly! I'll figure it out now.";
				link.l1.go = "Uicilopochtli_exit";
				break;
			}

			if (BladeIsPerfect(sBlade))
			{
				dialog.text = "Thanks for the gifts, but the fact is that your blade has already reached its limits of perfection, so I can't improve it even more, I'm sorry.";
				link.l1 = "Is that so? Okay.";
				link.l1.go = "Uicilopochtli_exit";
				break;
			}

			makearef(arChestItems, Locations[FindLocation(PChar.location)].box1);
			if (!TryTakeSacrificeForBladeImprovement(arChestItems, sBlade))
			{
				dialog.text = "Your sacrifice is not enough. I remind you, you need three blades of equivalent quality to yours and gold in an amount equivalent to three times the value of your blade.";
				link.l1 = "Okay, whatever you say.";
				link.l1.go = "Uicilopochtli_exit";
				break;
			}

			RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(PChar, sBlade);
			sBlade = ImproveGeneratedBlade(sBlade, 0.25);
			GiveItem2Character(PChar, sBlade);
			EquipCharacterByItem(PChar, sBlade);
			Dialog.Text = "Thank you, mortal" + GetSexPhrase("th.","th.");
			link.l1 = "And thank you, dear God.";
			link.l1.go = "Uicilopochtli_exit";
		break;

		case "Uicilopochtli_fan_1":
			dialog.text = "Problem?"
			link.l1 = "Yeah. Do you see that scarecrow running after me? I want to get rid of him, but I still can't. I've already tried - neither rapier, nor chisel, nor musket take it. And it would be all right, but he's so annoying that I'm going to go crazy soon.";
			link.l1.go = "Uicilopochtli_fan_2";
		break;

		case "Uicilopochtli_fan_2":
			dialog.text = "That's how it is. Wait a minute... But this is the fool that Mictlantecutli made immortal, haha! I can't believe that you still haven't lost - this guy can melt brains."
			link.l1 = "It seems that a little more and my brains will melt... Can you do something about it?";
			link.l1.go = "Uicilopochtli_fan_3";
		break;

		case "Uicilopochtli_fan_3":
			dialog.text = "Yes, I'll take him to limbo. Kamashtli has not hunted for a long time, it will be fun for the old man... Well, you should get a reward. Here, I give you a blade equal in value to this character, haha! Don't thank me, ha ha ha!"
			link.l1 = "Thank you, Huitzilopochtli! And he saved me from a mental disorder, and gave me a weapon...";
			link.l1.go = "Uicilopochtli_exit";

			ref rChar = CharacterFromID("ScamCharacter");
			rChar.LifeDay = 0;
			ChangeCharacterAddressGroup(rChar, "none", "", "");
			pchar.ScamDestroyed = true;
			Log_info("The most devoted fan of the Scam Games Arena champion is forever behind you.");

			GiveItem2Character(PChar, GenerateBladeByParams("blade28", 1, 1, 25));
		break;
	}
}

bool TryTakeSacrificeForBladeImprovement(aref arChestItems, string sBlade)
{
	int price = GetItemPrice(sBlade) * 3;
	if (sti(arChestItems.money) < price)
	{
		return false;
	}

	object bladesToTake;
	aref arBlades, arItem;
	makearef(arBlades, arChestItems.Items);
	string sCurrBlade, sCurrBladeQuality;
	string sBladeQuality = ItemsFromID(sBlade).quality;
	int bladesCount = 3;
	int i, num;
	for (i = 0; (i < GetAttributesNum(arBlades)) && (bladesCount > 0); i++)
	{
		arItem = GetAttributeN(arBlades, i);
		sCurrBlade = GetAttributeName(arItem);
		num = sti(GetAttributeValue(arItem));

		if (!IsBlade(sCurrBlade))
		{
			continue;
		}

		sCurrBladeQuality = ItemsFromID(sCurrBlade).quality;
		if (sCurrBladeQuality == sBladeQuality)
		{
			num = func_min(num, bladesCount);
			bladesToTake.(sCurrBlade) = num;
			bladesCount = bladesCount - num;
		}
	}

	if (bladesCount > 0)
	{
		return false;
	}

	arChestItems.money = sti(arChestItems.money) - price;
	makearef(arBlades, bladesToTake);
	for (i = 0; i < GetAttributesNum(arBlades); i++)
	{
		arItem = GetAttributeN(arBlades, i);
		sCurrBlade = GetAttributeName(arItem);
		num = sti(GetAttributeValue(arItem));
		TakeNItems(arChestItems, sCurrBlade, -num);
	}
	return true;
}
