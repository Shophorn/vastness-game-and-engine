/*
Shophorn Games
Leo Tamminen
Created 05/02/2019
*/

#pragma once

#include <ostream>

#include "Vector3f.hpp"
#include "Vector4f.hpp"
#include "Matrix4f.hpp"

std::ostream & operator << (std::ostream & os, const Engine::Maths::Vector3f & v);
std::ostream & operator << (std::ostream & os, const Engine::Maths::Vector4f & v);
std::ostream & operator << (std::ostream & os, const Engine::Maths::Matrix4f & v);

