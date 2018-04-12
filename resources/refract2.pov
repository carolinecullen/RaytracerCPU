camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<-100, 100, 100> color rgb <1.5, 1.5, 1.5>}


sphere { <0, 0, 0>, 3
  pigment { color rgbf <1.0, 1.0, 1.0, 0.75>}
  finish {ambient 0.2 diffuse 0.4  refraction 1.0 ior 1.33}
  translate <0, 0, 0>
}

sphere { <2, 1, -5>, 2.3
  pigment { color rgb <0.38, 0.69, 0.40>}
  finish {ambient 0.4 diffuse 0.8}
}

plane {<0, 1, 0>, -4
      pigment {color rgb <0.2, 0.2, 0.8>}
      finish {ambient 0.4 diffuse 0.8}
}
