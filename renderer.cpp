#include "renderer.h"

#include <GL/glew.h>

#include "block.h"
#include "GLAssert.h"

renderer::renderer(){

}
renderer::~renderer(){
    while(Index_IDs.size() > 0){
        VertexB_IDs.erase(VertexB_IDs.end()-1);
        VertexA_IDs.erase(VertexA_IDs.end()-1);
        Index_IDs.erase(Index_IDs.end()-1);
    }
}

/*! @brief Draws entities
 * 
 * @param[in] Entities Pointer to Array of Entities
 * @param[in] program ID of the program to use
 */
void renderer::draw(std::vector<void*> *Entities, unsigned int program)
{
    for(int i=0; i<Entities->size(); i++)
    {
        //[1]:
        unsigned char type = *(unsigned char*)(*Entities)[i];
        switch (type){
        case 0 :
            //[2]:
            GLCall(glBindVertexArray(VertexA_IDs[0]));                  //<- Detect which VA must be used by object type
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexB_IDs[0]));      //Currently only works cause there is only 1
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_IDs[0]));//type of object and graphics data
            GLCall(glUseProgram(program));

            //[3]:
            GLCall(glUniform2f(glGetUniformLocation(program, "pos"), float((*(block*)(*Entities)[i]).Xpos), float((*(block*)(*Entities)[i]).Ypos)));
            GLCall(glUniform1f(glGetUniformLocation(program, "size"), float((*(block*)(*Entities)[i]).size)));
            GLCall(glUniform4f(glGetUniformLocation(program, "Col"), (*(block*)(*Entities)[i]).R, (*(block*)(*Entities)[i]).G, (*(block*)(*Entities)[i]).B, 1.0));
            //^Godforsaken unreadable code
            break;
        
        case 1 :
            //[2]:
            GLCall(glBindVertexArray(VertexA_IDs[0]));                  //<- Detect which VA must be used by object type
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexB_IDs[0]));      //Currently only works cause there is only 1
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_IDs[0]));//type of object and graphics data
            GLCall(glUseProgram(program));

            //[3]:
            GLCall(glUniform2f(glGetUniformLocation(program, "pos"), float((*(block*)(*Entities)[i]).Xpos), float((*(block*)(*Entities)[i]).Ypos)));
            GLCall(glUniform1f(glGetUniformLocation(program, "size"), float((*(block*)(*Entities)[i]).size)));
            GLCall(glUniform4f(glGetUniformLocation(program, "Col"), (*(block*)(*Entities)[i]).R, (*(block*)(*Entities)[i]).G, (*(block*)(*Entities)[i]).B, 1.0));
            //^Godforsaken unreadable code
            break;
        
        default:
            std::cout << "[ERROR]:Entity was detected with an invalid Entity ID" << std::endl;
            std::cout << "|-----|:renderer.cpp" << std::endl;
            std::cout.flush();
            break;
        }
        //[4]:
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    }
    //1. [switch]:          Check object type to determine which graphics routine to call 
    //2. [glBind|Use]:      Bind the correct Vertex Array, Vertex Buffer and Indicies
    //3. [glUniform]:       Set the Uniforms needed for the object
    //4. [glDrawElements]:  Draw the object
}

void renderer::CreateSquareData()
{
    float verticies[8]{
        -1.0f, -1.0f,
        +1.0f, -1.0f,
        +1.0f, +1.0f,
        -1.0f, +1.0f,
    };
   
    unsigned int indicies[6]{
        0,1,2,
        0,2,3,
    };

    //^Data for a 2D Default Cube

    VertexB_IDs.emplace_back(0);
    VertexA_IDs.emplace_back(0);
    Index_IDs.emplace_back(0);
    
    GLCall(glGenBuffers(1, &VertexB_IDs.back()));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexB_IDs.back()));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), verticies, GL_STATIC_DRAW));

    GLCall(glGenVertexArrays(1, &VertexA_IDs.back()));
    GLCall(glBindVertexArray(VertexB_IDs.back()));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0));
    
    GLCall(glGenBuffers(1, &Index_IDs.back()));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_IDs.back()));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indicies, GL_STATIC_DRAW));

}