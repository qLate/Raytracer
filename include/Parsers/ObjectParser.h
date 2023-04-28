#pragma once

#include <vector>

#include "Triangle.h"
#include "Vertex.h"

class Model
{
    void parseObject(const std::filesystem::path& path);

public:
    std::vector<std::shared_ptr<Triangle>> triangles;
    std::vector<Vertex> vertices;

    explicit Model(const std::filesystem::path& path);

};