
#include <iostream>
#include <memory>
#include <utility>
#include <cassert>

#include "Library.hpp"
#include "Members/StudentMember.hpp"
#include "Members/TeacherMember.hpp"

// ==========================================
// AFFICHAGE VIA L'INTERFACE
// ==========================================

void DisplayObject(const IDisplayable& object)
{
    object.GetInfo();
}

int main()
{
    
}