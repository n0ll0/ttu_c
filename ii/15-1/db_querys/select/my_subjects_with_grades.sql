-- Leia kõik õppeained mis sa oled sooritanud. Näita neid koos hinnetega, alustades kõrgeimast hindest.
-- Muuda 'SINU_EID' enda eID vastu või kasuta snprintf C-koodis
SELECT sub.name_en, sub.code, d.grade
FROM students s
JOIN declarations d ON s.id = d.student_id
JOIN subjects sub ON d.subject_id = sub.id
WHERE s.eid = '%s'
ORDER BY d.grade DESC;
