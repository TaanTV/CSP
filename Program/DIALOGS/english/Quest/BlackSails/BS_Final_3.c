
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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//Скипаем с отравления три дня. ГГ приходит в себя в комнате таверны. Запись в СЖ: 'Неожиданно. Но предсказуемо. Флинт поимел нас всех. Кто бы мог подумать. Хорошо, что жив(ва) остался(лась)! Нужно разобраться в происходящем. Дьявол, как же мутит то!'

		//Далее, Вейна нет на Бермудах. Спускаемся в таверну. Подходит Макс

		case "BS_F3_1":	//Максин
			dialog.text = "You're finally awake, you've been out the longest.";
			link.l1 = "Is everyone alive? What's new?";
			link.l1.go = "BS_F3_2";
		break;

		case "BS_F3_2": //Максин
			dialog.text = "Everyone is alive, he put belladonna in the wine. Master Alexus was giving us all some kind of charcoal stuff and God knows what else. They vomited all over the residence, but they survived.";
			link.l1 = "I will definitely buy him something technical. So what's the news? Flint? Gold?";
			link.l1.go = "BS_F3_3";
		break;

		case "BS_F3_3":	//Максин
			dialog.text = "No Flint, no gold. There is only one chest of doubloons in the warehouse, there are about fifty thousand for everyone. And a note. ";
			link.l1 = "Damn prude! And I almost believed in his 'friendship'. Where are the others?";
			link.l1.go = "BS_F3_4";
		break;

		case "BS_F3_4":	//Максин
			dialog.text = "Eleanor is in residence, with Rekham and Bonnie with her, all three are angry as hell. They are constantly hitting and yelling at each other. As soon as Wayne got to his feet, he hoisted the sails and sped off somewhere";
			link.l1 = "I think it's better not to go into the residence yet. I'm going to get some air.";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: 'Трудно думать, когда тебя постоянно тошнит. Но нужно что-то делать. Попробую подключить разведку. Какой там пароль? На Антигуа! В путь'.

		//В таверну Сен Джонса посадить непися, который отзовётся на пароль

		//На Антигуа, идём в таверну и начинаем донимать нпс паролем 'Рыбалка удалась'. Ответы в духе: 'Пойди проспись!', 'Закусывать надо!', 'Что? О чем вы?'.

		//Нужный непись:

		case "BS_F3_5":	//Агент
			dialog.text = "";
			link.l1 = "Fishing was a success!";
			link.l1.go = "BS_F3_6";
		break;

		case "BS_F3_6":	//Агент
			dialog.text = "Is the catch just...?";
			link.l1 = "No catch, escaped salmon, or eel. Tuna? To hell with your games! There is a conversation!";
			link.l1.go = "BS_F3_7";
		break;

		case "BS_F3_7":	//Агент
			dialog.text = "Khgm. Well... I'm listening to you.";
			link.l1 = "Arrange for me to meet with your boss. Urgently. The fish can slip out of your hands completely, if you know what I mean!";
			link.l1.go = "BS_F3_8";
		break;

		case "BS_F3_8":	//Агент
			dialog.text = "I do not have such authority, but I will pass on the information. How do I get in touch with you?";
			link.l1 = "I'll stop by this tavern from time to time.";
			link.l1.go = "BS_F3_9";
		break;

		case "BS_F3_9":	//Агент
			dialog.text = "Fine, if you don't find me on the spot, contact the waitress";
			link.l1 = "Okay, but tell me that time is precious. All the best!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "I sent a message (la). We need to go back to Bermudes and look for Wayne. No matter how much he messes up.".
		//Плывём на Бермуды. В резиденции Гатри, Бонни, Рекхэм.


		case "BS_F3_10":	//Гатри начинает диалог.
			dialog.text = "Did you find Wayne?";
			link.l1 = "No. Any idea where he's gone?";
			link.l1.go = "BS_F3_11";
		break;

		case "BS_F3_11":	//Рэкхэм.
			dialog.text = "He said he would shake the soul out of black images, gave me a black eye and was like that";
			link.l1 = "Image? It's getting more and more interesting!";
			link.l1.go = "BS_F3_12";
		break;

		case "BS_F3_12":	//Бонни.
			dialog.text = "Flint was doing some business with runaway slaves. Maybe they have him now.";
			link.l1 = "Is there at least someone here with whom he has no connections and affairs?";
			link.l1.go = "BS_F3_13";
		break;

		case "BS_F3_13":	//Гатри.
			dialog.text = "Он забил им головы идеей о свободном государстве в Новом Свете. Равные права, нет господ, мир и счастье. На деле же, использует их как пушечное мясо/NЯ говорила, что Флинт – человек жестокий и рациональный? Идеалистом его никак назвать нельзя, а тот, кто поверит его пламенным речам – станет инструментом, не более";
			link.l1 = "(To myself) I don't think they should know about my contract with Bones yet. (Addressing everyone) Jack, Ann. Did you stay on the shore? I'm offering you places on my team. We'll find Charles, deal with the slaves, look for Flint's tracks in their hiding places.";
			link.l1.go = "BS_F3_14";
		break;

		case "BS_F3_14":	//Рэкхэм.
			dialog.text = "We would love to, but Ann is pregnant. I bought an old schooner here for pennies, and Master Alexus undertook to patch it up for thanks. In general, we decided to retire for now. We'll settle in Charlestown with Ann's father. I'll do coastal transportation, and so on, fishing for small things";
			link.l1 = "Here, there's a little bit. For a young family, so to speak. Ahem... And don't you dare refuse! Well. Good luck to you three. Do not disappear from sight."; //отдаём 75к
			link.l1.go = "BS_F3_15";
		break;

		case "BS_F3_15":	//Гатри.
			dialog.text = "A noble gesture! But to the point. The slaves are runaway, hiding in the jungle, being fed by Buccaneers. So you need to look for them either in Cuba or in Hispaniola. But why did you give up Wayne? The pirate Brethren? I would look for representatives of the Dutch West India Company.";
			link.l1 = "Wayne and I have unfinished business. No sentimentality. And what does the Dutch merchants have to do with it?";
			link.l1.go = "BS_F3_16";
		break;

		case "BS_F3_16":	//Гатри.
			dialog.text = "Flint has a recognizable ship and several tons of Spanish gold. It would be logical to divide the cargo into parts and send it by merchant galleons under military guard anywhere. To Carolina, for example, or even to Boston. I wouldn't be surprised if my dearest daddy is involved in this.";
			link.l1 = "It's worth checking this out too. Thank you. Is there anything else?";
			link.l1.go = "BS_F3_17";
		break;

		case "BS_F3_17":	//Гатри.
			dialog.text = "Maxine. Take her away from here. If necessary, by force!";
			link.l1 = "Is that so? Fine. I'll do the search. In which direction I have no idea. There are too many introductions. See you soon";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "The possible involvement of Eleanor's father? The West India Trading Company? Are Jack and Ann pious planters? Runaway slaves and Eleanor's quarrel with Max. Oh, and British military intelligence. All that's missing are the vengeful Spaniards, the cursed treasure and the ancient god of the local savages! Well, let's start with a simple one. Max. I'll check the tavern."
		//Идём в таверну. Говорим с Макс.

		case "BS_F3_18":	//Максин.
			dialog.text = "She demands that I get off her island! Yes, after everything we've had! I...";
			link.l1 = "Shhh. I don't want to know what you had there. I'm going in search of our money and I'm going to need your information mining talents. Therefore, get on board! No objections!";
			link.l1.go = "exit";
		break;

		//Макс в пассажиры. Выходим в море.
		//Запись в СЖ: "I'll take Maxine to Port Royal, let her gather rumors. And then I'll decide what to do next."
		//Отвозим Макс в ПР. Диалог на причале.

		case "BS_F3_19":	//Максин. Вариант с отказом от секаса.
			dialog.text = "You know, we've been through so much together, but we haven't gotten to know each other better. Maybe we should postpone all business for the evening and spend it over a bottle of good wine?";
			link.l1 = "I'll have wine down my throat if you know what I mean. Business first – entertainment later! No offense.";
			link.l1.go = "BS_F3_20";
		break;

		case "BS_F3_20":	//Максин.
			dialog.text = "No hard feelings. Goodbye Captain!";
			link.l1 = "(To myself) Maybe...? No! Time is running out!";
			link.l1.go = "exit";
		break;

		case "BS_F3_21":	//Максин. Вариант с секасом.
			dialog.text = "You know, we've been through so much together, but we haven't gotten to know each other better. Maybe we should postpone all business for the evening and spend it over a bottle of good wine?";
			link.l1 = "Tempting offer! Only wine makes me sick, if you know what I mean. How about some rum";
			link.l1.go = "BS_F3_22";
		break;

		case "BS_F3_22":	//Максин. Вариант с секасом.
			dialog.text = "Let there be rum! Come on!";
			link.l1 = "Let's go! I just have a couple of bottles with me!"; //ТП в бордель, картинка с потрахушками.
			link.l1.go = "exit";
		break;

		//В обоих вариантах запись в СЖ: "So I'm at a crossroads. Looking for Wayne and the runaway slave camps? Or find out how the British Navy can help? Or should I check out Eleanor's version with the hucksters? It's not worth spraying, there simply won't be enough time for everything at once. I'll mark the Dutch right away, even if it sounds logical, but the Company has its own intelligence, and Flint has spoiled a lot of their blood. So the search for Vane or the help of the fleet. It's time to decide!"
		//Тут опять выбор. Одно блочит другое.
		//Ниже вариант помощи разведке и Бонсу.
		//Плывём на Антигуа, в локации острова запись в СЖ: "Wayne is a big boy, I hope he doesn't mess up. I'll check the tavern. The agent said that if he was not there, ask the peddler"

		case "BS_F3_23":	//Офицантка.
			dialog.text = "Can I get you anything, Captain?";
			link.l1 = "No. Honey, have you seen my friend here? He's a big fan of fishing, did we have a drink here not so long ago?";
			link.l1.go = "BS_F3_24";
		break;


		case "BS_F3_24":	//Офицантка.
			dialog.text = "Are you hunting for big fish? He asked me to tell you that another fisherman will be waiting for you in the waters of Dominica at Castle Timber Beach.";
			link.l1 = "Thank you. Here's for you, uh..., for something beautiful!"; //Отдаём 500 рублей
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Gathering of fishermen from Dominica. We need to hurry.".
		//У пляжа стоит фрегат Бонса. Если решим пострелять - провал линейки. Высылаем шлюпку, разговор с Бонсом на борту.

		case "BS_F3_25":	//Бонс.
			dialog.text = "You should train your memory, Captain. The right password can sometimes save a life!";
			link.l1 = "I don't care about your password games and turnouts. I'm on business! Flint's gone! Along with the ship and the gold. We miraculously survived! Through my channels, I have no leads. Tell me what you have. Maybe we'll catch your fish together. Then we'll split up!";
			link.l1.go = "BS_F3_26";
		break;


		case "BS_F3_26":	//Бонс.
			dialog.text = "What about the honors? A reward? A pardon at last?";
			link.l1 = "With Urki gold, I can at least buy a title for myself. And the favor of the crown is also bought. Don't be a Tom, Billy. I'm itching to stab someone!";
			link.l1.go = "BS_F3_27";
		break;

		case "BS_F3_27":	//Бонс.
			dialog.text = "I'll start from afar. The Scarborough and the rest of the squadron are here not only and not so much for catching Flint and intimidating pirates. The primary task is to prevent the gold from getting from the Urca to Europe. Spain will easily repay part of its debts with this gold, and this will deprive them of influence, their creditors. In addition, such an amount of already minted coins will devalue the existing ones. So if gold disappears in the Caribbean, it's even better. That is, no one in Europe will look for him, and claim him too.";
			link.l1 = "I understand. Politics, intrigues, conspiracies. Old Europe, I can't calm down.";
			link.l1.go = "BS_F3_28";
		break;

		case "BS_F3_28":	//Бонс.
			dialog.text = "My formal commander, Sir Francis Newm, captain of the Scarborough, is a pompous blockhead, the son of some petty lord. He distributes patents and pardons left and right, and recruits supporters. He's looking for the same thing as you, and I suspect my failures are his doing. I have every reason to believe that he is going to get his hands on the gold.";
			link.l1 = "I'm losing the thread, Bill. Flint, gold. How can you help me?";
			link.l1.go = "BS_F3_29";
		break;

		case "BS_F3_29":	//Бонс.
			dialog.text = "There is unverified information about the parking lots of the Walrus in different bays. I don't have the opportunity to check them quickly. Therefore, let's split up. I will go to Cape Katoche and sail south under the Spanish flag. You go to the bay of Boca de la Sierra, and go from there to the west, checking every bay. We'll meet at the Chirique Lagoon. Do not enter ports, avoid collisions. Starting from this day, two weeks should be enough.";
			link.l1 = "You said that there is specific information about parking lots! It's necessary to inspect every bay!";
			link.l1.go = "BS_F3_30";
		break;

		case "BS_F3_30":	//Бонс.
			dialog.text = "The informant was not very accurate in his descriptions and died quickly. Newm, not only is he a cretin, he's also a sadist.";
			link.l1 = "So Newm is also looking for parking?";
			link.l1.go = "BS_F3_31";
		break;

		case "BS_F3_31":	//Бонс.
			dialog.text = "It will start soon. A few days ago, a courier brig arrived from the metropolis and the Scarborough took off her anchors. I do not know what orders Newm received. But it gives us a head start.";
			link.l1 = "So let's not delay!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Bones-Blackham is of little use, you need to explore a large piece of the coast of Main. But at least it's something. I'll start with the bay of Boca de la Sierra"
		//В бухте Бока де ла Сьерпэ, на берегу пусто. Запись в СЖ: "It's empty. I'll keep looking. It is necessary to exclude the bays that are in sight of the forts, Flint would not take such a risk. I'll check the map. Yeah, that leaves: Los Teques Beach, Guajira Bay, Covenas Bay, Mosquitos Bay. Well, let's go."
		//В Лос Текес – пара агрессивных английских фрегатов. Бой. Высадка. На берегу штук 30 военных – файт. Запись в СЖ: "It looks like Newm's people. They are looking for clues at the site of the death of the Urca. We need to be on our guard.".
		//Москитос. На берегу подбегает матрос.

		case "BS_F3_32":	//Матрос.
			dialog.text = "Captain " + GetFullName(pchar) + "? I'm from a fishing colleague!";
			link.l1 = "Billy still can't get enough of it? What have you got there?";
			link.l1.go = "BS_F3_33";
		break;

		case "BS_F3_33":	//Матрос.
			dialog.text = "Arrive in Bridgetown urgently! The search will be tolerated. That's what he said.";
			link.l1 = "Is that all? What's the urgency?";
			link.l1.go = "BS_F3_34";
		break;


		case "BS_F3_34":	//Матрос.
			dialog.text = "I have no idea, "+ GetSexPhrase("sir", "madam") +", I'm just a messenger!" ;
			link.l1 = "Okay, I got it.";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Something has happened. Bones demands to come to Bridgetown urgently."
		//Плывём на Барбадос. В городе подходит Бонс.

		case "BS_F3_35":	//Бонс.
			dialog.text = "You are here. Fine. The Barbadian authorities are asking for help, their garrison is still not manned, after the Spanish raid. And 'Scarborough' is unknown where" ;
			link.l1 = "What happened? By the way, on the beach of Los Teques I came across at the Newman's people. Rummaging through the wreckage of the 'Urca'";
			link.l1.go = "BS_F3_36";
		break;

		case "BS_F3_36":	//Бонс.
			dialog.text = "They won't find much there. An attack is planned on the plantations located on the island. Today, tomorrow, soon. And you won't believe who will lead the attack. Flint himself!" ;
			link.l1 = "What the hell does he need this for?";
			link.l1.go = "BS_F3_37";
		break;

		case "BS_F3_37":	//Бонс.
			dialog.text = "Somewhere in the colonies, he creates an army of convicts and runaway slaves, and here is the royal penal servitude. Thugs of all stripes, arm and ready.  That's what Spanish gold is for. And he does not intend to share it. There are only recruits and a militia of colonists in the local garrison. They will scatter at the first volleys. But if we combine our teams, we can fight back against him and, God willing, capture him!" ;
			link.l1 = "Shall we set up an ambush? Well, it might work. Gather people, meet me at the plantation!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "It's going to be a hot business. Flint is going to free the convicts for his army. A great opportunity to swat the bastard. But it's still worth remembering who we're dealing with. We'll set up an ambush on the plantation.".
		//Идём на плантацию. Там бродят наши в перемешку с английскими солдатами, заходим за калитку плантации. Вывести лог 'Засада организована! Всем быть на готове!' Начинаем спаунить пиратов от ворот. В три-четыре волны.
		//Перебили всех, Бонс орёт : 'Они с полей прут, ещё больше! Стрелки, к бою!'

		case "BS_F3_38":	//Бонс.
			dialog.text = "They are from the fields of the rod, even more! Shooters, ready to fight!" ;
			link.l1 = "Follow me!";
			link.l1.go = "exit";
		break;

		//Спауним пиратов прям на плантации. Перебили.


		case "BS_F3_39":	//Бонс.
			dialog.text = "Where the hell is Flint?" ;
			link.l1 = "It's not over yet! Do you hear? The guns are firing! Get down!";
			link.l1.go = "exit";
		break;

		//Нужна пара взрывов где-нибудь. От ворот ещё толпа пиратов. С ними Флинт и Вейн. Пока живы их пираты - Ф и В бессмернтые. Как только полегли все пираты Флинт начинает диалог.

		case "BS_F3_40":	//Флинт.
			dialog.text = "Wayne! Retreat, reinforcements are coming from the fort!" ;
			link.l1 = "I'll cover, go away!"; //Вейн
			link.l1.go = "BS_F3_41";
		break;


		case "BS_F3_40":	//Флинт.
			dialog.text = "I understand. "+pchar.name+"you're fighting on the wrong side! But it's your choice." ; //Убегает.
			link.l1 = "I'm behind Flint. You can't miss it!"; //Бонс. Убегает.
			link.l1.go = "BS_F3_41";
		break;

		case "BS_F3_41":	//Вейн.
			dialog.text = "Well? Just you and me?!" ;
			link.l1 = "What the hell is Charles? We had an agreement!";
			link.l1.go = "BS_F3_42";
		break;

		case "BS_F3_42":	//Вейн.
			dialog.text = "You change sides too often. And your new friends killed Eleanor!" ;
			link.l1 = "How?! When?";
			link.l1.go = "BS_F3_43";
		break;

		case "BS_F3_43":	//Вейн.
			dialog.text = "'Scarborough came to Bermudes while I was looking for Flint and did a sweep there. Eleanor was taken in chains to Port Royal and hanged at the port. Maxine is in jail and she's going to be hanged soon too. Jack is in jail in Charlestown, but he'll get out of it. Anne has been pardoned. The humane court decided that hanging a pregnant woman, even a pirate, is too much. And you became a dog sniffing out Spanish gold for British intelligence" ;
			link.l1 = "Did Flint tell you that? He can play with brains!";
			link.l1.go = "BS_F3_44";
		break;

		case "BS_F3_44":	//Вейн.
			dialog.text = "I saw her body. She was placed in a cage so that she would not fall apart during decomposition. It's still hanging near the pier. Stop talking! Someone will leave here alone!" ;
			link.l1 = "It's not my fault, Charles. But you can't be persuaded. Start as soon as you're ready!";
			link.l1.go = "exit";
		break;

		//Рубимся с Вейном. Убиваем. Страдаем, какой автор гнида. Идём в город. Подбегает Сильвер.

		case "BS_F3_45":	//Сильвер.
			dialog.text = "Hey "+pchar.name+"You don't have a face on! What was there? Is this Flint?" ;
			link.l1 = "Shut up, John. How did you end up here?";
			link.l1.go = "BS_F3_46";
		break;

		case "BS_F3_46":	//Сильвер.
			dialog.text = "Got away from Flint when he started cleaning up the tails. I cut out the whole old team!" ;
			link.l1 = "I'm thinking of catching up with him at sea. Are you with me?";
			link.l1.go = "BS_F3_47";
		break;

		case "BS_F3_47":	//Сильвер.
			dialog.text = "Flint?! No! Yes! Yes, I think it will be safer with you. I've been hiding under whores' skirts for a week now!" ;
			link.l1 = "Then to the sea!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Wayne. Damn you. You were my friend! And Bons, damn Bons. While I was looking for something, the British staged a sweep. Guthrie is dead. Everything is going to the abyss! It remains to get even with Flint and I don't care what happens next!"
		//Выходим в море, нас атакует 'Рейнджер'. Топим. Выходим на глобалку. От нас по съёбам удирает квестовик-энка (типо Флинт с Бонсом). Нужно скорости им накрутить, чтоб мы только-только угнаться могли. Энка пиздует к мысу Каточе и там исчезает. Выходим на локалку. Там фрегат Бонса гасится с Моржом (Бонс зелёненький). Берём Моржа на абордаж. В каюте рубилово с Флинтом. Нулим Флинта. Диалог


		case "BS_F3_48":	//Флинт.
			dialog.text = "Is Wayne dead? It's a pity, but he was too emotional. Did you accept the proposal of the British authorities? Pardon, patent, royal favors? You understand that they make promises easily and just as easily take them back. I was one of them!" ;
			link.l1 = "...";
			link.l1.go = "BS_F3_49";
		break;

		case "BS_F3_49":	//Флинт.
			dialog.text = "Just don't stare at me. It doesn't work on me.  There are still ways to sort things out. We will capture the frigate Bones, then under English flags and with the help of his signal book, we will trap the Scarborough. Thus, we will get rid of the attention of military intelligence, they now have their mouth full of worries without us. Next..." ;
			link.l1 = "Is that how your head works? Plans, inside plans? No friends, no enemies. There are only tools and interference. Are you even human?";
			link.l1.go = "BS_F3_50";
		break;

		case "BS_F3_50":	//Флинт.
			dialog.text = "Emotions are inappropriate, morality is a sign of weakness, compromises are the way to mediocrity. My goals are a new world. And to build a new one, you need to break the old one. You could be a useful tool, but I see irrational feelings that will interfere with your effectiveness. So be it. It will be a little more difficult, but nothing is impossible!" ;
			link.l1 = "Just shut up and die!";
			link.l1.go = "exit";
		break;

		//Файт. На трупе Нарвал, книга Марк Аврелий 'Размышления'. В сундуке 5кк денег, судовой журнал Флинта (зашифрованый).
		//Как только закрываем окно захвата корабля - СЮРПРИЗ. Спаун "" с парой фрегатов. Бой, без диалогов в случае захвата.
		//После победы ТП на берег. Фрегат Бонса удаляем, он потонул. На берегу Бонс, Сильвер, ГГ.

		case "BS_F3_51":	//Сильвер.
			dialog.text = "Is Flint dead?" ;
			link.l1 = "Dead.";
			link.l1.go = "BS_F3_52";
		break;

		case "BS_F3_52":	//Бонс.
			dialog.text = "Heh. Sorry. We would be very glad to see him alive in London." ;
			link.l1 = "After all that has happened, I think YOU will be welcome in London too!";
			link.l1.go = "BS_F3_53";
		break;

		case "BS_F3_53":	//Бонс.
			dialog.text = "I think so. Francis Newm, Esquire, died like a hero, and some commander survived. I really don't want to answer any questions that arise!" ;
			link.l1 = "You two! Here are Flint's papers, encrypted. Will you figure it out? I'm going to lie down and rest here. I tired of killing."; //Отдаём книгу, журнал.
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Somewhere along the way, I made the wrong choice. What was the turning point? Eleanor, Jack, Charles. How would their fates have turned out if I had made other decisions? Would I become a soulless machine under Flint's leadership? Damn, my head hurts! I need to rest.".
		//Ставим табличку "It's been ten hours, ", мотаем время.

		case "BS_F3_54":	//Сильвер.
			dialog.text = "Hey! Are you alive? You're a master at snoring!" ;
			link.l1 = "What? How are you doing?";
			link.l1.go = "BS_F3_55";
		break;

		case "BS_F3_55":	//Бонс.
			dialog.text = "Two sheets of coordinates. Latitude, longitude. Everything. No 'Seven steps from a dead tree', nothing!" ;
			link.l1 = "How this devil thought, how his head is arranged is incomprehensible.";
			link.l1.go = "BS_F3_56";
		break;

		case "BS_F3_56":	//Бонс.
			dialog.text = "Is this a route? But where is the beginning and the end? There are hundreds of points on the map! There must be a connection! She must! You just have to think, reread the damn book, there must be something!" ;
			link.l1 = "Where should I take you?";
			link.l1.go = "BS_F3_57";
		break;

		case "BS_F3_57":	//Сильвер.
			dialog.text = "What? Are you giving up?" ;
			link.l1 = "Puerto Princibe? We are not far from Cuba.";
			link.l1.go = "BS_F3_58";
		break;

		case "BS_F3_58":	//Бонс.
			dialog.text = "Yes, the Cube will do. I have a secret place there. That's enough for the first time." ;
			link.l1 = "Then let's go";
			link.l1.go = "exit";
		break;

		//Везём братву на Кубу. В бухте Пуэрто Присибе подходит Сильвер.


		case "BS_F3_59":	//Сильвер.
			dialog.text = "I'll look after Billy, it seems to me he's not himself. Where are you going?" ;
			link.l1 = "I'll try to save Max. At least I'll do something right. Good luck, John!";
			link.l1.go = "exit";
		break;

		//Плывём в Порт Рояль, идём в тюрягу, комендант.

		case "BS_F3_60":	//Комендант.
			dialog.text = "What is your question?" ;
			link.l1 = "I wanted to inquire about the fate of one person. Maxine.";
			link.l1.go = "BS_F3_61";
		break;

		case "BS_F3_61":	//Комендант.
			dialog.text = "Aah, madam! She's fine. They kept him in a cage for a couple of days, then a messenger came from the governor himself with a pardon. And they let me go with God!" ;
			link.l1 = "Thank you.";
			link.l1.go = "exit";
		break;

		//Идём в бордель. Комната мадам.

		case "BS_F3_62":	//ГГ
			dialog.text = "I had no hope to see you alive!" ;
			link.l1 = "My captain! As long as my girls are collecting rumors, I'm not in danger. I generously share them with both the authorities and the corsairs. Everyone is ready to stand up for me.";
			link.l1.go = "BS_F3_63";
		break;

		case "BS_F3_63":	//ГГ.
			dialog.text = "Well. Then my mission is complete. Here's your share, companion. Here is everything that could be found from the gold 'Urki'" ; //отдаём 2.5кк
			link.l1 = "I will not refuse. Moreover, expenses are coming. I got permission to give Eleanor a proper burial. And I'll send the money to Ann. Did you hear about Jack?";
			link.l1.go = "BS_F3_64";
		break;

		case "BS_F3_64":	//ГГ.
			dialog.text = "Yes. Flint is dead, Wayne is dead." ;
			link.l1 = "Has the story come to an end?";
			link.l1.go = "BS_F3_65";
		break;

		case "BS_F3_65":	//ГГ.
			dialog.text = "This story, yes. There are still many untold stories. Goodbye Max!" ;
			link.l1 = "Visit me, Captain, from time to time.";
			link.l1.go = "exit";
		break;

		//Уходим в закат. Макс – остаётся в роли мадам, с бесплатными потрахушками. Можно ей добавить слухов по 'Лёгкой добыче'.
		//На выходе из борделя – подбегает Сильвер


		case "BS_F3_66":	//Сильвер.
			dialog.text = "Bones found a connection!!! These are really waypoints! And only he has a map!" ;
			link.l1 = "Captain Flint's Treasure Island Map?";
			link.l1.go = "BS_F3_67";
		break;


		case "BS_F3_67":	//Сильвер.
			dialog.text = "Yes! But he got away. He disappeared. Disappeared with the map! We need to find him!" ;
			link.l1 = "This is already your story, John. Here's some for you. Buy yourself a tub and chase Billy Bones even to England!"; //отдаём 25к
			link.l1.go = "BS_F3_68";
		break;

		case "BS_F3_68":	//Сильвер.
			dialog.text = "But... Are you sure?! I see that, yes. I'll find you, I will! Oh, and we'll feast on Flint's money!" ;
			link.l1 = "Get lost Silver!";
			link.l1.go = "exit";
		break;

		//Квест уходит в архив.

}


}
