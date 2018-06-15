//csc 473 simple reflect - sphere reflective

camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<0, 100, 50> color rgb <1.5, 1.5, 1.5>}

sphere { <-2, 0, 4>, 2
  pigment { color rgb <0.38, 0.69, 0.40>}
  finish {ambient 0.4 diffuse 0.8 reflection 0.5}
}

sphere { <1, -1.5, 0>, 2
  pigment { color rgb <1.0, 0.92, 0.51>}
  finish {ambient 0.4 diffuse 0.8 reflection 0.8}
}

sphere { <1, 3.5, 0>, 2
  pigment { color rgb <0.0, 0.32, 0.81>}
  finish {ambient 0.4 diffuse 0.8 reflection 0.8}
}

sphere { <5, 0, -4>, 2
  pigment { color rgb <0.78, 0.39, 0.70>}
  finish {ambient 0.4 diffuse 0.8 reflection 0.5}
}


// Floor
plane {<0, 1, 0>, -4
  pigment {color rgb <0.6, 0.6, 0.6>}
  finish {ambient 0.4 diffuse 1.0}
}

// Background
plane {<0, 0, 1>, -100
  pigment {color rgb <0.8, 0.8, 0.8>}
  finish {ambient 0.2 diffuse 0.4}
}
