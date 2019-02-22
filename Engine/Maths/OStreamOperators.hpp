/*
Shophorn Games
Leo Tamminen
Created 05/02/2019
*/

#pragma once

#include <ostream>

#include "vector3f.hpp"
#include "Vector4f.hpp"
#include "matrix4f.hpp"

std::ostream & operator << (std::ostream & os, const Core::Maths::vector3f & v);
std::ostream & operator << (std::ostream & os, const Core::Maths::Vector4f & v);
std::ostream & operator << (std::ostream & os, const Core::Maths::matrix4f & v);

