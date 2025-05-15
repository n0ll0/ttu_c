-- Leia kõik õppeaineid mis sa oled sooritanud. Näita neid koos hinnetega, alustades kõrgeimast hindest.
-- Muuda 'SINU_EID' enda eID vastu
SELECT sub.name, d.grade
FROM students s
JOIN declarations d ON s.id = d.student_id
JOIN subjects sub ON d.subject_id = sub.id
WHERE s.eid = 'SINU_EID'
ORDER BY d.grade DESC;
