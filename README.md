# Raytracer

### Description of Raytracer
This is a raytracer written in C++ intended to be used for creating realistic images. Image output is defaulted to output.png.

Implementation features include:

* Blinn-Phong BRDF
* Refractions and reflections
* Super Sampling
* Object transformations
* Bounding Volume Hierarchy
* Monte Carlo global illumination
* Depth of Field
* Animation (Python Script)

# Usage
## Building Raytracer

* Install [GLM](https://glm.g-truc.net/)
* Clone project
* Run the following commands: 
	``` {.sourceCode .sh}
	mkdir build
	cd build
	cmake ..
	make
	```

## Running Raytracer

Command line arguments: 
* `render <input_file.pov> <width> <height> [-flags]` - render the actual image to output.png
* `sceneinfo <input_file.pov>` - gives various info from the scene

* `-fresnel` - for fresnel affect
* `-beers` - for beers law
* `-sds` - for adding spacial data structure
* `-gi [-gi_samples=N]` - for adding global illumination with optional sample size (default 2)
* `-focal [-focallength=N] [-aperture=N] [-output=something.png] [-camera=N]`  - depth of field has the option for different focal lengths, aperture sizes, output files, and camera positions
* `-ss=N` - super sampling with optional samples


## Example Images

* Monte Carlo Global Illumination

![gi](website/output2.jpg)

* Depth of field 

![gif_dof](website/15sample.gif)

![jpg_dof](website/depthoffield2.jpg)

