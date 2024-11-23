
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
			dialog.text = "Have you seen my ring, "+ GetSexPhrase("monsieur", "mademoiselle") +"?";
			link.l1 = "Excuse me, madam?";
			link.l1.go = "Starshka_1";
			PlayVoice("Kopcapkz\Voices\PDM\Old Woman.wav");
		break;

		case "Starshka_1":
			dialog.text = "I lost the ring... Have you seen him?";
			link.l1 = "I'm not quite sure... What kind of ring was that?";
			link.l1.go = "Starshka_2";
			link.l2 = "No, I didn't see it. Goodbye.";
			link.l2.go = "exit";
		break;

		case "Starshka_2":
			dialog.text = "Oh, "+ GetSexPhrase("monsieur", "mademoiselle") +", it was a very valuable ring... it was very expensive... I'm so sorry that I lost him...";
			link.l1 = "Expensive, you say? Was there a jewel in it or something?";
			link.l1.go = "Starshka_3";
		break;

		case "Starshka_3":
			dialog.text = "Ha ha ha!!! Of course! There was a stone! A diamond! Yes, it was a diamond. Or maybe a ruby... No, no, no-it was an emerald... That's right, an emerald on a gold ring... or it was topaz... Ha ha ha!";
			link.l1 = "Madam, I will not be able to find your ring without an accurate description... Have a nice day.";
			link.l1.go = "Starshka_4";
			NextDiag.TempNode = "Starshka_5";
			DeleteAttribute(npchar, "talker");
		break;

		case "Starshka_4":
			SetQuestHeader("PDM_Poteryanoe_Koltso");
			AddQuestRecord("PDM_Poteryanoe_Koltso", "1");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "a"));

			pchar.questTemp.PDM_PK_UznatLichnost = "UznatLichnost";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Starshka_5":
			dialog.text = "Have you seen my ring, "+ GetSexPhrase("monsieur", "mademoiselle") +"?";
			link.l1 = "Oh, no, madam. I haven't found it yet.";
			link.l1.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\Old Woman.wav");
		break;

		case "Francheska":
			dialog.text = "Hey, "+ GetSexPhrase("sailor", "girl") +", I'm Francesca. Do you want me to leave with you, and you can tell me about your travels and great exploits? (smiling) And show me...";
			link.l1 = "Hmmm... I would. But I think you'll tell me about your ring first.";
			link.l1.go = "SrazuProKoltso";
			link.l2 = "Yes, I can tell you a lot about my adventures. I think you'll like my story, Francesca. There is a woman living in one colony. She lost her son quite a long time ago...";
			link.l2.go = "Istoria";
			PlayVoice("Kopcapkz\Voices\PDM\Francesca.wav");
			pchar.questTemp.PDM_PK_UvestiNaVerh = true;
		break;

		case "SrazuProKoltso":
			dialog.text = "Which ring? I don't have any rings! Go away, go away!";
			link.l1 = "Understand, I need this ring for a poor woman.";
			link.l1.go = "Otstan";
			link.l2 = "Give me the ring, or I'll decorate your pretty face with my knife!";
			link.l2.go = "Krik";
			NextDiag.TempNode = "Uhodi";
		break;
		
		case "Otstan":
			dialog.text = "Do you want my ring? Go away, go away!";
			link.l1 = "Okay, I'll go to your mistress.";
			link.l1.go = "exit";
		break;

		case "Krik":
			dialog.text = "Aaaaaaaaaaaa!!!! (terrible scream)";
			link.l1 = "Enough! Enough! The guards will come running now... Okay, I'll go to your mistress.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
		break;

		case "Uhodi":
			dialog.text = "Do you want my ring? I don't have any rings! Go away, go away!";
			link.l1 = "Okay, I'll go to your mistress.";
			link.l1.go = "exit";
		break;

		case "Istoria":
			dialog.text = "This is a sad story! I don't like sad stories, "+ GetSexPhrase("honey", "honey") +". You'd better tell me something funny!";
			link.l1 = "No, Francesca, I'll finish this one first. That woman, as I said, lost her son, and when the news of his death came, she went crazy. She gave her boy a keepsake present. And so, in her madness, she imagined that she had lost this talisman... Just a talisman, not a son. I'd like to give it back to her. I think she is suffering unimaginably...";
			link.l1.go = "Istoria_2";
		break;

		case "Istoria_2":
			dialog.text = "(sob) She reminds me of my mom! My mom always confused me with the girl next door-her name was Francesca too (sob). What were we talking about? Ah, a magical thing! The talisman! What kind of talisman was that?";
			link.l1 = "It was a ring. You know, rings are often used as talismans.";
			link.l1.go = "Istoria_3";
		break;

		case "Istoria_3":
			dialog.text = "Oh! Look, I have a ring too. Maybe it's MAGICAL? A kind, good man gave it to me. Here. Tell me, is this a MAGIC ring?";
			link.l1 = "Oh my God! Unbelievable! This is the MAGIC ring that the woman lost! If you return this ring to me, I'll take it to the woman.";
			link.l1.go = "Volshebnoe";
			link.l2 = "No, no, of course not, Francesca. It is clear to everyone that this is a very ORDINARY ring. If you return this ring to me, I'll take it to the woman.";
			link.l2.go = "Obichnoe";
		break;

		case "Obichnoe":
			dialog.text = "I don't want a dead man's ring, especially since it's not MAGIC. Here, take it.";
			link.l1 = "Thank you. You're a very nice girl, Francesca! I promise you that one day I will come back and tell you a long story about my adventures. Now I have to go.";
			link.l1.go = "Pomenyt";
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Sneak", 250);
			ChangeCharacterReputation(pchar, 5);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;

			DeleteAttribute(pchar, "questTemp.PDM_PK_UvestiNaVerh");
			GiveItem2Character(PChar, "PDM_PK_Koltso");
			AddQuestRecord("PDM_Poteryanoe_Koltso", "4");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "a"));
		break;

		case "Volshebnoe":
			dialog.text = "Is that a ring? But this is a MAGIC ring! How can I give it to you?";
			link.l1 = "I just want to return it to the real owner. Think about it, will a ring taken from a dead person bring you happiness?";
			link.l1.go = "Kupit";
		break;

		case "Kupit":
			dialog.text = "Twenty thousand million! And no less, for the MAGIC ring! The ring is MAGICAL! You said it yourself! Then it should cost a lot! Very much!";
			link.l1 = "Here. (give her twenty)";
			link.l1.go = "Kupit_20";
			link.l2 = "Here. (give her twenty thousand)";
			link.l2.go = "Kupit_20000";
			link.l3 = "Here. (give her twenty million)";
			link.l3.go = "Kupit_20000000";
			link.l4 = "You know, I changed my mind...";
			link.l4.go = "exit";
			NextDiag.TempNode = "Popitka_Vtoraya";
		break;

		case "Kupit_20":
			dialog.text = "Twenty thousand million! I have twenty thousand million!!! Here, take the ring.";
			link.l1 = "Thank you. I am sure that now you will be able to buy the governor's palace. Goodbye.";
			link.l1.go = "Pomenyt";
			AddMoneyToCharacter(pchar, -20);
			NextDiag.TempNode = "UNasKoltso";

			DeleteAttribute(pchar, "questTemp.PDM_PK_UvestiNaVerh");
			GiveItem2Character(PChar, "PDM_PK_Koltso");
			AddQuestRecord("PDM_Poteryanoe_Koltso", "4");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "a"));
		break;

		case "Kupit_20000":
			if (sti(pchar.Money) >= 20000)
			{
				dialog.text = "It's only a thousand! You want to trick me!!! Aaaaaaaaaaaa!!!! (terrible scream)";
				link.l1 = "Enough! Enough! The guards are coming now... Okay, I'm leaving.";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				dialog.text = "";
				link.l1 = "Listen, I don't have enough money with me right now - but I'll bring it to you later...";
				link.l1.go = "exit";
			}
		break;

		case "Kupit_20000000":
			if (sti(pchar.Money) >= 20000000)
			{
				dialog.text = "It's only a million! You want to trick me!!! Aaaaaaaaaaaa!!!! (terrible scream)";
				link.l1 = "Enough! Enough! The guards are coming now... Okay, I'm leaving.";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				dialog.text = "";
				link.l1 = "Listen, I don't have enough money with me right now - but I'll bring it to you later...";
				link.l1.go = "exit";
			}
		break;

		case "Popitka_Vtoraya":
			dialog.text = "Oh, it's you. Will you tell me a story?";
			link.l1 = "No. I'm going to get the ring.";
			link.l1.go = "Popitka_Vtoraya_2";
		break;

		case "Popitka_Vtoraya_2":
			dialog.text = "Did you bring twenty thousand million for a MAGIC ring?";
			link.l1 = "Here. (give her twenty)";
			link.l1.go = "Kupit_20";
			link.l2 = "Here. (give her twenty thousand)";
			link.l2.go = "Kupit_20000";
			link.l3 = "Here. (give her twenty million)";
			link.l3.go = "Kupit_20000000";
			link.l4 = "You know, I changed my mind...";
			link.l4.go = "exit";
		break;

		case "UNasKoltso":
			dialog.text = "Hey, sailor! I have twenty thousand million! Do you know where I got them from?";
			link.l1 = "Of course! I gave them to you.";
			link.l1.go = "UNasKoltso_2";
			link.l2 = "I'm not interested in this question.";
			link.l2.go = "UNasKoltso_3";
		break;

		case "UNasKoltso_2":
			dialog.text = "Yes, it was you! Now I'm going to buy the governor's palace! And I invite you to visit!";
			link.l1 = "Thank you, Francesca, I very happy for you.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;

		case "UNasKoltso_3":
			dialog.text = "Then leave! I'm not going to tell you what I did with my twenty thousand million!";
			link.l1 = "See you later, Francesca.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;

		case "Pomenyt":
			sld = CharacterFromID("Josephine_Lodet");
			sld.dialog.currentnode   = "Konets";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NaVerhuSFrancheska":
			dialog.text = "Come on in, don't be shy, make yourself at home for the next two hours.";
			link.l1 = "No, Francesca, you can't leave here alive.";
			link.l1.go = "UbitEE";
			link.l2 = "Come to me, my fish.";
			link.l2.go = "TrahEE";
			PlayVoice("Kopcapkz\Voices\PDM\Francesca.wav");
			npchar.lifeday = 0;
		break;

		case "TrahEE":
			AddDialogExitQuest("PlaySex_1");
			GiveItem2Character(pchar, "PDM_PK_Koltso");
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("Josephine_Lodet");
			sld.dialog.currentnode   = "Konets";
			sld = CharacterFromID("PDM_PK_Francheska");
			sld.dialog.currentnode   = "PosleTraha";

			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterHealth(pchar, 10);

			AddQuestRecord("PDM_Poteryanoe_Koltso", "5");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "a"));
			DialogExit();
		break;

		case "PosleTraha":
			dialog.text = "I don't want to let you go, "+ GetSexPhrase("mine", "mine") +" "+ GetSexPhrase("knight", "valkyrie") +".";
			link.l1 = "Goodbye, Francesca.";
			link.l1.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\Francesca.wav");
			LAi_CharacterDisableDialog(npchar);
		break;

		case "UbitEE":
			LAi_LocationFightDisable(loadedLocation, false);
			Lai_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);

			sld = CharacterFromID("PDM_PK_Francheska");
			LAi_SetHP(sld, 20.0, 20.0);
			LAi_SetImmortal(sld, false);
			sld.SaveItemsForDead = true
			RemoveAllCharacterItems(sld, true);
			GiveItem2Character(sld, "PDM_PK_Koltso");
			LAi_SetActorType(sld); 
			LAi_ActorAnimation(sld, "afraid", "", 4.5);

			PChar.quest.PDM_PK_Ubita.win_condition.l1 = "item";
			PChar.quest.PDM_PK_Ubita.win_condition.l1.item = "PDM_PK_Koltso";
			PChar.quest.PDM_PK_Ubita.win_condition = "PDM_PK_Ubita";

			DialogExit();
		break;

		case "Konets":
			dialog.text = "Have you seen my ring, "+ GetSexPhrase("monsieur", "mademoiselle") +"? I lost my ring. It must be here somewhere. I'm so embarrassed, I can hardly remember... Sometimes I feel like I've lost something else... Something that I forgot...";
			link.l1 = "Yes, I know what you've lost. I accept"+ GetSexPhrase("eu", "if") +"you have your ring, madam. It was removed from the body of your son, who died during the battle at the walls of Santo Domingo. Here, take your ring.";
			link.l1.go = "Konets_2";

			PlayVoice("Kopcapkz\Voices\PDM\Josephine Lodet.wav");
		break;

		case "Konets_2":
			TakeItemFromCharacter(pchar, "PDM_PK_Koltso");
			dialog.text = "My ring... I remember this ring... I gave it to someone who had to return it. He had to come back... My Jacques... oh...";
			link.l1 = "Life does not end, madam. I think you need to find your relatives, I'm sure that they miss you very much.";
			link.l1.go = "Konets_3";
		break;
		
		case "Konets_3":
			dialog.text = "Wait, wait, "+ GetSexPhrase("monsieur", "mademoiselle") +". There's something coming to you as a reward. Keep five thousand coins and ten diamonds. They're yours now.";
			link.l1 = "Thank you very much, madam. Goodbye.";
			link.l1.go = "Nagrada";
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(PChar, "jewelry2", 10);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterReputation(pchar, 2);
		break;

		case "Nagrada":
			AddQuestRecord("PDM_Poteryanoe_Koltso", "6");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("PDM_Poteryanoe_Koltso");
			pchar.questdata.KoltsoLodet = 1;
			sld = CharacterFromID("Josephine_Lodet");
			sld.dialog.filename   = "Common_citizen.c";
			sld.dialog.currentnode = "First Time";

			DialogExit();
		break;
	}
}
