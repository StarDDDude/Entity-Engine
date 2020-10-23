#pragma once

#include <vector>

class renderer
{
public:     //Data
    std::vector<unsigned int> VertexB_IDs;
    std::vector<unsigned int> VertexA_IDs;
    std::vector<unsigned int> Index_IDs;


public:     //Functions
    renderer();
    ~renderer();

    void draw(std::vector<void*> *EA, unsigned int program);

    void CreateSquareData();
    void DestroySquareData();

};
