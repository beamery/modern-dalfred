CS 559 Project 2 Readme
=======================
By: Brian Murray

Features
--------

### Controls ###
- Adjustable height stools (J and K)
- Zoom in and out (I and O)
- Camera rotation (arrow keys)
- Wireframe (W)
- Switch between shaders (S)
- Switch between different views (F1)
- Switch to final view (F2)

### Things to note ###
- Fireplace is always rendered with Phong shading (to allow for correct texture lighting)
- Fire created with a textured particle emitter
  - Individual flames are rendered using point sprites
  - All lighting in the scene comes from the fire
  - Added flickering of the light to simulate the flickering of the light given off by an actual fire
- Also have a particle fountain, but it's not in use right now (didn't really fit with the scene)
- Table is one of Ikea's suggested accessories with Dalfred stools
- Vase, bowl, and goblet all modeled procedurally, using the same mesh generator
  - Use different variations on a sine wave to create different objects
