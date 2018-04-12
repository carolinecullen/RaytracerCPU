// cs473, gi
camera {
  location  <-2, 0, 14>
  up        <0,  1,  0>
  right     <1.333333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<5, 10, 5> color rgb <1.0, 1.0, 1.0>}

// floor
plane {<0, 1, 0>, -3
  pigment {color rgb <0.8, 0.2, 0.2>}
  finish {ambient 0.1 diffuse 0.8}
  translate <0, -1, 0>
}

// back wall
plane {<0, 0, 1>, -5
  pigment {color rgb <0.2, 0.8, 0.2>}
  finish {ambient 0.1 diffuse 0.8}
  rotate <0, 30, 0>
}


sphere { <2, 1, -3.74305>, 2
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.8}
  translate <-4, -3, 2>
}

sphere { <6, 1, -3.74305>, 2
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.8}
  translate <-4, -3, 2>
}

sphere { <4, 1, -0.25695>, 2
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.8}
  translate <-4, -3, 2>
}

sphere { <4, 4, -2>, 2
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.8}
  translate <-4, -3, 2>
}
