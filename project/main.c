#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
	printf("Getting width and height\n");

	printf("Width = %d, Height = %d\n", width, height);
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
		
		printf("uno %d (%d, %d, %d)\n", i, r, g, b);
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

int main(int argc, char* argv[]) {
	int r;
	char c;
	while(c = getopt(argc, argv, ))
	PPM_Image_Buffer image;
	r = read_ppm_color_bitmap("dainov.ppm", &image);
	//filter_color_component(&image, 1);
	convert_to_grayscale(&image);
	write_ppm_color_bitmap("dainov1.ppm", &image);
	free(image.data);
	return r;
}
