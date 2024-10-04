#include <stdio.h>

int main(void)
{
	/* Pangakaardiga seonduvad muutujad, millest osa on algväärtustatud. Ära neid muuda! */
	float accountBalance = 100.00f;		 // Konto jääk
	const int pinCodeDebitCard = 1234; // Kaardi pin kood - sellega tuleb võrrelda!
	int pinCodeEntered;								 // Siia loetakse programmist pin kood kontrollimiseks

	/* Andmed ostu kohta, tuleb sisse lugeda klaviatuurilt. Ära neid muuda! */
	float purchaseTotal;			// Kogu ostusumma
	int loyaltyCardPresented; // Kas esitati kliendikaart? 1 - jah, 0 - ei
	int applyExtraDiscount;		// Kas saab ka lisaallahndlust? 1 - jah, 0 - ei

	/** Sisestuste lugemine
	 * Järgnevalt tuleb sul lugeda sisse 3 väärtust. Päringud oleme sinu eest ära kirjutanud.
	 * Sina pead kirjutama iga päringu järel väärtuse arvutisse lugemiseks sobilikud laused.
	 * Vihje: selleks on scanf lause.
	 * Muutujad kuhu lugeda on juba üleval deklareeritud sinu eest.
	 * NB! Kompileeri pärast igat muudatust ja veendu, et ühtegi hoiatust ei teki!
	 */

	/* Loe sisse kogu ostusumma. */
	printf("Enter purchase total: ");
	scanf("%f", &purchaseTotal);

	/* Loe sisse kas kliendikaart esitati või mitte */
	printf("Did client present loyalty card?\n1 - yes\n0 - no\n");
	scanf("%d", &loyaltyCardPresented);

	/* Loe sisse kas anda kliendile lisasoodustus? */
	printf("Apply extra discount?\n1 - yes\n0 - no\n");
	scanf("%d", &applyExtraDiscount);

	/** Allahindluse haldamine
	 * Siin tuleb sul harjutada liittingimuse moodustamist ja else if lause kasutamist.
	 * Lisaks pead tegema ka protsentarvutuse muutmaks olemasolevat arve summat.
	 *
	 * 1. Eemalda kommentaarid järgnevate koodiridade eest
	 * 2. Asenda kommentaarina antud tingimuslaused ja arvutustehted sobilike C keelsete lausetega
	 */

	if (loyaltyCardPresented && applyExtraDiscount)
	{
		/* Vähenda hinda 20% jagu */
		purchaseTotal *= 0.8f;
	}
	else if (loyaltyCardPresented)
	{
		/* Vähenda hinda 10% jagu */
		purchaseTotal *= 0.9f;
	}

	printf("Invoice total: %.2f\n", purchaseTotal);

	/** Tehingu haldamine
	 * Nüüd tuleb sul luua üksteise sisse paigutatud tingimuslauseid.
	 * Kommentaaridena on struktuur sulle juba ette antud, kirjuta oma koodilaused pärast kommentaare.
	 *
	 * - Küsi kasutajalt ja seejärel loe sisse kaardi PIN kood
	 * - Kontrolli kas PIN kood oli õige. NB! Võrdluses peavad osalema 2 muutujat, mitte muutuja ja konstant!
	 *   - Kui PIN oli õige, kontrolli kas kliendil on piisavalt vabu vahendeid
	 *     - Kui kliendil oli piisavalt vabu vahendeid, trüki tehingu kinnitus,
	 *       arvuta uus konto jääk ning kuva see
	 *     - Kui raha polnud piisavalt, trüki vastav veateade
	 *   - Kui PIN kood oli vale, trüki veateade
	 */

	printf("Enter your PIN: ");
	scanf("%d", &pinCodeEntered);

	if (pinCodeDebitCard != pinCodeEntered)
	{
		printf("Incorrect PIN\n");
		return 1;
	}

	if (accountBalance < purchaseTotal) {
		printf("You don't have enough credit!\n");
		return 1;
	}

	printf("Purchase was successful!\n");
	printf("Your balance: %.2f\n", accountBalance);

	return 0;
}
