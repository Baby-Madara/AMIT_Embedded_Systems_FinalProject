#ifndef STD_TYPES_H_INCLUDED
#define STD_TYPES_H_INCLUDED

#define NULL ((void*) (0x00))

#define TRUE	1
#define FALSE	0
#define HIGH	1
#define LOW		0

#define NULLptr	((void(*)(void))(0x00))

typedef unsigned char 		u8;
typedef signed 	 char 		s8;

typedef unsigned char 		bool;

typedef unsigned short 		u16;
typedef signed 	 short 		s16;

typedef unsigned int 		u32;
typedef signed   int 		s32;

typedef unsigned long long 	u64;
typedef signed   long long  s64;

typedef float			float32;
typedef double			float64;



#endif //STD_TYPES_H_INCLUDED
