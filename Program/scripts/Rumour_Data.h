#define SIMPLE_RUMOUR_NUM	13
string DEFAULT_TEXT[31];
string NO_RUMOUR_TEXT[SIMPLE_RUMOUR_NUM];
string POOR_RUMOUR_TEXT[10];
string NO_RUMOUR_LSC_TEXT[5];
void InitRumours()
{
    if(LanguageGetLanguage() != "russian")
    {
        DEFAULT_TEXT[0] = "They say that once or twice a year the so-called Golden Fleet departs from Porto Bello - a caravan of several dozen merchant ships under the protection of warships. He always follows the same, unchangeable, once and for all established route: leaving the Spanish harbor of Porto Bello, he sets a course north to Havana. And then across the Atlantic to Europe. Needless to say, there are countless treasures on board the ships of the Golden Fleet.",
        DEFAULT_TEXT[1] = "You know that when someone's fleet attacks a colony, you can help capture it -you need to sail up to the flagship of the attacking squadron, send a boat to it and negotiate terms with the admiral.",
        DEFAULT_TEXT[2] = "It turns out that when someone's fleet attacks a colony, you can help its defense, go through the jungle into the city and talk to the governor about the conditions of assistance in defending the colony from attackers.",
        DEFAULT_TEXT[3] = "Sometimes, important information can be obtained in a tavern from visitors or servants. Since any visitor comes to the inn first of all.",
        DEFAULT_TEXT[4] = "To get into a hostile city, you can land in the nearest bay and make your way through the jungle to the city gate. But it's better to do it under the cover of darkness.",
        DEFAULT_TEXT[5] = "Captain, if you've captured an enemy captain, don't rush to deal with him! Because you can always get a good ransom for a rich prisoner. Or you can just drop him off on some deserted beach.",
        DEFAULT_TEXT[6] = "The climate here is hot and humid, but from April to October the rainy season begins with tropical downpours and severe storms. I would not wish anyone to get into such a storm on the high seas!",
        DEFAULT_TEXT[7] = "To trade profitably, you need to know profitable trade routes, have business acumen, and somewhere friendly relations with store owners. Also, a good treasurer helps a lot in trade matters.",
        DEFAULT_TEXT[8] = "Captain, remember that in naval combat, the most terrible salvo is the broadside, so always try to shoot at the enemy from side guns, but at the same time, try not to be exposed to the broadside of the enemy.",
        DEFAULT_TEXT[9] = "Sometimes it's better to avoid a naval battle with superior enemy forces, but to get away from enemies, you need to be very fast. When the situation is hopeless and you need to escape, it is better to throw the cargo out of the hold, thereby lightening the ship, which will allow you to develop high speed and escape from the chase.",
        DEFAULT_TEXT[10] = "Those who decide to engage in piracy can get valuable information about the rich merchants in the tavern. But not everyone will be told by the regulars of the tavern about easy prey. Only a person with a dark past can count on such a service. Although gold, as you know, opens any door.",
        DEFAULT_TEXT[11] = "In order to gain the favor of the Governor-General, and at the same time a letter of marque from one of the countries, it is necessary to prove your loyalty by exemplary service to the governor of one of the colonies of this country. Although there have been cases when famous pirates became privateers by simply buying a patent from unscrupulous agents.",
        DEFAULT_TEXT[12] = "The colonial authorities often set a large reward for the head of a daring pirate or a dashing robber. And then adventurers from all over the New World begin to hunt for him, they pursue him both on land and at sea.",
        DEFAULT_TEXT[13] = "The life of pirates is quite dangerous, so they often hid the looted treasures in secluded places, carefully mapping the treasure. Now such cards are quite common in the archipelago and they can be bought from various dark personalities.",
        DEFAULT_TEXT[14] = "An experienced crew is needed to manage the ship skillfully. A good team is a rarity, so you need to take care of your people in hot naval battles. An experienced doctor can minimize the loss of people, and medicines on board the ship will not be superfluous. ",
        DEFAULT_TEXT[15] = "On medium and large ships, in addition to the cabin, there is also a mess room - a great place to give the necessary instructions to all your officers.",
        DEFAULT_TEXT[16] = "Buccaneers have always been renowned as skilled hunters and marksmen. The secret of their success is that they always keep their weapons in excellent condition. So don't forget to buy bullets for the gun and carry a better gun with you. ",
        DEFAULT_TEXT[17] = "Remember that every action you do affects your reputation. The world is full of rumors, and a lot of interesting things can also be told about you. A low reputation can greatly damage you in trade deals, but it will help you when intimidating the enemy during boarding. He may even surrender to you without a fight. ",
        DEFAULT_TEXT[18] = "Keep a close eye on the morale of the team. If she is rebellious, it means that your sailors are on the verge of mutiny. Such a team can be appeased with money, well, or rum. As they say, a bad maneuver is better than mutiny on a ship.",
        DEFAULT_TEXT[19] = "They say that an unusual ship for these places goes to sea - the Xebec 'Blue Bird'. A very fast sailing ship, and it sails in the wind as well as in the wind!",
        DEFAULT_TEXT[20] = "The famous Xebec 'Blue Bird' is owned by an unknown pirate. No one knows his name...",
        DEFAULT_TEXT[21] = "If you meet a Bluebird in the sea, then consider the hold is already empty. It's useless to leave, he'll catch up anyway...",
        DEFAULT_TEXT[22] = "The Bluebird is a real storm of merchants. God forbid we meet her at sea...",
        DEFAULT_TEXT[23] = "Pearl fishermen are not only on the west coast of America. They are also in the local waters, but they are very secretive...",
        DEFAULT_TEXT[24] = "It is said that Bartalomew Sharp is a big fan of looting pearl crafts.",
        DEFAULT_TEXT[25] = "Contact the merchant in the store! They say that they are looking for a brave captain, they want to hire him for a good reward...",
        DEFAULT_TEXT[26] = "There are rumors that the Xebec 'Blue Bird' has got the Caribbean traders pretty bad. And now the merchants are looking for a captain who can save them from these problems...",
        DEFAULT_TEXT[27] = "You know, a strange story happened about three years ago with a pirate captain. This cap, Chard Capper, went out to sea and disappeared. What could have happened to him...?",
        DEFAULT_TEXT[28] = "They say that somewhere on the mainland there is an Aztec city of Tenochtitlan. The Aztecs were killed by the Spaniards, so the city is now in disrepair.",
        DEFAULT_TEXT[29] = "You know, there are rumors that during the conquest of America, the Spaniards destroyed the Aztec Indian civilization. Their city, Tenochtitlan, is now in disrepair.",
        DEFAULT_TEXT[30] = "Have you heard about Humphrey Douglas, who settled in our city? Such a brave military man, and so down!";
        /// Если новостей нет .
        NO_RUMOUR_TEXT[0] = "They haven't been saying anything interesting lately. Life flows calmly and peacefully. It's amazing!",
        NO_RUMOUR_TEXT[1] = "We have peace and quiet here. And ships don't come in very often, so there haven't been any important events lately.",
        NO_RUMOUR_TEXT[2] = "The arrival of your ship is what everyone has been talking about lately!",
        NO_RUMOUR_TEXT[3] = "I don't remember anything significant. Even tavern fights are rare here.",
        NO_RUMOUR_TEXT[4] = "I'm unlikely to be able to tell you any news, I haven't heard anything interesting for a long time...",
        NO_RUMOUR_TEXT[5] = "Eh, times have gone by now... Our governor has raised taxes again... so my neighbor and a couple of friends went into the jungle when they threatened to put them in casemates for arrears... What else can people do? Only for free fishing, or to hire dashing captains - everything is not a prison mess.",
        NO_RUMOUR_TEXT[6] = "They say that the soldiers in the garrison have not been paid from Europe for almost a year. There are rumors that the other day Ottudova, from the fort, means that several people deserted. And where will they go? It's a well-known thing - on the high road... what they don't give us, then we'll take it ourselves. And an honest man is already afraid to go out of the city gates.",
        NO_RUMOUR_TEXT[7] = "Our governor, they say, has ordered furniture from the Old World for himself again, so it means to the estate. And half the soldiers in the fort are almost in rags, and they count the peas in the stew for pieces... I heard that a garrison officer sold his family trinkets, bought a lugger and went to sea the other day. He was, of course, declared a deserter! And what could he do if the ranks are only concerned about their own good?",
        NO_RUMOUR_TEXT[8] = "There are rumors that a new war is brewing in Europe. So, taxes and duties will rise again, good trade at a loss. And simple people will be drawn to the highway to trade, away from collectors and bureaucrats... \nAnd who goes to sea, look for mercy from Lady Fortune, but run from a one-legged one... The war against poverty and robbery always goes hand in hand.",
        NO_RUMOUR_TEXT[9] = "We heard that a new squadron came from Europe to strengthen patrols and combat privateering, so. Yes, only those patrols from the tokmo pirates are different from the flag on the grotto. That's why they look - they'll meet the cargo on the high seas and confiscate it, and they'll think of a reason. Then go prove that it wasn't your heifer that trampled the oats... So merchants have to pay escorts and mercenaries to protect their trade. So what do we care? That's right - rum prices will jump again!.. damn it all!",
        NO_RUMOUR_TEXT[10] = "They say that Europe is restless again... So, refugees and crooks of all stripes will come here again. And who needs them here? That's right, there's only one way here - to trade on the highway, or to rob in the sea... Heh-heh, and the governors will increase the levies on the maintenance of garrisons again. That robbers in the jungle, that officials in expensive offices are all the same to ordinary people - blood-sucking bandits...",
        NO_RUMOUR_TEXT[11] = "Have you heard about those fishing tartans that sometimes appear near Turks?.. So, I will say that there is nothing for fishermen to do there! There has never been a fish in those waters! I swear by my leaky longboat, I will never drink rum... There is clearly something not clean here!",
        NO_RUMOUR_TEXT[12] = "Our town is quiet. But recently there was a regular battle nearby here, at the lighthouse. One captain, then, was smuggling with local businessmen, and the patrol caught them doing it! Bad money does not bring happiness, mark my words! So the patrol brigs clamped the schooner of that cap off the coast, and boarded it! The captain himself was shot to death, and the local buyers were hanged in the fort. But it's a pity for the sailors - they sold them all to the trading post. Eh-eh... God save their sinful souls...";
        /// Слухи нищих
        POOR_RUMOUR_TEXT[0] = "They say that somewhere in the Caribbean there is an unusual island. Whoever comes there stays there forever...",
        POOR_RUMOUR_TEXT[1] = "Eh, there is no truth in the Caribbean. But I have heard that there is one island where the latter become the first. And that island is not on the ground...",
        POOR_RUMOUR_TEXT[2] = "Justice is the dream of all the oppressed and offended. And they say there is an island in the Caribbean where there is justice!!",
        POOR_RUMOUR_TEXT[3] = "Island, Island of Justice! And this is not fiction, I tell you, this is reality. The island exists!",
        POOR_RUMOUR_TEXT[4] = "It is difficult to get to the island of Justice, but it is possible. But getting out is unlikely... But for me, if only I could get to this paradise in the Caribbean...",
        POOR_RUMOUR_TEXT[5] = "Yeah, I'm nobody in this town. But the time will come, and I will be lucky. We just need to get to the ISLAND...",
        POOR_RUMOUR_TEXT[6] = "It is human nature to strive for the best. So I want to get to an island where justice reigns. And you know, I will definitely find my way there!",
        POOR_RUMOUR_TEXT[7] = "Drunkenness ruined me, I must admit it honestly. Now I have only one road - to the island of Justice, and only there...",
        POOR_RUMOUR_TEXT[8] = "Do not think that the stories about the ISLAND are fiction. It's true. But no one knows the way there...",
        POOR_RUMOUR_TEXT[9] = "Just to find out how to get to the ISLAND. I'll go there the same day!";
        /// Если новостей нет в ГПК.
        NO_RUMOUR_LSC_TEXT[0] = "It's boring in our City. What news are you talking about?..",
        NO_RUMOUR_LSC_TEXT[1] = "What kind of gossip? Until the next storm, everything will be as calm as in a cemetery.",
        NO_RUMOUR_LSC_TEXT[2] = "There is nothing interesting, and probably won't be...",
        NO_RUMOUR_LSC_TEXT[3] = "I don't know anything new. This is the City of Abandoned Ships!",
        NO_RUMOUR_LSC_TEXT[4] = "No news, no gossip. Before the next storm, of course.";
    }
    else
    {
        DEFAULT_TEXT[0] = "Говорят, что раз-два в год из Порто Белло  отправляется  так  называемый  Золотой флот - караван из нескольких десятков  торговых  судов  под  охраной  боевых кораблей. Он следует всегда одним и  тем  же,  неизменным,  раз  и  навсегда установленным, маршрутом: выйдя из испанской гавани  Порто Белло, он берет курс на север, к Гаване. А затем через Атлантику в Европу. Не стоит и говорить о том, что на борту кораблей Золотого флота находятся несметные сокровища.",
        DEFAULT_TEXT[1] = "Вы знаете, что когда чей-то флот атакует колонию, можно помочь её захватить - надо подплыть к флагману атакующей эскадры, выслать на него шлюпку и договориться об условиях с адмиралом.",
        DEFAULT_TEXT[2] = "Оказывается, когда чей-то флот атакует колонию, можно  помочь её обороне, зайти через джунгли в город и поговорить с губернатором об условиях помощи в обороне колонии от нападающих.",
        DEFAULT_TEXT[3] = "Иногда, важные сведения можно получить в таверне от посетителей или прислуги. Так как любой приезжий перво-наперво заходит именно в трактир.",
        DEFAULT_TEXT[4] = "Чтобы попасть во враждебный город, можно высадиться в ближайшей бухте и через джунгли пробраться к городским воротам. Но лучше это сделать под покровом темноты.",
        DEFAULT_TEXT[5] = "Капитан, если ты захватил в плен вражеского капитана, не спеши расправляться с ним! Так как за богатого пленника всегда можно получить хороший выкуп. Или можно просто высадить его на каком-нибудь пустынном берегу.",
        DEFAULT_TEXT[6] = "Климат у нас тут жаркий и влажный, но с апреля по октябрь начинается сезон дождей с тропическими ливнями и суровыми штормами. Никому не пожелаю попасть в такой шторм в открытом море!",
        DEFAULT_TEXT[7] = "Чтобы выгодно торговать, нужно знать выгодные торговые маршруты, иметь деловую хватку, а где-то  приятельские отношения с владельцами магазинов. Также хороший казначей здорово помогает в торговых делах.",
        DEFAULT_TEXT[8] = "Капитан, помни, что в морском бою самый страшный залп - бортовой, поэтому старайся всегда стрелять по врагу из боковых орудий, но сам, при этом, старайся не подставляться под бортовой залп противника.",
        DEFAULT_TEXT[9] = "Иногда лучше избежать морского боя с превосходящими силами противника, но чтобы уйти от врагов, нужно быть очень быстрым. Когда ситуация безвыходная и нужно спасаться бегством, то лучше выбросить груз из трюма, тем самым облегчив судно, что позволит развить большую скорость и уйти от погони.",
        DEFAULT_TEXT[10] = "Те, кто решили заняться пиратством, могут получить ценные сведения о богатых купцах в таверне. Но не всякому завсегдатаи трактира расскажут о легкой добыче. Только человек с темным прошлым может рассчитывать на подобную услугу. Хотя золото, как известно, открывает любые двери.",
        DEFAULT_TEXT[11] = "Чтобы получить расположение генерал-губернатора, а заодно и каперский патент одной из стран, необходимо доказать свою преданность примерной службой губернатору одной из колоний этой страны. Хотя бывали случаи, когда известные пираты становились каперами, попросту купив патент у нечистых на руку агентов.",
        DEFAULT_TEXT[12] = "За голову дерзкого пирата или лихого разбойника колониальные власти частенько назначают большую награду. И тогда за ним начинают охотиться авантюристы со всего Нового света, они преследуют его как на суше, так и на море.",
        DEFAULT_TEXT[13] = "Жизнь пиратов довольно опасна, поэтому они нередко прятали награбленные сокровища в укромных местах, тщательно составляя карту клада. Теперь такие карты довольно распространены в архипелаге и их можно купить у разных темных личностей.",
        DEFAULT_TEXT[14] = "Для умелого управления кораблём нужен опытный экипаж. Хорошая команда - большая редкость, поэтому необходимо беречь своих людей в жарких морских сражениях. Опытный врач может свести потери людей к минимуму, да и лекарства на борту корабля лишними не будут. ",
        DEFAULT_TEXT[15] = "На средних и больших кораблях помимо каюты есть ещё кают компания - отличное место, чтобы раздать необходимые указания всем своим офицерам.",
        DEFAULT_TEXT[16] = "Буканьеры всегда славились как искусные охотники и меткие стрелки. Секрет их успеха в том, что они всегда держат свое оружие в прекрасном состоянии. Так что не забывай покупать пули для пистолета и носи при себе пистолет получше. ",
        DEFAULT_TEXT[17] = "Помните, что каждый ваш поступок влияет на вашу репутацию. Мир слухами полнится, о вас также могут рассказывать много интересного. Низкая репутация может сильно повредить вам в торговых сделках, но поможет вам при устрашении противника во время абордажа. Он может даже сдаться вам без боя. ",
        DEFAULT_TEXT[18] = "Внимательно следите за моралью команды. Если она мятежная, это значит, что ваши матросы на грани бунта. Такую команду можно ублажить деньгами, ну, или ромом. Как говорится - лучше плохой маневр, чем мятеж на корабле.",
        DEFAULT_TEXT[19] = "Говорят, что в море ходит необычный для здешних мест корабль - шебека 'Синяя Птица'. Очень быстроходный парусник, а в бейдевинд ходит также, как и по ветру!";
        DEFAULT_TEXT[20] = "Знаменитой шебекой 'Синяя Птица' владеет неизвестный пират. Никто не знает, как его зовут...";
        DEFAULT_TEXT[21] = "Если встретил в море шебеку 'Синяя Птица', то считай трюм уже пуст. Уходить бесполезно, догонит всё равно...";
        DEFAULT_TEXT[22] = "Щебека 'Синяя Птица' - настоящая гроза негоциантов. Не приведи Господь встретиться с ней в море...";
        DEFAULT_TEXT[23] = "Ловцы жемчуга есть не только на западном побережье Америки. Они есть и в здешних водах, только очень уж скрытны...";
        DEFAULT_TEXT[24] = "Говорят, что Барталомью Шарп - большой любитель пограбить жемчужные промыслы.";
        DEFAULT_TEXT[25] = "Обратитесь к торговцу в магазине! Говорят, что они ищут отважного капитана, хотят нанять за неплохое вознаграждение...";
        DEFAULT_TEXT[26] = "Ходят слухи, что шебека 'Синяя Птица' здорово достала карибских торговцев. И теперь торговцы ищут капитана, который сможет избавить их от этих проблем...";
        DEFAULT_TEXT[27] = "Вы знаете, странная история произошла года три назад с одним пиратским капитаном. Этот кэп, Чард Каппер, вышел в море и пропал. Что с ним могло случиться?..";
        DEFAULT_TEXT[28] = "Говорят, что где на материке есть город ацтеков Теночтитлан. Ацтеков перебили испанцы, так что город сейчас в запустении.";
        DEFAULT_TEXT[29] = "Вы знаете, ходят слухи, что во времена покорения Америки испанцы уничтожили индейскую цивилизацию ацтеков. Их город, Теночтитлан, сейчас в запустении.";
        DEFAULT_TEXT[30] = "Вы не слышали о Хемфри Дугласе, что поселился у нас в городе? Такой бравый военный, и так опуститься!";
        /// Если новостей нет .
        NO_RUMOUR_TEXT[0] = "Последнее время ничего интересного не говорят. Жизнь течёт спокойно и мирно. Просто диву даёшься!",
        NO_RUMOUR_TEXT[1] = "У нас тут тишь да гладь. А корабли заходят нечасто, поэтому никаких сколько-нибудь важных событий за последнее время не было.",
        NO_RUMOUR_TEXT[2] = "Приход вашего судна - вот о чём все говорят последнее время!",
        NO_RUMOUR_TEXT[3] = "Что-то я не припомню ничего значительного. Даже драки в таверне у нас редкость.",
        NO_RUMOUR_TEXT[4] = "Вряд ли смогу рассказать вам какие-нибудь новости, давно уже ни о чём интересном не слышно...",
        NO_RUMOUR_TEXT[5] = "Эх, времена нынче пошли... Губернатор-то наш опять налоги поднял... вот и сосед мой с парой дружков в джунгли подались, когда их за недоимки грозились в казематы засадить... \nА что людям остается делать? Только на вольный промысел, или к капитанам лихим наниматься - всё не тюремную баланду хлебать.",
        NO_RUMOUR_TEXT[6] = "Говорят, солдатам в гарнизоне уже чуть не год жалование из Европы не присылают. Вот ходят слухи, что на днях оттудова, из форта, значит, несколько человек дезертировало. А куда они подадутся? Известное дело - на большую дорогу... что нам не дают, то, значит, сами и возьмём. А честному человеку уже и за ворота городские выйти боязно.",
        NO_RUMOUR_TEXT[7] = "Губернатор наш, говорят, опять себе мебеля из Старого Света заказал, в усадьбу значит. А половина солдат в форте чуть не в обносках ходят, да горошины в похлёбке на штуки считают... \nВот слыхал я, один гарнизонный офицер, продал семейные побрякушки, купил люггер и на днях ушёл в море. Его, конечно, объявили дезертиром! А что ему оставалось делать, если чины только о своём благе и пекутся?",
        NO_RUMOUR_TEXT[8] = "Ходят слухи, что в Европе новая война зреет. Значит, опять налоги да пошлины вырастут, доброй торговле в убыток. А люд простой на большак промышлять потянется, от сборщиков да чинуш подальше... \nА кто в море подастся, у Госпожи Фортуны милости искать, да от одноногой бегать... Война с нищетой да разбоем всегда об руку ходит.",
        NO_RUMOUR_TEXT[9] = "Слыхали, из Европы новая эскадра пришла, для усиления патрулей и борьбы с каперством, значит. Да только те патрули от пиратов токмо флагом на гроте и отличаются. \nТого и гляди - в открытом море повстречают да груз и конфискуют, а уж причину надумают. Поди потом доказывай, что не твой телок овёс топтал... Вот и приходится торговцам платить конвоирам да наёмничкам за охрану своего промысла. А нам с того что? Правильно - опять цены на ром подскочут!.. провались оно всё пропадом!",
        NO_RUMOUR_TEXT[10] = "Поговаривают, что в Европе снова неспокойно... Значит, опять сюда беженцы да проходимцы всех мастей потянутся. А здесь кому они нужны? Верно, тут таким одна дорога - на большак промышлять, или в море разбойничать... \nЭ-хе-хе, а губернаторы опять поборы на содержание гарнизонов увеличат. Что разбойники в джунглях, что чиновники в дорогих кабинетах - простому люду всё одно - бандиты-кровопийцы...",
        NO_RUMOUR_TEXT[11] = "А слыхали вы, о тех рыбацких тартанах, что иногда появляются возле Теркса?.. Так вот, я скажу, что нечего там рыбакам делать! В тех водах отродясь рыбы не было! \nКлянусь своим дырявым баркасом, вовек мне рому не испить... Тут явно что-то не чисто!",
        NO_RUMOUR_TEXT[12] = "Городок-то у нас тихий. Но вот недавно была форменная баталия неподалёку тут, у маяка. Один капитан, значит, с местными дельцами контрабандой промышлял, а патруль их за этим делом и застукал! \nДурные деньги счастья не приносят, попомните мои слова! Зажали, значит, патрульные бриги шхуну того кэпа у берега, и на абордаж взяли! Самого капитана-то ядром насмерть зашибло, а местных скупщиков в форте повесили. А вот матросиков жалко - всех на факторию продали. Эх-эх... спаси, Господи, их грешные души...";
        /// Слухи нищих
        POOR_RUMOUR_TEXT[0] = "Говорят, что где-то в Карибском море есть необычный остров. Кто туда приходит, тот там и остается навсегда...",
        POOR_RUMOUR_TEXT[1] = "Эх, нет правды на Карибах. Но слышал я, что есть один остров, где последние становятся первыми. И остров тот не на земле стоит...",
        POOR_RUMOUR_TEXT[2] = "Справедливость - вот мечта всех угнетенных и обиженных. И говорят, есть в Карибском море остров, где справедливость ЕСТЬ!!",
        POOR_RUMOUR_TEXT[3] = "Остров, остров Справедливости! И это не выдумки, скажу я вам, это реальность. Остров существует!",
        POOR_RUMOUR_TEXT[4] = "Попасть на остров Справедливости хоть и сложно, но можно. А вот выбраться - это вряд ли... А по мне, только бы попасть в этот рай на Карибах...",
        POOR_RUMOUR_TEXT[5] = "М-да, в этом городе я - никто. Но придёт время, и мне улыбнется удача. Нужно только добраться до ОСТРОВА...",
        POOR_RUMOUR_TEXT[6] = "Человеку свойственно стремиться к лучшему. Вот и я хочу попасть на остров, где царит справедливость. И знайте, я обязательно найду туда дорогу!",
        POOR_RUMOUR_TEXT[7] = "Пьянство сгубило меня, надо признать это честно. Теперь мне одна дорога - на остров Справедливости, и только туда...",
        POOR_RUMOUR_TEXT[8] = "Не стоит думать, что рассказы об ОСТРОВЕ - выдумка. Это правда. Вот только дороги туда не знает никто...",
        POOR_RUMOUR_TEXT[9] = "Только бы узнать, как добраться до ОСТРОВА. В тот же день отправлюсь туда!";
        /// Если новостей нет в ГПК.
        NO_RUMOUR_LSC_TEXT[0] = "Скучно у нас в Городе. О каких новостях вы говорите?..",
        NO_RUMOUR_LSC_TEXT[1] = "Какие сплетни? До следующего шторма у нас всё будет спокойно, как на кладбище.",
        NO_RUMOUR_LSC_TEXT[2] = "Интересного ничего нет, да и не будет, наверное...",
        NO_RUMOUR_LSC_TEXT[3] = "Ничего нового мне неизвестно. Это же Город Потерянных Кораблей!",
        NO_RUMOUR_LSC_TEXT[4] = "Никаких новостей, никаких сплетен. До очередного шторма, конечно.";
    }
}