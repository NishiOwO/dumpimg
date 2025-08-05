#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <ctype.h>

int main(int argc, char** argv){
	int x, y, w, h, n;
	unsigned char* d;
	char* prefix = argc == 3 ? argv[2] : "image";
	if(argc != 2 && argc != 3){
		fprintf(stderr, "bad usage\n");
		return 1;
	}
	d = stbi_load(argv[1], &w, &h, &n, 4);
	if(d == NULL){
		fprintf(stderr, "bad image\n");
		return 1;
	}
	printf("#ifdef EMBED_");
	for(n = 0; prefix[n] != 0; n++) printf("%c", toupper(prefix[n]));
	printf("\n");
	printf("unsigned char %s_data[%d] = {\n", prefix, w * h * 4);
	for(y = 0; y < h; y++){
		printf("\t");
		for(x = 0; x < w; x++){
			unsigned char* px = &d[(y * w + x) * 4];
			printf("%d, %d, %d, %d%s", px[0], px[1], px[2], px[3], (x == (w - 1) && (y == (h - 1))) ? "" : ", ");
		}
		printf("\n");
	}
	printf("};\n");
	printf("int %s_width = %d;\n", prefix, w);
	printf("int %s_height = %d;\n", prefix, h);
	printf("#else\n");
	printf("extern unsigned char %s_data[%d];\n", prefix, w * h * 4);
	printf("extern int %s_width;\n", prefix);
	printf("extern int %s_height;\n", prefix);
	printf("#endif\n");
	stbi_image_free(d);
}
