/*
 * Copyright (C) 2006 Evgeniy Stepanov <eugeni.stepanov@gmail.com>
 * Copyright (C) 2009 Grigori Goronzy <greg@geekmind.org>
 *
 * This file is part of libass.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ass.h>
//#include <png.h>

#define PNG_BYTES_TO_CHECK 4

typedef struct image_s {
	int width, height, stride;
	unsigned char *buffer;      
} image_t;

ASS_Library *ass_library;
ASS_Renderer *ass_renderer;

//static image_t* read_png (char *filepath)
//{
//	image_t* frame;
//	FILE *fp;
//	png_structp png_ptr;
//	png_infop info_ptr;
//	png_byte **row_pointers;
//	char buf[PNG_BYTES_TO_CHECK];
//	int w, h, x, y, temp, color_type, ev=0;

//	frame = malloc(sizeof(image_t*));
//	fp = fopen( filepath, "r" );
//	if( fp == NULL ) {
//		return 0;
//	}
//	png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0 );
//	info_ptr = png_create_info_struct( png_ptr );

//	setjmp( png_jmpbuf(png_ptr) );
//	/* 读取PNG_BYTES_TO_CHECK个字节的数据 */
//	temp = fread( buf, 1, PNG_BYTES_TO_CHECK, fp );
//	/* 若读到的数据并没有PNG_BYTES_TO_CHECK个字节 */
//	if( temp < PNG_BYTES_TO_CHECK ) {
//		fclose(fp);
//		png_destroy_read_struct( &png_ptr, &info_ptr, 0);
//		return 0;
//	}/* 检测数据是否为PNG的签名 */
//	temp = png_sig_cmp( (png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK );
//	/* 如果不是PNG的签名，则说明该文件不是PNG文件 */
//	if( temp != 0 ) {
//		fclose(fp);
//		png_destroy_read_struct( &png_ptr, &info_ptr, 0);
//		return 0;
//	}

//	/* 复位文件指针 */
//	rewind( fp );
//	/* 开始读文件 */
//	png_init_io( png_ptr, fp );
//	/* 读取PNG图片信息 */
//	png_read_png( png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0 );
//	/* 获取图像的色彩类型 */
//	color_type = png_get_color_type( png_ptr, info_ptr );
//	/* 获取图像的宽高 */
//	frame->width = png_get_image_width( png_ptr, info_ptr );
//	frame->height = png_get_image_height( png_ptr, info_ptr );
//	/* 获取图像的所有行像素数据，row_pointers里边就是rgba数据 */
//	row_pointers = png_get_rows( png_ptr, info_ptr );
//	/* 根据不同的色彩类型进行相应处理 */
//	switch( color_type ) {
//		case PNG_COLOR_TYPE_RGB_ALPHA:
//			frame->stride = 3 * frame->width;
//			frame->buffer = (unsigned char*)malloc(frame->width * frame->height * 3 + 1);

//			for(y=0; y<frame->height; ++y) {
//				for(x = 0; x < frame->width*4 - 1; x += 4) {
//					frame->buffer[ev++] = row_pointers[y][x+2]; // b
//				    frame->buffer[ev++] = row_pointers[y][x+1]; // g
//					frame->buffer[ev++] = row_pointers[y][x];   // r
//															    // Delete alpha
//				}
//			}
//			break;
//		case PNG_COLOR_TYPE_RGB:
//			frame->stride = 3 * frame->width;
//			frame->buffer = (unsigned char*)malloc(frame->width * frame->height * 3 + 1);

//			for(y=0; y<frame->height; ++y) {
//				for(x = 0; x < frame->width*3 - 1; x += 3) {
//					frame->buffer[ev++] = row_pointers[y][x+2];	 // b
//					frame->buffer[ev++] = row_pointers[y][x+1];	 // g
//					frame->buffer[ev++] = row_pointers[y][x];	 // r
//				}
//			}
//			break;
//			/* 其它色彩类型的图像就不读了 */
//		default:
//			fclose(fp);
//			png_destroy_read_struct( &png_ptr, &info_ptr, 0);
//			exit(1);
//			return 0;
//	}
//	png_destroy_read_struct( &png_ptr, &info_ptr, 0);
//	return frame;
//}	/* -----  end of function read_png  ----- */

void msg_callback(int level, const char *fmt, va_list va, void *data)
{
	if (level > 6)
		return;
	printf("libass: ");
	vprintf(fmt, va);
	printf("\n");
}

//static void write_png(char *fname, image_t *img)
//{
//	FILE *fp;
//	png_structp png_ptr;
//	png_infop info_ptr;
//	png_byte **row_pointers;
//	int k;

//	png_ptr =
//		png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//	info_ptr = png_create_info_struct(png_ptr);
//	fp = NULL;

//	if (setjmp(png_jmpbuf(png_ptr))) {
//		png_destroy_write_struct(&png_ptr, &info_ptr);
//		fclose(fp);
//		return;
//	}

//	fp = fopen(fname, "wb");
//	if (fp == NULL) {
//		printf("PNG Error opening %s for writing!\n", fname);
//		return;
//	}

//	png_init_io(png_ptr, fp);
//	png_set_compression_level(png_ptr, 0);

//	png_set_IHDR(png_ptr, info_ptr, img->width, img->height,
//			8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
//			PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

//	png_write_info(png_ptr, info_ptr);

//	png_set_bgr(png_ptr);

//	row_pointers = (png_byte **) malloc(img->height * sizeof(png_byte *));
//	for (k = 0; k < img->height; k++)
//		row_pointers[k] = img->buffer + img->stride * k;

//	png_write_image(png_ptr, row_pointers);
//	png_write_end(png_ptr, info_ptr);
//	png_destroy_write_struct(&png_ptr, &info_ptr);

//	free(row_pointers);

//	fclose(fp);
//}

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
