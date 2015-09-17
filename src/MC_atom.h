//
//  MC_atom.h
//  c-learning
//
//  Created by Damir Cohadarevic on 4/11/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#ifndef __c_learning__MC_atom__
#define __c_learning__MC_atom__

#include <stdio.h>

typedef struct MC_Atom MC_Atom;

extern size_t           MC_AtomLength( const MC_Atom *atom );
extern const char *     MC_AtomBytes ( const MC_Atom *atom );
extern unsigned int     MC_AtomHash  ( const char *str, size_t len );
extern const MC_Atom *  MC_AtomNew   ( const char *str, size_t len );
extern const MC_Atom *  MC_AtomString( const char *str );
extern const MC_Atom *  MC_AtomLong  ( long n );

#ifdef DEBUG
extern void MC_AtomSuite();
#endif

#endif /* defined(__c_learning__MC_atom__) */
