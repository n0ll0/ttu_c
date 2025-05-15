-- Leia kõik õppeaineid, milles on eksam. Järjesta tulemused EAPde arvu alusel vähimast suurimani.
SELECT name_et, credits, assesment_type FROM subjects WHERE assesment_type = 'exam' ORDER BY credits ASC;
