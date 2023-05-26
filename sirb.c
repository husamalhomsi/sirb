#include <math.h>
#include <stdio.h>

// Full angle in radians
#define TAU 6.28318530717958647692

#define FILENAME "sirb.svg"

static FILE *file;

static double a; // Rhombus acute angle
static double o; // Rhombus opening angle
static double s; // Rhombus side
static double d; // Rhombus diagonal that bisects a
static double l; // Coordinate limit

static double shoulder1x, shoulder1y, shoulder2x, shoulder2y;

static void rhombus(double x, double y, double direction, _Bool set_shoulders) {
  double vertex2x = x + cos(direction + o) * s;
  double vertex2y = y + sin(direction + o) * s;

  double vertex4x = x + cos(direction - o) * s;
  double vertex4y = y + sin(direction - o) * s;

  double vertex3x = x + cos(direction) * d;
  double vertex3y = y + sin(direction) * d;

  fprintf(file,
    "  <polygon points='%+f,%+f %+f,%+f %+f,%+f %+f,%+f'/>\n",
    x, -y, vertex2x, -vertex2y, vertex3x, -vertex3y, vertex4x, -vertex4y);

  if (set_shoulders) {
    shoulder1x = vertex2x;
    shoulder1y = vertex2y;
    shoulder2x = vertex4x;
    shoulder2y = vertex4y;
  }
}

int main(void) {
  a = TAU / 12;
  o = a / 2;
  s = 1;
  d = 2 * cos(o) * s;
  l = 4 * s;

  file = fopen(FILENAME, "w");

  if (!file)
    return 1;

  fprintf(file,
    "<?xml version='1.0'?>\n"
    "<svg xmlns='http://www.w3.org/2000/svg' "
    "viewBox='%g %g %g %g' width='256px' height='256px' fill='white'>\n"
    "  <rect x='%g' y='%g' width='100%%' height='100%%' fill='black'/>\n",
    -l, -l, 2 * l, 2 * l, -l, -l);

  int birds = 6;
  double angle = 0;
  double direction = angle + a;
  double rotation = TAU / birds;
  double wing_offset = TAU / 3;

  while (birds--) {
    rhombus(cos(angle) * d, sin(angle) * d, direction, 1);
    rhombus(shoulder1x, shoulder1y, direction + wing_offset, 0);
    rhombus(shoulder2x, shoulder2y, direction - wing_offset, 0);

    angle += rotation;
    direction += rotation;
  }

  fputs("</svg>\n", file);
  fclose(file);
  printf("Wrote %s\n", FILENAME);
}
