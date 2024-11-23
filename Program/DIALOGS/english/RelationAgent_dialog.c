#define DIPLOMAT_SUM 80000

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iSumm = 0;
	string s1;

	if (!CheckAttribute(npchar, "PatentPrice"))
    {
		if (IsCharacterPerkOn(pchar, "Adventurer")) npchar.PatentPrice = (6000 + rand(4) * 500);
        else npchar.PatentPrice = (8000 + rand(6) * 1000);
    }
    int i;
    string attrLoc;
	ref    sld;

    attrLoc   = Dialog.CurrentNode;

    if (findsubstr(attrLoc, "SetNationPatent_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.nation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "patent_2";
 	}

 	if (findsubstr(attrLoc, "SetNationLicence_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType";
 	}

 	if (findsubstr(attrLoc, "NationLicenceType_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceType = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType2";
 	}

 	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
        npchar.quest.relation      = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
		    Dialog.CurrentNode = "RelationYet";
		}
		else
		{
 	    	Dialog.CurrentNode = "RelationAny_Done";
 	    	npchar.quest.relation.summ = CalculateRelationSum(sti(npchar.quest.relation)) * MOD_SKILL_ENEMY_RATE*3;
 	    }
 	}

 	if (findsubstr(attrLoc, "CityPay_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "CityInfo";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = "Glad to see you again.";
			link.l1 = "I need your services again.";
			link.l1.go = "relation";
			link.l2 = "I'm already leaving.";
			link.l2.go = "exit";
			//линейка ГПК, поиски торгашей -->
			if (pchar.questTemp.LSC == "toLicencer")
			{
				link.l3 = "I have a question for you about the Dutch West India Company.";
				link.l3.go = "SeekHVIC";
			}
			if (pchar.questTemp.LSC == "toLicencer_2")
			{
				link.l3 = "Hmm, I apologize for my leaky head. I'm talking about the Dutch West India Company again.";
				link.l3.go = "SeekHVIC_3";
			}
			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))
			{
				link.l4 = "I want to offer a deal."
				link.l4.go = "D_ShipLetters_1";
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}
			//<-- линейка ГПК, поиски торгашей
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Let me introduce myself, I am the person who can put in a good word for you to this or that governor. For a fee, of course, but believe me, my services are of the highest quality, and you will not regret using my talents.";
				if (CheckAttribute(pchar, "Whisper.BuyDocuments"))
				{
					link.l1 = "I was told that I would be able to apply for citizenship in one of the nations from you.";
					link.l1.go = "WhisperDocuments";
					break;
				}
				link.l1 = "Very interesting, go on.";
				link.l1.go = "relation";
				link.l2 = "Maybe another time.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}

			NextDiag.TempNode = "First time";
		break;

		//*************************** Линейка Виспер **************
		case "WhisperDocuments":
			dialog.text = "All right. This service will cost you 1000 coins. Whose citizenship would you like to get?";
			DeleteAttribute(Pchar, "perks.list.FlagSpa");
			DeleteAttribute(Pchar, "Whisper.BuyDocuments");
			if(makeint(Pchar.money) >= 1000)
            {
				link.l1 = "England.";
				link.l1.go = "WhisperEng";
				link.l2 = "France.";
				link.l2.go = "WhisperFra";
				link.l3 = "Holland.";
				link.l3.go = "WhisperHol";
			}
			link.l4 = "You know, I'd rather become a free corsair.";
			link.l4.go = "Whisper_exit";
		break;

		case "WhisperEng":
			dialog.text = "Okay. It remains to sign here and you are officially an English citizen.";
			Pchar.BaseNation = ENGLAND;
			SetCharacterPerk(Pchar, "FlagEng");
			AddMoneyToCharacter(pchar, -1000);
			Flag_Change(ENGLAND);
			link.l1 = "Done.";
			link.l1.go = "Whisper_exit";
		break;
		case "WhisperFra":
			dialog.text = "Okay. It remains to sign here and you are officially a French citizen.";
			Pchar.BaseNation = FRANCE;
			SetCharacterPerk(Pchar, "FlagFra");
			AddMoneyToCharacter(pchar, -1000);
			Flag_Change(FRANCE);
			link.l1 = "Done.";
			link.l1.go = "Whisper_exit";
		break;
		case "WhisperHol":
			dialog.text = "Okay. It remains to sign here and you are officially a Dutch citizen.";
			AddMoneyToCharacter(pchar, -1000);
			Pchar.BaseNation = HOLLAND;
			SetCharacterPerk(pchar, "FlagHol");
			Flag_Change(HOLLAND);
			link.l1 = "Done.";
			link.l1.go = "Whisper_exit";
		break;
		case "Whisper_exit":
			dialog.text = "Here are your papers, do not lose. Blow a little on the ink to dry, or it will smear\nAll the best.";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == PIRATE)
			{
				dialog.text = "In that case, please don't distract me.";
				Pchar.BaseNation = PIRATE;
				Flag_Change(PIRATE);
			}
			PChar.quest.WhisperPirateTownGetHat.win_condition.l1 = "location";
			PChar.quest.WhisperPirateTownGetHat.win_condition.l1.location = "PuertoPrincipe_town";
			PChar.quest.WhisperPirateTownGetHat.function = "WhisperPirateTownGetHat";
			PChar.quest.WhisperPirateTownBattle.win_condition.l1 = "location";
			PChar.quest.WhisperPirateTownBattle.win_condition.l1.location = "PuertoPrincipe_ExitTown";
			PChar.quest.WhisperPirateTownBattle.function = "WhisperPirateTownBattle";
			SetLocationCapturedState("PuertoPrincipe_town", true);
		break;
		//*************************** Генератор - "Found ship's documents" **************
		case "D_ShipLetters_1":
			dialog.text = "State the terms.";
			s1 = "By a happy coincidence, I turned out to have an absolutely legal package of ship's documents that have not yet been put on the wanted list.";
			s1 = s1 + "The ship is afloat and has not been excluded from the register, do not worry. It's just that the owner has managed to lose these papers...";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Let's take a look! Indeed, the marks are quite fresh. Well, luck favors you, "+ GetSexPhrase("sir","madam") +"! ";
			s1 = s1 + "I just needed just such a set, and I, in turn, offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + ". What do you say?";
			dialog.text = s1;
			link.l1 = "Truly royal generosity! Of course I am "+ GetSexPhrase("I agree","I agree") +"!";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "Probably not.";
			link.l2.go = "exit";
		break;
		case "D_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5));
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "9");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "relation":
			dialog.text = "Let's see how I can help you.";
            //#20200219-01
			int charNat = sti(pchar.nation);
			bool bCheck = false;
            if(GetNationRelation2MainCharacter(ENGLAND) > GetNationRelation(charNat, ENGLAND))
                bCheck = true;
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 || bCheck)
			{
				link.l3 = "I want to make peace with England.";
				link.l3.go = "RelationTo_0";
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 || bCheck)
			{
				link.l1 = "I want to make peace with France.";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 || bCheck)
			{
				link.l2 = "I want to make peace with Spain.";
				link.l2.go = "RelationTo_2";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 || bCheck)
			{
				link.l4 = "I want to make peace with Holland.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "I want to make peace with the smugglers.";
				Link.l5.go = "Contraband";
            }
			
            Link.l8 = "I need a patent.";
			Link.l8.go = "patent_0";

			Link.l9 = "Do you have trading licenses?";
			Link.l9.go = "Licence";

			if (isHeroOwnCity(true))
			{
				Link.l10 = "I have a question related to the affiliation of settlements.";
				Link.l10.go = "City_Buy";
			}

			Link.l11 = "I had a fight with one corsair and I want to improve our relationship. Can you arrange that?";
			Link.l11.go = "PGG_peace";

			link.l99 = "You know, I think I'll manage on my own.";
			link.l99.go = "exit";
		break;

		case "PGG_peace":
			dialog.text = "Which person are we talking about?";
			for(i=1; i<=PsHeroQty; i++)
			{
				sld = CharacterFromID("PsHero_"+i);
				if (PGG_ChangeRelation2MainCharacter(sld, 0) < 41 && !LAi_IsDead(sld) && sld.PGGAi.location != "Dead" && !IsCompanion(sld) && !IsOfficer(sld))
				{
					string attr = sld.ID;
					string linkPGG = "l" + i;
					NPChar.Temp.(attr) = attr;
					Link.(linkPGG) = GetFullName(sld);
					Link.(linkPGG).go = "PGG_make_peace_with_" + attr;
				}
				else
				{
					NPChar.Temp.(attr) = "";
				}
			}
			link.lexit = "Never mind.";
			link.lexit.go = "exit";
		break;

		int nFind = findSubStr(Dialog.CurrentNode, "PGG_make_peace_with_", 0);
		string idxVal;
		string nodName;
		if(nFind == 0)
		{
            npchar.PGGSelected = strcut(Dialog.CurrentNode, 20, strlen(Dialog.CurrentNode)-1);
			sld = CharacterFromID(npchar.PGGSelected);
			npchar.PGGPeaceMoney = ((sti(sld.rank) + sti(pchar.rank))/4 + (60 - PGG_ChangeRelation2MainCharacter(sld, 0))) * 1000;
			dialog.Text = "Yes, I heard that " + GetFullName(CharacterFromID(npchar.PGGSelected)) +" wishes you death with all " + NPCharSexPhrase(sld, "his","her") + " soul. I think I could find a suitable gift for " + NPCharSexPhrase(sld, "him","her") + " to make treat you more favorably. But this service will cost you "+ npchar.PGGPeaceMoney +" piastres.";
			if (sti(pchar.money) >= sti(npchar.PGGPeaceMoney))
			{

				Link.l1 ="I agree, get started.";
				Link.l1.go = "PGG_peace_made";
			}
			Link.l2 = "I changed my mind, I'm sorry.";
            Link.l2.go = "exit";
            break;
        }

		case "PGG_peace_made":
			sld = CharacterFromID(npchar.PGGSelected);
			int addPGGrelation = 60 - PGG_ChangeRelation2MainCharacter(sld, 0);
			PGG_ChangeRelation2MainCharacter(sld, addPGGrelation);
			addMoneyToCharacter(pchar, -sti(npchar.PGGPeaceMoney));

			if (CheckAttribute(sld, "PGGAi.Task.SetSail"))
			{
				PGG_Disband_Fleet(sld);
				sld.PGGAi.location.town = PGG_FindRandomTownByNation(sti(sld.nation));
			}

			dialog.Text = "Consider that everything has already been settled. Any hunt that "+ GetFullName(sld) +" could lead on you should stop soon."
			Link.l1 ="I hope you're right.";
			Link.l1.go = "exit";
		break;

		case "Licence":
			dialog.text = "Always available, for varying periods. What kind of trading license are you interested in?";
		    link.l1 = "England";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "France";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "Spain";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "Holland";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "You know, I think I'll manage on my own.";
			link.l9.go = "exit";
		break;

		case "NationLicenceType":
        	dialog.text = "For how long?";
		    link.l1 = "10 days";
			link.l1.go = "NationLicenceType_10";
		    link.l2 = "20 days";
			link.l2.go = "NationLicenceType_20";
		    link.l3 = "30 days";
			link.l3.go = "NationLicenceType_30";
			link.l9 = "I changed my mind.";
			link.l9.go = "exit";
		break;

		case "NationLicenceType2":
			if (IsCharacterPerkOn(pchar, "Agent")) iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE*3 * 500 + 200000 + (sti(PChar.rank)*1000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
			else iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE*3 * 1000 + 300000 + (sti(PChar.rank)*2000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
        	dialog.text = "So, license " + XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name + "Gen") + " on " + sti(npchar.LicenceType) + " days, costs " + FindRussianMoneyString(iSumm) + ".";
		    link.l1 = "Suits me.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "I changed my mind.";
			link.l9.go = "exit";
		break;

		case "NationLicenceType3":
            //iSumm = sti(npchar.LicenceType) * (2000 * MOD_SKILL_ENEMY_RATE*3) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 2000 + sti(PChar.rank)*10000;
			if (IsCharacterPerkOn(pchar, "Agent"))  iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE*3 * 500 + 200000 + (sti(PChar.rank)*1000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
			else iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE*3 * 1000 + 300000 + (sti(PChar.rank)*2000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
			dialog.text = "Here is your document. You need to enter the port under a friendly flag. Remember, the patrol can check if the license is expired.";
			link.l9 = "Thank you.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;

        case "No_money":
			dialog.text = "Great! Contact me when the required amount is available.";
			link.l1 = "Good.";
			link.l1.go = "exit";
		break;

        case "patent_0":
			dialog.text = "Wonderful! To do this, you must prove your loyalty to the state" +
                          " through impeccable service. Go to any governor" + //NationNameGenitive(sti(NPChar.nation)) +
                          " and complete a number of his tasks. He will then grant you a patent.";
			link.l1 = "Tell me, "+GetAddress_FormToNPC(NPChar) + ", is there any way around this formality?";
			link.l1.go = "patent_1";
			link.l2 = "Goodbye, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;

		case "patent_1":
			dialog.text = "Do you mean bribing an official!? Do you want me to grant you a patent myself?";
			link.l1 = "Exactly!";
			if (pchar.questTemp.piratesLine == "begin" || pchar.questTemp.piratesLine == "over" || pchar.questTemp.piratesLine == "waiting_Q8")
			{
				if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
				{
					link.l1.go = "patent_2_give";
				}
				else
				{
					link.l1.go = "patent_2_none";
				}
			}
			else link.l1.go = "patent_2_none2";
			link.l2 = "No. Have a nice day, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;

		case "patent_2_none":
			dialog.text = "At the moment, I don't have the connections to get a blank patent form with all the seals and signatures.";
            link.l1 = "Sorry. Goodbye, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;

		case "patent_2_none2":
			dialog.text = "As far as I know, you work for the Brethren, and therefore even having a patent will not allow you to enter the service of any governor-General.";
            link.l1 = "Sorry. Goodbye, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;

		case "patent_2_give":
			dialog.text = "Okay, I can arrange it. What kind of patent do you need?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "England";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "France";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "Spain";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "Holland";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "You know, I think I'll manage on my own.";
			link.l9.go = "exit";
		break;

		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			// pchar.PatentPrice = 350000 - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 2000 + 6000 * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE*3;
			if (IsCharacterPerkOn(pchar, "Agent")) pchar.PatentPrice = 100000 * MOD_SKILL_ENEMY_RATE*3 - (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 5000 + 35000 + (sti(PChar.rank)*5000);
			else pchar.PatentPrice = 150000 * MOD_SKILL_ENEMY_RATE*3 - (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 5000 + 500000 + (sti(PChar.rank)*5000);
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "Явный баг, если видите - сообщите ALexusB";
                    link.l1 = "Not a bad prospect. I agree on your terms!";
                    break;
                case HOLLAND :
                    dialog.text = "Holland is almost a peaceful country, you will have many friends and few enemies. And the patent itself will only cost you "+pchar.PatentPrice+" gold.";
                    link.l1 = "Not a bad prospect. I agree on your terms!";
                    break;
                case FRANCE :
                    dialog.text = "France's friends and enemies will be yours. You will be able to sink enemy ships. And the patent itself will only cost you "+pchar.PatentPrice+" gold.";
                    link.l1 = "Great prospect! I don't care who I serve! I will serve the French too!";
                    break;
                case SPAIN :
                    dialog.text = "Spain has many enemies and they will immediately become yours! The Spaniards are a nation of sea warriors. The patent will only cost you "+pchar.PatentPrice+" gold.";
                    link.l1 = "You're the only one offering me something worthwhile! Get these pitiful pennies for the romance of a bloody battle and new tasks for high-ranking people!";
                    break;
                case ENGLAND :
                    dialog.text = "To be honest, this is how the Governor-General of England fills his pocket. And the patent itself will only cost you "+pchar.PatentPrice+" gold. ";
                    link.l1 = "I agree to give you my hard-earned money that I got while smuggling and boarding!!";
                    break;
			}

            if(makeint(Pchar.money) < makeint(pchar.PatentPrice))
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "patent_3";
			}

			link.l2 = "No, it's not for me!";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "I'm glad we agreed. It's a deal.";
			link.l1 = "Goodbye, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			if (IsCharacterPerkOn(pchar, "Agent")) Pchar.questTemp.Relations.sum = makeint(0.3 * stf(Pchar.rank)/stf(Pchar.reputation)*DIPLOMAT_SUM);
			else Pchar.questTemp.Relations.sum = makeint(0.1 * stf(Pchar.rank)/stf(Pchar.reputation)*DIPLOMAT_SUM);
			dialog.Text = "Good. It will cost " + Pchar.questTemp.Relations.sum + "gold.";
			Link.l1 = "I agree.";
			if(makeint(Pchar.money) < makeint(Pchar.questTemp.Relations.sum))
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "I think I've changed my mind.";
			Link.l2.go = "exit";
		break;

		case "Contraband_Agreed":
			dialog.Text = "Great, I'll handle it. They will deal with you.";
			Link.l99 = "Thank you.";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, 25);
			AddMoneyToCharacter(pchar, -sti(Pchar.questTemp.Relations.sum));
		break;
        // boal <--
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			dialog.text = "Hmm... I don't even know what to say. I will certainly be able to fulfill your request for reconciliation with "+ XI_ConvertString(Nations[sti(npchar.quest.relation)].Name + "Abl") +", but it will cost you " + FindRussianMoneyString(iSumm) + ".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "I don't think I have a choice anyway. So here's your money.";
				link.l1.go = "relation3";
			}
			link.l2 = "No, this is too much money. Goodbye.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "Great! You are surprisingly easy to deal with. You can rest easy, not more than 15 days, your affairs will be settled.";
			link.l1 = "Okay.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
		break;

		case "RelationYet":
			dialog.Text = "A petition has already been sent for you. Wait, things don't get done that fast.";
			Link.l99 = "Thank you.";
			Link.l99.go = "exit";
		break;

		case "City_Buy":
			dialog.Text = "Which settlement do you want to discuss?";
			for (i=0; i<MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true && sti(colonies[i].isBought) == false)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id) + " - " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)));
					Link.(attrLoc).go = "CityPay_" + i;
				}
			}
			Link.l99 = "no. Nothing.";
			Link.l99.go = "exit";
		break;

		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "City " + GetCityName(colonies[i].id) + ", belonged to " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)) + "Gen") + ", the amount of the ransom to stop attempts to recapture the settlement will be " + FindRussianMoneyString(iSumm) + ".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "Yes, that's fine with me.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "No, thanks. It's not interesting.";
			Link.l99.go = "exit";
		break;

		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "Well, the information about the deal has gone. There will be no more attempts to the city " + GetCityName(colonies[i].id) + " capturing.";
			Link.l2 = "Thank you. Have a nice day.";
			Link.l2.go = "exit";
			Link.l3 = "One more question.";
			Link.l3.go = "relation";
		break;
		//линейка ГПК
		case "SeekHVIC":
			dialog.text = "Hmm, however... Captain, what's got you interested in this office?";
			link.l1 = "I'm doing one order for them, and there are questions.";
			link.l1.go = "SeekHVIC_1";
		break;
		case "SeekHVIC_1":
			dialog.text = "What makes you think I know where they are?";
			link.l1 = "Okay, stop fooling around! Where do you get licenses from this company?";
			link.l1.go = "SeekHVIC_2";
		break;
		case "SeekHVIC_2":
			dialog.text = "At the representative of the company here in the Caribbean. By the way, what's his name? If you're dealing with him, you should know that.";
			Link.l1.edit = 6;
			link.l1 = "";
			link.l1.go = "SeekHVIC_res";
		break;
		case "SeekHVIC_res":
			attrLoc = GetStrSmallRegister(dialogEditStrings[6]);
			if (findsubstr(attrLoc, "oliver" , 0) != -1 && findsubstr(attrLoc, "trust" , 0) != -1)
			{
				dialog.text = "Hmm, that's right... Well, you can find him on San Martin, in Marigo. He has an office in the representative office of the Company, a large administrative building with security, it is difficult to miss. Don't tell me I sent you to him. Just in case...";
				link.l1 = "No problem.";
				link.l1.go = "exit";
				pchar.questTemp.LSC = "toOliverTrast";
				AddQuestRecord("ISS_PoorsMurder", "10");
				LocatorReloadEnterDisable("Marigo_town", "houseH2", false);
				if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("PoorKillSponsor", "smuggler_boss", "man", "man_fast", 30, PIRATE, -1, true)); // LEO: Страдать превозмогаторам 07.12.2021
				else sld = GetCharacter(NPC_GenerateCharacter("PoorKillSponsor", "smuggler_boss", "man", "man", 30, PIRATE, -1, true));
				sld.name = "Oliver";
				sld.lastname = "Trust";
				FantomMakeCoolFighter(sld, 40, 90, 90, "blade26", "pistol3", 100);
				sld.SaveItemsForDead = true;
				AddItems(sld, "talisman5", 1);
				if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
				sld.Dialog.Filename = "Quest\ForAll_dialog.c";
				sld.dialog.currentnode = "Begin_PoorKill";
				sld.nation = HOLLAND;
				sld.city = "Marigo_town";
				sld.location = "Marigo_houseH2";
				sld.location.group = "sit";
				sld.location.locator = "sit1";
				sld.dialog.currentnode = "PKInMarigo";
				sld.items.letter_LSC = 1;
				LAi_CharacterEnableDialog(sld);
				LAi_RemoveLoginTime(sld);
				sld.standUp = true; //вставать и нападать на врага
				LAi_SetHuberType(sld);
				ChangeItemName("letter_LSC", "itmname_letter_LSC_1");
				ChangeItemDescribe("letter_LSC", "itmdescr_letter_LSC_1");
                pchar.restoreLSCTrustLetter = "letter_LSC";
			}
			else
			{
				dialog.text = "You don't know anyone, so get out!";
				link.l1 = "Damn, it slipped my mind...";
				link.l1.go = "exit";
				pchar.questTemp.LSC = "toLicencer_2";
			}
		break;
		case "SeekHVIC_3":
			dialog.text = "Well, what do you want from me again?";
			link.l1 = "I remembered the name of the representative of the Dutch West India Company!";
			link.l1.go = "SeekHVIC_4";
		break;
		case "SeekHVIC_4":
			dialog.text = "Yes?! Well, what's his name?";
			Link.l1.edit = 6;
			link.l1 = "";
			link.l1.go = "SeekHVIC_res";
		break;
	}
}

