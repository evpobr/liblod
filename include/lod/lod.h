#ifndef LOD_H
#define LOD_H

/**
 * @file lod.h
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "lod_export.h"

typedef struct lod_private lod_ctx;

typedef long long lod_off_t;

typedef lod_off_t (*lod_vio_get_filelen)(void *user_data);
typedef int (*lod_vio_seek)(lod_off_t offset, int whence, void *user_data);
typedef size_t (*lod_vio_read)(void *ptr, size_t count, void *user_data);
typedef size_t (*lod_vio_write)(const void *ptr, size_t count, void *user_data);
typedef lod_off_t (*lod_vio_tell)(void *user_data);

/**
 * @brief LOD boolean types
 */
enum LOD_BOOL
{
	/*!< False value. */
	LOD_FALSE = 0,
	/*!< True value. */
	LOD_TRUE  = 1
};

/**
* @brief LOD Virtual IO structure
*/
struct lod_vio
{
	lod_vio_get_filelen	get_filelen;
	lod_vio_seek		seek;
	lod_vio_read		read;
	lod_vio_write		write;
	lod_vio_tell		tell;
};

/**
 * @brief Creates new LOD context.
 */
LOD_EXPORT lod_ctx *lod_new(void);

/**
 * @brief Opens existing LOD file from path.
 */
LOD_EXPORT lod_ctx * lod_open(const char *filename);

/**
 * @brief Opens existing LOD file using virtual IO.
 */
LOD_EXPORT lod_ctx * lod_open_vio(lod_ctx *ctx, struct lod_vio *vio);

/**
 * @brief Closes existing LOD context and sets all values to defaults.
 */
LOD_EXPORT void lod_close(lod_ctx *ctx);

/**
 * @brief Destoys LOD context and frees allocated memory.
 *
 */
LOD_EXPORT void lod_free(lod_ctx *ctx);

#ifdef __cplusplus
}
#endif

#endif
