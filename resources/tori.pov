// csc473, assignment 4 file

camera {
  location  <0, 1, 18>
  up        <0,  0.9985,  -0.0555>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<0, 100, 50> color rgb <1.5, 1.5, 1.5>}

sphere { <-10, 0, 0>, 1.0
  pigment { color rgbf <1.0, 0.0, 1.0, 0.9> }
  finish {ambient 0.2 diffuse 0.4 reflection 0.2 ior 1.6}
}

sphere { <10, 0, 0>, 1.0
  pigment { color rgbf <1.0, 0.0, 1.0, 0.9> }
  finish {ambient 0.2 diffuse 0.4 reflection 0.2 ior 1.6}
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.7, 0.6, 0.1> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
  scale <4.5, 4.5, 0.6>
  translate <-6.5, 6, -12>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.7, 0.65, 0.0> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
  scale <4.5, 4.5, 0.6>
  translate <6.5, 6, -12>
}


sphere { <0, 0, 0>, 2.7
  pigment { color rgbf <1, 1, 1, 0.8> }
  finish { ambient 0.5 diffuse 0.5 specular 0.2 roughness 0.2 reflection 0 ior 1.0 }
  scale <1, 0.05, 1>
  rotate <0, -25, -30>
  translate <-5, 0, 0>
}

sphere { <0, 0, 0>, 2.7
  pigment { color rgbf <1, 1, 1, 0.8> }
  finish { ambient 0.5 diffuse 0.5 specular 0.2 roughness 0.2 reflection 0 ior 1.0 }
  scale <1, 0.05, 1>
  rotate <0, 25, 30>
  translate <5, 0, 0>
}

// Triangle
triangle {
  <0, -2, -5>,
  <5, 3, 5>,
  <-5, 3, 5>
  pigment {color rgb <1.0, 1.0, 0.4>}
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
  rotate <0, 180, 0>
}

// Floor
plane { <0, 0, 1>, -4
  pigment {color rgb <0.7, 0.5, 0.8>}
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
  rotate <-90, 0, 0>
}

// Background
plane { <0, 0, 1>, -100
  pigment {color rgb <0.9, 0.7, 0.8>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.7}
}
