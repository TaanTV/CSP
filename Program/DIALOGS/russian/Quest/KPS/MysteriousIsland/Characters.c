
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string sName = PChar.name + " " + PChar.lastname;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Что тебе ещё надо, бледнолицый? Я не желаю с тобой сейчас говорить.";
			link.l1 = "Как знаешь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "1":
			dialog.text = "Ба, какая встреча, капитан Жофруа! Вот уж не думал, что мы вновь свидимся.";
			link.l1 = "";
			link.l1.go = "1_1";
			sld = CharacterFromID("Davy Forser");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Zhofrua Djubben"));
		break;	
		
		case "1_1":
			DialogExit();
			StartInstantDialog("Zhofrua Djubben", "2", "Quest\KPS\MysteriousIsland\Characters.c");
		break;
		
		case "2":
			dialog.text = "Ты обманул меня, грязная скотина!";
			link.l1 = "";
			link.l1.go = "2_1";
			sld = CharacterFromID("Zhofrua Djubben");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Davy Forser"));
		break;
		
		case "2_1":
			DialogExit();
			StartInstantDialog("Davy Forser", "3", "Quest\KPS\MysteriousIsland\Characters.c");
		break;
		
		case "3":
			dialog.text = "Нет, это твоя жадность и алчность закрыли тебе глаза на правду. Впрочем, в любом случае - я использовал тебя, и теперь ты мне не нужен.";
			link.l1 = "";
			link.l1.go = "3_1";
			sld = CharacterFromID("Davy Forser");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Zhofrua Djubben"));
		break;
		
		case "3_1":
			dialog.text = "Кстати, кто это с тобой? Твой новый компаньон?";
			link.l1 = "Сейчас кровь смоет улыбку с твоего лица. Защищайся, коварный ублюдок!";
			link.l1.go = "exit";
			sld = CharacterFromID("Davy Forser");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			AddDialogExitQuestFunction("MysteriousIslandFightDavyForser");
			LAi_LocationDisableMonGenTimer("Hispaniola_Cave", 9999);
			LAi_LocationDisableToughSkeletonTimer("Hispaniola_Cave", 9999);
		break;
		
		case "5":
			dialog.text = "Похоже, капитан Дэви Форсер мёртв, не так ли? Я слышал звуки боя?!";
			link.l1 = "Да, ты не ошибся - он отдал Богу душу.";
			link.l1.go = "6";
		break;
		
		case "6":
			dialog.text = "Забрали ли вы золотого идола, которого я отдал ему?";
			link.l1 = "Да, идол у нас, но мы не знаем, каково его предназначение.";
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = "Я помог Дэви проникнуть на остров в первый раз - с помощью двух кораблей нам удалось обойти заклятие. Он должен был достать для меня одну вещь, которая находилась в древних подземных руинах, расположенных прямо под деревней. Дэви Форсер сдержал своё слово и доставил мне ту вещь. За это я обещал ему отдать идола, снимающего заклятие с этого острова\nПоложите идол на священный алтарь, который находится внутри разбитого корабля и забирайте золото. Сколько хотите. Опасности больше не будет.";
			link.l1 = "От чего ты так добр к нам, Мончитлан? Мы ведь убили твоего компаньона!";
			link.l1.go = "8";
		break;

		case "8":
			dialog.text = "Все белые люди для меня одинаковы. Я не вижу разницы. Считайте, что этот дар упал на вас с неба.";
			link.l1 = "Странные вещи ты говоришь. Остаётся только поверить тебе, прощай!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandRetryToIsland");
		break;

		case "9":
			dialog.text = "Да-а, капитан " + sName + ", ты здорово помог"+GetSexPhrase("","ла")+" мне. И поэтому я отблагодарю тебя доброй сталью.";
			link.l1 = "О чём это ты?";
			link.l1.go = "9_1";
		break;
		
		case "9_1":
			dialog.text = "Как"+GetSexPhrase("ой","ая")+" же ты наивн"+GetSexPhrase("ый","ая")+", "+pchar.name+"! Неужели ты думал"+GetSexPhrase("","а")+", что я стану делить с тобой золото?";
			link.l1 = "Ах вот ты о чём... Я долж"+GetSexPhrase("ен","на")+" был"+GetSexPhrase("","а")+" догадаться. Жадность тебя погубит...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandFightWithDubbenInGrot");
		break;
		
		case "10":
			dialog.text = "Я ждал тебя, капитан!";
			link.l1 = "Похоже, ты в чём-то ошибся, старик! Посмотри, что происходит вокруг!";
			link.l1.go = "11";
			
			DeleteAllOfficersFromLocation();
			bDisableOfficers = true;
		break;
		
		case "11":
			dialog.text = "Никакой ошибки не было, капитан. И ты, и Дэви Форсер желали золота - ты его получил"+GetSexPhrase("","а")+", не так ли? Белые люди ради золота истребили почти весь наш древний народ, теперь пусть сами захлебнутся в нём\nДо появления бледнолицых на нашей земле люди правильно относились к золоту - ели на нём, пили воду из золотых кубков и делали красивые украшения для своих женщин, но когда пришли конкистадоры - жадные и беспощадные, и стали убивать людей из-за золотых побрякушек - индейские старейшины собрали большой совет. Было решено схоронить оставшееся золото на том самом острове, а верховный шаман наложил на него заклятие. Я - его прямой потомок.";
			link.l1 = "Так ты всё сделал нарочно, старый мерзавец! Почему ты считаешь, что нынешнее поколение белых людей должно жизнью расплачиваться за действия конкистадоров начала 16 века? Воспользовавшись мно"+GetSexPhrase("й","ю")+", ты хочешь извести безвинных матерей с их детьми, честных отцов семейств и благородных стариков, но я не позволю тебе этого сделать! Глупо мстить людям, которые родились через много лет после событий, о которых ты говоришь, и застали этот мир таким, каков он есть! Историю нельзя повернуть вспять!";
			link.l1.go = "12";
		break;

		case "12":
			dialog.text = "Ваши нравы не изменились с тех пор, и ценности тоже. Ты хотел"+GetSexPhrase("","а")+" золота, капитан - бери его сколько хочешь!";
			link.l1 = "Я "+GetSexPhrase("ошибся","ошиблась")+", но Бог дал человеку выбор между добром и злом и сейчас я исправлю свою ошибку! Я убью тебя!";
			link.l1.go = "13";
		break;

		case "13":
			dialog.text = "Глуп"+GetSexPhrase("ый мальчишка","ая девчонка")+"! Что ты можешь сделать со мной!?";
			link.l1 = "Всё, что смогу! Если я погибну, то так тому и быть!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandFightWithMonchitlan");
		break;

		case "14":
			dialog.text = "Ты правильно поступил"+GetSexPhrase("","а")+", капитан "+GetFullName(pchar)+"! Теперь заклятие вновь обрело свою силу!";
			link.l1 = "Откуда ты меня знаешь?";
			link.l1.go = "15";
		break;

		case "15":
			dialog.text = "Не задавай глупых вопросов!";
			link.l1 = "Не знаю, как к вам обращаться...";
			link.l1.go = "16";
		break;

		case "16":
			dialog.text = "Лучше тебе и не знать. Прощай, капитан! Я уверен, что ты больше не будешь беспокоить индейский схрон, но на всякий случай напоминаю, что не стоит этого делать.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandTheEnd");
			LAi_LocationDisableMonGenTimer("Hispaniola_Cave", -1);
			LAi_LocationDisableToughSkeletonTimer("Hispaniola_Cave", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
