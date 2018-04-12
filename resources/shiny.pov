// csc473, assignment 4 file

camera {
  location  <0, 1, 18>
  up        <0,  0.9985,  -0.0555>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<0, 100, 50> color rgb <1.5, 1.5, 1.5>}

// White
sphere { <0, 0, 0>, 2.0
  pigment { color rgb <1.0, 1.0, 1.0> }
  finish {roughness 0.02 ior 1.6 reflection 1.0}
}

// Green
sphere { <-2.5, -3, 4>, 1.0
  pigment { color rgb <0.4, 1.0, 0.4> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}

// Red
sphere { <2.5, -3, 4>, 1.0
  pigment { color rgb <1.0, 0.3, 0.3> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}

// Purple
sphere { <5, -2, 0>, 0.8
  pigment { color rgb <0.8, 0.4, 1.0> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}

// Yellow
sphere { <-5, -2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 0.4> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}

// Blue
sphere { <-6.5, 0, 4>, 1.0
  pigment { color rgb <0.4, 0.6, 1.0> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}

// Orange
sphere { <6.5, 0, 4>, 1.0
  pigment { color rgb <1.0, 0.65, 0.0> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}


sphere { <2.5, -3, 14>, 1.0
  pigment { color rgb <1.0, 0.3, 0.3> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}
sphere { <-2.5, -3, 14>, 1.0
  pigment { color rgb <0.4, 1.0, 0.4> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}
sphere { <5, -2, 12>, 0.8
  pigment { color rgb <0.8, 0.4, 1.0> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}
sphere { <-5, -2, 12>, 0.8
  pigment { color rgb <1.0, 1.0, 0.4> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}
sphere { <-6.5, 0, 12>, 1.0
  pigment { color rgb <0.4, 0.6, 1.0> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}
sphere { <6.5, 0, 12>, 1.0
  pigment { color rgb <1.0, 0.5, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
}

// Floor
plane {<0, 1, 0>, -4
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
}

// Background
plane {<0, 0, 1>, -100
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4}
}
