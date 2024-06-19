# 110590049 final

## result

![](https://imgur.com/JDM4Mvn.png)
![](https://imgur.com/2pWPjj2.png)

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
./build/cg-course.exe
```


### linux
```bash
cmake -B build
cmake --build build
./build/cg-course
```
## key action

| Key Pressed | Action             |
| ----------- | ------------------ |
| 1           | Increment trans.x  |
| 2           | Increment trans.y  |
| 3           | Increment trans.z  |
| 4           | Increment angle.x  |
| arrow up    | camera turn up     |
| arrow down  | camera turn down   |
| arrow right | camera turn  right |
| arrow left  | camera turn left   |
