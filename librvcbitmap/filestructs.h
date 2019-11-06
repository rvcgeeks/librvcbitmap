/* ___________________________________________________________
 * ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
 * CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
 *
 * #RVCGEEKS bitmap library -- include header file
 * some functions for pixel modification,image creation,etc...
 * 
*/

typedef unsigned       char uchar_t;
typedef unsigned       int  uint32_t;
typedef unsigned short int  uint16_t;
typedef signed         int  int32_t;
typedef signed   short int  int16_t;
const int MIN_RGB=0;
const int MAX_RGB=255;
const int BMP_MAGIC_ID=2;
struct bmpfile_magic{
    uchar_t  magic[BMP_MAGIC_ID];
};
struct bmpfile_header{          //here is all the metadata of a bitmap image file
    uint32_t file_size;
    uint16_t creator1;
    uint16_t creator2;
    uint32_t bmp_offset;
};
struct bmpfile_dib_info{
    uint32_t header_size;
    int32_t  width;
    int32_t  height;
    uint16_t num_planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t bmp_byte_size;
    int32_t  hres;
    int32_t  vres;
    uint32_t num_colors;
    uint32_t num_important_colors;
};
