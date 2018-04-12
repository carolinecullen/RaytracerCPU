// csc 473 basic box
camera {
location  <0, 0, 14>
up        <0,  1,  0>
right     <1.5, 0,  0>
look_at   <0, 0, 0>}

light_source {<10, 10, 3> color rgb <1.0, 1.0, 1.0>}

// floor
plane {<0, 1, 0>, -5
pigment {color rgb <0.2, 0.2, 0.8>}
finish {ambient 0.4 diffuse 0.2 reflection 0.2}
}

// left wall
plane {<.707, 0, .707>, -8
pigment {color rgb <0.8, 0.2, 0.2>}
finish {ambient 0.4 diffuse 0.2 }
}

// back wall on the right
plane {<.34, 0, .94>, -30
pigment {color rgb <0.0, 0.2, 0.2>}
finish {ambient 0.4 diffuse 0.8 }
}

box { <-2, -5, -5>, <2, 5, 5>
  pigment { color rgb <1.0, 0.2, 1.0>}
  finish {ambient 0.2 diffuse 0.8}
  rotate <0, -45, 0>
  translate <3, 0, -5>
}
