#ifndef ___LIST_H
#define ___LIST_H

#include "gmem.h"
#include "glist.h"

class ListNode{
public:
list_head list;
void* Object;
};
#define for_all_list(pl,L) for(pl.init(L);pl.p!=&L.list;pl++) 

#define for_all_list_find_equal(pl,F,Type,elem,eq) \
for_all_list(pl,F) if((((Type*)pl.get())->elem)==eq) 

#define for_all_list_find_more(pl,F,Type,elem,eq) \
for_all_list(pl,F) if((((Type*)pl.get())->elem)>eq) 

#define for_all_list_find_less(pl,F,Type,elem,eq) \
for_all_list(pl,F) if((((Type*)pl.get())->elem)<eq) 

#define for_all_list_obj(pl,F,elem,Type) \
for(pl.init(F) , elem = (Type*)pl.get();pl.p!=&F.list;pl++,elem = (Type*)pl.get()) 

///////////////////////////////////////
class List
{public:
	//data
	list_head list;
	
	
	//constr
	List() {list.next=&list;list.prev=&list;};
	
	void* operator[](int n);
	const void* operator[](int n) const;


	//method
	void add(void *O)
	{	
		ListNode* l = new ListNode;
		l->Object=O;
		list_add_tail(&l->list,&list);
	};
	
	void add_node(ListNode* l)
	{	
		list_add_tail(&l->list,&list);
		};
	
	void print(){
		*stdprint << "num" << "\t" << "pointer" << "\t\t" << "next" << "\t\t" << "prev" <<"\t\t" << "data" << '\n\r' ;
		pr("head"); prtab(); prhex(&list); pr(" ");prtab(); prhex(list.next); pr(" ");prtab(); prhex(list.prev); pr(" "); prln();
		
		list_head *p;int i=0;
		list_for_each(p,&list){
		pr(i); prtab(); prhex(p); pr(" ");prtab(); prhex(p->next); pr(" ");prtab(); prhex(p->prev); pr(" "); prtab(); prhex(container_of(p,ListNode,list)->Object); 
		*stdprint << '\n';		
			i++;
			};	
		};
		
	int number()
	{
		int num=0;
		list_head* p;
		list_for_each(p,&list) num++;
		return num;
		};
	
	void del_all()
	{
		list_head* p,*n;
		list_for_each_safe(p,n,&list) list_del((&(container_of(p,ListNode,list))->list));
		};
	
};

class List_it
	{
	public:
	list_head * p, * next, * prev;
	List_it() {};
	void init(List L) {p=L.list.next; next=L.list.next->next; prev=&L.list;};
	int operator++(int) {p=next;next=p->next;prev=p->prev;};
	int operator--(int) {p=prev;next=p->next;prev=p->prev;};
	
	void print(){
		pr("p:"); prhex(p); pr(" next:"); prhex(next); pr(" prev:"); prhex(prev); pr(" data:");prhex(container_of(p,ListNode,list)->Object); prln();
	};
	
	void unlist() 
	{p->next->prev=p->prev;
	 p->prev->next=p->next;};
	
	void del_obj()
	{
		unlist();
		delete get_node()->Object;
		delete get_node();
	};
		
	
	void* get()
	{
		return get_node()->Object;
		};
	
	
	void relist(List &L2)
	{
		unlist();
		L2.add_node(get_node());
		};	
	
	ListNode* get_node() {return(container_of(p,ListNode,list));}; 
};


#endif
