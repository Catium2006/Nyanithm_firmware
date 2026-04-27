#ifndef __DEBUG_H__
#define __DEBUG_H__

#define ENABLE_DEBUG 0

#include <stdio.h>

#ifndef ENABLE_DEBUG
#define ENABLE_DEBUG 0
#endif

#if ENABLE_DEBUG
#define DEBUG(content) printf("[DEBUG] %s line %d -> %s\n", __FILE_NAME__, __LINE__, content)
#else
#define DEBUG(content)
#endif


#endif