-- Lisa deklaratsioon (aine valimine)
INSERT INTO declarations (student_id, subject_id, grade)
SELECT s.id, sub.id, %d
FROM students s, subjects sub
WHERE s.eid = '%s' AND sub.name = '%s';
