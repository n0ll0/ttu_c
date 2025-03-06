/**
 * File:         emplyee_db.h
 * Author:       Risto Heinsar
 * Created:      10.02.2015
 * Modified:     25.02.2023
 *
 * Description:  Library description for employee data helper functions
 */
 
#ifndef EMPLOYEE_DB_H
#define EMPLOYEE_DB_H

#define LEN 32

typedef struct
{
    char fName[LEN];
    char lName[LEN];
    float wage;
    int yearsEmployed;
} employee;

/* Print function for employees*/
void PrintStructArray(employee *staff, int len);

/* Qsort compare functions for sorting based on one member */
int ComparFuncStructEmploymentLength(const void *x, const void *y);
int ComparFuncStructFirstName(const void *x, const void *y);

/* Qsort compare functions for sorting based on two members */
int ComparFuncStructLastFirstName(const void *x, const void *y);

#endif //EMPLOYEE_DB_H
