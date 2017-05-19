#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <lod/lod.h>
#include "lod_private.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "std_io.h"

LOD_EXPORT lod_ctx *lod_new(void)
{
	return calloc(1, sizeof(lod_ctx));
}

LOD_EXPORT lod_ctx * lod_open(const char * filename)
{
	lod_ctx * ctx = lod_new();
	if (ctx)
		lod_set_std_vio(ctx, filename);

	return ctx;
}

LOD_EXPORT lod_ctx * lod_open_vio(lod_ctx * ctx, struct lod_vio * vio)
{
	int ret = LOD_FALSE;
	lod_ctx * c = ctx;

	lod_close(c);

	if (vio)
	{
		if (vio->get_filelen && vio->read && vio->seek && vio->tell && vio->write)
		{
			if (!c)
				c = lod_new();

			c->vio = vio;
			c->close_vio = LOD_FALSE;
			ret = LOD_TRUE;
		}
	}

	return c;
}

LOD_EXPORT void lod_close(lod_ctx * ctx)
{
	if (ctx)
	{
		if (ctx->is_opened)
		{
			if (ctx->vio)
			{
				if (ctx->close_vio)
				{
					if (ctx->fp)
						fclose(ctx->fp);
				}
				free(ctx->vio);
			}
		}
		
		memset(ctx, 0, sizeof(*ctx));
	}
}

LOD_EXPORT void lod_free(lod_ctx *ctx)
{
	if (ctx)
	{
		lod_close(ctx);
		free(ctx);
	}
}
