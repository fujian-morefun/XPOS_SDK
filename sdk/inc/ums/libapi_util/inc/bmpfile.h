#ifndef __bmpfile_h__
#define __bmpfile_h__

#ifdef __cplusplus
#define BMP_BEGIN_DECLS extern "C" {
#define BMP_END_DECLS }
#else
#define BMP_BEGIN_DECLS
#define BMP_END_DECLS
#endif

BMP_BEGIN_DECLS

#ifndef bool
typedef int bool;
#endif

#ifndef FALSE
#define FALSE (0)
#define TRUE !FALSE
#endif

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif

#ifndef uint16_t
typedef unsigned short uint16_t;
#endif

#ifndef uint32_t
typedef unsigned int uint32_t;
#endif

#define TMPFILE_TMP	"tmpfile.bmp"

typedef enum
{
	BI_RGB = 0, //0~不压缩
	BI_RLE8, //1~RLE8-使用8位RLE压缩方式
	BI_RLE4, //2~RLE4-使用4位RLE压缩方式
	BI_BITFIELDS, //3~Bitfields-位域存放方式
	BI_JPEG, //
	BI_PNG, //
} bmp_compression_method_t;

typedef struct _rgb_pixel_t
{
	uint8_t blue; //蓝色
	uint8_t green; //绿色
	uint8_t red; //红色
	uint8_t alpha;
} rgb_pixel_t;

typedef struct _bmp_header_t
{
	uint8_t magic[2]; /* 文件标识, 一般为“BM”。 BM-Windows 3.1x,95,NT; BA-OS/2 Bitmap Array; CI-OS/2 Color Icon; CP-OS/2 Color Pointer; IC-OS/2 Icon; PT-OS/2 Pointer.*/
	uint32_t filesz; /* 文件大小 。BMP文件的大小(以字节为单位) */
	uint16_t creator1; /* 保留 */
	uint16_t creator2; /* 保留 */
	uint32_t offset; /* 位图数据偏移。从文件开始到位图数据开始之间的偏移量(以字节为单位) */
} bmp_header_t;

typedef struct _bmp_dib_v3_header_t
{
	uint32_t header_sz; /* 信息头长度, 以字节为单位. 值为40 */
	uint32_t width; /* 位图的宽度, 以像素为单位. */
	uint32_t height; /* 位图的高度, 以像素为单位. */
	uint16_t nplanes; /* 位图的面数, 总是1 */
	uint16_t depth; /* 字节/像素. 每个像素的位数(1~单色位图, 4~16色位图, 8~256色位图, 16~16bit高彩色位图, 24~24bit真彩色位图, 32~32bit增强型真彩色位图) */
	uint32_t compress_type; /* 压缩说明:0~不压缩, 1~RLE8-使用8位RLE压缩方式, 2~RLE4-使用4位RLE压缩方式, 3~Bitfields-位域存放方式. */
	uint32_t bmp_bytesz; /* 位图数据大小. 用字节数表示的位图数据的大小。该数必须是4的倍数。*/
	uint32_t hres; /* 水平分辨率. 用像素/米表示的水平分辨率。*/
	uint32_t vres; /* 垂直分辨率。用像素/米表示的垂直分辨率。*/
	uint32_t ncolors; /* 颜色数。位图使用的颜色数。*/
	uint32_t nimpcolors; /* 重要颜色。指定重要的颜色数。当该域的等于颜色数时(或者等于0)，表示所有颜色都一样重要。*/
} bmp_dib_v3_header_t;

typedef struct _bmpfile
{
	bmp_header_t header; //文件信息头
	bmp_dib_v3_header_t dib;
	rgb_pixel_t **pixels;
	rgb_pixel_t *colors;
} bmpfile_t;

//typedef struct _bmpfile bmpfile_t;

bmpfile_t* bmp_create(uint32_t width, uint32_t height, uint32_t depth);
void bmp_destroy(bmpfile_t *bmp);
bmp_header_t bmp_get_header(bmpfile_t *bmp);
bmp_dib_v3_header_t bmp_get_dib(bmpfile_t *bmp);

uint32_t bmp_get_width(bmpfile_t *bmp);
uint32_t bmp_get_height(bmpfile_t *bmp);
uint32_t bmp_get_depth(bmpfile_t *bmp);

uint32_t bmp_get_dpi_x(bmpfile_t *bmp);
uint32_t bmp_get_dpi_y(bmpfile_t *bmp);
void bmp_set_dpi(bmpfile_t *bmp, uint32_t x, uint32_t y);

rgb_pixel_t* bmp_get_pixel(bmpfile_t *bmp, uint32_t x, uint32_t y);
bool bmp_set_pixel(bmpfile_t *bmp, uint32_t x, uint32_t y, rgb_pixel_t pixel);
bool bmp_save(bmpfile_t *bmp, const char *filename);

BMP_END_DECLS
#endif /* __bmpfile_h__ */
