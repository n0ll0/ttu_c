#ifndef file_type
#define file_type
enum FILE_TYPE { FILE_TYPE_TXT, FILE_TYPE_CSV, FILE_TYPE_COUNT };

#define FILE_TYPE_FORMATS_EXTENSIONS                                           \
  {[FILE_TYPE_TXT] = ".txt", [FILE_TYPE_CSV] = ".csv"};

#define FILE_TYPE_FORMATS                                                      \
  {[FILE_TYPE_TXT] = "%d %s %s %s %.1f\n",                                     \
   [FILE_TYPE_CSV] = "%d,%s,%s,%s,%.1f\n"};

#endif // file_type
