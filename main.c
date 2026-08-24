#include "haversine.h"
#include <complex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  /*
    Read file
  */
  FILE *fh = fopen("input.txt", "r");
  if (fh == NULL) {
    printf("Abort: failed to read file.\n");
    return 1;
  }
  const int ROWS_LIMIT = 10;
  point_t places[ROWS_LIMIT];
  int i = 0;
  while (i < ROWS_LIMIT && fscanf(fh, " %s %lf %lf", places[i].name,
                                  &places[i].ltt, &places[i].lng) == 3) {
    i++;
  }
  fclose(fh);

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

  /*
    Ask for place 2
  */
  int n2;
  printf("Choose place 2: ");
  scanf(" %d", &n2);

  /*
    Calculate distance
  */
  distance_t d = distance(places[n1], places[n2]);

  bool abort = false;

  switch (d.status) {
  case DIST_OK:
    abort = false;
    break;

  case P1_LTT_INVALID:
    abort = true;
    printf("Abort: LTT1 %.6lf is invalid\n", places[n1].ltt);
    break;

  case P1_LNG_INVALID:
    abort = true;
    printf("Abort: LNG1 %.6lf is invalid\n", places[n1].lng);
    break;

  case P2_LTT_INVALID:
    abort = true;
    printf("Abort: LTT2 %.6lf is invalid\n", places[n2].ltt);
    break;

  case P2_LNG_INVALID:
    abort = true;
    printf("Abort: LNG2 %.6lf is invalid\n", places[n2].lng);
    break;

  case OVERFLOW_MAX:
    abort = false;
    printf("Error: distance overflow, forced to max\n");
    break;

  case OVERFLOW_MIN:
    abort = false;
    printf("Error: distance overflow, forced to min\n");
    break;

  default:
    abort = true;
    printf("Error: unexpected error\n");
    break;
  }

  if (abort) {
    return 1;
  }

  printf("Distance between %s and %s is %.2F km\n", places[n1].name,
         places[n2].name, d.distance);
  return 0;
}
