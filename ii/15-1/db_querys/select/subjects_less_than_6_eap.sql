-- Leia kõik õppeained, mis on vähem kui 6 EAPd
SELECT name_en, name_et, code, credits, assesment_type FROM subjects WHERE credits < 6;
