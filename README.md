# Entity-Engine
Personal Game engine project

This is a project where I am attempting to build a GamEngine from scratch
My goal is to have a system that can do the following (very broad goal):
1. Update behaviour of entities
2. Draw the world onto the screen

This is mostly meant as a learning project for myself.
Due to that I am not planning on collaborating with others on it within the near future.

However I wanna keep this publically hosted in hope that others can learn of it
(though currently you can't cause I just created this and there's nothing of substance)


In case you wanna compile this in your own use:
I am building the project via VSCode
Currently the compilation is set up in the .vscode folder in a way that just gives g++ the .cpp files as input.
Resulting in this command ({workspace folder} representing the root folder of the project):
g++ -g '{workspace folder}/main.cpp' -o '{workspace folder}/Build' -lglfw -lGL -lGLEW
If you are using a different development envoirement you'll have to make sure about proper compilation yourself.

Take into consideration that There are dependencies I have inked via global include paths and are not in the projects.
These currently are:
glew.h
glfw3.h

I am planning to create a proper build setup in the future.



At the ed of this readme I'd like to credit the sources which I used to learn about the concepts and libraries I am using here:
[Name of Resource]{Link to Resource}
[The Cherno]{https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2}






P.S. to myself: This feels way to detailed for what the code currently is
