
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int Bonus = sti(pchar.rank);
	if (Bonus <= 6) Bonus = 1;
	if (Bonus >= 7 && Bonus <= 12) Bonus = 1.2;
	if (Bonus >= 13) Bonus = 1.5;
	int Plata1 = 3000 + 200 * sti(pchar.rank) * Bonus;
	int Plata2 = 15000 + 500 * sti(pchar.rank) * Bonus;
	pchar.PDM_Apt_Plata1.Money = 3000 + 200 * sti(pchar.rank) * Bonus;
	pchar.PDM_Apt_Plata2.Money = 15000 + 500 * sti(pchar.rank) * Bonus;

	int i, iOfficer;
	string attrL, offtype;
	ref chref;

	attrL = Dialog.CurrentNode;

	if(HasSubStr(attrL, "OfficerConfusedSel_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.OfficerToHealConfuse = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "OfficerConfused";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":							//Автор Sinistra
			dialog.text = "Greetings, I am a doctor of alchemy and medicine. My name is Alumnus. And what is your name, "+ GetSexPhrase("young man", "girl") +"?";
			link.l1 = "You can call me "+pchar.name+".";
			link.l1.go = "Alumnus_PervoeZadanie_1";
		break;
		
		case "Alumnus_PervoeZadanie_1":
			dialog.text = "It's good that you came in, "+pchar.name+"! Listen, could you give me a little help, otherwise I can't leave for a long time...";
			link.l1 = "What should I do?";
			link.l1.go = "Alumnus_PervoeZadanie_2";
		break;
		
		case "Alumnus_PervoeZadanie_2":
			dialog.text = "One of my patients is lying here in Marigo, his name is Budevin. You need to take the medicine to him, and he will pay for the delivery himself.";
			link.l1 = "It seems to be nothing complicated. I'll take the medicine to him.";
			link.l1.go = "Alumnus_PervoeZadanie_3";
			link.l2 = "Dr. Alumnus, hire yourself a courier, and I have more serious things to do.";
			link.l2.go = "Alumnus_PervoeZadanie_Net";
		break;
		
		case "Alumnus_PervoeZadanie_3":
			dialog.text = "Oh, I knew you wouldn't say no, "+pchar.name+", thank you! To find his house, you need to climb up the mountain, it stands next to the exit to the jungle.Here, keep the medicine. Come see me again, I'll find a job for you.";
			link.l1 = "I will definitely come in. Goodbye!";
			link.l1.go = "Alumnus_PervoeZadanie_4";
			NextDiag.TempNode = "Alumnus_PervoeZadanie_3_EsheRaz";
		break;
		
		case "Alumnus_PervoeZadanie_3_EsheRaz":
			dialog.text = "Did you take the medicine to Budevin?";
			link.l1 = "Not yet, but I'll be with him soon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_PervoeZadanie_3_EsheRaz";
		break;
		
		case "Alumnus_PervoeZadanie_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetQuestHeader("PDM_Aptekar");
			AddQuestRecord("PDM_Aptekar", "1");
			GiveItem2Character(PChar, "PDM_Heal_Poroshok");
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Markus", "prison_3", "man", "man", 10, HOLLAND, -1, false));
			sld.name	= "Budevin";
			sld.lastname	= "";
			sld.Dialog.Filename = "Quest\PDM\Aptekar.c";
			sld.dialog.currentnode   = "Markus_1";
			LAi_SetGroundSitType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Smallhome_K2", "quest", "quest1");
		break;
		
		case "Alumnus_PervoeZadanie_Net":
			dialog.text = "Very sorry, "+pchar.name+". I'm busy with something right now, so I can't examine you.";
			link.l1 = "Well, then I'll go.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Obijen";
		break;
		
		case "Alumnus_Obijen":
			dialog.text = "Hello, "+pchar.name+". How can I help you?";
			link.l1 = "Just passing by.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Obijen";
		break;
		
		case "Markus_1":
			dialog.text = "(coughs)... Yes, what did you want?";
			link.l1 = "I'm from Dr. Alumnus, he asked me to give you this medicine.";
			link.l1.go = "Markus_2";
			locCameraFromToPos(1.00, 2.00, 0.00, false, -4.00, -1.20, -4.00);
		break;
		
		case "Markus_2":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+"How are you on time, this pain is unbearable... I was attacked by some bandits last night. They took everything valuable from me, but thank God I stayed alive. The guards are still looking for them, but I hope the villains get what they deserve.";
			link.l1 = "Yes, an unpleasant situation has happened to you. Dr. Alumnus said you would pay for the delivery.";
			link.l1.go = "Markus_3";
			TakeItemFromCharacter(pchar, "PDM_Heal_Poroshok");
		break;
		
		case "Markus_3":
			dialog.text = "Oh yes, of course. Here, "+Plata1+" piastres are yours. I wish I could sleep now...";
			link.l1 = "Get well, Mynheer, and now I'll leave you.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Plata1));
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("PDM_Aptekar", "2");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("if", "a"));
			AddQuestUserData("PDM_Aptekar", "sSex2", GetSexPhrase("", "a"));
			
			sld = CharacterFromID("Doktor_Alumnus");
			sld.dialog.filename   = "Quest\PDM\Aptekar.c";
			sld.dialog.currentnode   = "Alumnus_VtoroeZadanie";
		break;

		case "Alumnus_VtoroeZadanie":
			dialog.text = "Ah, it's you, "+ GetSexPhrase("my young and impatient captain", "my young and impatient friend") +"! What do you want from me?";
			link.l1 = "I wanted to find out if you need any help?";
			link.l1.go = "Alumnus_VtoroeZadanie_2";
		break;

		case "Alumnus_VtoroeZadanie_2":
			dialog.text = "Yes, indeed, I need help right now. I need a small amount of one rare herb that grows on the Caribbean islands. I can't cook my miraculous healing concoctions without it. If you could get this herb for me, I could treat you and your officers for any injuries and illnesses. I once bought some of this herb from an Indian... What was his name? Oh, yes, at Tuantuh's.";
			link.l1 = "Tell me about this Tuantukha.";
			link.l1.go = "Alumnus_VtoroeZadanie_3";
		break;

		case "Alumnus_VtoroeZadanie_3":
			dialog.text = "He's pretty weird... Even his fellow tribesmen shun him. He sails from one island to another on his boat, collecting various rare herbs and medicines, and then sells them to doctors, pharmacists and midwives. But it seems to me that he is an intelligent man, despite his habits - he gave me a couple of very useful tips about local diseases and the psychology of Indians. He lives apart from people, and was last seen somewhere in the Bahamas. Since he has a boat, he lives next to the sea, on the rocks.";
			link.l1 = "I'll bring you this weed. What's it called?";
			link.l1.go = "Alumnus_VtoroeZadanie_4";
		break;

		case "Alumnus_VtoroeZadanie_4":
			dialog.text = "Ah. Here's a little problem. I can't remember the exact name of it. I'm sure Tuantuh called this herb to me when he sold it, but I just forgot the name, it sounds extremely strange to a European's ear, you know.";
			link.l1 = "And how should I look for this herb when I don't know what it's called?";
			link.l1.go = "Alumnus_VtoroeZadanie_5";
		break;

		case "Alumnus_VtoroeZadanie_5":
			dialog.text = "Well, I'll tell you how to identify this herb. Its smell resembles the smells of cinnamon and anise at the same time. A rather odorous mixture, I must say. I think this is due to the influence of Neptune and Europa on the ripening process of this herb. Hindenburg wrote a whole work on the influence of the outer planets on the ripening of herbs during the vernal equinox. However, I digress.";
			link.l1 = "Yes, you are distracted. Thanks for the lecture. I will try to find this herb for you. See you later.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_VtoroeZadanie_6";

			sld = GetCharacter(NPC_GenerateCharacter("Pablo_Loco", "indsar1", "man", "man", 10, PIRATE, -1, false));
			sld.name = "Tuantuh";
			sld.lastname = "";
			sld.greeting = "GR_Pablo_Loco";
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetStayType(sld);
			sld.dialog.filename   = "Quest\PDM\Aptekar.c";
			sld.dialog.currentnode   = "Pablo_Loco_FT";
			ChangeCharacterAddressGroup(sld, "Shore68", "quest", "quest18");

			AddQuestRecord("PDM_Aptekar", "3");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("", "a"));
		break;

		case "Alumnus_VtoroeZadanie_6":
			dialog.text = "Welcome back! Have you managed to find the plant I need?";
			link.l1 = "Not yet, Doctor. I'm continuing my search.";
			link.l1.go = "exit";
			link.l2 = "Doctor, remind me how to identify this herb.";
			link.l2.go = "Alumnus_Novoe_Kak_Opoznat";
			NextDiag.TempNode = "Alumnus_VtoroeZadanie_6";
		break;

		case "Alumnus_Novoe_Kak_Opoznat":
			dialog.text = "Remember: this rare herb grows on the Caribbean islands, its smell resembles both cinnamon and anise. I think this is due to the influence of Neptune and Europa on the ripening process of this herb. Hindenburg wrote a whole work on the influence of the outer planets on the ripening of herbs during the vernal equinox...";
			link.l1 = "Okay, doctor, that's enough, I ran.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_VtoroeZadanie_6";
		break;

		case "Pablo_Loco_FT":
			dialog.text = "Ah! Yours is to desire gold, isn't it? Yours is to desire a lot of gold. Blind"+ GetSexPhrase("oh fool", "aya fool") +"! Doesn't yours really care about the state of your soul?";
			link.l1 = "What are you talking about? Who are you?";
			link.l1.go = "Pablo_Loco_1";
			NextDiag.TempNode = "Pablo_Loco_ER_1";
		break;

		case "Pablo_Loco_ER_1":
			dialog.text = "Do you want to throw your greed into the sea?";
			link.l1 = "What are you talking about?";
			link.l1.go = "Pablo_Loco_ER_2";
		break;

		case "Pablo_Loco_ER_2":
			dialog.text = "Greed makes your heart as heavy as gold itself. Your duty is to throw it into the sea to be cleansed.";
			link.l1 = "Tell me your story.";
			link.l1.go = "Pablo_Loco_2";
		break;

		case "Pablo_Loco_1":
			dialog.text = "I am Tuantukh. The one whose ears yearn for birdsong and the voices of his brothers, but hear only screams and screams. The one whose nose yearns for the fragrance of flowers and the salty sea, but feels only bitter black powder.";
			link.l1 = "You are undoubtedly an unhappy person. Tell me your story.";
			link.l1.go = "Pablo_Loco_2";
			link.l2 = "Your mind is clearly out for a walk, and I have urgent business everywhere. Goodbye.";
			link.l2.go = "exit";
		break;

		case "Pablo_Loco_2":
			dialog.text = "I lived in Inachetla. I am to be found in a boat drifting in the ocean, a little child, alive among the many dead. I grew up strong. I feel the spirit of this island, and I feel the spirit of the sea. My brothers fished in the sea in small boats. They drew life from the sea. But then the sea brings them death.";
			link.l1 = "What do you mean?";
			link.l1.go = "Pablo_Loco_3";
		break;

		case "Pablo_Loco_3":
			dialog.text = "One day my brothers saw huge ships at sea. They had never seen such large ships, and they thought they were huge winged birds sent by the gods. They headed towards these ships, shouting and waving their spears in a joyful greeting. But these were not the ships of the gods. These were the ships of the white men. The Palefaces are afraid of my brothers and think they are being attacked. So they killed my brothers, and then they went to my village and killed everyone who was there-everyone except me, who was alive again among the dead. So now I'm the only one left who can feel the spirit of the island and the sea. That's my story.";
			link.l1 = "I am grieving for your loss... Uh, are you the Tuantuh, the herbalist?";
			link.l1.go = "Pablo_Loco_Trava";
		break;

		case "Pablo_Loco_Trava":
			dialog.text = "Yes, it's me. I can feel the spirit of nature: the call of the sea, the whisper of seeds, the laughter of flowers. Tuantuh: That's who I am.";
			link.l1 = "Indeed. 'Laughter of flowers', eh? It's, uh, very interesting. Well, Tuantuh, I need a herb that smells like...";
			link.l1.go = "Pablo_Loco_5";
		break;

		case "Pablo_Loco_5":
			dialog.text = "What does this herb smell like?";
			Link.l1.edit = 1;
			Link.l1 = "";
			link.l1.go = "Pablo_Loco_Pravilno";
			NextDiag.TempNode = "Pablo_Loco_5";
		break;

		case "Pablo_Loco_Pravilno":
			string answer = GetStrSmallRegister(dialogEditStrings[1])
			if (HasSubStr(answer, "cinnamon") && HasSubStr(answer, "anise"))
			{
Dialog.text = "Does it smell like cinnamon and anise? I know this kind of grass. It can heal, or it can kill. Tell me, why do you need this herb?";
				Link.l1 = "Dr. Alumnus sent me to get her.";
				Link.l1.go = "Pablo_Loco_6";
				break;
			}
			else
			{
Dialog.text = "Mine is not to know herbs with such a smell.";
				{
					Link.l1 = "I'll try again right now.";
					Link.l1.go = "Pablo_Loco_5";
				}
				link.l2 = "I need to think about it.";
				link.l2.go = "exit";
			}
		break;

		case "Pablo_Loco_6":
			dialog.text = "So, Alumnus, did you say? My knowledge of this man is a wise fool. It is dangerous to give tzescatlat umtat into the hands of a 'man of knowledge'. But I know that he won't use grass to intentionally kill another person - that's not the right person. Very good. To find this grass, I need a boat, because mine has to sail to where it grows. Herbs don't grow all in one place, white man.";
			link.l1 = "I'll buy it for you.";
			link.l1.go = "Pablo_Loco_7";
		break;

		case "Pablo_Loco_7":
			dialog.text = "No, no! You can't 'buy' a boat! Golden contagion spoil the spirit of the boat! You should build a boat with your own hands and your own heart, and not infect it with golden poison!";
			link.l1 = "You are a difficult person, Tuantuh, do you know about this? Well, okay: what should I do to help you build a boat?";
			link.l1.go = "Pablo_Loco_8";
		break;

		case "Pablo_Loco_8":
			dialog.text = "I need a special tree. This tree is called Teshkatali. If you want me to get your grass for you, you must deliver the Teshkatali tree to me. It grows on the continent in the jungle, next to the Karataska lagoon.";
			link.l1 = "Teshkatali tree? I understand and I won't forget. Goodbye, Tuantuh. I'll be back.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_9";

			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition.l1 = "location";
			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition.l1.location = "Shore10";
			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition = "PDM_Apt_Prihov_v_buhtu";

			AddQuestRecord("PDM_Aptekar", "4");
		break;

		case "Pablo_Loco_9":
			dialog.text = "Why are you bothering me? The only thing I need from you is the Teshkatali tree. When you bring him to me, I'll build myself a new boat. And then you will get tzescatlat umtat. That's all I can say.";
			link.l1 = "I understand. Goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_9";
		break;

		case "Nashel_Derevo":
			dialog.text = "You again? You delivered Teshkatali tree?";
			link.l1 = "I have the tree you need. Here it is. Now come on, build your boat so you can bring me my tzeska... tla.. la... mumat... or whatever the damn weed is called.";
			link.l1.go = "Nashel_Derevo_2";
		break;

		case "Nashel_Derevo_2":
			TakeItemFromCharacter(pchar, "PDM_Derevo_Teshkali");
			dialog.text = "Come back in a week, at this time I will have the grass you need.";
			link.l1 = "Let me call my sailors, together with them you will make the boat five times faster.";
			link.l1.go = "Nashel_Derevo_3";
		break;

		case "Nashel_Derevo_3":
			dialog.text = "(looks at you with an angry look)";
			link.l1 = "Okay, okay, I won't bother you. I'll see you in a week.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_Stroit_lodku";

			SetTimerCondition("PDM_Apt_Lodka_Postroena", 0, 0, 7, false);

			AddQuestRecord("PDM_Aptekar", "7");
		break;

		case "Pablo_Loco_Stroit_lodku":
			dialog.text = "The boat may not be ready yet, come back later.";
			link.l1 = "All right, Tuantuh, do as you can.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_Stroit_lodku";
		break;

		case "Pablo_Loco_Lodka_Postroena":
			dialog.text = "White man, my find your grass.";
			link.l1 = "My thanks, Tuantuh. Yours should not worry, this herb does not bring death, but benefits medicine. Mine is saying goodbye to yours.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;

			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 150);

			GiveItem2Character(PChar, "PDM_Trava_Tzes_Umrat");
			AddQuestRecord("PDM_Aptekar", "8");

			sld = CharacterFromID("Doktor_Alumnus");
			sld.dialog.filename   = "Quest\PDM\Aptekar.c";
			sld.dialog.currentnode   = "Alumnus_Finish_Zadanie";
		break;

		case "Alumnus_Finish_Zadanie":
			dialog.text = "You're back. Stunningly. Did you bring me the grass that I asked you for, "+ GetSexPhrase("my young captain", "Mrs.") +"?";
			link.l1 = "Tzescatlat Umtat?";
			link.l1.go = "Alumnus_Finish_Zadanie_2";
		break;

		case "Alumnus_Finish_Zadanie_2":
			dialog.text = "I'm sorry, what??";
			link.l1 = "Here it is.";
			link.l1.go = "Alumnus_Finish_Zadanie_3";
		break;

		case "Alumnus_Finish_Zadanie_3":
			dialog.text = "Ah! You brought it! What luck! I can now prepare my own medicinal concoctions, as well as continue one unfinished research!";
			link.l1 = "Tell me, Doctor, if it's not a secret, why do you need this stinky herb?";
			link.l1.go = "A_pravda_ZACHEM???";
			TakeItemFromCharacter(pchar, "PDM_Trava_Tzes_Umrat");
		break;

		case "A_pravda_ZACHEM???":
			dialog.text = "You see, "+ GetSexPhrase("my young captain", "madam") +", I'm going to solve the main mystery of natural philosophy - the secret of immortality! With this herb, I intend to create a potion that will allow me to live forever!";
			link.l1 = "Clear. Okay, if after you swallow this potion, you suddenly find that the balls bounce off you, please let me know.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Lechenie_s_voprosom";

			CloseQuestHeader("PDM_Aptekar");
		break;

		case "Alumnus_Lechenie_s_voprosom":	//Для Грегга
			dialog.text = "... but here the element of fire is represented by the aroma of cinnamon, whose dominance is balanced by the smell... Oh, Captain, I didn't notice you, what can I do for you?";
			link.l1 = "Hello, Dr. Alumnus, I would like u to examine my wounded officers.";
			link.l1.go = "CheckForConfuse";
			link.l2 = "Why is your door closed from the street? You're missing out on customers.";
			link.l2.go = "Alumnus_Lechenie_s_voprosom_2";
			link.l3 = "Just checking on you. Goodbye.";
			link.l3.go = "exit";	//Для выхода
			if(CheckAttribute(PChar, "Luke.BadPoison"))
			{
				link.l4 = "Doctor, I really need your help, I was poisoned with a very strong poison!";
				link.l4.go = "LukePoison";
			}
		break;

		case "Alumnus_Lechenie_s_voprosom_2":
			dialog.text = "You see, my house is located right between the docks and the tavern, if I keep the door open, random visitors constantly come here, who try to knock over one of my tinctures. I then had to bring one such 'guest' to my senses for a whole week, and I do not feel a shortage of customers in any way, everyone in the city knows this shop, from the governor to the longshoreman.";
			link.l1 = "Okay, I get it. Can you examine my wounded officers?";
			link.l1.go = "CheckForConfuse";
			link.l2 = "It was very interesting. Goodbye.";
			link.l2.go = "exit";

			NextDiag.TempNode = "Alumnus_Lechenie";
		break;

		case "Alumnus_Lechenie":
			dialog.text = "... but here the element of fire is represented by the aroma of cinnamon, whose dominance is balanced by the smell... Oh, Captain, I didn't notice you, what can I do for you?";
			link.l1 = "Hello, Dr. Alumnus, I would like to examine my wounded officers.";
			link.l1.go = "CheckForConfuse";
			link.l2 = "Just checking on you. Goodbye.";
			link.l2.go = "exit";
			if(CheckAttribute(PChar, "Luke.BadPoison"))
			{
				link.l3 = "Doctor, I really need your help, I was poisoned with a very strong poison!";
				link.l3.go = "LukePoison";
			}
		break;

		case "CheckForConfuse":
			dialog.text = "Who exactly needs medical attention, Captain?";
			for(i=0; i<GetPassengersQuantity(pchar); i++)
			{
				iOfficer = GetPassenger(pchar, i);
				sld = GetCharacter(iOfficer);
				if (!GetRemovable(sld)) continue;
				if (!CheckAttribute(sld, "HPminusDaysNeedtoRestore")) continue;
				attrL = "l"+i;
				Link.(attrL)	= "Officer " + GetFullName(sld) + ".";
				Link.(attrL).go = "OfficerConfusedSel_" + i;
			}
			Link.l99 = "No one at the moment.";
			Link.l99.go = "exit";
		break;

		case "OfficerConfused":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));

			if (!CheckAttribute(chref, "quest.officertype")) offtype = "Universal";
			else offtype = XI_ConvertString(chref.quest.officertype);
			dialog.Text = "You mean " + GetFullName(chref)+", specialization is "+offtype+".";
			Link.l1 = "Yes, exactly.";
			Link.l1.go = "OfficerConfused_2";
			Link.l99 = "No, I changed my mind.";
			Link.l99.go = "exit";
		break;

		case "OfficerConfused_2":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));
			if (CheckAttribute(chref, "chr_ai.max_hp")) npchar.HealPrice = (makeint(chref.chr_ai.max_hp)*100)+makeint((sti(chref.rank)*500)*(MOD_SKILL_ENEMY_RATE*3/2));
			else npchar.HealPrice = (makeint(chref.health.maxhp)*100)+makeint((sti(chref.rank)*500)*(MOD_SKILL_ENEMY_RATE*3/2));
			dialog.Text = "According to forecasts, this officer is in "+(sti(chref.HPminusDaysNeedtoRestore)-sti(chref.HPminusDays))+" days away from a complete natural cure... I could try to speed up the recovery process, but it will cost you "+FindRussianMoneyString(sti(npchar.HealPrice));
			if (sti(pchar.money)>=sti(npchar.HealPrice))
			{
				Link.l1 = "Okay, I'm ready to pay.";
				Link.l1.go = "OfficerConfused_3";
			}
			Link.l99 = "Probably not, I'm still a little strapped for money.";
			Link.l99.go = "exit";
		break;

		case "OfficerConfused_3":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));
			AddMoneyToCharacter(pchar,-sti(npchar.HealPrice));
			LAi_Fade("", "");
			WaitDate("",0,0,0, 0, 60);
			DeleteAttribute(chref, "HPminusDays");
			DeleteAttribute(chref, "HPminusDaysNeedtoRestore");
			Log_Info("Officer " + GetFullName(chref) + " recovered.");
			dialog.Text = "I managed to completely heal " + GetFullName(chref) + ". Although I must admit that it was very difficult...  Is that all, or does someone else need my help?";
			Link.l1 = "No, there are still those in need.";
			Link.l1.go = "CheckForConfuse";
			Link.l99 = "That's it for now. Thank you for your help.";
			Link.l99.go = "exit";
		break;

		case "LukePoison":
			dialog.text = "Captain, let me examine you... Yes, this poison was made from very rare and harmful herbs! But don't worry, I know how to treat it. And now, "+pchar.name+"Get into bed, I'll take care of you soon.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("HealingPoison");
		break;
		
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery in broad daylight!!! What is going on?! Well, wait, "+ GetSexPhrase("buddy","girlfriend") +"...", "Hey, what are you doing there?! No way, you decided to rob me? Well, then you're finished...", "Wait, where are you going? You are a thief! Well, consider that you have sailed, bitch...");
			link.l1 = LinkRandPhrase("Devil!!", "Carramba!!", "Oh, damn!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
