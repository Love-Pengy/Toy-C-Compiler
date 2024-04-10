/*
 * d-java.c
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

//#define MSDOS

#define TARGET "D-Java"
#define TARGET_CAPS "D-JAVA"

#if defined (MSDOS) || defined (__MSDOS__)
#include <crt0.h>
int _crt0_startup_flags = _CRT0_FLAG_DISALLOW_RESPONSE_FILES;
#endif /* MSDOS */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined (MSDOS) || defined (__MSDOS__)
#include <io.h>
#include <fcntl.h>
#endif /* MSDOS */

int getopt(int, char * const *, const char *);

#include "d-java.h"

/* Global variables */
Options options;
FILE *errfile;
int status;
u4 *labels;
u4 num_labels;

static void print_usage(void);
static void print_help(void);

char buf[1025];

int main(int argc, char *argv[])
{
    int c;
    extern char *optarg;
    extern int optind;
    int firstclassfile_flag;
    int firstfileind;
    int errflg = 0;
    int errfile_flag = FALSE;
    time_t now;
    
    FILE *fp;
    ClassFile *cf;
    int status;

    *buf = '\0';
    
    if (argc < 2) {
	print_usage();
	exit(ERR_USAGE);
    }
    
    /* Set default options */
    options.showLVT = 1;
    options.showLNT = 1;
    options.jasmin  = 0;
    options.verbose = 0;
    options.fieldsOnly = 0;
    options.redirect_stderr = 0;
    errfile = stderr;
    options.attributesOnly = 0;

    while ((c = getopt(argc, argv, "ae:fhvn:o:")) != EOF) {
        switch (c) {
            case 'a':
                options.attributesOnly = 1;
                break;
            case 'e':
            	if (errfile_flag == TRUE) {
            	    fprintf(stderr, "Warning: Only first '-e' used\n");
            	    break;
            	}
            	options.redirect_stderr = 1;
            	/* If the first char is a '+' then append */
            	if (optarg[0] == '+') {
            	    errfile = fopen(optarg+1, "wt+");
            	}
            	else {
            	    errfile = fopen(optarg, "wt");
            	}
            	if (errfile == NULL) {
            	    fprintf(stderr, "Warning: Could not open \"%s\" for writing.  Defaulting to stderr.\n",
            	        optarg[0] == '+' ? optarg+1 : optarg);
            	    errfile = stderr;
            	}
            	else {
            	    errfile_flag = TRUE;
            	    time(&now);
            	    fprintf(errfile, "---\n"TARGET" log\n%s---\n",
            	        asctime(localtime(&now)));
            	}
            	break;
            case 'f':
                options.fieldsOnly = 1;
                break;
            case 'h':
                print_help();
                exit(0);
            case 'v':
                options.verbose = 1;
                break;
            case 'n':
                if (!strcmp(optarg, "lvt")) options.showLVT = 0;
                else if (!strcmp(optarg, "lnt")) options.showLNT = 0;
                else errflg++;
                break;
            case 'o':
                if (!strcmp(optarg, "jasmin")) {
                    options.jasmin = 1;
                    options.javaa = 0;
                }
                else if (!strcmp(optarg, "javaa")) {
                    options.javaa = 1;
                    options.jasmin = 0;
                }
                else if (!strcmp(optarg, "default")) {
                    options.jasmin = 0;
                    options.javaa = 0;
                }
                else errflg++;
                break;
            case '?':
                errflg++;
                break;
        }
    }
    if (errflg) {
        print_usage();
        exit(ERR_USAGE);
    }

    /* For spacing  purposes */
    firstclassfile_flag = TRUE;
    /* Keeps track of if the first classfile is '-' */
    firstfileind = optind;
    for ( ; optind < argc; optind++) {
        strcpy(buf, argv[optind]);
        /* Check for the stdin option */
        if (optind == firstfileind && !strcmp(buf, "-")) {
            fp = stdin;
/* stdin in MSDOS is text mode */
#if defined (MSDOS) || defined (__MSDOS__)
            setmode(fileno(stdin), O_BINARY);
#endif /* MSDOS */
        }
        else {
            if (strcmp(buf + strlen(buf)-6, ".class"))
                strcat(buf, ".class");
            fp = fopen(buf, "rb");
        }

        if (fp == NULL) {
            fprintf(errfile, TARGET": Error: %s \"%s\"\n", err_string[ERR_OPEN], buf);
            continue;
        }

        if ((status = readClassFile(fp, &cf)) != ERR_OK) {
            fprintf(errfile, TARGET": Error: %s\n", err_string[status]);
            /* Don't cf here because on error, readClassFile() does. */
            if (fp == stdin) break;
            continue;
        }
    
        if (options.verbose) fprintf(errfile, "Disassembling \"%s\"", buf);

        if (firstclassfile_flag == FALSE) putchar('\n');
        firstclassfile_flag = FALSE;
        if (options.jasmin) putchar(';');
        printf(">> %s <<\n", fp == stdin ? "stdin" : buf);
        if ((status = showClassFile(cf)) != ERR_OK) {
            fprintf(errfile, "\n"TARGET": Error: %s\n", err_string[status]);
        }
        if (options.verbose) fputc('\n', stderr);
        
        /*decompileClassFile(cf);*/

        freeClassFile(cf);
    
        if (fp == stdin) break;
        
        if (fclose(fp) != 0) {
            fprintf(errfile, TARGET": Error: %s \"%s\"\n", err_string[ERR_CLOSE], buf);
            continue;
        }
    }
    
    if (errfile != stderr) fclose(errfile);
    
    return 0;
}

static void print_usage(void)
{
    fprintf(stderr, "Compile date: "__DATE__"\n");
    fprintf(stderr, "Usage: "TARGET" [-afhv] [-e [+]<logfile>] [[-n <info>]...] [-o <format>]\n");
    fprintf(stderr, "              [-]|[classfile...]\n");
    fprintf(stderr, "  Output is to stdout.\n");
    fprintf(stderr, "  "TARGET" -h for more detailed help.\n");
}

static void print_help(void)
{
    print_info(stderr);
    fprintf(stderr, "Usage: "TARGET" [options] ClassFile[.class]...\n");
    fprintf(stderr, "  If the first classfile is '-' then "TARGET" will read from stdin.\n");
    fprintf(stderr, "        -a              Only show names of ClassFile and Method attributes\n");
    fprintf(stderr, "                          (ignored for jasmin output)\n");
    /*fprintf(stderr, "        -d              Decompile\n");*/
    fprintf(stderr, "        -e [+]<logfile> Redirect stderr to <logfile>\n");
    fprintf(stderr, "                          (a '+' as the first character appends)\n");
    fprintf(stderr, "        -f              Fields only, don't display method bodies\n");
    fprintf(stderr, "                          (ignored for jasmin output)\n");
    fprintf(stderr, "        -h              This help screen\n");
    /*fprintf(stderr, "        -i <size>       Indent size (default 4 spaces)\n");*/
    fprintf(stderr, "        -n <info>       Don't output debugging info,\n");
    fprintf(stderr, "                        where <info> can be one of:\n");
    fprintf(stderr, "                            * lvt - local variable table\n");
    fprintf(stderr, "                            * lnt - line number table\n");
    fprintf(stderr, "        -o <format>     Output in a specific format,\n");
    fprintf(stderr, "                        where <format> can be one of:\n");
    fprintf(stderr, "                            * jasmin\n");
    fprintf(stderr, "                            * default (automatic if \'-o\' is not specified)\n");
    fprintf(stderr, "        -v              Verbose\n");
    fprintf(stderr, "        --              End of options\n");
/*
    fprintf(stderr, "Examples:   "TARGET" -f Animator\n");
    fprintf(stderr, "            "TARGET" -o jasmin Animator.class\n");
    fprintf(stderr, "            "TARGET" -vo jasmin -n lvt -n lnt Animator\n");
    fprintf(stderr, "            "TARGET" -f -- -MyClassWithDashInFront\n");
*/
}

void print_info(FILE *fp)
{
    fprintf(fp, "--------- "TARGET_CAPS" ("__DATE__") ---------\n");
    /*fprintf(fp, "  written by: Shawn Silverman\n");*/
    fprintf(fp, " Copyright (c) 1996-1997 Shawn Silverman\n");
    fprintf(fp, "      e-mail: umsilve1@cc.umanitoba.ca\n");
    fprintf(fp, "----------------------------------------\n");
}

void print_info_jasmin(FILE *fp)
{
    fprintf(fp, ";\n");
    fprintf(fp, "; Output created by "TARGET" ("__DATE__")\n");
    fprintf(fp, "; mailto:umsilve1@cc.umanitoba.ca\n");
    fprintf(fp, "; Copyright (c) 1996-1997 Shawn Silverman\n");
    fprintf(fp, ";\n");
}
