#ifndef HASHBLOCK_H
#define HASHBLOCK_H

#include "uint256.h"
#include "sph_sha2.h"
#include "sph_radiogatun.h"
#include "sph_panama.h"

#ifndef QT_NO_DEBUG
#include <string>
#endif

#ifdef GLOBALDEFINED
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL sph_sha256_context		z_sha256;
GLOBAL sph_radiogatun64_context	z_radiogatun64;
GLOBAL sph_panama_context	z_panama;


#define fillz() do { \
    sph_sha256_init(&z_sha256); \
	sph_radiogatun64_init(&z_radiogatun64); \
    sph_panama_init(&z_panama); \
} while (0) 

template<typename T1>
inline uint256 HashMirror(const T1 pbegin, const T1 pend)

{
    sph_sha256_context	 ctx_sha256;
	sph_radiogatun64_context  ctx_radiogatun64;
	sph_panama_context	 ctx_panama;
    static unsigned char pblank[3];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif

       
    uint512 hash[7];

    sph_radiogatun64_init(&ctx_radiogatun64);
    sph_radiogatun64(&ctx_radiogatun64, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_radiogatun64_close(&ctx_radiogatun64, static_cast<void*>(&hash[0]));
    
    sph_panama_init(&ctx_panama);
    sph_panama(&ctx_panama, static_cast<const void*>(&hash[0]), 64);
    sph_panama_close(&ctx_panama, static_cast<void*>(&hash[1]));
    
    sph_sha256_init(&ctx_sha256);
    sph_sha256(&ctx_sha256, static_cast<const void*>(&hash[1]), 64);
    sph_sha256_close(&ctx_sha256, static_cast<void*>(&hash[2]));
        
     /*-------------------------------MIRROR---------------------------*/
        
    sph_sha256_init(&ctx_sha256);
    sph_sha256(&ctx_sha256, static_cast<const void*>(&hash[2]), 64);
    sph_sha256_close(&ctx_sha256, static_cast<void*>(&hash[3]));    
    
    sph_panama_init(&ctx_panama);
    sph_panama(&ctx_panama, static_cast<const void*>(&hash[3]), 64);
    sph_panama_close(&ctx_panama, static_cast<void*>(&hash[4]));
    
    sph_radiogatun64_init(&ctx_radiogatun64);
    sph_radiogatun64(&ctx_radiogatun64, static_cast<const void*>(&hash[4]), 64);
    sph_radiogatun64_close(&ctx_radiogatun64, static_cast<void*>(&hash[5]));
    

    return hash[5].trim256();
}






#endif // HASHBLOCK_H

