/*
 *
 */

#include <math.h>
#include <stdio.h>
#include "libosm.h"

coordinates coord2xy(double lat, double lon, int z) {
    coordinates result;
    result.x = numTiles(z) * TILESIZE * (lon + 180) / 360;
    result.y = numTiles(z) * TILESIZE * (1 - log(tan(radians(lat)) + sec(radians(lat))) / M_PI) / 2;
    return(result);
}

coordinates latlon2relativeXY(double lat, double lon) {
    coordinates result;
    result.x = (lon + 180) / 360;
    result.y = (1 - log(tan(radians(lat)) + sec(radians(lat))) / M_PI) / 2;
    
    return(result);
}


coordinates latlon2xy(double lat, double lon, int z) {
    coordinates result;
    result.x = numTiles(z) * (lon + 180) / 360;
    result.y = numTiles(z) * (1 - log(tan(radians(lat)) + sec(radians(lat))) / M_PI) / 2;
    
    return(result);
}

coordinates latEdges(int y, int z) {
    coordinates result;
    
    float unit = 1 / numTiles(z);
    result.x = mercatorToLat(M_PI * (1 - 2 * (y * unit)));
    result.y = mercatorToLat(M_PI * (1 - 2 * (y * unit + unit)));
    
    return(result);
}

coordinates lonEdges(int x, int z) {
    coordinates result;
    
    float unit = 360 / numTiles(z);
    result.x = -180 + (x * unit);
    result.y = -180 + (x * unit) + unit;
    
    return(result);
}

edges tile2edges(int x, int y, int z) {
    edges result;
    coordinates ret;
    
    ret = latEdges(y,z);
    result.N = ret.x;
    result.S = ret.y;
    
    ret = lonEdges(x,z);
    result.W = ret.x;
    result.E = ret.y;
    
    return(result);
}

/*
 * vim: expandtab shiftwidth=4:
 */