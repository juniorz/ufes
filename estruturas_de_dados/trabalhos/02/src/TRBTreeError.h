#ifndef TRBTreeError_h
#define TRBTreeError_h
#include <iostream>

class TRBTreeError {

	public:
		TRBTreeError (char *metodo, char *msg) { 
			std::cerr << "Error: [TBRTree::" << metodo << "]: " << msg << std::endl;
		};
		
};

#endif
