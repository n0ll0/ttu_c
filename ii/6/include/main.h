#pragma once
#include "../include/data_read.h"
#include "../include/log.h"
/*
PR2ET6: Makefile ja logimine
Labori materjal
Laboriülesanded
Ülesande osa 1 / 2 [W06-1]: Andmete lugemine, töötlemine
Nõuded
Vihje
Testimine
Ülesande osa 2 / 2 [W06-2]: Logimine
Nõuded
Vihjeid
Lisaülesanne 1 [W06-3]: Logimise teek
Nõuded
Lisaülesanne 2 [W06-4]: Lihtsustatud CSV failist lugemine
Nõuded
Lahenduskäik
Pärast seda tundi peaksid
Täiendav materjal
Labori materjal
Slaidid: Silumine
Slaidid: Makefile ja logimine
Täiendav näide: Korduvkasutatava koodi (teegi) loomine
Lisalugemist: Fun with valgrind (inglise keeles)
Testfailid valgrindi proovimiseks:
https://blue.pri.ee/ttu/files/iax0584/demokood/valgrind.zip Laboriülesanded
Selles laboris on üks ülesanne, mis on jagatud kahte ossa. Ülesannet laiendab
kaks lisaülesannet.

NB! Kuigi arendada saad oma lahendused ükskõik mis platvormil, siis üks osa
tõestusest vajab Valgrind tööriista kasutamist. Valgrind töötab kontrollitult
vaid Linuxil (rakendus olemas ka MacOSil) – vajadusel saad rakenduse tõestuseks
üles laadida kooliarvutisse.

Lae alla andmefailid:
https://blue.pri.ee/ttu/files/iax0584/andmefailid/6_make_data.zip

Arhiiv sisaldab andmefaile nii baasülesandeks kui lisaülesandeks!

Ülesande osa 1 / 2 [W06-1]: Andmete lugemine, töötlemine
Esimeses osas on meie eesmärgiks saada programmi andmed sisse ning
demonstreerida oma oskusi Makefile’i koostamiseks ja kasutamiseks ning mälus
vigade puudumiseks.

Nõuded
Loe andmed sisendfailist
Andmefaili struktuur
<õppeaine nimi> <hinnete arv> <hinded>
Loetud andmed salvesta struktuurimassiivi. Hinnete jaoks võid teha mõistliku
pikkusega massiivi – näiteks max 20 hinnet aine kohta (lähtuvalt näitefaili
struktuurist). Kuva ekraanil Õppeaine nimi Õppeaines antud hinded Õppeaine
keskmine hinne Hoia andmete lugemine, keskmise leidmine ja väljastus eraldi
funktsioonides! Kood peab olema tükeldatud vähemalt kahte koodifaili, millest
mõlemal on oma päisefail. Tükeldus peab olema mõistlik, kuid on jäetud sinu
otsustada. Kood kompileeri programmiks kasutades Makefile’i Makefile’is peab
olema minimaalselt kirjeldatud retsept all , muutuja CFLAGS  ja lipud -Wall
-Wextra -Wconversion -g Ülejäänud Makefile’i keerukuse ja ülesehituse võid ise
otsustada Kaitsmisel Näita projekti kompileerimist kasutades Makefile’i Näita
programmi väljundit läbi Valgrindi tõestamaks, et puuduvad mäluvead. Vihje
Hinnete arv aine kohta varieerub – st iga failis olev andmerida võib olla
erineva pikkusega. Seetõttu andmefaili võimalik lugeda ühe ühte fscanf()
funktsiooni väljakutsega!

Lugemine on vaja teha pesastatud tsüklitega, kus

Välimine tsükkel loeb õppeaine nime ning hinnete arvu
Vastavalt välimisest tsüklist saadud hinnete arvule määratakse ära sisemise
tsükli korduste arv, lugemaks sisse õppeaines antud hinded. Ära unusta sisemise
tsükli fscanf()  funktsiooni tagastust kontrollida! Testimine Näide võimalikust
koodi struktuurist.

NB! Failide nimed ei ole ette määratud, tegu on lihtsalt näidisega. Samuti
piisab vaid ühest andmefailist ning see ei pea olema eraldi kaustas.

.
├── data
│   ├── data_grades.csv
│   └── data_grades.txt
├── analyzer.c
├── analyzer.h
├── Makefile
├── subjects_processor.c
├── subjects_processor.h
NB! Järgnevas näites ei ole kajastatud valgrindi väljundit! Ära unusta testida
oma programmi korrektsust valgrindiga!

Subject: Programming
Grades:  4 5 5 4 2 5 1 4 2 5
Average: 3.70

Subject: Databases
Grades:  5 3 3 4 4 3
Average: 3.67

Subject: Mechatronics
Grades:  3 3 4 4 5 0
Average: 3.17

Subject: Physics
Grades:  5 5 3 3 2 3 4 5 1 1 2 4
Average: 3.17

Subject: Ethics
Grades:  5 5 5 4 5 3
Average: 4.50

Subject: Scientology
Grades:  N/A
Average: N/A

Subject: Chemistry
Grades:  4 4 3 4 5 4 5
Average: 4.14

Ülesande osa 2 / 2 [W06-2]: Logimine
Selle osa raames tuleb sul lisada oma programmi logimine.

Nõuded
Lisa oma programmi logimine
Üks logi rea kohta. Logi ei tohi olla kaherealine!
Iga logi rida algab ajatempliga. Ajatempel peab sisaldama kuupäeva (päev, kuu,
aasta) ja kellaaega (tunnid, minutid, sekundid) Programmi järgmine käivitus ei
tohi kustutada eelneva käivituse logi Logitavad sündmused Programmi käivitamine
ja sulgemine Sisendfaili avamise seisund (edukas / ebaõnnestunud) Faili lugemine
lõpetatud. Logis kuva loetud ridade arv! Faili lugemine katkestatud kuna
massiivi maksimaalne piir on ületatud (maksimaalne piir kuvatakse logis).  NB!
Sul on struktuuride massiiv ja struktuuri liikmena hinnete massiiv! Viga aine
keskmise hinde arvutamisel. Logi terviklikkus peab olema garanteeritud ka
programmi kokkujooksu korral Võimalus 1: Väljundpuhvrist on võimalik sunniga
andmed faili kirjutada kasutades funktsiooni fflush() Võimalus 2: Sulge logifail
pärast kirjutamist – faili sulgemise järel kirjutatakse puhvris olevad andmed
faili. Logifaili avamise ebaõnnestumisel peab programm jätkama tööd, mitte
väljuma! Teavita kasutajat logimise ebaõnnestumisest. Vihjeid Valmista ette
logitav sõne enne logimise funktsiooni väljakutsumist! Ära koorma logimise
funktsiooni üle parameetritega. Sõne ettevalmistamiseks on hea funktsioon
snprintf() Logifunktsiooni lihtsustamiseks on soovitatav mitte failiviita ega
nime sellele kaasa anda. Võimalike lahendusi: Ava ja sulge fail logifunktsioonis
järjest See on üks võimalikest eranditest globaalmuutujale – soovi korral võid
teha failiviida logifailile globaalmuutujana. (See ei ole hea lahendus, kuid
aktsepteeritav – parem võimalus on kirjutatud lahti lisaülesandena). Näiteks
võiks logimise väljakutsumine välja näha nii: Logger("Program started");
Lisaülesanne 1 [W06-3]: Logimise teek
Selle ülesande raames lood sa endale logimise teegi. Vihje: seda saad ära
kasutada kodutöö 2 juures!

Nõuded
Lisa programmile eraldi .c ja .h fail ja tõsta sinna logimine
Lisa 4 logimise taset – OFF, ERROR, WARNING ja INFO – need on loendi tüüpi
(enum). Iga logifaili rea juures on kirjeldatud selle logi tase. Logi
kirjutatakse faili vaid siis, kui määratud tase seda lubab. Näiteks: INFO taseme
korral kirjutatakse kõigi tasemete logid; WARNING taseme korral kirjutatakse
ainult WARNING ja ERROR tasemega logid; ERROR taseme korral kirjutatakse ainult
ERROR tasemega logid; OFF korral logisid ei kirjutata; Iga kutse logi
kirjutamiseks peab nüüd sisaldama selle logi olulisuse taset (ERROR, WARNING või
INFO) Näiteks: Logger(LOG_INFO, "Program started"); Teek peab toetama logi
väljundfaili nime andmist Näiteks: LoggerSetOutputName("log.txt"); Teek peab
toetama programmi logitaseme sättimist Näiteks: LoggerSetLoggingLevel(LOG_INFO);
Logimise seadistused tuleb hoida logimise teegi sisemiselt. Selleks on logifaili
nimi ja logi tase (võid ka lisada täiendavaid). Need hoiusta logi koodifailis
globaalmuutujatena. Logifaili seadistustel peavad olema vaikeväärtused – näiteks
kui kasutaja unustab või ei soovi neid seadistada, siis programm ei läheks
katki. Iga logi peab sisaldama kellaaega nii nagu oli kirjeldatud ülesande
teises osas. Lisaülesanne 2 [W06-4]: Lihtsustatud CSV failist lugemine Käesoleva
lisaülesande eesmärgiks on toetada mitmest sõnast koosnevaid õppeainete nimesid.
Selleks on vaja toetada välja sees paikevat tühikut.

Nõuded
Kasuta sisendfailina CSV versiooni sisendfailist
Andmeväljad on üksteisest eraldatud komaga. Andmeväljad ise komasid ei sisalda.
Lahenduskäik
NB! Kasutame lihtsustatud metoodikat CSV lugemiseks. Sellega ei ole võimalik
lugeda ükskõik missugust CSV faili! St kui andmeväli võib sisaldada ka komasid,
siis seda metoodikat kasutada ei saa!

Kui vajad täielikku CSV tuge, kasuta kas vastavat teeki (nt libcsv) või kirjuta
näiteks olekumasina-põhine töötlemine (loed tähemärk-haaval ja otsustad mida
teha lähtuvalt loetud tähemärgist ja hetkeolekust olekumasinas)

scanf() funktsioonide perekond võimaldab lisaks andmeformaadi kirjeldamisele ka
kirjeldada oodatavat sisendit ning lihtsamaid regulaaravaldisi.

Näiteks lugemaks kasutajalt kellaaega, saame kasutada formaati scanf("%d:%d",
&hours, &minutes);  – sellisel juhul saab kasutaja sisestada kellaaja formaadiga
14:35 . Muutuja hours  saab väärtuseks 14 ja minutes  väärtuseks 35 . Kui aga
kasutaja sisestab 14 35 , siis hours  saab ikka väärtuseks 14 , kuid kuna tühik
polnud oodatud formaat, siis sealt edasi ei loeta ning minutes  jääb
väärtustamata.

Lähtuvalt sellest teadmisest saame koostada faili lugemiseks formaadi fscanf(fp,
"%[^,],%d", ...)  . Asenda failiviida nimi enda kasutatud viidaga ning kolme
punkti asemele pane oma muutujad kuhu andmeid salvestad.

Esimene väli loetakse tekstina kuniks komani (koma ei loeta). See salvestatakse
tekstimassiivi (õppeaine nimi) Seejärel loetakse puhvrist välja koma (ja
visatakse ära) Siis loetakse sisse üks täisarv (hinnete arv aines) Sedasi saad
loetud esimesed 2 välja. Edasi pead juba formaadi koostama hinnete lugemiseks
(ära komasid unusta!).

Pärast seda tundi peaksid
Teadma erinevate ehitussüsteemide kohta
Oskama koostada lihtsat Makefile’i
Teadma kuidas deklareerida muutujaid ja neid kasutada
Teadma kuidas koostada retsepti, sh mitut retsepti ühes failis
Teadma mis retsepti sees käib
Teadma varjatud reeglitest ja oskama neid vajadusel kasutada
Oskama kasutada Makefile’i programmi kompileerimiseks
Oskama kasutada valgrindi programmist vigade leidmiseks ja korrektsuse
kontrollimiseks Oskama programmi siseselt hetke kellaaega leida ning seda
kujundada Teadma logimise põhitõdesid ja olulisust Täiendav materjal Make manual
https://www.gnu.org/software/make/manual/make.html
What is a Makefile and how does it work?
https://opensource.com/article/18/8/what-how-makefile
Compiling Programs with Make
https://web.stanford.edu/class/archive/cs/cs107/cs107.1194/resources/make
Makefile tutor project (näidisprojektid koos Makefile’iga)
https://github.com/clemedon/Makefile_tutor
Makefile tutorial
https://makefiletutorial.com
VMWare VSphere Logging options (levels)
https://docs.vmware.com/en/VMware-vSphere/8.0/vsphere-vcenter-configuration/GUID-0439D577-66F7-4584-AF05-5EB41A761873.html
Logimise teegi näidis (keerukam kui meil vaja)
https://github.com/rxi/log.c
strftime() funktsioon
https://www.cplusplus.com/reference/ctime/strftime/
Valgrind dokumentatsioon
https://valgrind.org/docs/manual/index.html
Teegi tegemise juhend
http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html
Address Sanitizer dokumentatsioon
https://github.com/google/sanitizers/wiki/AddressSanitizer
*/