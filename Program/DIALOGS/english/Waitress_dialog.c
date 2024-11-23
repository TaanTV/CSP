
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "I asked you to wait for me upstairs. Don't loom here, don't attract attention...";
					link.l1 = "Okay, I won't set you up...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "I'm new here, so don't keep me busy, please. I haven't settled into a new place yet...";
					link.l1 = "Where's the waitress who worked before you? " + pchar.questTemp.different.FackWaitress.Name + "it seems...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{
					dialog.text = "Come back, dear. If there's time, we'll have more fun...";
					link.l1 = "Required!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{
					dialog.text = "I don't know you, don't bother me...";
					link.l1 = "Where is my money?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Sorry, "+ GetSexPhrase("handsome", "beautiful") +", I'm busy. A good day for a tavern is not always a good day to talk!";
					link.l1 = "...";
					link.l1.go = "exit";
					link.l9 = "I want to ask you a couple of questions.";
					link.l9.go = "quests";//(перессылка в файл города)
				break;

				case 1:
					dialog.text = "Please, Captain, don't make a row! It's so hard to clean up after them!";
					link.l1 = ""+ GetSexPhrase("Ahem... It didn't seem like I was going to.", "Do I look like a rowdy?") +"";
					link.l1.go = "exit";
					link.l9 = "I want to ask you a couple of questions.";
					link.l9.go = "quests";//(перессылка в файл города)
				break;

				case 2:
					dialog.text = ""+ GetSexPhrase("Oh, Captain! Would you like to get into my arms today? I don't like to brag, but...", "Have a seat, Captain. A real sea wolf is always welcome here.") +"";
					link.l1 = ""+ GetSexPhrase("Alas, I'm in a hurry now! Let's do it another time!", "Thanks, cutie.") +"";
					link.l1.go = "exit";
					link.l9 = "I want to ask you a couple of questions.";
					link.l9.go = "quests";//(перессылка в файл города)
					// boal 27.03.2004 -->
					bool isBloodPrologue = false;
					if (CheckAttribute(Pchar, "questTemp.CapBloodLine") && Pchar.questTemp.CapBloodLine == true) isBloodPrologue = true;
					if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && pchar.questTemp.piratesLine != "Soukins_toPuertoPrincipe" && PChar.sex != "woman" && pchar.questTemp.piratesLine != "Soukins_seekRings" && !isBloodPrologue && pchar.GenQuest.EncGirl != "HorseToTavern"/*&& npchar.city != "Villemstad"*/)
					{
						link.l2 = "With great pleasure, baby!";
						link.l2.go = "Love_1";
						link.l9 = "I want to ask you a couple of questions.";
						link.l9.go = "quests";//(перессылка в файл города)
						if (SharleMaryIsHere())
						{
							link.l1 = "...";
							link.l1.go = "Mary_Eto_Lovushka_1";
							DeleteAttribute(link, "l2");
							DeleteAttribute(link, "l9");
							pchar.Mary.waitress.npcharID = npchar.id;
						}
					}
					// boal 27.03.2004 <--
				break;

				case 3:
					dialog.text = "If you want to order something, please contact the owner. He's standing behind the counter.";
					link.l1 = "Thanks for the advice.";
					link.l1.go = "exit";
					link.l9 = "I want to ask you a couple of questions.";
					link.l9.go = "quests";//(перессылка в файл города)
				break;

				case 4:
					dialog.text = "If you want to have a good rest and improve your health, rent a room for the night. Spending the night in the common room is unlikely to add to your strength.";
					link.l1 = "Thank you.";
					link.l1.go = "exit";
					link.l9 = "I want to ask you a couple of questions.";
					link.l9.go = "quests";//(перессылка в файл города)
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City")) //квест мэра поп поиску шпиона
			{
				link.l4 = "Tell me, "+ GetSexPhrase("beauty", "darling") +", have you noticed anyone suspicious here lately?";
				if (pchar.GenQuest.SeekSpy.City == "1")
				{
					link.l4.go = "SeekSpy_Seen";
				}
				else
				{
					link.l4.go = "SeekSpy_NotSeen";
				}
			}
		break;

		case "Mary_Eto_Lovushka_1":
			StartInstantDialogNoType(pchar.SharleMaryId, "Mary_Eto_Lovushka_2", "Waitress_dialog.c");
		break;
		case "Mary_Eto_Lovushka_2":
			dialog.text = RandPhraseSimple("(to the waitress) I'm going to scratch your eyes out, you bitch!", "(to the waitress) Do you want to take my husband away?! I'm going to take you to hell now!");
	        link.l1 = "Mary, put the knife away! We don't want any trouble here.";
	        link.l1.go = "Mary_Eto_Lovushka_3";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID(pchar.Mary.waitress.npcharID));
		break;
		case "Mary_Eto_Lovushka_3":
			DialogExit();
			
			sld = characterFromID("SharleMary");
			sld.Dialog.Filename = "Quest\MainheroPrologues\Mary_dialog.c";
			sld.dialog.currentnode = "hired";
			LAi_SetOfficerType(sld);
		break;
        case "Love_1":
			dialog.text = "Then listen carefully. Rent a room at our tavern. Go there and wait for me. I'll sneak in to see you later...";
			link.l1 = "Heh! I'll do everything, darling! I'm waiting!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = cRand(2);
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterReputation(pchar, -1);
		break;
        case "Love_IDN":
			dialog.text = "She doesn't work here anymore, she quit... I'm sorry, I have a lot to do.";
			link.l1 = "Okay...";
			link.l1.go = "exit";
		break;
        case "Love_IDN_1":
			dialog.text = "That's what, you horny dog. I do not know where your money is! If you bother me, I'll call the guards, and you'll end up in jail today!";
			link.l1 = "Okay, don't need a guard... The fool himself.";
			link.l1.go = "Love_IDN_2";
		break;
        case "Love_IDN_2":
			dialog.text = "That's exactly what the fool himself is. You'll be smarter and more decent from now on.";
			link.l1 = "Yeah, I'll try...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "Are you awake?";
			link.l1 = "Mm-hmm.";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "Are you feeling ill? Does your head hurt?";
			link.l1 = "Where the hell am I?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "So you don't remember anything? Even the way you were robbed?";
			link.l1 = "What? Oh... my head... Who dared?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "How should I know? They came, threatened to kill, searched their pockets and left.";
			link.l2 = "Okay, what's gone is gone.";
			link.l2.go = "exit";
		break;
		//==> eddy. квест мэра, вопросы не замечала ли шпиона
		case "SeekSpy_Seen":
			dialog.text = NPCStringReactionRepeat("I don't even know... Suspicious? Although, wait, it seems there is one. He looks like an ordinary citizen, but he's too annoying with different questions, and I haven't seen him in the city before. You're unlikely to find him here, but look for him in the city.",
				"Oh, well, we've already talked about him! I can't say anything else.", "It's the same thing again... I've already told you everything.", "How many times can you ask the same thing?! Maybe you need something else?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thank you, "+ GetSexPhrase("beauty", "darling") +". Well, I'm going to look for this guy.", "Yes? Well, okay...",
                      "Hmm, yeah...", "Sorry"+ GetSexPhrase(", beautiful", "") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "SeekSpy_NotSeen":
			dialog.text = NPCStringReactionRepeat("No, I haven't seen anyone so suspicious right now.",
				"Oh, well, we've already talked about him! I can't say anything else.", "It's the same thing again... I've already told you everything.", "How many times can you ask the same thing?! Maybe you need something else?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thank you, "+ GetSexPhrase("beauty", "darling") +". Well, I'm going to look for this guy.", "Yes? Well, okay...",
                      "Hmm, yeah...", "Sorry"+ GetSexPhrase(", beautiful", "") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
}

