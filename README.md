# 110590049

## result
| obj                                | render mode                        | color                              |
| ---------------------------------- | ---------------------------------- | ---------------------------------- |
| ![](https://imgur.com/l1Y0vKk.png) | ![](https://imgur.com/JavrM8G.png) | ![](https://imgur.com/mo4HF2t.png) |
| ![](https://imgur.com/VpUyd3i.png) | ![](https://imgur.com/SX5JcnG.png) | ![](https://imgur.com/PWeBeTZ.png) |
| ![](https://imgur.com/duf2Wij.png) | ![](https://imgur.com/duf2Wij.png) | ![](https://imgur.com/vD20nEr.png) |
| ![](https://imgur.com/RROwZdE.png) |                                    |                                    |

## require
* cmake
* g++


## run
```bash
cmake -B build
cmake --build build
./build/ComputerGraph ./obj/teddy.obj
```
## key action
| Key Pressed | Action                          |
| ----------- | ------------------------------- |
| q           | Increment trans.x               |
| a           | Increment trans.y               |
| z           | Increment trans.z               |
| w           | Increment angle.x               |
| s           | Increment angle.y               |
| x           | Increment angle.z               |
| e           | Increment scale.x               |
| d           | Increment scale.y               |
| c           | Increment scale.z               |
| r           | Increment camera.x              |
| f           | Increment camera.y              |
| v           | Increment camera.z              |
| t           | Increment look_point.x          |
| g           | Increment look_point.y          |
| b           | Increment look_point.z          |
| y           | Increment arbitray_direction.x  |
| h           | Increment arbitray_direction.y  |
| n           | Increment arbitray_direction.z  |
| u           | Decrement arbitray_direction.x  |
| j           | Decrement arbitray_direction.y  |
| m           | Decrement arbitray_direction.z  |
| i           | Increment arbitray rotate angle |
| 1           | Reset                           |