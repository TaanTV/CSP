
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sBlade;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "simon_helper_bazar":
			dialog.text = "Присоединяйся, капитан! Чокнутый Саймон на халяву наливает, ты только подыграй ему маленько, если выпить хочешь.";
			link.l1 = "Конечно присоединюсь. А кто из вас Саймон?";
			link.l1.go = "1";
		break;

		case "1":
			dialog.text = "Да вот этот, в шляпе.";
			link.l1 = "Вот и славно.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "simon_helper_bazar";
		break;

		case "simon_bazar":
			dialog.text = "О, неофит! Приш"+GetSexPhrase("ёл","ла")+" поклониться Хозяину моря?";
			link.l1 = "Не совсем. Я приш"+GetSexPhrase("ёл","ла")+" поговорить о деньгах, что вы заняли у...";
			link.l1.go = "6";
		break;

		case "6":
			int KSM_DVR_Schitaem2 = pchar.Quest.KSM_DVR_Dengi.FindCitizenMoney;
			if(KSM_DVR_Schitaem2 < 10000) { KSM_DVR_Schitaem2 = 10000 + drand2(1000); }
			if(KSM_DVR_Schitaem2 > 30000) { KSM_DVR_Schitaem2 = 30000 + drand2(1000); }
			dialog.text = "Хозяин моря не нуждается в деньгах! Лучше выпей с нами и восславь МЕНЯ как подобает!";
			link.l1 = "Саймон, вы заняли " + KSM_DVR_Schitaem2 + " пиастров у ростовщика, лучше бы вам об этом вспомнить...";
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = "Ты мне надоел"+GetSexPhrase("","а")+", "+GetSexPhrase("назойливый червь","назойливая муха")+". Тебе пора умирать... Ребята, помогите "+GetSexPhrase("ему","ей")+"!";
			link.l1 = "Вот чёрт!";
			link.l1.go = "Draka";
		break;

		case "Draka":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("KSM_DVR_Saiman");
			LAi_SetActorType(sld);
			for (i=1; i<=3; i++)									//Количество
			{
				sld = CharacterFromID("KSM_DVR_SaimanOhrana_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "KSM_DVR_Pobeda");

			chrDisableReloadToLocation = true;
		break;

		case "dolg_bazar_1":
			dialog.text = "Благодарю вас, капитан "+pchar.name+".";
			link.l1 = "Какого чёрта вы убили этого чудака?";
			link.l1.go = "8";
		break;

		case "8":
			dialog.text = "Пуля - лучшее лекарство от безумия, капитан. Да и к тому же... Разве он не заслужил смерти, приказав убить вас?";
			link.l1 = "Пожалуй... Ну, раз вашими стараниями Саймон мёртв, вы и смотрите сколько денег он нам оставил.";
			link.l1.go = "Smotrim";
		break;

		case "Smotrim":
			DialogExit();
			LAi_Fade("", "");
			sld = CharacterFromID("Villemstad_usurer");
			LAi_SetActorType(sld);
			DoQuestCheckDelay("KSM_DVR_Smotrim_2", 0.5);
		break;

		case "dolg_bazar_2":
			int KSM_DVR_Dengi = sti(pchar.Quest.KSM_DVR_Dengi.FindCitizenMoney);
			int KSM_DVR_Nashli = KSM_DVR_Dengi - (KSM_DVR_Dengi / 4);
			dialog.text = "Отлично! Здесь больше " + KSM_DVR_Nashli + " пиастров!";
			link.l1 = "И сколько из них принадлежит мне?";
			link.l1.go = "9";
		break;

		case "9":
			int KSM_DVR_Dengi2 = pchar.Quest.KSM_DVR_Dengi.FindCitizenMoney;
			int KSM_DVR_Nashli2 = KSM_DVR_Dengi2 - (KSM_DVR_Dengi2 / 4);
			int KSM_DVR_Nagrada = KSM_DVR_Nashli2 / 2;
			dialog.text = "" + KSM_DVR_Nagrada + " пиастров, капитан. Берите, они ваши.";
			link.l1 = "Благодарю вас.";
			link.l1.go = "Konets";
			AddMoneyToCharacter(pchar, sti(KSM_DVR_Nagrada));
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Konets":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);

			AddQuestRecord("KSM_DVR", "2");
			CloseQuestHeader("KSM_DVR");
			pchar.questdata.DengiRost = 1;
			DeleteAttribute(pchar, "Quest.KSM_DVR_Dengi");

			PChar.quest.KSM_DVR_RostovshikDomoy.win_condition.l1 = "ExitFromLocation";
			PChar.quest.KSM_DVR_RostovshikDomoy.win_condition.l1.location = PChar.location;
			PChar.quest.KSM_DVR_RostovshikDomoy.win_condition = "KSM_DVR_RostovshikDomoy";
		break;
	}
}
