
#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "microrl/microrl.h"
#include "Stream.h"



void transport_char(Stream& a, Stream& b);
void transport_char(Stream& a, Stream* b);
void transport_all(Stream* a, Stream* b);
void transport_char(Stream& a, microrl_t& m);
//void double_transport_char(Stream& a, microrl_t& m,Stream* b);
//void double_transport_char(Stream& a, microrl_t& m,Stream& b);
void double_transport_char(Stream& a, Stream& d,Stream* b);





#endif
