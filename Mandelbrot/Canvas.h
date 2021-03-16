#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include "Mesh.h"

class Canvas
{
protected:
	std::unique_ptr<Mesh> mesh;

public:
	Canvas();

	void create_mesh();
	void render();
};

