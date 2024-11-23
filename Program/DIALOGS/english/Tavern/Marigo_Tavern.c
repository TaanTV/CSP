// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the gossip of the city "+ GetCityName(npchar.city) +" at your service. What would you like to know?",
                          "We have just raised this issue. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Why are you talking like a parrot? The same thing...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, "+ GetSexPhrase("forgot", "forgot") +"something...",
                      "Yeah, really for the third time...", "Yeah...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			//виспер
			if(CheckAttribute(pchar, "Whisper.FindDesouzaHol"))
			{
				DeleteAttribute(pchar, "Whisper.FindDesouzaHol")
				link.l1 = "Listen, did any guys of suspicious appearance come up to you here? They should also have a crucifix-shaped brand on their arm.";
				link.l1.go = "FindDesouzaHol";
				break;
			}
			//виспер
			
			// ==> Анжелика Тич: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.AT_PZD_taverna"))
			{
				DeleteAttribute(pchar, "questTemp.AT_PZD_taverna")
				link.l1 = "There are Spaniards among your guests. Do you know where they came from, or what ship they sailed on?";
				link.l1.go = "AT_PZD_taverna_1";
				break;
			}
			// <== Анжелика Тич: Портниха знатной дамы

			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
            {
                case "SeekChumakeiro_ToAaronHouse": //Голландская линейка, квест №1. поиски Чумакейро.
                    link.l1 = HeroStringReactionRepeat("Listen, you have a certain Aaron Mendes Chumaqueiro staying in Marigo. Do you know someone like that?",
                    "I'm talking about Aaron... we've already found out, I'm sorry.", "Aaron, Aa-a-aro-o-n...", "Aaron's been dealt with, I'm sorry...", npchar, Dialog.CurrentNode);
                    link.l1.go = DialogGoNodeRepeat("Step_H1_1", "", "", "", npchar, Dialog.CurrentNode);
                break;

            }
            // <== Проверяем поле состояния квестов.


 		break;
		//============ Анжелика Тич: Портниха знатной дамы
		case "AT_PZD_taverna_1":
    		dialog.text = "I'm not in the mood to chat with visitors right now. Spaniards, the Portuguese, the sea devil himself has not even looked in today.";
    		link.l1 = "So things are going well?";
    		link.l1.go = "AT_PZD_taverna_2";
 		break;
		case "AT_PZD_taverna_2":
    		dialog.text = "It's a sin to complain. Here, every evening, the governor arranges receptions at the residence in honor of the coming of age of his daughters. Then an ambassador will arrive, then someone else will bring, and everyone sails on something. There are plenty of sailors, just have time to serve the trays. You'd better go to the port authority, any captain is marked there. Ah! There's nothing to tell you.";
			link.l1 = "Yes, I think I will.";
    		link.l1.go = "exit";
 		break;
        //============ Голландская линейка, квест №1. поиски Чумакейро.
 		case "Step_H1_1":
    		dialog.text = "I know. I found him a suitable house to rent. A good man, paid well...";
    		link.l1 = "Understood... And where is this house that Aaron rented?";
    		link.l1.go = "Step_H1_2";
 		break;
 		case "Step_H1_2":
    		dialog.text = "Between the brothel and the residence of HWIC. A small brick house, slightly dilapidated from the outside. But everything is fine inside, " + npchar.name + "does not harm people.";
    		link.l1 = "Thank you, I'm going to visit this Aaron.";
    		link.l1.go = "Step_H1_3";
 		break;
 		case "Step_H1_3":
    		dialog.text = "Take a queue.";
    		link.l1 = "How to understand?";
    		link.l1.go = "Step_H1_4";
 		break;
 		case "Step_H1_4":
    		dialog.text = "That's the way to understand it - take a turn to visit Aaron. They have already asked about him and, apparently, went to meet him.";
    		link.l1 = "Who?";
    		link.l1.go = "Step_H1_5";
 		break;
 		case "Step_H1_5":
    		dialog.text = "Some stranger, I saw him for the first time in our city. Aaron has an open house today, hehe.";
    		link.l1 = "Oh, it looks like that... Oh well, thank you again. Goodbye.";
    		link.l1.go = "exit";
 		break;
		case "FindDesouzaHol":
    		dialog.text = "Not to me, but my waitress was molested by guys matching the description. You can ask her for details.";
    		link.l1 = "Okay, thanks.";
			pchar.Whisper.FindDesouzaHolWaitress = true;
    		link.l1.go = "exit";
 		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

