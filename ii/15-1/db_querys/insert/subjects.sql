-- Lisa uus õppeaine
INSERT INTO subjects (name, eap, exam)
SELECT '%s', %d, %d
WHERE NOT EXISTS (SELECT 1 FROM subjects WHERE name = '%s');
