#include <lod/lod.h>
#include "lod_private.h"
#include <stdio.h>
#include <memory.h>

#include "std_io.h"

lod_off_t std_io_get_filelen(void *user_data)
{
	FILE *fp = user_data;
	if (user_data)
	{
#ifdef _WIN32
		lod_off_t curpos = _ftelli64(fp);
		_fseeki64(fp, 0, SEEK_END);
		lod_off_t len = _ftelli64(fp);
		_fseeki64(fp, curpos, SEEK_CUR);

		return len;
#else
		return -1;
#endif
	}
	else
	{
		return -1;
	}
}

int std_io_seek(lod_off_t offset, int whence, void *user_data)
{
	FILE *fp = user_data;
	if (user_data)
	{
#ifdef _WIN32
		return _fseeki64(fp, offset, whence);
#else
		return -1;
#endif
	}
	else
	{
		return -1;
	}
}

size_t std_io_read(void *ptr, size_t count, void *user_data)
{
	FILE *fp = user_data;
	if (user_data && ptr)
	{
		return fread(ptr, 1, count, fp);
	}
	else
	{
		return -1;
	}
}

size_t std_io_write(const void *ptr, size_t count, void *user_data)
{
	FILE *fp = user_data;
	if (user_data && ptr)
	{
		return fwrite(ptr, 1, count, fp);
	}
	else
	{
		return -1;
	}
}

lod_off_t std_io_tell(void *user_data)
{
	FILE *fp = user_data;
	if (user_data)
	{
#ifdef _WIN32
		return _ftelli64(fp);
#else
		return -1;
#endif
	}
	else
	{
		return -1;
	}
}

FILE *std_io_open(const char *filename, struct lod_vio **vio)
{
#ifdef USE_MSVC_SAFE_CRT
	FILE *fp = NULL;
	fopen_s(&fp, filename, "rb");
#else
	FILE *fp = fopen(filename, "rb");
#endif

	if (fp)
	{
		struct lod_vio *_vio = calloc(1, sizeof(struct lod_vio));
		if (*vio)
		{
			_vio->get_filelen = std_io_get_filelen;
			_vio->seek = std_io_seek;
			_vio->read = std_io_read;
			_vio->write = std_io_write;
			_vio->tell = std_io_tell;
			*vio = _vio;
		}
		else
		{
			fclose(fp);
			fp = NULL;
		}
	}

	return fp;
}

int lod_set_std_vio(lod_ctx *ctx, const char *filename)
{
	int ret = LOD_FALSE;

	lod_close(ctx);

	if (ctx && filename)
	{
		FILE *fp = std_io_open(filename, &ctx->vio);
		if (fp)
		{
			ctx->user_data = fp;
			ctx->close_vio = LOD_TRUE;
			ret = LOD_TRUE;
		}
	}

	return ret;
}
