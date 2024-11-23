
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

		case "First time":
			dialog.text = "What? Who are you? What do you want from me?";
			link.l1 = "Sorry to bother you. Goodbye.";
			link.l1.go = "exit";
			link.l2 = "Take it easy, take it easy. Who are you?";
			link.l2.go = "Next_1";
			LAi_CharacterPlaySound(NPChar, "GR_Kakovi_Merzavczi");
			DeleteAttribute(npchar, "talker");
			UnmarkCharacter(npchar);
		break;

		case "Next_1":
            dialog.text = "My name is Albrecht Zalpfer, but I have no desire to talk to you.";
            link.l1 = "Mmm... I'm sorry, but I don't understand, mister, why don't we talk?";
			link.l1.go = "Next_2";
			link.l2 = "Oh, well, if so, then goodbye.";
			link.l2.go = "exit";
		break;

		case "Next_2":
            dialog.text = "Because I have the intention to leave this island, where all the scoundrels live. I am the voice that cries out in the desert! No one wants to listen to me, no one wants to enter a new era, ya!";
            link.l1 = "Listen, you won't lose anything if you tell me what happened.";
			link.l1.go = "Next_4";
			link.l2 = "What is this new era?";
			link.l2.go = "Next_3";
		break;

		case "Next_3":
            dialog.text = "There will be no new era, no progress, and all because of these thick-headed cretins who don't have enough brains to listen to me, ya. I have to get off this island, and as soon as possible. I hate being here.";
            link.l1 = "Yes, it's a pity. Damn it, no progress-just think! Listen, you won't lose anything if you tell me what happened.";
			link.l1.go = "Next_4";
		break;

		case "Next_4":
			sld = CharacterFromID("Charles_shipyarder");
            dialog.text = "I worked for several years at the shipyard of this scoundrel "+sld.name+". Ah, as an assistant. And then he fired me for asking him for workers in order to implement his latest invention!"+
							"I told him that this invention would open a new era in shipbuilding, that it would be a real revolution, ya! But I was put under lock and key the very minute the governor heard that I was planning a revolution\n"+
							"I was released not so long ago, but no one wants to hire me-and here I am, penniless.";
            link.l1 = "Yes, it looks like you were really misunderstood. So what do you say your discovery is?";
			link.l1.go = "Next_5";
			link.l2 = "I have an idea, mister. If you've worked at a shipyard, you should know a lot about ship building. I'm hiring you as a carpenter, and you're going to get off this island that you don't like so much.";
			link.l2.go = "Next_6";
		break;

		case "Next_5":
			sld = CharacterFromID("Charles_shipyarder");
            dialog.text = "Aha! I suspected it! I assumed that you were one of the spies of my former shipwright master "+sld.name+". Ah! I won't say another word! First, you put me in jail, and then you want to steal my invention? You're all just scoundrels! Scoundrels, ya! I won't talk to you!";
            link.l1 = "Uh, buddy, I've had to steal before, especially ships - but ideas? Never! And what should I do with your inventions-I don't know anything about shipbuilding. I just wanted to know...";
			link.l1.go = "Next_7";
		break;

		case "Next_6":
            dialog.text = "CARPENTER? What do I hear, "+ GetSexPhrase("Herr kapitan", "fraulein") +"? Do you want to hire me, the most outstanding inventor of our century, as a pathetic ship craftsman? You're in yours... although... I agree! I loathe this miserable English island! Perfectly! I'll just pack my things, and that's all they saw! I'm ready, "+ GetSexPhrase("herr", "fraulein") +"! Where is your ship?";
            link.l1 = "In the harbor, of course, Mr. Zalpfer. I hope that you will not change your mind, and will be on board by the time you set sail.";
			link.l1.go = "Next_8";
		break;

		case "Next_7":
			sld = CharacterFromID("Charles_shipyarder");
            dialog.text = "Never! You are just "+ GetSexPhrase("deceiver", "deceiver") +", "+ GetSexPhrase("crook", "thief") +"just like your master "+sld.name+", ya! When I was released from prison, I went to this scoundrel and demanded to return my drawings. But he just laughed at me and said he burned them. Ha! But I know, I know that he took them for himself, ya, and now he wants to find out the very essence of this invention - well, no! Let him break his head! I won't talk to you anymore!";
            link.l1 = "I'm sorry, Mr. Inventor, but you should think about the design of your head. There's definitely something missing in it. Have a nice day.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Next_9";
		break;

		case "Next_9":
            dialog.text = "Ha! It's you! You are a spy! You want to steal the secret of my ingenious invention - I won't tell you anything!";
			link.l1 = "I have an idea, Mr. If you've worked at the shipyard, you should know better than that. I'm hiring you as a carpenter, and you're getting off this island that you don't like so much.";
			link.l1.go = "Next_6";
            link.l2 = "Uh, take it easy, take it easy. I didn't really want to talk to you. Have a nice day.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Next_9";
		break;

		case "Next_8":
            dialog.text = "But know this, I'm going to leave your ship as soon as we reach Port Royal. I have heard that the governor there is an understanding person and is able to appreciate the genius of my invention.";
            link.l1 = "Undoubtedly, Mr. Zalpfer, and now proceed to my ship.";
			link.l1.go = "Cod_1"
			if (pchar.rank >= 1 && pchar.rank <= 4)
			{
				pchar.questTemp.PDM_AZ_6rang = true;
			}
		break;

		case "Cod_1":
			SetQuestHeader("ColonyBuilding");
			AddQuestRecord("ColonyBuilding", "0.1");
			AddQuestUserData("ColonyBuilding", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ColonyBuilding", "sSex1", GetSexPhrase("xia", "as"));
			sld = CharacterFromID("Albreht_Zalpfer");
			SetCharacterRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			LAi_RemoveLoginTime(sld);
			sld.loyality = MAX_LOYALITY;
			sld.Payment = true;
			sld.quest.OfficerPrice = sti(pchar.rank)*10;
			sld.OfficerWantToGo.DontGo = true;
			sld.rank = 4;
			SetSelfSkill(sld, 5, 40, 5, 5, 5);
			SetShipSkill(sld, 5, 5, 5, 5, 5, 35, 5, 5, 5);
			Pchar.quest.PDM_Albreht_Vhod.win_condition.l1           = "location";
        	Pchar.quest.PDM_Albreht_Vhod.win_condition.l1.location  = "PortRoyal_town";
        	Pchar.quest.PDM_Albreht_Vhod.win_condition              = "PDM_Albreht_Vhod";
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			//sld.dialog.filename = "Quest\PDM\Albreht_Zalpfer.c";
			//sld.dialog.currentnode = "Pl_1";
			DialogExit();
		break;

		/*case "Pl_1":
            dialog.text = "I'm going to leave your ship as soon as we reach Port Royal. I have heard that the governor there is an understanding man and is able to appreciate the genius of my invention.";
            link.l1 = "Yes, Mr. Zalpfer, I remember.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pl_1";
		break;*/

		case "Ja_1":
			sld = CharacterFromID("Charles_shipyarder");
            dialog.text = "Thank you, "+ GetSexPhrase("herr", "fraulein") +" "+pchar.name+". You have given me a chance to escape from this center of intrigue, and I am very grateful to you\n"+
							"As a pledge of my gratitude, I ask you to accept from me these drawings that reveal the essence of my invention. In the event that news of my death reaches you, or if this scoundrel "+sld.name+" he will try to appropriate the right of the discoverer, I want these papers to remain only with you, ya. Any person who knows a little bit about mechanics will figure out what is there It's written.";
            link.l1 = "Thank you, Albrecht, I am "+ GetSexPhrase("I was glad", "I was glad") +" to help you. Goodbye.";
			link.l1.go = "Finish";
			AddQuestRecord("ColonyBuilding", "0.2");
			RemovePassenger(pchar, NPChar);
			RemoveCharacterCompanion(pchar, NPChar);
			NextDiag.TempNode = "Ja_2";
		break;

		case "Ja_2":
            dialog.text = "Oh! I can't believe, "+ GetSexPhrase("Herr kapitan", "fraulein") +" how stupid they all are! They just couldn't figure out how brilliant I am, can you imagine? I should go to London, to the Royal Society of Science! Or to the Paris Academy! Only there are people who can appreciate my brain. Ya, I should sail to England. Take me to England. Immediately...";
            link.l1 = "I'm sorry, Albrecht, but I'm not right now"+ GetSexPhrase("intend", "intend") +" sail to Europe. I have a lot of unfinished business here.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Ja_2";
		break;

		case "Finish":
			Log_info("Drawings received from Albrecht Zalpfer.");
			PlaySound("Interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.PDM_AZ_6rang"))
			{
				GiveItem2Character(PChar, "Ship_Print_6");
			}
			else
			{
				GiveItem2Character(PChar, "Ship_Print_5");
			}
			DeleteAttribute(pchar, "questTemp.PDM_AZ_6rang");
			AddCharacterExpToSkill(pchar, "Sailing", 130);
			ChangeCharacterReputation(pchar, 3);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
