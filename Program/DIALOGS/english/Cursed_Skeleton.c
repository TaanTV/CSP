// Генерируемый скелет-босс из пещеры
#include "DIALOGS\english\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	ref cursedLocLoad = &locations[reload_location_index];
	bool hungry = true;
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	//ref itm;
	int skullgen = drand(2)+1;
	string cursed_artifact = "sculMa"+sti(skullgen); // Квестовый предмет

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				scareOfficers(50);
				dialog.text = "How dare you disturb the peace in my tomb, mortal!? And you're rummaging through my stuff! It's worth teaching you a lesson.";
				npchar.quest.meeting = "1";
				link.l1 = "Damn, I thought that no one lives here. I'm sorry, I'm going to leave right now.";
				link.l1.go = "meeting_1";
				//Если мы пришли по церковному квесту
				if(CheckAttribute(cursedLocLoad, "DestroyGhost"))
				{
					link.l1 = "I'm here to rid this place of filth! Get out, unclean! In the name of God, I conjure...";
					link.l1.go = "meeting_2";
					break;
				}
				link.l3 = "Die, brat!";
				link.l3.go = "skel_fight";
				if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue") && pchar.questTemp.AnjelikaTichPrologue == "ATP")	//Sinistra Пролог Анжелика Тич
				{
					dialog.text = "Don't be afraid of me, I'm a good undead. Take what you want, don't deny yourself anything.";
					link.l1 = "(shock) Dear Mom!";
					link.l1.go = "AT_pr_Uhoju";
					npchar.lifeday = 0;
					DeleteAttribute(link, "l2");
					DeleteAttribute(link, "l3");
				}
				NextDiag.TempNode = "First time";
				break;
			}
			else if (npchar.quest.meeting == "2")
			{
				dialog.text = "I gave you a chance to save your miserable life, but you didn't take it. ";
				DeleteAttribute(pchar, "cursed.waitingSkull");
				LAi_SetPlayerType(PChar);



				link.l1 = "Devil, how did you end up here? Wait, I can still find your skull!";
				link.l1.go = "end_quest_battle";
				link.l2 = "Anchor me in the the..!";
				link.l2.go = "skel_fight";
				if(CheckCharacterItem(pchar, pchar.questTemp.Cursed.Item) && CheckAttribute(pchar, "cursed.Skullbought"))
				{
					dialog.text = "I know you have the skull. Give it to me.";
					link.l1 = "Take it and leave me alone at last!";
					link.l1.go = "end_quest";
					link.l2 = "What else. Now the skull is mine. Thanks for the tip, without you I wouldn't have found it.";
					link.l2.go = "end_quest_battle";
				}

			}
			else
			{
				dialog.text = "Any questions?";
				npchar.quest.meeting = "1";

				link.l1 = "When I return the skull to you, what are you going to do? Will you cancel the contract and accept death?";
				link.l1.go = "question";
				link.l2 = "I decided to retire you in a different, more efficient way!";
				link.l2.go = "skel_fight";
				link.l3 = "No.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = "I've been thinking about this for a long time. With the skull, I can regain my past life, my body. Maybe I'll even get a ship and get my notoriety back. No, I'm not exactly going to die.";
			link.l1 = "Okay, I'll go look for it.";
			link.l1.go = "question";
			link.l2 = "Even if this life is achieved at the cost of thousands of deaths of others? Well, no, I have to stop you!";
			link.l2.go = "skel_fight";
		break;
		case "end_quest_battle":
			dialog.text = "It's too late, I'll find a more accommodating seeker.";
			link.l1 = "Carramba!";
			link.l1.go = "skel_fight";
			if(CheckCharacterItem(pchar, pchar.questTemp.Cursed.Item) && CheckAttribute(pchar, "cursed.Skullbought"))
				{
					dialog.text = "You shouldn't have started this, no one has ever managed to defeat me in this form.";
					link.l1 = "I will be the first!";
					link.l1.go = "skel_fight";
				}

		break;

		case "end_quest":
			dialog.text = "Thank you. As I promised, you are free. As a reward for your efforts, I will even give you one book. There wasn't much to do in the long years that I've been in the cave, so I've read it over and over again. I must admit, it's a very interesting read. I managed to find something new for myself every time I read it.";
			TakeItemFromCharacter(pchar, pchar.questTemp.Cursed.Item);
			string book = PickAbook();
			GiveItem2Character(pchar, book);
			LAi_SetImmortal(npchar, true);
			link.l1 = "Wow, thank you!";
			CloseQuestHeader("CursedSkeleton");
			link.l1.go = "Exit_1";
		break;

		case "skel_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			npchar.SaveItemsForDead = true;
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			SetSkeletonsToLocation(cursedLocLoad);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			npchar.quest.meeting = "0";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DeleteAttribute(pchar, "cursed.Skullbought");
			CloseQuestHeader("CursedSkeleton");
            DialogExit();
		break;

		case "meeting_1":
			dialog.text = "Well, no, you can't get out that easily. I need help with something. If you manage, I will save your life and freedom. And what happens in case of failure or rejection, it's better for you not to know.";
			link.l1 = "And what kind of help do you need?";
			link.l1.go = "meeting_3";

			link.l2 = "I'd rather just cut you down!";
			link.l2.go = "skel_fight";
		break;

		case "meeting_2":
			dialog.text = "You have no chance in a fight with me. And your spells won't help here, and the Lord won't hear you.";
			npchar.quest.answer_1 = "true";
			TakeNItems(NPCHAR, "Chest_ammo", 2 + sti(pchar.rank)*0.1);
			TakeNItems(NPCHAR, "Chest_quest", 1 );
			link.l1 = "We'll see about that! Please, Lord, guide my hand so that I can smite this unclean one for your glory!";
			link.l1.go = "skel_fight";
		break;

		case "meeting_3":
			dialog.text = "You see, I wasn't always like this. In a previous life, I had my own ship, just like you. I will say more - I was a corsair, whose name inspired horror in all the colonies. However, it's been too long for anyone to remember.";
			link.l2 = "...";
			link.l2.go = "meeting_5";
			link.l1 = "Get to the point.";
			link.l1.go = "meeting_4";
		break;
		case "meeting_4":
			dialog.text = "Don't interrupt me, mortal! Otherwise your life will end here and now!";
			link.l1 = "I'm sorry, go on.";
			link.l1.go = "meeting_5";

			link.l2 = "I'm tired of this already. I'm going to put you out of your misery now!";
			link.l2.go = "skel_fight";
		break;
		case "meeting_5":
			dialog.text = "During my lifetime, I was lucky and collected a lot of valuable loot. And when I decided to retire, I was going to bury some of my loot in the chest next to you. There is nothing there now, of course, because I was viciously killed right here, without being given the opportunity to finish what I started.";
			link.l1 = "And who did it?";
			link.l1.go = "meeting_6";

			link.l2 = "This is all very interesting, but it's time for me to go to the ship, and for you to go to the other world!";
			link.l2.go = "skel_fight";
		break;
		case "meeting_6":
			dialog.text = "My own XO! I considered him my best friend, but he betrayed me, and also talked the team into it. It's all because of that damn skull, damn it.";
			link.l1 = "What kind of skull?";
			link.l1.go = "meeting_7";
		break;
		case "meeting_7":
			SelectCursedRendom();
			pchar.questTemp.Cursed.Item = cursed_artifact;
			dialog.text = "I managed to drunkenly make a deal with some guy with cat eyes. It occurred to me too late that it was a demon. He gave me "+ GetConvertStr("itmname_"+pchar.questTemp.Cursed.Item, "ItemsDescribe.txt") +" and he said that as long as I carry this item with me, my luck will not leave me.\nBut there is a price for everything. In order for the effect to continue, it is necessary to regularly send the souls of other people to the next world, otherwise a curse will take the place of luck, as a result of which I found myself in this position.";
			link.l1.go = "meeting_7_1";
		break;
		case "meeting_7_1":
			dialog.text = "In order to cancel the contract with the demon, the skull had to be buried away from living people. That's what I was going to do here. I guess I didn't kill for too long and caught myself too late, so I didn't notice how the positive effect of the skull changed to a negative one and turned my best friend against me. The worst thing is, you can't live a full life or die with this curse.";
			link.l1 = "As I understand it, you want to find this " + GetConvertStr("itmname_"+pchar.questTemp.Cursed.Item, "ItemsDescribe.txt") +"?";
			link.l1.go = "meeting_8";
		break;
		case "meeting_8":
			dialog.text = "Yes. And I even know where he might be. During my lifetime, my team and I sold the loot to a merchant from "+ XI_ConvertString("Colony" + pchar.questTemp.Cursed.TownId + "Gen") +". Surely my XO didn't realize the true value of this item and sold it along with the rest of my belongings. Go there immediately, I can't wait any longer.";
			link.l1 = "Okay...";
			link.l1.go = "meeting_9";
		break;
		case "meeting_9":
			dialog.text = "I'm giving you exactly one month to find the skull. If you don't, you'll be sorry. And don't think that once you get out of here, you're gonna get rid of me, and I've tied my soul to yours, so I'll have no problem finding you at the end of the world.";

			ReOpenQuestHeader("CursedSkeleton");
			AddQuestRecord("CursedSkeleton", "1");
			AddQuestUserData("CursedSkeleton", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CursedSkeleton", "sSex1", GetSexPhrase("ся", "ась"));
			AddQuestUserData("CursedSkeleton", "scityName", XI_ConvertString("Colony" + pchar.questTemp.Cursed.TownId));
			npchar.lifeday = 0;
			link.l1 = "Stop scaring me. I'll help you. I'm taking the course on "+ XI_ConvertString("Colony" + pchar.questTemp.Cursed.TownId + "Acc") +".";
			pchar.cursed.waitingSkull = true;
			link.l1.go = "exit";
		break;
		
		case "AT_pr_Uhoju":
			DialogExit();
			
			sld = CharacterFromID("CursedSkeleton")
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;


// <-- специальные реакции

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetWarriorType(NPChar);
			DialogExit();
		break;
		case "Exit_1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterAddress(npchar, "none", "");
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "cursed.Skullbought");
			chrDisableReloadToLocation = false;
			DialogExit();
		break;
	}
}

void SelectCursedRendom()
{
		int n, nation;
		int storeArray[MAX_COLONIES];
		int howStore = 0;
		for(n=0; n<MAX_COLONIES; n++)
		{
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
		nation = storeArray[drand(howStore-1)];
		pchar.questTemp.Cursed.TownId = colonies[nation].id;
		pchar.questTemp.Cursed.TraderId = colonies[nation].id + "_trader";

}

string PickAbook()
{
	int quality = 1;
	if (pchar.rank <= 10) quality = 1;
	if (pchar.rank >= 10) quality = 2;
	if (pchar.rank >= 20) quality = 3;
	if (pchar.rank > 30) quality = 4;
	return "book"+quality+"_"+sti(drand(13)+1);
}
