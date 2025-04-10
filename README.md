# Particle-System ✅125/100
Particle-system creator & renderer using OpenCL as compute shaders

Particle-systems are only composed of points, textures aren't handled for now

Graphic libraries :
  - OpenGL v4.5
  - OpenCL v3.0 (currently adding 2.0 support [in this branch](https://github.com/DailyWind00/Particle-System/tree/OpenCL-2.0-Support))
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


You can load particle systems like this in config.json:
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
> You also have a template for beginner in "./systems/exemple/" to get started with particle-systems creation
#
<p align="center">
  <img src="exemple.gif"/>
</p>
