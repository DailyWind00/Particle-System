# Particle-System ✅125/100
Particle-system creator & renderer using OpenCL as compute shaders

Particle-systems :
  - are only composed of points, textures aren't handled for now
  - are technically in 3D, but you need to add a camera to really see it, and exemple (except rain) are in 2D
  - can have many particles, up to ~3 millions, depending on your GPU memory
  - never instanciate particles in CPU, particles are created in the compute shader

> Graphic libraries :
>   - OpenGL v4.5 (v2.0 support [here](https://github.com/DailyWind00/Particle-System/tree/OpenGL-2.0-Support))
>   - OpenCL v3.0 (v2.0 support [here](https://github.com/DailyWind00/Particle-System/tree/OpenCL-2.0-Support))
#
To load particle systems, you have a json API, connecting your kernel programs (compute shaders) and shaders to the renderer.

To run the program, clone the repo, make and execute is with a json config path as a parameter, additionals flags can be added before the json :

```shell
# Clone the repo
  git clone https://github.com/DailyWind00/Particle-System/ && cd Particle-System

# Create the executable
  make

# Run the program
  ./Particle-System [flags] <json config>
```
Here are the flags availables and the commands that can be used during runtime :
```
  Flags:
    -v, --verbose	: Verbose mode
    -r, --resizable	: Resizable window
    -s, --size [value]	: Set the particles size (default 1)
        --no-tooltip	: Disable the commands tooltip in the standard output
    -h, --help		: Display this information

  Commands:
    Left/Right arrows	: Switch particle system
    +/-			: Change particles size
    ESC			: Close the window
```


You can load particle systems like this in "*config.json*":
```json
  {
  	"particleSystem": [
  		{
  			"name": "string",
  			"particleCount": "unsigned int",
  			"shader": ["vertex path", "fragment path"],
  			"kernel": ["kernel program path", "..."]
  		},
  		{
  			"..."
  		},
  		"..."
  	]
  }
```
## 🔨 DIY | Make your OWN Particle System ! 🔨

You have a template for beginner in "[*./systems/exemple/*](https://github.com/DailyWind00/Particle-System/tree/main/systems/exemple)" to get started with particle-systems creation :
  - *compute.cl* is the compute shader, meaning :
    - It's written in OpenCL C (meaning you can use C syntax highlight but no IntelliSense)
    - It's main purpose is to create/respawn and move up to millions of particles at the same time

  - *fragment.frag* is the fragment shader, meaning :
    - It's where you render your particles, with color depending on what you want

> You also have the vertex shader for additional particle movement, but ideally you should not use it unless you really know what you are doing

Finally, add your files to "*config.json*" following the exemple right above, and enjoy you new Particle System !

#

Consider the "*./src/* *" folder as an User Interface (UI) for all your tests :
  - You can add uniform variables to shaders in the "[*program loop*](https://github.com/DailyWind00/Particle-System/blob/main/srcs/routine.cpp#L4-L42)", in the exemple I pass the time and the mouse position to my shaders

###### If you need help or want to implement a complex feature, contact me at dailywind.github@gmail.com

#
<p align="center">
  <img src="exemple.gif"/>
</p>

###### Don't forget to leave a star ! 🌟
