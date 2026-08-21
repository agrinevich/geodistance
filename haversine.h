#include <stdbool.h>

typedef enum { POINT_OK, LTT_INVALID, LNG_INVALID } pstatus_t;

typedef struct {
  double ltt;
  double lng;
  char name[64];
  pstatus_t status;
} point_t;

typedef enum { DIST_OK, OVERFLOW_MIN, OVERFLOW_MAX } dstatus_t;

typedef struct {
  double distance;
  dstatus_t status;
} distance_t;

bool ltt_is_valid(const double);
bool lng_is_valid(const double);
point_t point_init(double ltt, double lng);

distance_t distance(const point_t *p1, const point_t *p2);
double to_rad(double degrees);
