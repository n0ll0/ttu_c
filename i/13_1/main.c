/*
Juhend
1. samm: kasutaja sisestuse lugemine
Esimese sammu teeme tunnis koos läbi! Selle käigus loome me 2 vajalikku funktsiooni oma programmi.

Alustame esimesest mida kasutame sõne lugemiseks. Lahenduses on oluline, et me suudaksime lugeda mitmetest sõnadest koosnevaid sõnesid ehk tühik ei tohiks meil lugemist ära lõpetada! Selleks on mitmeid viise, kuid meie läheneme ülesandele kasutades funktsiooni fgets() . Soovi korral võid ise teist teed minna.

Funktsiooni fgets()  eripäradeks on, et ta on mõeldud lugemaks failist. Küll aga kõik asjad on failid, sh ka klaviatuurilt tulev andmevoog, seega saame kasutada failina stdin  nimelist faili. Teine keerukus antud funktsiooni juures on see, et ta vajab endale pikkust palju tohib lugeda – see on tegelikult ohutuse tagamiseks, et puhvri pikkusest üle ei loetaks. Kolmas ja kõige probleemsem on see, et kui me vajutame klaviatuurilt enter klahvi, siis see reavahetus \n  salvestatakse samuti sinna massiivi.

Lähenemises kasutame põhimõtet, et loome funktsioonidele wrapperid ehk ümbritseme need täiendavate lausetega, mis funktsiooni kasutamise meeldivamaks või mugavamaks muudavad meie jaoks.

Meie ümbrisel on vaja kahte sisendit – sõnet ehk tähemärgimassiivi kuhu loetava teksti salvestame ning kui suur see tekstimassiiv loomise hetkel oli, et me lubatud pikkusest üle ei kirjutaks ja programmi rünnata sedasi ei lubaks.

Antud lahenduses olen jätnud kolme kohta küsimärgid sisse, kus pead ise lüngad täitma! Vihjeks: kui loetud stringi pikkus on 10 tähemärki, siis indeksiga 8 on meie jaoks viimane oluline tähemärk mille kasutaja sisestas. Sellele järgneb meile ebasoovitav reavahetus, millest peame lahti saada, asendades selle sõne lõpu sümboliga.

Vajadusel kasuta varasemalt välja toodud abifunktsiooni!

Selleks, et funktsioon ka kompileeruks olen need 2 täiendavalt vajalikku rida välja kommenteerinud. Olles küsimärgid asendanud kommenteeri need sisse.

void GetString(char str[], int max)
{
    // Read the string from keyboard
    fgets(str, max, stdin);

    // TODO: Find the length of the actual string we just read
    // size_t len = ???;

    // TODO: Write the string terminator in place of the newline to fix the string
    // str[ ??? ] = ???;
}
Kui lugemine on valmis, loome järgmise ümbrise oma vastloodud GetString()  funktsioonile. Nii saame mugavalt sisestust küsida!

void PromptString(char str[], int max, char prompt[])
{
    printf("%s: ", prompt);
    GetString(str, max);
}
Nüüd kui soovime mõnda sõnet lugeda, saame oma väljakutse luua üsna mugavalt. Näiteks kui meil on tähemärgimassiiv sentence[]  mille pikkus on defineeritud makroga MAX_STR , saame väljakutse luua

PromptString(sentence, STR_MAX, "Please enter a sentence");

2. samm: lause lugemine ja selle pikkus
Loe kasutajalt sisse lause. Seejärel leia ja väljasta sisestatud lause pikkus.

3. samm: fraasi otsimine
Lisa programmi funktsioon, milles küsitakse kasutajalt otsingufraas. Programm väljastab seepeale kas see fraas eksisteeris varasemalt sisestatud lauses või mitte.

Jah-ei vastuseks piisab kui kontrollida tagastust järgneval kujul

if (strstr() != NULL)
{

}
else
{

}

4. samm: parooli küsimine
Lisa programmi funktsioon, mis küsib kasutajalt parooli. Näiteks:

void PromptPassword(char correctPassword[])
{
    char userEnteredPassword[STR_MAX];

    // Write your loop for password prompt here
}
Parooli küsimine peab olema tsüklis ja küsima kasutajalt parooli senikaua, kuniks kasutaja sisestab korrektse parooli. Parooli kontroll peab olema tõstutundlik (st suuri ja väiketähti ei võrdsustata). Soovi korral võid panna programmi vale parooli puhul vihjeid andma või end sulgema pärast korduvalt parooli valesti sisestamist.

5. samm: lause moodustamine
Lisa programmi funktsioon, mille käigus moodustad lihtlause. Kuna funktsioonile meil head sisendit ega tagastust anda ei ole, võiksid alustada funktsiooni sedasi (void-void funktsioonid on erandlikud ja enamasti tuleb neid vältida!):

void FormulateSentence(void)
{
    // String where the final sentence will be held
    char sentence[ ??? ];

    // Strings for the two user-entered words


    // Prompt the user for the two words


    // Formulating the final sentence


    // Print the final formulated sentence
    printf("Result: %s\n", sentence);
}
Mõttekoht: kui pikk peaks olema sentence  massiivi pikkus, et see mahutaks halvimal juhul ära mõlemad kasutaja sisestatud sõnad ning sinu lisatavad sõnad, tühikud ja kirjavahemärgid, et moodustada lauset? Suurus võib olla liigkaudne aga peab olema piisav!

Edasi mõtle välja millist lauset moodustada soovid. Oluline on, et selles lauses oleks kaks lünka, kuhu kasutaja sisestab enda soovitud sõnad (ise otsustad millised – nt inimese nimi, ese, nimisõna, tegusõna, …). Üks nendest sõnadest peab olema lause esimene sõna, teise asukoht on sinu enda otsustada. Näiteks <sõna1> on <sõna2> nimi! .

Olles kasutajalt sõnad pärinud ja programmi sisse lugenud tuleb sul need sõnad lauseks kokku kleepida. Kokku kleebitav lause peab olema salvestatud täiesti uude tühja tähemärgimassiivi. Oluline on arvestada, et mis iganes kasutaja sisestab (lubatud pikkuste raames) peab ära mahtuma sinna koostatavasse massiivi ka sellisel juhul, kui kasutaja otsustas maksimaalselt pikad sõnad sisestada.

Näide
string.h
Please enter a password: password
Invalid password! Try again!

Please enter a password: again
Invalid password! Try again!

Please enter a password: hunter2
Password accepted. Welcome AzureDiamond!

Enter a sentence: I do wish we could chat longer, but I'm having an old friend for dinner.
The length of the entered sentence is 72

Please enter a search phrase: old friend
Your search phrase "old friend" exists in the originally entered sentence

Enter a name: Pauline
Enter an adjective: awesome

Result: Pauline is an awesome person!
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SENTENCE_LENGTH 100
#define WORDS_IN_SENTENCE 2

void DebugString(char str[]);
bool FindPhrase(char sentence[], char phrase[]);
void PromptPassword(char correctPassword[]);
void FormulateSentence(void);
void PromptString(char str[], int max, char prompt[]);
void StatString(char str[]);

int main(void)
{
  char sentence[MAX_SENTENCE_LENGTH];
  PromptString(sentence, MAX_SENTENCE_LENGTH, "Enter a sentence: ");
  // DebugString(sentence);
  printf("Sentence length: %ld\n", strlen(sentence));

  char prompt[MAX_SENTENCE_LENGTH];
  PromptString(prompt, MAX_SENTENCE_LENGTH, "Enter a prompt: ");
  if (FindPhrase(sentence, prompt))
  {
    puts("Prompt exists in sentence!");
  };

  char password[MAX_SENTENCE_LENGTH];
  PromptPassword("qwerty");

  FormulateSentence();

  char str[MAX_SENTENCE_LENGTH];
  PromptString(str, MAX_SENTENCE_LENGTH, "Enter a string: ");
  StatString(str);

  return 0;
}

void GetString(char str[], int max)
{
  // Read the string from keyboard
  fgets(str, max, stdin);

  size_t len = strlen(str);

  str[len - 1] = '\0';
}

void PromptString(char str[], int max, char prompt[])
{
  printf("%s: ", prompt);
  GetString(str, max);
}

void DebugString(char str[])
{
  int i = 0;
  printf("String is: '%s'\n", str);
  while (str[i] != '\0')
  {
    printf("str[%d] = %3hhu %c\n", i, str[i], str[i]);
    i++;
  }
  printf("\n");
}

bool FindPhrase(char sentence[], char phrase[])
{
  return (strstr(sentence, phrase) != NULL);
}

void PromptPassword(char correctPassword[])
{
  char userEnteredPassword[MAX_SENTENCE_LENGTH];

  // Example implementation
  PromptString(userEnteredPassword, MAX_SENTENCE_LENGTH, "Please enter a password: ");
  while (strcmp(userEnteredPassword, correctPassword) != 0)
  {
    printf("Invalid password! Try again!\n");
    PromptString(userEnteredPassword, MAX_SENTENCE_LENGTH, "Please enter a password: ");
  }
  printf("Welcome aboard n0ll!\n");
}

void FormulateSentence(void)
{
  // String where the final sentence will be held
  char sentence[2 * MAX_SENTENCE_LENGTH + 5];

  // Strings for the two user-entered words
  char words[WORDS_IN_SENTENCE][MAX_SENTENCE_LENGTH];

  // Prompt the user for the two words
  for (int i = 0; i < WORDS_IN_SENTENCE; ++i)
  {
    char prompt[21];
    sprintf(prompt, "Enter %s: ", i == 0 ? "a name" : "an adjective");
    PromptString(words[i], MAX_SENTENCE_LENGTH, prompt);
  }

  // Formulating the final sentence
  // sprintf(sentence, "%s is %s\n", words[0], words[1]);

  // Print the final formulated sentence
  // printf("Result: %s\n", sentence);
  printf("Result: ");
  printf("%s is %s\n", words[0], words[1]);
}

void StatString(char *str)
{
  size_t len = strlen(str);
  printf("%s\n", str);
  printf("Length of the string: %ld\n", len);

  int alphabetic_characters = 0;
  int digits = 0;
  int specialChars = 0;
  int spaces = 0;
  int others = 0;

  for (int i = 0; i < len; i++)
  {
    char c = str[i];
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
    {
      alphabetic_characters++;
    }
    else if (c >= '0' && c <= '9')
    {
      digits++;
    }
    else if (c == ' ' || c == '\t')
    {
      spaces++;
    }
    else if (c == '.' || c == ',' || c == '!' || c == '?' || c == ':' || c == ';' || c == '-' || c == '_')
    {
      specialChars++;
    }
    else
    {
      others++;
    }
  }
  printf("Alphabetic characters: %d\n", alphabetic_characters);
  printf("Digits: %d\n", digits);
  printf("Special characters: %d\n", specialChars);
  printf("Spaces: %d\n", spaces);
  printf("Others: %d\n", others);

  printf("Percentage of chars not alphabetic: %.1lf%%\n", 100.0 * ((double)(digits + specialChars + spaces + others) / (double)alphabetic_characters));
}