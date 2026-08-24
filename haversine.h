#include <stdbool.h>

typedef struct {
  double ltt;
  double lng;
  char name[64];
} point_t;

typedef enum {
  DIST_OK,
  OVERFLOW_MIN,
  OVERFLOW_MAX,
  P1_LTT_INVALID,
  P1_LNG_INVALID,
  P2_LTT_INVALID,
  P2_LNG_INVALID
} dstatus_t;

typedef struct {
  double distance;
  dstatus_t status;
} distance_t;

bool ltt_is_valid(const double);
bool lng_is_valid(const double);

distance_t distance(const point_t, const point_t);
double to_rad(double degrees);
