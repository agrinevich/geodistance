#include "haversine.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>

const double PI = 3.14159265358979323846;
const double EARTH_RADIUS_KM = 6371.0;
const double LTT_MIN = -90.0;
const double LTT_MAX = 90.0;
const double LNG_MIN = -180.0;
const double LNG_MAX = 180.0;
const double DIST_KM_MIN = 0.0;
const double DIST_KM_MAX = 20000.0;

bool ltt_is_valid(const double ltt) {
  if (ltt < LTT_MIN) {
    return false;
  }
  if (ltt > LTT_MAX) {
    return false;
  }

  return true;
}

bool lng_is_valid(const double lng) {
  if (lng < LNG_MIN) {
    return false;
  }
  if (lng > LNG_MAX) {
    return false;
  }

  return true;
}

/*

  Function: distance
    calculates distance between 2 geo points.
    https://rosettacode.org/wiki/Haversine_formula

*/

distance_t distance(const point_t p1, const point_t p2) {

  if (ltt_is_valid(p1.ltt) == false) {
    distance_t d = {.distance = 0, .status = P1_LTT_INVALID};
    return d;
  }

  if (lng_is_valid(p1.lng) == false) {
    distance_t d = {.distance = 0, .status = P1_LNG_INVALID};
    return d;
  }

  if (ltt_is_valid(p2.ltt) == false) {
    distance_t d = {.distance = 0, .status = P2_LTT_INVALID};
    return d;
  }

  if (lng_is_valid(p2.lng) == false) {
    distance_t d = {.distance = 0, .status = P2_LNG_INVALID};
    return d;
  }

  double ltt_1r = to_rad(p1.ltt);
  double ltt_2r = to_rad(p2.ltt);

  double dlng = p1.lng - p2.lng;
  double dlng_r = to_rad(dlng);

  double dz = sin(ltt_1r) - sin(ltt_2r);
  double dx = cos(dlng_r) * cos(ltt_1r) - cos(ltt_2r);
  double dy = sin(dlng_r) * cos(ltt_1r);

  double dist =
      asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * EARTH_RADIUS_KM;

  if (dist < DIST_KM_MIN) {
    distance_t d = {.distance = DIST_KM_MIN, .status = OVERFLOW_MIN};
    return d;
  }

  if (dist > DIST_KM_MAX) {
    distance_t d = {.distance = DIST_KM_MAX, .status = OVERFLOW_MAX};
    return d;
  }

  distance_t d = {.distance = dist, .status = DIST_OK};
  return d;
}

double to_rad(double degrees) {
  double radians = 0.0;
  radians = degrees * PI / 180;
  return radians;
}
