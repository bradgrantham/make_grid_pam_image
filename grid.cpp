#include <cstdio>
#include <cstdlib>
#include <cmath>

int main(int argc, char **argv)
{
    if(argc < 4) {
        fprintf(stderr, "usage: %s grid_squares image_size line_thickness # PAM on stdout\n", argv[0]);
        fprintf(stderr, "e.g. %s 32 512 4 | pamtopng > grid.png # outputs512x512 PAM with 32 grid \n\tsquares and 4-pixel wide lines, converting to PNG.\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int squares = atoi(argv[1]);
    int pixels = atoi(argv[2]);
    int thickness = atoi(argv[3]);
    
    int totallinepixels = thickness * (squares + 1);
    float squarepixels = (pixels - totallinepixels) / (float)squares;
    float lineandsquare = thickness + squarepixels;

    unsigned char line_color[4] = {0, 0, 0, 255};
    unsigned char square_color[4] = {255, 255, 255, 0};

    printf("P7\nWIDTH %d\nHEIGHT %d\nDEPTH 4\nMAXVAL 255\nTUPLTYPE RGB_ALPHA\nENDHDR\n", pixels, pixels);
    for(int j = 0; j < pixels; j++)
        for(int i = 0; i < pixels; i++) {
            bool line = (fmod(i, lineandsquare) < thickness) || (fmod(j, lineandsquare) < thickness);
            if(line)
                fwrite(line_color, 4, 1, stdout);
            else
                fwrite(square_color, 4, 1, stdout);
        }
}
