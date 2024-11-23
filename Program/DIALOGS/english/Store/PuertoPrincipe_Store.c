// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Ask, what do you want?",
                          "We have just raised this issue. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Listen, this is a store, people are buying something here. Don't distract me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, "+ GetSexPhrase("forgot", "forgot") +"something...",
                      "Yeah, really for the third time...", "Um, I won't...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.BlueBird == "toPuertoPrincipe")
			{
				link.l1 = "John, I'm here to see you about Pascal Voisier.";
				link.l1.go = "BlueBird_1";
			}
		break;
		case "BlueBird_1":
			if (isBadReputation(pchar, 10))
			{
				dialog.text = NPCStringReactionRepeat("I will not talk about Pascal with a person with a reputation like yours. I am ready to trade with you, no more.",
					"I've already told you everything.",
					"We have already talked about this topic.",
					"I have nothing to add to what has been said.", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("But I really need to talk to you, try to understand this...",
					"Hmm...",
					"Yes, that's right...",
					"I see...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("BlueBird_close", "", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = "Hmm, I don't even know what to say... And what kind of case is this?";
				link.l1 = "Well... Here, damn it, now I do not know what to say.";
				link.l1.go = "BlueBird_2";
			}
		break;

		case "BlueBird_close":
			dialog.text = "Think better about your reputation... I have nothing more to say to you.";
			link.l1 = "Heh!..";
			link.l1.go = "exit";
		break;

		case "BlueBird_2":
			dialog.text = "Start with the main thing.";
			link.l1 = "I think I'll do that. I have a suspicion that Pascal Voisier is not just a merchant. I was told that you are, like, enemies. That's why I'm here, I want to find out as much as possible about this person.";
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = "Ha! Has anyone in the Caribbean really seen the light? "+ GetSexPhrase("My friend", "Girl") +", Pascal Voisier is really not just a merchant. He's a regular scoundrel, but he knows how to do things quietly, so he gets away with everything...";
			link.l1 = "What is it? What does he get away with?";
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = "Let's start with how this bastard took the store from me. He deprived me of goods, even the local pirates didn't sell me anything, he bought everything from them!";
			link.l1 = "Wow, he has a grip like a wolf!";
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = "Like a jackal, that's the right way to say it! And just imagine - the entire Caribbean trading community considers him a decent man! But I think that all the troubles of the merchants are his doing.";
			link.l1 = "Do you think?";
			link.l1.go = "BlueBird_6";
		break;
		case "BlueBird_6":
			dialog.text = "I'm sure. But no one listens to me, everyone thinks it's a grudge against him for the lost case in Bermudes. It is, of course, not without it, but not to the same extent! Then I stopped saying anything at all - kind people hinted that I should calm down...";
			link.l1 = "Oh... You know, I'm currently looking for the Bluebird xebec. It is this ship that robs the merchant's private vessels.";
			link.l1.go = "BlueBird_7";
		break;
		case "BlueBird_7":
			dialog.text = "I think this xebec is acting at least on a tip from the bastard Pascal. And it may very well be that this is his ship at all, so consider what a cunning man is - he robs merchants, and then lends them their own money!";
			link.l1 = "Oh, there are no words... Listen, so how do I catch this xebec?";
			link.l1.go = "BlueBird_8";
		break;
		case "BlueBird_8":
			dialog.text = "I don't know... But here's what I recommend. Think about how he delivers the goods to his store. His xebec hardly docks at the port.";
			link.l1 = "It doesn't dock exactly, I found out.";
			link.l1.go = "BlueBird_9";
		break;
		case "BlueBird_9":
			dialog.text = "Well, then my reasoning is correct... You know, Bermudes has an underground passage that leads from the shipyard directly into the bay. In general, look for every single lead, "+ GetSexPhrase("buddy", "girlfriend") +". May the force come with you!";
			link.l1 = "Thank you, you helped me a lot!";
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "toSeekBermudes";
			AddQuestRecord("Xebeca_BlueBird", "4");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

