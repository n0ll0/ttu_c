#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "db_utils.h"

#define SQL_INSERT_STUDENT "db_querys/insert/student.sql"
#define SQL_INSERT_SUBJECT "db_querys/insert/subjects.sql"
#define SQL_INSERT_DECLARATION "db_querys/insert/declarations.sql"
#define SQL_SELECT_STUDENTS "db_querys/select/students.sql"
#define SQL_SELECT_SUBJECTS "db_querys/select/subjects.sql"
#define SQL_SELECT_DECLARATIONS "db_querys/select/declarations.sql"
#define SQL_SELECT_JOINED "db_querys/other/selectJOINED.sql"

int print_callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s: %s\t", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <database_path>\n", argv[0]);
        return 1;
    }
    printf("\nwe work yes\n");
    const char* db_path = argv[1];
    sqlite3* db;
    if (sqlite3_open(db_path, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    printf("\nwe work yes 2\n");

    // Example: SELECT all students
    char* sql = read_sql_from_file(SQL_SELECT_STUDENTS);
    if (sql) {
        printf("All students:\n");
        char* errMsg = 0;
        if (sqlite3_exec(db, sql, print_callback, 0, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        }
        free(sql);
    }

    // --- Ülesanne 1: Lisa iseennast andmebaasi ---
    // Muuda need väärtused enda andmetega!
    const char* my_eid = "50503290316";
    const char* my_fname = "Uko";
    const char* my_lname = "Poschlin";
    const char* my_uniid = "244508IACB";

    char* insert_student_sql = read_sql_from_file(SQL_INSERT_STUDENT);
    if (insert_student_sql) {
        char query[512];
        snprintf(query, sizeof(query), insert_student_sql, my_eid, my_fname, my_lname, my_uniid, my_eid);
        char* errMsg = 0;
        if (sqlite3_exec(db, query, 0, 0, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        }
        free(insert_student_sql);
    }

    // Lisa uus õppeaine (muuda väärtused enda ainele!)
    const char* my_subject = "Elektroonika";
    int my_eap = 6;
    const char* my_exam = "idk"; // 1 = eksam, 0 = arvestus
    char* insert_subject_sql = read_sql_from_file(SQL_INSERT_SUBJECT);
    if (insert_subject_sql) {
        char query[512];
        snprintf(query, sizeof(query), insert_subject_sql, my_subject, my_eap, my_exam, my_subject);
        char* errMsg = 0;
        if (sqlite3_exec(db, query, 0, 0, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        }
        free(insert_subject_sql);
    }

    // Lisa endale 3 deklaratsiooni (üks enda ainele, kaks olemasolevatele)
    struct { const char* subject; int grade; } decls[] = {
        { my_subject, 5 },
        { "Matemaatika", 4 }, // olemasolev aine
        { "Andmebaasid", 3 }  // olemasolev aine
    };
    for (int i = 0; i < 3; ++i) {
        char* insert_decl_sql = read_sql_from_file(SQL_INSERT_DECLARATION);
        if (insert_decl_sql) {
            char query[512];
            snprintf(query, sizeof(query), insert_decl_sql, decls[i].grade, my_eid, decls[i].subject);
            char* errMsg = 0;
            if (sqlite3_exec(db, query, 0, 0, &errMsg) != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", errMsg);
                sqlite3_free(errMsg);
            }
            free(insert_decl_sql);
        }
    }

    // --- Ülesanne 2: Andmete pärimine ---
    // 2.1 Päring 1: Leia kõik õppeained, mis on vähem kui 6 EAPd
    char* sql1 = read_sql_from_file("db_querys/select/subjects_less_than_6_eap.sql");
    if (sql1) {
        printf("\nÕppeained < 6 EAP:\n");
        char* errMsg = 0;
        sqlite3_exec(db, sql1, print_callback, 0, &errMsg);
        free(sql1);
    }
    // 2.1 Päring 2: Leia kõik eksamiga õppeained, järjestatud EAP järgi
    char* sql2 = read_sql_from_file("db_querys/select/subjects_with_exam_ordered.sql");
    if (sql2) {
        printf("\nÕppeained eksamiga (EAP järgi):\n");
        char* errMsg = 0;
        sqlite3_exec(db, sql2, print_callback, 0, &errMsg);
        free(sql2);
    }
    // 2.2 Päring 1: Leia õppuri 'Marko' kõik hinded
    char* sql3 = read_sql_from_file("db_querys/select/marko_grades.sql");
    if (sql3) {
        printf("\nMarko hinded:\n");
        char* errMsg = 0;
        sqlite3_exec(db, sql3, print_callback, 0, &errMsg);
        free(sql3);
    }
    // 2.2 Päring 2: Leia kõik õppeained, mis sa oled sooritanud (enda eID)
    char* sql4 = read_sql_from_file("db_querys/select/my_subjects_with_grades.sql");
    if (sql4) {
        char query[512];
        snprintf(query, sizeof(query), sql4, my_eid);
        printf("\nMinu õppeained ja hinded:\n");
        char* errMsg = 0;
        sqlite3_exec(db, query, print_callback, 0, &errMsg);
        free(sql4);
    }
    // 2.3: Leia iga tudengi poolt teenitud EAP ja keskmine hinne
    char* sql5 = read_sql_from_file("db_querys/select/students_eap_and_avg_grade.sql");
    if (sql5) {
        printf("\nTudengite EAP ja keskmine hinne:\n");
        char* errMsg = 0;
        sqlite3_exec(db, sql5, print_callback, 0, &errMsg);
        free(sql5);
    }

    sqlite3_close(db);
    return 0;
}
