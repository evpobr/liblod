#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <lod/lod.h>
#include "lod_private.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "std_io.h"

const uint32_t lod_magic = 0x00444f4c;

static int lod_read_header(lod_ctx *ctx);

LOD_EXPORT lod_ctx *lod_new(void)
{
	return calloc(1, sizeof(lod_ctx));
}

LOD_EXPORT lod_ctx * lod_open(const char * filename)
{
	int ret = LOD_FALSE;

	lod_ctx * ctx = lod_new();
	if (ctx)
	{
		lod_set_std_vio(ctx, filename);

		if (lod_read_header(ctx) == LOD_TRUE)
		{
			if (ctx->header.magic == 0x00444f4c)
			{
				size_t enrtries_size = sizeof(struct lod_entry) * ctx->header.entries_count;
				ctx->entries = malloc(enrtries_size);
				size_t entries_size_read = ctx->vio->read(ctx->entries, enrtries_size, ctx->user_data);
				if (entries_size_read == enrtries_size)
					ret = LOD_TRUE;
			}
		}
	}

	if (ret == LOD_FALSE)
		lod_close(ctx);

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
					if (ctx->user_data)
						fclose(ctx->user_data);
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

static int lod_read_header(lod_ctx *ctx)
{
	int ret = LOD_FALSE;

	if (ctx)
	{
		if (ctx->vio)
		{
			ctx->vio->seek(0, SEEK_CUR, ctx->user_data);
			size_t bytes_read = ctx->vio->read(&ctx->header, sizeof(ctx->header), ctx->user_data);
			if (bytes_read == sizeof(ctx->header))
				ret = LOD_TRUE;
		}
	}

	return ret;
}
