# CUB3D
A little program in C language that reproduces a 3D environment like wolfenstein 3d.

This project uses the principle of ray-casting to calculate and display a simple 3d environment (made of straight walls, a floor and a ceiling).
It use the mlx_linux library that is provide by school 42.

You can use it like that :
```
$ make
$ ./cub3d map.cub
```
There are some exemple of maps in the "cartes" folder but you can create your own as long as it includes a resolution, a textures for each wall face, also a texture for floor, ceiling and sprites. Of course it need to include a map, which is composed of 1 (wall), 0 (empty) and of 2 (sprites).
