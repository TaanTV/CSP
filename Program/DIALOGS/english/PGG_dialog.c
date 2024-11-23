#include "DIALOGS\english\Common_Duel.c"

#define MAX_PGG_STORIES 		12
#define MAX_PGG_QUEST_STORIES 	3
#define MAX_PGG_MEET_REP 		8

string PGG_Stories[MAX_PGG_STORIES] = {
	"...only the devil and I know this place, and the last one alive will take it all!..",
	"...and Maynard replied, 'I'm not expecting mercy from you, and you won't get it from me either'.",
	"...Cats have clung to the hull! Take your places! And the sea devil can't resist here!..",
	"...In the right hand, a saber! In the left - a pistol! Together we'll send hundreds to the other world!..",
	"...We're pressed to the mast! Smoke - like in hell! Better to die in battle than hang in port!",
	"...once at sea, a little drunk, he suggested: 'Let's create our own hell here right now and see who can endure longer'.",
	"...And here's a funny story that happened to my old friend in Portobello. We were walking through the evening streets from the port to the hot quarter. I'm on the foc'sle, and my companion has already taken the topsail in a reef, then a pair of brigantines came towards us. Both ready for battle. And as soon as we aligned side by side, my friend fires from both sides! Ha-ha-ha-ha...",
	"...Ha-ha-ha!.. And in Santa Cruz, there was an incident during mooring. With a shout of 'Watch out!' my sailor throws the heaving line and hits a local onlooker right in the forehead! The guy - boom! - and falls unconscious. The sailor, frightened, without waiting for the gangway, jumps onto the pier and starts pouring water from the end of the line. Finally, the guy comes to and says to the sailor: - When you throw the heaving line, you need to shout 'Look out!'. Ah-ha-ha...",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues"
};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
	"...Somehow we got stuck in Florida - waiting out the calm. When the rum supplies ran out at the tavern, we ended up in a brothel. And being under the reef, I apparently blurted out to one of the girls about the gold I had tucked away for a rainy day. So imagine - when a month later I visited my hiding place, it was as empty as a hungover head! Bite me, sardine, if that talkative beast didn't spill the beans about my stash to the first scoundrel. So, I have no faith in women, not even half a peso!..\nBut then an experienced hanger-on approached our table. He surely has a special approach to the ladies. Or am I wrong? Bite me, sardine, ha-ha-ha!..",
	"...and he mockingly says to her, 'Let's go upstairs. Before joining the crew, we need to check what you can do, like an officer.' And the girl grabbed a knife almost as big as her and says, 'First, let's see if you're fit to be my captain!' Ha-ha-ha... She chased him around the tavern like a shark chasing a cod, and it would have been very funny, gentlemen, if she hadn't killed the poor fellow right in the middle of the hall in front of everyone. May the Lord rest his soul... But since then, I keep an eye out on the Bermudes, just in case she shows up there too!\nHo, let's welcome the worthy captain, who surely would find a way to get along with this fury! Ah-ha-ha-ha...",
	"TBD in InitDynamicValues"
}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
	"It's rare to meet a decent captain in these seas.",
	"Nobility is not in fashion nowadays.",
	"And here's an honest captain, no match for you thugs! Hehe!",
	"It's rare to meet a decent captain in these parts.",
	"Damn it, nobility is not in fashion these days.",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues"
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
	"Here comes another pirate!",
	"There was a smell of gunpowder and blood, a filibuster on the starboard side!",
	"I feel the smell of gunpowder... Gentlemen, we have been joined by another glorious corsair, who will certainly have something to tell in confession. Ha ha ha",
	"There was a smell of gunpowder and blood on the starboard side!",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues"
};

string PGGQuestID = "Gen_PGGQuest1";
bool isSetSail = false; // флаг того, что поймали ПГГ на море
bool isPGGInitiative = false; // флаг того, что ПГГ сам подошел

void InitDynamicValues(ref NPChar) {
	isSetSail = CheckAttribute(NPChar, "PGGAi.Task.SetSail");
	isPGGInitiative = CheckAttribute(NPChar, "PGGAi.ActiveQuest");
	if (NPChar.sex == "woman") PGGQuestID = "Gen_PGGQuest1" + NPChar.sex;

	PGG_Stories[8] = "... No, gentlemen, these are all jokes... And here's a story that I personally was in not only a witness, but also a participant in some way. I was heading to the Charlestown tavern one day, straight from the dock, where I was watching heeling over his old Condor, and Captain Sharp himself falls out of the tavern door to meet me! It storms him mercilessly, the mizzen has already been completely torn off, and only with a blind he tries to maneuver up the steps. No sooner had I offered him a services of a pilot, then railing broke under him!!! Ho-ho-ho-ho...\n",
	PGG_Stories[9] = "... I can't say anything about the Flying Dutchman. Neither I nor any of my sailors have ever seen him, thank God... But there was a case no less mysterious. To the east of Bermudes, we met a brigantine under full sail, but she was on a strange course – a kind of zigzags. I didn't plan anything like that, but I sent a boat. What was our surprise when there was not a single soul on board!.. And there are 1,700 barrels of excellent wine in the hold!.. That's what I call luck! And without a single shot being fired! Ha ha ha..\n",
  	PGG_Stories[10] = "... Still, I'm a slope to think, gentlemen, that all these tales about the Flying Dutchman are nothing more than idle inventions of cowardly merchants who are ready to see in every sail on the horizon a bloodthirsty privateer with a drunken monster on the bridge, and in every lugger they meet a harbinger of misfortune...\n";
	PGG_Stories[11] = "... Maybe someone remembers the case south of Key West when I was concussed by beams? Although there was no visible damage, I've layed there for two months. " + NPCharSexPhrase(NPChar, "And my passion of that time persuaded me", "And my friend at that time persuaded me") + " to confess. Like, with God's help, things will get better... Well, I went, and the priest asks: 'Have you killed many people?', " + NPCharSexPhrase(NPChar, "my son", "my daughter") + "? Have you sunk many ships?' – 'Lo-o-ot of' – I said. He din't calm down: 'Did you kill men? That's when I say, 'Padre, I'm not here to brag!' Ha-ha-ha...\n";

	// TODO: не подходят по контексту, надо бы заменить для женского ПГГ
	if (NPChar.sex == "woman") {
		PGG_QuestStories[0] = "... In my right, a saber shines, in the left, a pistol gleams, together we'll send them, beyond the earthly dreams...";
		PGG_QuestStories[1] = "... We're pinned to the mast! The smoke is like hell! It's better to die in a fight than to hang in the port!";
	}
	PGG_QuestStories[2] = "...I don't know about the Flying Dutchman himself, but I saw a ghost ship with my own eyes, as I see you now, gentlemen!.. The damn frigate, black as night, flew out of the fog and boarded without firing a shot! I must admit, I was pretty scared, but we dodged on the port tack and were just preparing to fire a volley of buckshot when he disappeared, as suddenly as he appeared! He was flying through the waves like a bird! I only managed to see the title - 'Queen'... And thunder struck me - on the deck and the cables of this vessel were full of living dead men...\nSuch a devil... And who would not be scared? Suddenly the Sea Devil himself was at the helm? ho ho ho! Rum all!",

  PGG_Meet_BadRep[4] = "Oh, gentlemen, here's a seasoned corsair who probably has something to tell in a friendly company over a mug of rum.. " + IfPhraseSimple(isSetSail, "", "Would you like to join us?");
	PGG_Meet_BadRep[5] = "Gentlemen, there is gentleman of fortune, " + IfPhraseSimple(isSetSail, "on our deck", "at our table") + ", I suppose.";
	PGG_Meet_BadRep[6] = "And here's another " + GetSexPhrase("darling of Fortune", "sea wolf") + "!";
	PGG_Meet_BadRep[7] = GetSexPhrase("Another gentleman of fortune", "Another conqueror of the seas") + ", I suppose.";

  PGG_Meet_GoodRep[5] = "And here's another 'Great Captain', who don't look for easy ways..."
	PGG_Meet_GoodRep[6] = "And here's a heroic personality, I've already heard about you!";
	PGG_Meet_GoodRep[7] = "Gentlemen, we have worthy captain, who haven't been in such a mess yet. What will you tell us, respectfull captain?";
}

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	InitDynamicValues(NPChar);

  ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";

	switch(Dialog.CurrentNode)
	{
	case "Enemy_town":
		Dialog.text = "Hmm... I'm a daredevil, of course, but it's a risk.... Well, no, I'll go my own way...";
		link.l1 = RandPhraseSimple("Eh... Oh well...", "Have a nice day.");
		link.l1.go = "Exit";
		break;	

	case "First time":
		if (!CheckAttribute(PChar, "questTemp.DuelTimer"))
		{//Запускаем счётчик для отката
			PChar.questTemp.DuelTimer = true;
			SaveCurrentQuestDateParam("PChar.questTemp.DuelCooldown");
		}

		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(PChar, "questTemp.PGGContra.Know"))
		{
			ContrabandDialog(link);
			break;
		}

		if(rand(10) == 0)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else {
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd] + LinkRandPhrase("... Blast me!.. ", "...Bite me with a snake!..", "... Hold me seven!.. ") + PCharRepPhrase(PGG_Meet_BadRep[iAns], PGG_Meet_GoodRep[iAns]);
		}

		if (sti(PChar.Ship.Type) != SHIP_NOTUSED) {
			link.l1 = PCharRepPhrase(
				RandSwear() + RandPhraseSimple(
					"I'm captain " + GetFullName(PChar) + ".",
					"I am captain of the vessel '" + PChar.Ship.Name + "' and a couple hundred desperate sons of bitches! Hehe! My name is " + GetFullName(PChar) + "."
				),
				RandPhraseSimple(
					"Let me introduce myself. I'm captain " + GetFullName(PChar) + ".", 
					"I had not honor to be introduced to you. I'm captain of the ship '" + PChar.Ship.Name + "' under the " + NationNameGenitive(sti(PChar.nation)) + " flag. My name is " + GetFullName(PChar) + "."
				)
			);
		} else {
			link.l1 = "Let me introduce myself, my name is " + GetFullName(PChar) + ". By chance, I found myself without a ship.";
		}

		link.l1.go = "Second time";
		NPChar.onceGreeting = true;
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(PChar, "questTemp.PGGContra.Know")) {
			ContrabandDialog(link);
			break;
		}
		
		// если репа позволяет, общаемся по-человечески
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd] + PCharRepPhrase(PGG_Meet_BadRep[iAns], PGG_Meet_GoodRep[iAns]) + 
				RandPhraseSimple("What news?", "What's new going on in the archipelago?");

			if(rand(10) == 0)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd] + PCharRepPhrase("What news?", "What's new going on in the archipelago?");
			}
		} else {
			Dialog.text = RandPhraseSimple(
				"What do you need" + GetFullName(PChar) + "?", 
				RandPhraseSimple(
					"Who is this? Oh, you... Get lost, I'm not in the mood...", 
					"Oh, it's you... Walk by, I'm not in the mood..."
				)
			);
		}

		link.l1 = "What about the deal?";
		link.l1.go = "quest";

		/* // && !CheckAttribute(NPChar, "PGGWhisperQuestEnd") && !CheckAttribute(PChar, "PGGWhisperComplete")	//выглядит избыточно - достаточно 1го должно быть
		if (NPChar.name == "Whisper" && !CheckAttribute(NPChar, "PGGWhisperQuestStart") && GetCharacterShipClass(PChar) < 4 && PChar.rank >= 15 && pchar.location != "Deck_Near_Ship")
		{			
			Dialog.Text = "You know, you're just in time, there's one thing.";
			link.l1 = "What are you talking about?";
			link.l1.go = "Quest_Whisper";
			//DeleteAttribute(PChar, "GenQuest.PGG_Quest");//Зачем это здесь? Какая связь с ПП и квестом Виспер? 
			//разобраться, сможет ли ВИспер после квеста выдавать ПП нормально?
		} */

		link.lgame = "Don't you want to unwind?";
		link.lgame.go = "Play_Game";

		if(!CheckAttribute(PChar, "PGG_hired"))
		{
			if (sti(PChar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = "I've been thinking... Would you like to join me? " + 
					"With two ships, we can do good things.";
				link.l2.go = "companion";
			}

			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				link.l3 = RandPhraseSimple(
					"Would you like to join my ship as an officer?", 
					"Perhaps, an officer like you, I could use it. What do you say?"
				);
				link.l3.go = "officer";
			}
		}

		// потерял корабль, переопределяем все выше сказанное
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED) {
			Dialog.Text = RandPhraseSimple(
				"Oh, woe is me, woe is me... My ship is at the bottom!", 
				"Who do I see?! What kind of wind brought you to our region? But I'm left without a ship..."
			);
		}

		// первый раз встретили, переопределяем все выше сказанное
		if (CheckAttribute(NPChar, "onceGreeting")) {
			Dialog.Text = "Well, everyone here knows me! I am " + GetFullName(NPChar);
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED) {
				Dialog.Text = Dialog.Text + ", Captain of " + XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen") + " '" + NPChar.Ship.Name + "'";
			}
			Dialog.Text = Dialog.Text + ". Nice to meet you, what can I do for you" + NPCharSexPhrase(NPChar, "en", "on") + "?";
			DeleteAttribute(NPChar, "onceGreeting");
		}
		
		if (bBettaTestMode)
		{
			link.l5 = "(Betta Test) Quests.";
			link.l5.go = "BT_Quest";
			link.l6 = "(Betta Test) Duels.";
			link.l6.go = "outraged";
		}

		if (GetQuestPastDayParam("PChar.questTemp.DuelCooldown") >= 3 || bBettaTestMode)
		{
			if (sti(PChar.reputation < 20) && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 51 && !isSetSail)
			{
				link.l8 = PCharRepPhrase(
					"This tavern is too cramped for the two of us. I want you to disappear.",
					"If you only knew who are you talking to, you'd sang differently, " + NPCharSexPhrase(NPChar, "bastard", "harbor slut") + "."
				);
				link.l8.go = "outraged";
			}
		}

		link.l9 = "Nothing.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// Officer
//==================================================
	case "officer":
		//раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow && !CheckAttribute(NPChar, "HiringMoneyPaid"))
		{
			Dialog.Text = RandPhraseSimple(
				"I've already told you that I'm not interested in it.", 
				"I thought we had already discussed everything."
			);
			link.l1 = RandPhraseSimple("How could I forget it?!", "It's true. Well, bye.");
			link.l1.go = "exit";
			break;
		}

		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("Hmm... probably not. There is no desire for a second time.", "And you think I'm going to take that bait twice?!!");
			link.l1 = RandPhraseSimple("As you wish...", "Well... take care of yourself.");
			link.l1.go = "exit";
			break;
		}

		//если отношение ниже 70, то в 70 процентов случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && drand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm.. Perhaps not...", "No, it's not for me! I don't want to be an officer!");
			link.l1 = RandPhraseSimple("Well, whatever you want...", "Well, have a nice stay.");
			link.l1.go = "exit";
			NPChar.HiringMoney = sti(NPChar.rank)*100000;
			link.l2 = "Then I'll make an offer that you can't refuse anymore - " + NPChar.HiringMoney +  " piastres.";
			link.l2.go = "officer_pay";

			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple(
				"Yes, you have a complete set already.", 
				"I don't think you're ready to command me."
			);
			link.l1 = RandPhraseSimple("It's a pity...", "So it's not fate.");
			link.l1.go = "exit";
			
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}

		if (!CheckAttribute(NPChar, "Quest.Officer.Price")) NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE*3 - MakeInt(GetSummonSkillFromNameToOld(PChar, SKILL_COMMERCE)*1000);
		
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
			RandPhraseSimple(
				"This is what you need! Our blades will drink enemy blood! One problem, I need " + NPChar.Quest.Officer.Price + " piastres to pay off debts.",
				"You look real sea woolf. And if you're ready to pay " + NPChar.Quest.Officer.Price + "piastrres, then perhaps we can work together."
			),
			LinkRandPhrase(
				"Your offer is very flattering to me. I agree for a very reasonable fee in the amount of " + NPChar.Quest.Officer.Price + " piastres.",
				"Hmm... You look like you've been a sailor. Maybe I should accept the offer if you agree to pay me " + NPChar.Quest.Officer.Price + " piastres.",
				"I think we'll work together, Captain. In total " + NPChar.Quest.Officer.Price + " piastres and we will shake hands."
			)
		);

		MakeRandomLinkOrderTwo(link, 
			PCharRepPhrase(RandSwear() + 
				RandPhraseSimple(
					"It suits me. But I hope you won't demand that much every day.", 
					"It's damn expensive, but I think you're worth it."
				),
				LinkRandPhrase(
					"I agree. Consider yourself enrolled in the team.", 
					"Hmm... I think I'm ready to part with this amount.", 
					"It looks like you're worth the money. Here you go!"
				)
			), "officer_hired",
			PCharRepPhrase(RandSwear() + 
				RandPhraseSimple(
					"You're not worth that much. Be...", 
					"It's damn expensive, I'm not ready to throw away so much money."
				),
				LinkRandPhrase(
					"yeah... Greed is not a vice...", 
					"Are you kidding me? For such money, I can buy a dozen like you.", 
					"This is a robbery... Where will I get you that amount?"
				)
			), "exit"
		);

		link.l3 = "Hmm... And what are you like?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (!CheckAttribute(NPChar, "HiringMoneyPaid") && sti(PChar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "It looks like you have a cash problem, Captain.";
			link.l1 = "Ah... Indeed.";
			link.l1.go = "exit";
			break;
		}

		Restore_PGG(NPChar);
		PChar.questTemp.HiringOfficerIDX = NPChar.index;
		if (NPChar.model.animation == "man" || NPChar.model.animation == "YokoDias" || NPChar.model.animation == "Milenace") NPChar.CanTakeMushket = true;
		if(NPChar.model == "PGG_Whisper_6") EquipCharacterByItem(NPChar, "suit_1");
		if (!CheckAttribute(NPChar, "HiringMoneyPaid")) AddMoneyToCharacter(PChar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		if (NPChar.sex == "woman") {
			NPChar.greeting = "Gr_Danielle";
		}

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");
		
		Dialog.Text = RandPhraseSimple("That's great!", "I didn't doubt in you, captain.");
		link.l1 = "Don't be late for departure.";
		link.l1.go = "exit";
		break;

//==================================================
// Companion
//==================================================
	case "companion":
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow  && !CheckAttribute(NPChar, "HiringMoneyPaid"))
		{
			Dialog.Text = RandPhraseSimple("I've already told you that I'm not interested in it.", "I thought we discussed everything.");
			link.l1 = RandPhraseSimple("How could I forget it?!", "It's true. Well, bye.");
			link.l1.go = "exit";
			break;
		}

		// если разница в кораблях больше 1 класса, отказываем
		if (GetCharacterShipClass(PChar) - 1 > GetCharacterShipClass(NPChar))
		{
			Dialog.Text = RandPhraseSimple("Swim with you!?? Find a bigger ship!", "I don't think I'm interested in this!");
			link.l1 = RandPhraseSimple("Well, whatever you want...", "Well, have a nice stay.");
			link.l1.go = "exit";

			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}

		if (GetCompanionQuantity(PChar) >= COMPANION_MAX) {
			MaxCompanionsExceededDialog(link, NPChar)
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}

		//если отношение ниже 70, то в 100 процентов случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70)
		{
			Dialog.Text = RandPhraseSimple(
				"Hmm.. Probably not... I don't know you at all. For starters, we should go on a business trip together sometime.", 
				"No, thanks. I don't like to swim under someone else's command. And I don't know you at all. We should go on a business trip together sometime before making such offers to each other."
			);
			link.l1 = RandPhraseSimple("Well, whatever you want...", "Well, have a nice stay.");
			link.l1.go = "exit";
			NPChar.HiringMoney = sti(NPChar.rank)*100000;
			link.l2 = "Then I'll make an offer that you can't refuse anymore - "+ NPChar.HiringMoney+ " piastres.";
			link.l2.go = "companion_pay";

			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}

		SetCompanionIndex(PChar, -1, sti(NPChar.index));
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
			RandPhraseSimple(
				"I like you! It's a deal! I can already hear the ringing of the piastres in our pockets!",
				"You're not bad, "+ GetSexPhrase("guy", "girl") +"... I think we'll work together!"
			),
			LinkRandPhrase(
				"I like your offer. I agree.",
				"It's interesting. I also think that together we can do more!", 
				"Perhaps it will be interesting. It's a deal."
			)
		);
		link.l1 = RandPhraseSimple("Great, I'm waiting for you at sea!", "It's a deal! We're going to be a great team.");
		link.l1.go = "exit";

		Restore_PGG(NPChar);
		NPChar.PGGAi.IsPGG = false;
		NPChar.PGGAi.location.town = "none";
		NPChar.Dialog.TempNode = "hired";
		NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
		NPChar.Payment = true;
		NPChar.Money   = 0;

		if (NPChar.model.animation == "man" || NPChar.model.animation == "YokoDias" || NPChar.model.animation == "Milenace") NPChar.CanTakeMushket = true;
		if(NPChar.model == "PGG_Whisper_6") EquipCharacterByItem(NPChar, "suit_1");
		PGG_Disband_Fleet(NPChar);
		SetBaseShipData(NPChar);
		DeleteAttribute(NPChar, "ship.sails");
		RepairMasts(NPChar);
		DeleteAttribute(NPChar, "ship.blots");
		Fantom_SetCannons(NPChar, "pirate");
		Fantom_SetBalls(NPChar, "pirate");

		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");
		SetCharacterRemovable(NPChar, true);
		SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		LAi_SetImmortal(NPChar, false);

		break;

	case "companion_pay":
		if (sti(PChar.money) < sti(NPChar.HiringMoney))
		{
			NotEnoughMoneyDialog(link, NPChar);
			break;
		}
		
		Dialog.Text = RandSwear() + "I really can't."
		PGG_ChangeRelation2MainCharacter(NPChar, 100);
		AddMoneyToCharacter(PChar, -sti(NPChar.HiringMoney));
		NPChar.HiringMoneyPaid = true;

		link.l1 = "Here's your money.";
		link.l1.go = "companion";

		break;

	case "officer_pay":
		if (sti(PChar.money) < sti(NPChar.HiringMoney))
		{
			NotEnoughMoneyDialog(link, NPChar);
			break;
		}
		
		Dialog.Text = RandSwear() + "I really can't."
		PGG_ChangeRelation2MainCharacter(NPChar, 100);
		AddMoneyToCharacter(PChar, -sti(NPChar.HiringMoney));
		NPChar.HiringMoneyPaid = true;
		link.l1 = "Here's your money.";
		link.l1.go = "officer_hired";
	break;

	case "companion_leave":		
		Dialog.Text = RandSwear() + NPCharRepPhrase(NPChar,
			RandPhraseSimple("Tear you apart, shark!!! I'm leaving the squadron!", "My patience has run out! I'm leaving."),
			RandPhraseSimple("I've had enough, Admiral!... I'm going my own way!", "I've had enough! I'm leaving the squadron.")
		);

		link.l1 = PCharRepPhrase(
			RandPhraseSimple("Well, get lost " + NPCharSexPhrase(NPChar, "to your health", "from here, cheapie") + "!", "You can go to hell " + NPCharSexPhrase(NPChar, ".", "cabin bugger!")),
			RandPhraseSimple("Well, I won't keep it.", "Free will. A fair wind in the sails.")
		);
		link.l1.go = "Exit_Companion_Leave";

		link.l2 = PCharRepPhrase(
			RandPhraseSimple("E... How about a little bonus?", "Carramba!!! Why don't you stay? I'm ready even to pay a bonus to your team!"),
			RandPhraseSimple("It's a pity to break up... Maybe a small reward will resolve our differences?", "How about a raise?")
		);
		link.l2.go = "companion_stay";
		
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion.Price"))
		{
			Dialog.Text = RandPhraseSimple("Once is enough for me. I don't believe in your promises anymore!", "No amount of money can tempt me. My decision is final!");
			link.l1 = RandPhraseSimple("Well, then, all the best.", "Then get out, and don't let me see you anymore!");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}

		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear() + NPCharRepPhrase(NPChar,
			RandPhraseSimple(
				"A bonus? Great! Amount in " + NPChar.Quest.Companion.Price + " piastres, it will suit me.",
				"Perhaps if you pay my team " + NPChar.Quest.Companion.Price + " piastres, I'll persuade them to stay."
			),
			RandPhraseSimple(
				"Good! I'm ready " + NPCharSexPhrase(NPChar, "", "a") + " stay for a modest bonus in the amount of " + NPChar.Quest.Companion.Price + " piastres!",
				NPChar.Quest.Companion.Price + " piastres will arrange for me and my team for a while."
			)
		);
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"You're making fun of me! Get the hell out.", 
				"Ha... yes, I'd rather spend this money on something more useful!"
			),
			RandPhraseSimple(
				"Well, no way. I'm not that rich!", 
				"Goodbye. I don't want to pay that much."
			)
		);
		link.l1.go = "Exit_Companion_Leave";

		if (sti(PChar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(
				RandPhraseSimple(
					"That's great! Keep the bonus money!", 
					"I didn't doubt that it's only about the money!"
				),
				RandPhraseSimple(
					"Great! I'm happy that you're staying!", 
					"Here is the promised bonus. And now we're back together."
				)
			);
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(PChar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
		GetCharacterPos(NPChar, &locx, &locy, &locz);
		sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(PChar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// Quests
//==================================================
//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = "Choose a template!";
		link.l1 = "Quest 1 Template - marine.";
		link.l1.go = "BT_Quest_1";
		link.l2 = "Quest 2 Template - land.";
		link.l2.go = "BT_Quest_2";
		link.l3 = "Quest 3 Template - land.";
		link.l3.go = "HelpBackShip";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "SELECTED! Quest 1 Template - marine.";
		link.l1 = "Oh yeah...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "SELECTED! Quest 1 Template is overland.";
		link.l1 = "Oh yeah...";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;

		Dialog.Text = RandPhraseSimple("What are talking about? Ic... Can't you see my friends and I are having a rest!.. Ic..", "E... No business today!");
		link.l1 = "I see...";
		link.l1.go = "exit";

		if (!PGG_IsQuestAvaible() && !isSetSail) {
			Log_TestInfo("Wrong location for PP")
			break; // локация не подходит
		}

		if (CheckAttribute(NPChar, "mapEnc") && findsubstr(NPChar.mapEnc.Name, "merchants" , 0) != -1) // ПГГ с прицепом
		{
			Dialog.Text = "I have enough things to do right now. You can see that I'm not swimming " + NPCharSexPhrase(NPChar, "one", "alone") + "?";
			link.l1 = "I see...";
			link.l1.go = "exit";
			break;
		}

		if (!CheckAttribute(PChar, "Ship.Type") || sti(PChar.Ship.Type) == SHIP_NOTUSED) // гг без корабля
		{
			PCharNoShipDialog(link, NPChar);
			break;
		}

		if (!CheckAttribute(NPChar, "Ship.Type") || sti(NPChar.Ship.Type) == SHIP_NOTUSED) // пгг без корабля
		{
			PGGNoShipDialog(link, NPChar);
			break;
		}

		if (GetCharacterShipClass(PChar) > 4) // класс не подходит
		{
			PCharShipClassIsLowDialog(link, NPChar);
			break;
		}

		if (GetCompanionQuantity(PChar) >= COMPANION_MAX) // компаньонов максимальное количество
		{
			MaxCompanionsExceededDialog(link, NPChar);
			break;
		}

		int iDays = GetQuestPastDayParam("QuestTalk");
		if (isSetSail && iDays < 7) // поймали в море и с прошлого ПП прошло менее недели
		{
			Log_TestInfo("Time has not passed since the previous PP (the zero day of NG creation is also considered)")
			Log_TestInfo(" days have passed: " + iDays + ", days left: " + sti(7 - iDays))
			PGGQuestNotEnoughtTimePassedDialog(link, NPChar);
			break;
		}

		if (iDays < 14) // поймали в городе и с прошлого ПП прошло менее двух недель
		{
			Log_TestInfo("Time has not passed since the previous PP (the zero day of NG creation is also considered)")
			Log_TestInfo(" days have passed: " + iDays + ", days left: " + sti(14 - iDays))
			PGGQuestNotEnoughtTimePassedDialog(link, NPChar);
			break;
		}

		// квест Виспер постоянно ломал ПП
		if (CheckAttribute(PChar, "PGGWhisperComplete") || CheckAttribute(pchar, "PGGWhisperQuest")) {
			if (CheckAttribute(PChar, "GenQuest.PGG_Quest") && NPChar.name != "Whisper")
			DeleteAttribute(PChar, "GenQuest.PGG_Quest");
		}

 		// TODO: тут неведомая хуйня, вот это иногда багает и так и остается флажок, будто мы на ПП еще, хотя квест закрыт
		// пытался дебажить, но причину найти не смог, вроде во всех исходах мы подчищаем это
		// есть подозрение, что были ошибки до подчистки флага -> мы вылетели к хуям, либо скипнули дальнейшую обработку -> флаг так и остался в подвешенном состоянии
		if (CheckAttribute(PChar, "GenQuest.PGG_Quest"))
		{
			bool toSkip = PGGQuestAlreadyActive(link, NPChar);
			if (toSkip) {
				break;
			}
		}

		if (drand1(100) > 60 || isSetSail) // шанс 40% на дельце, либо поймали в море
		{
			Dialog.Text = "What kind of conversation is this? Although you're on time. I have a business for you!";
			link.l1 = "Hmm. What are you talking about?";

			if (isSetSail) link.l1.go = "Quest_1_Ship";
			else link.l1.go = "Quest_1_Work";

			NPChar.PGGAi.ActiveQuest = true;
			isPGGInitiative = true;
			PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
			SaveCurrentQuestDateParam("QuestTalk");
		}

		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		SaveCurrentQuestDateParam("QuestTalk");
		Dialog.Text = "Be careful!!! Oh! I think I know you, you're a famous person! I've heard a lot about you."; 

		if (CheckAttribute(NPChar, "meeting") && sti(NPChar.meeting))
		{
			link.l1 = "Hello, " + GetFullName(NPChar) + ". How are you?";
			link.l1.go = "Quest_1_Work";
			break;
		}
			
		link.l1 = PCharRepPhrase(
			RandSwear() + RandPhraseSimple(
				"I'm captain " + GetFullName(PChar) + ".",
				"I'm captain of the vessel '" + PChar.Ship.Name + "' and a couple hundred desperate sons of bitches! Hehe! " + 
				"My name is " + GetFullName(PChar) + "."
			),
			RandPhraseSimple(
				"Let me introduce myself. I'm captain " + GetFullName(PChar) + ".", 
				"Let me introduce myself. I'm captain " + GetFullName(PChar) + ".", 
				"Let me introduce myself. I'm captain " + GetFullName(PChar) + ".", 
				"I haven't the honor to be introduced to you" +
				". I'm captain of the ship '" + PChar.Ship.Name + "' under the flag of " + NationNameGenitive(sti(PChar.nation)) + 
				". My name is " + GetFullName(PChar) + "."
			)
		);
		link.l1.go = "Quest_1_Meeting";
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		Dialog.Text = "I am " + GetFullName(NPChar) + ", captain of the " + XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen") + " '" + NPChar.Ship.Name + "'" +
		NPCharSexPhrase(NPChar, 
			NPCharRepPhrase(NPChar, ". The most famous corsair of the entire Spanish Main.", ". An ordinary sailor."), 
			NPCharRepPhrase(NPChar, ". The most famous conqueror of the seas in all the Caribbean.", ". The most ordinary pirate girl.")
		);
		link.l1 = "Yes, I'll remember you now.";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		GeneratePGGQuestLocation(NPChar);

		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"I have a great deal for you and your devils. ",
				"Let's join forces and we can take a great jackpot! Well, we'll have to kill someone, of course. Hehe."
			),
			RandPhraseSimple(
				"I have a business proposal for you, Captain. ",
				"Captain, your reputation is well known and, therefore, I want to offer you a part in a tempting case. "
			)
		) + RandPhraseSimple(
			"Just between us. Let's discuss everything on my deck on the '" + NPChar.Ship.Name + "', over a keg of excellent ale. Today.", 
			"There's no reason to talk about it here, we'll talk on my ship '" + NPChar.Ship.Name + "' in peace and quiet. Don't delay the visit."
		);

		link.l1 = PCharRepPhrase(
			RandSwear() + RandPhraseSimple(
				"To hell with the delays! I want to know the good quickly, and the bad even faster!",
				"There's no need to delay! There's a room in the tavern, we'll discuss it there!"
			),
			RandPhraseSimple(
				"Why not discuss your proposal right now, in the tavern room?",
				"I'm afraid I have no desire to visit your ship. If you need anything, post it here!"
			)
		);
		link.l1.go = "Quest_1_Work_1";

		link.l2 = PCharRepPhrase(
			RandPhraseSimple(
				"I'll be there! But if you waste my time, I'll rip out your tongue!",
				RandSwear() + "Wait, I hope it's worth it. And don't you dare mess with me!"
			),
			RandPhraseSimple(
				"I am pleased to accept your invitation, Captain.",
				"You intrigued me. Of course I will come."
			)
		);
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"You're probably sick of pitching! Go find yourself a mom with a pacifier!!!",
				"Did you, "+ GetSexPhrase("buddy", "girlfriend") +", shit your pants from fear?!! Get out! You're not my match."
			),
			RandPhraseSimple(
				"No, that's not it. I won't force you, so you're not interested in gold.",
				"It's either that or nothing. It's up to you. There are many hunters for gold."
			)
		);
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Ha! And you with a pepper! And you're not afraid... I'll come!",
				"You know how to insist on your own, Captain. Wait."
			),
			RandPhraseSimple(
				"Okay, I agree.",
				"You are very convincing. I'm ready to discuss business on your ship."
			)
		);
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";

		link.l2 = PCharRepPhrase(
			RandPhraseSimple(
				"Ha! I thought" + NPCharSexPhrase(NPChar, "", "a") + "lure me onto your ship and kill me? It won't work!",
				"Your words are not worth a penny! I don't need to have anything to do with you!"
			),
			RandPhraseSimple(
				"A dubious offer. I have to refuse.",
				"It was nice to meet you, Captain " + GetFullName(NPChar) + ". Goodbye."
			)
		);
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Rum for me! And you get out of my sight!",
				"We've already discussed everything, haven't we?"
			),
			RandPhraseSimple(
				"Go your way, I'm busy " + NPCharSexPhrase(NPChar, "", "a") + ".",
				"I guess you and I don't have any common topics."
			)
		);
		link.l1 = RandSwear();
		link.l1.go = "Exit_2";

		SaveCurrentQuestDateParam("QuestTalk");
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "I told you so " + NPCharSexPhrase(NPChar, "", "a") + "I'm waiting for you on the ship!";
		link.l1 = "A... Of course...";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader(PGGQuestID);
		if (isPGGInitiative) {
			AddQuestRecord(PGGQuestID, "q1_Tavern");
		} else {
			AddQuestRecord(PGGQuestID, "q1_Tavern_1");
			AddQuestUserData(PGGQuestID, "sSex", GetSexPhrase("", "a"));
		}
		AddQuestUserData(PGGQuestID, "sShipName", NPChar.Ship.Name);
		AddQuestUserData(PGGQuestID, "sPGGName", GetFullName(NPChar));

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") 	LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 20);

		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";

		if (GetCharacterShipClass(PChar) > 4) // класс не подходит
		{
			PCharShipClassIsLowDialog(link, NPChar);

			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}

		if (GetCompanionQuantity(PChar) >= COMPANION_MAX) // компаньонов максимальное количество
		{
			MaxCompanionsExceededDialog(link, NPChar);

			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}

		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (isSetSail) {
			GeneratePGGQuestLocation(NPChar)

			Dialog.Text = "You have chosen a good time to step on my deck, Captain! " + 
			"I've got a good deal for you - take some loose goods.";
		} else {
			Dialog.Text = RandPhraseSimple(
				"Welcome aboard, Captain!",
				"Well, that's good, now I'm sure that there are no extra ears, my sailors are already aware."
			) + " The offer is to take a little unattended good.";
		}
		link.l1 = RandPhraseSimple(
			"What's so difficult about that? And why are you sharing this with me" + NPCharSexPhrase(NPChar, "", ", dear") + "?",
			"Unattended? " + NPCharSexPhrase(NPChar, "You're kidding, buddy", "You're kidding, honey") + "!"
		);
		link.l1.go = "Quest_1_Ship_1";

		break;

	case "Quest_1_Ship_1":
		Dialog.Text = RandPhraseSimple(
			"Well, there are people who consider him their own, but you need to convince them otherwise.",
			"Of course, we'll have to kill someone. But it's not a reason to refuse, is it?!"
		);
		link.l1 = PCharRepPhrase(RandSwear() + 
			RandPhraseSimple(
				"Get to the point!",
				"This already smells like a good massacre! Where are they?"
			),
			RandPhraseSimple(
				"I would like to know the details of your proposal.",
				"What exactly do you want to offer me?"
			)
		);
		link.l1.go = "Quest_1_Ship_Detail";

		link.l2 = PCharRepPhrase(
			RandPhraseSimple(
				"You're obscuring something. I don't want to get involved in this with you!",
				"It looks simple, but I don't believe you! Do you want to rake in the heat with someone else's hands? I disagree!"
			),
			RandPhraseSimple(
				"The offer is tempting, but I have to refuse.",
				"No, I have not taken anyone else's since childhood, I prefer to be given. I'll pass."
			)
		);
		link.l2.go = "Quest_1_Ship_Refuse";
		break;

	case "Quest_1_Ship_Detail":
		while (PChar.GenQuest.PGG_Quest.Island == "") GeneratePGGQuestLocation(NPChar);
		sTmp = "A caravan belonging to " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", transporting ";
		PChar.GenQuest.PGG_Quest.Goods.Text = GetStrSmallRegister(XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name + "Acc"));
		sTmp += PChar.GenQuest.PGG_Quest.Goods.Text;

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "StLucia")
		{
			sLoc = GetConvertStr(PChar.GenQuest.PGG_Quest.Island, "LocLables.txt");
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}

		if (sti(PChar.GenQuest.PGG_Quest.Template))
		{
			sTmp +=	", will pass near " + sLoc + " by the " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + ", they had to deviate from their usual route.";
		}
		else
		{
			sTmp += ", got caught in a storm near " + sLoc + " and went to the bottom. But they managed to save part of the cargo and landed in " + 
				GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + ". They are now waiting for their squadron to arrive.";
		}

		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear() + 
			RandPhraseSimple(
				"Don't delay, tell me everything quickly!",
				"I'm not wrong about you. What else do you know?"
			),
			RandPhraseSimple(
				"Very interesting, go on!",
				"I'm all ears!"
			)
		);
		link.l1.go = "Quest_1_Ship_Detail_1";

		link.l2 = PCharRepPhrase(
			RandPhraseSimple(
				"It's not a bad deal, but I'll refuse. It doesn 't make sense to me to fight with " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + ".",
				"A caravan? Unattended? There are a thousand soldiers with him! That won't do. I'm leaving."
			),
			RandPhraseSimple(
				"No, sir, I'm not fighting with " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", I'm not interested.",
				"My answer is no! I'm not going to spoil relations with " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + "!"
			)
		);
		link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");

		if (sti(PChar.GenQuest.PGG_Quest.Template))
		{
			AddQuestRecord(PGGQuestID, "q1_Detail_A");
		}
		else
		{
			AddQuestRecord(PGGQuestID, "q1_Detail_B");
		}
		AddQuestUserData(PGGQuestID, "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData(PGGQuestID, "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData(PGGQuestID, "sColony", sLoc);
		AddQuestUserData(PGGQuestID, "sShore", GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
		break;

	case "Quest_1_Ship_Detail_1":
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Through " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " the caravan will leave and we will not be able to catch up with them.",
				"We have exactly " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " to cut them out and pick up the loot!"
			),
			RandPhraseSimple(
				"At our disposal " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " for the whole operation.",
				"We should hurry up, " + PChar.Name + ". We only have " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + "."
			)
		);
		link.l1 = RandPhraseSimple(
			"We'll make it! We sail today.", 
				"We'll make it! We sail today.", 
			"We'll make it! We sail today.", 
			"Let's not delay. Order them to sail today."
		);
		link.l1.go = "Exit_Quest_1_Accept";

		AddQuestRecord(PGGQuestID, "q1_Accept");
		AddQuestUserData(PGGQuestID, "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));

		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "Let's not delay! Let's go!";
		link.l1 = "Let's go!";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		ReOpenQuestHeader(PGGQuestID);

		PGG_Disband_Fleet(NPChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1AcceptedQuestDeleteFantom("");
			Map_ReleaseQuestEncounter(NPChar.id);
			group_DeleteGroup(NPChar.id+"_Group");
			if (sti(PChar.GenQuest.PGG_Quest.Template))
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.CompanionEnemyEnable = true;
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);

			SetBaseShipData(NPChar);
			DeleteAttribute(NPChar, "ship.sails");
			RepairMasts(NPChar);
			DeleteAttribute(NPChar, "ship.blots");

			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear() + "You disappoint me, Captain. And you thought that I would invite you to "+ RandPhraseSimple("Sunday Mass?!!", "children's matinee!??"));
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"It's your business " + NPCharSexPhrase(NPChar, "", "dear") + ". And it's mine to decide.",
				"I don't want to dry in the sun because of a couple of piastres."
			),
			RandPhraseSimple(
				"My decision is final, Captain.",
				"We have nothing more to talk about."
			)
		);
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord(PGGQuestID, "q1_Close");
			AddQuestUserData(PGGQuestID, "sSex", GetSexPhrase("xia", "as"));
			CloseQuestHeader(PGGQuestID);
			
			DeleteAttribute(NPChar, "AlwaysFriend");
			SaveCurrentQuestDateParam("QuestTalk");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Come on, everything will go like clockwork and no one will know. We'll slaughter everyone.",
				"I told you information, and you want to do it yourself? Fuck you!"
			),
			RandPhraseSimple(
				"Where are you going in a hurry, Captain? Surely not to the authorities?",
				"It's very unwise to get into a tiger's den and think that you can easily get out of there."
			)
		);
		link.l1 = PCharRepPhrase(RandSwear() + 
			RandPhraseSimple(
				"Get to the sea devil! I'm captain " + GetFullName(pchar) + ", and you don't order me! I'm leaving!",
				"By the devil, you're pissing me off!"
			),
			RandPhraseSimple(
				"I am not interested in your proposal, and there is nothing more to talk about. Goodbye.",
				"I guess we have nothing more to talk about. I have things to do."
			)
		);
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear() + PCharRepPhrase(
			RandPhraseSimple(
				"Grab "+ GetSexPhrase("him", "her") +"! Tie "+ GetSexPhrase("him", "her") +" to the cannon! Let's see what color is guts!!!",
				"Hey, Johnny! Henderson! Grab the bastard! Don't let "+ GetSexPhrase("him", "her") +" go to the boat!!!"
			),
			RandPhraseSimple(
				"It's a pity, Captain! I hope you'll feel comfortable in our hold. Well, then we'll decide what to do with you.",
				"White slaves don't live long, Captain, so decide: either Hands will shoot you in the head with a musket, or you will spend the rest of your life in the quarries."
			)
		);
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"I'm going to make you eat your filthy insides, " + GetFullName(NPChar) + "!!!",
				"Get out of the way! The bastards! I'll split my head open like a rotten pumpkin!"
			),
			RandPhraseSimple(
				"Your offer is unacceptable... And very unwise!!!",
				"And you are not very hospitable... Get out of the way!!!"
			)
		);
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
		GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);

		sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);

		//группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(PChar, "questTemp.PGGContra.Know")) sTmp = "PGGTmp";
		else sTmp = "PGGQst";
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(PChar, true);
		break;

	case "Quest_1_Time2Late":
		DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)], "DisableEncounters");
		chrDisableReloadToLocation = false;
		SaveCurrentQuestDateParam("QuestTalk");

		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Thunder and lightning! We're too late! And it's all because of you, lazy oafs! There's nothing to share with you now, " + GetFullName(PChar) + ". Raise the staysail! Poison Mars little by little! ",
				"So, " + GetFullName(pchar) + ", I shouldn't have connected with you. The loot flowed through my fingers like water. Goodbye!"
			),
			RandPhraseSimple(
				"They're gone! Your sluggishness is to blame for everything! You and I are not on the same path, " + GetFullName(PChar) + ".",
				"We won't catch up with the caravan, we can dry the oars. I shouldn't have contacted you! Goodbye."
			)
		)
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"And to hell with this caravan! Pearl fishers are no worse, but there is no risk!",
				"Luck is with us, it's not evening yet! The sea is full of pathetic hucksters waiting for us to take their money!"
			),
			RandPhraseSimple(
				"It's really a pity that such a brilliant operation ended in a complete fiasco! Goodbye!",
				"Man suggests, but God disposes... Goodbye!"
			)
		);
		link.l1.go = "Exit_Quest_1_2Late";

		AddQuestRecord(PGGQuestID, "q1_Time2Late");
		CloseQuestHeader(PGGQuestID);
		break;

	case "Exit_Quest_1_2Late":
		LAi_SetPlayerType(PChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(PChar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck") PChar.quest.Munity = "Deads";
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;
		SaveCurrentQuestDateParam("QuestTalk");

		//не взяли груз...
		PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Bloodthirsty"+ GetSexPhrase("You bastard", "That's rubbish") +"! Everything went down to the sea devil! " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " piastres on a barrel, and I don't want to see you anymore!",
				"You imagined yourself Admiral Nelson? You've sunk all loot, "+ GetSexPhrase("idiot", "fool") +"! Give me " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " piastres and get out!"
			),
			RandPhraseSimple(
				"You decided to make a war here! This is absolutely no good! I guess we'll forget everything if you pay us " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " piastres.",
				"Your methods are unacceptable in this kind of business! You've failed the whole thing! Immediately pay our share in the amount of " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " piastres and go to all four sides! "
			)
		);
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"If it wasn't for me, you'd be feeding crabs right now " + NPCharSexPhrase(NPChar, "", "a") + NPCharSexPhrase(NPChar, ", greedy image!", "You're a clumsy monkey!"),
				"It would have been better to let the flagship board your trough, then you would have been already on the bottom and did not poison the air! "
			),
			RandPhraseSimple(
				"Your demands are inappropriate, and your insinuations are insulting!",
				"There was no contract for a penalty, therefore, I will not pay!"
			)
		);
		link.l1.go = "Quest_1_NotPay";

		if (sti(PChar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
		{
			link.l2 = PCharRepPhrase(
				RandPhraseSimple(
					"I can't give you a fight right now, and you know it! Choke on your piastres! Here!",
					"Piastres!!! Well, fortune is not on my side right now. I agree."
				),
				RandPhraseSimple(
					"Your demands are outrageous, but I don't seem to have a choice.",
					"Your appetites are excessive, but I have to agree!"
				)
			);
			link.l2.go = "Exit_Quest_1_Failed";
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) <= MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3)) {
			AddQuestRecord(PGGQuestID, "q1_Fail");
			break;
		}

		PChar.GenQuest.PGG_Quest.Ok = 1;
		Dialog.Text = PCharRepPhrase(
			"A hot deal! The goods amounted to " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".",
			"Well done, Captain! The goods amounted to " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + "."
		);
		DeleteAttribute(PChar, "PGGShoreQuest");
		int greedyPGG = 0;
		string greed = "";
		if (GetCharacterShipClass(NPChar) > GetCharacterShipClass(PChar))
		{
			PChar.GenQuest.PGG_Quest.Parts = (GetCharacterShipClass(NPChar) - GetCharacterShipClass(PChar));
			i = sti(PChar.GenQuest.PGG_Quest.Parts)+2-greedyPGG;
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
		}
		else
		{
			if (makeint(NPChar.reputation) < 40 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && drand(200) > sti(GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)))
			{
				greedyPGG = 2;
				greed = "And I don't advise you to mess around.";
				NPChar.Greed = true;
			}
			PChar.GenQuest.PGG_Quest.Parts = (GetCharacterShipClass(PChar) - GetCharacterShipClass(NPChar));
			i = sti(PChar.GenQuest.PGG_Quest.Parts)+2+greedyPGG;
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken)) - MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
		}

		Dialog.Text = Dialog.Text + PCharRepPhrase(" My share is ", " The share attributable to my ship is ") + PChar.GenQuest.PGG_Quest.Goods.Part + ". "+greed;
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Fair enough! The boats are already being loaded!", 
				"Yes, that's right... A deal is more expensive than money."
			),
			RandPhraseSimple(
				"Your calculations are correct. I agree.", 
				"You are impeccable in the division."
			)
		);
		link.l1.go = "Exit_Quest_1_End";

		if (!CheckAttribute(NPChar, "Greed")) {
			link.l2 = PCharRepPhrase(
				RandPhraseSimple(
					"And you still demand your share? Yes, you should be strung up on the yard and not delay!",
					"A share? It's every man for himself here, and if you didn't get anything, then that's your problem!"
				),
				RandPhraseSimple(
					"I don't think you can count on anything.",
					"My answer is no! I'm not going to share with " + NPCharSexPhrase(NPChar, "different crooks", "different scum") + "!"
				)
			);
		} else {
			link.l2 = "Are you trying to trick me? In that case, I'm taking everything for myself!";
		}
		link.l2.go = "Quest_1_NotPay";
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"No, that's not it! I won't argue! Goodbye!",
				"Let's not shed blood and aggravate the failure! You'll have better luck next time!"
			),
			RandPhraseSimple(
				"Well, goodbye, Captain, I'm not in a position to insist...",
				"The damage to my ship and the losses do not allow me to insist on a fair solution to the issue. I'll leave it on your conscience, Captain!"
			)
		);
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Fair wind!", 
				"Seven feet under the keel!"
			),
			RandPhraseSimple(
				"Goodbye! I think the fresh sea air will do you good!",
				"I hope your failures don't make your character even more obnoxious, goodbye!"
			)
		);
		link.l1.go = "Exit_Quest_1_Failed";

		PChar.GenQuest.PGG_Quest.Stage = -1;

		if (!CheckAttribute(NPChar, "Greed"))	ChangeCharacterReputation(PChar,-20);
		else	NPChar.PGG_Hunter = true;
		DeleteAttribute(NPChar, "Greed");

		bOk = makeint(NPChar.reputation) < 40 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(
				RandPhraseSimple(
					"You don't understand! With this you could buy your own life! Grab this "+ GetSexPhrase("bastard", "bastard") +"!",
					"You probably think you're being joked with? We'll let you under the keel, and you'll immediately become more accommodating!"
				),
				RandPhraseSimple(
					"We'll have to shorten your life, Captain! If you don't want to be nice, get to know Saint Martin!",
					"You leave me no choice, " + GetFullName(PChar) + "! I'll take mine, whether you want it or not!"
				)
			);
			link.l1 = PCharRepPhrase(
				RandPhraseSimple(
					"By the devil, you're going to pay for this!!!",
					"Yho-ho! Come and get me, Captain " + GetFullName(PChar) + "! "
				),
				RandPhraseSimple(
					"The incision will be deep and long! ",
					"Do you want to die right away or suffer a little?"
				)
			);
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord(PGGQuestID, "q1_FailPay");
			AddQuestUserData(PGGQuestID, "sSex", GetSexPhrase("", "a"));
			AddQuestUserData(PGGQuestID, "sSex1", GetSexPhrase("en", "on"));
		}
		ChangeCharacterReputation(NPChar, 10);
		CloseQuestHeader(PGGQuestID);
		RemoveCharacterCompanion(PChar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -10);

		LAi_SetImmortal(NPChar, true);
		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "I don't want to do business with you anymore!";
		link.l1 = "And you don't need to.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "Today we sail to " + XI_ConvertString("Colony"+NPChar.PGGAi.location.town) + "drink up the loot! If you want, join us! Anyway, it's nice doing business with you! Good luck.";
		link.l1 = "And you.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(PChar, NPChar);

		ChangeCharacterReputation(NPChar, -5);
		LAi_LockFightMode(PChar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");

		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		if (PChar.location != "Ship_Deck") sTmp = "sea";
		NPChar.location = PChar.location;

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(PChar, true);
		break;

	case "Exit_Quest_1_End":
		DeleteAttribute(NPChar, "Greed");
		RemoveCharacterCompanion(PChar, NPChar);
		ChangeCharacterReputation(PChar, 5);
		PGG_ChangeRelation2MainCharacter(NPChar, 30);
		NPChar.PGGAi.location.town = PGG_FindRandomTownByNation(sti(NPChar.nation));
		NPChar.PGGAfterShare = true;
		NPChar.PGGAi.AfterSail.TaskCounter = 0;
		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
		PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
		PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		AddQuestRecord(PGGQuestID, "q1_OkShare");
		CloseQuestHeader(PGGQuestID);

		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		SaveCurrentQuestDateParam("QuestTalk");
		Dialog.Text = PCharRepPhrase(
			NPCharSexPhrase(NPChar, "It was a real massacre, it's a pity the girls weren't with them.", "A real massacre, knipel in my ass!, it's a pity, it ended quickly") + "! The goods amounted to " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".", 
			"Not bad, Captain! The goods amounted to " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + "."
		);

		PChar.PGGShoreQuest = true;
		PChar.GenQuest.PGG_Quest.Parts = 2;
		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
    SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		
		Dialog.Text = Dialog.Text + " My share is " + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Fair enough, damn me!", 
				"Yes, that's right, damn me!"
			),
			RandPhraseSimple(
				"Your calculations are correct. I agree.", 
				"You are impeccable in the division."
			)
		);
		link.l1.go = "Exit_Quest_1_End";

		break;
//===================================
//              Exits
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Exit_PIRATES":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetPlayerType(PChar);
		break;

	case "Exit_2":
		if (CheckAttribute(PChar, "GenQuest.PGG_Quest")) DeleteAttribute(PChar, "GenQuest.PGG_Quest");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		NPChar.willDie = true;
		CloseQuestHeader("Gen_StrangeInfo");
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(PChar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}

void ContrabandDialog(aref link) {
	Dialog.text = "Listen, get out of here! You 'll rip it off " + GetSexPhrase("A deal, and I'll rip your heart out!", "I care, and I'll squeeze your filthy teeth out!");
	link.l1 = RandPhraseSimple("You dare threaten me, " + GetSexPhrase("the dog", "the creature") + "?", GetSexPhrase("You'll choke on your words, you rascal!", "I'm going to cut you into straps, bitch!"));
	link.l1.go = "Exit_Smugglers_Fight";
	link.l2 = "Come on, I know what business is. See you later.";
	link.l2.go = "Exit";
}

void MaxCompanionsExceededDialog(aref link, ref NPChar) {
	Dialog.Text = RandPhraseSimple("It looks like you've had enough companions already.", "You already have a lot of ships. Why do you need another one?");
	link.l1 = "yeah... Maybe you're right.";
	link.l1.go = "exit";
}

void NotEnoughMoneyDialog(aref link, ref NPChar) {
	Dialog.Text = RandSwear() + "Was it a joke? The wind is whistling in your pockets!"
	link.l1 = "It's true... I'll go.";
	link.l1.go = "exit";
}

void PGGNoShipDialog(aref link, ref NPChar) {
	Dialog.Text = "Yes, I'm left without a ship.";
	link.l1 = RandSwear() + "Then we'll talk later about how you get the ship.";
	link.l1.go = "exit";
}

void PCharNoShipDialog(aref link, ref NPChar) {
	Dialog.Text = "What do you want me to do? Get the boat first, then we'll talk!";
	link.l1 = RandSwear() + "Well, you don't have to!";
	link.l1.go = "exit";
}

void PCharShipClassIsLowDialog(aref link, ref NPChar) {
	Dialog.Text = "Is the matter with you!?? Find a decent ship first! Well, your shell only needs to carry mail...";
	link.l1 = RandSwear() + "Well, you don't have to!";
	link.l1.go = "exit";
}

void PCharRankLowDialog(aref link, ref NPChar) {
	Dialog.Text = "Is the matter with you!?? Gain experience first!";
	link.l1 = RandSwear() + "Well, you don't have to!";
	link.l1.go = "exit";
}

void PGGQuestNotEnoughtTimePassedDialog(aref link, ref NPChar) {
	Dialog.Text = NPCharRepPhrase(NPChar, 
		"No business today, get lost.", 
		"Sorry, I can't offer anything."
	);
	link.l1 = PCharRepPhrase(RandSwear(), "Well, see you later.");
	link.l1.go = "exit";
}

bool PGGQuestAlreadyActive(aref link, ref NPChar) {
	int currQuestPGGid = GetCharacterIndex(PChar.GenQuest.PGG_Quest.PGGid);
	if (currQuestPGGid < 0 || currQuestPGGid > TOTAL_CHARACTERS) {
		DeleteAttribute(PChar, "GenQuest.PGG_Quest");
		return false;
	}

	ref currQuestPGG = &characters[currQuestPGGid];
	Dialog.Text = "What do you need me for, I wonder? Come back as soon as you finish all the business with the cap " + GetFullName(currQuestPGG) + "!";
	link.l1 = "Indeed, I forgot it...";
	link.l1.go = "exit";
	return true;
}

void GeneratePGGQuestLocation(ref NPChar) 
{
	PChar.GenQuest.PGG_Quest.Template = drand(1);
	if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
	{
		PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
	}
	PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
	PChar.GenQuest.PGG_Quest.Nation = rand(3);

	// генерим остров и пляж, пока не найдем пустой(без квеста)
	PChar.GenQuest.PGG_Quest.Island.Shore = "";
	string sCurIsland = GetCharacterCurrentIslandId(pchar);

	while(PChar.GenQuest.PGG_Quest.Island.Shore == "" || 
		PChar.GenQuest.PGG_Quest.Island == "Pearl" || 
        PChar.GenQuest.PGG_Quest.Island == "Panama" ||		
		PChar.GenQuest.PGG_Quest.Island == "KhaelRoa" ||
		PChar.GenQuest.PGG_Quest.Island == "Reefs" ||
		PChar.GenQuest.PGG_Quest.Island == sCurIsland)//фикс - не даём квест на этот остров
	{
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomUninhabitatIsland();
		} 
		else 
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
	}
	
	PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);

	if (isSetSail) PChar.GenQuest.PGG_Quest.Days = rand(4) + 5;
	else PChar.GenQuest.PGG_Quest.Days = GetMaxDaysFromIsland2Island(GetCharacterCurrentIslandId(PChar), PChar.GenQuest.PGG_Quest.Island) + 1;

	PChar.GenQuest.PGG_Quest.Goods = GOOD_SLAVES + drand(2);
	
	PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;
	NPChar.Nation.Bak = NPChar.Nation;
}