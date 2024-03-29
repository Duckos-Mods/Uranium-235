#include <array>
#include <string>
#include "strUtil.hpp"

namespace Uranium::Catagories
{
    static const std::array<std::string, 5> catagories = { "construction", "equipment", "items", "nature", "none" };
    enum class Catagory: unsigned char
    {
        construction = 0,
        equipment = 1,
        items = 2,
        nature = 3,
        none = 4,
    };


    // O(1) time complexity
    static CStrWithLength catagoryToString(Catagory catagory)
    {
        return { catagories[static_cast<int>(catagory)].c_str(), catagories[static_cast<int>(catagory)].size(), false };
    }

    // O(n) time complexity (n = number of catagories)
    static Catagory stringToCatagory(std::string catagory)
    {
        for (int i = 0; i < catagories.size(); i++)
        {
            if (catagory == catagories[i])
            {
                return static_cast<Catagory>(i);
            }
        }
        return Catagory::none;
    }
}
