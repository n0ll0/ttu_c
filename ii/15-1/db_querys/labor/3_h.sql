-- Leia kõik deklaratsioonid koos tudengi ja aine nimedega
SELECT *
FROM declarations d
JOIN students s ON d.student_id = s.id
JOIN subjects sub ON d.subject_id = sub.id
WHERE s.fname = 'Uko';