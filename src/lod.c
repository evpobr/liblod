#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <lod/lod.h>
#include "lod_private.h"

#include <stdlib.h>

LOD_API lod_ctx *lod_new(void)
{
	return malloc(sizeof(lod_ctx));
}

LOD_API void lod_free(lod_ctx *ctx)
{
	if (ctx)
		free(ctx);
}
