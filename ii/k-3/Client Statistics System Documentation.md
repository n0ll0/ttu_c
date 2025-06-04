# Client Statistics System Documentation

---

## Tiitelleht (Cover Page)

**Projekt:** Client Statistics System  
**Autor:** [Your Name]  
**Kuupäev:** 2025-06-04

---

## Autorideklaratsioon (Author Declaration)

Mina, [Your Name], kinnitan, et käesolev dokumentatsioon ja kood on minu iseseisev töö ning kõiki allikaid on nõuetekohaselt viidatud.  
Kui olen kasutanud tehisintellekti abi (näiteks VSCode CoPilot) või mõnda teist tööriista, siis olen seda dokumenteerinud.

---

## Lühendite ja Mõistete Sõnastik

- **PK** – Primaarvõti
- **FK** – Välisvõti
- **SQL** – Structured Query Language
- **CRUD** – Create, Read, Update, Delete

---

## Sisukord (Table of Contents)

1. [Ülesande püstitus](#ülesande-püstitus)
2. [Rakenduse kirjeldus](#rakenduse-kirjeldus)
3. [Andmebaasi Disain](#andmebaasi-disain)
   - 3.1. Tabelite kirjeldus
   - 3.2. PK ja FK seosed
4. [SQL päringud](#sql-päringud)
5. [Kokkuvõte](#kokkuvõte)
6. [Kasulikud viited](#kasulikud-viited)

---

## Ülesande püstitus

**Kursuse nimetus:** IAX0584 Programming II  
**Teema:** SQL, C, sqlite3

**Püstitus:**  
Arendada süsteem, mis analüüsib ja kuvab kliendi ostukäitumist kasutades SQLite andmebaasi ja C programmeerimiskeelt.  
Süsteem peab:

- Lubama välisvõtete kehtestamist (`PRAGMA foreign_keys = ON`).
- Kontrollima ja vajadusel looma PURCHASES tabeli.
- Tooma välja erinevaid statistilisi päringuid, sh:
  1. PURCHASES kirje lisamine, muutmine ja kustutamine.
  2. Kuvama kõiki PURCHASES kirjeid kliendi kaupa grupeeritult.
  3. Kuvama kliendi keskmist kulutust kaupluste lõikes.
  4. Kuvama ülemaailmseid ja kaupluspõhiseid top 10 kliente.

---

## Rakenduse kirjeldus

Rakendus on menüüd põhine kliendi statistika süsteem, mis kasutab SQLite andmebaasi. Kasutaja saab käivitada järgmisi funktsioone:

- **Purchase Operations:** Lisada, muuta ja kustutada PURCHASES tabeli kirjeid.
- **Statistical Reports:** Kuvada erinevaid statistilisi aruandeid (nt kliendi keskmised kulutused ja top10 kliendid).

Programmi peamised moodulid ja failid:

- **src/main.c:** Rakenduse sisenemispunkt, mis tegeleb andmebaasi avamise ja menüü väljakutsetega.
- **src/setup_db.c:** Funktsioonid välisvõtete lubamiseks ja PURCHASES tabeli loomise kontrollimiseks.
- **src/stats_ops.c:** SQL päringud, mis genereerivad statistilisi aruandeid.
- **src/purchase_ops.c:** Funktsioonid, mis haldavad PURCHASES tabeli CRUD operatsioone.
- **src/cmenu.c:** Menüü kuvamine ja kasutaja sisendi töötlemine.

---

## Andmebaasi Disain

### 3.1 Tabelite kirjeldus

#### CLIENTS

- **id**: INTEGER, Primaarvõti  
- **first_name**: TEXT, Not NULL  
- **last_name**: TEXT, Not NULL  

#### PRODUCTS

- **id**: INTEGER, Primaarvõti  
- **shop_id**: INTEGER, FK viidates SHOPS (NOT NULL)  
- **price**: REAL, Not NULL  
- **name**: TEXT, Not NULL  

#### SHOPS

- **id**: INTEGER, Primaarvõti  
- **name**: TEXT, Not NULL, Unique  

#### PURCHASES

- **id**: INTEGER, Primaarvõti  
- **client_id**: INTEGER, FK viidates CLIENTS (NOT NULL)  
- **product_id**: INTEGER, FK viidates PRODUCTS (NOT NULL)  
- **amount**: INTEGER, Not NULL  

### 3.2 PK ja FK seosed

- **PURCHASES.client_id** on välisvõti, mis viitab **CLIENTS.id**.
- **PURCHASES.product_id** on välisvõti, mis viitab **PRODUCTS.id**.
- **PRODUCTS.shop_id** on välisvõti, mis viitab **SHOPS.id**.

---

## SQL päringud

Kõik SQL päringud on rakenduse koodis kasutatud valmistatud deklaratsioonidena (prepared statements) ning need on grupeeritud päringu tüübi järgi:

### SELECT päringud

1. **Kuvab kõik ostud grupeeritult kliendi järgi**  

   ```sql
   SELECT clients.first_name || ' ' || clients.last_name AS client_name, 
          purchases.id, products.shop_id, purchases.amount
   FROM purchases
   JOIN clients ON purchases.client_id = clients.id
   JOIN products ON purchases.product_id = products.id
   ORDER BY client_name;
   ```

2. **Kuvab keskmise kulutuse kliendi lõikes**  

   ```sql
   SELECT clients.first_name || ' ' || clients.last_name AS client_name, 
          AVG(purchases.amount)
   FROM purchases
   JOIN clients ON purchases.client_id = clients.id
   GROUP BY clients.id
   ORDER BY client_name;
   ```

3. **Kuvab keskmise kulutuse kliendi lõikes kaupluse kaupa**  

   ```sql
   SELECT clients.first_name || ' ' || clients.last_name AS client_name, 
          shops.name, 
          AVG(purchases.amount)
   FROM purchases
   JOIN clients ON purchases.client_id = clients.id
   JOIN products ON purchases.product_id = products.id
   JOIN shops ON products.shop_id = shops.id
   GROUP BY clients.id, shops.id
   ORDER BY client_name, shops.name;
   ```

4. **Kuvab ülemaailmsed Top 10 kliendid (summaarne kulutuse järgi)**  

   ```sql
   SELECT clients.first_name || ' ' || clients.last_name AS client_name, 
          SUM(purchases.amount) as total
   FROM purchases
   JOIN clients ON purchases.client_id = clients.id
   GROUP BY clients.id
   ORDER BY total DESC
   LIMIT 10;
   ```

5. **Kuvab kaupluspõhised Top 10 kliendid**  

   ```sql
   SELECT shops.name, 
          clients.first_name || ' ' || clients.last_name AS client_name, 
          SUM(purchases.amount) as total
   FROM purchases
   JOIN clients ON purchases.client_id = clients.id
   JOIN products ON purchases.product_id = products.id
   JOIN shops ON products.shop_id = shops.id
   GROUP BY shops.id, clients.id
   ORDER BY shops.name, total DESC;
   ```

### INSERT, UPDATE ja DELETE päringud

6. **INSERT – lisab ostu**  

   ```sql
   INSERT INTO PURCHASES (client_id, product_id, amount)
   VALUES (?, ?, ?);
   ```

7. **UPDATE – muudab ostu andmeid**  

   ```sql
   UPDATE PURCHASES 
   SET amount = ?
   WHERE id = ?;
   ```

8. **DELETE – kustutab ostu**  

   ```sql
   DELETE FROM PURCHASES
   WHERE id = ?;
   ```

---

## Kokkuvõte

Selle dokumendideldud süsteemi eesmärgiks on pakkuda tööriista kliendi ostueelarvamiste analüüsimiseks ja aruannete koostamiseks. Projekti käigus rakendati SQL päringud valmistatud lausete (prepared statements) kaudu, mis tagab parem turvalisuse ja vigade kontrolli.  
Isiklikult leian, et projekti struktuur on selge ja süsteem on laiendatav. Tulevikus võiks lisada täiendavaid valideerimisi ja kasutajaliidese täiustusi.

---

## Kasulikud viited

- [SQLite Dokumentatsioon](https://sqlite.org/docs.html)
- IEEE viitamisjuhised:  
  - [TalTechi juhend IEEE stiilis viitamiseks](https://haldus.taltech.ee/sites/default/files/2024-05/IEEE_stiilis_viitamine_2024%20%281%29.pdf)  
  - [Ametlik IEEE Referentside juhend](https://journals.ieeeauthorcenter.ieee.org/wp-content/uploads/sites/7/IEEE_Reference_Guide.pdf)

---

*Lisatud: Kui kasutasin tehisintellekti abi näiteks koodi värvimiseks ja dokumendi koostamiseks (nt VSCode CoPilot), siis olen seda alljärgnevalt märkinud.*

---

Märkus: Kõik eeltingimused (nt negatiivsete andmete valideerimine, unikaalsuse kontroll, välisvõtete kontroll jne) on rakendatud vastavalt ülesande püstitusele.
