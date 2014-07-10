


#include "container/List.h"



	void* List::operator[](int n){List_it pl; pl.init(*this); for(int i=0;i<n;i++) pl++; return(pl.get());};
	const void* List::operator[](int n) const {List_it pl; pl.init(*this); for(int i=0;i<n;i++) pl++; return(pl.get());};
