// cs473, recurses
camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.5, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<-5, 3, 0> color rgb <0.3, 0.5, 0.3>}
light_source {<5, 10, 5> color rgb <0.3, 0.4, 0.5>}

// floor
plane {<0, 1, 0>, -4
  pigment {color rgb <0.2, 0.2, 0.8>}
  finish {ambient 0.4 diffuse 0.2 reflection 0.2}
  translate <0, -1, 0>
}

// left wall
plane {<1, 0, 0>, -8
  pigment {color rgb <0.8, 0.2, 0.2>}
  finish {ambient 0.4 diffuse 0.2 reflection 0.2}
  rotate <0, 30, 0>
}

// back wall
plane {<0, 0, -1>, 30
  pigment {color rgb <0.8, 0.4, 0.2>}
  finish {ambient 0.4 diffuse 0.2 reflection 0.2}
  rotate <0, 30, 0>
}

// back wall on the right
plane {<0, 0, -1>, 30
  pigment {color rgb <0.0, 0.2, 0.2>}
  finish {ambient 0.4 diffuse 0.8 reflection 0.2}
  rotate <0, -20, 0>
}

// pyramid of spheres
sphere { <-2, -1.74305, -1.74305>, 2
  pigment { color rgbf <1.0, 0.0, 1.0, 0.4>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.6}
  translate <-4, -3, 2>
}

sphere { <2, -1.74305, -1.74305>, 2
  pigment { color rgbf <1.0, 0.0, 1.0, 0.4>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.6}
  translate <-4, -3, 2>
}

sphere { <0, -1.74305, 1.74305>, 2
  pigment { color rgbf <1.0, 0.0, 1.0, 0.4>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.6}
  translate <-4, -3, 2>
}

sphere { <0, 1.74305, 0>, 2
  pigment { color rgbf <1.0, 0.0, 1.0, 0.4>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.6}
  translate <-4, -3, 2>
}


// and a few assorted objects
sphere { <0, 0, 0>, 2
  pigment {color rgbf <1.0, 1.0, 1.0, 0.8>}
  finish {ambient 0.2 diffuse 0.8 refraction 1.0 ior 1.333}
  translate <5.5, -3, -1>
}

box { <-2, -5, -5>, <2, 5, 5>
  pigment { color rgbf <1.0, 0.2, 1.0, 0.6>}
  finish {ambient 0.2 diffuse 0.8 reflection 0.2 refraction 1.0 ior 1.9}
  rotate <0, -45, 0>
  translate <3, 0, -5>
}


// tile the floor
// leftmost column
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-22, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-18, -4.9999, -12>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-18, -4.9999, -16>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-18, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -8>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -12>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -16>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -24>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, 4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, 0>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -8>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -8>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -12>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -16>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -24>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -28>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -32>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -36>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -40>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


// one column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, 4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, 0>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -8>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -12>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -16>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -24>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -28>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -32>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -36>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -40>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -44>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -48>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, 4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, 0>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -8>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -12>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -16>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -24>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -28>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -32>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -36>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


// one more column to the right

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, 4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, 0>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -8>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -12>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -16>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -24>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -28>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}


// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, 4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, 0>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -8>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -12>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -16>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -24>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -28>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, 4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, 0>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -8>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -12>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -16>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -24>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -28>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -4>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -8>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -12>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -16>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -24>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -8>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -12>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -16>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -24>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -28>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <22, -4.9999, -12>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <22, -4.9999, -16>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <22, -4.9999, -20>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <22, -4.9999, -24>
  pigment {color rgb <0.9, 0.9, 0.0>}
  finish {ambient 0.4 diffuse 0.5}
}

