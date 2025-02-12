/**
 * Ülesanne 2: CSV-st meiliaadresside genereerimine
Selle ülesande eesmärk on sulle tutvustada laialtlevinud andmeformaati CSV (comma separated value). Ülesande lahendamise käigus saad harjutada üksikute tähemärkide tuvastamist ja töötlemist.

Lae alla ülesande aluskood: 12_2_csv_starter.c

CSV formaat
CSV on struktuursete andmete hoiustamise formaat, kus iga andmeväli on eraldatud eelnevast ja järgnevast komaga. Tegu on tõenäoliselt kõige levinuma andmete varundamiseks ja hoiustamiseks  kasutatava formaadiga väljaspool andmebaasisüsteeme. Tema peamisteks eelisteks on lihtne struktuur ning sellest tingitult on CSV toetatud praktiliselt kõigis rakendustes, mis vähekegi andmetega töötlevad.

Kõige lihtsamal kujul nagu öeldud on kõik väljad eraldatud üksteisest komaga. Näiteks:

Mari,Maasikas,112222IACB,49001013333
Toomas,Toomingas,111111MVEB,39002204444
Täpselt sellise keerukusega andmeid vaatame ka selles tunnitöös. Nägemaks keerulisemaid formaate ja reegleid kuidas hoiustada väljasid, mis peavad sisaldama komasid, jutumärke ning kuidas lisada pealkirju võid lugeda siit: https://en.wikipedia.org/wiki/Comma-separated_values#Basic_rules.

Nõuded
Ülesande lahendus on ehitatud antud aluskoodile
Programm loob igale aluskoodis antud inimesele e-postiaadressi.
e-postiaadressi nimeosa koosneb kolmest eesnimetähest ja kolmest perenimetähest.
Nimeosale järgneb sinu valitud domeen.
E-postiaadressi nimi ja domeen peavad koosnema vaid väiketähtedest.
E-postiaadress tuleb salvestada terviklikult tekstimassiivi (loo uus muutuja seal kus vaja) ja väljastada selle kaudu. Jooksvalt tähemärkhaaval väljastus pole lubatud.
Programm väljastab:
Inimese täisnime. Eesnime ja perenime osa peavad olema eraldatud tühikuga
Genereeritud e-postiaadressi.
Aluskoodis juba olevat koodi ülesande lahendamiseks muuta ei tohi ilma juhendaja poolse nõusolekuta. Sinu poolt kirjutatava lahenduse alguspunkt peaks asuma  ProcessPerson()   funktsiooni sees. Soovi korral võid julgelt funktsioone juurde lisada.
Näide
CSV
Number of CSV lines: 3

Processing line: 'Maria,Kask'
Name: Maria Kask
E-mail: markas@ttu.ee

Processing line: 'Johanna-Maria,Kask'
Name: Johanna-Maria Kask
E-mail: johkas@ttu.ee

Processing line: 'Kalev Kristjan,Kuusk'
Name: Kalev Kristjan Kuusk
E-mail: kalkuu@ttu.ee
Vihjed
Teades koma asukohta, tead ka mis indeksilt algab perenime esimene täht
ASCII suur- ja väiketäht erinevad üksteisest ühe biti võtta, mille järgu väärtuseks on 32 (nt A 65, a 97)
Kõik toimingud peale e-mailiaadressi lõpu lisamise on kõige lihtsam teha selles ülesandes tähemärk-haaval. Saab ka kasutada string.h  teegi funktsioone, kuid need võivad olla asjatult keerukad.
Kõige tüüpilisem viga selles ülesandes on unustada sõnele null-baidi ehk terminaatori lõppu lisamist pärast nimeosa koostamist!
Lisaülesanne 1: lühikesed nimed
Muuda oma e-postiaadresside genereerimise algoritmi sedasi, et see tuleks toime ka lühemate nimede puhul.

Näiteks: Ly Kask -> lykask@ttu.ee

Lisaülesanne 2: unikaalsed e-postiaadressid
Muuda oma e-postiaadresside genereerimise algoritmi sedasi, et see genereeriks unikaalseid postiaadresse ka siis kui nimel on sarnane algus.

Muuda oma data massiiv järgnevaks:

char *data[] = {"Maria,Kask",
                "Johanna-Maria,Kask",
                "Kalev,Kristjan,Kuusk",
                "Margit,Kasemets",
                "Maris,Kase",
                "Marko,Kasvataja",
                "Margus,Kasevee"};
Nõuded

Loodavad e-postiaadressid peavad olema unikaalsed
Aadressi nimeosa peab jätkuvalt olema 6 tähemärki
Aadressid peavad jätkuvalt viitama nime omanikule nii palju kui võimalik
Täpne algoritm ja seega saavutatav nimekuju on sinu enda valida. Põhjenda valitud lahendust kaitsmisel.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 50
#define MAX_MAIL_NAME_LENGTH 6
#define MAX_EMAIL_LENGTH 100
#define MAX_CSV_LINES 100

// Function prototypes

void GenerateEmails(char *data[], int n);
void ReadCSV(char ***result, int *numLines);
int isEmailUnique(const char *email, char **existingEmails, int emailCount);
void ProcessPerson(const char entry[], char **existingEmails, int *emailCount);

int main(void)
{
    char *data1[] = {"Maria,Kask",
                    "Johanna-Maria,Kask",
                    "Kalev Kristjan,Kuusk"};

    int numOfPeople = sizeof data1 / sizeof(char *);

    GenerateEmails(data1, numOfPeople);

    char **data;
    int numLines;

    ReadCSV(&data, &numLines);
    GenerateEmails(data, numLines);

    // Free allocated memory
    for (int i = 0; i < numLines; i++)
    {
        free(data[i]);
    }
    free(data);

    return 0;
}

void GenerateEmails(char *data[], int n)
{
    int i;
    char *existingEmails[MAX_CSV_LINES];
    int emailCount = 0;

    printf("Number of CSV lines: %d\n\n", n);

    for (i = 0; i < n; i++)
    {
        ProcessPerson(data[i], existingEmails, &emailCount);
    }

    // Free allocated memory for emails
    for (i = 0; i < emailCount; i++)
    {
        free(existingEmails[i]);
    }
}
void ProcessPerson(const char entry[], char **existingEmails, int *emailCount)
{
    char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH], email[MAX_EMAIL_LENGTH];
    int i = 0, j = 0;

    // first name
    while (entry[i] != ',' && entry[i] != '\0')
    {
        firstName[j++] = entry[i++];
    }
    firstName[j] = '\0';
    i++; // Skip the comma

    // last name
    j = 0;
    while (entry[i] != '\0')
    {
        lastName[j++] = entry[i++];
    }
    lastName[j] = '\0';

    // initial email
    snprintf(email, sizeof(email), "%.3s%.3s@ttu.ee", firstName, lastName);

    for (i = 0; email[i]; i++)
    {
        email[i] = tolower(email[i]);
    }

    // Ensure email is unique
    int suffix = 1;
    while (!isEmailUnique(email, existingEmails, *emailCount))
    {
        snprintf(email, sizeof(email), "%.3s%.3s%d@ttu.ee", firstName, lastName, suffix++);
        for (i = 0; email[i]; i++)
        {
            email[i] = tolower(email[i]);
        }
    }

    // Store the unique email
    existingEmails[*emailCount] = strdup(email);
    (*emailCount)++;

    // Print results
    printf("Name: %s %s\n", firstName, lastName);
    printf("E-mail: %s\n", email);

    // free(firstName);
    // free(lastName);
    // free(email);
}

int isEmailUnique(const char *email, char **existingEmails, int emailCount)
{
    for (int i = 0; i < emailCount; i++)
    {
        if (strcmp(email, existingEmails[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}
void ReadCSV(char ***result, int *numLines)
{
    char **data = NULL;
    char line[256];
    int count = 0;

    printf("Enter CSV lines (end with an empty line):\n");

    while (fgets(line, sizeof(line), stdin))
    {

        // Break if the line is empty
        if (line[0] == '\0')
            break;
        if (line[0] == '\n')
            continue;
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';


        data = realloc(data, sizeof(char *) * (count + 1));
        if (!data)
        {
            perror("Failed to reallocate memory");
            exit(EXIT_FAILURE);
        }
        data[count] = strdup(line);
        if (!data[count])
        {
            perror("Failed to duplicate line");
            exit(EXIT_FAILURE);
        }
        count++;
    }

    *result = data;
    *numLines = count;
}