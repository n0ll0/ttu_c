-- Leia õppuri 'Marko' kõik hinded
SELECT s.fname, s.lname, sub.name_en, sub.code, d.grade
FROM students s
JOIN declarations d ON s.id = d.student_id
JOIN subjects sub ON d.subject_id = sub.id
WHERE s.fname = 'Marko';
