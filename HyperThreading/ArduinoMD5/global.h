#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifndef PROTOTYPES
#define PROTOTYPES 0
#endif//PROTOTYPES

typedef unsigned char* POINTER; //POINTER defines a generic pointer type
typedef unsigned short int UINT2; //UINT2 defines a two byte word
typedef unsigned long int UINT4; //UINT4 defines a four byte word

//PROTO_LIST is defined depending on how PROTOTYPES is defined above
//If using PROTOTYPES then PROTO_LIST returns the list
//otherwise it returns an empty list

#if PROTOTYPES
    #define PROTO_LIST(list) list
#else
    #define PROTO_LIST(list) ()
#endif

#endif//_GLOBAL_H_