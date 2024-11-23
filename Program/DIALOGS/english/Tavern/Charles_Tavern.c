// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question, " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Are we going to ask questions again?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now..."), "Hmm, something happened to my memory...",
                      "Yes, really for the third time...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "toSeekSister")
			{
				link.l1 = "Buddy, I'm looking for a young lady named Elizabeth Sheppard. Have you ever heard of such a thing?";
				link.l1.go = "MCLiz";
			}
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_NevisTaverna_1"))
			{
				link.l1 = "I am interested in whether a black frigate vessel has entered the port.";
				link.l1.go = "BlackFregat_1";
			}
		break;
//========================  Квест "Strange things are happening in the archipelago" ==>
		case "BlackFregat_1":
			dialog.text = "Black frigate? Let me think about it... No, he definitely didn't come to us, but I know one guy who seems to have run into him.";
			link.l1 = "And? How can I talk to this person?";
			link.l1.go = "BlackFregat_2";
		break;
		case "BlackFregat_2":
			dialog.text = "Yes, there he is sitting at a small round table. If I'm not mistaken, his name is Balltezar Figueidal.";
			link.l1 = "Okay. I'll go talk to him.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_NevisTaverna_1");
			
			sld = CharacterFromID("PKM_SvpvA_Shturman_1")
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Shturman_v_taverne_2";			
		break;
//========================  Квест "Strange things are happening in the archipelago" <==		
		case "MCLiz":
			dialog.text = "Miss Liz Sheppard is a resident of our city. What do you want from her?";
			link.l1 = "You see, she forgot something in Maracaibo Bay...";
			link.l1.go = "MCLiz_1";
		break;
		case "MCLiz_1":
			dialog.text = "Yes, Liz has been traveling a lot lately. You won't find her in the city.";
			link.l1 = "Where is she now?";
			link.l1.go = "MCLiz_2";
		break;
		case "MCLiz_2":
			dialog.text = "Now at home.";
			link.l1 = "Does she have her own house?";
			link.l1.go = "MCLiz_3";
		break;
		case "MCLiz_3":
			dialog.text = "Yes, her father's house.";
			link.l1 = "And who is her father?";
			link.l1.go = "MCLiz_4";
		break;
		case "MCLiz_4":
			dialog.text = "Well, it's a very quiet thing to say, but I'll tell you.\n"+
				"Have you heard about Captain Staton? No? Ho ho, then know that Captain Staton, one of the first filibusters, is Liz's father. In his time, when he was still alive, captain did a lot for the development of the city, so the people of Nevis owe him.";
			link.l1 = "Elizabeth has the surname Sheppard.";
			link.l1.go = "MCLiz_5";
		break;
		case "MCLiz_5":
			dialog.text = "That's what captain decided. When he settled with his family in the city, he took a different surname. Just in case...";
			link.l1 = "And Liz lives alone now?";
			link.l1.go = "MCLiz_6";
		break;
		case "MCLiz_6":
			dialog.text = "Yes, her mother briefly outlived her husband and is buried here on the island. And Danielle hasn't been home in two years.";
			link.l1 = "Daniel?";
			link.l1.go = "MCLiz_7";
		break;
		case "MCLiz_7":
			dialog.text = "Liz's older sister.";
			link.l1 = "Understood. Well, thank you, buddy.";
			link.l1.go = "MCLiz_8";
		break;
		case "MCLiz_8":
			dialog.text = "You're welcome. I hope you brought Liz some good news. She's a good girl, Captain...";
			link.l1 = "Anyway, nothing bad. That's for sure.";
			link.l1.go = "exit";
			pchar.questTemp.MC = "toSeekSisterAT";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

