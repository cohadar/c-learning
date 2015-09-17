//
//  double.c - detects adjacent identical words in file or stdin
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "double.h"

#define MAX_WORD_LENGTH 50

static char buffer[ MAX_WORD_LENGTH + 1 ];

//===========================================================================//
static void ReadWord( FILE *fp, int *line ) {
    int i = 1;
    int c;
    while ( ( c = getc( fp ) ) != EOF && i < MAX_WORD_LENGTH ) {
        if ( isspace( c ) ) {
            if ( c == '\n' ){
                ( *line )++;
            }
            break;
        }
        buffer[ i++ ] = c;
    }
    buffer[ i ] = 0;
}

//===========================================================================//
static void DoubleWords( const char *fileName, FILE *fp ) {
    int c;
    int line = 1;
    while ( ( c = getc( fp ) ) != EOF ){
        if ( isspace( c ) ) {
            if ( c == '\n' ){
                line++;
            }
            continue;
        }
        // read word
        buffer[ 0 ] = c;
        ReadWord( fp, &line );
        printf( "%s[%d]: %s\n", fileName, line, buffer );
    }
}

//===========================================================================//
int DoubleMain( int argc, const char **argv ) {
    if ( argc == 1 ) {
        DoubleWords( NULL, stdin );
        return EXIT_SUCCESS;
    }
    for ( int i = 1; i < argc; i++ ) {
        const char * fileName = argv[ i ];
        FILE *fp = fopen( fileName, "r" );
        if ( fp == NULL ) {
            fprintf( stderr, "cannot open: %s, reason: %s\n", fileName, strerror( errno ) );
            return EXIT_FAILURE;
        }
        DoubleWords( argv[ i ], fp );
    }
    return EXIT_SUCCESS;
}


#ifdef DEBUG

//===========================================================================//
int Njak( int x ) {
    ASRT_TRUE( x < 100 );
    return 0;
}

//===========================================================================//
int Zrak( const char *a, const char *b ) {
    ASRT_STRZ( a, b );
    return 0;
}


//===========================================================================//
void DoubleSuite() {
    ASRT_TEST( Njak, 1 );
    ASRT_TEST( Njak, 3 );
    ASRT_TEST( Njak, 12 );
    ASRT_TEST( Njak, 15 );
    ASRT_TEST( Njak, 17 );
    ASRT_TEST( Zrak, "aaa", "aaa" );
}

#endif // DEBUG
