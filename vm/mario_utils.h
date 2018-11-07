/*
Some utils functions like str / array 
*/

#ifndef MARIO_UTILS
#define MARIO_UTILS

#include <inttypes.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus /* __cplusplus */
extern "C" {
#else
#ifndef bool
typedef enum bool_enum {false, true} bool;
#endif
#endif

/** memory functions.-----------------------------*/
#ifndef PRE_ALLOC
	#include <stdlib.h>
	#define _malloc malloc
	#define _realloc realloc
	#define _free free
#else
/*TODO*/
#endif

#define STATIC_STR_MAX 32

typedef void (*free_func_t)(void* p, void* extra);

extern void _free_none(void*p, void* extra);

extern void (*_out_func)(const char*);
extern bool _debug_mode;
void _debug(const char* s);
void _err(const char* s);

typedef struct st_array {
	void** items;
	uint32_t max: 16;
	uint32_t size: 16;
} m_array_t;

void array_init(m_array_t* array);
void array_add(m_array_t* array, void* item);
void* array_add_buf(m_array_t* array, void* s, uint32_t sz);
void* array_get(m_array_t* array, uint32_t index);
void* array_set(m_array_t* array, uint32_t index, void* p);
void* array_tail(m_array_t* array);
void* array_head(m_array_t* array);
void* array_remove(m_array_t* array, uint32_t index);
void array_del(m_array_t* array, uint32_t index, free_func_t fr, void* extra);
void array_remove_all(m_array_t* array);
void array_clean(m_array_t* array, free_func_t fr, void* extra);
#define array_tail(array) (((array)->items == NULL || (array)->size == 0) ? NULL: (array)->items[(array)->size-1]);

typedef struct st_str {
	char* cstr;
	uint32_t max: 16;
	uint32_t len: 16;
} str_t;

void str_reset(str_t* str);
char* str_ncpy(str_t* str, const char* src, uint32_t l);
char* str_cpy(str_t* str, const char* src);
str_t* str_new(const char* s);
char* str_append(str_t* str, const char* src);
char* str_add(str_t* str, char c);
void str_free(str_t* str);
const char* str_from_int(int i, char* s);
const char* str_from_float(float i, char* s);
const char* str_from_bool(bool b);
int str_to_int(const char* str);
float str_to_float(const char* str);
void str_split(const char* str, char c, m_array_t* array);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif