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
				link.l1 = "Buddy, do you know if a certain Edward Law lives in your city?";
				link.l1.go = "PL_Q2_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_KV"))	//Квест ***Проклятая жара***		(Вино)
			{
				link.l1 = "I just remembered I was asked to buy a bottle of wine.";
				link.l1.go = "PDM_PJ_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_KR"))	//Квест ***Проклятая жара***		(Ром)
			{
				link.l1 = "I need to buy some rum.";
				link.l1.go = "PDM_PJ_Rom_1";
			}
		break;
		case "PL_Q2_1":
			dialog.text = NPCStringReactionRepeat("No, this is the first time I've heard it. We don't have that in the city.",
				"You've already "+ GetSexPhrase("asked", "asked") +"about him, we don't have anyone.",
				"I already answered that Edward Law is out of town.",
                "Tired...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Understood... Thank you.",
				"Yes, yes, I understand...",
                "Got it...",
				"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

		case "PDM_PJ_1":
			dialog.text = "So it's not a problem! Heh-heh-heh! You've come to the right place, and you're talking to the right person! Would you like a bottle of wine? You can buy a barrel! The best wine in the whole archipelago!",
			link.l1 = "Well, that's just great, but I only need one bottle. How much do you want for it?",
			link.l1.go = "PDM_PJ_2";
		break;

		case "PDM_PJ_2":
			dialog.text = "Oh, "+ GetSexPhrase("monsieur", "mademoiselle") +", I am sure that you will feel the true value of this divine nectar! You will receive a bottle of my fine old wine for only 200 gold coins!",
			MakeRandomLinkOrderThree(link,
			"I'll take the wine, " + npchar.name+". But with these prices, you're unlikely to get many buyers.",
			"PDM_PJ_Beru_1",

			"But that's stupid! For that price, I can buy a great Burgundy from France! You're trying to trick me, you scoundrel!",
			"PDM_PJ_Beru_2",

			"Forget about it. The guard will do without his bottle of wine.",
			"exit");
		break;

		case "PDM_PJ_Beru_1":
			dialog.text = "Here's your bottle... A noble wine for a noble man, hehe hehe. You will not be disappointed, "+ GetSexPhrase("monsieur", "mademoiselle") +". Do you want anything else?",
			link.l1 = "No, I don't want to. And I hope that such a fountain of wit as you will be able to appreciate the irony of what is happening - I am buying this bottle of exquisite expensive wine for a simple French soldier. Goodbye, " + npchar.name+".",
			link.l1.go = "PDM_PJ_Beru_3";
		break;

		case "PDM_PJ_Beru_2":
			dialog.text = "Inflate? Hehe hehe, "+ GetSexPhrase("monsieur", "mademoiselle") +", of course you're joking. Yes, in France you can buy a bottle of Burgundy for 200 gold. But Martinique isn't in France, is it? Heh heh heh!",
			link.l1 = "Give me this damn wine, and in the name of God, stop this giggling!",
			link.l1.go = "PDM_PJ_Beru_3";
		break;

		case "PDM_PJ_Beru_3":
			DialogExit();

			AddQuestRecord("PDM_Proklyataya_Jara", "2");
			GiveItem2Character(PChar, "PDM_PJ_Vino");
			AddMoneyToCharacter(pchar, -200);
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KV");
			DeleteAttribute(pchar, "questTemp.PDM_PJ_SS");
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Prines_Vino_1";
		break;

		case "PDM_PJ_Rom_1":
			dialog.text = "It's much easier to deal with wine, yes, yes! Rum is the cheapest drink you can buy in the archipelago, but, "+ GetSexPhrase("monsieur", "mademoiselle") +", I never sell an amount of rum with a volume less than a barrel! Heh heh heh! No one bottles rum! Heh heh heh!",
			link.l1 = "Yes, okay, " + npchar.name+"! Sailors constantly drink rum in your tavern and don't buy it with barrels...",
			link.l1.go = "PDM_PJ_Rom_2";
		break;

		case "PDM_PJ_Rom_2":
			dialog.text = "Oh, you are so insightful, that is, that is. Only... they drink rum from mugs, and I fill mugs from a barrel. Of course, I can sell you a mug of rum... But, "+ GetSexPhrase("monsieur", "mademoiselle") +", you're not walking down the street with a mug in your hand, are you? Heh heh heh! Oh, how the guys will laugh!",
			link.l1 = "This is the funniest nonsense... Wait! You can fill these empty wine bottles with rum from a barrel! That's all! There is no problem...",
			link.l1.go = "PDM_PJ_Rom_3";
		break;

		case "PDM_PJ_Rom_3":
			dialog.text = "Truly, you are almost a genius, Captain. You're absolutely right, I can do it... But I hope you understand that these are exclusive, special services... the bottle is washed and dried by hand, you know...  I can sell my client bottled rum for... 200 coins! Heh heh heh!",
			link.l1 = "You're completely out of your mind, " + npchar.name+". 200 coins for cheap rum? No! Goodbye!",
			link.l1.go = "exit";
			link.l2 = "Well, good! You really amused me, you scoundrel. Here's your money. Give me the rum. You certainly deserve your gold.",
			link.l2.go = "PDM_PJ_Rom_4";
		break;

		case "PDM_PJ_Rom_4":
			dialog.text = "Thank you, "+ GetSexPhrase("monsieur", "mademoiselle") +". Wait a minute please\n"+
							"Here's your TWO-bottled cask of rum, Captain. I tied it up with pink ribbons for you personally... Oh, heh heh heh...",
			link.l1 = "Caution, " + npchar.name+", one day you'll just suffocate with laughter. I think if I don't leave here, that's exactly what's going to happen. Goodbye.",
			link.l1.go = "PDM_PJ_Rom_5";
			AddMoneyToCharacter(pchar, -200);
		break;

		case "PDM_PJ_Rom_5":
			DialogExit();

			Log_info("You got two bottles, one of which is now YOURS");
			GiveItem2Character(PChar, "PDM_PJ_Rom");
			GiveItem2Character(PChar, "PDM_PJ_BsRL");
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KR");
			sld = CharacterFromID("PDM_PJ_Strajnik_2")
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Prines_Rom_1";
			AddQuestRecord("PDM_Proklyataya_Jara", "4");
			
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "stun_1", "", 1.0);
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

