/*
Shophorn Games
Leo Tamminen
Created 05/02/2019
*/

#pragma once

#include <ostream>

#include "vector3f.hpp"
#include "vector4f.hpp"
#include "matrix4f.hpp"

std::ostream & operator << (std::ostream & os, const maths::vector3f & v);
std::ostream & operator << (std::ostream & os, const maths::vector4f & v);
std::ostream & operator << (std::ostream & os, const maths::matrix4f & v);

