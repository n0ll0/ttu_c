#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>

// Helper to print error and exit
void die(const char* msg, int rc, sqlite3* db) {
  fprintf(stderr, "%s: %s\n", msg, sqlite3_errmsg(db));
  if (db)
    sqlite3_close(db);
  exit(rc);
}

void print_subjects_less_than_6_eap(sqlite3* db) {
  printf("All subjects with less than 6 EAP:\n");
  const char* sql = "SELECT name, eap, exam FROM subjects WHERE eap < 6;";
  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK)
    die("Failed to prepare statement", 1, db);
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    printf("Name: %s, EAP: %d, Exam: %s\n", sqlite3_column_text(stmt, 0),
           sqlite3_column_int(stmt, 1),
           sqlite3_column_int(stmt, 2) ? "Yes" : "No");
  }
  sqlite3_finalize(stmt);
  printf("\n");
}

void print_subjects_with_exam_ordered(sqlite3* db) {
  printf("Subjects with exam, ordered by EAP ascending:\n");
  const char* sql =
      "SELECT name, eap FROM subjects WHERE exam = 1 ORDER BY eap ASC;";
  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK)
    die("Failed to prepare statement", 1, db);
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    printf("Name: %s, EAP: %d\n", sqlite3_column_text(stmt, 0),
           sqlite3_column_int(stmt, 1));
  }
  sqlite3_finalize(stmt);
  printf("\n");
}

void print_marko_grades(sqlite3* db) {
  printf("All grades for student 'Marko':\n");
  const char* sql = "SELECT s.name, d.grade "
                    "FROM students st "
                    "JOIN declarations d ON st.id = d.student_id "
                    "JOIN subjects s ON d.subject_id = s.id "
                    "WHERE st.name = 'Marko';";
  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK)
    die("Failed to prepare statement", 1, db);
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    printf("Subject: %s, Grade: %d\n", sqlite3_column_text(stmt, 0),
           sqlite3_column_int(stmt, 1));
  }
  sqlite3_finalize(stmt);
  printf("\n");
}

void print_my_subjects_and_grades(sqlite3* db, const char* my_name) {
  printf(
      "All subjects you have passed, with grades (ordered by grade desc):\n");
  const char* sql = "SELECT s.name, d.grade "
                    "FROM students st "
                    "JOIN declarations d ON st.id = d.student_id "
                    "JOIN subjects s ON d.subject_id = s.id "
                    "WHERE st.name = ? "
                    "ORDER BY d.grade DESC;";
  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK)
    die("Failed to prepare statement", 1, db);
  sqlite3_bind_text(stmt, 1, my_name, -1, SQLITE_STATIC);
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    printf("Subject: %s, Grade: %d\n", sqlite3_column_text(stmt, 0),
           sqlite3_column_int(stmt, 1));
  }
  sqlite3_finalize(stmt);
  printf("\n");
}

void print_eap_and_avg_grade_per_student(sqlite3* db) {
  printf("EAP sum and average grade per student:\n");
  const char* sql = "SELECT st.name, SUM(s.eap), AVG(d.grade) "
                    "FROM students st "
                    "JOIN declarations d ON st.id = d.student_id "
                    "JOIN subjects s ON d.subject_id = s.id "
                    "GROUP BY st.id;";
  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK)
    die("Failed to prepare statement", 1, db);
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    printf("Student: %s, Total EAP: %d, Avg Grade: %.2f\n",
           sqlite3_column_text(stmt, 0), sqlite3_column_int(stmt, 1),
           sqlite3_column_double(stmt, 2));
  }
  sqlite3_finalize(stmt);
  printf("\n");
}

int main() {
  sqlite3* db;
  if (sqlite3_open("study_information.db", &db) != SQLITE_OK)
    die("Can't open database", 1, db);

  print_subjects_less_than_6_eap(db);
  print_subjects_with_exam_ordered(db);
  print_marko_grades(db);
  print_my_subjects_and_grades(
      db, "SINU_NIMI"); // Replace with your name as in the DB
  print_eap_and_avg_grade_per_student(db);

  sqlite3_close(db);
  return 0;
}
