//navy
#include "DIALOGS\english\Common_Duel.c"
// boal 29.05.04 даём карту клада
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	aref   item;
	bool   ok;

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	ProcessDuelDialog(NPChar, link, Diag); //navy

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "Map_NotBuy":
            dialog.Text = "When you get rich, I'll wrap you in a rag and a handkerchief.";
			Link.l1 = "Stay here, I'll be right there!";
			Link.l1.go = "exit";
		break;

		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "Pss... listen. I have something for you...";
			Link.l1 = "What do you mean?";
			Link.l1.go = "map_treasure_1";
		break;

		case "map_treasure_1":
            ok = (GetCharacterItem(Pchar, "map_part1")>0)  && (GetCharacterItem(Pchar, "map_part2")>0);
            if (GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "It's a drink!! And-ic... Have a drink with me!";
    			Link.l1 = "Oh, come on. I was thinking that you're serious.";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "I have something special for you at a reasonable price.";
    			Link.l1 = "And what is it?";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "Oh, come on. I don't have time.";
    			Link.l2.go = "exit";
			}
		break;

		case "map_treasure_2":
            dialog.Text = "This is a great map. You can't find one in the store. It shows where the treasures are buried! I can't get there myself, but the map is definitely authentic. I swear.";
			Link.l1 = "It's very interesting. How much are you asking for?";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "Oh, come on. I don't have time.";
			Link.l2.go = "exit";
		break;

		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
            dialog.Text = "Humble "+Pchar.GenQuest.TreasureMoney+" piastres.";
			Link.l1 = "Come on, wrap it in a nice cloth.";
			if (sti(Pchar.Money) >= sti(Pchar.GenQuest.TreasureMoney))
			{
			   Link.l1.go = "map_treasure_buy";
			}
			else
			{
			   Link.l1.go = "Map_NotBuy";
			}
			Link.l2 = "It's very expensive. No need.";
			Link.l2.go = "exit";
		break;

		case "map_treasure_buy":
            dialog.Text = "Take it. Now you will definitely get rich!";
			Link.l1 = "Thank you!";
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(Pchar.GenQuest.TreasureMoney));
			GiveItem2Character(pchar, "map_full");
			AddMoneyToCharacter(NPChar, sti(Pchar.GenQuest.TreasureMoney));
			Items_FindItem("map_full", &item);
			if ( sti(item.MapTypeIdx) == -1 ) npchar.fakemap = 1; else npchar.fakemap = 0;
			//FillMapForTreasure(item);
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;

		case "Temp_treasure":
            dialog.Text = "Let's have a drink? And-ic... It's a good rum here!";
			Link.l1 = "There's no time!";
			Link.l1.go = "exit";
            if (npchar.fakemap == "1")
            {
    			Link.l2 = "You sold me a fake!!";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;

		case "Temp_treasure_1":
			NPChar.SaveItemsForDead = true;
            dialog.Text = "And who are you? And-ic... I don't know you and I don't want to know anymore.";
			Link.l1 = "Well, don't!";
			Link.l1.go = "exit";
			Link.l2 = "You sold me this fake!!! I'm going to...";
//			Link.l2.go = "tavern_keeper";
//			Diag.TempNode = "Temp_treasure";
			Link.l2.go = "outraged"; //navy -- дуэли!!!
			Diag.TempNode = "let_s_duel";
			npchar.LifeDay = 1; // чтоб не слетел на выходе
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;

		case "tavern_keeper":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}
