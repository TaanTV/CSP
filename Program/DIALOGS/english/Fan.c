
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
		case "FirstMeet":
			dialog.text = "Wow, the great champion of the arena himself came out to meet me! May I follow you? Please, please!";
			link.l1 = "So be it... Bye.";
			link.l1.go = "exit";
			LAi_CharacterPlaySound(NPChar, "Fan_FirstMeet");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			Log_info("The most devoted fan of the Scam Games Arena champion is following you from now on.");
		break;

		case "exit_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "", "", "", "OpenTheDoors", -1);
			npchar.LifeDay = 0;
			pchar.ScamDestroyed = true;
		break;

		case "exit_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			InterfaceStates.DisFastTravel = false;
		break;

		case "Scared":
			dialog.text = "What are we doing here?! We must escape from here immediately!";
			link.l1 = "Hmm, this is the first time I've seen such a reaction from you. Why would you suddenly...?";
			link.l1.go = "Scared_2";
			LAi_CharacterPlaySound(NPChar, "Fan_Scared");
		break;

		case "Scared_2":
			SpawnDeadGodSkulls();
			DialogExit();
		break;

		case "DeadGod":
		if (CheckCharacterItem(pchar, "skullAztec"))
		{
			dialog.text = "Oh, who do I see... Are you still carrying my gift?";
			link.l1 = "Miktlantekutli, I have a request for you. Will you listen?";
			link.l1.go = "DeadGod_2";
		}
		else
		{
			dialog.text = "What is a mortal doing in a Sacrificial temple? I demand an explanation!";
			link.l1 = "I don't know who you are, but the sight of you scares me already.";
			link.l1.go = "DeadGod_2";
		}
		break;

		case "DeadGod_2":
			if (CheckCharacterItem(pchar, "skullAztec"))
			{
				dialog.text = "Let me guess. Is that weirdo with you? Get rid of him?";
				link.l1 = "To the point. Will you help me?";
				link.l1.go = "DeadGod_3";
			}
			else
			{
				dialog.text = "Wait a minute... Who else is with you? It smells very familiar. Isn't that the idiot I gave immortality to for fun, seeing his utter worthlessness?";
				link.l1 = "If you help me get rid of him, I'll do anything.";
				link.l1.go = "DeadGod_3";
			}
		break;

		case "DeadGod_3":
			dialog.text = "Never mind... Ready! He will never come back here, to the sinful earth. He has to go.";
			link.l1 = "How can I repay you?";
			link.l1.go = "DeadGod_4";
			ref rChar = CharacterFromID("ScamCharacter");
			rChar.LifeDay = 0;
			ChangeCharacterAddressGroup(rChar, "none", "", "");
			Log_info("The most devoted fan of the Scam Games Arena champion is forever behind you.");
		break;

		case "DeadGod_4":
			dialog.text = "Don't mess around here. There are rarely any living people in Tenochtitlan besides my priests, so I'll watch what you do here.";
			link.l1 = "I will try not to upset you unnecessarily. Goodbye!";
			link.l1.go = "exit_2";
		break;

		case "CoolStory":
			string coolstory = "";
			switch (rand(20))
			{
				case 0:
					coolstory = "You should definitely add a list of unique quests to the encyclopedia and a description of which cities you can take them to."
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_0");
				break;
				case 1:
					coolstory = "Предложение насчёт небольшого баланса кораблей. Сейчас бермудка корабля очень выгодна и в какой-то степени слишком хороша. Речь прежде всего о калибрах. Перескакивание с 24ф на 32ф это довольно сильно. Поэтому предложение немного сбалансировать этот аспект, чтобы это всё ещё было отличным апгрейдом, но без такого апа, который есть сейчас. На примере любого корабля с 24ф. Сейчас бермудка апает с 24 до 32. Предложение сделать промежуточный калибр 28ф. всё ещё это будет хорошее усиление, но не такое сильное, как сейчас. Тоже самое сделать для других калибров, например вместо с 16 до 20 добавить промежуточный 18ф калибр. Уверен это окажет нормальное влияние на баланс."
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_1");
				break;
				case 2:
					coolstory = "
";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_2");
				break;
				case 3:
					coolstory = "The proposal is to add the opportunity for smugglers to order the necessary guns for themselves. The price will be more expensive than usual. It will also be useful for those who play for the pirate nation.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_3");
				break;
				case 4:
					coolstory = "I personally think skeletons in the role of the main characters are a failed idea. No one wants to code and write a story for them, so there is no point in them. At most, it would be possible to leave one such character as a unique character, but only on condition of at least a short plot, as well as a unique character model in the form of a living person after rebirth.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_4");
				break;
				case 5:
					coolstory = "In a good way, the Dog should be returned to the CPC. Whisper to give another thorn instead of the Dog. The housing needs to be removed from the GPC and left for the future. According to the type of FD, she needs her own separate quest. There will be a quest with a Black Beard for the MC. At least some people talked about it. Although I don't like the MKA either. Moreover, I have seen some models of the MKA, which are much better. It's a pity that they need to be textured and so on.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_5");
				break;
				case 6:
					coolstory = "Слишком много кораблей в паке. Хрен с ними с плохими моделями. Многие можно заменить. Но многие корабли просто ненужны. Они просто банально ни о чем. Зачем в игру нужно добавлять 10 видов шлюпов ненужных, когда будет три нормальных и адекватно сбалансированных?";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_6");
				break;
				case 7:
					coolstory = "Решение с бесполезностью офицеров в лейте простое: 1. Сделать некоторые перки уникальными только для офицеров без возможности взять их для гг. Для этого можно ввести новые перки. 2. Сделать строгую привязку офицеров к своей специализации. Чтобы торгаш мог быть только торговцем без возможности быть абордажником. Так же и с другими должностями.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_7");
				break;
				case 8:
					coolstory = "If you want to help introduce something new, then it is much more useful for everyone to introduce some new animation of strikes than to add such game with children to Corsairs. We've seen enough of these kids in Skyrim. There is no point in such games, especially when they play the role of ordinary dummies. And to play for such horror, and even on a Storm - no thanks!";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_8");
				break;
				case 9:
					coolstory = "Вообще разделение по названиям не так просто сделать. Удачное решение, как сейчас - это когда названия некоторых кораблей разделены по нациям. То есть, английский галеон, испанский и так далее. А вот от названий по типу тяжёлый боевой флейт нужно, как-то избавляться. Корабли 1 класса можно разделить по рангам на линейные корабли в зависимости от количества пушек.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_9");
				break;
				case 10:
					coolstory = "All this is game, all these repaints that are decades old. There will be nothing without new models.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_10");
				break;
				case 11:
					coolstory = "The whole problem is that the boat is interesting in naval combat. It's really interesting to fight. But in combat on land, sometimes it is very suffocating. Someone suggested a long time ago that it was possible to divide the complexity into two sliders. Difficulty on land and at sea. Then it would be possible to safely set the bar for naval battles and, for example, the difficulty is less for land combat. Then there would be no complaints about the stifling battles on land.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_11");
				break;
				case 12:
					coolstory = "Add England, Holland and Spain to their unique ships as a reward for completing the national line. It's a little unfair that only France has its own Soleil. Others can also pick up similar ships. Make them not mega monsters, but so that each has its own uniqueness in characteristics.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_12");
				break;
				case 13:
					coolstory = "Remove the pointless drain of the Orion quest. I understand that maybe this was done earlier in order for the player to accidentally stumble upon this quest and so on. But many players will not even find out about him, as many simply will not want to take a job as an escort and, accordingly, may never even find out about this quest. To make a simple solution is to add a separate dialogue about rumors and work to the tavern keeper. This has already been done in many normal quests.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_13");
				break;
				case 14:
					coolstory = "A slightly strange, but understandable proposal is to remove pistols from skeletons. Maybe someone won't like it, since everyone is used to skeletons with four-barrel pistols and so on, but this is understandable from the point of view of common sense and even according to the lore of the game. Skeletons can't have serviceable weapons.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_14");
				break;
				case 15:
					coolstory = "At least Blood can extend the plot because he doesn't have it, but Whisper does. Also Grammon, Patterson and Diego.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_15");
				break;
				case 16:
					coolstory = "To begin with, all the key characters would like to make normal prologues. And it's strange to think about a global plot.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_16");
				break;
				case 17:
					coolstory = "Самое забавное, что даже на невозможно ближе к 30 рангу спокойно уничтожаются любые корабли. То есть даже на такой сложности гг всё равно имба. Но все же сейчас у ии появились апгрейды + защита корпуса. Так просто 3 классом первый класс уже не пробьешь.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_17");
				break;
				case 18:
					coolstory = "Вообще с балансом кораблей есть конечно проблемы. То, что полно так себе моделей это понятно, но замена модели лишь сделает кораблики покрасивее визуально, но не сделает их играбельными. Особенно таким страдают корабли 6 и 5 классов всякие шхуны, шлюпы, люггеры, которые просто очень слабы на фоне своих конкурентов в классе. К примеру тяжёлый шлюп в 6 вообще тянет на 5 класс. Остальные на его фоне просто дно. Ну и проблема в балансе 1 и 2 классов. На мой взгляд их чересчур много в игре. Всем нравятся красивые бои между кучей военных кораблей, но пожалуй перебор. Идеальный баланс, чтобы 2 и 1 класс встречались редко и только в самых сильных эскадрах. Тогда и игроку будет мотивация пытаться найти и захватить такие корабли.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_18");
				break;
				case 19:
					coolstory = "In general, it's a strange topic for officers. Anyway, for example, no one will appoint a tradesman as a boarder because of low skills. Therefore, all the talk for their imbecility is slightly far-fetched. The quest offers are also quest ones, that they are universal and many of them still need to be found.";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_19");
				break;
				case 20:
					coolstory = "In general, it would be nice to distribute all current OFS models by nation. So that, for example, pirates have only models of the appearance of pirates and sailors. And in the national cities there were officers in the appropriate uniforms. It's just that all the officers are just random right now. I wonder if they can prescribe a nation like PMC and MC?";
					LAi_CharacterPlaySound(NPChar, "Fan_CoolStory_20");
				break;
			}
			dialog.text = coolstory;
			link.l1 = "Amazing stories you tell, bro...!";
			link.l1.go = "exit_3";
		break;
	}
}

void SpawnDeadGodSkulls()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("FakeDeadmansGod", "mictlantecuhtli", "skeleton", "man", 100, PIRATE, 0, true));
    FantomMakeCoolFighter(sld, 100, 100, 100, "toporAZ", "pistol5", 3000);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "Temple_skulls", "goto", "goto2");
	LAi_SetActorTypeNoGroup(sld);
	LAi_SetImmortal(sld,true);
	sld.name = "Mictlantecutli";
	sld.lastname = "";
	sld.dialog.filename = "Fan.c";
	sld.dialog.currentnode = "DeadGod";
	LAi_group_MoveCharacter(sld, "player");
	LAi_ActorDialog(sld, pchar, "", 4.0, 0);
}
