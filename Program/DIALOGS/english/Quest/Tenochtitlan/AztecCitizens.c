
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
		//------------------------ Мешитли ------------------------
		case "AztecFT":
			dialog.text = "Oh, the white man came to us again? "+ GetSexPhrase("", "Woman? ") +" I saw you go by the dam.";
			link.l1 = "Greetings to the aborigine! My name is Captain " + GetFullName(pchar) + ". What's your name?";
			link.l1.go = "AztecFT_1";
		break;
		case "AztecFT_1":
			dialog.text = "Meshitli.";
			link.l1 = "Do you live here, Meshitli? Who else is here besides you?";
			link.l1.go = "AztecFT_2";
		break;
		case "AztecFT_2":
			dialog.text = "My brother Auisotl.";
			link.l1 = "Heh, yes, I see you are quite a normal Aztec. I'm ashamed to say, but a painted and dressed-up Indian told me such a thing! There's a man standing on the shore, Montezuma's name is...";
			link.l1.go = "AztecFT_3";
		break;
		case "AztecFT_3":
			dialog.text = "Quiet! This is the one they don't talk about here! If you walk around Tenochtitlan and talk about someone whose name cannot be pronounced, then Mictlantecutli will get angry and make you his servant ahead of time!";
			link.l1 = "Mict... Miktla... Oh, I can't pronounce it! In general, isn't this your god who raises the dead?";
			link.l1.go = "AztecFT_4";
		break;
		case "AztecFT_4":
			dialog.text = "He is the one. And I advise you to treat him with respect. And best of all, sacrifice to him.";
			link.l1 = "What sacrifice?";
			link.l1.go = "AztecFT_5";
		break;
		case "AztecFT_5":
			dialog.text = "As usual, the blood of the warriors you captured. Bring them here, and then go with them to the sacrificial temple. You must cut out the heart of the war while he is still alive, and sprinkle blood on the sacrificial stone of Mictlantecutli.";
			link.l1 = "Somehow I don't really want this...";
			link.l1.go = "AztecFT_6";
		break;
		case "AztecFT_6":
			dialog.text = "Ah, well, then good luck not seeing it here. Mictlantecutli will look after you and take you in.";
			link.l1 = "Well, we'll see about that... How many soldiers are you sacrificing? I heard that you have a lot of gods...";
			link.l1.go = "AztecFT_7";
		break;
		case "AztecFT_7":
			dialog.text = "There used to be a lot, but now we only serve Miktlantekutli. My brother and I do not capture warriors and do not sacrifice, because Mictlantecutli promised us his protection and life after death. So we work in the city in small ways, we don't even keep weapons.";
			link.l1 = "Did you actually talk to Miktlantekutli as a person? Heh, as you were savages, you still are. That the dandy on the shore, whose name is not pronounced, that you and your brother are here. That's how I believed in your Mictlantecutli. You'd better tell me what's interesting about your Tenochtitlan.";
			link.l1.go = "AztecFT_8";
		break;
		case "AztecFT_8":
			dialog.text = "Nothing special. The Temple of the Great Life Force is the largest structure. In the pyramids on both sides of it are the temples of 10 gods. The Temple of the White Gods is a pyramid with a round tower, right in front of the Temple of the Great Life Force. The bathing area...";
			link.l1 = "Listen, how would I get into this Great Temple?";
			link.l1.go = "AztecFT_9";
		break;
		case "AztecFT_9":
			dialog.text = "You shouldn't do that. My brother and I will not interfere, but Mictlantecutli can easily send his warriors after you. Not to mention that the temples are guarded by his servants, the great warriors of the past.";
			link.l1 = "Understood... Well, be healthy, Meshitli. I'll talk to your brother again on occasion.";
			link.l1.go = "AztecFT_10";
		break;
		case "AztecFT_10":
			dialog.text = "He will be very happy. There is no one left alive in Tenochtitlan except us, so we are interested in the aliens."+ GetSexPhrase("", " Especially so beautiful.") +"";
			link.l1 = ""+ GetSexPhrase("Hmm, I see.", "Wow, you can also say compliments!") +"";
			link.l1.go = "AztecFT_11";
		break;
		case "AztecFT_11":
			LAi_SetImmortal(sld, false);
			LAi_SetCitizenType(npchar);
			NextDiag.TempNode = "Aztec1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Aztec1":
			dialog.text = "Greetings, "+ GetSexPhrase("captain", "beautiful squaw") +" " + GetFullName(pchar) + ".";
			link.l1 = "Hello to you too, Meshitli";
			link.l1.go = "exit";
		break;

		case "Aztec1AF":
			dialog.text = ""+ GetSexPhrase("The White Captain walked", "The beautiful squaw walked") +"to the Temple of the Great Life Force and survived? I am very surprised...";
			link.l1 = "Didn't you think you'd see me alive?";
			link.l1.go = "Aztec1AF_1";
		break;
		case "Aztec1AF_1":
			dialog.text = "No. My brother and I had a bet about when Mictlantecutli would take you. No one won - you're alive.";
			link.l1 = "I talked with your Mictlantecutli. Very informative.";
			link.l1.go = "Aztec1AF_2";
		break;
		case "Aztec1AF_2":
			dialog.text = "You're lucky, "+ GetSexPhrase("white captain", "beautiful squaw") +". Mictlantecutli himself talked to you and let you go!";
			link.l1 = "He also gave me a jade skull.";
			link.l1.go = "Aztec1AF_3";
		break;
		case "Aztec1AF_3":
			dialog.text = "This skull has power over the dead, know this! You are very lucky, "+ GetSexPhrase("white captain", "beautiful squaw") +".";
			link.l1 = "I know. Well, come on, Meshitli.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Aztec1";
		break;


		//------------------------ Ауисотль ------------------------
		case "AztecFT2":
			dialog.text = "Oh, the white man in Tenochtitlan! "+ GetSexPhrase("", "And such a beautiful squaw! ") +"Very interesting...";
			link.l1 = "Hello, Aztec. As far as I understand, your name is Auisotl.";
			link.l1.go = "AztecFT2_1";
		break;

		case "AztecFT2_1":
			dialog.text = "Yes, it is. And who are you?";
			link.l1 = "I am captain " + GetFullName(pchar) + ". Glad to meet, so to speak, with a local resident. We've already talked to your brother, Meshitli.";
			link.l1.go = "AztecFT2_2";
		break;
		case "AztecFT2_2":
			dialog.text = "That's good. Tell me, "+ GetSexPhrase("white captain", "beautiful squaw") +", what do you need in our city?";
			link.l1 = "Looking for something. Listen, can you tell me how to get into the Temple of the Great Life Force? And I also need to go to the Temple of the White Gods...";
			link.l1.go = "AztecFT2_3";
		break;
		case "AztecFT2_3":
			dialog.text = "Are you out of your mind, "+ GetSexPhrase("white captain", "beautiful squaw") +"? Mictlantecutli will devour your body and soul!";
			link.l1 = "I'm not afraid. If you know something, tell me.";
			link.l1.go = "AztecFT2_4";
		break;
		case "AztecFT2_4":
			dialog.text = "You "+ GetSexPhrase("stupid man, white captain", "very beautiful, white squaw, but also very stupid") +". You need to go and argue with your brother about how long you'll live...";
			link.l1 = "Is that all you can say?";
			link.l1.go = "AztecFT2_5";
		break;
		case "AztecFT2_5":
			dialog.text = "My brother and I are servants of the great Miktlantekutli, what did you want to hear from us? I like you"+ GetSexPhrase(", white captain, though you're' stupid", ", white squaw, though you're stupid") +". And I will tell you that the Temple of the Great Life Force can be accessed not only through the entrance at the top of the pyramid...";
			link.l1 = "Well, thanks for that, Auisotl.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Aztec2";
		break;

		case "Aztec2":
			dialog.text = "Are you still "+ GetSexPhrase("live, white captain", "live, beautiful squaw") +"?";
			link.l1 = "As you can see, Auisotl.";
			link.l1.go = "exit";
		break;

		case "Aztec2AF":
			dialog.text = ""+ GetSexPhrase("White Captain, you walked", "Beautiful squaw, you walked") +"to Mictlantecutli?";
			link.l1 = "Walked.";
			link.l1.go = "Aztec2AF_1";
		break;
		case "Aztec2AF_1":
			dialog.text = "And he didn't take you as his servant?";
			link.l1 = "No. As you can see, I'm still alive, Auisotl.";
			link.l1.go = "Aztec2AF_2";
		break;
		case "Aztec2AF_2":
			dialog.text = "Oh, you're a great man if Mictlantecutli himself let you go!";
			link.l1 = "Let go, and even gave away the jade skull!";
			link.l1.go = "Aztec2AF_3";
		break;
		case "Aztec2AF_3":
			dialog.text = "Resurrection skull?! I can't believe Powisotl wishes you luck. Goodbye, "+ GetSexPhrase("white captain", "beautiful squaw") +".";
			link.l1 = "Goodbye, Auisotl.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Aztec2AF_4";
		break;

		case "Aztec2AF_4":
			dialog.text = "My brother and I will "+ GetSexPhrase("remember you, white captain", "miss you, beautiful squaw") +".";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
		break;
	}
}
