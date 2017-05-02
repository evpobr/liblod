#ifndef LOD_H
#define LOD_H

/**
 * @file lod.h
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "lod_export.h"

typedef struct lod_private lod_ctx;

/**
 * @brief Creates new LOD context.
 */
LOD_API lod_ctx *lod_new(void);

/**
 * @brief Destoys LOD context and frees allocated memory.
 */
LOD_API void lod_free(lod_ctx *ctx);

#ifdef __cplusplus
}
#endif

#endif
