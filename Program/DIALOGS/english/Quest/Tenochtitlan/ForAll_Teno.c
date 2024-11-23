
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
			dialog.text = "I don't want to talk.";
			link.l1 = "Hmm, I see...";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//встреча в бухте с перцем, который валит из Тено
		case "Shore53":
			pchar.defaultanimation = MainChAnim;
			dialog.text = GetSexPhrase("Senor", "Senorita") +", get out of here! Sail away immediately!";
			link.l1 = "What's the matter?";
			link.l1.go = "Shore53_1";
		break;
		case "Shore53_1":
			dialog.text = "Everyone died, they were devoured by the infernal flames!!!";
			link.l1 = "Who died?";
			link.l1.go = "Shore53_2";
		break;
		case "Shore53_2":
			dialog.text = "Ah, why did we go there at all?";
			link.l1 = "Buddy, calm down! Tell me slowly and in order what happened.";
			link.l1.go = "Shore53_3";
		break;
		case "Shore53_3":
			dialog.text = "Okay, "+ GetSexPhrase("senor", "senorita") +". My name is Silvio Ricci. It all started with the fact that Don Esteban hired me, along with others, to search for a new El Dorado. We landed in this bay and went to the Indian city, which Cortez himself plundered more than a hundred years ago. My God, for what?!!";
			link.l1 = "So, it's started again... Stop it immediately!!!";
			link.l1.go = "Shore53_4";
		break;
		case "Shore53_4":
			dialog.text = "Okay, "+ GetSexPhrase("senor", "senorita") +"A week ago, almost 50 people entered this jungle. And now I'm the only one out there.";
			link.l1 = "Where are the others?";
			link.l1.go = "Shore53_5";
		break;
		case "Shore53_5":
			dialog.text = "They are dead, "+ GetSexPhrase("senor", "senorita") +"! They were devoured by the flames of hell!";
			link.l1 = "What?!";
			link.l1.go = "Shore53_6";
		break;
		case "Shore53_6":
			dialog.text = "I'm telling the real truth, "+ GetSexPhrase("senor", "senorita") +". The devil himself lights this fire there!";
			link.l1 = "Did you see the devil there?";
			link.l1.go = "Shore53_7";
		break;
		case "Shore53_7":
			dialog.text = "Maybe it was the devil! There is a painted Indian standing on the shore, near the city. There are about ten of us left, those who survived the hellfire. We were about to go back when Pedro decided to take the gold trinkets off this nigger. As soon as he stretched out his arms to him, he immediately received a club on the head. And the head burst like a ripe watermelon! Then this devil started running after us and hitting everyone with his club. One blow and the head shatters into pieces. I'm the only one who ran away...";
			link.l1 = "Where is your boss, Don Esteban?";
			link.l1.go = "Shore53_8";
		break;
		case "Shore53_8":
			dialog.text = "Burned in hellfire.";
			link.l1 = "Well, yes, an inglorious end...";
			link.l1.go = "Shore53_9";
		break;
		case "Shore53_9":
			dialog.text = GetSexPhrase("Senior", "Seniorita") +", don't go there. This place is cursed!";
			link.l1 = "I'll take a chance anyway.";
			link.l1.go = "Shore53_10";
		break;
		case "Shore53_10":
			dialog.text = "Well, it's up to you, but I've had enough. Goodbye, "+ GetSexPhrase("senor", "senorita") +"!";
			link.l1 = "Goodbye...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Teno_startInShore_2");
		break;
	}
}
