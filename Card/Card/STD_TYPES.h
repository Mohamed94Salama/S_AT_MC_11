#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Boolean Standard Values */
#define FALSE                          0u
#define TRUE									1u

#define ENABLE									1u
#define DISABLE								0u

#define NULLPTR			((void *)0)
typedef unsigned char           uint8_t;
typedef signed char             sint8_t;
typedef unsigned int            uint16_t;
typedef signed int              sint16_t;
typedef unsigned long int       uint32_t;
typedef signed long int         sint32_t;
typedef unsigned long long int  uint64_t;
typedef signed long long int    sint64_t;

typedef enum {E_ERROR=0, E_OK=1,ERROR=0,SUCCESS=1}				enuErrorStatus_t;
typedef enum {LOW, HIGH}               enuDigitalStates_t;

#endif /* STD_TYPES_H_ */