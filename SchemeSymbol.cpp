#include "SchemeSymbol.h"

SchemeSymbol::SchemeSymbol(string s){
	symbolName = s;
}

string SchemeSymbol::value() const{
	return symbolName;
}
