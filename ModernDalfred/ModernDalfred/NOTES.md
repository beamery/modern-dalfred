Project 2 Notes
===============

Generating meshes
-----------------
- First create a mesh of vertices, with just positions and colors filled in.
  - These vertices will each have a std::vector of normal coords associated with it 
    (empty at initialization)
  - This vector will be stored outside of the actual vertex

- Go through and generate triangles from the vertices
  - For each triangle, store the vertex ordering, as well as the normal of the triangle
  - if a particular vertex is used in the triangle, push the normal of the triangle
    into the vector of normals associated with.
  - Once we are done generating triangle index order, we will have the normals associated
    with every vertex.
  - We will then average these normals and put them into the normal location inside 
    each vertex

- With this implementation, the triangles will not actually be used for rendering, but will
  simply be a way to grab a normal vector


Next
======
- Not going to worry about optimizing my stool rendering for now
- While I do that, I should think of an environment that I want to model

Environment Ideas
=================
- Den
  - Stools at table, possibly with chairs at other spots in the room
  - Bookcase maybe
  - Definitely a fireplace
	- That means figuring out how to make a particle generator
  - Need texturing (I think)

- Outdoors
  - Could make a procedurally generated landscape
  - Need trees
  - Billboards for grass
	- Could also make a procedurally generated grass texture
  - Need to figure out texturing
  - Sounds more difficult

