// cpe473 simple reflect - planes and spheres reflective

camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<-100, 100, 100> color rgb <1.5, 1.5, 1.5>}


sphere { <0, 0, 0>, 3
  pigment { color rgb <1.0, 0.92, 0.51>}
  finish {ambient 0.4 diffuse 0.8 reflection 0.8}
}

sphere { <4, 1, 0>, 1
  pigment { color rgb <0.38, 0.69, 0.40>}
  finish {ambient 0.4 diffuse 0.8 reflection 0.5}
}

plane {<0, 1, 0>, -4
  pigment {color rgb <0.29, 0.25, 0.49>}
  finish {ambient 0.4 diffuse 0.8 reflection 0.7}
}
