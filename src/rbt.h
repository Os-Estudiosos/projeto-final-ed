#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "tree_utils.h"

namespace RBT
{

    void rotateLeft(Node** );


    void rotateRight(Node** );


    void fixInsert(Node **root, Node* z);
}