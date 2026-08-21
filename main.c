#include "haversine.h"
#include <complex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  /*
    Read file
  */
  FILE *input = fopen("input.txt", "r");
  if (input == NULL) {
    printf("Abort: failed to read file.\n");
    return 1;
  }
  const int ROWS_LIMIT = 10;
  point_t places[ROWS_LIMIT];
  int i = 0;
  while (i < ROWS_LIMIT && fscanf(input, " %s %lf %lf", places[i].name,
                                  &places[i].ltt, &places[i].lng) == 3) {
    i++;
  }
  fclose(input);

  /*
    Show list of places
  */
  printf("Places:\n");
  for (int j = 0; j < i; j++) {
    printf("%d\t%s\t%.6lf\t%.6lf\n", j, places[j].name, places[j].ltt,
           places[j].lng);
  }

  /*
    Ask for place 1
  */
  int n1;
  printf("Choose place 1: ");
  scanf("%d", &n1);

  bool abort = false;

  point_t p1 = point_init(places[n1].ltt, places[n1].lng);
  switch (p1.status) {
  case POINT_OK:
    abort = false;
    break;

  case LTT_INVALID:
    abort = true;
    printf("Abort: LTT %.6lf is invalid\n", places[n1].ltt);
    break;

  case LNG_INVALID:
    abort = true;
    printf("Abort: LNG %.6lf is invalid\n", places[n1].lng);
    break;

  default:
    abort = true;
    printf("Abort: unexpected point init error\n");
    break;
  }

  if (abort) {
    return 1;
  }

  /*
    Ask for place 2
  */
  int n2;
  printf("Choose place 2: ");
  scanf(" %d", &n2);

  point_t p2 = point_init(places[n2].ltt, places[n2].lng);
  switch (p2.status) {
  case POINT_OK:
    abort = false;
    break;

  case LTT_INVALID:
    abort = true;
    printf("Abort: LTT %.6lf is invalid\n", places[n2].ltt);
    break;

  case LNG_INVALID:
    abort = true;
    printf("Abort: LNG %.6lf is invalid\n", places[n2].lng);
    break;

  default:
    abort = true;
    printf("Abort: unexpected point init error\n");
    break;
  }

  if (abort) {
    return 1;
  }

  /*
    Calculate distance
  */
  distance_t d = distance(&p1, &p2);

  switch (d.status) {
  case DIST_OK:
    break;

  case OVERFLOW_MAX:
    printf("Error: distance overflow, forced to max\n");
    break;

  case OVERFLOW_MIN:
    printf("Error: distance overflow, forced to min\n");
    break;

  default:
    printf("Error: unexpected distance error\n");
    break;
  }

  printf("Distance is %.2F km\n", d.distance);

  return 0;
}
