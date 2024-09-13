#include <stdio.h>

int main(void)
{
    /* Pangakaardiga seonduvad muutujad, millest osa on algväärtustatud. Ära neid muuda! */
    float accountBalance = 1000.0f; // Konto jääk
    int pinCodeDebitCard = 1234;    // Kaardi pin kood
    int pinCodeEntered;             // Siia loetakse programmist pin kood kontrollimiseks

    /* Andmed ostu kohta, tuleb sisse lugeda klaviatuurilt. Ära neid muuda! */
    float purchaseTotal;             // Kogu ostusumma
    short loyaltyCardPresented = -1; // Kas esitati kliendikaart? 1 - jah, 0 - ei
    short applyExtraDiscount = -1;   // Kas saab ka lisaallahndlust? 1 - jah, 0 - ei

    printf("Enter purchase total: ");
    /* Loe sisse kogu ostusumma. Vihje: kasuta scanf funktsiooni */
    scanf("%f", &purchaseTotal);

    while (loyaltyCardPresented != 1 && loyaltyCardPresented != 0)
    {
        printf("Did client present loyalty card?\n1 - yes\n0 - no\n");
        if (scanf("%hd", &loyaltyCardPresented) != 1 || (loyaltyCardPresented != 1 && loyaltyCardPresented != 0))
        {
            printf("Please input '1' or '0'\n");
            while (getchar() != '\n');
        }
    }
    // printf("Did client present loyalty card?\n1 - yes\n0 - no\n");
    // /* Loe sisse kas kliendikaart esitati või mitte */
    // scanf("%d", &loyaltyCardPresented);

    while (applyExtraDiscount != 1 && applyExtraDiscount != 0)
    {
        printf("Apply extra discount?\n1 - yes\n0 - no\n");
        if (scanf("%hd", &applyExtraDiscount) != 1 || (applyExtraDiscount != 1 && applyExtraDiscount != 0))
        {
            printf("Please input '1' or '0'\n");
            while (getchar() != '\n');
        }
    }
    // printf("Apply extra discount?\n1 - yes\n0 - no\n");
    // /* Loe sisse kas anda kliendile lisasoodustus? */
    // scanf("%d", &applyExtraDiscount);

    /** Allahindluse haldamine
     * Else if lause kasutamine, liittingimuse moodustamine ja
     * protsentarvutus.
     *
     * Asenda kommentaarid nõutud tingimuslausetega ja
     * pane arvutustehted sinna kus vaja uue hinna leidmiseks
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
     * Üksteise sisse paigutatud tingimuslausete moodustamine
     *
     * - Küsi kasutajalt ja seejärel loe sisse kaardi PIN kood
     * - Kontrolli kas PIN kood oli õige
     *   - Kui PIN oli õige, kontrolli kas kliendil on piisavalt vabu vahendeid
     *     - Kui kliendil oli piisavalt vabu vahendeid, trüki tehingu kinnitus,
     *       arvuta uus konto jääk ning kuva see
     *     - Kui raha polnud piisavalt, trüki vastav veateade
     *   - Kui PIN kood oli vale, trüki veateade
     */

    for (int i = 3; i > 0; --i)
    {

        printf("Please enter card PIN code: ");
        scanf("%d", &pinCodeEntered);
        if (pinCodeDebitCard == pinCodeEntered)
        {
            if (accountBalance >= purchaseTotal)
            {
                accountBalance -= purchaseTotal;
                printf("Purchase complete!\n");
                printf("New account balance is %.2f\n", accountBalance);
                printf("Thank you, come again!\n");
            }
            else
            {
                printf("Error! Not enough assets on the card!\n");
            }
            break;
        }
        else
        {
            printf("Error! Incorrect PIN code!\n");
            if (i > 1)
            {
                printf("You have %d attempts left!\n\n", i - 1);
            }
        }
    }

    return 0;
}
