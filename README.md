### blendmodes
This OpenGL-based tool allows you to perform basic image blending operations using the CLI. An OpenGL 2.0+ compatible graphics card is required for this tool to work. Systems without a graphics card are currently out of luck. However, software rendering mode is coming soon!

#### Requirements
* [glfw](http://www.glfw.org/)

#### Instructions
```
make
./bm backgroundFilename foregroundFilename outputFilename blendMode blendOpacity
```

**Example:** ```./bm lena.png baboon.png lenaAddBaboon.png 0 1.0```

| Background                           | Foreground                           | Output                               | Blend mode      | Blend opacity |
|:------------------------------------:|:------------------------------------:|:------------------------------------:|-----------------|:-------------:|
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/sJzhepN.png) | 0: add          | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/gIQKb3f.png) | 1: average      | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/DIOdLqq.png) | 2: colorBurn    | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/hpqmcGh.png) | 3: colorDodge   | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/hi2flFf.png) | 4: darken       | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/jEpFxqG.png) | 5: difference   | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/SYARHnF.png) | 6: exclusion    | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/F7bmvGc.png) | 7: glow         | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/LNGswtP.png) | 8: hardLight    | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/8mMOOJ2.png) | 9: hardMix      | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/LxQwUtK.png) | 10: lighten     | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/FgIlJ0n.png) | 11: linearBurn  | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/6BkFVwn.png) | 12: linearDodge | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/9ABKRwO.png) | 13: linearLight | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/OO19r9v.png) | 14: multiply    | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/BoUOVcG.png) | 15: negation    | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/aSErNpA.png) | 16: normal      | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/2bOSFpw.png) | 17: overlay     | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/wI9IYrO.png) | 18: phoenix     | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/GtZEqfS.png) | 19: pinLight    | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/Ae9wLEU.png) | 20: reflect     | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/RuGGGGh.png) | 21: screen      | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/CMObCms.png) | 22: softLight   | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/UkCt810.png) | 23: subtract    | 1.0           |
| ![](https://i.imgur.com/dwnT1rz.png) | ![](https://i.imgur.com/EpcbGTg.png) | ![](https://i.imgur.com/AdM5OkV.png) | 24: vividLight  | 1.0           |

**Supported image types**:
* png
* bmp
* tga
* jpg

**Supported platforms**:
* Windows (Makefile coming soon!)
* Linux (Makefile coming soon!)
* macOSX

#### Credits
* Shaders inspired by [glsl-blend](https://github.com/jamieowen/glsl-blend)
* Sean T. Barrett for his fantastic C library [stb](https://github.com/nothings/stb)

#### TODO
* Adapt Makefile for Windows and Linux
* Allow to set x and y offsets for foreground and background using CLI parameters
* Write man page
* Add support for software rendering mode