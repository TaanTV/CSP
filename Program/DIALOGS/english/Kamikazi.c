
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arAll;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Kamikazi":
			dialog.text = "...";
			link.l1 = "What the...";
			link.l1.go = "Kamikazi_2";
		break;

		case "Kamikazi_2":
			StopSound(0,0);
			chrDisableReloadToLocation = false;
			LAi_Explosion(NPChar,20);
			LaunchBlood(NPChar,1.0,true);
			LaunchBlast(NPChar);
			LaunchBlastGrenade(NPChar);
			ChangeCharacterAddress(npchar, "none", "");

			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			makearef(arAll, pchar.GenQuest.DestroyGang);
			pchar.GenQuest.DestroyGang = "Execute"; //флаг выполнил успешно
			pchar.Kamikazi = "Meet";
			string sTemp = GetFullName(&characters[GetCharacterIndex(arAll.MayorId)]);
			// судовой журнал
			AddQuestRecord("MayorsQuestsList", "22");
			// слухи
			AddSimpleRumour(LinkRandPhrase("You know, the governor " + sTemp + " instructed a certain "+ GetSexPhrase("to him captain", "to the sailor") +" " + GetMainCharacterNameDat() + " destroy a famous bandit named " + GetFullName(arAll) + ". And it seems that "+ GetSexPhrase("captain did", "she did") +"the governor's assignment...",
				""+ GetSexPhrase("Some brave captain volunteered", "Some brave girl volunteered") +" find and destroy a local bandit named " + GetFullName(arAll) + ". And it looks like captain did it!",
				"Ha, finally our governor took up the task of restoring order in the jungle - he instructed captain " + GetMainCharacterNameDat() + " to find the most famous bandit in the jungle and kill him. And you know, this bandit, " + GetFullName(arAll) + " is dead!"), sti(characters[GetCharacterIndex(arAll.MayorId)].nation), 5, 1);
			DialogExit();
		break;
	}
}
