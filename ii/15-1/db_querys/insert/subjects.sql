-- Lisa uus õppeaine
INSERT INTO subjects (name_en, name_et, code, credits, assesment_type)
SELECT '%s', '%s', '%s', %d, '%s'
WHERE NOT EXISTS (SELECT 1 FROM subjects WHERE code = '%s');
