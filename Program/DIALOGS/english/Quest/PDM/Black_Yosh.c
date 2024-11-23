
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

		case "First time":							//Автор Sinistra
			dialog.text = "Wow? Who is it? Hey... hic... I like you... hic... Don't know?";
			link.l1 = "My name is "+pchar.name+". What are you doing here?";
			link.l1.go = "Kristofer_1";
			//PlayVoice("Kopcapkz\Voices\PDM\пьяница.wav");
		break;

		case "Kristofer_1":
            dialog.text = "Can't you see? I'm s-s-s-celebrating. I'm an appointment... ic... p-got on the frigate. That's what he said... hic. Hey, hey, HEY! You're trying to... hic... to find out... Mr. State... t-a secret! I'm arresting you...";
            link.l1 = "No, buddy, you're wrong. I'm not going to pry a state secret out of you at all. You're the one trying to tell me... My God, what kind of stuff are you drinking?";
			link.l1.go = "Kristofer_2";
		break;
		
		case "Kristofer_2":
            dialog.text = "Ah. This. What am I talking about? I want to say... hic... If you buy me a drink, I'll tell you a state t-secret. Ic... If I remember, I remember.";
            link.l1 = "Yes? A real state secret? Stunningly. I'll buy you a drink.";
			link.l1.go = "Kristofer_3";
			link.l2 = "What can a drunken brute like you know about state secrets? You're drunk as a pig. Leave me alone.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristofer_6_snova";
			npchar.lifeday = 0;
		break;
		
		case "Kristofer_3":
            dialog.text = "But don't cheat. If I run out of rum... ick... I'll be mute, like... like... like something out there. Shh! Shh! P-get closer! Still! These frigates? P-p-p-were they for p-p-rearmament? They... JUNK! Damn ruins! A bunch of Indians in their canoes can d-sink them.";
            link.l1 = "But then what's the point of all this? Why is Governor Thomas Madiford rearming them?";
			link.l1.go = "Kristofer_4";
		break;
		
		case "Kristofer_4":
            dialog.text = "Ir... Did I s-say 'rearmament'? Yes, something like that. You've eaten me up! Get off!";
            link.l1 = "Hey, man, you seem to be getting delirium tremens.";
			link.l1.go = "Kristofer_5";
		break;
		
		case "Kristofer_5":
            dialog.text = "Exactly. Hey, wait a minute. I've been assigned to one of those damn frigates. I... ick... He's already dead. I'm going to c-feed the sharks after the first battle... you know... That's it. Oops! That doesn't make me happy. P-p-it looks like I'm... hiccup... got drunk.";
            link.l1 = "Drunk? God, you're drunk as a pig. I'm sorry, I hate looking at you. Good luck to you, sailor.";
			link.l1.go = "exit";
			pchar.questTemp.BlackYosh_1 = "BlackYosh_1";
		break;
		
		case "Kristofer_6_snova":
            dialog.text = "Uffff.... Ick! Ufff... Ik! Hrr...";
            link.l1 = "So drunk he can't talk.";
			link.l1.go = "exit";
		break;


	}
}
