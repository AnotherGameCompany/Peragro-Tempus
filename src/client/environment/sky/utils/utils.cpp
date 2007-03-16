


#include <math.h> // fmod
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "utils.h"


namespace StelUtils {

  void sphe_to_rect(double lng, double lat, Vec3d& v)
  {
    const double cosLat = cos(lat);
    v.Set(cos(lng) * cosLat, sin(lng) * cosLat, sin(lat));
  }

  void sphe_to_rect(float lng, float lat, Vec3d& v)
  {
    const double cosLat = cos(lat);
    v.Set(cos(lng) * cosLat, sin(lng) * cosLat, sin(lat));
  }

  void rect_to_sphe(double *lng, double *lat, const Vec3d& v)
  {
    double r = v.length();
    *lat = asin(v[2]/r);
    *lng = atan2(v[1],v[0]);
  }

}