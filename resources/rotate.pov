// csc473, assignment 4  - transforms

camera {
  location  <0, 1, 7>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 1, 0>
}


light_source {<-10, 10, 10> color rgb <1.5, 1.5, 1.5>}

// red
triangle { <-2, 3, 0>, <-2, 0, 0>, <1, 1.5, 0>
  pigment { color rgb <0.8, 0.2, 0.2>}
  finish { ambient 0.2 diffuse 0.4 }
  rotate <0, 0, 90>
}

// green
triangle { <1, 1.5, 0>, <1, -1.5, 0>, <4, 0, 0>
  pigment { color rgb <0.2, 0.8, 0.2>}
  finish { ambient 0.2 diffuse 0.4 }
  rotate <0, 0, 90>
}

// blue
triangle { <-2, 0, 0>, <-2, -3, 0>, <1, -1.5, 0>
  pigment { color rgb <0.2, 0.4, 0.8>}
  finish { ambient 0.2 diffuse 0.4 }
  rotate <0, 0, 90>
}

// cyan
triangle { <-2, 3, -6>, <-2, 0, -6>, <1, 1.5, -6>
  pigment { color rgb <0.2, 0.8, 0.8>}
  finish { ambient 0.2 diffuse 0.4 }
  rotate <0, 0, -90>
}

// magenta
triangle { <1, 1.5, -6>, <1, -1.5, -6>, <4, 0, -6>
  pigment { color rgb <0.8, 0.2, 0.8>}
  finish { ambient 0.2 diffuse 0.4 }
  rotate <0, 0, -90>
}

// yellow
triangle { <-2, 0, -6>, <-2, -3, -6>, <1, -1.5, -6>
  pigment { color rgb <0.8, 0.8, 0.2>}
  finish { ambient 0.2 diffuse 0.4 }
  rotate <0, 0, -90>
}

plane {<0, 1, 0>, -4
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish { ambient 0.4 diffuse 0.8 reflection 0.6 }
}
