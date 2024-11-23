#include "DIALOGS\english\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	int license_price = sti(PChar.rank) * (2500) * (0.01 * (120 - GetSummonSkillFromName(PChar, SKILL_COMMERCE)));;
	int license_expires = rand(2);

	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;

	int i, cn, iOfficer;
	ref chref, compref;
	ref rRealShip;
	string attrL, sTitle, sCapitainId, s1;
	string sColony;
	string offtype = "";

	String sLastSpeakDate = LastSpeakDate();

	bool ok, ok2;
	int iTest = FindColony(NPChar.City); // город магазина
	ref rColony;

	attrL = Dialog.CurrentNode;

	if(HasSubStr(attrL, "OfficerStockManBack_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.OfficerToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "OfficerStockManBack";
	}

	if(HasSubStr(attrL, "OfficerStockSel_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.OfficerToStoreIdx = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "OfficerStock_2";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "First time":
			NextDiag.TempNode = "First time";
			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Greetings, " + GetAddress_Form(NPChar) + ". We don't seem to know each other. I am "  + GetFullName(npchar)+ " - the Governor of the Chapter of the Spanish Invasion of the Caribbean Islands.";
				Link.l1 = "Hello, " + GetFullName(NPChar) + ". I am " + GetFullName(PChar) + ", captain of the ship '" + PChar.ship.name + "'.";
			}
			else
			{
				dialog.text = LinkRandPhrase("Greetings, " + GetAddress_Form(NPChar) + ". Are you here on business?",
									"Hello, " + GetFullName(Pchar) + ". I've been informed of your arrival.",
									"Ah, Captain " + GetFullName(Pchar) + ". What brings you to me?");
				Link.l1 = "Hello, " + GetFullName(NPChar) + ". I want to talk to you.";
			}
			if (NPChar.id == "Wh_Jim")
			{
				dialog.text = "Captain! It's good to see you again. What did you come with today?";
				Link.l1 = "Hello, " + npchar.name + ". There's something we need to discuss.";

			}
			Link.l1.go = "node_2";
		break;
		case "node_2":
			// Церковный генератор 1

			dialog.text = "That's fine. I am at your service, " + GetFullName(PChar) + ".";

			Link.l3 = "I want to leave an officer here for training.";
			Link.l3.go = "ShipStock_1";

			if (sti(NPChar.Portman) > 0)
			{
				Link.l4 = "I want to take my officer back.";
				Link.l4.go = "OfficerStockReturn_1";
			}

			Link.l15 = "Thank you. Goodbye.";
			Link.l15.go = "exit";
		break;
		case "again":
			dialog.text = "Something else?";

			Link.l3 = "I want to leave an officer here for training.";
			Link.l3.go = "ShipStock_1";

			if (sti(NPChar.Portman) > 0)
			{
				Link.l4 = "I want to take my officer back.";
				Link.l4.go = "OfficerStockReturn_1";
			}

			Link.l15 = "Nothing else. Goodbye.";
			Link.l15.go = "exit";
		break;

		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
			dialog.text = "Who exactly do you want to leave?";
			for(i=0; i<GetPassengersQuantity(pchar); i++)
			{
				iOfficer = GetPassenger(pchar, i);
				sld = GetCharacter(iOfficer);
				if (CheckAttribute(sld, "prisoned") && (sld.prisoned == true)) continue;
				if (!GetRemovable(sld)) continue;
				attrL = "l"+i;
				Link.(attrL)	= "Officer " + GetFullName(sld) + ".";
				Link.(attrL).go = "OfficerStockSel_" + i;
			}
			Link.l99 = "Thanks, no need.";
			Link.l99.go = "exit";
		break;

		case "OfficerStock_2":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));

			if (!CheckAttribute(chref, "quest.officertype")) offtype = "Universal";
			else offtype = XI_ConvertString(chref.quest.officertype);
			dialog.Text = "You have chosen " + GetFullName(chref)+", specialization is "+offtype+".";
			Link.l1 = "Yeah. That's fine with me.";
			Link.l1.go = "OfficerStock_3";
			Link.l99 = "No, I changed my mind.";
			Link.l99.go = "exit";
		break;

		case "OfficerStock_3":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));
			chref.OfficerInStockMan = NPChar.id;
			// Warship 22.03.09 fix Не перенеслось с КВЛ 1.2.3
			chref.OfficerInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "OfficerInStockMan.Date"); // для расчёта
			RemovePassenger(pchar, chref);

			chref.location = "";
			chref.location.group = "";
			chref.location.locator = "";
			NPChar.Portman	= sti(NPChar.Portman) + 1;
			pchar.OfficerInStock = sti(pchar.OfficerInStock) + 1;//разобраться - что это. не могу найти, где оно используется.

			dialog.text = "Okay. You can pick it up when you need it.";
			Link.l1 = "Thank you.";
			Link.l1.go = "again";
		break;

		case "OfficerStockReturn_1":
			dialog.text = "Who exactly are you picking up?";
			cn = 1;
			for(i=1; i<MAX_CHARACTERS; i++)
			{
				makeref(chref, Characters[i]);
				if (CheckAttribute(chref, "OfficerInStockMan"))
				{
					if (chref.OfficerInStockMan == NPChar.id)
					{
						attrL = "l"+cn;
						if (!CheckAttribute(chref, "quest.officertype")) offtype = "Universal";
						else offtype = XI_ConvertString(chref.quest.officertype);
						Link.(attrL)	= "Officer " + GetFullName(chref) + ", specialization - "+offtype+".";
						Link.(attrL).go = "OfficerStockManBack_" + i;
						cn++;
					}
				}
			}

			Link.l99 = "No, I changed my mind.";
			Link.l99.go = "exit";
		break;
	  	case "OfficerStockManBack":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));
			dialog.Text = "Are you taking the officer " + GetFullName(chref)+"?";
			Link.l1 = "Yes.";
			Link.l1.go = "OfficerStockManBack2";
			Link.l2 = "No, I changed my mind.";
			Link.l2.go = "exit";
		break;

		case "OfficerStockManBack2":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));
			dialog.text = GetFullName(chref)+" was sent to your ship, Captain.";
			Link.l1 = "Thank you.";
			Link.l1.go = "again";
			DeleteAttribute(chref, "OfficerInStockMan");
			AddPassenger(pchar, chref, false);

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.OfficerInStock = sti(pchar.OfficerInStock) - 1;

		break;

	}
}

void DelBakSkill(ref _compref)
{
	DelBakSkillAttr(pchar);
	ClearCharacterExpRate(pchar);
	RefreshCharacterSkillExpRate(pchar);
	SetEnergyToCharacter(pchar);

	DelBakSkillAttr(_compref);
	ClearCharacterExpRate(_compref);
	RefreshCharacterSkillExpRate(_compref);
	SetEnergyToCharacter(_compref);
}
