o = pi / 12        # Rhombus opening angle
a = 2 * o          # Rhombus acute angle
s = 2              # Rhombus side
d = 2 * cos(o) * s # Rhombus diagonal that bisects a
l = 4 * s          # Coordinate limit

rhombus = function(x, y, direction) {
  vertex2x = x + cos(direction + o) * s
  vertex2y = y + sin(direction + o) * s

  vertex4x = x + cos(direction - o) * s
  vertex4y = y + sin(direction - o) * s

  vertex3x = x + cos(direction) * d
  vertex3y = y + sin(direction) * d

  xs = c(x, vertex2x, vertex3x, vertex4x)
  ys = c(y, vertex2y, vertex3y, vertex4y)

  polygon(xs, ys, border="white", col="white")
  return(c(vertex2x, vertex2y, vertex4x, vertex4y))
}

par(bg="black", mar=rep(0, 4))
plot(0, 0, ann=F, axes=F, type="n", xlim=c(-l, l), ylim=c(-l, l))

direction = a

for (bird in 1:6) {
  shoulders = rhombus(cos(direction - a) * d, sin(direction - a) * d, direction)
  rhombus(shoulders[1], shoulders[2], direction + 2 * pi / 3)
  rhombus(shoulders[3], shoulders[4], direction - 2 * pi / 3)

  direction = direction + pi / 3
}
