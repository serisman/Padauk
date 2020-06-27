#ifndef __HAL_H__
#define __HAL_H__

#if defined(PMS150C)
 #include "pdk/pms150c.h"
#elif defined(PFS154)
 #include "pdk/pfs154.h"
#elif defined(PFS173)
 #include "pdk/pfs173.h"
#else
 #error "Unknown processor. Please define processor"
#endif

#endif //__HAL_H__
