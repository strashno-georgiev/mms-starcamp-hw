#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#define max(a, b) (a>b?a:b)
#define LINE_LEN 32
typedef struct Pixel_Data {
	int red;
	int green;
	int blue;
} Pixel_Data;

typedef struct PPM_Image_Buffer {
	Pixel_Data* data;
	int rown;
	int coln;
} PPM_Image_Buffer;

int read_ppm_color_bitmap(char* filename, PPM_Image_Buffer* buf) {
	FILE* file = fopen(filename, "a+");
	int width, height, i;
	int r, g, b;
	char line[10];
	fgets(line, 10-1, file);
	fscanf(file, "%d %d", &width, &height);
	//printf("Getting width and height\n");

	//printf("Width = %d, Height = %d\n", width, height);
	fscanf(file, "%d", &i);
	
	buf->rown = height;
	buf->coln = width;
	buf->data = malloc(sizeof(Pixel_Data) * width * height);
	
	i=0;
	while(i < width * height) {

		fscanf(file, "%d %d %d", &r, &g, &b);
		
		buf->data[i].red = r;
		buf->data[i].green = g;
		buf->data[i].blue = b;
		
		//printf("uno %d (%d, %d, %d)\n", i, r, g, b);
		i++;
	}
	fclose(file);
	return 0;
}

int write_ppm_color_bitmap(char* filename, PPM_Image_Buffer* buf) {
	FILE* file = fopen(filename, "w");
	fprintf(file, "P3\n");
	fprintf(file, "%d %d\n", buf->coln, buf->rown);
	fprintf(file, "255\n");
	int i=0;
	while(i < (buf->coln * buf->rown)) {
		fprintf(file, "%d %d %d\n", buf->data[i].red, buf->data[i].green, buf->data[i].blue);
		i++;
	}
	fclose(file);
	return 0;
}

void filter_color_component(PPM_Image_Buffer* image, unsigned int rgb_mask) {
	char r=0, g=0, b=0;
	r = 1 & rgb_mask;
	g = 2 & rgb_mask;
	b = 4 & rgb_mask;
	for(int i=0; i < image->rown * image->coln; i++) {
		if(!r) {
			image->data[i].red = 0;
		}
		if(!b) {
			image->data[i].blue = 0;
		}
		if(!g) {
			image->data[i].green = 0;
		}
	}
}

void convert_to_grayscale(PPM_Image_Buffer* image) {
	int max;
	for(int i=0; i < image->rown * image->coln; i++) {
		max = max(image->data[i].blue, max(image->data[i].green, image->data[i].red));
		image->data[i].red = max;
		image->data[i].green = max;
		image->data[i].blue	= max;
	}
}

int strhas(char* str, char c) {
	for(int i=0; str[i] != '\0'; i++) {
		if(str[i] == c) {
			return 1;
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
	int r, mask;
	char c, m;
	if(argc < 4) {
		fprintf(stderr, "Usage: %s <input-image> <output-image> [-f <mask>]/[-g]\n", argv[0]);
		return -1;
	}
	
	PPM_Image_Buffer image;
	r = read_ppm_color_bitmap(argv[1], &image);
	if(r < 0) { 
		return -1;
	}
	
	while((c = getopt(argc, argv, "gf:")) != -1) {
		switch(c) {
			case 'g':
				m = 'g';
				break;
			case 'f':
				printf("-f: %s\n", optarg);
				mask = (strhas(optarg, 'r') ? 1 : 0) | (strhas(optarg, 'g') ? 2 : 0) | (strhas(optarg, 'b') ? 4 : 0);
				printf("mask: %d\n", mask);
				m = 'f';
				break;
			default:
				fprintf(stderr, "Usage: %s <input-image> <output-image> [-f <mask>]/[-g]\n", argv[0]);
		}
	}
	
	for(int i=0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	
	if(m == 'f') {
		filter_color_component(&image, mask);
	}
	else if(m == 'g') {
		convert_to_grayscale(&image);
	}
	r = write_ppm_color_bitmap(argv[argc-1], &image);
	if(r < 0) {
		return -1;
	}
	free(image.data);
	return 0;
}
