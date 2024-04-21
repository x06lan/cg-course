# 110590049

## result
| obj                                | render mode                        | color                              |
| ---------------------------------- | ---------------------------------- | ---------------------------------- |
| ![](https://imgur.com/l1Y0vKk.png) | ![](https://imgur.com/JavrM8G.png) | ![](https://imgur.com/mo4HF2t.png) |
| ![](https://imgur.com/VpUyd3i.png) | ![](https://imgur.com/SX5JcnG.png) | ![](https://imgur.com/PWeBeTZ.png) |
| ![](https://imgur.com/duf2Wij.png) | ![](https://imgur.com/duf2Wij.png) | ![](https://imgur.com/vD20nEr.png) |
| ![](https://imgur.com/RROwZdE.png) |                                    |                                    |

## require
* [cmake](https://github.com/Kitware/CMake/releases/download/v3.29.2/cmake-3.29.2-windows-x86_64.msi)

<!-- ###  ubuntu

* install [wsl](https://apps.microsoft.com/detail/9pdxgncfsczv?ocid=pdpshare&hl=en-us&gl=US)

```
sudo apt install g++
sudo apt install cmake

``` -->


## run
**recommend use linux**
### windows
<!-- install `cmake tools` in your vscode -->
```
./cg-course.exe ./obj/teddy.obj
```


### linux
```bash
cmake -B build
cmake --build build
./build/cg-course ./obj/teddy.obj
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