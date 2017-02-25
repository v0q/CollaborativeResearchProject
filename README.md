# Parameterised 3D Modelling with Distance Fields
## Collaborative Research Project

### Abstract
When approaching 3D modelling, it requires a large amount of expertise to develop complex scenes in quick succession. Powerful modelling tools are required for the user to carry out these demands and artists often look for different ways to achieve quicker and more accurate results. In this paper, we present a visual, node-based approach to 3D modelling using signed distance fields. The node-based approach is similar to those employed by Houdini and Grasshopper and allows for easy parameterisation of the scene. By using signed distance functions to represent the scene, complex objects can be modelled using a combination of set-theoretic operations and simple deformations. Using an already functional and tested scene builder method it grants us a secure building block to base our tool around. This allows the artist to have a more streamlined and user-friendly application which is essential when constructing 3D scenes. Furthermore, the user can provide multiple instructions without having to understand the mathematical operations needed to generate the scene, thus making the application accessible to a wide variety of artists. In our implementation, we create a bridge between the visual front end and the technical back end to represent the scene.

### Node Editor
The original node editor used in this project was created by Dimitry Pinaev (https://github.com/paceholder/nodeeditor). The current implementation uses a modified version of the editor. Details regarding the modifications made to the node editor can be found in ./nodeEditor/README.md

### Examples
![example1](https://github.com/v0q/CollaborativeResearchProject/tree/master/Examples/1.png "Example 1")
![example2](https://github.com/v0q/CollaborativeResearchProject/tree/master/Examples/2.png "Example 2")
![example3](https://github.com/v0q/CollaborativeResearchProject/tree/master/Examples/3.png "Example 3")

Two examples videos can be found under _Examples_

### Dependencies

- Qt >5.6
- OpenGL >4.1
- GLM
- C++11
