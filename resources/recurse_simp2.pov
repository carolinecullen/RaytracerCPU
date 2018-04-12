// csc 473 reflection and refraction
camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.5, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<-5, 3, 0> color rgb <1.0, 1.0, 1.0>}

// floor
plane {<0, 1, 0>, -5
pigment {color rgb <0.2, 0.2, 0.8>}
finish {ambient 0.4 diffuse 0.2 reflection 0.2}
}

// left wall
plane {<.707, 0, .707>, -8
pigment {color rgb <0.8, 0.2, 0.2>}
finish {ambient 0.4 diffuse 0.2 reflection 0.2}}

// back wall
plane {<-.707, 0, -.707>, 30
pigment {color rgb <0.8, 0.4, 0.2>}
finish {ambient 0.4 diffuse 0.2 reflection 0.2}}

// back wall on the right
plane {<-.34, 0, -.94>, 30
pigment {color rgb <0.0, 0.2, 0.2>}
finish {ambient 0.4 diffuse 0.8 reflection 0.2}}

sphere { <5.5, -3, -1>, 2
pigment {color rgbf <1.0, 1.0, 1.0, 0.8>}
finish {ambient 0.2 diffuse 0.8 reflection 0.1 refraction 1.0 ior 1.333}}

