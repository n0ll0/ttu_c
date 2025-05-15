-- Lisa uus õppeaine
INSERT INTO subjects (name_et, eap, exam)
SELECT '%s', %d, %d
WHERE NOT EXISTS (SELECT 1 FROM subjects WHERE name_et = '%s');
