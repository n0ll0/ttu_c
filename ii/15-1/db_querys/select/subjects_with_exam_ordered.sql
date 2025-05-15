-- Leia kõik õppeaineid, milles on eksam. Järjesta tulemused EAPde arvu alusel vähimast suurimani.
SELECT name, eap, exam FROM subjects WHERE exam = 1 ORDER BY eap ASC;
