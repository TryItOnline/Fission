//
//  PartialMirror.cpp
//  Fission
//
//  Created by C0deH4cker on 2/26/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "PartialMirror.h"
#include <cstdint>
#include "common.h"
#include "Atom.h"
#include "Grid.h"

using namespace fsn;


PartialMirror::PartialMirror(Token type, Grid& grid)
: Component(type), grid(grid) {}

bool PartialMirror::onHit(Atom& atom) {
	switch(type) {
		case Token::PARTIAL_SPLITTER: {
			int64_t smaller = atom.mass >> 1;
			atom.mass -= smaller;
			
			Atom reflected(atom);
			atom.dir ^= 2;
			atom.mass = smaller;
			
			grid.spawn(reflected);
			break;
		}
		
		case Token::PARTIAL_CLONER: {
			Atom reflected(atom);
			reflected.dir ^= 2;
			
			grid.spawn(reflected);
			break;
		}
		
		default:
			fatal("Cell '%c' is not a PartialMirror.", (char)type);
	}
	
	return false;
}

