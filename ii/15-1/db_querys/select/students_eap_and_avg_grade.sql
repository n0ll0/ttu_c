-- Leia iga tudengi poolt teenitud EAPde arv ning keskmine hinne
SELECT s.fname, s.lname, SUM(sub.eap) AS total_eap, AVG(d.grade) AS avg_grade
FROM students s
JOIN declarations d ON s.id = d.student_id
JOIN subjects sub ON d.subject_id = sub.id
GROUP BY s.id;
