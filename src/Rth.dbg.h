
#if 0
#include <stdio.h>
static FILE* g_logfile;
#define log_init(F)	{ g_logfile = fopen( F , "w" ); }
#define log_close	{ fclose( g_logfile ); }
#define log_sz(X)	{ fprintf( g_logfile, "[%d] - %s\n", 0, X ); fflush(g_logfile); }
#define log_num(X)	{ fprintf( g_logfile, "[%d] - %d\n", 0, X ); fflush(g_logfile); }
#define log_num2(X ,Y)	{ fprintf( g_logfile, "[%d] - %d - %d\n", 0, X, Y ); fflush(g_logfile); }
#else
#define log_init(F)	
#define log_close	
#define log_sz(X)	
#define log_num(X)	
#define log_num2(X,Y)	
#endif


