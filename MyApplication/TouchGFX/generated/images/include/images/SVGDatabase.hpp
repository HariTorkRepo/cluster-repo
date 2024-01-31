// Generated by imageconverter. Please, do not edit!

#ifndef TOUCHGFX_SVGDATABASE_HPP
#define TOUCHGFX_SVGDATABASE_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/hal/VGData.hpp>

enum SVGImages
{
    SVG_DOG_ID = 0,
    SVG_MUSIC_ID = 1,
    SVG_OLD_PHOTO_CAMERA_ID = 2,
    SVG_PALETTE_ID = 3,
    SVG_RUNNING_ID = 4,
    SVG_SETTINGS_ID = 5,
    SVG_STLOGO_ID = 6,
    NUMBER_OF_SVG_IMAGES = 7
};

namespace SVGDatabase
{
const touchgfx::VGObject* getInstance();
uint16_t getInstanceSize();
} // namespace SVGDatabase

#endif // TOUCHGFX_SVGDATABASE_HPP
