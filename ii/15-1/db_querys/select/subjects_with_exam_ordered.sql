-- Leia kõik eksamiga õppeained, järjestatuna EAP järgi
SELECT name_en, name_et, code, credits, assesment_type FROM subjects WHERE assesment_type = 'EXAM' ORDER BY credits ASC;
