#pragma once
#include "data.h"

Data ReadData(const char* filename, enum FileType fileType);
void FreeData(Data*);
