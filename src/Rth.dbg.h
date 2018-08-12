
#if 1
#include <stdio.h>
static FILE* g_logfile;
#define log_init(F)	{ g_logfile = fopen( F , "w" ); }
#define log_close	{ fclose( g_logfile ); }
#define log_sz(X)	{ fprintf( g_logfile, "[%d] - %s\n", __LINE__, X ); fflush(g_logfile); }
#define log_sz_num(X, Y)	{ fprintf( g_logfile, "[%d] - %s : %d\n", __LINE__, X, Y ); fflush(g_logfile); }
#define log_num(X)	{ fprintf( g_logfile, "[%d] - %s : %d\n", __LINE__, #X, X ); fflush(g_logfile); }
#define log_num2(X ,Y)	{ fprintf( g_logfile, "[%d] - %s : %d - %s : %d\n", __LINE__, #X, X, #Y, Y ); fflush(g_logfile); }
#define log_num3(X ,Y, Z)	{ fprintf( g_logfile, "[%d] - %s : %d - %s : %d - %s : %d\n", __LINE__, #X, X, #Y, Y, #Z, Z ); fflush(g_logfile); }
#else
#define log_init(F)	
#define log_close	
#define log_sz(X)	
#define log_sz_num(X, Y)
#define log_num(X)	
#define log_num2(X,Y)	
#define log_num3(X,Y,Z)	
#endif


