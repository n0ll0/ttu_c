/**
 * File:        generator.h
 * Author:      Risto Heinsar
 * Created:     12.03.2015
 * Modified     12.03.2023
 *
 * Description: Header file to provide the name pools required for the task.
 */
#ifndef GENERATOR_H
#define GENERATOR_H
#include "candidate.h"
int GetRand(int numMin, int numMax);
int ComparePersonNames(const void* a, const void* b);

void GenerateCandidates(int numCandidates, Candidate* candidates,
                        const char* firstNames[], int firstNamePoolSize,
                        const char* lastNames[], int lastNamePoolSize,
                        const char* curriculumCodes[],
                        int curriculumCodePoolSize);

#endif // GENERATOR_H
