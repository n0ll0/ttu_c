-- Lisa tudeng, kui teda veel pole
INSERT INTO students (eid, fname, lname, uni_id)
SELECT '%s', '%s', '%s', '%s'
WHERE NOT EXISTS (SELECT 1 FROM students WHERE eid = '%s');