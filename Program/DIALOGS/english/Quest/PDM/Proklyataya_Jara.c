
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":							//Автор Sinistra
			dialog.text = "Hey, you! What are you doing hanging around here! Come here, "+ GetSexPhrase("guy", "girl") +"!";
			link.l1 = "My name is Captain "+pchar.name+"and I'm strolling, not hanging out!";
			link.l1.go = "Mne_Jarko_1";
			PlayVoice("Kopcapkz\Voices\PDM\Hervisse - Town Guard.wav");
		break;

		case "Mne_Jarko_1":
			dialog.text = "Oh, sorry, Captain. I didn't recognize you right away. It's the damn heat.";
			MakeRandomLinkOrderTwo(link,
			"I accept your apologies. Standing here in the sun all day is probably not very pleasant. Do they even give you a break during the watch?",
			"Mne_Jarko_2",

			"No, it's not enough. You are careless and untidy looking. Be more polite next time.",
			"exit");
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS");
		break;

		case "Mne_Jarko_2":
			dialog.text = "Sometimes we change with each other, left to right, right to left... It all depends on where the shadow falls. It's terrible, I would give anything for a sip of cool wine.";
			link.l1 = "Yes, it's just disgusting... Maybe I can help you in some way?";
			link.l1.go = "Mne_Jarko_3";
		break;

		case "Mne_Jarko_3":
			dialog.text = "Oh, thank you, "+ GetSexPhrase("monsieur", "mademoiselle") +"! All I can dream about right now is just a little sip of wine. Of course, I'm not supposed to drink on duty, but still... Would you mind bringing me a bottle of wine? I could even pay you for it.";
			MakeRandomLinkOrderTwo(link,
			"I know how hard debt can be sometimes... I'll bring you a bottle of wine.",
			"Mne_Jarko_4",

			"Soldier, you are very close to overstepping the bounds of duty. I'll close my eyes to that for now... But don't ask me to do it anymore. See you later.",
			"exit");
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";
		break;

		case "Mne_Jarko_4":
			dialog.text = "I am eternally indebted to you. Please hurry up.";
			link.l1 = "I'll be back before you blink.";
			link.l1.go = "Mne_Jarko_5";
			DeleteAttribute(npchar, "talker");
		break;

		case "Mne_Jarko_5":
			SetQuestHeader("PDM_Proklyataya_Jara");
			AddQuestRecord("PDM_Proklyataya_Jara", "1");
			DialogExit();
			pchar.questTemp.PDM_PJ_KV = "KupitVino";
			pchar.questTemp.PDM_PJ_SS = "SdatSoldata";
			sld = CharacterFromID("PDM_PJ_Strajnik_1");
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Mne_Jarko_5_EsheRaz";
		break;

		case "Mne_Jarko_5_EsheRaz":
			dialog.text = "Have you brought wine for me?";
			link.l1 = "Not yet, I was just looking around the city. But I'll stop by the tavern later.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Mne_Jarko_5_EsheRaz";
		break;

		case "Prines_Vino_1":
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";
			dialog.text = "Greetings once again, "+ GetSexPhrase("monsieur", "mademoiselle") +"Captain! Did you bring me wine?";
			link.l1 = "Here, take it.";
			link.l1.go = "Prines_Vino_2";
		break;

		case "Prines_Vino_2":
			TakeItemFromCharacter(pchar, "PDM_PJ_Vino");
			dialog.text = "I didn't think that you would really be able to bring me a bottle. Thank you, Captain "+pchar.name+". How much do I owe you for this wine?";
			MakeRandomLinkOrderTwo(link,
			"Don't worry about the money-it was nice to do this for you.",
			"Prines_Vino_Drujba_1",

			"500 gold. I asked not very expensive wine, but it looks like your tavern is run by a former pirate, this " + GetFullName(CharacterFromID("FortFrance_tavernkeeper"))+".",
			"Prines_Vino_Obman_1");
		break;

		case "Prines_Vino_Drujba_1":
			dialog.text = "You are a very kind person. I will be happy to serve you if you need anything.";
			link.l1 = "Thanks, buddy. See you later.";
			link.l1.go = "A_Eto_eshe_ne_vse";
			ChangeCharacterReputation(pchar, 3);
		break;

		case "Prines_Vino_Obman_1":
			dialog.text = "500 gold? But that's half my salary... what am I supposed to do now?";
			MakeRandomLinkOrderTwo(link,
			"You should have thought about this earlier. Now pay up.",
			"Prines_Vino_Obman_2",

			"Forget about it. Let's consider this bottle just a gift.",
			"Prines_Vino_Drujba_1");
		break;

		case "Prines_Vino_Obman_2":
			dialog.text = "Damn it. Well, if I come across this " + GetFullName(CharacterFromID("FortFrance_tavernkeeper"))+". All right, take the money. That's it, I need to stand guard, I can't talk to you anymore. See you later.";
			link.l1 = "Goodbye, soldier.";
			link.l1.go = "A_Eto_eshe_ne_vse";
			ChangeCharacterReputation(pchar, -4);
			AddMoneyToCharacter(pchar, 437);
		break;

		case "A_Eto_eshe_ne_vse":
			DialogExit();
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Ya_Toje_Hochu_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0.0, 0);
		break;

		case "Ya_Toje_Hochu_1":
			PlayVoice("Kopcapkz\Voices\PDM\Eustache Heumont.wav");
			dialog.text = "Greetings, "+ GetSexPhrase("monsieur", "mademoiselle") +". Glad to see you!";
			link.l1 = "Why are you so glad to see me, soldier? And what is that grin on your face?";
			link.l1.go = "Ya_Toje_Hochu_2";
		break;

		case "Ya_Toje_Hochu_2":
			dialog.text = "I know that you are a kind person. I saw you bring my partner a bottle of wine... It was a Christian act, and I appreciated it. I also wanted to ask you, Captain... Could you show me the same mercy, too? Please, Captain!";
			link.l1 = "What?!? Do you want me to buy wine?";
			link.l1.go = "Ya_Toje_Hochu_3";
		break;

		case "Ya_Toje_Hochu_3":
			dialog.text = "Well, to tell the truth, I'm not a big fan of wine. But I could use a drop of rum.";
			MakeRandomLinkOrderTwo(link,
			"Well, you're not exactly a shy boy... Oh well. To be honest, I confused by my own soft-heartedness, but I'll buy you some rum. Wait for me here.",
			"Ya_Toje_Hochu_4",

			"Obviously, they now allow blind people to serve in the army, since you take me for a waitress. No rum, young man, and if I find out that one of the sentries is drinking on duty, I will tell the governor about it.",
			"Ya_Toje_Hochu_Proval");
		break;

		case "Ya_Toje_Hochu_Proval":
			DialogExit();
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.dialog.filename   = "Common_Soldier.c";
			sld.dialog.currentnode   = "First time";
			CloseQuestHeader("PDM_Proklyataya_Jara");
			pchar.questdata.ProklyatayaJara = 1;
		break;

		case "Ya_Toje_Hochu_4":
			dialog.text = "Of course. I can't go anywhere - I'm on duty... Thank you very much, "+ GetSexPhrase("monsieur", "mademoiselle") +".";
			link.l1 = "I'll be back soon.";
			link.l1.go = "Ya_Toje_Hochu_5";
		break;

		case "Ya_Toje_Hochu_5":
			DialogExit();
			AddQuestRecord("PDM_Proklyataya_Jara", "3");
			pchar.questTemp.PDM_PJ_KR = "KupitRom";
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Ya_Toje_Hochu_5_EsheRaz";
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.City = "FortFrance";
		break;

		case "Ya_Toje_Hochu_5_EsheRaz":
			dialog.text = "Oh, are you back yet, Captain? Where's my rum?";
			link.l1 = "I'm ashamed to say, but I forgot about our little contract. I'll go get him right now.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Ya_Toje_Hochu_5_EsheRaz";
		break;

		case "Prines_Rom_1":
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";
			dialog.text = "Oh, are you back, Captain? And... I'm sorry... but... Have you found any rum?";
			link.l1 = "Here, take it. I think it will strengthen my reputation as the best local liquor supplier for the French army.";
			link.l1.go = "Prines_Rom_2";
		break;

		case "Prines_Rom_2":
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			TakeItemFromCharacter(pchar, "PDM_PJ_Rom");
			dialog.text = "Good joke. And thank you very much for the rum. You're "+ GetSexPhrase("strong man", "pretty girl") + " with a kind heart, not like these arrogant aristocrats. I wish I had such a commander.";
			link.l1 = "Okay, soldier, you better get back to your post. And keep quiet about the rum, otherwise my joke may turn out to be too similar to the truth...";
			link.l1.go = "Prines_Rom_3";
		break;

		case "Prines_Rom_3":
			dialog.text = "As you wish, "+ GetSexPhrase("monsieur", "mademoiselle") +". I'll keep my mouth shut, I promise. Thank you. Have a nice day.";
			link.l1 = "You're welcome. See you later.";
			link.l1.go = "Prines_Rom_4";
		break;

		case "Prines_Rom_4":
			DialogExit();
			CloseQuestHeader("PDM_Proklyataya_Jara");
			pchar.questdata.ProklyatayaJara = 1;
			AddQuestRecord("PDM_Proklyataya_Jara", "5");
			AddCharacterExpToSkill(pchar, "Leadership", 170);
			AddCharacterExpToSkill(pchar, "Commerce", 80);
			
			sld = CharacterFromID("PDM_PJ_Strajnik_1");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "stun_1", "", 1.0);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.City = "FortFrance";
			
			PChar.quest.PDM_PJ_Protrezvel.win_condition.l1 = "ExitFromLocation";
			PChar.quest.PDM_PJ_Protrezvel.win_condition.l1.location = PChar.location;
			PChar.quest.PDM_PJ_Protrezvel.win_condition = "PDM_PJ_Protrezvel";
		break;

	}
}
