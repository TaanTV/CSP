
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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

		case "First time":							//Авторы Nikk и Sinistra
			dialog.text = "Ishik doesn't catch pearls?";
			link.l1 = "Are you talking to me?";
			link.l1.go = "Знакомство_1";
		break;
		
		case "Знакомство_1":
			dialog.text = "Kuali was a good warrior, not a stupid one.";
			link.l1 = "There are no fools here, what do you want from me?";
			link.l1.go = "Знакомство_2";
		break;
		
		case "Знакомство_2":
			dialog.text = "Kuali gave his macuahuitl man tunaku catches pearls, macuahuitl wants back.";
			link.l1 = "Wait, Kuali is you, and macuahuitl is your weapon, and then why did you give it away?";
			link.l1.go = "Знакомство_3";
		break;
		
		case "Знакомство_3":
			dialog.text = "A good warrior, not a stupid one. The tunaku man catches pearls, carries a gun.";
			link.l1 = "He had a gun, so no arrows making thunder. Of course, there was a man from the pearl fisheries here, he pointed a gun at you and you gave your maku-u... Ugh, damn it, what's his name? Your weapon and now you want me to return it to you.";
			link.l1.go = "Знакомство_4";
		break;
		
		case "Знакомство_4":
			dialog.text = "Mali-mali! Returned back.";
			link.l1 = "Not a stupid warrior should understand that I need something in return.";
			link.l1.go = "Знакомство_5";
		break;
		
		case "Знакомство_5":
			dialog.text = "Life will give.";
			link.l1 = "Will you keep me alive? It doesn't seem like a threat, in your position, so will you give yours?";
			link.l1.go = "Знакомство_6";
		break;
		
		case "Знакомство_6":
			dialog.text = "Ishik Malov's life.";
			link.l1 = "Well, I'll try to look for your weapon, maybe you really will give me something valuable.";
			link.l1.go = "Согласие";
			link.l2 = "I don't understand you. Running around the jungle here for a pig in a poke, looking for unknown kind of stick. No, Kuali, I won't take it on.";
			link.l2.go = "Отказ";
		break;
		
		case "Отказ":
			DialogExit();
			DeleteAttribute(npchar, "talker");
			UnmarkCharacter(npchar);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Согласие":
			DialogExit();
			DeleteAttribute(npchar, "talker");
			UnmarkCharacter(npchar);
			
			SetQuestHeader("Kuali");
			AddQuestRecord("Kuali", "1");
			AddQuestUserData("Kuali", "sSex", GetSexPhrase("","la"));
			
			sld = CharacterFromID("Kuali");
			sld.dialog.filename = "Quest\Kuali.c";
			sld.dialog.currentnode = "ЕщёРаз_1";
			
			pchar.questTemp.Kuali_1 = true;
		break;
		
		case "ЕщёРаз_1":
			dialog.text = "Ishik find my macuahuitl?";
			link.l1 = "I didn't.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ЕщёРаз_1";
		break;
		
		case "ВозвращаемПалку_1":
			if (CheckCharacterItem(pchar, "toporAZ"))
			{
				dialog.text = "Nit ola ishik. I returned it, I returned it back!";
				link.l2 = "Yes, take it, and give me what you promised me in return.";
				link.l2.go = "ВозвращаемПалку_2";
				TakeItemFromCharacter(pchar, "toporAZ");
				Log_info("You gave away the Macuahuitl");
			}
			else
			{
				dialog.text = "Ishik find my macuahuitl?";
				link.l1 = "I didn't.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ВозвращаемПалку_1";
			}
		break;
		case "ВозвращаемПалку_2":
			dialog.text = "Kuali is honest. It will give life. You've been taken into account.";
			link.l1 = "That's it, you meant 'health'. It'll do. Perhaps this is a fair deal. Good luck to you, Kuali.";
			link.l1.go = "ВозвращаемПалку_3";
			
			AddItems(pchar, "talisman15", 1);
			AddItems(pchar, "potion2", 3);
			Log_info("You got the Indian amulet");
			Log_info("and 3 elixirs of health");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "ВозвращаемПалку_3":
			DialogExit();
			
			PChar.quest.Kuali_EtoNashaPalka.over = "yes";
			AddQuestRecord("Kuali", "6");
			CloseQuestHeader("Kuali");
			pchar.questdata.Kuali = 1;
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		
	}
}
