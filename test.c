#include "haversine.h"
#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>

bool doubles_equal(double a, double b, double epsilon) {
  return fabs(a - b) < epsilon;
}

int main() {
  point_t place1 = {.ltt = 51.2608836, .lng = 3.0573051, .name = "Bruges"};
  point_t place2 = {.ltt = 50.4015679, .lng = 30.202377, .name = "Kyiv"};

  double d_expected = 1897.95;
  distance_t d = distance(place1, place2);
  assert(d.status == DIST_OK);
  assert(doubles_equal(d.distance, d_expected, 0.5));

  place1.ltt = 91.2608836;
  d = distance(place1, place2);
  assert(d.status == P1_LTT_INVALID);

  place1.ltt = 51.2608836;
  place1.lng = 183.0573051;
  d = distance(place1, place2);
  assert(d.status == P1_LNG_INVALID);

  place2.ltt = 150.4015679;
  place1.lng = 3.0573051;
  d = distance(place1, place2);
  assert(d.status == P2_LTT_INVALID);

  place2.ltt = 50.4015679;
  place2.lng = 230.202377;
  d = distance(place1, place2);
  assert(d.status == P2_LNG_INVALID);

  return 0;
}
