
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
		case "First time":
			dialog.text = "Oh, another white one has arrived. What brought you to Tenochtitlan?";
			link.l1 = "See what's what. "+ GetSexPhrase("That's the kind of person I am", "That's the way I am") +" - I want to know everything.";
			link.l1.go = "FT_1";
			if (pchar.questTemp.Teno == "takeFire")
			{
				dialog.text = "Hello, "+ GetSexPhrase("white man", "white squaw") +". Why are you here?";
				link.l1 = "See what's what. "+ GetSexPhrase("That's the kind of person I am", "That's the way I am") +" - I want to know everything. I take it you're an Aztec, buddy.";
				link.l1.go = "FTS_1";
			}
		break;
		case "FT_1":
			dialog.text = "Understood... But do you even know where you got?";
			link.l1 = "I know that this city is the Indian capital. And that Cortez himself walked here with fire and sword.";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Yes, it is. This city has the name Tenochtitlan, and the people who lived here for centuries were called Aztecs.";
			link.l1 = "Clear. And you're an Aztec too, I take it?";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Yes, I am an Aztec, you guessed it. My name is Montezuma. What can I call you?";
			link.l1 = "My name is captain " + GetFullName(pchar) + ". Montezuma... I think that was the name of the Indian chief.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "I am named after him. Tell me, "+ GetSexPhrase("white captain", "beautiful squaw") +" " + GetFullName(pchar) + ", what are you going to do next?";
			link.l1 = "I want to get into the city.";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "You probably realized that this is not so easy to do. The dam to the city is reliably protected by a fire spell. Quite recently, there were a lot of white people here. They all burned down...";
			link.l1 = "Well, not everything. As far as I know, you cracked someone's skull.";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "It is true, but they are to blame for their own death. You shouldn't have touched Montezuma.";
			link.l1 = "Okay, let's not talk about it. Tell me better, what is there interesting in the city? Does someone live there, or not? And what are you doing here on this coast?";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "Oh, it's a long story. Get ready to listen, "+ GetSexPhrase("white captain", "beautiful squaw") +"\n"+
				"My ancestors came to the shores of this lake called Texcoco many centuries ago. Then they were called meshiki. The shores of the lake were inhabited by other tribes who were hostile to the newcomers. But our supreme god, Huitzilopochtli, ordered them to stay here. Then the leader of the Meshiks, Tenoch, decided to stay on the shores of Texcoco, and the meshiks began to be called tenochki\n"+
				"Koshkoshtli, the leader of the powerful city of Kuluakan, plotted to exterminate the Tenochki. Then my ancestors left the coast and began to live on a swampy island in the middle of the lake. Time passed, and the shadows managed to strengthen the island and even build a dam to the shore. And when the tenochki chose Itzcoatl as their leader, a confederation of tribes was created, and the peoples of the confederation became known as the Aztecs\n"+
				"These are blessed times, the Aztecs ruled the world. All the tribes paid taxes to the Aztecs, supplied food, slaves and concubines. Sacrificial blood-the food of our gods-made the waters of Texcoco red. Noble warriors were sacrificed to Tezcatlipoca, the patron saint of the priests, and ordinary warriors were burned in honor of Kamashtli. The women gave their blood to the goddess Mayahuel, and the children to the fertility god Tlaloc\n"+
				"It's been like this for over a hundred years. But then the Spaniards came and Tenochtitlan was besieged. And our heroes fell, led by Cuauhtemoc\n"+
				"Tenochtitlan is now ruled by the god of the realm of the dead, Mictlantecutli.";
			link.l1 = "So the city is uninhabited?";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "Inhabited. Both living people and dead people live there.";
			link.l1 = "What?";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = "Miktlantekutli has the power to resurrect people. Mictlantecutli brought warriors back to life to guard the temples of the gods, and there are also living Aztecs.";
			link.l1 = "Why don't you live in Tenochtitlan?";
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = "I was expelled by Miktlantekutli. As long as his power is unlimited, I can't go back, Listen to me, "+ GetSexPhrase("white captain", "beautiful squaw") +". Now I'm going to offer you a deal that I make with everyone who comes here.";
			link.l1 = "I'm listening to you, Montezuma.";
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = "If you can reduce the power of Mictlantecutli, then I will help you gain power. There is a weapon in the temple of the White Gods, which has no equal and will not be. You can have it for yourself.";
			link.l1 = "What do you need?";
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = "The jade skull of Mictlantecutli. He is in the temple of the Great Life Force.";
			link.l1 = "I understand it won't be easy to get there.";
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = "I'll give you some advice.";
			link.l1 = "Why don't you come to the city with me? You'll swing your club, crack skulls...";
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = "Club?! You're a club! This is the obsidian sword of Macquahuitl! Did you know that our obsidian spears and swords terrified the Spaniards more than the iron ones?";
			link.l1 = "I'm sorry, Montezuma, for asking, but then why did you lose the war?";
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			dialog.text = "Our gods have turned away from us...";
			link.l1 = "Gods again...";
			link.l1.go = "FT_17";
		break;
		case "FT_17":
			dialog.text = "Gods decide everything, not people. One of my ancestors tried to solve everything for the gods, and he was wrong. The price he paid for this mistake was prohibitively high. Okay, let's talk about the deal. Do you agree to sneak into Tenochtitlan and bring me a jade skull?";
			link.l1 = "I'm ready to try it.";
			link.l1.go = "FT_18";
		break;
		case "FT_18":
			dialog.text = "Okay. Then, first of all, you need to remove the fire spell from the dam leading into the city.";
			link.l1 = "And how do I do this? Who was able to organize such a thing?";
			link.l1.go = "FT_19";
		break;
		case "FT_19":
			dialog.text = "Miktlantekutli, who else? By the power of Kamashtli, the god of war and fate, he cast a fire spell on the dam. For Kamashtli is the creator of fire.";
			link.l1 = "Understood... Well, how do I remove this fire?";
			link.l1.go = "FT_20";
		break;
		case "FT_20":
			dialog.text = "There are two ways. The first is to find the Kamashtli totem, get through the fire into the city, and insert this Totem into the sacrificial stone, which is located near the entrance to the city.";
			link.l1 = "Get through the fire? So, I'm going to burn!";
			link.l1.go = "FT_21";
		break;
		case "FT_21":
			dialog.text = "There is no fire on the wooden isthmus of the dam. You can rest there.";
			link.l1 = "Clear... And the second way?";
			link.l1.go = "FT_22";
		break;
		case "FT_22":
			dialog.text = "Find two totems - the goddess Tlasolteotl, the devourer of dirt, and the god of heaven and sun Tonatiu. Then insert them into the sacrificial stones that are on the shore in front of the dam. Then the spell will be lifted and you can safely go to Tenochtitlan.";
			link.l1 = "Understood. And where are these totems to be found?";
			link.l1.go = "FT_23";
		break;
		case "FT_23":
			dialog.text = "I can't tell you this, otherwise our deal will lose its meaning, but I can hint...";
			link.l1 = "Well, give me a hint.";
			link.l1.go = "FT_24";
		break;
		case "FT_24":
			dialog.text = "The Kamashtli totem is closer than you think. The Tlasolteotl totem is located nearby, in the grass. And the Tonatiu totem is abandoned in the jungle between two Spanish cities that are located on the isthmus between the continents.";
			link.l1 = "Damn! Is there no way to be more precise?";
			link.l1.go = "FT_25";
		break;
		case "FT_25":
			dialog.text = "Nothing. Search, "+ GetSexPhrase("white captain", "beautiful squaw") +". I've said it all, now it's up to you.";
			link.l1 = "Okay, I'll look for...";
			link.l1.go = "exit";
			npchar.location.locator = "quest1";
			NextDiag.TempNode = "Fire";
			AddDialogExitQuestFunction("Teno_MontesumaGoQuest1");
		break;
		//--------------
		case "FTS_1":
			dialog.text = "Yes, I am an Aztec, you guessed it. My name is Montezuma. What can I call you?";
			link.l1 = "My name is captain " + GetFullName(pchar) + ". Montezuma... I think that was the name of the Indian chief.";
			link.l1.go = "FTS_2";
		break;
		case "FTS_2":
			dialog.text = "I am named after him. Tell me, "+ GetSexPhrase("white captain", "beautiful squaw") +" " + GetFullName(pchar) + ", what are you going to do next? You did manage to remove the fire spell!";
			link.l1 = "I will search the city properly. Maybe I'll find something worthwhile.";
			link.l1.go = "FTS_3";
		break;
		case "FTS_3":
			dialog.text = "I want to make you an offer, white captain.";
			link.l1 = "Listen to you, Montezuma.";
			link.l1.go = "FTS_4";
		break;
		case "FTS_4":
			dialog.text = "Okay. Listen carefully, "+ GetSexPhrase("white captain", "beautiful squaw") +"\n"+
				"My ancestors came to the shores of this lake, called Texcoco, many centuries ago. Then they were called meshiki. The shores of the lake were inhabited by other tribes who were hostile to the newcomers. But our supreme god, Huitzilopochtli, ordered them to stay here. Then the leader of the Meshiks, Tenoch, decided to stay on the shores of Texcoco, and the meshiks began to be called tenochki\n"+
				"Koshkoshtli, the leader of the powerful city of Kuluakan, plotted to exterminate the Tenochki. Then my ancestors left the coast and began to live on a swampy island in the middle of the lake. Time passed, and the tenochki managed to strengthen the island and build a stone city and even a dam to the shore. And when the tenochki chose Itzcoatl as their leader, a confederation of tribes was created, and the peoples of the confederation became known as the Aztecs\n"+
				"These are blessed times, the Aztecs ruled the world. All the tribes paid taxes to the Aztecs, supplied food, slaves and concubines. Sacrificial blood-the food of our gods-made the waters of Texcoco red. Noble warriors were sacrificed to Tezcatlipoca, the patron saint of the priests, and ordinary warriors were burned in honor of Kamashtli. The women gave their blood to the goddess Mayahuel, and the children to the fertility god Tlaloc\n"+
				"It's been like this for over a hundred years. But then the Spaniards came and Tenochtitlan was besieged. And our heroes fell, led by Cuauhtemoc\n"+
				"Tenochtitlan is now ruled by the god of the realm of the dead, Mictlantecutli.";
			link.l1 = "So the city is uninhabited?";
			link.l1.go = "FTS_5";
		break;
		case "FTS_5":
			dialog.text = "Inhabited. Both living people and dead people live there.";
			link.l1 = "What?";
			link.l1.go = "FTS_6";
		break;
		case "FTS_6":
			dialog.text = "Mictlantecutli has the power to resurrect people. Mictlantecutli brought warriors back to life to guard the temples of the gods, and there are also living Aztecs.";
			link.l1 = "Why don't you live in Tenochtitlan?";
			link.l1.go = "FTS_7";
		break;
		case "FTS_7":
			dialog.text = "I was expelled by Miktlantekutli. As long as his power is unlimited, I can't go back, Listen to me, "+ GetSexPhrase("white captain", "beautiful squaw") +". Now I'm going to offer you a deal that I make with everyone who comes here.";
			link.l1 = "I'm listening to you, Montezuma.";
			link.l1.go = "FTS_8";
		break;
		case "FTS_8":
			dialog.text = "If you can reduce the power of Mictlantecutli, then I will help you gain power. There is a weapon in the temple of the White Gods, which has no equal and will not be. You can have it for yourself.";
			link.l1 = "What do you need?";
			link.l1.go = "FTS_9";
		break;
		case "FTS_9":
			dialog.text = "The jade skull of Mictlantecutli. He is in the temple of the Great Life Force.";
			link.l1 = "I understand it won't be easy to get there.";
			link.l1.go = "FTS_10";
		break;
		case "FTS_10":
			dialog.text = "I'll give you some advice.";
			link.l1 = "Why don't you come to the city with me? You'll swing your club, crack skulls...";
			link.l1.go = "FTS_11";
		break;
		case "FTS_11":
			dialog.text = "Club?! You're a club! This is the obsidian sword of Macquahuitl! Did you know that our obsidian spears and swords terrified the Spaniards more than the iron ones?";
			link.l1 = "I'm sorry, Montezuma, for asking, but then why did you lose the war?";
			link.l1.go = "FTS_12";
		break;
		case "FTS_12":
			dialog.text = "Our gods have turned away from us...";
			link.l1 = "Gods again...";
			link.l1.go = "FTS_13";
		break;
		case "FTS_13":
			dialog.text = "Gods decide everything, not people. One of my ancestors tried to solve everything for the gods, and he was wrong. The price he paid for this mistake was prohibitively high. Okay, let's talk about the deal. Do you agree to sneak into Tenochtitlan and bring me a jade skull?";
			link.l1 = "I'm ready to try it.";
			link.l1.go = "FTS_14";
		break;
		case "FTS_14":
			dialog.text = "Okay. Now listen to what you owe to do.";
			link.l1 = "I'm listening to you, Montezuma.";
			link.l1.go = "Fire_1";
		break;
		//после снятия огня
		case "Fire":
			if (CheckAttribute(loadedLocation, "gotoFire"))
			{
				dialog.text = "The fire spell has not been lifted from the dam yet.";
				link.l1 = "Not yet, but I'm working on it.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "You managed remove the fire spell, that's good. Now listen to what you have to do next.";
				link.l1 = "I'm listening carefully, Montezuma.";
				link.l1.go = "Fire_1";
			}
		break;
		case "Fire_1":
			dialog.text = "You got access to Tenochtitlan and you can enter the temples of the gods. The jade skull I need is in the temple of the Great Life Force. To get access there, you must collect 10 totems of gods and place them on sacrificial stones of 10 temples.";
			link.l1 = "And where are these temples located?";
			link.l1.go = "Fire_2";
		break;
		case "Fire_2":
			dialog.text = "Five in the pyramid to the left of the temple of the Great Life Force, five to the right of it. The small pyramids have five entrances, each of which leads to the temple of its god. Above each entrance you can see an image of the god who owns this temple. It's better to watch at noon, so you can't make mistakes at the entrance, because with each visit you make, the strength of the temple guards will grow.";
			link.l1 = "Is there also a temple guard there?";
			link.l1.go = "Fire_3";
		break;
		case "Fire_3":
			dialog.text = "Yes, the resurrected Mictlantecutli Aztec warriors. You'll have to fight them. You won't be able to take helpers inside the temples, so only you will have to do everything.";
			link.l1 = "Yeah, the bad news... what are those 10 totems I'm supposed to find?";
			link.l1.go = "Fire_4";
		break;
		case "Fire_4":
			dialog.text = "You have to find the following totems: Xochiquetzalcoatl, goddess of flowers and love. Mictlantecutli, god of the dead already known to you. Pcetzalcoatl, god of the morning star, lord of the elements. Mishcoatl, god of hunting. Tescatlipoca, patron of the priests. Ptalcihuitlicue, goddess of the sea and lakes. Puitzilopochtli, god of the blue clear sky. Tlaloka, god of thunder and rain. Mayahuel, the goddess of fertility. Tonakatekutli, the creator god who gives food to people.";
			link.l1 = "Understood. Now tell me where to get these totems.";
			link.l1.go = "Fire_5";
		break;
		case "Fire_5":
			dialog.text = "No, I can't do that. Search for them all over the world yourself.";
			link.l1 = "Great news! Listen, don't you need a jade skull? You're not showing much zeal in this case.";
			link.l1.go = "Fire_6";
		break;
		case "Fire_6":
			dialog.text = "That's all I can do. There are reasons for everything I do, believe me.";
			link.l1 = "Understood... Well, then wait until I can get these totems, get into the temple and bring you the skull. I'm afraid it's going to be a long wait.";
			link.l1.go = "Fire_7";
		break;
		case "Fire_7":
			dialog.text = "I'll be waiting, "+ GetSexPhrase("white captain", "beautiful squaw") +". That's the only thing left for me...";
			link.l1 = "Well, see you then.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Totem";
			pchar.questTemp.Teno = "openTenTemples";
			AddQuestRecord("Tenochtitlan", "3");
			AddQuestUserData("Tenochtitlan", "sSex", GetSexPhrase("en", "on"));
		break;

		case "Totem":
			dialog.text = "You don't have a jade skull! I'm waiting for you to bring it to me, "+ GetSexPhrase("white captain", "beautiful squaw") +".";
			link.l1 = "I'm doing this, Montezuma.";
			link.l1.go = "exit";
		break;

        //после драки с
		case "AfterGTemple":
			if (CheckCharacterItem(pchar, "SkullAztec")) //череп найден
			{
				dialog.text = "You got the jade skull of Mictlantecutli! Give it to me!!!";
				if (CheckCharacterItem(pchar, "pistol7"))
				{
					link.l1 = "And what do I get for it? I didn't get it easy, you know...";
					link.l1.go = "Skull_1";
				}
				else
				{
					link.l1 = "Not so fast, buddy! You promised me some kind of powerful weapon. I still haven't found anything.";
					link.l1.go = "NotShootgun_1";
				}
			}
			else
			{
				dialog.text = "You were in the Temple of the Great Life Force. But you don't have the jade skull with you. Why didn't you take him?";
				link.l1 = "I didn't find it.";
				link.l1.go = "NotSkull";
			}
		break;
		//с собой нет черепа
		case "NotSkull":
			dialog.text = "You're lying, "+ GetSexPhrase("white captain", "white squaw") +". Montezuma will punish you for this!";
			link.l1 = "Well, try...";
			link.l1.go = "NotSkull_1";
		break;
		case "NotSkull_1":
			chrDisableReloadToLocation = true;
			LAi_group_SetRelation("MontesumaGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("MontesumaGroup", LAI_GROUP_PLAYER, true);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NotShootgun_1":
			dialog.text = "The weapon is in the Temple of the White Gods, I told you so!";
			link.l1 = "It's closed.";
			link.l1.go = "NotShootgun_2";
		break;
		case "NotShootgun_2":
			dialog.text = "The temple opens an obsidian knife, which the priests use to open the victims' hearts. Find him and you will be able to open the temple.";
			link.l1 = "Where can I find him?";
			link.l1.go = "NotShootgun_3";
		break;
		case "NotShootgun_3":
			dialog.text = "In the Temple of the Great Life Force, now give me the skull!";
			link.l1 = "One indication that the weapon is in some kind of temple is not enough for me. And what else can I get of value? It wasn't easy for me to get this skull, you know...";
			link.l1.go = "Skull_1";
		break;

		case "Skull_1":
			dialog.text = "Do you dare to contradict me, fool?! You don't know who you're talking to!";
			link.l1 = "I know. You are Montezuma II, the last ruler of the Aztecs. Mictlantecutli told me that.";
			link.l1.go = "Skull_2";
		break;
		case "Skull_2":
			dialog.text = "This is the last time I ask you to give me the jade skull. I helped you get it, we have a deal!";
			link.l1 = "Why do you need it?";
			link.l1.go = "Skull_3";
		break;
		case "Skull_3":
			dialog.text = "With his help, I will bring my people back to life. Tenochtitlan will regain its power, and the Aztec empire will conquer the nations!";
			link.l1 = "Your gods have turned their backs on the Aztecs. And your people are gone.";
			link.l1.go = "Skull_4";
		break;
		case "Skull_4":
			dialog.text = "I will raise my people from the graves with the help of a jade skull! And we will find new gods for ourselves, appease them with the blood of slaves. The Aztecs will regain their power, but now we will have experience. I will not repeat the mistakes of the past, and the white people will pay for their treachery!";
			link.l1 = "I will not give you the skull, Montezuma. You've painted a picture here that I don't like.";
			link.l1.go = "Skull_5";
		break;
		case "Skull_5":
			dialog.text = "Then prepare to die.";
			link.l1 = "Get ready you too. I have sustained a fight with Mictlantecutli himself, and I will definitely send you to his permanent place of residence.";
			link.l1.go = "Skull_6";
		break;
		case "Skull_6":
			dialog.text = "I can't die a second time, "+ GetSexPhrase("white captain", "white squaw") +"!";
			link.l1 = "I have a jade skull, and it gives power over the dead. So it's over you. I guess that changes everything.";
			link.l1.go = "Skull_7";
		break;
		case "Skull_7":
			AddQuestRecord("Tenochtitlan", "5");
			AddQuestUserData("Tenochtitlan", "sSex", GetSexPhrase("xia", "as"));
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Tenochtitlan", "reload1_back", false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "MontesumaGroup");
			LAi_group_SetRelation("MontesumaGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("MontesumaGroup", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("MontesumaGroup", "OpenTheDoors");
			pchar.quest.Teno_clearGroups.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Teno_clearGroups.win_condition.l1.location = pchar.location;
			pchar.quest.Teno_clearGroups.function = "Teno_clearGroups";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
