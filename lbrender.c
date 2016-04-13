#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ass.h>

#define PNG_BYTES_TO_CHECK 4

typedef struct image_s {
	int width, height, stride;
	unsigned char *buffer;      
} image_t;

ASS_Library *ass_library;
ASS_Renderer *ass_renderer;


void msg_callback(int level, const char *fmt, va_list va, void *data)
{
	if (level > 6)
		return;
	printf("libass: ");
	vprintf(fmt, va);
	printf("\n");
}


static void init(int frame_w, int frame_h)
{
	ass_library = ass_library_init();
	if (!ass_library) {
		printf("ass_library_init failed!\n");
		exit(1);
	}

	ass_set_message_cb(ass_library, msg_callback, NULL);

	ass_renderer = ass_renderer_init(ass_library);
	if (!ass_renderer) {
		printf("ass_renderer_init failed!\n");
		exit(1);
	}

	ass_set_frame_size(ass_renderer, frame_w, frame_h);
	ass_set_fonts(ass_renderer, NULL, "Sans", 1, NULL, 1);
}

static image_t *gen_image(int width, int height)
{
	image_t *img = malloc(sizeof(image_t));
	img->width = width;
	img->height = height;
	img->stride = width * 3;
	img->buffer = (unsigned char *) calloc(1, height * width * 3);
	memset(img->buffer, 63, img->stride * img->height);
	//for (int i = 0; i < height * width * 3; ++i)
	// img->buffer[i] = (i/3/50) % 100;
	return img;
}

#define _r(c)  ((c)>>24)
#define _g(c)  (((c)>>16)&0xFF)
#define _b(c)  (((c)>>8)&0xFF)
#define _a(c)  ((c)&0xFF)

static void blend_single(image_t * frame, ASS_Image *img)
{
	int x, y;
	unsigned char opacity = 255 - _a(img->color);
	unsigned char r = _r(img->color);
	unsigned char g = _g(img->color);
	unsigned char b = _b(img->color);

	unsigned char *src;
	unsigned char *dst;

	src = img->bitmap;
    dst = frame->buffer + img->dst_y * frame->stride + img->dst_x * 4;
	for (y = 0; y < img->h; ++y) {
		for (x = 0; x < img->w; ++x) {
			unsigned k = ((unsigned) src[x]) * opacity / 255;
			// possible endianness problems
            dst[x * 4] = (k * b + (255 - k) * dst[x * 4]) / 255;
            dst[x * 4 + 1] = (k * g + (255 - k) * dst[x * 4 + 1]) / 255;
            dst[x * 4 + 2] = (k * r + (255 - k) * dst[x * 4 + 2]) / 255;
		}
		src += img->stride;
		dst += frame->stride;
	}
}

static void blend(image_t * frame, ASS_Image *img)
{
	int cnt = 0;
	while (img) {
		blend_single(frame, img);
		++cnt;
		img = img->next;
	}
	printf("%d images blended\n", cnt);
}

void lb_render(unsigned char *img, char *sub, size_t bufsize)
{
	const int frame_w = 1002;
	const int frame_h = 321;

    double tm = 1;

    image_t* frame;
    frame = malloc(sizeof(image_t*));
    frame->buffer = img;
    frame->height = 321;
    frame->stride = 4 * 1002;
    frame->width = 1002;
	init(frame_w, frame_h);
    ASS_Track *track = ass_read_memory(ass_library, sub, bufsize, NULL);
	if (!track) {
		printf("track init failed!\n");
		return 1;
	}

    ASS_Image *ass_img =
		ass_render_frame(ass_renderer, track, (int) (tm * 1000), NULL);
//	image_t *frame = gen_image(frame_w, frame_h);
    blend(frame, ass_img);

	ass_free_track(track);
	ass_renderer_done(ass_renderer);
	ass_library_done(ass_library);

//	write_png(out, frame);

    //free(frame->buffer);
    //free(frame);

}
