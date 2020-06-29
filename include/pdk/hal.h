#ifndef __HAL_H__
#define __HAL_H__

#if defined(PMS150C)
 #include "pms150c.h"
#elif defined(PMS152)
 #include "pms152.h"
#elif defined(PFS154)
 #include "pfs154.h"
#elif defined(PFS172)
 #include "pfs172.h"
#elif defined(PFS173)
 #include "pfs173.h"
#else
 #error "Unknown processor. Please define processor"
#endif

#endif //__HAL_H__
