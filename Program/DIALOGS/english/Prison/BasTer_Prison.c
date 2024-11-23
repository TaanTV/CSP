// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I'm listening.";
			link.l1 = "I "+ GetSexPhrase("wrong", "wrong") +". Goodbye.";
			link.l1.go = "Exit";
			if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "true")
            {
                link.l1 = "You have an Indian in custody who was captured by Askold. May I take a look at it?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "commandante")
            {
                link.l1 = "Tell me, are you really going to hang this Indian? Isn't the punishment too severe for such a minor offense?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "pay")
            {
                link.l1 = "It's me again, Commandant. Askold wrote a petition for the pardon of the Indian. Here it is.";
                link.l1.go = "Tichingitu_6";
            }
		break;

		case "Tichingitu":
			dialog.text = "Ah, Askold told you his story too? I see no reason to stop you. You are not the first who comes to look at this red man. Although in ten days all the residents of our city will be able to admire him when we hang him up to dry in the sun...";
			link.l1 = "So can I go to the casemates?";
			link.l1.go = "Tichingitu_1";
		break;

		case "Tichingitu_1":
			dialog.text = "I'm telling you, I see no reason to refuse you. Come on in.";
			link.l1 = "Thank you!";
			link.l1.go = "Tichingitu_2";
		break;

		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;

		case "Tichingitu_3":
			dialog.text = "You don't understand the situation in our colonies. This execution will serve as a lesson to all other red-skinned scoundrels who dare to encroach on the property of the French colonists. Besides, Askold insists on it, and he is a very respected person in our city and a close friend of the governor.";
			link.l1 = "Is there really no way to mitigate the punishment? I still think it's unjustifiably harsh...";
			link.l1.go = "Tichingitu_4";
		break;

		case "Tichingitu_4":
			dialog.text = "Oh, "+ GetSexPhrase("young man", "madam") +", don't get into philosophy! If you are so offended by this question, go to Askold and ask him for the Indian. If he writes a petition for clemency, we will grant it.";
			link.l1 = "I understand everything, officer. I'm going.";
			link.l1.go = "Tichingitu_5";
		break;

		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Tichingitu = "ascold";
			AddQuestRecord("Ascold", "3_2");
		break;

		case "Tichingitu_6":
			RemoveItems(pchar, "letter_A", 1);
			dialog.text = "(reads) Hmm... This Askold is strange: first he demands a show execution, and now he asks to release the Indian... Well, okay, apparently, all the governor's friends have similar quirks. All right, you can go to the cell and pick up this redskin.";
			link.l1 = "Thank you, officer!";
			link.l1.go = "Tichingitu_7";
		break;

		case "Tichingitu_7":
			DialogExit();
			pchar.questTemp.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
