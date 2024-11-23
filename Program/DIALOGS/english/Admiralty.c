
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
			DialogExit()
		break;
		
		case "First time":
			dialog.text = "If you are on the issue of trade transportation, payment of duties, or hiring, then you need to go to the right wing of the building. This wing houses the Admiralty, which deals exclusively with ships in His Majesty's service.";
			Link.l1 = "I see. Have a nice day.";
			link.l1.go = "exit";
			if (pchar.questTemp.AnjelikaTichPrologue3 == "ATP3")
			{
				dialog.text = "";
				Link.l1 = "My name is Angelica Remedios, I have an urgent message to the governor. I was informed that he is here now.";
				link.l1.go = "AT_pr_Pochta1";
			}
			if (pchar.questTemp.AnjelikaTichPrologue3_1 == "ATP3_1")
			{
				dialog.text = "Are you lost?";
				Link.l1 = "No. It's okay, I'm leaving now.";
				link.l1.go = "exit";
			}
		break;
		
		//Sinistra Пролог Анжелика Тич
		case "AT_pr_Pochta1":
			dialog.text = "Remedios? You are a relative of the former governor of our La Vega colony.";
			Link.l1 = "Exactly. So is the governor here?";
			link.l1.go = "AT_pr_Pochta2";
		break;
		
		case "AT_pr_Pochta2":
			dialog.text = "Yes, of course. Go through the floor above.";
			Link.l1 = "Thank you.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AnjelikaTichPrologue3");
			pchar.questTemp.AnjelikaTichPrologue3_1 = "ATP3_1";
			
			sld = CharacterFromID("SantoDomingo_Mayor")
			sld.model = "huber_spa";
			sld.greeting = "";
			sld.Dialog.Filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "ATpr_SD_Gubernator_1";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SantoDomingo_Admiralty", "quest", "quest4");
			
			sld = GetCharacter(NPC_GenerateCharacter("ATpr_SD_Off_Guber_1", "off_spa_1", "man", "man", 30, SPAIN, -1, false));
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "SantoDomingo_Admiralty", "quest", "quest8");
			
			sld = GetCharacter(NPC_GenerateCharacter("ATpr_SD_Off_Guber_2", "off_spa_2", "man", "man", 30, SPAIN, -1, false));
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "SantoDomingo_Admiralty", "quest", "quest2");
		break;
		
		case "Strajniki":
			dialog.text = RandPhraseSimple("I'm watching you.", ""+ GetSexPhrase("Senor", "Senorita") +", this is a government institution, stay here according to its status.");
			Link.l1 = RandPhraseSimple("I'll keep it in mind.", "I got it.");
			link.l1.go = "exit";
			NextDiag.TempNode = "Strajniki";
		break;
	}
}
