# FdF

**FdF** is a project from 42 School where we transform a file containing a grid of height values into a 3D wireframe using the MiniLibX graphics library. Think of it as turning numbers into art!

## Project Overview

The main goal of FdF is to read a file with height values arranged in a grid and render it as a stunning 3D wireframe model. We use the **MiniLibX** library to handle graphics rendering.

### Example

Here is an example of a small map file:

```
0  0  0  0  0  0  0  0  0  0
0 10 10 10 10 10 10 10 10  0
0 10 20 15 12 15 17 20 10  0
0 10 15 10 12 15 15 15 10  0
0  5 15 10 12 15 15 13 10  0
0  5 10  5  7 12 12 12 10  0
0  5  7  1  2  7  5  5  7  0
0  3  0  0  1  2  2  2  5  0
0  1  0  0  0  0  0  0  3  0
0  0  0  0  0  0  0  0  0  0
```

And here’s how it looks when rendered:

![Example Render](img/small-example.png)

### Larger Maps in Action

![Demo mars](img/demo1-mars.png)
![Demo t1](img/demo2-t1.png)
![Demo fract](img/demo3-fract.png)
![Demo star](img/demo4-star.png)

## Features

### Controls & informations

Wondering what to do inside the window? Don’t worry—controls are displayed by default! You can hide them with `[C]`.

![Controls](img/infos-controls.png)

Need more details? Activate the real-time information panel with `[I]`. A lot of informations are here, enjoy nerds!

![Informations](img/infos-realtime.png)

### Z-Axis Scaling

Some maps have exaggerated heights that look out of proportion. You can adjust the Z-axis scaling with `[-]` and `[+]`.

![s shrink](img/z-shrink.gif)


### Perspective Projection

Enable **perspective projection** for a more realistic 3D effect.

![Perspective Projection](img/perspective.png)

With perspective enabled, you can tweak parameters like the field of view (FOV) using `[<]` and `[>]`. The default FOV is 60.

### Free Camera Mode

Explore your wireframe in **free camera mode**! Move around the scene with the `WASD` keys for an immersive experience. It pairs beautifully with perspective mode.

![Free Camera Mode](img/freecam.gif)

### Z-ordering

By default, lines are drawn in the same order for every frame. This can cause visual glitches where lines that should be behind others appear in front. 
![z ordering problem](img/z-ordering-off.png)

Toggle Z-ordering with `[Z]` to fix this issue. Note: it’s disabled by default due to performance costs.
![z ordering on](img/z-ordering-on.png)

### Color Presets

Switch between various color presets to change the wireframe’s appearance. Use the numpad keys to select one of four presets:

1. **Default**: White at the lowest points, purple at the highest.
2. **Earth-like (smooth)**: Great for maps like `MGDS_WHOLE_WORLD_OCEAN1_M/L/XL.fdf`.
3. **Earth-like (non-smooth)**: Same as preset 2 but without smoothing.
4. **Moon-like**: Perfect for maps like `USGS_ULCN2005_grid.txt_OCEAN1_M/L.fdf`.

#### Earth Preset
![Earth preset](img/earth-color-preset.gif)

#### Moon Preset
![Moon preset](img/moon-color-preset.gif)

### Spherical Projection

Flat maps are boring! With my FdF, maps can become spherical for a more realistic touch. Science says the Earth is round, and so is ours. 🌍

![Spherical Earth Projection](img/round-earth.gif) 
(As you see we can also here play with the z-axe ratio)

This works for any map not just Earth. Check out the Moon in all its spherical glory:

![Spherical Moon Projection](img/round-moon.png) 

## Conclusion

**FdF** is an exciting project that teaches you file parsing tricks and how to project 3D points `(x, y, z)` onto a 2D screen. You’ll sharpen your matrix calculation skills and discover the joy of bringing numbers to life. With bonuses and extra features, this project becomes even more fun and rewarding.

Pick this project, dive in, and enjoy the ride!  
![Capybara wine](img/capy-wine.png)