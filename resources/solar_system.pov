// Cameron Taylor (2017)
// custom .pov file for p4

// camera
camera {
  location <0, 1, 25>
  up <0, 1, 0>
  right < 1.33333, 0, 0>
  look_at <0, 0, 0>
}

// general lighting
// light_source {<-70, 100, 70> color rgb <1.5, 1.5, 1.5>}

// Star
sphere { <0, 1, 26>, 0.1
  pigment { color rgb <10, 10, 10> }
  finish { ambient 1.0 diffuse 1.0 specular 1.0 roughness 0.02 reflection 0 }
}
light_source {<0, 1, 25> color rgb <1.5, 1.5, 1.5>}

// Sun
sphere { <40, 0, 0>, 30
  pigment { color rgbf <6.0, 0.6, 0.2, 0.1>}
  finish {ambient 0.2 diffuse 0.8 specular 0.3 roughness 0.4 ior 1.8 reflection 0.05}
  translate <0, 0, 0>
}
light_source {<9, 2, 2> color rgb <1.5, 1.5, 1.5>}

// Mercury
sphere { <9, 0, 0>, 0.3
  pigment { color rgbf <0.6, 0.6, 0.6, 0.1>}
  finish {ambient 0.2 diffuse 0.5 specular 0.7 roughness 0.02 ior 1.8 reflection 0.3}
  translate <0, 0, 0>
}

// Venus
sphere { <7, 0, 0>, 0.7
  pigment { color rgbf <1, 0.6, 0.4, 0.1>}
  finish {ambient 0.2 diffuse 0.8 specular 0.3 roughness 0.4 ior 1.8 reflection 0.05}
  translate <0, 0, 0>
}

// Earth
sphere { <4.5, 0, 0>, 0.7
  pigment { color rgbf <0.2, 0.6, 0.4, 0.1>}
  finish {ambient 0.2 diffuse 0.8 specular 0.3 roughness 0.4 ior 1.8 reflection 0.05}
  translate <0, 0, 0>
}

// Mars
sphere { <2.2, 0, 0>, 0.41
  pigment { color rgbf <1.0, 0.4, 0.2, 0.1>}
  finish {ambient 0.2 diffuse 0.8 specular 0.3 roughness 0.4 ior 1.8 reflection 0.05}
  translate <0, 0, 0>
}

// Jupiter
sphere { <-1.2, 0, 0>, 2
  pigment { color rgbf <1.0, 0.2, 0.2, 0.5>}
  finish {ambient 0.4 diffuse 0.4 specular 0.3 roughness 0.4 ior 1.3 reflection 0.05}
  translate <0, 0, 0>
}
sphere { <0, 0, 0>, 1.8
  pigment { color rgb <0.8, 0.8, 0>}
  finish {ambient 0.3 diffuse 0.7 specular 0.1 roughness 0.4 }
  scale <1, 0.1, 1>
  translate <-1.2, 0, 0>
}
sphere { <0, 0, 0>, 1.3
  pigment { color rgb <0.8, 0.8, 0.4>}
  finish {ambient 0.3 diffuse 0.7 specular 0.1 roughness 0.4 }
  scale <1, 0.1, 1>
  translate <-1.2, 0.7, 0>
}
sphere { <0, 0, 0>, 1.3
  pigment { color rgb <0.8, 0.8, 0.4>}
  finish {ambient 0.3 diffuse 0.7 specular 0.1 roughness 0.4 }
  scale <1, 0.1, 1>
  translate <-1.2, -0.7, 0>
}
sphere { <0, 0, 0>, 0.5
  pigment { color rgb <0.8, 0.8, 0.4>}
  finish {ambient 0.3 diffuse 0.7 specular 0.1 roughness 0.4 }
  scale <1, 0.2, 1>
  translate <-1.2, 1.6, 0>
}
sphere { <0, 0, 0>, 0.5
  pigment { color rgb <0.8, 0.8, 0.4>}
  finish {ambient 0.3 diffuse 0.7 specular 0.1 roughness 0.4 }
  scale <1, 0.2, 1>
  translate <-1.2, -1.6, 0>
}
sphere { <0, 0, 0>, 0.5
  pigment { color rgbf <1, 1, 0.6, 0.5>}
  finish {ambient 0.5 diffuse 0.8 specular 0.1 roughness 0.4 ior 1.1 }
  scale <1, 0.5, 0.5>
  translate <-0.9, -0.7, 1.5>
}

// Saturn
sphere { <-5.8, 0, 0>, 1.6
  pigment { color rgb <1, 0.9, 0.4>}
  finish {ambient 0.2 diffuse 0.8 specular 0.7 roughness 0.02 reflection 0}
  translate <0, 0, 0>
}
sphere { <0, 0, 0>, 2.7
  pigment { color rgbf <1, 1, 1, 0.8> }
  finish { ambient 0.5 diffuse 0.5 specular 0.2 roughness 0.2 reflection 0 ior 1.0 }
  scale <1, 0.05, 1>
  rotate <0, -25, -30>
  translate <-5.8, 0, 0>
}

// Uranus
sphere { <-10.2, 0, 0>, 1
  pigment { color rgb <0.2, 0.7, 0.9>}
  finish {ambient 0.2 diffuse 0.8 specular 0.7 roughness 0.02 reflection 0.2}
  translate <0, 0, 0>
}

// Neptune
sphere { <-13, 0, 0>, 0.5
  pigment { color rgb <0.1, 0.6, 1.0>}
  finish {ambient 0.2 diffuse 0.8 specular 0.7 roughness 0.02 reflection 0.2}
  translate <0, 0, 0>
}

// Pluto
sphere { <-15.5, 0, 0>, 0.1
  pigment { color rgb <0.7, 0.7, 0.7>}
  finish {ambient 0.2 diffuse 0.8 specular 0.7 roughness 0.02 reflection 0.2}
  translate <0, 0, 0>
}
