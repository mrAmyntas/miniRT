# miniRT
miniRT

Coded a basic raytracer in C. Works on macOS.
Can handle planes, cylinders, spheres, discs & tori.

Runs by creating program and adding a scene to display as an argument.

"./miniRT scene1"

Look at scenes for examples.

Colors are RGB and range 0 to 255.
Directions are always x,y,z with range -1 to 1.

Positions are always x,y,z coordinates.

Ambient lighting is set with identifier A, followed by the contrast ratio (range 0-1) followed by color.

Camera position is set with identifier C, followed by is position, the direction it is facing and the field of view.

Light sources are set with identifier L (only bonus can handle multiple), followed by position, intensity (range 0-1), and color.

Cylinders are set with identifier cy, followed by position (centre of bottom cap), a direction (3d normalized vector of axis of cylinder), the diameter, the height and the color.

Spheres are set with identifier sp, followed by position (centre of sphere), diameter and color.

Planes are set with identifier pl, followed by position, 'direction' (3d normalized normal vector), and the color. 

Tori (only bonus) are set with identifier tor, followed by position (centre of hole), 'direction' (3d normalized normal vector), the diameter of the larger circle (around the hole), the diameter of smaller circle (the curved cylinder) and the color. (only works when first diameter is larger than second).

Checkerboard pattern (only bonus) is set by including identifier cb, followed by amount of the pattern you want vertically and then horizontally. 

Example of a bunch of spheres with different light sources which have different colors.

![Alt text](/marbles.png?raw=true "Marbles")

