#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "tree_utils.h"

namespace RBT
{

    enum Color {RED, BLACK};

    void rotateLeft(Node** root, Node* x);


    void rotateRight(Node** root, Node* y);


    void fixInsert(Node **root, Node* z);
}