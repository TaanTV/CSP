// Тичингиту - индеец-офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	sAttr = Dialog.CurrentNode;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Did you want something?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Tichingitu":
			dialog.text = "What do you want, paleface? Tichingitu has no words for you.";
			link.l1 = "Is your name Tichingitu? Hmm. Listen, warrior, I'm here not to stare at you, but to ask: why did you climb into this Askold's house?";
			link.l1.go = "Tichingitu_1";
		break;

		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Are you silent? Stupidly. You'll be hanged for stealing and that's it. Tell me why you did this act-maybe I can help you.";
			link.l1.go = "Tichingitu_2";
		break;

		case "Tichingitu_2":
			dialog.text = "Tichingitu come to the city of the palefaces through many, many roads, through a large river, from a country of large forests and swamps. Tichingitu gets tired and wants to eat. Tichingitu is starving to death. No one wants to help Tichingitu, shout - out, red dog. The innkeeper kicked the Indian out like a mangy dog. Tichingitu wants to eat.";
			link.l1 = "Damn it, but then why did you come to this settlement from... your forest?";
			link.l1.go = "Tichingitu_3";
		break;

		case "Tichingitu_3":
			dialog.text = "To expel Tichingitu from his native tribe. Tichingitu quarrel shaman tribe, shaman say chief, shaman curse Tichingitu - Tichingitu leave the tribe, away-away from the native camp. Tichingitu is not at home, there are no weapons, there is nothing.";
			link.l1 = "Yeah, you're out of luck. Well, why did you quarrel with your people?";
			link.l1.go = "Tichingitu_4";
		break;

		case "Tichingitu_4":
			dialog.text = "The shaman of our tribe is an evil man. He says - my wife is possessed by an evil spirit, my wife must die. My wife is just sick, the spirit does not move in. I am a heal wife, a shaman kill wife. Tichingitu stand up against the shaman, everyone stand up against Tichingitu, Tichingitu leave.";
			link.l1 = "Did you try to save your wife? Is that why you were expelled from the village?";
			link.l1.go = "Tichingitu_5";
		break;

		case "Tichingitu_5":
			dialog.text = "So, paleface, Tichingitu doesn't have a choice - either steal or starve...";
			link.l1 = "Here's the problem... To hang a man on a piece of food for a few pitiful coins... Tichingitu, I'll try to help you. I know Askold, the guy whose house you broke into. Maybe I can do something... I'll talk to the commandant now.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Tichingitu = "commandante";
			AddQuestRecord("Ascold", "3_1");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("", "а"));
		break;

		case "Tichingitu_wait":
			dialog.text = "Tichingitu wait. An Indian is not afraid of death. The shaman curses Tichingitu - Tichingitu must die.";
			link.l1 = "All is not lost yet. I'm trying to help...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;

		case "Tichingitu_6":
			dialog.text = "Tichingitu wait. An Indian is not afraid of death. The shaman curses Tichingitu - Tichingitu must die.";
			link.l1 = "Don't be so pessimistic. Your ordeal is over. I dealed your release.";
			link.l1.go = "Tichingitu_7";
		break;

		case "Tichingitu_7":
			dialog.text = "Paleface joking? Is Tichingitu free?";
			link.l1 = "No kidding. They're going to open your cell and let you out. Follow me, I'll get you out of jail.";
			link.l1.go = "Tichingitu_8";
		break;

		case "Tichingitu_8":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("BasTer_exittown", "rld", "aloc9", "TichingituFree"); // 170712
			pchar.quest.FreeTichingituOver.over = "yes"; //снять таймер
		break;

		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "Here you are again at large. Take a walk, Tichingitu, look out, don't steal and don't get caught anymore! You'd better find some Indian village and live with your own-I don't think they'll refuse to accept you.";
			link.l1.go = "Tichingitu_10";
		break;

		case "Tichingitu_10":
			dialog.text = "Tichingitu not to go. Master save Tichingitu's life. Tichingitu stay. Tichingitu's life belongs to the master.";
			link.l1 = "What? What are you talking about? I'm not a master! Didn't you understand - you're free! Go!";
			link.l1.go = "Tichingitu_11";
		break;

		case "Tichingitu_11":
			dialog.text = "Indian in debt, white master. Tichingitu will serve you faithfully. Tichingitu should be able to fight. Tichingitu to die in battle for his state"+GetSexPhrase("din", "zha")+". He's staying.";
			link.l1 = "Ugh, you devil... I am not your master, Tichingitu. I helped you cause of my kindness, but not to turn you into a slave.";
			link.l1.go = "Tichingitu_12";
		break;

		case "Tichingitu_12":
			dialog.text = "Tichingitu is not a slave, white "+ GetSexPhrase("man", "woman")+". Tichingitu is a free Indian. Tichingitu wants to serve you. An Indian can fight, any dog can die before approaching the state"+ GetSexPhrase("dean", "zha")+". Tichingitu should be able to clean and load a musket. Tichingitu should be able to shoot a musket.";
			link.l1 = "Although... You know, Tichingitu, it's not a bad idea. I need the right people, and you seem like a good person to me. And you can shoot a musket. And what are you going to do alone? If you get caught stealing again, then they'll definitely hang you... All right, stay. But keep in mind: there will be no quiet life with me.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "That's enough. Go in peace, red-skinned brother. May your gods protect you!";
			link.l2.go = "Tichingitu_exit";
		break;

		case "Tichingitu_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Tichingitu");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterReputation(pchar, 1);
			AddQuestRecord("Ascold", "3_5");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("", "а"));
		break;

		case "Tichingitu_13":
			dialog.text = "Tichingitu is not afraid of anything, white "+GetSexPhrase("man", "woman")+". Tichingitu will be glad to serve you. The captain will be faithful to Tichingitu until his last breath.";
			link.l1 = "Okay. Welcome to the team, Tichingitu!";
			link.l1.go = "Tichingitu_hire";
		break;

		case "Tichingitu_hire":
			DialogExit();
			npchar.HalfImmortal = true;
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = sti(pchar.rank)*20;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.CanTakeMushket = true;
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			NextDiag.CurrentNode = "hired";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			DeleteAttribute(pchar, "questTemp.Tichingitu");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterReputation(pchar, 1);
			AddQuestRecord("Ascold", "3_4");
		break;

	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Tichingitu listen to you, Captain "+pchar.name+"!";
			Link.l1 = "Listen to my order!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nothing yet. At ease!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;

		case "stay_follow":
            dialog.Text = "What are the orders?";
			if (CheckAttribute(npchar, "IsMushketer"))
			{
				Link.l3 = "I want you to keep a certain distance from the target.";
				Link.l3.go = "TargetDistance";
			}
            Link.l1 = "Stay here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
			if (!CheckAttribute(npchar, "AboardRestriction"))
			{
				Link.l4 = "I ask you not to participate in the boarding. Take care of yourself.";
				Link.l4.go = "AboardRestriction";
			}
			else
			{
				Link.l4 = "I've changed my mind, you can participate in the boarding.";
				Link.l4.go = "AboardAllowed";
			}
		break;

		case "AboardRestriction":
			npchar.AboardRestriction = true;
			dialog.text = "That's right captain. I will not participate in boarding until you allow it again.";
            Link.l1 = "That's good.";
            Link.l1.go = "exit";
		break;

		case "AboardAllowed":
			DeleteAttribute(npchar, "AboardRestriction");
			dialog.text = "That's right captain. I will participate in boarding from now on.";
            Link.l1 = "That's good.";
            Link.l1.go = "exit";
		break;

        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "There is a change of location!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;

        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "There is a change of location!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
        break;

		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "Which one exactly, Captain? Specify the Tichingite in yards, but not more than twenty.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;

		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Captain, forgive Tichingitu, but I don't understand you.";
				link.l1 = "Sorry, I mistaken...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tiching should be standing still, not moving anywhere. Is that what you want, Captain?";
				link.l1 = "Yes, that's exactly what is required of you.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu cannot get up from the target more than twenty yards away. Then he'll miss.";
				link.l1 = "Okay, then keep twenty yards away.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu to understand everything. Tichingitu to take a position at the specified distance.";
			link.l1 = "Okay.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
