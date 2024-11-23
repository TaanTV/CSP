void ProcessDialogEvent()
{
    ref NPChar;
    ref Pchar = GetMainCharacter();
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
    break;
	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this city, I ask you not to walk with a naked blade here.", "You know, as a citizen of this city, I ask you not to walk with a naked blade here.");
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Careful on turns, "+ GetSexPhrase("buddy", "girlfriend") +", when you run with a gun in your hand. I can get nervous...", "I don't like when "+ GetSexPhrase("men", "all sorts") +" walk in front of me with weapons at the ready. It scares me...");
			link.l1 = RandPhraseSimple("Understood.", "I'm removing.");
		}
		Link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
	break;
    case "First Time":
        if (!isMainCharacterPatented())
        {
            Log_info("You don't have a patent");
            dialog.text = "Come on, what's up.";
            link.l1 = "Okay, okay, don't get all worked up.";
            link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
        }
        else
        {
            dialog.text = "Oh! Who do I see?! " + GetFullName(pchar) + ", in person! What a meeting!";
            link.l1 = "Uh... I'm afraid I don't recognize you.";
            link.l1.go = "StartQuest_1";
            AddBonusEnergyToCharacter(NPChar, 50);
        }
    break;
    case "StartQuest_1":
        dialog.text = "Yes, it's me, Luke! We went under the flag of Bart the Portuguese.";
        link.l1 = "Your mizzen! Luke! How you've changed, old man!";
        link.l2 = "Hmm... Still not there. You'd get away from me, buddy, for good, for good.";
        link.l1.go = "StartQuest_3";
        link.l2.go = "exit";
    break;
    case "StartQuest_3":
        dialog.text = "Heh! And I thought I was completely crazy, and it wasn't you. Let's go to the tavern, sit and chat!";
        link.l1 = "Ha! With pleasure!";
		DeleteAttribute(NPChar, "quest");
        AddDialogExitQuest("Taverna");
    break;
    case "StartQuest_4":
        dialog.text = GetFullName(pchar) + ", how are you, " + GetSexPhrase("buddy", "girlfriend") + "? Tell me, how did you get here?";
        link.l1 = "I'm a kind of traveler, then I'll sail to one island, then to another, and maybe I'll want to go to Main.";
        link.l1.go = "StartQuest_6";
    break;
    case "StartQuest_6":
        dialog.text = "That's how it is. I remember our last trip, when we went to plunder Guinea for slaves. We were almost interrupted then. The settlement we decided to capture was very well defended. Yes... Not everyone managed to leave... Let's drink to the fact that we stayed alive!";
        link.l1 = "Oh, yeah, a lot of our people died then. But everyone could have left if it wasn't for the greed of our commander! Let's have a drink!";
        link.l1.go = "StartQuest_7";
    break;
    case "StartQuest_7":
        dialog.text = "I see you have your own ship and rank... Listen, it's not convenient for me to ask you, we haven't seen each other for so long, and so immediately...";
        link.l1 = "Don't yule, spit it out, I'll help if I can.";
        link.l1.go = "GiveQuest";
    break;
    case "GiveQuest":
        string spawn_max;
        int Gorod;
        NPChar = characterFromID("Old Friend");
        if (Pchar.PatentNation == "eng")
        {
            while (0 < 1)
            {
                Gorod = rand(5);
                if (Gorod == 0)
                {
                    spawn_max = "PortRoyal_tavern";
                    dialog.text = "Please deliver a letter from me to my friend in Port Royal. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                    link.l1 = "Ha! Your old nickname! Give me the letter!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                    AddQuestUserData("Silence_Price", "sCity2", "Port Royal");
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 1)
                {
                    spawn_max = "SentJons_tavern";
                    dialog.text = "Please deliver a letter from me to my friend in St. John's. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                    link.l1 = "Ha! Your old nickname! Give me the letter!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                    AddQuestUserData("Silence_Price", "sCity2", "St. John's");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 2)
                {
                    spawn_max = "Charles_tavern";
                    dialog.text = "Please deliver a letter from me to my friend in Charlestown. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                    link.l1 = "Ha! Your old nickname! Give me the letter!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                    AddQuestUserData("Silence_Price", "Friendname", NPChar.name + " " + NPChar.lastname);
                    AddQuestUserData("Silence_Price", "sCity2", "Charlestown");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 3)
                {
                    spawn_max = "Bridgetown_tavern";
                    dialog.text = "Please deliver a letter from me to my friend in Bridgetown. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                    link.l1 = "Ha! Your old nickname! Give me the letter!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                    AddQuestUserData("Silence_Price", "sCity2", "Bridgetown");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 4)
                {
                    spawn_max = "Portspein_tavern";
                    dialog.text = "Please deliver a letter from me to my friend in Port of Spain. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                    link.l1 = "Ha! Your old nickname! Give me the letter!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                    AddQuestUserData("Silence_Price", "sCity2", "Port of Spain");
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
            }
        }
        else
        {
            if (Pchar.PatentNation == "hol")
            {
                while (0 < 1)
                {
                    Gorod = rand(3);
                    if (Gorod == 0)
                    {
                        spawn_max = "Villemstad_tavern";
                        dialog.text = "Please deliver a letter from me to my friend in Willemstad. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                        link.l1 = "Ha! Your old nickname! Give me the letter!";
                        link.l1.go = "StartQuest_8";
                        SetQuestHeader("Silence_Price");
                        AddQuestRecord("Silence_Price", "1");
                        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                        AddQuestUserData("Silence_Price", "sCity2", "Willemstad");
                        AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                        AddDialogExitQuest("AfterDialog");
                        TakeItemFromCharacter(NPChar, "Lukes_letter");
                        GiveItem2Character(Pchar, "Lukes_letter");
                        PlaySound("Interface\important_item.wav");
                        SpawnMaks(spawn_max);
                    break;
                    }
                    if (Gorod == 1)
                    {
                        spawn_max = "Marigo_tavern";
                        dialog.text = "Please deliver a letter from me to my friend in Marigo. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                        link.l1 = "Ha! Your old nickname! Give me the letter!";
                        link.l1.go = "StartQuest_8";
                        SetQuestHeader("Silence_Price");
                        AddQuestRecord("Silence_Price", "1");
                        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                        AddQuestUserData("Silence_Price", "sCity2", "Marigo");
                        AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                        AddDialogExitQuest("AfterDialog");
                        TakeItemFromCharacter(NPChar, "Lukes_letter");
                        GiveItem2Character(Pchar, "Lukes_letter");
                        PlaySound("Interface\important_item.wav");
                        SpawnMaks(spawn_max);
                    break;
                    }
                    if (Gorod == 2)
                    {
                        spawn_max = "FortOrange_tavern";
                        dialog.text = "Please deliver a letter from me to my friend in Fort Orange. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                        link.l1 = "Ha! Your old nickname! Give me the letter!";
                        link.l1.go = "StartQuest_8";
                        SetQuestHeader("Silence_Price");
                        AddQuestRecord("Silence_Price", "1");
                        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                        AddQuestUserData("Silence_Price", "sCity2", "a");
                        AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                        AddDialogExitQuest("AfterDialog");
                        TakeItemFromCharacter(NPChar, "Lukes_letter");
                        GiveItem2Character(Pchar, "Lukes_letter");
                        PlaySound("Interface\important_item.wav");
                        SpawnMaks(spawn_max);
                    break;
                    }
                }
            }
            else
            {
                if (Pchar.PatentNation == "fra")
                {
                    while (0 < 1)
                    {
                        Gorod = rand(4);
                        if (Gorod == 0)
                        {
                            spawn_max = "FortFrance_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Fort De France. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Fort De France");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 1)
                        {
                            spawn_max = "FortFrance_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Fort De France. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Fort De France");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 2)
                        {
                            spawn_max = "BasTer_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Basse-Terre. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Basse-Terre");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 3)
                        {
                            spawn_max = "Tortuga_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Tortuga. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Tortuga");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                    }
                }
                else
                {
                    while (0 < 1)
                    {
                        Gorod = rand(9);
                        if (Gorod == 0)
                        {
                            spawn_max = "Caracas_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Caracas. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Caracas");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 1)
                        {
                            spawn_max = "Cumana_tavern";
                            dialog.text = "Please deliver a letter from me for my friend in Cumana. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Kumanu");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 2)
                        {
                            spawn_max = "Cartahena_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Cartagena. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Cartagena");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 3)
                        {
                            spawn_max = "Maracaibo_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Maracaibo. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Maracaibo");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 4)
                        {
                            spawn_max = "PortoBello_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Porto Bello. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Porto Bello");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 5)
                        {
                            spawn_max = "SantaCatalina_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Santa Catalina. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Santa Catalina");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 6)
                        {
                            spawn_max = "Beliz_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Belize. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Belize");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 7)
                        {
                            spawn_max = "SantoDomingo_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Santo Domingo. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Santo Domingo");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 8)
                        {
                            spawn_max = "SanJuan_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in San Juan. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1")
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "San Juan");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 9)
                        {
                            spawn_max = "Santiago_tavern";
                            dialog.text = "Please deliver a letter from me to my friend in Santiago. Don't look like that, you'll get paid on arrival! You'll probably find him at the tavern. My friend's name is Maximilian Weber, tell me you're from Luke the Artist.";
                            link.l1 = "Ha! Your old nickname! Give me the letter!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
                            AddQuestUserData("Silence_Price", "sCity2", "Santiago");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + " " + NPChar.lastname);
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                    }
                }
            }
        }
        break;
    case "StartQuest_8":
        dialog.text = "Yes, the nickname has not gone away! Thank you very much! Good luck with your sailing and a fair wind! Let's have a drink!";
        link.l1 = "Let's have a drink!";
        NextDiag.TempNode = "Story1";
        link.l1.go = "Exit";
		Pchar.Luke.SpawnMaks = "1";
    break;
    case "Story1":
		dialog.text = "What are you waiting for? It's time for you to hit the road!";
		link.l1="Wait, Luke. How did you manage to get out then? I remember that I was alone. Tell me, what happened then?";
		link.l1.go="Story2";
	break;
	case "Story2":
		dialog.text = "Hmm, I knew you'd ask. Well, listen. Then, after we fled, the musketeer hit me right in the thigh and I fell among the dead bodies. When the firing subsided, enemy soldiers found me alive. They didn't kill me, but they captured me...";
		link.l1="What happened next?";
		link.l1.go="Story3";
	break;
	case "Story3":
		dialog.text = "Listen. They did not torture me, but on the contrary helped with my injury and put me on my feet. They taught me military and naval art and set me free for a promise.";
		link.l1="What kind of promise did you make to them?";
		link.l1.go="Story4";
	break;
	case "Story4":
		dialog.text = "Hmm, I promise I'll tell you about it when you get back from Maximilian. Now is not the time for this conversation.";
		link.l1="Okay, Luke, I hope you keep your promise";
		link.l1.go="exit";
		AddQuestRecord("Silence_Price", "3");
		AddQuestUserData("Silence_Price", "sSex",GetSexPhrase("", "а"));
		NextDiag.TempNode="Pause";
	break;
    case "Pause":
        dialog.text = "Oh, who do I see! Have a seat, let's have a drink.";
        link.l1 = "Yes, it's me. No, thanks, I have things to do.";
        link.l1.go = "exit";
    break;
	case "SecondQuest_1":
		dialog.text = Pchar.name +"?! What are you doing here?! How... How did you find me? This... This is impossible!";
		link.l1="What are you, Luke. What's the point of your games? Do you want to get rid of me? Annoy me? What's your goal, bastard?";
		link.l1.go="SecondQuest_2";
	break;
	case "SecondQuest_2":
		dialog.text = "You don't understand... I had everything, everything I needed. I was happy. But after that ill-fated hike, damn it, my life went downhill. I want to take revenge on everyone who is guilty of this.";
		link.l1 = "Wait, Luke, but what is my fault?";
		link.l1.go = "SecondQuest_3";
	break;
	case "SecondQuest_3":
		dialog.text = Pchar.Name + ", I told you, you won't understand. Homo homini lupus est. There are no innocent people. There are only different degrees of responsibility. And now you will feel responsible for everything that happened back then.";
		link.l1 = "Whatever you say. I'm going to put an end to your acting career now, you bastard!";
		link.l1.go = "exit";
		AddDialogExitQuest("LukeFight");
	break;
	case "SecondQuest_4":
		dialog.text = Pchar.Name + ", wait, I give up... You won.";
		link.l1 = "What?! Just like that?!";
		link.l1.go = "SecondQuest_5";
	break;
	case "SecondQuest_5":
		dialog.text = "Of course not! Max, come to me! " + Pchar.Name + ", catch it!";
		link.l1 = "Kha, kha kha... What is it?!";
		link.l1.go = "exit";
		AddDialogExitQuest("LukeOut");
	break;
	}
}
