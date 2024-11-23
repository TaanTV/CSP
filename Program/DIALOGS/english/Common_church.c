// boal 25/04/04 общий диалог церковь
#include "DIALOGS\english\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

    string iDay, iMonth, lastspeak_date;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }

    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {
        npchar.quest.BadMeeting = "";
    }
	if (!CheckAttribute(npchar, "quest.Fooled"))
    {
        npchar.quest.Fooled = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}

	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}

	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase(""+ GetSexPhrase("My son", "My daughter") +"Unfortunately, I can't give you shelter. Run!", "The whole city guard is scouring the city in search of you, "+ GetSexPhrase("my son", "my daughter") +". The church is open to the suffering, but I cannot provide you with shelter...", ""+ GetSexPhrase("My son", "My daughter") +", you have to run! Please don't delay this!"),
					LinkRandPhrase("What are you doing in church, fallen soul? I demand that you get out immediately, before the soldiers break in and start a massacre here!", "Immediately leave the temple, godless! I won't stand next to someone like you!", "Immediately leave the temple of God! I don't need any murders here!!"));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Come on, Padre...", "I don't need your help..."),
					LinkRandPhrase("Holy Father, it's better not to get in the way...", "I'll leave, don't worry...", "Padre, don't fuss, it's not up to you, by God"));
				link.l1.go = "fight";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				Dialog.Text = "Welcome under the canopy of the holy monastery, "+ GetSexPhrase("my son", "my daughter") +".";
				link.l1 = "Padre, the tavern is stormed by a crowd of tipsy townspeople. They claim that there is a werewolf there, but I saw just a scared person. He wants to confess!";
				link.l1.go = "MC_CaracasChirch";
				Link.l2 = "I have to go.";
				Link.l2.go = "exit";
				break;
			}
			if (IsEquipCharactersByItem(pchar, "DHGlove") && npchar.quest.BadMeeting != lastspeak_date)
			{
				Dialog.Text = "You... are a sorcerer! How dare you, you filthy impious man, come to the temple of God?! Fiend of hell, may the wrath of the Lord fall on you!";
				Link.l1 = "A sorcerer, you say... And actually why a sorcerer?";
				Link.l1.go = "DHreaction";
				break;
			}
			if (startherotype == 2 && npchar.quest.BadMeeting != lastspeak_date && npchar.quest.Fooled != lastspeak_date && !IsEquipCharacterByItem(pchar, "glasses") && 80 > sti(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)))
			{
				Dialog.Text = "Your eyes... Leave the temple of the Lord, fiend of hell! You and I have nothing to talk about!";
				Link.l2 = "You are mistaken, Holy Father. I am an angel from heaven, and I have come down to earth to fulfill the Lord's commission.";
				Link.l2.go = "fool_priest";
				Link.l1 = "I didn't really want to.";
				Link.l1.go = "exit";
				break;
			}

			if (pchar.sex == "Skeleton" && GetCharacterEquipSuitID(pchar)!= "suit_1")
			{
				Dialog.Text = "Leave the temple of the Lord, fiend of hell! You and I have nothing to talk about!";
				Link.l1 = "I didn't really want to.";
				Link.l1.go = "exit";
				Link.l2 = "I don't give a damn about you and your god!";
				Link.l2.go = "exit";
				break;
			}

            if (npchar.quest.BadMeeting != lastspeak_date )
			{
				if(!CheckAttribute(Pchar, "questTemp.CapBloodLine") || Pchar.questTemp.CapBloodLine == false)
				{					
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
					{
						Dialog.Text = ""+ GetSexPhrase("My son", "My daughter") +"I'm glad to see you again!";
						link.l1 = "And I'm glad to see you in good health, Father " + npchar.name + "...";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
						break;
					}

					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						Dialog.Text = ""+ GetSexPhrase("My son", "My daughter") +"! I am glad to see you in good health and good mood again. Apparently, God contributed to the happy conclusion of our business?";
						link.l1 = "Yes, " + RandPhraseSimple("padre", "holy father") + ", although a fair wind did not always blow into my sails, even though I spent a little more time, effort and money, but in the end your assignment is completed.";
						link.l1.go = "GenQuest_Church_1_Complete_1";
						break;
					}
				}
				Dialog.Text = "Welcome under the canopy of the holy monastery, "+ GetSexPhrase("my son", "my daughter") +".";
				link.l1 = "Hello, Holy Father.";
				link.l1.go = "node_3";
				Link.l2 = "You're not my father, and don't you dare treat me like that anymore.";
				Link.l2.go = "node_2";

				if (startherotype == 2 && !IsEquipCharacterByItem(pchar, "glasses"))
				{
					Dialog.Text = "My angel! How can I help you?";
					Link.l2 = "Nothing, I'm already leaving.";
					Link.l2.go = "exit";
				}
			}
			if (npchar.quest.BadMeeting == lastspeak_date)
			{
				Dialog.Text = "Leave the temple of the Lord, blaspheme! You and I have nothing to talk about!";
				if (pchar.sex == "Skeleton" || startherotype == 2)
				{
					Dialog.Text = "Leave the temple of the Lord, evil spirits! You and I have nothing to talk about!";
				}
				Link.l1 = "I didn't really want to.";
				Link.l1.go = "exit";
			}

			NextDiag.TempNode = "First time";
		break;

		case "DHreaction":
			dialog.text = "Get out! I have nothing to talk about with you!";
			link.l1 = "I didn't really want to.";
			link.l1.go = "exit";
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -5);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "fool_priest":
			if (drand(80) > sti(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)))
			{
				dialog.text = "You can't fool me! Get out of here, so as not to defile the temple of God with your presence!";
				link.l1 = "The Devil!";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 5 + 5 * sti(pchar.rank));
				ChangeCharacterReputation(pchar, -1);
				npchar.quest.BadMeeting = lastspeak_date;
			}
			else
			{
				dialog.text = "I'm so sorry, I didn't find out. How can a simple priest serve such a heavenly creature?";
				link.l1 = "There is one question.";
				AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50 + 10 * sti(pchar.rank));
				link.l1.go = "node_3";
				npchar.quest.Fooled = lastspeak_date;

			}
		break;

		case "node_2":
			dialog.text = "Oh, you're blaspheme! Get out of here, so as not to desecrate the temple of God with your presence!";
			link.l1 = "I didn't want, anyway.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			dialog.text = "May the Lord bless you and your deeds... Did you come to me for some purpose?";
			if (startherotype == 2 && !IsEquipCharacterByItem(pchar, "glasses"))
			{
				dialog.text = "I am at your service.";
			}
			//зачарованный город -->
  			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				link.l1 = "Padre, the tavern is stormed by a crowd of tipsy townspeople. They claim that there is a werewolf there, but I saw just a terrified person. He wants to confess!";
				link.l1.go = "MC_CaracasChirch";
				break;
			}
  			if (pchar.questTemp.MC == "toCaracasTavern" && npchar.city == "Caracas")
			{
				dialog.text = "Bring this person to me. I confess it here in the church.";
				link.l1 = "I got it, Padre.";
				link.l1.go = "exit";
				break;
			}
			//<-- зачарованный город
			//homo Линейка Блада
            if (!CheckAttribute(Pchar, "questTemp.CapBloodLine") || Pchar.questTemp.CapBloodLine == false)
            {
    			link.l1 = RandPhraseSimple("I want to donate.", "I want to donate to a good cause.");
    			link.l1.go = "donation";
				if (startherotype !=2)
				{
					link.l2 = RandPhraseSimple("I think it's time for confession.", "I need to repent, "+RandPhraseSimple("padre.", "holy Father."));
					link.l2.go = "ispoved";
				}
    			link.l3 = RandPhraseSimple("I have business with you, " + RandPhraseSimple("padre.", "holy Father."),
                                           "I have arrived on business, " + RandPhraseSimple("padre.", "holy father."));
    			link.l3.go = "work";//"quest lines";
            }

			link.l6 = "Excuse me, I have to go.";
			link.l6.go = "exit";
		break;

		//Ограбление церкви -->
		case "GenQuest_Church_2_Start_2":
			dialog.text = "Oh, "+ GetSexPhrase("my son", "my daughter") +", a terrible blasphemy has been committed, the most shameful of crimes! Rob the church!!! It's like putting your dirty paws right in the pocket of the Lord!";
				link.l1 = "Oh, that's it!.. And how did this happen?";
				link.l1.go = "GenQuest_Church_2_Start_3";
				link.l2 = LinkRandPhrase("This is all sad, of course, but I think I'll go...", "I'm sorry, Padre, but I have to go...", "You probably relied too much on the Lord, you should have put stronger locks. I think I'll go...");
				link.l2.go = "exit";
			break;

		case "GenQuest_Church_2_Start_3":
			dialog.text = "Some scoundrels took out everything that was collected by the flock under the cover of night! And they took the sacrificial bowl, the atheists!";
				link.l1 = "Yeah, the times... But I hope you have taken some steps? in hot pursuit, so to speak.";
				link.l1.go = "GenQuest_Church_2_Start_4";
			break;

		case "GenQuest_Church_2_Start_4":
			dialog.text = "Oh yes! Of course!! I excommunicated the God-defying robbers from the church! And now I'm anathematizing their souls.";
				link.l1 = "I have no doubt that this is the most effective measure. But I mean something more practical. Organize a chase, for example.";
				link.l1.go = "GenQuest_Church_2_Start_5";
			break;

		case "GenQuest_Church_2_Start_5":
			dialog.text = "Ah, "+ GetSexPhrase("my son", "my daughter") +", what can a simple priest, bound by a vow of non-resistance to evil, do? These scoundrels are probably already far away from here - drinking stolen goods in taverns, or indulging in debauchery and debauchery in the arms of harlots! I hope that's where they'll end!";
				link.l1 = RandPhraseSimple("Hmm, I'm sure that such an outcome is much more attractive than hanging out on the yard. However, I won't bother you. All the best.", "Hmm, well, since we are all destined to go to our forefathers sooner or later, I would not refuse such an outcome. However, I have to go now. I wish you success in your hard work.");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("Holy Father", "Padre", "Father") + ", but I am not bound by any vows, and I will readily help the Lord bring the hour of retribution closer.";
				link.l2.go = "GenQuest_Church_2_Start_5_1";
			break;
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = "I will pray for you, " + GetSexPhrase("my son", "my daughter") + "! Go and give these scammers their due!";
				link.l1 = "You can be sure, " + RandPhraseSimple("padre.", "holy father.");
				link.l1.go = "GenQuest_Church_2_Start_6";
			break;

		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
		//	AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			break;

		case "GenQuest_Church_2_Thief_2":
			dialog.text = "Well, will the all-good Creator send pestilence and gladness on his foolish children in order to punish them for their grave sins...";
				link.l1 = "For example, for pride, or, let's say, greed... Why are you so pale, Padre?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;

		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = "Jesus Christ... Have mercy on me, a sinner... You found it... Robbers? Did you kill them?";
					link.l1 = "Or let's take the Ten Commandments, which are known to every good Christian since infancy: do not kill, do not steal, do not utter perjury against your neighbor. How can a God-fearing person violate them? And even more so, a spiritual pastor?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "It's very stuffy in here... So did you find the robbers? Did you kill them?";
					link.l1 = "Or take the Ten Commandments, which are known to every good Christian since infancy: do not kill, do not steal, do not utter perjury against your neighbor. How can a God-fearing person violate them? And even more so, a spiritual pastor?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
			break;

		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+ GetSexPhrase("My son, sir", "My daughter, madam") +"... God forgive me... such money, such temptation... The man is weak, weak! I couldn't resist... I couldn't find a place for myself... He incessantly offered prayers, performed penance, and observed strict fasting... he mortified the flesh and, unworthy, asked heaven for only one thing - that those unfortunate people whom he had led into sin, driven by greed, would remain alive...";
				link.l1 = LinkRandPhrase("Holy Father", "Padre", "Father") + ", calm down. The main thing is that they didn't tell anyone anything... and they won't tell you. By the way, they voluntarily gave me the communion cup, which I brought you.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
			break;

		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "Thank you, God! The prayers of an unworthy slave, a sinner who stumbled, mired in filth and vice have been heard...";
				link.l1 = "Anyone can stumble... However, seeing your sincere repentance, I will say this: you are not a bad person, and you are a good priest. If you go to court, it won't benefit anyone. And whether or not to remain in the service of the Lord, you will decide for yourself in your conversations with Him...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
			break;

		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+ GetSexPhrase("My son", "My daughter") +"... With tears of remorse and gratitude, I accept the cup from you. The purity and nobility of your soul shocked me. I wholeheartedly bless you and beg you to accept this modest reward in the amount of " + FindRussianMoneyString(iMoneyToCharacter) + "... I hope it will cover your expenses?";
					// ГГ не берет деньги. Плюсанем репу
					link.l1 = "This is unnecessary, Father, " + npchar.name + ". I'm not good enough to use this money for the benefit of your parishioners.";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
					// ГГ берет деньги
					link.l2 = "Thank you, " + LinkRandPhrase("holy father", "padre", "Father") + ", that's quite enough.";
					link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("My son", "My daughter") +"... With tears of remorse and gratitude, I accept the cup from you as a sign of God's mercy and forgiveness. The purity and nobility of your soul shocked me. I bless you from the bottom of my heart!";
					link.l1 = "Thank you for the blessing, " + LinkRandPhrase("padre", "father") + ".";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
					link.l1 = "A blessing, of course, is necessary, but it would be nice to back it up with something more material, since I'm on the road"+ GetSexPhrase("eu", "if") +"considerable expenses...";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}

			// Если будет чаша - здесь её отбирать!
			ChurchGenQuest2_RemoveCup();
			break;

		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("cя", "as"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterReputation(PChar, -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Oh, my child, I completely forgot... I hope this modest contribution is in the amount of " + FindRussianMoneyString(iMoneyToCharacter) + " will pay off your expenses.";
				link.l1 = "Yes, " + LinkRandPhrase("padre", "Father") + "Thank you.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
			break;

		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "I don't understand your hints, "+ GetSexPhrase("my son", "my daughter") +", what are you talking about?!";
				link.l1 = "I'm talking about the terrible things that greed can do to a person. And about this communion bowl that I got from the ragamuffins, who allegedly robbed your church... Did you want to say something?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
			break;

		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "I will say, my child, that you are very disrespectful to a person of spiritual rank, and that you may regret it. And this is the first time I've seen this cup, but if you want to donate it to the parish, then...";
				link.l1 = "Take it easy, Padre, you won't get it until you explain yourself.";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
			break;

		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = "What should I explain to you?! You are "+ GetSexPhrase("smart man", "smart girl") +", and you should understand for yourself - everything that these crooks said that I allegedly hired them is all a blatant lie! The Lord will punish these atheists not only for blasphemy, but also for perjury!";
					link.l1 = "Leave the Lord alone! How do you know what those wretches you set me on told me? Maybe I killed them before they had time to tell about your nefarious deeds?";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "I have nothing to talk about with you, you have not fulfilled the obligation you made in the face of the Lord, you swear in the temple, you are trying to blackmail the priest by shaking the church utensils that you got in some unknown way! And thank God that I'm not calling novices to catch you red-handed!";
					link.l1 = "Well... I see that you are so steeped in sin that you are not afraid of human judgment. But there is a Higher Court, before which all of us will sooner or later appear. Take your 'church utensils' and think about whether you are worthy to touch them, Father " + npchar.name + ".";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
					link.l2 = "Forgive my doubts, Holy Father, for the human heart is weak and the soul is in turmoil. Take the cup and bless me.";
					link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
			break;

		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "Uh... "+ GetSexPhrase("My son... Sir... Sir", "My daughter... Madam... Madam") +" " + PChar.name + "... I am ready to meet you halfway... consider our differences.... to compensate your travel expenses with this modest amount in the amount of " + FindRussianMoneyString(iMoneyToCharacter) + "... of course, if you do not involve outsiders in this matter...";
			// При этом варианте репу плюсуем
			link.l1 = "I'm not going to involve anyone. Take the bowl! And do not think that I will take the gold that you secretly steal from the pockets of your parishioners!";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = "I'm not going to involve anyone. Take the bowl! I'm taking this gold only because I spent too much time and money, but nothing will compensate for my deep disappointment in you!";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";

			// Если будет чаша - здесь её отбирать!
			break;

		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("en", "on"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("", "a"));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("", "la"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterReputation(PChar, 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("en", "on"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("", "a"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1":

		// ничего не принесли священнику.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
		{
			link.l1 = "Disappointing news, " + LinkRandPhrase("holy father", "padre", "Father") + ": the robbers turned out to be so insidious and resourceful that I was unable to return the church gold...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
			break;
		}

		// Принесли священнику только чашу.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
		{
			link.l1 = "Disappointing news, " + LinkRandPhrase("holy father", "padre", "Father") + ": I managed to catch up with the kidnappers, but my only trophy turned out to be this communion cup.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
			ChurchGenQuest2_RemoveCup();
			break;
		}

		// Принесли священнику и деньги и чашу.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
		{
			if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
			{
				link.l1 = "I am sure that the news will please you - I have roughly punished robbers and took away parish money, as well as this communion cup.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
			}

			// Деньги можно заныкать.
			link.l2 = LinkRandPhrase("Holy Father", "Padre", "Father") + ", I brought bad news... I had to spend a lot of time, effort and money to track down the scoundrels, but when I finally got them, it turned out that they had managed to drink and squander everything except this communion cup...";
			link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			ChurchGenQuest2_RemoveCup();
			break;
		}

		// Священник - вор.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
		{
			dialog.text = "Ah, "+ GetSexPhrase("my son", "my daughter") +", what could have happened to me? This is your path full of dangers and worries, and my peaceful cell is the limit of thoughts and prayers - like a quiet island in the raging ocean of human passions...";
				link.l1 = "Is there nothing that can shake the peace of your blissful solitude?";
				link.l1.go = "GenQuest_Church_2_Thief_2";
			break;
		}

		// Короткий вариант прохождения квеста.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
		{
			if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
			{
				link.l1 = "I am sure that the news will please you - I have roughly punished robbers and privates parish money.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
			}

			// Деньги можно заныкать.
			link.l2 = LinkRandPhrase("Holy Father", "Padre", "Father") + "... I have to upset you. I was chasing robbers all over the archipelago, overcome many dangers and obstacles, and eventually caught them, but alas... They've already squandered the church money.";
			link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
		}

		break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
		if(rand(1) == 0)	// Священник верит ГГ но не даёт денег...
		{
			if(rand(4) == 3) // Более "soft" исход событий.
			{
				dialog.text = "Oh, "+ GetSexPhrase("my son", "my daughter") +". Your words have plunged me into deep sorrow, but not into despair, for despair is a mortal sin! The Lord is sending us another test to strengthen our faith.";
					link.l1 = "Amen, Holy Father...";
					link.l1.go = "exit";
					sQuestTitle = NPChar.City + "ChurchGenQuest2";
					AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
					AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "a"));
					CloseQuestHeader(sQuestTitle);
					ChangeCharacterReputation(PChar, -2);
					DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("My son", "My daughter") +"do not lie to your spiritual pastor.";
					link.l1 = "I'm sorry, Father, but, by all the saints, I'm telling the truth...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
			}
		}
		else
		{
			// Священник даёт деньги ГГ...
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Oh, "+ GetSexPhrase("my son", "my daughter") +". Your words have plunged me into deep sorrow, but not into despair, for despair is a mortal sin! The Lord is sending us another test to strengthen our faith. However, your efforts and expenses should be rewarded, even if they did not bear fruit. Take this small amount - " + FindRussianMoneyString(iMoneyToCharacter) + " - and continue your righteous path!";
				link.l1 = "Uh-hmm!... Thank you, Padre, I will use this money for a charitable cause.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
				link.l2 = LinkRandPhrase("Holy Father", "Padre", "Father") + "... you put me in an awkward position. I can't accept a reward from you for the work you haven't done, you'd better upgrade the altar with this money.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
		}
		break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
		if(rand(6) == 3)
		{
			dialog.text = "Okay, I believe you, "+ GetSexPhrase("my son", "my daughter") +". The Lord is putting us through another test to strengthen our faith.";
				link.l1 = "Amen...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
			break;
		}
			dialog.text = "Despicable, did you really think to deceive our Lord? Damn you! Get out and remember that this money won't do you any good!";
				link.l1 = "Come on!.. Padre!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterReputation(PChar, -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterReputation(PChar, -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "Oh, "+ GetSexPhrase("my son", "my daughter") +". Your words have plunged me into deep sorrow, but not into despair, for despair is a mortal sin! The Lord is sending us another test to strengthen our faith.";
					link.l1 = "Amen, Holy Father...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = "Yes, this is the cup that disappeared with the money... but... If you got it, why didn't you return the money? There was a considerable amount there, and ordinary scammers could not spend it so soon... "+ GetSexPhrase("My son", "My daughter") +", remember that there is no worse sin than lying to your spiritual pastor, and even perjury in the temple, in front of the face of the Lord!!";
					link.l1 = "Father, " + npchar.name + ", I almost loose my life, getting this vase, I thought to please you, even if not with coins, then at least with utensils. I'm not talking about my expenses for this enterprise anymore!";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;

		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "Go away, my friend, and thank the Creator who rewarded me with a soft heart, because only for this reason you have not yet been declared a thief!";
				link.l1 = "How is that?! " + LinkRandPhrase("Holy father", "Padre", "Father") + "!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
			break;

		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("xia", "as"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "Oh, "+ GetSexPhrase("my son", "my daughter") +". Your words have plunged me into deep sorrow, but not into despair, for despair is a mortal sin! The Lord is sending us another test to strengthen our faith.";
				link.l1 = "Amen, Holy Father...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
			break;

		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "God, thank You! You have served as an instrument of the Lord, my child! I knew that our heavenly Father would guide you in the right way and would not leave you with his help! I prayed incessantly, and so...";
				link.l1 = "Actually, guns are more useful in such matters than prayers, Padre. But apparently God has really heard your prayers.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
			break;

		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+ GetSexPhrase("My son", "My daughter") +", I want to reward you with dignity"+ GetSexPhrase(", as a true knight of the Holy Mother Church,", ",") +" we did for you our best and overcame...";
				link.l1 = "Holy Father, you exaggerate my humble merits too much. I leave you to praise the Lord...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
			break;

		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "a"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

	//================================================================================================================


		case "donation":
			if (startherotype != 2 || IsEquipCharacterByItem(pchar, "glasses"))
			{
				dialog.Text = "Of course, "+ GetSexPhrase("my son", "my daughter") +". How much do you want to donate to the Holy Church?";
				Link.l1 = "I'm sorry, Father, but there will be no donation.";
				Link.l1.go = "No donation";
				Link.l2 = "Let me decide...";
				link.l2.go = "donate_input";
			}
			else
			{
				dialog.Text = "There's no need. Your mere appearance here is already worth more than any money.";
				Link.l1 = "As you wish. Then there's another question...";
				Link.l1.go = "node_3";

			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "Holy Father, I don't want to make a donation on my own. I'm doing this on an errand.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "Hmm... This is your decision, and you have the right to change it. But do not forget that this will be counted against you at the Last Judgment.";
			Link.l1 = "And not only that. Let's change the subject.";
			Link.l1.go = "node_3";
			Link.l2 = "Excuse me, Father, I have to go.";
			Link.l2.go = "exit";
		break;

		case "donate_input":
			dialog.Text = "Of course, "+ GetSexPhrase("my son", "my daughter") +". How much do you want to donate to the Holy Church?";
			Link.l1.edit = 1;
			link.l1 = " ";
			link.l1.go = "donation_thank_you";
		break;

		case "donation_thank_you":
			int iDonation = sti(dialogEditStrings[1]);
			if(iDonation > sti(pchar.money) || iDonation <= 0)
			{
				dialog.text = "Oh, " + GetSexPhrase("my son", "my daughter") + ", I see you don't have enough money...";
				link.l1 = "You're right, Father, I will change amount."
				link.l1.go = "donate_input";
				link.l2 = "You know, I changed my mind.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.Text = "On behalf of the Holy Church, thank you, "+ GetSexPhrase("my son", "my daughter") +", for your gift.";
				int iRepIncr = iDonation / 5000;
				ChangeCharacterReputation(pchar, iRepIncr);
				AddMoneyToCharacter(pchar, -iDonation);
				Link.l1 = "I need to talk to you, Father.";
				Link.l1.go = "node_3";
				Link.l2 = "Excuse me, Father, I have to go.";
				Link.l2.go = "exit";
			}
		break;

		case "ispoved":
			dialog.text = "Of course, "+ GetSexPhrase("my son", "my daughter") +"I'm listening to you.";
			link.l1 = "I changed my mind. Maybe another time.";
			link.l1.go = "exit";
			link.l2 = "I am so sinful, Holy Father. It won't take a whole day to list all my sins...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "We are all sinners, my child...";
			link.l1 = "Yes, but the burden of thousands of deaths is on my conscience. I robbed and drowned ships...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "I hope there weren't any of them who walked under the flag of " + NationNameGenitive(sti(NPChar.nation)) + "?";
			link.l1 = "No, of course not, Holy Father.";
			link.l1.go = "ispoved_3";
			link.l2 = "There were all sorts, Holy Father... all sorts.";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "Then the Lord will forgive you these sins. For our age is cruel, and by destroying the enemies of your sovereign, you save the lives of his faithful subjects.";
			link.l1 = "Thank you, Holy Father, you have comforted me very much... I'm going to go.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "The Lord will never forgive such a sin! Pray and repent, repent and pray! You have only one road - to the monastery!";
			link.l1 = "The monastery will have to wait. Not in this life, at least. Goodbye...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "I'm sorry, "+ GetSexPhrase("my son", "my daughter") +", but now all the confessionals are occupied. I will be glad to hear your repentance in at least half an hour.";
				link.l1 = "Sorry, " + RandPhraseSimple("padre", "holy father") + ", this case is of a slightly different nature. Father " + PChar.GenQuest.ChurchQuest_1.PriestName + " from " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " once shared the priceless treasures of my theological library, and now he has instructed me to pick them up if I have an opportunity.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "What business brought you, "+ GetSexPhrase("my son", "my daughter") +"?";
			link.l1 = "I wanted to ask you one question, Padre...";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("I want to talk about working for the benefit of the church of " + NationNameGenitive(sti(NPChar.nation)) + ".",
                                        "How are things going in the parish, do you need any help?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Holy Father", "Padre") + ", I wanted to talk to you about financial issues."; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "I need healing.";
                link.l4.go = "healthAdd_1";
				//Lipsar квест История давней дружбы
				if(CheckAttribute(PChar, "Luke.BadPoison"))
				{
						link.l4 = "Padre, help me. I was poisoned with some very strong poison, what should I do?";
						link.l4.go = "LukePoison";
				}
            }
			// BlackThorn - Нежданное наследство
			if (CheckAttribute(PChar, "UnexpectedInheritance"))
            {
				if(!CheckAttribute(pchar, "UnexpectedInheritance_translator"))
				{
					link.l10 = "Holy Father, I got my hands on an interesting text. It's in Latin. May I ask you to make a transfer?";
					link.l10.go = "UnexpectedInheritance_translate";
				}
				else
				{
					if(npchar.id == pchar.UnexpectedInheritance_translator && GetNpcQuestPastDayWOInit(npchar, "UnexpectedInheritance_translate") > 0 && sti(pchar.money) >= 1000)
					{
						link.l10 = "Holy Father, I'm here about the transfer. And here, please, take it for the needs of the parish.";
						link.l10.go = "UnexpectedInheritance_translate_end";
					}
				}
            }
            //==> Вставка Эдди, квест Аззи, возможность сдачи лампы.
            if (CheckCharacterItem(pchar, "Azzy_bottle"))
            {
                link.l6 = "Holy Father, I have something that I want to give to you. It's a strange tin vessel, look at it.";
                link.l6.go = "GiveLamp";
            }
			//<== Вставка Эдди, квест Аззи возможность сдачи лампы.
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Holy Father", "Padre") + ", I'm here on behalf of a man. His name is the governor " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".";
	            link.l7.go = "IntelligenceForAll";
            }
			//==> успокоить нечисть в пещерах
			if (CheckAttribute(npchar, "quest.DestroyGhost") && npchar.quest.DestroyGhost == "GoodResult")
			{
				switch (npchar.quest.DestroyGhost.label)
				{
					case "Cave": sTemp = "cave cleared"; break;
					case "cave": sTemp = "cave cleared"; break;
					case "Grotto": sTemp = "grotto cleared"; break;
					case "grotto": sTemp = "grotto cleared"; break;
					case "Dungeon": sTemp = "dungeon cleared"; break;
					case "dungeon": sTemp = "dungeon cleared"; break;
				}
				link.l5 = "Holy Father, " + sTemp + " from evil spirits. The job is done, now no one will bother the residents.";
                link.l5.go = "GhostShip_S1";
			}
			//==> ночной сторож в церкви
			if (CheckAttribute(pchar, "questTemp.different.Church_NightGuard") && pchar.questTemp.different.Church_NightGuard == npchar.location)
			{
	            link.l8 = RandPhraseSimple("Holy Father", "Padre") + ", I want to report on an assignment to work as a night watchman.";
	            link.l8.go = "NightGuard_result";
            }
			//<== ночной сторож в церкви
			link.l99 = "I've changed my mind, I have things to do.";
			link.l99.go = "exit";
		break;

		case "UnexpectedInheritance_translate":
			dialog.text = "I'm sorry, but I only provide such services to my friends and true believers. I can't attribute you to either of them.";
			link.l1 = "Very sorry.";
			link.l1.go = "exit";
			if (sti(pchar.reputation) > (REPUTATION_NEUTRAL + 10))  // кибальчиш
			{
				dialog.text = "Okay, I'll take a look. Come back tomorrow, "+GetSexPhrase("my son", "my daughter")+"and don't forget about those in need.";
				SaveCurrentNpcQuestDateParam(npchar, "UnexpectedInheritance_translate");
				pchar.UnexpectedInheritance_translator = npchar.id;
				link.l1 = "Thank you, Holy Father.";
				link.l1.go = "exit";
			}

		break;

		case "UnexpectedInheritance_translate_end":
			dialog.text = "God bless you. That's what I got.";
			link.l1 = "Thank you, Father.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			UnexpectedInheritanceTranslatePart(pchar.UnexpectedInheritance);
			DeleteAttribute(pchar, "UnexpectedInheritance_translator");
			DeleteAttribute(pchar, "UnexpectedInheritance");

		break;

		case "prihod":
			//Ограбление церкви
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "Caiman_church" && rand(4) == 1)
			{
				dialog.text = "Oh, "+ GetSexPhrase("my son", "my daughter") +", a terrible blasphemy has been committed, the most shameful of crimes! Rob the church!!! It's like putting your dirty paws right in the pocket of the Lord!";
				link.l1 = "Oh, that's it!.. And how did this happen?";
				link.l1.go = "GenQuest_Church_2_Start_3";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
				break;
			}
			//упокоение нечисти
			if (rand(2)==1 && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.DestroyGhost") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && GetNpcQuestPastDayWOInit(npchar, "Ghost") > 7 && NPChar.location != "Caiman_church")
			{
                dialog.text = "It's not really convenient for me to talk about this, but I have no other choice. There are no random things in life. And the will of the Almighty lies on everything. Maybe you are the weapon of the Lord that we need to destroy the evil spirits that defile our land.";
        		link.l1 = RandPhraseSimple("I don't quite understand, Holy Father, what scared you so much? What causes this fear?",
                                            "I beg you to continue on, Holy Father.");
        		link.l1.go = "DestroyGhost_1";
				SaveCurrentNpcQuestDateParam(npchar, "Ghost");
				npchar.quest.add = true;
				break;
			}
			//караулить церковь ночью
			if (!CheckAttribute(npchar, "quest.add") && rand(4)==1 && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.GuardNightChurch") && !CheckAttribute(pchar, "questTemp.different.Church_NightGuard") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && GetNpcQuestPastDayWOInit(npchar, "NightChurch") > 60 && GetHour() < 23)
			{
                dialog.text = ""+ GetSexPhrase("My son", "My daughter") +", I have a simple assignment for you. We need a night watchman, but not an old man with a mallet and not a defenseless parishioner. The thing is, the 'brothers' have been a little nervous lately. Some strange guys began to enter the church, but they do not pray, but only stare around...";
        		link.l1 = "And that bothers you, Father?";
				link.l1.go = "NightChurch_1";
				SaveCurrentNpcQuestDateParam(npchar, "NightChurch");
				break;
			}
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        		dialog.text = "It beautiful However, in these harsh days, "+ GetSexPhrase("my son", "my daughter") +"not everyone who comes to the temple is able to benefit the mother of our Church.";
						link.l1 = LinkRandPhrase("Padre", "Holy Father", "My Father") + ", I am a true Christian, and my intentions to serve the Mother Church are sincere."+ GetSexPhrase("Who will become her support if not such loyal knights as me?", "") +"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
				break;
		    }
            dialog.text = "Everything is calm in our parish, "+ GetSexPhrase("my son", "my daughter") +". Thanks for the offer.";
    		link.l2 = "Well, since everything is fine, I'll go about my business.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;

		// Вернуть рукописи священника -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "Well, I have one delicate assignment, the execution of which will require not only purity of thought, but also considerable courage, as well as subtlety of mind...";
				link.l1 = LinkRandPhrase("Padre", "Holy Father", "My Father") + ", I'll be happy to do you any favor, even if I have to slip into hell itself to do it! Not in the church, be it said.";
				link.l1.go = "GenQuest_Church_1_Start_2";
			break;

		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "That's how it is! It's good... But the matter is extremely delicate... Some time ago, the rector of the church " + PChar.GenQuest.ChurchQuest_1.ToName + " from " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + ", which is on " + XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland + "Voc") + " he asked me for a few theological works and ancient manuscripts from the church library for a while. Since the request was supported by the archbishop's demand not to hinder the spread of the benevolent light of knowledge, I could not refuse, although I assumed that the complexity of sea travel would not allow him to return the manuscripts on time...Could you help resolve this problem?";
			link.l1 = "I'm afraid" + LinkRandPhrase("padre", "holy father", "my father") + "that I will not justify your trust. The matter is too delicate, and you need to be a good diplomat to solve it.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Padre", "Holy Father", "My Father") + ", your assignment does not seem difficult to me. I'll be on my way today.";
			link.l2.go = "GenQuest_Church_1_Start_3";
			break;

		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
			break;

		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = "Oh!.. Yes... Indeed, I remember... But, "+ GetSexPhrase("my son", "my daughter") +"These treasures are more spiritual than material, they have brought immeasurable benefits to my parishioners and could bring it in the future!";
				link.l1 = "However, " + LinkRandPhrase("padre", "holy father", "my father") + ", the souls of the parishioners of the father " + PChar.GenQuest.ChurchQuest_1.PriestName + "they also need salvation, and without these works he is deprived of the support of the pillars of theosophy and inspiration in his sermons.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = "Oh, yes!.. Indeed... "+ GetSexPhrase("My son", "My daughter") +"these treasures are more spiritual than material, they have brought so much benefit to my parishioners that, to my shame, I was somewhat delayed in returning them to the owner...";
				link.l1 = "Exactly, " + RandPhraseSimple("padre", "holy father") + " exactly. Therefore, the father " + PChar.GenQuest.ChurchQuest_1.PriestName + "and instructed me to deliver these books to him personally.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;

		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = "I understand, my child, but don't we pray to the Lord every day: 'And forgive us, as we forgive our debtors'? But the church in " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + " immeasurably richer than my humble parish.";
			link.l1 = "Yes, Holy Father, you are right, but other biblical lines came to my mind: 'do not look for easy ways, because the Devil is waiting for us on them, and his voice is the more insinuating, and the temptation is the stronger, the easier the path!' And the padre " + PChar.GenQuest.ChurchQuest_1.PriestName + "already intended to report your forgetfulness to the archbishop, as soon as I dissuaded him by offering my help.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;

		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "A-a-to the archbishop?! About such a small thing!.. Well, why, why? I myself have long wanted to send these works to my dear brother in Christ, but somehow everything did not come across a reliable opportunity. But in you, "+ GetSexPhrase("my son", "my daughter") +", I have seen a worthy servant of God. Here, I am handing over books and manuscripts, deliver them to my father " + PChar.GenQuest.ChurchQuest_1.PriestName + "safe and sound and add my deepest thanks.";
			link.l1 = "I will definitely add, " + LinkRandPhrase("padre", "holy father", "father") + ". Absolutely.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;

		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "the manuscript" -->
			AddItems(PChar, "Bible", 1);	// Даём рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "the manuscript"
			break;

		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "officer_" + (rand(42)+1), "man", "man", 15, NPChar.nation, -1, true));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade24", "pistol3", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS24, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
		//	sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1"; // Выставляем ноду диалога на палубе корабля
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа

			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = "But, "+ GetSexPhrase("my son", "my daughter") +"... The fact is that last week I had a chance to meet with captain of the ship '" + sld.Ship.Name + "', where I was called to receive communion from a dying sailor. To my great joy, captain " + GetFullName(sld) + " reported that he was heading to " + XI_ConvertString("Colony" + GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown)) + ". And although he did not vouch for the timing, he agreed to help, assuring me that the port " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " he will definitely come in. Of course, I took advantage of the opportunity, sent the books with this kind man and handed their fate to the Lord.";
					link.l1 = "Hmm, are you sure you can trust this captain? Has he sufficiently understood the value of the work entrusted to him and the importance of the task entrusted to him?";
					link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "Ah, "+ GetSexPhrase("my son", "my daughter") +"! You are literally hours late! I have already sent my Father's books " + PChar.GenQuest.ChurchQuest_1.PriestName + ". In the morning, Captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + " came to confession and mentioned that his ship was going to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapColony) + ". And although captain did not vouch for the timing, he agreed to help, assuring me that the port " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + "he will definitely come in.";
					link.l1 = LinkRandPhrase("Padre", "Holy Father", "My Father") + "... are you sure that this captain can be trusted? And I also wanted to know the name of his ship.";
					link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
			break;

		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "I believe people, "+ GetSexPhrase("my son", "my daughter") +"because we are all created in the image and likeness, and in every soul there is a spark of God!";
				link.l1 = "Oh. This is a valid argument. Well... bless me, Holy Father, and wish me luck in finding this captain.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
			break;

		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
			break;

		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "You need to trust people, "+ GetSexPhrase("my son", "my daughter") +". Unfortunately, I can't say anything about the ship.";
				link.l1 = "And you gave valuable manuscripts to captain without even bothering to find out the name of his ship?!!";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
			break;

		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "You see, "+ GetSexPhrase("my son", "my daughter") +", captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + "a very God-fearing man...";
				link.l1 = "I've already heard this, " + LinkRandPhrase("padre", "holy father", "father") + ".";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
			break;

		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "Patience, "+ GetSexPhrase("young man", "girl") +"! Captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + " is very God-fearing, and his ship was called by such a word until today that a clergyman does not need to pronounce it even mentally! Today, in confession, I pointed out this omission to the lost soul. For, according to the Bible, the purity of the spirit should be guarded by us sinners more than the purity of the body, for our Lord has blocked the way to the kingdom of heaven for profanity...";
				link.l1 = "I understand, " + LinkRandPhrase("padre", "holy Father", "Father") + "! The God-fearing captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", a gambler and drunkard known to all the Caribbean, thanks to your suggestion, decided to rename his trough?";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
			break;

		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "You are very perceptive, "+ GetSexPhrase("my son", "my daughter") +". I do not know the new name of the ship, but undoubtedly it will be something sublime.";
				link.l1 = "Oh, " + RandPhraseSimple("padre", "holy father") + "... thank you for everything. And pray for my sinful soul...";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
			break;

		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			break;

		case "GenQuest_Church_1_Complete_1":
			dialog.text = "Oh, my child! I prayed fervently, and now everything has been resolved as well as possible! For your help and zeal, "+ GetSexPhrase("my son", "my daughter") +"Paradise and angelic heaven are undoubtedly waiting for you...";
				link.l1 = RandPhraseSimple("Padre", "Father") + ", I'm not going on a date with St. Peter yet, thank the Creator. And the living, besides the promises of heavenly grace, need many different material things...";
				link.l1.go = "GenQuest_Church_1_Complete_2";
			break;

		case "GenQuest_Church_1_Complete_2":
			dialog.text = "Yes, yes, "+ GetSexPhrase("my son", "my daughter") +", yes, yes. I will reward you properly. Here, take this, and remember that God punishes those unreasonable ones who overly care about earthly goods and worship the yellow devil!";
				link.l1 = "Thank you, " + LinkRandPhrase("padre", "holy father", "my father") + ". Take your long-awaited books and manuscripts, and pray for my sinful soul... Goodbye";
				link.l1.go = "GenQuest_Church_1_Complete_3";
			break;

		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			//PChar.GenQuest.ChurchQuest_1.AwardSumm = (rand(8) + 2) * 500;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterReputation(PChar, 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			//AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_1.AwardSumm));
			TakeNItems(pchar, "chest", 3+drand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трём кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "a"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			break;
		// <-- Вернуть рукописи священника

		//--->> успокоить нечисть
		case "DestroyGhost_1":
			npchar.quest.DestroyGhost = "toCave"; //личный флаг священника на взятый квест
			//получим пещеру для чистки
			sTemp = GetArealByCityName(npchar.city);
			if (sTemp == "Cuba2") sTemp = "Cuba1";
			if (sTemp == "Hispaniola2") sTemp = "Hispaniola1";
			aref aPlace, aPlace_2;
			makearef(aPlace, NullCharacter.TravelMap.Islands.(sTemp).Treasure);
			int iQty = GetAttributesNum(aPlace)-1;
			aPlace_2 = GetAttributeN(aPlace, rand(iQty));
			npchar.quest.DestroyGhost.locationId = GetAttributeName(aPlace_2); //Id целевой пещеры
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			npchar.quest.DestroyGhost.label = GetConvertStr(sld.id.label, "LocLables.txt"); //тип подземелья для диалогов
			switch (npchar.quest.DestroyGhost.label)
			{
				case "cave": sTemp = "The fact is that the cave located near our city has become a haven for evil spirits!"; break;
				case "Cave": sTemp = "The fact is that the cave located near our city has become a haven for evil spirits!"; break;
				case "grotto": sTemp = "The fact is that the grotto, located near our city, has become a haven for evil spirits!"; break;
				case "Grotto": sTemp = "The fact is that the grotto, located near our city, has become a haven for evil spirits!"; break;
				case "dungeon": sTemp = "The fact is that the dungeon located near our city has become a haven for evil spirits!"; break;
				case "Dungeon": sTemp = "The fact is that the dungeon located near our city has become a haven for evil spirits!"; break;
			}
			dialog.text = "More and more people are talking about terrible incidents. " + sTemp + " From there, such creatures climb into the light of God that they would not dream of in a terrible dream. People are scared, fear gets into their hearts...";
			link.l1 = "How can I help you, Holy Father?";
			link.l1.go = "DestroyGhost_2";
		break;
		case "DestroyGhost_2":
			dialog.text = "You are"+ GetSexPhrase("brave man", "brave girl") +". Become the instrument of the Lord in my hands! Destroy the evil spirits! And you will be granted the remission of your sins...";
			link.l1 = "I'm ready, padre!";
			link.l1.go = "DestroyGhost_3";
			link.l2 = "Holy Father, I cannot accept your offer. Some other time.";
			link.l2.go = "DestroyGhost_out";
		break;
		case "DestroyGhost_out":
			dialog.text = "Bad, "+ GetSexPhrase("my son", "my daughter") +", very bad. I was hoping for you!";
			link.l1 = "I think everything will work out over time...";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.DestroyGhost");
			ChangeCharacterReputation(pchar, -3);
		break;
		case "DestroyGhost_3":
			dialog.text = "Very good, "+ GetSexPhrase("my son", "my daughter") +". Go there, and may the force be with you!";
			link.l1 = "It's going to be all right, Father.";
			link.l1.go = "exit";
			pchar.questTemp.different = "DestroyGhost";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			//флаг квеста на локацию, сюда же пишем индекс дающего священника
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			sld.DestroyGhost = npchar.index;
			LAi_LocationResetMonGenTimer(sld.id);
			sTitle = sld.id + "Church_DestroyGhost";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Church_DestroyGhost", "1");
			switch (npchar.quest.DestroyGhost.label)
			{
				case "Cave": sTemp = "cave"; break;
				case "cave": sTemp = "cave"; break;
				case "Grotto": sTemp = "grotto"; break;
				case "grotto": sTemp = "grotto"; break;
				case "Dungeon": sTemp = "dungeon"; break;
				case "dungeon": sTemp = "dungeon"; break;
			}
			AddQuestUserDataForTitle(sTitle, "sLocation", sTemp);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sLocation", sTemp);
		break;

		case "GhostShip_S1":
			dialog.text = "Excellent, "+ GetSexPhrase("my son", "my daughter") +"! You did a godly deed. Know that the attitude of " + NationNameGenitive(sti(NPChar.nation)) + " to you will get better.";
			link.l1 = "I'm happy, padre...";
			link.l1.go = "GhostShip_S2";
		break;
		case "GhostShip_S2":
			dialog.text = "I will pray for you. Go, "+ GetSexPhrase("my son", "my daughter") +", and be honest before your conscience and our Lord.";
			link.l1 = "All right, Holy Father.";
			link.l1.go = "exit";
			switch (npchar.quest.DestroyGhost.label)
			{
				case "Cave": sTemp = "cave"; break;
				case "cave": sTemp = "cave"; break;
				case "Grotto": sTemp = "grotto"; break;
				case "grotto": sTemp = "grotto"; break;
				case "Dungeon": sTemp = "dungeon"; break;
				case "dungeon": sTemp = "dungeon"; break;
			}
			AddSimpleRumourCity(LinkRandPhrase("Our holy father, " + GetFullName(npchar) + ", told us that you cleaned up the evil spirits in " + sTemp + " near our city. It's a God-pleasing thing, I'll tell you...",
				"Have you heard, "+ GetSexPhrase("a certain captain", "a certain girl") +" at the request of our holy father, cleared " + sTemp + " near our city from demons ."+ GetSexPhrase("What a brave man!", "") +"",
				""+ GetSexPhrase("Captain", "Girl") +", did you clear the " + sTemp + " near our city from evil spirits? Know that we are all very grateful to you!"), npchar.city, 10, 1, "");
			ChangeCharacterReputation(pchar, 5);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			sTitle = sld.id + "Church_DestroyGhost";
			AddQuestRecordEx(sTitle, "Church_DestroyGhost", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("xia", "as"));
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);

			DeleteAttribute(npchar, "quest.DestroyGhost");
			//#20170727-01 Bug fix church skeleton quest infinite reputation
			//Attribute set in SetSkeletonsToLocation, QuestsUtilite.c
			DeleteAttribute(npchar, "DestroyGhost");
		break;
        //<<--- успокоить нечисть
		//--->> ночной сторож
		case "NightChurch_1":
			dialog.text = "That's right. And believe me, it's not for nothing. When such things happen, it is a sure sign of an impending robbery. Apparently, someone liked the church utensils. I hope you agree to spend a few nights in church?";
			link.l1 = "No, I think I will refuse, Holy Father. Please excuse me.";
			link.l1.go = "exit";
			link.l2 = "In principle, I agree. But how many nights will I have to guard the church? Maybe no one will show up, and your strange guys are ordinary thugs who are just shy to show their religious feelings in public.";
			link.l2.go = "NightChurch_2";
		break;
		case "NightChurch_2":
			dialog.text = "Hmm, maybe so, but it's unlikely. In general, you will need to stay here for three nights. If no one shows up, then we'll assume that your job has been completed successfully.";
			link.l1 = "Well, that suits me. I agree!";
			link.l1.go = "NightChurch_3";
		break;
		case "NightChurch_3":
			dialog.text = "Then start tonight. And remember that you owe to be in the church continuously from midnight to six in the morning.";
			link.l1 = "I see, Holy Father. You can rest easy for your utensils for three nights.";
			link.l1.go = "exit";
			pchar.questTemp.different = "Church_NightGuard";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			pchar.questTemp.different.Church_NightGuard = npchar.location; //флаг срабатывания нуля часов
			pchar.questTemp.different.Church_NightGuard.NightQty = 0; //кол-вот отработанных ночей
			pchar.questTemp.different.Church_NightGuard.chance = rand(3); //рендом на появление грабителей
			pchar.questTemp.different.Church_NightGuard.fight = false; //флаг боевки
			SaveCurrentQuestDateParam("questTemp.different.Church_NightGuard"); //запишем дату
			sTitle = npchar.location + "Church_NightGuard";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Church_NightGuard", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		break;

		case "NightGuard_result":
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) == 0)
			{
				dialog.text = ""+ GetSexPhrase("My son", "My daughter") +", you didn't watch a single night. Go do your job, don't bother me...";
				link.l1 = "All right, Holy Father.";
				link.l1.go = "exit";
			}
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) > 0 && sti(pchar.questTemp.different.Church_NightGuard.NightQty) < 3)
			{
				dialog.text = ""+ GetSexPhrase("My son", "My daughter") +", you didn't bring work to the end, we agreed on three nights...";
				link.l1 = "Yes, I remember... I'll keep watch.";
				link.l1.go = "exit";
			}
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) >= 3)
			{
				if (sti(pchar.questTemp.different.Church_NightGuard.fight))
				{
					dialog.text = ""+ GetSexPhrase("My son", "My daughter") +", I already know you caught church thieves. And although murder within the walls of the temple of the Lord is a sin, but the Lord will let it go to you.";
					link.l1 = "Thank you, Holy Father...";
					link.l1.go = "NightGuard_fight";
				}
				else
				{
					dialog.text = ""+ GetSexPhrase("My son", "My daughter") +", you were in the church at night. Did you see anything strange?";
					link.l1 = "No, Holy Father, everything was calm. I didn't see anyone.";
					link.l1.go = "NightGuard_noLook";
				}
			}
		break;

		case "NightGuard_noLook":
			dialog.text = "Hmm, it looks like we were wrong... Well, a wonderful result! As a reward, I do not offer you money, but I can say that your sins are before our Lord and " + NationNameAblative(sti(npchar.nation)) + " will be reduced.";
			link.l1 = "Thank you, Holy Father.";
			link.l1.go = "exit";
			sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);

			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			OfficersReaction("good");
			AddSimpleRumourCity(LinkRandPhrase("They say that you are on duty in our church at night...",
				"Night duty in the church is a matter pleasing to God. Thank you.",
				"Our holy father, " + GetFullName(npchar) + ", mentioned that you were on guard at night in our church."), npchar.city, 10, 1, "");
		break;
		case "NightGuard_fight":
			dialog.text = "In addition, I am able to reduce your sins before " + NationNameAblative(sti(npchar.nation)) + ", which I will do. Besides, I will pray for your health, and I believe you will soon feel the healing power of prayer to our Lord!";
			link.l1 = "Thank you very much, Holy Father!";
			link.l1.go = "exit";
			sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);

			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			OfficersReaction("good");
			AddCharacterMaxHealth(pchar, 2);
			AddSimpleRumourCity(LinkRandPhrase("They say that you caught bandits in our church at night! Thank you so much!",
				"You know, all the residents of the city are grateful to you for not allowing the ruin of our church. Thank you!",
				"Our holy father, " + GetFullName(npchar) + ", only talks about how you saved our church utensils that night..."), npchar.city, 10, 1, "");
		break;

		//<<--- ночной сторож
		//Lipsar квест История давней дружбы
		case "LukePoison":
			dialog.text = GetSexPhrase("My son", "My daughter") +"Let me examine you... Lord have mercy! I am not aware of this poison, I have never encountered it. You need to urgently find someone who will help you, otherwise your health will never get better!";
			link.l1 = "I'm sorry, Padre, that you can't help me.";
			link.l1.go = "exit";
			if (NPChar.City == "Bridgetown")
			{
				dialog.text = GetSexPhrase("My son", "My daughter") +", let me examine you... Lord have mercy! I know what kind of poison it is! He is very dangerous, you need to start treatment immediately! I'll help you.";
				link.l1 = "What are we waiting for?! I will gladly accept your help!";
				link.l1.go = "exit";
				AddDialogExitQuest("HealingPoison");
			}
		break;
        case "healthAdd_1":
            if (stf(pchar.Health.HP) >= 57.0) // отлично
            {
                dialog.text = "Your health " + GetHealthNameMaxSmall(pchar) + " and the wounds will heal themselves. You just need to avoid bloodshed and take care of your health.";
    			link.l1 = "Thank you, you are encouraging. I'll try not to get into fights for a while.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "Your health " + GetHealthNameMaxSmall(pchar) + ", and although the wounds will heal themselves, it won't hurt you to fix it.";
    			link.l1 = "What is needed for this?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "Why is my health deteriorating at all?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "Very simple, "+ GetSexPhrase("my son", "my daughter") +", you take damage when you are injured. This does not go away without a trace, your health is undermined by every wound, and as a result you become weak and can't fence anymore. Your team, seeing the weakness of the leader, loses respect for you. But on the other hand, you become more careful and the ability to protect yourself temporarily increases. Timely rest and minimization of injuries will help you stay always full of energy.";
			link.l1 = "Thank you, you enlightened me.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "Prayers and non-violence, "+ GetSexPhrase("my son", "my daughter") +". Then the Lord will return to you what you have lost.";
			link.l1 = "Could you pray for me?";
			link.l1.go = "healthAdd_3";
			link.l2 = "That is, no way? Hm.. We were encouraging, thank you.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "Me? Perhaps it is possible. But you will have to contribute alms to our parish.";
    			link.l1 = pcharrepphrase("How much?", "With pleasure! What is its size?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "I'll do it myself, somehow...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+ GetSexPhrase("My son", "My daughter") +", I'm already praying for your well-being. Prayers will take up all my time until the end of the month.";
    			link.l1    = "Thank you, "+RandPhraseSimple("padre.", "holy Father.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "One hundred thousand gold will be quite enough payment for a miracle of healing.";
			link.l1 = pcharrepphrase("How much!!! Are you out of your mind?! I'll pay that amount when I plunder a couple of churches.", "It's too much for me. It can be seen that they are telling the truth - money cannot buy health.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "I agree!";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "Okay. Your health will improve a little. But you need to avoid fights and take care of yourself, otherwise the effect will come to naught. I need to spend a whole month praying for your mortal body.";
			link.l1 = "Thank you. I'll come back in a month, if I'll need. .";
			link.l1.go = "exit";
		break;
		// диалог для капелата из тюряги
		case "Prison_Temp":
            NextDiag.TempNode = "Prison_Temp";
			dialog.text = "We have nothing more to talk about.";
			link.l1 = "Yes and no need.";
			link.l1.go = "Exit";
		break;

		case "Prison_Cell":
            NextDiag.TempNode = "Prison_Temp";
			dialog.text = "Lost soul, do you want to repent of your sins, purify your soul and ease your lot?";
			link.l1 = "Who are you, actually?";
			link.l1.go = "Prison_Cell_Info";
			link.l2 = "With willingness and humility, Padre.";
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = "Get out, holy man.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Info":
			dialog.text = "I am a local chaplain, I ease the fate of prisoners, I confess before and sing a funeral after the execution of the death sentence, or I give a farewell before the long road to the mines.";
			link.l1 = "Is there any other choice besides hard labor and execution?";
			link.l1.go = "Prison_Cell_Info_2";
			link.l2 = "I'm ready to repent, Padre.";
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = "I am absolutely not guilty. I don't need any of this.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Info_2":
			dialog.text = "Of course "+ GetSexPhrase("my son", "my daughter") +", not everyone lives to be sentenced, many casemates remain an eternal shelter. Are you ready to tell me about your sins?";
			link.l2 = "I'm ready to repent, Padre.";
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = "I am absolutely not guilty. I don't need any of this.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_None":
			dialog.text = "Perseverance in heresy and apostasy will never bring you to the Kingdom of God. Hunt and repent!";
			link.l1 = "I insist, I don't need it. Go away!";
			link.l1.go = "Prison_Cell_death";//"Exit";
			//AddDialogExitQuest("MoveToPrison_Cell");
		break;

		case "Prison_Cell_Talk":
			dialog.text = "I'm listening to you, "+ GetSexPhrase("my son", "my daughter") +".";
			link.l2 = "I am a sinner, Padre, many atrocities on my account, I robbed and killed innocent, but I wasn't alone. I was helped by loyal colleagues. Can you give them a message from me?";
			link.l2.go = "Prison_Cell_Talk_2";
			link.l3 = "I changed my mind. Leave me alone.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Talk_2":
			dialog.text = "So you're also the ringleader of criminals? And you're asking me to help you with your insidious plans? This is not going to happen! I will immediately insist on your sentence.";
			link.l1 = "What a fool you are, and you also put on a cassock!";
			link.l1.go = "Prison_Cell_death";
		break;

		case "Prison_Cell_death":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   			sld = &Characters[sti(PChar.GenQuest.ToPrisonCmdIdx)];
			// to_do DeathExecutionStart(Pchar, sti(sld.nation));
		break;
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = "And who is this kind soul that donates?";
			link.l1 = "Hmm... This is the owner of the local brothel.";
			link.l1.go = "HostessChurch_call";
			link.l2 = "I would prefer not to say names. There could be an anonymous donation!";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		case "HostessChurch_call":
			if (sti(pchar.reputation) < 10)
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = "Are you asking for a sinner? She's thought about your soul. It's great, because we will all appear before the Lord!";
					link.l1 = "That's right. I hope the Lord will be merciful to me... So how about a donation?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Get out, Satan!!! Take your wicked money and get out of here!";
					link.l1 = "Holy Father, how is that?! We come to you with all our heart, and you...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = "I am glad that you are helping sinners find their way to our Lord. You will be rewarded in heaven for this!";
					link.l1 = "That would be great! So what about the donation?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "I cannot accept money earned in sin. Give them back to this harlot, "+ GetSexPhrase("my son", "my daughter") +". There is no way to find the way to the Lord through money.";
					link.l1 = "It is a pity that you reject it. It's a pity...";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "Take this money without even knowing who it's from...";
				link.l1 = "Yes, Padre, that's right. Accept the donation from the bottom of your heart!";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "Take this money without even knowing who it's from? Are you crazy?! And suddenly, there is blood on this money!!";
				link.l1 = "Holy Father, there is blood on all the money...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "I accept it, "+ GetSexPhrase("my son", "my daughter") +". Go, you can give this to the harlot.";
			link.l1 = "All right, Padre. Thank you.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		case "HostessChurch_ok_1":
			dialog.text = "I accept it, "+ GetSexPhrase("my son", "my daughter") +". You can pass it to the pitcher.";
			link.l1 = "All right, Padre. Thank you.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		case "HostessChurch_bad":
			dialog.text = "Get out, you fiend of hell!!! And don't you dare show your face to me!";
			link.l1 = "Heh, all right.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		case "HostessChurch_bad_1":
			dialog.text = "This is my decision. Go in peace, "+ GetSexPhrase("my son", "my daughter") +".";
			link.l1 = "Goodbye, Padre.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		case "HostessChurch_bad_2":
			dialog.text = "That's what you think, you're wick! Get out of the temple and don't show your face to me!";
			link.l1 = "Right? Yes, please, I will leave...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		//зачарованный город. базар падре в Каракасе
		case "MC_CaracasChirch":
			dialog.text = ""+ GetSexPhrase("My son", "My daughter") +", The Church saves the lost. Werewolves, witches and warlocks are guided on the right path by the Holy Inquisition. Or ordinary citizens, if the Lord chooses them as his tool. Who are we to interfere?";
			link.l1 = "But if he's really innocent? Strange: to me"+ GetSexPhrase(", corsair, ", "") +"I have to appeal to the conscience of the priest!";
			link.l1.go = "MC_CaracasChirch_1";
		break;
		case "MC_CaracasChirch_1":
			dialog.text = "Don't get too excited, "+ GetSexPhrase("my son", "my daughter") +". If his soul is innocent, then it will go to heaven! But if I profess to be a fiend, there is a way to check. The devil's spawn will not be able to enter the temple of God. If you bring him here, and the punishment of heaven does not strike him, of course, I will not refuse him confession.";
			link.l1 = "I'll bring him!";
			link.l1.go = "exit";
			pchar.questTemp.MC = "toCaracasTavern";
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
				sld.lifeDay = 0;
			}
			//дым от костра
			locations[FindLocation("Caracas_town")].hidden_effects = true;
		break;

	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr);
	//string sColony = FindNonEnemyColonyForAdventure(GetCityNation(PChar.GenQuest.ChurchQuest_1.QuestTown), PChar.GenQuest.ChurchQuest_1.QuestTown, true);
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].IslandLable;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;

	// Чтоб жизнь мёдом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Church Generator 1: Key scene - 2A (just take the manuscripts from the priest).");
		break;

		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Church Generator 1: Key Scene - 2B-A (cap search. There is complete information about him).");
		break;

		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Church Generator 1: Key Scene - 2B-B (cap search. The name of the spike is unknown.)");
		break;
	}
}
