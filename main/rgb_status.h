typedef unsigned char byte;
typedef unsigned int  word;

#define RGB_RED       1
#define RGB_GREEN     2
#define RGB_BLUE      4

int rgb_status_init(int num_colors, byte *color_defs);

int rgb_status_set(int n_status, byte enable);
