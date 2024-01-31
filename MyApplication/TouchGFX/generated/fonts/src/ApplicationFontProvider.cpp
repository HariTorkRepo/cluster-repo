/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <fonts/ApplicationFontProvider.hpp>
#include <fonts/GeneratedFont.hpp>
#include <texts/TypedTextDatabase.hpp>

touchgfx::Font* ApplicationFontProvider::getFont(touchgfx::FontId typography)
{
    switch (typography)
    {
    case Typography::MAINSELECTEDSUBDEMO:
        // Saira_SemiCondensed_SemiBold_32_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[0]);
    case Typography::LARGENUMBER:
        // ShareTechMono_Regular_63_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[1]);
    case Typography::WATHDIGITALCLOCK:
        // Saira_SemiCondensed_SemiBold_51_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[2]);
    case Typography::VERYLARGENUMBER:
        // Saira_SemiCondensed_SemiBold_150_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[3]);
    case Typography::SMALLNUMBERSAIRA:
        // Saira_SemiCondensed_SemiBold_24_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[4]);
    case Typography::HUMONGOUSNUMBER:
        // ShareTechMono_Regular_72_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[5]);
    case Typography::MEDIUMNUMBER:
        // ShareTechMono_Regular_26_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[6]);
    case Typography::SMALLNUMBER:
        // ShareTechMono_Regular_20_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[7]);
    case Typography::SMALLTEXT:
        // Saira_SemiCondensed_SemiBold_16_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[8]);
    case Typography::LARGENUMBERSAIRA:
        // Saira_SemiCondensed_SemiBold_42_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[9]);
    case Typography::MEDIUMTEXT:
        // Saira_SemiCondensed_SemiBold_20_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[10]);
    default:
        return 0;
    }
}
