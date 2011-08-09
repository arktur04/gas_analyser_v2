#ifndef BMPS_h
#define BMPS_h

#define BMP_HN         0
#define BMP_O2         1
#define BMP_SMALL_TP   2
#define BMP_SMALL_CHE  3
#define BMP_SMALL_NE   4
#define BMP_SMALL_O2   5
#define BMP_SMALL_HN   6
#define BMP_EXLAMATION 7
#define BMP_KEY_INPUT  8
#define BMP_FORWARD    9
#define BMP_BACKWARD   10
#define BMP_HOME       11

const char* GetBmp(char bmp_id);
char GetBmpWidth(char bmp_id);
char GetBmpHeight(char bmp_id);

#endif
