// csc 473 more interesting box

camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.5, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<10, 10, 3> color rgb <1.0, 1.0, 1.0>}


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


box {<-2, -3, -4.5>, <2, 6, 4.5>
  pigment { color rgbf <1.0, 1.0, 1.0, 0.6>}
  finish {ambient 0.2 diffuse 0.8 ior 1.33}
  rotate <0, -45, 0>
  translate <-7, 0, -5>
}

box {<-2, -3, -4.5>, <2, 6, 4.5>
  pigment { color rgbf <1.0, 1.0, 1.0, 0.6>}
  finish {ambient 0.2 diffuse 0.8 ior 1.33}
  rotate <0, 45, 0>
  translate <7, 0, -5>
}

box {<-1, -1, -1>, <1, 1, 1>
  pigment { color rgbf <0.9, 0.2, 0.3, 0.4>}
  finish {ambient 0.2 diffuse 0.8 ior 1.167}
  translate <0, -2.5, -3>
}

box {<-1, -1, -1>, <1, 1, 1>
  pigment { color rgbf <0.5, 0.9, 0.2, 0.4>}
  finish {ambient 0.2 diffuse 0.8 ior 1.167}
  translate <4, -2.5, 3>
}

box {<-1, -1, -1>, <1, 1, 1>
  pigment { color rgbf <0.2, 0.6, 0.8, 0.4>}
  finish {ambient 0.2 diffuse 0.8 ior 1.167}
  translate <-4, -2.5, 3>
}
