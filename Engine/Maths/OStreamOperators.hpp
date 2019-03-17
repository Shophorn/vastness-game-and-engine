/*
Shophorn Games
Leo Tamminen
Created 05/02/2019
*/

#pragma once

#include <ostream>

#include "vector2f.hpp"
#include "vector3f.hpp"
#include "vector4f.hpp"
#include "matrix4f.hpp"
#include "Quaternion.hpp"

std::ostream & operator << (std::ostream & os, maths::vector2f v);
std::ostream & operator << (std::ostream & os, const maths::vector3f & v);
std::ostream & operator << (std::ostream & os, const maths::vector4f & v);
std::ostream & operator << (std::ostream & os, const maths::matrix4f & m);
std::ostream & operator << (std::ostream & os, const maths::quaternion & q);

