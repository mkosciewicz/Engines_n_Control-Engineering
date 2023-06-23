//
// Created by mkoscie on 6/12/23.
//
#include "string.h"
#include "stdint.h"
#include "stdio.h"

#define MAX_BUFFER_SIZE 256

char test[MAX_BUFFER_SIZE]={"$GPGGA,1305q5.00,5213.30026,N,02100.36327,E,1,09,1.09,120.9,M,34.3,M,,*52"};

void parseGGA() {
    char* ggaStart = strstr(test, "$GPGGA");

    if (ggaStart != NULL) {
        char term[10], latitude[15], longitude[15];
        char NS, EW;
        float altitude;
        int ignored;

        sscanf(ggaStart, "$GPGGA,%9[^,],%14[^,],%c,%14[^,],%c,%d,%d,%*f,%f,M,%f",
        term, latitude, &NS, longitude, &EW, &ignored, &ignored, &altitude, &ignored);

        printf("Latitude: %s %c\n", latitude, NS);
        printf("Longitude: %s %c\n", longitude, EW);
        printf("Altitude: %.2f M\n", altitude);
    }
}

int main(void) {
    parseGGA();
    return 0;
}
