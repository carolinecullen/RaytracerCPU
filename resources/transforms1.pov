// csc473, assignment 4 file

camera {
  location  <0, 1, 18>
  up        <0,  0.9985,  -0.0555>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<0, 100, 50> color rgb <1.5, 1.5, 1.5>}

// Green
sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.4, 1.0, 0.4> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.5, 3, 0.5>
  rotate <0, 0, -45>
  translate <-2.5, -1, 4>
}

// Red
sphere { <0, 0, 0>, 1.0
  pigment { color rgb <1.0, 0.3, 0.3> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.5, 3, 0.5>
  rotate <0, 0, 45>
  translate <2.5, -1, 4>
}

// Purple
sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.8, 0.4, 1.0> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.5, 3, 0.5>
  rotate <45, 0, 0>
  translate <5, -2, 0>
}

// Yellow
sphere { <0, 0, 0>, 1.0
  pigment { color rgb <1.0, 1.0, 0.4> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.5, 3, 0.5>
  rotate <45, 0, 0>
  translate <-5, -2, 0>
}

// Blue
sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.4, 0.6, 1.0> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
  scale <4.5, 4.5, 0.6>
  translate <-6.5, 2, -4>
}

// Orange
sphere { <0, 0, 0>, 1.0
  pigment { color rgb <1.0, 0.65, 0.0> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
  scale <4.5, 4.5, 0.6>
  translate <6.5, 2, -4>
}

// Triangle
triangle {
  <14, 11, 8>,
  <0, -4, 10>,
  <-14, 11, 8>
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
  rotate <0, 180, 0>
}

// Floor
plane { <0, 0, 1>, -4
  pigment {color rgb <0.7, 0.9, 0.8>}
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
  rotate <-90, 0, 0>
}

// Background
plane { <0, 0, 1>, -100
  pigment {color rgb <0.9, 0.7, 0.8>}
  finish {ambient 0.2 diffuse 0.4}
}

// Center
sphere { <0, -2, 0>, 1.0
  pigment { color rgb <1.0, 1.0, 1.0> }
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
}
