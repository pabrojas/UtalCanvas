#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "colors.h"

typedef enum
{
    INDIAN_RED          , CRIMSON             , LIGHTPINK           , LIGHTPINK_1         , LIGHTPINK_2         , 
    LIGHTPINK_3         , LIGHTPINK_4         , PINK                , PINK_1              , PINK_2              , 
    PINK_3              , PINK_4              , PALEVIOLETRED       , PALEVIOLETRED_1     , PALEVIOLETRED_2     , 
    PALEVIOLETRED_3     , PALEVIOLETRED_4     , LAVENDERBLUSH_1     , LAVENDERBLUSH_2     , LAVENDERBLUSH_3     , 
    LAVENDERBLUSH_4     , VIOLETRED_1         , VIOLETRED_2         , VIOLETRED_3         , VIOLETRED_4         , 
    HOTPINK             , HOTPINK_1           , HOTPINK_2           , HOTPINK_3           , HOTPINK_4           , 
    RASPBERRY           , DEEPPINK_1          , DEEPPINK_2          , DEEPPINK_3          , DEEPPINK_4          , 
    MAROON_1            , MAROON_2            , MAROON_3            , MAROON_4            , MEDIUMVIOLETRED     , 
    VIOLETRED           , ORCHID              , ORCHID_1            , ORCHID_2            , ORCHID_3            , 
    ORCHID_4            , THISTLE             , THISTLE_1           , THISTLE_2           , THISTLE_3           , 
    THISTLE_4           , PLUM_1              , PLUM_2              , PLUM_3              , PLUM_4              , 
    PLUM                , VIOLET              , MAGENTA             , MAGENTA_2           , MAGENTA_3           , 
    MAGENTA_4           , PURPLE              , MEDIUMORCHID        , MEDIUMORCHID_1      , MEDIUMORCHID_2      , 
    MEDIUMORCHID_3      , MEDIUMORCHID_4      , DARKVIOLET          , DARKORCHID          , DARKORCHID_1        , 
    DARKORCHID_2        , DARKORCHID_3        , DARKORCHID_4        , INDIGO              , BLUEVIOLET          , 
    PURPLE_1            , PURPLE_2            , PURPLE_3            , PURPLE_4            , MEDIUMPURPLE        , 
    MEDIUMPURPLE_1      , MEDIUMPURPLE_2      , MEDIUMPURPLE_3      , MEDIUMPURPLE_4      , DARKSLATEBLUE       , 
    LIGHTSLATEBLUE      , MEDIUMSLATEBLUE     , SLATEBLUE           , SLATEBLUE_1         , SLATEBLUE_2         , 
    SLATEBLUE_3         , SLATEBLUE_4         , GHOSTWHITE          , LAVENDER            , BLUE                , 
    BLUE_2              , BLUE_3              , BLUE_4              , NAVY                , MIDNIGHTBLUE        , 
    COBALT              , ROYALBLUE           , ROYALBLUE_1         , ROYALBLUE_2         , ROYALBLUE_3         , 
    ROYALBLUE_4         , CORNFLOWERBLUE      , LIGHTSTEELBLUE      , LIGHTSTEELBLUE_1    , LIGHTSTEELBLUE_2    , 
    LIGHTSTEELBLUE_3    , LIGHTSTEELBLUE_4    , LIGHTSLATEGRAY      , SLATEGRAY           , SLATEGRAY_1         , 
    SLATEGRAY_2         , SLATEGRAY_3         , SLATEGRAY_4         , DODGERBLUE_1        , DODGERBLUE_2        , 
    DODGERBLUE_3        , DODGERBLUE_4        , ALICEBLUE           , STEELBLUE           , STEELBLUE_1         , 
    STEELBLUE_2         , STEELBLUE_3         , STEELBLUE_4         , LIGHTSKYBLUE        , LIGHTSKYBLUE_1      , 
    LIGHTSKYBLUE_2      , LIGHTSKYBLUE_3      , LIGHTSKYBLUE_4      , SKYBLUE_1           , SKYBLUE_2           , 
    SKYBLUE_3           , SKYBLUE_4           , SKYBLUE             , DEEPSKYBLUE_1       , DEEPSKYBLUE_2       , 
    DEEPSKYBLUE_3       , DEEPSKYBLUE_4       , PEACOCK             , LIGHTBLUE           , LIGHTBLUE_1         , 
    LIGHTBLUE_2         , LIGHTBLUE_3         , LIGHTBLUE_4         , POWDERBLUE          , CADETBLUE_1         , 
    CADETBLUE_2         , CADETBLUE_3         , CADETBLUE_4         , TURQUOISE_1         , TURQUOISE_2         , 
    TURQUOISE_3         , TURQUOISE_4         , CADETBLUE           , DARKTURQUOISE       , AZURE_1             , 
    AZURE_2             , AZURE_3             , AZURE_4             , LIGHTCYAN_1         , LIGHTCYAN_2         , 
    LIGHTCYAN_3         , LIGHTCYAN_4         , PALETURQUOISE_1     , PALETURQUOISE_2     , PALETURQUOISE_3     , 
    PALETURQUOISE_4     , DARKSLATEGRAY       , DARKSLATEGRAY_1     , DARKSLATEGRAY_2     , DARKSLATEGRAY_3     , 
    DARKSLATEGRAY_4     , CYAN                , CYAN_2              , CYAN_3              , CYAN_4              , 
    TEAL                , MEDIUMTURQUOISE     , LIGHTSEAGREEN       , MANGANESEBLUE       , TURQUOISE           , 
    COLDGREY            , TURQUOISEBLUE       , AQUAMARINE_1        , AQUAMARINE_2        , AQUAMARINE_3        , 
    AQUAMARINE_4        , MEDIUMSPRINGGREEN   , MINTCREAM           , SPRINGGREEN         , SPRINGGREEN_1       , 
    SPRINGGREEN_2       , SPRINGGREEN_3       , MEDIUMSEAGREEN      , SEAGREEN_1          , SEAGREEN_2          , 
    SEAGREEN_3          , SEAGREEN_4          , EMERALDGREEN        , MINT                , COBALTGREEN         , 
    HONEYDEW_1          , HONEYDEW_2          , HONEYDEW_3          , HONEYDEW_4          , DARKSEAGREEN        , 
    DARKSEAGREEN_1      , DARKSEAGREEN_2      , DARKSEAGREEN_3      , DARKSEAGREEN_4      , PALEGREEN           , 
    PALEGREEN_1         , PALEGREEN_2         , PALEGREEN_3         , PALEGREEN_4         , LIMEGREEN           , 
    FORESTGREEN         , GREEN_1             , GREEN_2             , GREEN_3             , GREEN_4             , 
    GREEN               , DARKGREEN           , SAPGREEN            , LAWNGREEN           , CHARTREUSE_1        , 
    CHARTREUSE_2        , CHARTREUSE_3        , CHARTREUSE_4        , GREENYELLOW         , DARKOLIVEGREEN_1    , 
    DARKOLIVEGREEN_2    , DARKOLIVEGREEN_3    , DARKOLIVEGREEN_4    , DARKOLIVEGREEN      , OLIVEDRAB           , 
    OLIVEDRAB_1         , OLIVEDRAB_2         , OLIVEDRAB_3         , OLIVEDRAB_4         , IVORY_1             , 
    IVORY_2             , IVORY_3             , IVORY_4             , BEIGE               , LIGHTYELLOW_1       , 
    LIGHTYELLOW_2       , LIGHTYELLOW_3       , LIGHTYELLOW_4       , LIGHTGOLDENRODYELLOW, YELLOW_1            , 
    YELLOW_2            , YELLOW_3            , YELLOW_4            , WARMGREY            , OLIVE               , 
    DARKKHAKI           , KHAKI_1             , KHAKI_2             , KHAKI_3             , KHAKI_4             , 
    KHAKI               , PALEGOLDENROD       , LEMONCHIFFON_1      , LEMONCHIFFON_2      , LEMONCHIFFON_3      , 
    LEMONCHIFFON_4      , LIGHTGOLDENROD_1    , LIGHTGOLDENROD_2    , LIGHTGOLDENROD_3    , LIGHTGOLDENROD_4    , 
    BANANA              , GOLD_1              , GOLD_2              , GOLD_3              , GOLD_4              , 
    CORNSILK_1          , CORNSILK_2          , CORNSILK_3          , CORNSILK_4          , GOLDENROD           , 
    GOLDENROD_1         , GOLDENROD_2         , GOLDENROD_3         , GOLDENROD_4         , DARKGOLDENROD       , 
    DARKGOLDENROD_1     , DARKGOLDENROD_2     , DARKGOLDENROD_3     , DARKGOLDENROD_4     , ORANGE_1            , 
    ORANGE_2            , ORANGE_3            , ORANGE_4            , FLORALWHITE         , OLDLACE             , 
    WHEAT               , WHEAT_1             , WHEAT_2             , WHEAT_3             , WHEAT_4             , 
    MOCCASIN            , PAPAYAWHIP          , BLANCHEDALMOND      , NAVAJOWHITE_1       , NAVAJOWHITE_2       , 
    NAVAJOWHITE_3       , NAVAJOWHITE_4       , EGGSHELL            , TAN                 , BRICK               , 
    CADMIUMYELLOW       , ANTIQUEWHITE        , ANTIQUEWHITE_1      , ANTIQUEWHITE_2      , ANTIQUEWHITE_3      , 
    ANTIQUEWHITE_4      , BURLYWOOD           , BURLYWOOD_1         , BURLYWOOD_2         , BURLYWOOD_3         , 
    BURLYWOOD_4         , BISQUE_1            , BISQUE_2            , BISQUE_3            , BISQUE_4            , 
    MELON               , CARROT              , DARKORANGE          , DARKORANGE_1        , DARKORANGE_2        , 
    DARKORANGE_3        , DARKORANGE_4        , ORANGE              , TAN_1               , TAN_2               , 
    TAN_3               , TAN_4               , LINEN               , PEACHPUFF_1         , PEACHPUFF_2         , 
    PEACHPUFF_3         , PEACHPUFF_4         , SEASHELL_1          , SEASHELL_2          , SEASHELL_3          , 
    SEASHELL_4          , SANDYBROWN          , RAWSIENNA           , CHOCOLATE           , CHOCOLATE_1         , 
    CHOCOLATE_2         , CHOCOLATE_3         , CHOCOLATE_4         , IVORYBLACK          , FLESH               , 
    CADMIUMORANGE       , BURNTSIENNA         , SIENNA              , SIENNA_1            , SIENNA_2            , 
    SIENNA_3            , SIENNA_4            , LIGHTSALMON_1       , LIGHTSALMON_2       , LIGHTSALMON_3       , 
    LIGHTSALMON_4       , CORAL               , ORANGERED_1         , ORANGERED_2         , ORANGERED_3         , 
    ORANGERED_4         , SEPIA               , DARKSALMON          , SALMON_1            , SALMON_2            , 
    SALMON_3            , SALMON_4            , CORAL_1             , CORAL_2             , CORAL_3             , 
    CORAL_4             , BURNTUMBER          , TOMATO_1            , TOMATO_2            , TOMATO_3            , 
    TOMATO_4            , SALMON              , MISTYROSE_1         , MISTYROSE_2         , MISTYROSE_3         , 
    MISTYROSE_4         , SNOW_1              , SNOW_2              , SNOW_3              , SNOW_4              , 
    ROSYBROWN           , ROSYBROWN_1         , ROSYBROWN_2         , ROSYBROWN_3         , ROSYBROWN_4         , 
    LIGHTCORAL          , INDIANRED           , INDIANRED_1         , INDIANRED_2         , INDIANRED_4         , 
    INDIANRED_3         , BROWN               , BROWN_1             , BROWN_2             , BROWN_3             , 
    BROWN_4             , FIREBRICK           , FIREBRICK_1         , FIREBRICK_2         , FIREBRICK_3         , 
    FIREBRICK_4         , RED_1               , RED_2               , RED_3               , RED_4               , 
    MAROON              , SGI_BEET            , SGI_SLATEBLUE       , SGI_LIGHTBLUE       , SGI_TEAL            , 
    SGI_CHARTREUSE      , SGI_OLIVEDRAB       , SGI_BRIGHTGRAY      , SGI_SALMON          , SGI_DARKGRAY        , 
    SGI_GRAY_12         , SGI_GRAY_16         , SGI_GRAY_32         , SGI_GRAY_36         , SGI_GRAY_52         , 
    SGI_GRAY_56         , SGI_LIGHTGRAY       , SGI_GRAY_72         , SGI_GRAY_76         , SGI_GRAY_92         , 
    SGI_GRAY_96         , WHITE               , WHITE_SMOKE         , GAINSBORO           , LIGHTGREY           , 
    SILVER              , DARKGRAY            , GRAY                , BLACK               , GRAY_99             , 
    GRAY_98             , GRAY_97             , GRAY_95             , GRAY_94             , GRAY_93             , 
    GRAY_92             , GRAY_91             , GRAY_90             , GRAY_89             , GRAY_88             , 
    GRAY_87             , GRAY_86             , GRAY_85             , GRAY_84             , GRAY_83             , 
    GRAY_82             , GRAY_81             , GRAY_80             , GRAY_79             , GRAY_78             , 
    GRAY_77             , GRAY_76             , GRAY_75             , GRAY_74             , GRAY_73             , 
    GRAY_72             , GRAY_71             , GRAY_70             , GRAY_69             , GRAY_68             , 
    GRAY_67             , GRAY_66             , GRAY_65             , GRAY_64             , GRAY_63             , 
    GRAY_62             , GRAY_61             , GRAY_60             , GRAY_59             , GRAY_58             , 
    GRAY_57             , GRAY_56             , GRAY_55             , GRAY_54             , GRAY_53             , 
    GRAY_52             , GRAY_51             , GRAY_50             , GRAY_49             , GRAY_48             , 
    GRAY_47             , GRAY_46             , GRAY_45             , GRAY_44             , GRAY_43             , 
    GRAY_42             , DIMGRAY             , GRAY_40             , GRAY_39             , GRAY_38             , 
    GRAY_37             , GRAY_36             , GRAY_35             , GRAY_34             , GRAY_33             , 
    GRAY_32             , GRAY_31             , GRAY_30             , GRAY_29             , GRAY_28             , 
    GRAY_27             , GRAY_26             , GRAY_25             , GRAY_24             , GRAY_23             , 
    GRAY_22             , GRAY_21             , GRAY_20             , GRAY_19             , GRAY_18             , 
    GRAY_17             , GRAY_16             , GRAY_15             , GRAY_14             , GRAY_13             , 
    GRAY_12             , GRAY_11             , GRAY_10             , GRAY_9              , GRAY_8              , 
    GRAY_7              , GRAY_6              , GRAY_5              , GRAY_4              , GRAY_3              , 
    GRAY_2              , GRAY_1              
} ColorName;

UtalCanvasColor* __utalCanvasColors = NULL;

void __init_colors()
{
    if( __utalCanvasColors != NULL )
        return;

    __utalCanvasColors = (UtalCanvasColor*)malloc( 552*sizeof(UtalCanvasColor));
    __utalCanvasColors[INDIAN_RED].red = 176;
    __utalCanvasColors[INDIAN_RED].green = 23;
    __utalCanvasColors[INDIAN_RED].blue = 31;

    __utalCanvasColors[CRIMSON].red = 220;
    __utalCanvasColors[CRIMSON].green = 20;
    __utalCanvasColors[CRIMSON].blue = 60;

    __utalCanvasColors[LIGHTPINK].red = 255;
    __utalCanvasColors[LIGHTPINK].green = 182;
    __utalCanvasColors[LIGHTPINK].blue = 193;

    __utalCanvasColors[LIGHTPINK_1].red = 255;
    __utalCanvasColors[LIGHTPINK_1].green = 174;
    __utalCanvasColors[LIGHTPINK_1].blue = 185;

    __utalCanvasColors[LIGHTPINK_2].red = 238;
    __utalCanvasColors[LIGHTPINK_2].green = 162;
    __utalCanvasColors[LIGHTPINK_2].blue = 173;

    __utalCanvasColors[LIGHTPINK_3].red = 205;
    __utalCanvasColors[LIGHTPINK_3].green = 140;
    __utalCanvasColors[LIGHTPINK_3].blue = 149;

    __utalCanvasColors[LIGHTPINK_4].red = 139;
    __utalCanvasColors[LIGHTPINK_4].green = 95;
    __utalCanvasColors[LIGHTPINK_4].blue = 101;

    __utalCanvasColors[PINK].red = 255;
    __utalCanvasColors[PINK].green = 192;
    __utalCanvasColors[PINK].blue = 203;

    __utalCanvasColors[PINK_1].red = 255;
    __utalCanvasColors[PINK_1].green = 181;
    __utalCanvasColors[PINK_1].blue = 197;

    __utalCanvasColors[PINK_2].red = 238;
    __utalCanvasColors[PINK_2].green = 169;
    __utalCanvasColors[PINK_2].blue = 184;

    __utalCanvasColors[PINK_3].red = 205;
    __utalCanvasColors[PINK_3].green = 145;
    __utalCanvasColors[PINK_3].blue = 158;

    __utalCanvasColors[PINK_4].red = 139;
    __utalCanvasColors[PINK_4].green = 99;
    __utalCanvasColors[PINK_4].blue = 108;

    __utalCanvasColors[PALEVIOLETRED].red = 219;
    __utalCanvasColors[PALEVIOLETRED].green = 112;
    __utalCanvasColors[PALEVIOLETRED].blue = 147;

    __utalCanvasColors[PALEVIOLETRED_1].red = 255;
    __utalCanvasColors[PALEVIOLETRED_1].green = 130;
    __utalCanvasColors[PALEVIOLETRED_1].blue = 171;

    __utalCanvasColors[PALEVIOLETRED_2].red = 238;
    __utalCanvasColors[PALEVIOLETRED_2].green = 121;
    __utalCanvasColors[PALEVIOLETRED_2].blue = 159;

    __utalCanvasColors[PALEVIOLETRED_3].red = 205;
    __utalCanvasColors[PALEVIOLETRED_3].green = 104;
    __utalCanvasColors[PALEVIOLETRED_3].blue = 137;

    __utalCanvasColors[PALEVIOLETRED_4].red = 139;
    __utalCanvasColors[PALEVIOLETRED_4].green = 71;
    __utalCanvasColors[PALEVIOLETRED_4].blue = 93;

    __utalCanvasColors[LAVENDERBLUSH_1].red = 255;
    __utalCanvasColors[LAVENDERBLUSH_1].green = 240;
    __utalCanvasColors[LAVENDERBLUSH_1].blue = 245;

    __utalCanvasColors[LAVENDERBLUSH_2].red = 238;
    __utalCanvasColors[LAVENDERBLUSH_2].green = 224;
    __utalCanvasColors[LAVENDERBLUSH_2].blue = 229;

    __utalCanvasColors[LAVENDERBLUSH_3].red = 205;
    __utalCanvasColors[LAVENDERBLUSH_3].green = 193;
    __utalCanvasColors[LAVENDERBLUSH_3].blue = 197;

    __utalCanvasColors[LAVENDERBLUSH_4].red = 139;
    __utalCanvasColors[LAVENDERBLUSH_4].green = 131;
    __utalCanvasColors[LAVENDERBLUSH_4].blue = 134;

    __utalCanvasColors[VIOLETRED_1].red = 255;
    __utalCanvasColors[VIOLETRED_1].green = 62;
    __utalCanvasColors[VIOLETRED_1].blue = 150;

    __utalCanvasColors[VIOLETRED_2].red = 238;
    __utalCanvasColors[VIOLETRED_2].green = 58;
    __utalCanvasColors[VIOLETRED_2].blue = 140;

    __utalCanvasColors[VIOLETRED_3].red = 205;
    __utalCanvasColors[VIOLETRED_3].green = 50;
    __utalCanvasColors[VIOLETRED_3].blue = 120;

    __utalCanvasColors[VIOLETRED_4].red = 139;
    __utalCanvasColors[VIOLETRED_4].green = 34;
    __utalCanvasColors[VIOLETRED_4].blue = 82;

    __utalCanvasColors[HOTPINK].red = 255;
    __utalCanvasColors[HOTPINK].green = 105;
    __utalCanvasColors[HOTPINK].blue = 180;

    __utalCanvasColors[HOTPINK_1].red = 255;
    __utalCanvasColors[HOTPINK_1].green = 110;
    __utalCanvasColors[HOTPINK_1].blue = 180;

    __utalCanvasColors[HOTPINK_2].red = 238;
    __utalCanvasColors[HOTPINK_2].green = 106;
    __utalCanvasColors[HOTPINK_2].blue = 167;

    __utalCanvasColors[HOTPINK_3].red = 205;
    __utalCanvasColors[HOTPINK_3].green = 96;
    __utalCanvasColors[HOTPINK_3].blue = 144;

    __utalCanvasColors[HOTPINK_4].red = 139;
    __utalCanvasColors[HOTPINK_4].green = 58;
    __utalCanvasColors[HOTPINK_4].blue = 98;

    __utalCanvasColors[RASPBERRY].red = 135;
    __utalCanvasColors[RASPBERRY].green = 38;
    __utalCanvasColors[RASPBERRY].blue = 87;

    __utalCanvasColors[DEEPPINK_1].red = 255;
    __utalCanvasColors[DEEPPINK_1].green = 20;
    __utalCanvasColors[DEEPPINK_1].blue = 147;

    __utalCanvasColors[DEEPPINK_2].red = 238;
    __utalCanvasColors[DEEPPINK_2].green = 18;
    __utalCanvasColors[DEEPPINK_2].blue = 137;

    __utalCanvasColors[DEEPPINK_3].red = 205;
    __utalCanvasColors[DEEPPINK_3].green = 16;
    __utalCanvasColors[DEEPPINK_3].blue = 118;

    __utalCanvasColors[DEEPPINK_4].red = 139;
    __utalCanvasColors[DEEPPINK_4].green = 10;
    __utalCanvasColors[DEEPPINK_4].blue = 80;

    __utalCanvasColors[MAROON_1].red = 255;
    __utalCanvasColors[MAROON_1].green = 52;
    __utalCanvasColors[MAROON_1].blue = 179;

    __utalCanvasColors[MAROON_2].red = 238;
    __utalCanvasColors[MAROON_2].green = 48;
    __utalCanvasColors[MAROON_2].blue = 167;

    __utalCanvasColors[MAROON_3].red = 205;
    __utalCanvasColors[MAROON_3].green = 41;
    __utalCanvasColors[MAROON_3].blue = 144;

    __utalCanvasColors[MAROON_4].red = 139;
    __utalCanvasColors[MAROON_4].green = 28;
    __utalCanvasColors[MAROON_4].blue = 98;

    __utalCanvasColors[MEDIUMVIOLETRED].red = 199;
    __utalCanvasColors[MEDIUMVIOLETRED].green = 21;
    __utalCanvasColors[MEDIUMVIOLETRED].blue = 133;

    __utalCanvasColors[VIOLETRED].red = 208;
    __utalCanvasColors[VIOLETRED].green = 32;
    __utalCanvasColors[VIOLETRED].blue = 144;

    __utalCanvasColors[ORCHID].red = 218;
    __utalCanvasColors[ORCHID].green = 112;
    __utalCanvasColors[ORCHID].blue = 214;

    __utalCanvasColors[ORCHID_1].red = 255;
    __utalCanvasColors[ORCHID_1].green = 131;
    __utalCanvasColors[ORCHID_1].blue = 250;

    __utalCanvasColors[ORCHID_2].red = 238;
    __utalCanvasColors[ORCHID_2].green = 122;
    __utalCanvasColors[ORCHID_2].blue = 233;

    __utalCanvasColors[ORCHID_3].red = 205;
    __utalCanvasColors[ORCHID_3].green = 105;
    __utalCanvasColors[ORCHID_3].blue = 201;

    __utalCanvasColors[ORCHID_4].red = 139;
    __utalCanvasColors[ORCHID_4].green = 71;
    __utalCanvasColors[ORCHID_4].blue = 137;

    __utalCanvasColors[THISTLE].red = 216;
    __utalCanvasColors[THISTLE].green = 191;
    __utalCanvasColors[THISTLE].blue = 216;

    __utalCanvasColors[THISTLE_1].red = 255;
    __utalCanvasColors[THISTLE_1].green = 225;
    __utalCanvasColors[THISTLE_1].blue = 255;

    __utalCanvasColors[THISTLE_2].red = 238;
    __utalCanvasColors[THISTLE_2].green = 210;
    __utalCanvasColors[THISTLE_2].blue = 238;

    __utalCanvasColors[THISTLE_3].red = 205;
    __utalCanvasColors[THISTLE_3].green = 181;
    __utalCanvasColors[THISTLE_3].blue = 205;

    __utalCanvasColors[THISTLE_4].red = 139;
    __utalCanvasColors[THISTLE_4].green = 123;
    __utalCanvasColors[THISTLE_4].blue = 139;

    __utalCanvasColors[PLUM_1].red = 255;
    __utalCanvasColors[PLUM_1].green = 187;
    __utalCanvasColors[PLUM_1].blue = 255;

    __utalCanvasColors[PLUM_2].red = 238;
    __utalCanvasColors[PLUM_2].green = 174;
    __utalCanvasColors[PLUM_2].blue = 238;

    __utalCanvasColors[PLUM_3].red = 205;
    __utalCanvasColors[PLUM_3].green = 150;
    __utalCanvasColors[PLUM_3].blue = 205;

    __utalCanvasColors[PLUM_4].red = 139;
    __utalCanvasColors[PLUM_4].green = 102;
    __utalCanvasColors[PLUM_4].blue = 139;

    __utalCanvasColors[PLUM].red = 221;
    __utalCanvasColors[PLUM].green = 160;
    __utalCanvasColors[PLUM].blue = 221;

    __utalCanvasColors[VIOLET].red = 238;
    __utalCanvasColors[VIOLET].green = 130;
    __utalCanvasColors[VIOLET].blue = 238;

    __utalCanvasColors[MAGENTA].red = 255;
    __utalCanvasColors[MAGENTA].green = 0;
    __utalCanvasColors[MAGENTA].blue = 255;

    __utalCanvasColors[MAGENTA_2].red = 238;
    __utalCanvasColors[MAGENTA_2].green = 0;
    __utalCanvasColors[MAGENTA_2].blue = 238;

    __utalCanvasColors[MAGENTA_3].red = 205;
    __utalCanvasColors[MAGENTA_3].green = 0;
    __utalCanvasColors[MAGENTA_3].blue = 205;

    __utalCanvasColors[MAGENTA_4].red = 139;
    __utalCanvasColors[MAGENTA_4].green = 0;
    __utalCanvasColors[MAGENTA_4].blue = 139;

    __utalCanvasColors[PURPLE].red = 128;
    __utalCanvasColors[PURPLE].green = 0;
    __utalCanvasColors[PURPLE].blue = 128;

    __utalCanvasColors[MEDIUMORCHID].red = 186;
    __utalCanvasColors[MEDIUMORCHID].green = 85;
    __utalCanvasColors[MEDIUMORCHID].blue = 211;

    __utalCanvasColors[MEDIUMORCHID_1].red = 224;
    __utalCanvasColors[MEDIUMORCHID_1].green = 102;
    __utalCanvasColors[MEDIUMORCHID_1].blue = 255;

    __utalCanvasColors[MEDIUMORCHID_2].red = 209;
    __utalCanvasColors[MEDIUMORCHID_2].green = 95;
    __utalCanvasColors[MEDIUMORCHID_2].blue = 238;

    __utalCanvasColors[MEDIUMORCHID_3].red = 180;
    __utalCanvasColors[MEDIUMORCHID_3].green = 82;
    __utalCanvasColors[MEDIUMORCHID_3].blue = 205;

    __utalCanvasColors[MEDIUMORCHID_4].red = 122;
    __utalCanvasColors[MEDIUMORCHID_4].green = 55;
    __utalCanvasColors[MEDIUMORCHID_4].blue = 139;

    __utalCanvasColors[DARKVIOLET].red = 148;
    __utalCanvasColors[DARKVIOLET].green = 0;
    __utalCanvasColors[DARKVIOLET].blue = 211;

    __utalCanvasColors[DARKORCHID].red = 153;
    __utalCanvasColors[DARKORCHID].green = 50;
    __utalCanvasColors[DARKORCHID].blue = 204;

    __utalCanvasColors[DARKORCHID_1].red = 191;
    __utalCanvasColors[DARKORCHID_1].green = 62;
    __utalCanvasColors[DARKORCHID_1].blue = 255;

    __utalCanvasColors[DARKORCHID_2].red = 178;
    __utalCanvasColors[DARKORCHID_2].green = 58;
    __utalCanvasColors[DARKORCHID_2].blue = 238;

    __utalCanvasColors[DARKORCHID_3].red = 154;
    __utalCanvasColors[DARKORCHID_3].green = 50;
    __utalCanvasColors[DARKORCHID_3].blue = 205;

    __utalCanvasColors[DARKORCHID_4].red = 104;
    __utalCanvasColors[DARKORCHID_4].green = 34;
    __utalCanvasColors[DARKORCHID_4].blue = 139;

    __utalCanvasColors[INDIGO].red = 75;
    __utalCanvasColors[INDIGO].green = 0;
    __utalCanvasColors[INDIGO].blue = 130;

    __utalCanvasColors[BLUEVIOLET].red = 138;
    __utalCanvasColors[BLUEVIOLET].green = 43;
    __utalCanvasColors[BLUEVIOLET].blue = 226;

    __utalCanvasColors[PURPLE_1].red = 155;
    __utalCanvasColors[PURPLE_1].green = 48;
    __utalCanvasColors[PURPLE_1].blue = 255;

    __utalCanvasColors[PURPLE_2].red = 145;
    __utalCanvasColors[PURPLE_2].green = 44;
    __utalCanvasColors[PURPLE_2].blue = 238;

    __utalCanvasColors[PURPLE_3].red = 125;
    __utalCanvasColors[PURPLE_3].green = 38;
    __utalCanvasColors[PURPLE_3].blue = 205;

    __utalCanvasColors[PURPLE_4].red = 85;
    __utalCanvasColors[PURPLE_4].green = 26;
    __utalCanvasColors[PURPLE_4].blue = 139;

    __utalCanvasColors[MEDIUMPURPLE].red = 147;
    __utalCanvasColors[MEDIUMPURPLE].green = 112;
    __utalCanvasColors[MEDIUMPURPLE].blue = 219;

    __utalCanvasColors[MEDIUMPURPLE_1].red = 171;
    __utalCanvasColors[MEDIUMPURPLE_1].green = 130;
    __utalCanvasColors[MEDIUMPURPLE_1].blue = 255;

    __utalCanvasColors[MEDIUMPURPLE_2].red = 159;
    __utalCanvasColors[MEDIUMPURPLE_2].green = 121;
    __utalCanvasColors[MEDIUMPURPLE_2].blue = 238;

    __utalCanvasColors[MEDIUMPURPLE_3].red = 137;
    __utalCanvasColors[MEDIUMPURPLE_3].green = 104;
    __utalCanvasColors[MEDIUMPURPLE_3].blue = 205;

    __utalCanvasColors[MEDIUMPURPLE_4].red = 93;
    __utalCanvasColors[MEDIUMPURPLE_4].green = 71;
    __utalCanvasColors[MEDIUMPURPLE_4].blue = 139;

    __utalCanvasColors[DARKSLATEBLUE].red = 72;
    __utalCanvasColors[DARKSLATEBLUE].green = 61;
    __utalCanvasColors[DARKSLATEBLUE].blue = 139;

    __utalCanvasColors[LIGHTSLATEBLUE].red = 132;
    __utalCanvasColors[LIGHTSLATEBLUE].green = 112;
    __utalCanvasColors[LIGHTSLATEBLUE].blue = 255;

    __utalCanvasColors[MEDIUMSLATEBLUE].red = 123;
    __utalCanvasColors[MEDIUMSLATEBLUE].green = 104;
    __utalCanvasColors[MEDIUMSLATEBLUE].blue = 238;

    __utalCanvasColors[SLATEBLUE].red = 106;
    __utalCanvasColors[SLATEBLUE].green = 90;
    __utalCanvasColors[SLATEBLUE].blue = 205;

    __utalCanvasColors[SLATEBLUE_1].red = 131;
    __utalCanvasColors[SLATEBLUE_1].green = 111;
    __utalCanvasColors[SLATEBLUE_1].blue = 255;

    __utalCanvasColors[SLATEBLUE_2].red = 122;
    __utalCanvasColors[SLATEBLUE_2].green = 103;
    __utalCanvasColors[SLATEBLUE_2].blue = 238;

    __utalCanvasColors[SLATEBLUE_3].red = 105;
    __utalCanvasColors[SLATEBLUE_3].green = 89;
    __utalCanvasColors[SLATEBLUE_3].blue = 205;

    __utalCanvasColors[SLATEBLUE_4].red = 71;
    __utalCanvasColors[SLATEBLUE_4].green = 60;
    __utalCanvasColors[SLATEBLUE_4].blue = 139;

    __utalCanvasColors[GHOSTWHITE].red = 248;
    __utalCanvasColors[GHOSTWHITE].green = 248;
    __utalCanvasColors[GHOSTWHITE].blue = 255;

    __utalCanvasColors[LAVENDER].red = 230;
    __utalCanvasColors[LAVENDER].green = 230;
    __utalCanvasColors[LAVENDER].blue = 250;

    __utalCanvasColors[BLUE].red = 0;
    __utalCanvasColors[BLUE].green = 0;
    __utalCanvasColors[BLUE].blue = 255;

    __utalCanvasColors[BLUE_2].red = 0;
    __utalCanvasColors[BLUE_2].green = 0;
    __utalCanvasColors[BLUE_2].blue = 238;

    __utalCanvasColors[BLUE_3].red = 0;
    __utalCanvasColors[BLUE_3].green = 0;
    __utalCanvasColors[BLUE_3].blue = 205;

    __utalCanvasColors[BLUE_4].red = 0;
    __utalCanvasColors[BLUE_4].green = 0;
    __utalCanvasColors[BLUE_4].blue = 139;

    __utalCanvasColors[NAVY].red = 0;
    __utalCanvasColors[NAVY].green = 0;
    __utalCanvasColors[NAVY].blue = 128;

    __utalCanvasColors[MIDNIGHTBLUE].red = 25;
    __utalCanvasColors[MIDNIGHTBLUE].green = 25;
    __utalCanvasColors[MIDNIGHTBLUE].blue = 112;

    __utalCanvasColors[COBALT].red = 61;
    __utalCanvasColors[COBALT].green = 89;
    __utalCanvasColors[COBALT].blue = 171;

    __utalCanvasColors[ROYALBLUE].red = 65;
    __utalCanvasColors[ROYALBLUE].green = 105;
    __utalCanvasColors[ROYALBLUE].blue = 225;

    __utalCanvasColors[ROYALBLUE_1].red = 72;
    __utalCanvasColors[ROYALBLUE_1].green = 118;
    __utalCanvasColors[ROYALBLUE_1].blue = 255;

    __utalCanvasColors[ROYALBLUE_2].red = 67;
    __utalCanvasColors[ROYALBLUE_2].green = 110;
    __utalCanvasColors[ROYALBLUE_2].blue = 238;

    __utalCanvasColors[ROYALBLUE_3].red = 58;
    __utalCanvasColors[ROYALBLUE_3].green = 95;
    __utalCanvasColors[ROYALBLUE_3].blue = 205;

    __utalCanvasColors[ROYALBLUE_4].red = 39;
    __utalCanvasColors[ROYALBLUE_4].green = 64;
    __utalCanvasColors[ROYALBLUE_4].blue = 139;

    __utalCanvasColors[CORNFLOWERBLUE].red = 100;
    __utalCanvasColors[CORNFLOWERBLUE].green = 149;
    __utalCanvasColors[CORNFLOWERBLUE].blue = 237;

    __utalCanvasColors[LIGHTSTEELBLUE].red = 176;
    __utalCanvasColors[LIGHTSTEELBLUE].green = 196;
    __utalCanvasColors[LIGHTSTEELBLUE].blue = 222;

    __utalCanvasColors[LIGHTSTEELBLUE_1].red = 202;
    __utalCanvasColors[LIGHTSTEELBLUE_1].green = 225;
    __utalCanvasColors[LIGHTSTEELBLUE_1].blue = 255;

    __utalCanvasColors[LIGHTSTEELBLUE_2].red = 188;
    __utalCanvasColors[LIGHTSTEELBLUE_2].green = 210;
    __utalCanvasColors[LIGHTSTEELBLUE_2].blue = 238;

    __utalCanvasColors[LIGHTSTEELBLUE_3].red = 162;
    __utalCanvasColors[LIGHTSTEELBLUE_3].green = 181;
    __utalCanvasColors[LIGHTSTEELBLUE_3].blue = 205;

    __utalCanvasColors[LIGHTSTEELBLUE_4].red = 110;
    __utalCanvasColors[LIGHTSTEELBLUE_4].green = 123;
    __utalCanvasColors[LIGHTSTEELBLUE_4].blue = 139;

    __utalCanvasColors[LIGHTSLATEGRAY].red = 119;
    __utalCanvasColors[LIGHTSLATEGRAY].green = 136;
    __utalCanvasColors[LIGHTSLATEGRAY].blue = 153;

    __utalCanvasColors[SLATEGRAY].red = 112;
    __utalCanvasColors[SLATEGRAY].green = 128;
    __utalCanvasColors[SLATEGRAY].blue = 144;

    __utalCanvasColors[SLATEGRAY_1].red = 198;
    __utalCanvasColors[SLATEGRAY_1].green = 226;
    __utalCanvasColors[SLATEGRAY_1].blue = 255;

    __utalCanvasColors[SLATEGRAY_2].red = 185;
    __utalCanvasColors[SLATEGRAY_2].green = 211;
    __utalCanvasColors[SLATEGRAY_2].blue = 238;

    __utalCanvasColors[SLATEGRAY_3].red = 159;
    __utalCanvasColors[SLATEGRAY_3].green = 182;
    __utalCanvasColors[SLATEGRAY_3].blue = 205;

    __utalCanvasColors[SLATEGRAY_4].red = 108;
    __utalCanvasColors[SLATEGRAY_4].green = 123;
    __utalCanvasColors[SLATEGRAY_4].blue = 139;

    __utalCanvasColors[DODGERBLUE_1].red = 30;
    __utalCanvasColors[DODGERBLUE_1].green = 144;
    __utalCanvasColors[DODGERBLUE_1].blue = 255;

    __utalCanvasColors[DODGERBLUE_2].red = 28;
    __utalCanvasColors[DODGERBLUE_2].green = 134;
    __utalCanvasColors[DODGERBLUE_2].blue = 238;

    __utalCanvasColors[DODGERBLUE_3].red = 24;
    __utalCanvasColors[DODGERBLUE_3].green = 116;
    __utalCanvasColors[DODGERBLUE_3].blue = 205;

    __utalCanvasColors[DODGERBLUE_4].red = 16;
    __utalCanvasColors[DODGERBLUE_4].green = 78;
    __utalCanvasColors[DODGERBLUE_4].blue = 139;

    __utalCanvasColors[ALICEBLUE].red = 240;
    __utalCanvasColors[ALICEBLUE].green = 248;
    __utalCanvasColors[ALICEBLUE].blue = 255;

    __utalCanvasColors[STEELBLUE].red = 70;
    __utalCanvasColors[STEELBLUE].green = 130;
    __utalCanvasColors[STEELBLUE].blue = 180;

    __utalCanvasColors[STEELBLUE_1].red = 99;
    __utalCanvasColors[STEELBLUE_1].green = 184;
    __utalCanvasColors[STEELBLUE_1].blue = 255;

    __utalCanvasColors[STEELBLUE_2].red = 92;
    __utalCanvasColors[STEELBLUE_2].green = 172;
    __utalCanvasColors[STEELBLUE_2].blue = 238;

    __utalCanvasColors[STEELBLUE_3].red = 79;
    __utalCanvasColors[STEELBLUE_3].green = 148;
    __utalCanvasColors[STEELBLUE_3].blue = 205;

    __utalCanvasColors[STEELBLUE_4].red = 54;
    __utalCanvasColors[STEELBLUE_4].green = 100;
    __utalCanvasColors[STEELBLUE_4].blue = 139;

    __utalCanvasColors[LIGHTSKYBLUE].red = 135;
    __utalCanvasColors[LIGHTSKYBLUE].green = 206;
    __utalCanvasColors[LIGHTSKYBLUE].blue = 250;

    __utalCanvasColors[LIGHTSKYBLUE_1].red = 176;
    __utalCanvasColors[LIGHTSKYBLUE_1].green = 226;
    __utalCanvasColors[LIGHTSKYBLUE_1].blue = 255;

    __utalCanvasColors[LIGHTSKYBLUE_2].red = 164;
    __utalCanvasColors[LIGHTSKYBLUE_2].green = 211;
    __utalCanvasColors[LIGHTSKYBLUE_2].blue = 238;

    __utalCanvasColors[LIGHTSKYBLUE_3].red = 141;
    __utalCanvasColors[LIGHTSKYBLUE_3].green = 182;
    __utalCanvasColors[LIGHTSKYBLUE_3].blue = 205;

    __utalCanvasColors[LIGHTSKYBLUE_4].red = 96;
    __utalCanvasColors[LIGHTSKYBLUE_4].green = 123;
    __utalCanvasColors[LIGHTSKYBLUE_4].blue = 139;

    __utalCanvasColors[SKYBLUE_1].red = 135;
    __utalCanvasColors[SKYBLUE_1].green = 206;
    __utalCanvasColors[SKYBLUE_1].blue = 255;

    __utalCanvasColors[SKYBLUE_2].red = 126;
    __utalCanvasColors[SKYBLUE_2].green = 192;
    __utalCanvasColors[SKYBLUE_2].blue = 238;

    __utalCanvasColors[SKYBLUE_3].red = 108;
    __utalCanvasColors[SKYBLUE_3].green = 166;
    __utalCanvasColors[SKYBLUE_3].blue = 205;

    __utalCanvasColors[SKYBLUE_4].red = 74;
    __utalCanvasColors[SKYBLUE_4].green = 112;
    __utalCanvasColors[SKYBLUE_4].blue = 139;

    __utalCanvasColors[SKYBLUE].red = 135;
    __utalCanvasColors[SKYBLUE].green = 206;
    __utalCanvasColors[SKYBLUE].blue = 235;

    __utalCanvasColors[DEEPSKYBLUE_1].red = 0;
    __utalCanvasColors[DEEPSKYBLUE_1].green = 191;
    __utalCanvasColors[DEEPSKYBLUE_1].blue = 255;

    __utalCanvasColors[DEEPSKYBLUE_2].red = 0;
    __utalCanvasColors[DEEPSKYBLUE_2].green = 178;
    __utalCanvasColors[DEEPSKYBLUE_2].blue = 238;

    __utalCanvasColors[DEEPSKYBLUE_3].red = 0;
    __utalCanvasColors[DEEPSKYBLUE_3].green = 154;
    __utalCanvasColors[DEEPSKYBLUE_3].blue = 205;

    __utalCanvasColors[DEEPSKYBLUE_4].red = 0;
    __utalCanvasColors[DEEPSKYBLUE_4].green = 104;
    __utalCanvasColors[DEEPSKYBLUE_4].blue = 139;

    __utalCanvasColors[PEACOCK].red = 51;
    __utalCanvasColors[PEACOCK].green = 161;
    __utalCanvasColors[PEACOCK].blue = 201;

    __utalCanvasColors[LIGHTBLUE].red = 173;
    __utalCanvasColors[LIGHTBLUE].green = 216;
    __utalCanvasColors[LIGHTBLUE].blue = 230;

    __utalCanvasColors[LIGHTBLUE_1].red = 191;
    __utalCanvasColors[LIGHTBLUE_1].green = 239;
    __utalCanvasColors[LIGHTBLUE_1].blue = 255;

    __utalCanvasColors[LIGHTBLUE_2].red = 178;
    __utalCanvasColors[LIGHTBLUE_2].green = 223;
    __utalCanvasColors[LIGHTBLUE_2].blue = 238;

    __utalCanvasColors[LIGHTBLUE_3].red = 154;
    __utalCanvasColors[LIGHTBLUE_3].green = 192;
    __utalCanvasColors[LIGHTBLUE_3].blue = 205;

    __utalCanvasColors[LIGHTBLUE_4].red = 104;
    __utalCanvasColors[LIGHTBLUE_4].green = 131;
    __utalCanvasColors[LIGHTBLUE_4].blue = 139;

    __utalCanvasColors[POWDERBLUE].red = 176;
    __utalCanvasColors[POWDERBLUE].green = 224;
    __utalCanvasColors[POWDERBLUE].blue = 230;

    __utalCanvasColors[CADETBLUE_1].red = 152;
    __utalCanvasColors[CADETBLUE_1].green = 245;
    __utalCanvasColors[CADETBLUE_1].blue = 255;

    __utalCanvasColors[CADETBLUE_2].red = 142;
    __utalCanvasColors[CADETBLUE_2].green = 229;
    __utalCanvasColors[CADETBLUE_2].blue = 238;

    __utalCanvasColors[CADETBLUE_3].red = 122;
    __utalCanvasColors[CADETBLUE_3].green = 197;
    __utalCanvasColors[CADETBLUE_3].blue = 205;

    __utalCanvasColors[CADETBLUE_4].red = 83;
    __utalCanvasColors[CADETBLUE_4].green = 134;
    __utalCanvasColors[CADETBLUE_4].blue = 139;

    __utalCanvasColors[TURQUOISE_1].red = 0;
    __utalCanvasColors[TURQUOISE_1].green = 245;
    __utalCanvasColors[TURQUOISE_1].blue = 255;

    __utalCanvasColors[TURQUOISE_2].red = 0;
    __utalCanvasColors[TURQUOISE_2].green = 229;
    __utalCanvasColors[TURQUOISE_2].blue = 238;

    __utalCanvasColors[TURQUOISE_3].red = 0;
    __utalCanvasColors[TURQUOISE_3].green = 197;
    __utalCanvasColors[TURQUOISE_3].blue = 205;

    __utalCanvasColors[TURQUOISE_4].red = 0;
    __utalCanvasColors[TURQUOISE_4].green = 134;
    __utalCanvasColors[TURQUOISE_4].blue = 139;

    __utalCanvasColors[CADETBLUE].red = 95;
    __utalCanvasColors[CADETBLUE].green = 158;
    __utalCanvasColors[CADETBLUE].blue = 160;

    __utalCanvasColors[DARKTURQUOISE].red = 0;
    __utalCanvasColors[DARKTURQUOISE].green = 206;
    __utalCanvasColors[DARKTURQUOISE].blue = 209;

    __utalCanvasColors[AZURE_1].red = 240;
    __utalCanvasColors[AZURE_1].green = 255;
    __utalCanvasColors[AZURE_1].blue = 255;

    __utalCanvasColors[AZURE_2].red = 224;
    __utalCanvasColors[AZURE_2].green = 238;
    __utalCanvasColors[AZURE_2].blue = 238;

    __utalCanvasColors[AZURE_3].red = 193;
    __utalCanvasColors[AZURE_3].green = 205;
    __utalCanvasColors[AZURE_3].blue = 205;

    __utalCanvasColors[AZURE_4].red = 131;
    __utalCanvasColors[AZURE_4].green = 139;
    __utalCanvasColors[AZURE_4].blue = 139;

    __utalCanvasColors[LIGHTCYAN_1].red = 224;
    __utalCanvasColors[LIGHTCYAN_1].green = 255;
    __utalCanvasColors[LIGHTCYAN_1].blue = 255;

    __utalCanvasColors[LIGHTCYAN_2].red = 209;
    __utalCanvasColors[LIGHTCYAN_2].green = 238;
    __utalCanvasColors[LIGHTCYAN_2].blue = 238;

    __utalCanvasColors[LIGHTCYAN_3].red = 180;
    __utalCanvasColors[LIGHTCYAN_3].green = 205;
    __utalCanvasColors[LIGHTCYAN_3].blue = 205;

    __utalCanvasColors[LIGHTCYAN_4].red = 122;
    __utalCanvasColors[LIGHTCYAN_4].green = 139;
    __utalCanvasColors[LIGHTCYAN_4].blue = 139;

    __utalCanvasColors[PALETURQUOISE_1].red = 187;
    __utalCanvasColors[PALETURQUOISE_1].green = 255;
    __utalCanvasColors[PALETURQUOISE_1].blue = 255;

    __utalCanvasColors[PALETURQUOISE_2].red = 174;
    __utalCanvasColors[PALETURQUOISE_2].green = 238;
    __utalCanvasColors[PALETURQUOISE_2].blue = 238;

    __utalCanvasColors[PALETURQUOISE_3].red = 150;
    __utalCanvasColors[PALETURQUOISE_3].green = 205;
    __utalCanvasColors[PALETURQUOISE_3].blue = 205;

    __utalCanvasColors[PALETURQUOISE_4].red = 102;
    __utalCanvasColors[PALETURQUOISE_4].green = 139;
    __utalCanvasColors[PALETURQUOISE_4].blue = 139;

    __utalCanvasColors[DARKSLATEGRAY].red = 47;
    __utalCanvasColors[DARKSLATEGRAY].green = 79;
    __utalCanvasColors[DARKSLATEGRAY].blue = 79;

    __utalCanvasColors[DARKSLATEGRAY_1].red = 151;
    __utalCanvasColors[DARKSLATEGRAY_1].green = 255;
    __utalCanvasColors[DARKSLATEGRAY_1].blue = 255;

    __utalCanvasColors[DARKSLATEGRAY_2].red = 141;
    __utalCanvasColors[DARKSLATEGRAY_2].green = 238;
    __utalCanvasColors[DARKSLATEGRAY_2].blue = 238;

    __utalCanvasColors[DARKSLATEGRAY_3].red = 121;
    __utalCanvasColors[DARKSLATEGRAY_3].green = 205;
    __utalCanvasColors[DARKSLATEGRAY_3].blue = 205;

    __utalCanvasColors[DARKSLATEGRAY_4].red = 82;
    __utalCanvasColors[DARKSLATEGRAY_4].green = 139;
    __utalCanvasColors[DARKSLATEGRAY_4].blue = 139;

    __utalCanvasColors[CYAN].red = 0;
    __utalCanvasColors[CYAN].green = 255;
    __utalCanvasColors[CYAN].blue = 255;

    __utalCanvasColors[CYAN_2].red = 0;
    __utalCanvasColors[CYAN_2].green = 238;
    __utalCanvasColors[CYAN_2].blue = 238;

    __utalCanvasColors[CYAN_3].red = 0;
    __utalCanvasColors[CYAN_3].green = 205;
    __utalCanvasColors[CYAN_3].blue = 205;

    __utalCanvasColors[CYAN_4].red = 0;
    __utalCanvasColors[CYAN_4].green = 139;
    __utalCanvasColors[CYAN_4].blue = 139;

    __utalCanvasColors[TEAL].red = 0;
    __utalCanvasColors[TEAL].green = 128;
    __utalCanvasColors[TEAL].blue = 128;

    __utalCanvasColors[MEDIUMTURQUOISE].red = 72;
    __utalCanvasColors[MEDIUMTURQUOISE].green = 209;
    __utalCanvasColors[MEDIUMTURQUOISE].blue = 204;

    __utalCanvasColors[LIGHTSEAGREEN].red = 32;
    __utalCanvasColors[LIGHTSEAGREEN].green = 178;
    __utalCanvasColors[LIGHTSEAGREEN].blue = 170;

    __utalCanvasColors[MANGANESEBLUE].red = 3;
    __utalCanvasColors[MANGANESEBLUE].green = 168;
    __utalCanvasColors[MANGANESEBLUE].blue = 158;

    __utalCanvasColors[TURQUOISE].red = 64;
    __utalCanvasColors[TURQUOISE].green = 224;
    __utalCanvasColors[TURQUOISE].blue = 208;

    __utalCanvasColors[COLDGREY].red = 128;
    __utalCanvasColors[COLDGREY].green = 138;
    __utalCanvasColors[COLDGREY].blue = 135;

    __utalCanvasColors[TURQUOISEBLUE].red = 0;
    __utalCanvasColors[TURQUOISEBLUE].green = 199;
    __utalCanvasColors[TURQUOISEBLUE].blue = 140;

    __utalCanvasColors[AQUAMARINE_1].red = 127;
    __utalCanvasColors[AQUAMARINE_1].green = 255;
    __utalCanvasColors[AQUAMARINE_1].blue = 212;

    __utalCanvasColors[AQUAMARINE_2].red = 118;
    __utalCanvasColors[AQUAMARINE_2].green = 238;
    __utalCanvasColors[AQUAMARINE_2].blue = 198;

    __utalCanvasColors[AQUAMARINE_3].red = 102;
    __utalCanvasColors[AQUAMARINE_3].green = 205;
    __utalCanvasColors[AQUAMARINE_3].blue = 170;

    __utalCanvasColors[AQUAMARINE_4].red = 69;
    __utalCanvasColors[AQUAMARINE_4].green = 139;
    __utalCanvasColors[AQUAMARINE_4].blue = 116;

    __utalCanvasColors[MEDIUMSPRINGGREEN].red = 0;
    __utalCanvasColors[MEDIUMSPRINGGREEN].green = 250;
    __utalCanvasColors[MEDIUMSPRINGGREEN].blue = 154;

    __utalCanvasColors[MINTCREAM].red = 245;
    __utalCanvasColors[MINTCREAM].green = 255;
    __utalCanvasColors[MINTCREAM].blue = 250;

    __utalCanvasColors[SPRINGGREEN].red = 0;
    __utalCanvasColors[SPRINGGREEN].green = 255;
    __utalCanvasColors[SPRINGGREEN].blue = 127;

    __utalCanvasColors[SPRINGGREEN_1].red = 0;
    __utalCanvasColors[SPRINGGREEN_1].green = 238;
    __utalCanvasColors[SPRINGGREEN_1].blue = 118;

    __utalCanvasColors[SPRINGGREEN_2].red = 0;
    __utalCanvasColors[SPRINGGREEN_2].green = 205;
    __utalCanvasColors[SPRINGGREEN_2].blue = 102;

    __utalCanvasColors[SPRINGGREEN_3].red = 0;
    __utalCanvasColors[SPRINGGREEN_3].green = 139;
    __utalCanvasColors[SPRINGGREEN_3].blue = 69;

    __utalCanvasColors[MEDIUMSEAGREEN].red = 60;
    __utalCanvasColors[MEDIUMSEAGREEN].green = 179;
    __utalCanvasColors[MEDIUMSEAGREEN].blue = 113;

    __utalCanvasColors[SEAGREEN_1].red = 84;
    __utalCanvasColors[SEAGREEN_1].green = 255;
    __utalCanvasColors[SEAGREEN_1].blue = 159;

    __utalCanvasColors[SEAGREEN_2].red = 78;
    __utalCanvasColors[SEAGREEN_2].green = 238;
    __utalCanvasColors[SEAGREEN_2].blue = 148;

    __utalCanvasColors[SEAGREEN_3].red = 67;
    __utalCanvasColors[SEAGREEN_3].green = 205;
    __utalCanvasColors[SEAGREEN_3].blue = 128;

    __utalCanvasColors[SEAGREEN_4].red = 46;
    __utalCanvasColors[SEAGREEN_4].green = 139;
    __utalCanvasColors[SEAGREEN_4].blue = 87;

    __utalCanvasColors[EMERALDGREEN].red = 0;
    __utalCanvasColors[EMERALDGREEN].green = 201;
    __utalCanvasColors[EMERALDGREEN].blue = 87;

    __utalCanvasColors[MINT].red = 189;
    __utalCanvasColors[MINT].green = 252;
    __utalCanvasColors[MINT].blue = 201;

    __utalCanvasColors[COBALTGREEN].red = 61;
    __utalCanvasColors[COBALTGREEN].green = 145;
    __utalCanvasColors[COBALTGREEN].blue = 64;

    __utalCanvasColors[HONEYDEW_1].red = 240;
    __utalCanvasColors[HONEYDEW_1].green = 255;
    __utalCanvasColors[HONEYDEW_1].blue = 240;

    __utalCanvasColors[HONEYDEW_2].red = 224;
    __utalCanvasColors[HONEYDEW_2].green = 238;
    __utalCanvasColors[HONEYDEW_2].blue = 224;

    __utalCanvasColors[HONEYDEW_3].red = 193;
    __utalCanvasColors[HONEYDEW_3].green = 205;
    __utalCanvasColors[HONEYDEW_3].blue = 193;

    __utalCanvasColors[HONEYDEW_4].red = 131;
    __utalCanvasColors[HONEYDEW_4].green = 139;
    __utalCanvasColors[HONEYDEW_4].blue = 131;

    __utalCanvasColors[DARKSEAGREEN].red = 143;
    __utalCanvasColors[DARKSEAGREEN].green = 188;
    __utalCanvasColors[DARKSEAGREEN].blue = 143;

    __utalCanvasColors[DARKSEAGREEN_1].red = 193;
    __utalCanvasColors[DARKSEAGREEN_1].green = 255;
    __utalCanvasColors[DARKSEAGREEN_1].blue = 193;

    __utalCanvasColors[DARKSEAGREEN_2].red = 180;
    __utalCanvasColors[DARKSEAGREEN_2].green = 238;
    __utalCanvasColors[DARKSEAGREEN_2].blue = 180;

    __utalCanvasColors[DARKSEAGREEN_3].red = 155;
    __utalCanvasColors[DARKSEAGREEN_3].green = 205;
    __utalCanvasColors[DARKSEAGREEN_3].blue = 155;

    __utalCanvasColors[DARKSEAGREEN_4].red = 105;
    __utalCanvasColors[DARKSEAGREEN_4].green = 139;
    __utalCanvasColors[DARKSEAGREEN_4].blue = 105;

    __utalCanvasColors[PALEGREEN].red = 152;
    __utalCanvasColors[PALEGREEN].green = 251;
    __utalCanvasColors[PALEGREEN].blue = 152;

    __utalCanvasColors[PALEGREEN_1].red = 154;
    __utalCanvasColors[PALEGREEN_1].green = 255;
    __utalCanvasColors[PALEGREEN_1].blue = 154;

    __utalCanvasColors[PALEGREEN_2].red = 144;
    __utalCanvasColors[PALEGREEN_2].green = 238;
    __utalCanvasColors[PALEGREEN_2].blue = 144;

    __utalCanvasColors[PALEGREEN_3].red = 124;
    __utalCanvasColors[PALEGREEN_3].green = 205;
    __utalCanvasColors[PALEGREEN_3].blue = 124;

    __utalCanvasColors[PALEGREEN_4].red = 84;
    __utalCanvasColors[PALEGREEN_4].green = 139;
    __utalCanvasColors[PALEGREEN_4].blue = 84;

    __utalCanvasColors[LIMEGREEN].red = 50;
    __utalCanvasColors[LIMEGREEN].green = 205;
    __utalCanvasColors[LIMEGREEN].blue = 50;

    __utalCanvasColors[FORESTGREEN].red = 34;
    __utalCanvasColors[FORESTGREEN].green = 139;
    __utalCanvasColors[FORESTGREEN].blue = 34;

    __utalCanvasColors[GREEN_1].red = 0;
    __utalCanvasColors[GREEN_1].green = 255;
    __utalCanvasColors[GREEN_1].blue = 0;

    __utalCanvasColors[GREEN_2].red = 0;
    __utalCanvasColors[GREEN_2].green = 238;
    __utalCanvasColors[GREEN_2].blue = 0;

    __utalCanvasColors[GREEN_3].red = 0;
    __utalCanvasColors[GREEN_3].green = 205;
    __utalCanvasColors[GREEN_3].blue = 0;

    __utalCanvasColors[GREEN_4].red = 0;
    __utalCanvasColors[GREEN_4].green = 139;
    __utalCanvasColors[GREEN_4].blue = 0;

    __utalCanvasColors[GREEN].red = 0;
    __utalCanvasColors[GREEN].green = 128;
    __utalCanvasColors[GREEN].blue = 0;

    __utalCanvasColors[DARKGREEN].red = 0;
    __utalCanvasColors[DARKGREEN].green = 100;
    __utalCanvasColors[DARKGREEN].blue = 0;

    __utalCanvasColors[SAPGREEN].red = 48;
    __utalCanvasColors[SAPGREEN].green = 128;
    __utalCanvasColors[SAPGREEN].blue = 20;

    __utalCanvasColors[LAWNGREEN].red = 124;
    __utalCanvasColors[LAWNGREEN].green = 252;
    __utalCanvasColors[LAWNGREEN].blue = 0;

    __utalCanvasColors[CHARTREUSE_1].red = 127;
    __utalCanvasColors[CHARTREUSE_1].green = 255;
    __utalCanvasColors[CHARTREUSE_1].blue = 0;

    __utalCanvasColors[CHARTREUSE_2].red = 118;
    __utalCanvasColors[CHARTREUSE_2].green = 238;
    __utalCanvasColors[CHARTREUSE_2].blue = 0;

    __utalCanvasColors[CHARTREUSE_3].red = 102;
    __utalCanvasColors[CHARTREUSE_3].green = 205;
    __utalCanvasColors[CHARTREUSE_3].blue = 0;

    __utalCanvasColors[CHARTREUSE_4].red = 69;
    __utalCanvasColors[CHARTREUSE_4].green = 139;
    __utalCanvasColors[CHARTREUSE_4].blue = 0;

    __utalCanvasColors[GREENYELLOW].red = 173;
    __utalCanvasColors[GREENYELLOW].green = 255;
    __utalCanvasColors[GREENYELLOW].blue = 47;

    __utalCanvasColors[DARKOLIVEGREEN_1].red = 202;
    __utalCanvasColors[DARKOLIVEGREEN_1].green = 255;
    __utalCanvasColors[DARKOLIVEGREEN_1].blue = 112;

    __utalCanvasColors[DARKOLIVEGREEN_2].red = 188;
    __utalCanvasColors[DARKOLIVEGREEN_2].green = 238;
    __utalCanvasColors[DARKOLIVEGREEN_2].blue = 104;

    __utalCanvasColors[DARKOLIVEGREEN_3].red = 162;
    __utalCanvasColors[DARKOLIVEGREEN_3].green = 205;
    __utalCanvasColors[DARKOLIVEGREEN_3].blue = 90;

    __utalCanvasColors[DARKOLIVEGREEN_4].red = 110;
    __utalCanvasColors[DARKOLIVEGREEN_4].green = 139;
    __utalCanvasColors[DARKOLIVEGREEN_4].blue = 61;

    __utalCanvasColors[DARKOLIVEGREEN].red = 85;
    __utalCanvasColors[DARKOLIVEGREEN].green = 107;
    __utalCanvasColors[DARKOLIVEGREEN].blue = 47;

    __utalCanvasColors[OLIVEDRAB].red = 107;
    __utalCanvasColors[OLIVEDRAB].green = 142;
    __utalCanvasColors[OLIVEDRAB].blue = 35;

    __utalCanvasColors[OLIVEDRAB_1].red = 192;
    __utalCanvasColors[OLIVEDRAB_1].green = 255;
    __utalCanvasColors[OLIVEDRAB_1].blue = 62;

    __utalCanvasColors[OLIVEDRAB_2].red = 179;
    __utalCanvasColors[OLIVEDRAB_2].green = 238;
    __utalCanvasColors[OLIVEDRAB_2].blue = 58;

    __utalCanvasColors[OLIVEDRAB_3].red = 154;
    __utalCanvasColors[OLIVEDRAB_3].green = 205;
    __utalCanvasColors[OLIVEDRAB_3].blue = 50;

    __utalCanvasColors[OLIVEDRAB_4].red = 105;
    __utalCanvasColors[OLIVEDRAB_4].green = 139;
    __utalCanvasColors[OLIVEDRAB_4].blue = 34;

    __utalCanvasColors[IVORY_1].red = 255;
    __utalCanvasColors[IVORY_1].green = 255;
    __utalCanvasColors[IVORY_1].blue = 240;

    __utalCanvasColors[IVORY_2].red = 238;
    __utalCanvasColors[IVORY_2].green = 238;
    __utalCanvasColors[IVORY_2].blue = 224;

    __utalCanvasColors[IVORY_3].red = 205;
    __utalCanvasColors[IVORY_3].green = 205;
    __utalCanvasColors[IVORY_3].blue = 193;

    __utalCanvasColors[IVORY_4].red = 139;
    __utalCanvasColors[IVORY_4].green = 139;
    __utalCanvasColors[IVORY_4].blue = 131;

    __utalCanvasColors[BEIGE].red = 245;
    __utalCanvasColors[BEIGE].green = 245;
    __utalCanvasColors[BEIGE].blue = 220;

    __utalCanvasColors[LIGHTYELLOW_1].red = 255;
    __utalCanvasColors[LIGHTYELLOW_1].green = 255;
    __utalCanvasColors[LIGHTYELLOW_1].blue = 224;

    __utalCanvasColors[LIGHTYELLOW_2].red = 238;
    __utalCanvasColors[LIGHTYELLOW_2].green = 238;
    __utalCanvasColors[LIGHTYELLOW_2].blue = 209;

    __utalCanvasColors[LIGHTYELLOW_3].red = 205;
    __utalCanvasColors[LIGHTYELLOW_3].green = 205;
    __utalCanvasColors[LIGHTYELLOW_3].blue = 180;

    __utalCanvasColors[LIGHTYELLOW_4].red = 139;
    __utalCanvasColors[LIGHTYELLOW_4].green = 139;
    __utalCanvasColors[LIGHTYELLOW_4].blue = 122;

    __utalCanvasColors[LIGHTGOLDENRODYELLOW].red = 250;
    __utalCanvasColors[LIGHTGOLDENRODYELLOW].green = 250;
    __utalCanvasColors[LIGHTGOLDENRODYELLOW].blue = 210;

    __utalCanvasColors[YELLOW_1].red = 255;
    __utalCanvasColors[YELLOW_1].green = 255;
    __utalCanvasColors[YELLOW_1].blue = 0;

    __utalCanvasColors[YELLOW_2].red = 238;
    __utalCanvasColors[YELLOW_2].green = 238;
    __utalCanvasColors[YELLOW_2].blue = 0;

    __utalCanvasColors[YELLOW_3].red = 205;
    __utalCanvasColors[YELLOW_3].green = 205;
    __utalCanvasColors[YELLOW_3].blue = 0;

    __utalCanvasColors[YELLOW_4].red = 139;
    __utalCanvasColors[YELLOW_4].green = 139;
    __utalCanvasColors[YELLOW_4].blue = 0;

    __utalCanvasColors[WARMGREY].red = 128;
    __utalCanvasColors[WARMGREY].green = 128;
    __utalCanvasColors[WARMGREY].blue = 105;

    __utalCanvasColors[OLIVE].red = 128;
    __utalCanvasColors[OLIVE].green = 128;
    __utalCanvasColors[OLIVE].blue = 0;

    __utalCanvasColors[DARKKHAKI].red = 189;
    __utalCanvasColors[DARKKHAKI].green = 183;
    __utalCanvasColors[DARKKHAKI].blue = 107;

    __utalCanvasColors[KHAKI_1].red = 255;
    __utalCanvasColors[KHAKI_1].green = 246;
    __utalCanvasColors[KHAKI_1].blue = 143;

    __utalCanvasColors[KHAKI_2].red = 238;
    __utalCanvasColors[KHAKI_2].green = 230;
    __utalCanvasColors[KHAKI_2].blue = 133;

    __utalCanvasColors[KHAKI_3].red = 205;
    __utalCanvasColors[KHAKI_3].green = 198;
    __utalCanvasColors[KHAKI_3].blue = 115;

    __utalCanvasColors[KHAKI_4].red = 139;
    __utalCanvasColors[KHAKI_4].green = 134;
    __utalCanvasColors[KHAKI_4].blue = 78;

    __utalCanvasColors[KHAKI].red = 240;
    __utalCanvasColors[KHAKI].green = 230;
    __utalCanvasColors[KHAKI].blue = 140;

    __utalCanvasColors[PALEGOLDENROD].red = 238;
    __utalCanvasColors[PALEGOLDENROD].green = 232;
    __utalCanvasColors[PALEGOLDENROD].blue = 170;

    __utalCanvasColors[LEMONCHIFFON_1].red = 255;
    __utalCanvasColors[LEMONCHIFFON_1].green = 250;
    __utalCanvasColors[LEMONCHIFFON_1].blue = 205;

    __utalCanvasColors[LEMONCHIFFON_2].red = 238;
    __utalCanvasColors[LEMONCHIFFON_2].green = 233;
    __utalCanvasColors[LEMONCHIFFON_2].blue = 191;

    __utalCanvasColors[LEMONCHIFFON_3].red = 205;
    __utalCanvasColors[LEMONCHIFFON_3].green = 201;
    __utalCanvasColors[LEMONCHIFFON_3].blue = 165;

    __utalCanvasColors[LEMONCHIFFON_4].red = 139;
    __utalCanvasColors[LEMONCHIFFON_4].green = 137;
    __utalCanvasColors[LEMONCHIFFON_4].blue = 112;

    __utalCanvasColors[LIGHTGOLDENROD_1].red = 255;
    __utalCanvasColors[LIGHTGOLDENROD_1].green = 236;
    __utalCanvasColors[LIGHTGOLDENROD_1].blue = 139;

    __utalCanvasColors[LIGHTGOLDENROD_2].red = 238;
    __utalCanvasColors[LIGHTGOLDENROD_2].green = 220;
    __utalCanvasColors[LIGHTGOLDENROD_2].blue = 130;

    __utalCanvasColors[LIGHTGOLDENROD_3].red = 205;
    __utalCanvasColors[LIGHTGOLDENROD_3].green = 190;
    __utalCanvasColors[LIGHTGOLDENROD_3].blue = 112;

    __utalCanvasColors[LIGHTGOLDENROD_4].red = 139;
    __utalCanvasColors[LIGHTGOLDENROD_4].green = 129;
    __utalCanvasColors[LIGHTGOLDENROD_4].blue = 76;

    __utalCanvasColors[BANANA].red = 227;
    __utalCanvasColors[BANANA].green = 207;
    __utalCanvasColors[BANANA].blue = 87;

    __utalCanvasColors[GOLD_1].red = 255;
    __utalCanvasColors[GOLD_1].green = 215;
    __utalCanvasColors[GOLD_1].blue = 0;

    __utalCanvasColors[GOLD_2].red = 238;
    __utalCanvasColors[GOLD_2].green = 201;
    __utalCanvasColors[GOLD_2].blue = 0;

    __utalCanvasColors[GOLD_3].red = 205;
    __utalCanvasColors[GOLD_3].green = 173;
    __utalCanvasColors[GOLD_3].blue = 0;

    __utalCanvasColors[GOLD_4].red = 139;
    __utalCanvasColors[GOLD_4].green = 117;
    __utalCanvasColors[GOLD_4].blue = 0;

    __utalCanvasColors[CORNSILK_1].red = 255;
    __utalCanvasColors[CORNSILK_1].green = 248;
    __utalCanvasColors[CORNSILK_1].blue = 220;

    __utalCanvasColors[CORNSILK_2].red = 238;
    __utalCanvasColors[CORNSILK_2].green = 232;
    __utalCanvasColors[CORNSILK_2].blue = 205;

    __utalCanvasColors[CORNSILK_3].red = 205;
    __utalCanvasColors[CORNSILK_3].green = 200;
    __utalCanvasColors[CORNSILK_3].blue = 177;

    __utalCanvasColors[CORNSILK_4].red = 139;
    __utalCanvasColors[CORNSILK_4].green = 136;
    __utalCanvasColors[CORNSILK_4].blue = 120;

    __utalCanvasColors[GOLDENROD].red = 218;
    __utalCanvasColors[GOLDENROD].green = 165;
    __utalCanvasColors[GOLDENROD].blue = 32;

    __utalCanvasColors[GOLDENROD_1].red = 255;
    __utalCanvasColors[GOLDENROD_1].green = 193;
    __utalCanvasColors[GOLDENROD_1].blue = 37;

    __utalCanvasColors[GOLDENROD_2].red = 238;
    __utalCanvasColors[GOLDENROD_2].green = 180;
    __utalCanvasColors[GOLDENROD_2].blue = 34;

    __utalCanvasColors[GOLDENROD_3].red = 205;
    __utalCanvasColors[GOLDENROD_3].green = 155;
    __utalCanvasColors[GOLDENROD_3].blue = 29;

    __utalCanvasColors[GOLDENROD_4].red = 139;
    __utalCanvasColors[GOLDENROD_4].green = 105;
    __utalCanvasColors[GOLDENROD_4].blue = 20;

    __utalCanvasColors[DARKGOLDENROD].red = 184;
    __utalCanvasColors[DARKGOLDENROD].green = 134;
    __utalCanvasColors[DARKGOLDENROD].blue = 11;

    __utalCanvasColors[DARKGOLDENROD_1].red = 255;
    __utalCanvasColors[DARKGOLDENROD_1].green = 185;
    __utalCanvasColors[DARKGOLDENROD_1].blue = 15;

    __utalCanvasColors[DARKGOLDENROD_2].red = 238;
    __utalCanvasColors[DARKGOLDENROD_2].green = 173;
    __utalCanvasColors[DARKGOLDENROD_2].blue = 14;

    __utalCanvasColors[DARKGOLDENROD_3].red = 205;
    __utalCanvasColors[DARKGOLDENROD_3].green = 149;
    __utalCanvasColors[DARKGOLDENROD_3].blue = 12;

    __utalCanvasColors[DARKGOLDENROD_4].red = 139;
    __utalCanvasColors[DARKGOLDENROD_4].green = 101;
    __utalCanvasColors[DARKGOLDENROD_4].blue = 8;

    __utalCanvasColors[ORANGE_1].red = 255;
    __utalCanvasColors[ORANGE_1].green = 165;
    __utalCanvasColors[ORANGE_1].blue = 0;

    __utalCanvasColors[ORANGE_2].red = 238;
    __utalCanvasColors[ORANGE_2].green = 154;
    __utalCanvasColors[ORANGE_2].blue = 0;

    __utalCanvasColors[ORANGE_3].red = 205;
    __utalCanvasColors[ORANGE_3].green = 133;
    __utalCanvasColors[ORANGE_3].blue = 0;

    __utalCanvasColors[ORANGE_4].red = 139;
    __utalCanvasColors[ORANGE_4].green = 90;
    __utalCanvasColors[ORANGE_4].blue = 0;

    __utalCanvasColors[FLORALWHITE].red = 255;
    __utalCanvasColors[FLORALWHITE].green = 250;
    __utalCanvasColors[FLORALWHITE].blue = 240;

    __utalCanvasColors[OLDLACE].red = 253;
    __utalCanvasColors[OLDLACE].green = 245;
    __utalCanvasColors[OLDLACE].blue = 230;

    __utalCanvasColors[WHEAT].red = 245;
    __utalCanvasColors[WHEAT].green = 222;
    __utalCanvasColors[WHEAT].blue = 179;

    __utalCanvasColors[WHEAT_1].red = 255;
    __utalCanvasColors[WHEAT_1].green = 231;
    __utalCanvasColors[WHEAT_1].blue = 186;

    __utalCanvasColors[WHEAT_2].red = 238;
    __utalCanvasColors[WHEAT_2].green = 216;
    __utalCanvasColors[WHEAT_2].blue = 174;

    __utalCanvasColors[WHEAT_3].red = 205;
    __utalCanvasColors[WHEAT_3].green = 186;
    __utalCanvasColors[WHEAT_3].blue = 150;

    __utalCanvasColors[WHEAT_4].red = 139;
    __utalCanvasColors[WHEAT_4].green = 126;
    __utalCanvasColors[WHEAT_4].blue = 102;

    __utalCanvasColors[MOCCASIN].red = 255;
    __utalCanvasColors[MOCCASIN].green = 228;
    __utalCanvasColors[MOCCASIN].blue = 181;

    __utalCanvasColors[PAPAYAWHIP].red = 255;
    __utalCanvasColors[PAPAYAWHIP].green = 239;
    __utalCanvasColors[PAPAYAWHIP].blue = 213;

    __utalCanvasColors[BLANCHEDALMOND].red = 255;
    __utalCanvasColors[BLANCHEDALMOND].green = 235;
    __utalCanvasColors[BLANCHEDALMOND].blue = 205;

    __utalCanvasColors[NAVAJOWHITE_1].red = 255;
    __utalCanvasColors[NAVAJOWHITE_1].green = 222;
    __utalCanvasColors[NAVAJOWHITE_1].blue = 173;

    __utalCanvasColors[NAVAJOWHITE_2].red = 238;
    __utalCanvasColors[NAVAJOWHITE_2].green = 207;
    __utalCanvasColors[NAVAJOWHITE_2].blue = 161;

    __utalCanvasColors[NAVAJOWHITE_3].red = 205;
    __utalCanvasColors[NAVAJOWHITE_3].green = 179;
    __utalCanvasColors[NAVAJOWHITE_3].blue = 139;

    __utalCanvasColors[NAVAJOWHITE_4].red = 139;
    __utalCanvasColors[NAVAJOWHITE_4].green = 121;
    __utalCanvasColors[NAVAJOWHITE_4].blue = 94;

    __utalCanvasColors[EGGSHELL].red = 252;
    __utalCanvasColors[EGGSHELL].green = 230;
    __utalCanvasColors[EGGSHELL].blue = 201;

    __utalCanvasColors[TAN].red = 210;
    __utalCanvasColors[TAN].green = 180;
    __utalCanvasColors[TAN].blue = 140;

    __utalCanvasColors[BRICK].red = 156;
    __utalCanvasColors[BRICK].green = 102;
    __utalCanvasColors[BRICK].blue = 31;

    __utalCanvasColors[CADMIUMYELLOW].red = 255;
    __utalCanvasColors[CADMIUMYELLOW].green = 153;
    __utalCanvasColors[CADMIUMYELLOW].blue = 18;

    __utalCanvasColors[ANTIQUEWHITE].red = 250;
    __utalCanvasColors[ANTIQUEWHITE].green = 235;
    __utalCanvasColors[ANTIQUEWHITE].blue = 215;

    __utalCanvasColors[ANTIQUEWHITE_1].red = 255;
    __utalCanvasColors[ANTIQUEWHITE_1].green = 239;
    __utalCanvasColors[ANTIQUEWHITE_1].blue = 219;

    __utalCanvasColors[ANTIQUEWHITE_2].red = 238;
    __utalCanvasColors[ANTIQUEWHITE_2].green = 223;
    __utalCanvasColors[ANTIQUEWHITE_2].blue = 204;

    __utalCanvasColors[ANTIQUEWHITE_3].red = 205;
    __utalCanvasColors[ANTIQUEWHITE_3].green = 192;
    __utalCanvasColors[ANTIQUEWHITE_3].blue = 176;

    __utalCanvasColors[ANTIQUEWHITE_4].red = 139;
    __utalCanvasColors[ANTIQUEWHITE_4].green = 131;
    __utalCanvasColors[ANTIQUEWHITE_4].blue = 120;

    __utalCanvasColors[BURLYWOOD].red = 222;
    __utalCanvasColors[BURLYWOOD].green = 184;
    __utalCanvasColors[BURLYWOOD].blue = 135;

    __utalCanvasColors[BURLYWOOD_1].red = 255;
    __utalCanvasColors[BURLYWOOD_1].green = 211;
    __utalCanvasColors[BURLYWOOD_1].blue = 155;

    __utalCanvasColors[BURLYWOOD_2].red = 238;
    __utalCanvasColors[BURLYWOOD_2].green = 197;
    __utalCanvasColors[BURLYWOOD_2].blue = 145;

    __utalCanvasColors[BURLYWOOD_3].red = 205;
    __utalCanvasColors[BURLYWOOD_3].green = 170;
    __utalCanvasColors[BURLYWOOD_3].blue = 125;

    __utalCanvasColors[BURLYWOOD_4].red = 139;
    __utalCanvasColors[BURLYWOOD_4].green = 115;
    __utalCanvasColors[BURLYWOOD_4].blue = 85;

    __utalCanvasColors[BISQUE_1].red = 255;
    __utalCanvasColors[BISQUE_1].green = 228;
    __utalCanvasColors[BISQUE_1].blue = 196;

    __utalCanvasColors[BISQUE_2].red = 238;
    __utalCanvasColors[BISQUE_2].green = 213;
    __utalCanvasColors[BISQUE_2].blue = 183;

    __utalCanvasColors[BISQUE_3].red = 205;
    __utalCanvasColors[BISQUE_3].green = 183;
    __utalCanvasColors[BISQUE_3].blue = 158;

    __utalCanvasColors[BISQUE_4].red = 139;
    __utalCanvasColors[BISQUE_4].green = 125;
    __utalCanvasColors[BISQUE_4].blue = 107;

    __utalCanvasColors[MELON].red = 227;
    __utalCanvasColors[MELON].green = 168;
    __utalCanvasColors[MELON].blue = 105;

    __utalCanvasColors[CARROT].red = 237;
    __utalCanvasColors[CARROT].green = 145;
    __utalCanvasColors[CARROT].blue = 33;

    __utalCanvasColors[DARKORANGE].red = 255;
    __utalCanvasColors[DARKORANGE].green = 140;
    __utalCanvasColors[DARKORANGE].blue = 0;

    __utalCanvasColors[DARKORANGE_1].red = 255;
    __utalCanvasColors[DARKORANGE_1].green = 127;
    __utalCanvasColors[DARKORANGE_1].blue = 0;

    __utalCanvasColors[DARKORANGE_2].red = 238;
    __utalCanvasColors[DARKORANGE_2].green = 118;
    __utalCanvasColors[DARKORANGE_2].blue = 0;

    __utalCanvasColors[DARKORANGE_3].red = 205;
    __utalCanvasColors[DARKORANGE_3].green = 102;
    __utalCanvasColors[DARKORANGE_3].blue = 0;

    __utalCanvasColors[DARKORANGE_4].red = 139;
    __utalCanvasColors[DARKORANGE_4].green = 69;
    __utalCanvasColors[DARKORANGE_4].blue = 0;

    __utalCanvasColors[ORANGE].red = 255;
    __utalCanvasColors[ORANGE].green = 128;
    __utalCanvasColors[ORANGE].blue = 0;

    __utalCanvasColors[TAN_1].red = 255;
    __utalCanvasColors[TAN_1].green = 165;
    __utalCanvasColors[TAN_1].blue = 79;

    __utalCanvasColors[TAN_2].red = 238;
    __utalCanvasColors[TAN_2].green = 154;
    __utalCanvasColors[TAN_2].blue = 73;

    __utalCanvasColors[TAN_3].red = 205;
    __utalCanvasColors[TAN_3].green = 133;
    __utalCanvasColors[TAN_3].blue = 63;

    __utalCanvasColors[TAN_4].red = 139;
    __utalCanvasColors[TAN_4].green = 90;
    __utalCanvasColors[TAN_4].blue = 43;

    __utalCanvasColors[LINEN].red = 250;
    __utalCanvasColors[LINEN].green = 240;
    __utalCanvasColors[LINEN].blue = 230;

    __utalCanvasColors[PEACHPUFF_1].red = 255;
    __utalCanvasColors[PEACHPUFF_1].green = 218;
    __utalCanvasColors[PEACHPUFF_1].blue = 185;

    __utalCanvasColors[PEACHPUFF_2].red = 238;
    __utalCanvasColors[PEACHPUFF_2].green = 203;
    __utalCanvasColors[PEACHPUFF_2].blue = 173;

    __utalCanvasColors[PEACHPUFF_3].red = 205;
    __utalCanvasColors[PEACHPUFF_3].green = 175;
    __utalCanvasColors[PEACHPUFF_3].blue = 149;

    __utalCanvasColors[PEACHPUFF_4].red = 139;
    __utalCanvasColors[PEACHPUFF_4].green = 119;
    __utalCanvasColors[PEACHPUFF_4].blue = 101;

    __utalCanvasColors[SEASHELL_1].red = 255;
    __utalCanvasColors[SEASHELL_1].green = 245;
    __utalCanvasColors[SEASHELL_1].blue = 238;

    __utalCanvasColors[SEASHELL_2].red = 238;
    __utalCanvasColors[SEASHELL_2].green = 229;
    __utalCanvasColors[SEASHELL_2].blue = 222;

    __utalCanvasColors[SEASHELL_3].red = 205;
    __utalCanvasColors[SEASHELL_3].green = 197;
    __utalCanvasColors[SEASHELL_3].blue = 191;

    __utalCanvasColors[SEASHELL_4].red = 139;
    __utalCanvasColors[SEASHELL_4].green = 134;
    __utalCanvasColors[SEASHELL_4].blue = 130;

    __utalCanvasColors[SANDYBROWN].red = 244;
    __utalCanvasColors[SANDYBROWN].green = 164;
    __utalCanvasColors[SANDYBROWN].blue = 96;

    __utalCanvasColors[RAWSIENNA].red = 199;
    __utalCanvasColors[RAWSIENNA].green = 97;
    __utalCanvasColors[RAWSIENNA].blue = 20;

    __utalCanvasColors[CHOCOLATE].red = 210;
    __utalCanvasColors[CHOCOLATE].green = 105;
    __utalCanvasColors[CHOCOLATE].blue = 30;

    __utalCanvasColors[CHOCOLATE_1].red = 255;
    __utalCanvasColors[CHOCOLATE_1].green = 127;
    __utalCanvasColors[CHOCOLATE_1].blue = 36;

    __utalCanvasColors[CHOCOLATE_2].red = 238;
    __utalCanvasColors[CHOCOLATE_2].green = 118;
    __utalCanvasColors[CHOCOLATE_2].blue = 33;

    __utalCanvasColors[CHOCOLATE_3].red = 205;
    __utalCanvasColors[CHOCOLATE_3].green = 102;
    __utalCanvasColors[CHOCOLATE_3].blue = 29;

    __utalCanvasColors[CHOCOLATE_4].red = 139;
    __utalCanvasColors[CHOCOLATE_4].green = 69;
    __utalCanvasColors[CHOCOLATE_4].blue = 19;

    __utalCanvasColors[IVORYBLACK].red = 41;
    __utalCanvasColors[IVORYBLACK].green = 36;
    __utalCanvasColors[IVORYBLACK].blue = 33;

    __utalCanvasColors[FLESH].red = 255;
    __utalCanvasColors[FLESH].green = 125;
    __utalCanvasColors[FLESH].blue = 64;

    __utalCanvasColors[CADMIUMORANGE].red = 255;
    __utalCanvasColors[CADMIUMORANGE].green = 97;
    __utalCanvasColors[CADMIUMORANGE].blue = 3;

    __utalCanvasColors[BURNTSIENNA].red = 138;
    __utalCanvasColors[BURNTSIENNA].green = 54;
    __utalCanvasColors[BURNTSIENNA].blue = 15;

    __utalCanvasColors[SIENNA].red = 160;
    __utalCanvasColors[SIENNA].green = 82;
    __utalCanvasColors[SIENNA].blue = 45;

    __utalCanvasColors[SIENNA_1].red = 255;
    __utalCanvasColors[SIENNA_1].green = 130;
    __utalCanvasColors[SIENNA_1].blue = 71;

    __utalCanvasColors[SIENNA_2].red = 238;
    __utalCanvasColors[SIENNA_2].green = 121;
    __utalCanvasColors[SIENNA_2].blue = 66;

    __utalCanvasColors[SIENNA_3].red = 205;
    __utalCanvasColors[SIENNA_3].green = 104;
    __utalCanvasColors[SIENNA_3].blue = 57;

    __utalCanvasColors[SIENNA_4].red = 139;
    __utalCanvasColors[SIENNA_4].green = 71;
    __utalCanvasColors[SIENNA_4].blue = 38;

    __utalCanvasColors[LIGHTSALMON_1].red = 255;
    __utalCanvasColors[LIGHTSALMON_1].green = 160;
    __utalCanvasColors[LIGHTSALMON_1].blue = 122;

    __utalCanvasColors[LIGHTSALMON_2].red = 238;
    __utalCanvasColors[LIGHTSALMON_2].green = 149;
    __utalCanvasColors[LIGHTSALMON_2].blue = 114;

    __utalCanvasColors[LIGHTSALMON_3].red = 205;
    __utalCanvasColors[LIGHTSALMON_3].green = 129;
    __utalCanvasColors[LIGHTSALMON_3].blue = 98;

    __utalCanvasColors[LIGHTSALMON_4].red = 139;
    __utalCanvasColors[LIGHTSALMON_4].green = 87;
    __utalCanvasColors[LIGHTSALMON_4].blue = 66;

    __utalCanvasColors[CORAL].red = 255;
    __utalCanvasColors[CORAL].green = 127;
    __utalCanvasColors[CORAL].blue = 80;

    __utalCanvasColors[ORANGERED_1].red = 255;
    __utalCanvasColors[ORANGERED_1].green = 69;
    __utalCanvasColors[ORANGERED_1].blue = 0;

    __utalCanvasColors[ORANGERED_2].red = 238;
    __utalCanvasColors[ORANGERED_2].green = 64;
    __utalCanvasColors[ORANGERED_2].blue = 0;

    __utalCanvasColors[ORANGERED_3].red = 205;
    __utalCanvasColors[ORANGERED_3].green = 55;
    __utalCanvasColors[ORANGERED_3].blue = 0;

    __utalCanvasColors[ORANGERED_4].red = 139;
    __utalCanvasColors[ORANGERED_4].green = 37;
    __utalCanvasColors[ORANGERED_4].blue = 0;

    __utalCanvasColors[SEPIA].red = 94;
    __utalCanvasColors[SEPIA].green = 38;
    __utalCanvasColors[SEPIA].blue = 18;

    __utalCanvasColors[DARKSALMON].red = 233;
    __utalCanvasColors[DARKSALMON].green = 150;
    __utalCanvasColors[DARKSALMON].blue = 122;

    __utalCanvasColors[SALMON_1].red = 255;
    __utalCanvasColors[SALMON_1].green = 140;
    __utalCanvasColors[SALMON_1].blue = 105;

    __utalCanvasColors[SALMON_2].red = 238;
    __utalCanvasColors[SALMON_2].green = 130;
    __utalCanvasColors[SALMON_2].blue = 98;

    __utalCanvasColors[SALMON_3].red = 205;
    __utalCanvasColors[SALMON_3].green = 112;
    __utalCanvasColors[SALMON_3].blue = 84;

    __utalCanvasColors[SALMON_4].red = 139;
    __utalCanvasColors[SALMON_4].green = 76;
    __utalCanvasColors[SALMON_4].blue = 57;

    __utalCanvasColors[CORAL_1].red = 255;
    __utalCanvasColors[CORAL_1].green = 114;
    __utalCanvasColors[CORAL_1].blue = 86;

    __utalCanvasColors[CORAL_2].red = 238;
    __utalCanvasColors[CORAL_2].green = 106;
    __utalCanvasColors[CORAL_2].blue = 80;

    __utalCanvasColors[CORAL_3].red = 205;
    __utalCanvasColors[CORAL_3].green = 91;
    __utalCanvasColors[CORAL_3].blue = 69;

    __utalCanvasColors[CORAL_4].red = 139;
    __utalCanvasColors[CORAL_4].green = 62;
    __utalCanvasColors[CORAL_4].blue = 47;

    __utalCanvasColors[BURNTUMBER].red = 138;
    __utalCanvasColors[BURNTUMBER].green = 51;
    __utalCanvasColors[BURNTUMBER].blue = 36;

    __utalCanvasColors[TOMATO_1].red = 255;
    __utalCanvasColors[TOMATO_1].green = 99;
    __utalCanvasColors[TOMATO_1].blue = 71;

    __utalCanvasColors[TOMATO_2].red = 238;
    __utalCanvasColors[TOMATO_2].green = 92;
    __utalCanvasColors[TOMATO_2].blue = 66;

    __utalCanvasColors[TOMATO_3].red = 205;
    __utalCanvasColors[TOMATO_3].green = 79;
    __utalCanvasColors[TOMATO_3].blue = 57;

    __utalCanvasColors[TOMATO_4].red = 139;
    __utalCanvasColors[TOMATO_4].green = 54;
    __utalCanvasColors[TOMATO_4].blue = 38;

    __utalCanvasColors[SALMON].red = 250;
    __utalCanvasColors[SALMON].green = 128;
    __utalCanvasColors[SALMON].blue = 114;

    __utalCanvasColors[MISTYROSE_1].red = 255;
    __utalCanvasColors[MISTYROSE_1].green = 228;
    __utalCanvasColors[MISTYROSE_1].blue = 225;

    __utalCanvasColors[MISTYROSE_2].red = 238;
    __utalCanvasColors[MISTYROSE_2].green = 213;
    __utalCanvasColors[MISTYROSE_2].blue = 210;

    __utalCanvasColors[MISTYROSE_3].red = 205;
    __utalCanvasColors[MISTYROSE_3].green = 183;
    __utalCanvasColors[MISTYROSE_3].blue = 181;

    __utalCanvasColors[MISTYROSE_4].red = 139;
    __utalCanvasColors[MISTYROSE_4].green = 125;
    __utalCanvasColors[MISTYROSE_4].blue = 123;

    __utalCanvasColors[SNOW_1].red = 255;
    __utalCanvasColors[SNOW_1].green = 250;
    __utalCanvasColors[SNOW_1].blue = 250;

    __utalCanvasColors[SNOW_2].red = 238;
    __utalCanvasColors[SNOW_2].green = 233;
    __utalCanvasColors[SNOW_2].blue = 233;

    __utalCanvasColors[SNOW_3].red = 205;
    __utalCanvasColors[SNOW_3].green = 201;
    __utalCanvasColors[SNOW_3].blue = 201;

    __utalCanvasColors[SNOW_4].red = 139;
    __utalCanvasColors[SNOW_4].green = 137;
    __utalCanvasColors[SNOW_4].blue = 137;

    __utalCanvasColors[ROSYBROWN].red = 188;
    __utalCanvasColors[ROSYBROWN].green = 143;
    __utalCanvasColors[ROSYBROWN].blue = 143;

    __utalCanvasColors[ROSYBROWN_1].red = 255;
    __utalCanvasColors[ROSYBROWN_1].green = 193;
    __utalCanvasColors[ROSYBROWN_1].blue = 193;

    __utalCanvasColors[ROSYBROWN_2].red = 238;
    __utalCanvasColors[ROSYBROWN_2].green = 180;
    __utalCanvasColors[ROSYBROWN_2].blue = 180;

    __utalCanvasColors[ROSYBROWN_3].red = 205;
    __utalCanvasColors[ROSYBROWN_3].green = 155;
    __utalCanvasColors[ROSYBROWN_3].blue = 155;

    __utalCanvasColors[ROSYBROWN_4].red = 139;
    __utalCanvasColors[ROSYBROWN_4].green = 105;
    __utalCanvasColors[ROSYBROWN_4].blue = 105;

    __utalCanvasColors[LIGHTCORAL].red = 240;
    __utalCanvasColors[LIGHTCORAL].green = 128;
    __utalCanvasColors[LIGHTCORAL].blue = 128;

    __utalCanvasColors[INDIANRED].red = 205;
    __utalCanvasColors[INDIANRED].green = 92;
    __utalCanvasColors[INDIANRED].blue = 92;

    __utalCanvasColors[INDIANRED_1].red = 255;
    __utalCanvasColors[INDIANRED_1].green = 106;
    __utalCanvasColors[INDIANRED_1].blue = 106;

    __utalCanvasColors[INDIANRED_2].red = 238;
    __utalCanvasColors[INDIANRED_2].green = 99;
    __utalCanvasColors[INDIANRED_2].blue = 99;

    __utalCanvasColors[INDIANRED_4].red = 139;
    __utalCanvasColors[INDIANRED_4].green = 58;
    __utalCanvasColors[INDIANRED_4].blue = 58;

    __utalCanvasColors[INDIANRED_3].red = 205;
    __utalCanvasColors[INDIANRED_3].green = 85;
    __utalCanvasColors[INDIANRED_3].blue = 85;

    __utalCanvasColors[BROWN].red = 165;
    __utalCanvasColors[BROWN].green = 42;
    __utalCanvasColors[BROWN].blue = 42;

    __utalCanvasColors[BROWN_1].red = 255;
    __utalCanvasColors[BROWN_1].green = 64;
    __utalCanvasColors[BROWN_1].blue = 64;

    __utalCanvasColors[BROWN_2].red = 238;
    __utalCanvasColors[BROWN_2].green = 59;
    __utalCanvasColors[BROWN_2].blue = 59;

    __utalCanvasColors[BROWN_3].red = 205;
    __utalCanvasColors[BROWN_3].green = 51;
    __utalCanvasColors[BROWN_3].blue = 51;

    __utalCanvasColors[BROWN_4].red = 139;
    __utalCanvasColors[BROWN_4].green = 35;
    __utalCanvasColors[BROWN_4].blue = 35;

    __utalCanvasColors[FIREBRICK].red = 178;
    __utalCanvasColors[FIREBRICK].green = 34;
    __utalCanvasColors[FIREBRICK].blue = 34;

    __utalCanvasColors[FIREBRICK_1].red = 255;
    __utalCanvasColors[FIREBRICK_1].green = 48;
    __utalCanvasColors[FIREBRICK_1].blue = 48;

    __utalCanvasColors[FIREBRICK_2].red = 238;
    __utalCanvasColors[FIREBRICK_2].green = 44;
    __utalCanvasColors[FIREBRICK_2].blue = 44;

    __utalCanvasColors[FIREBRICK_3].red = 205;
    __utalCanvasColors[FIREBRICK_3].green = 38;
    __utalCanvasColors[FIREBRICK_3].blue = 38;

    __utalCanvasColors[FIREBRICK_4].red = 139;
    __utalCanvasColors[FIREBRICK_4].green = 26;
    __utalCanvasColors[FIREBRICK_4].blue = 26;

    __utalCanvasColors[RED_1].red = 255;
    __utalCanvasColors[RED_1].green = 0;
    __utalCanvasColors[RED_1].blue = 0;

    __utalCanvasColors[RED_2].red = 238;
    __utalCanvasColors[RED_2].green = 0;
    __utalCanvasColors[RED_2].blue = 0;

    __utalCanvasColors[RED_3].red = 205;
    __utalCanvasColors[RED_3].green = 0;
    __utalCanvasColors[RED_3].blue = 0;

    __utalCanvasColors[RED_4].red = 139;
    __utalCanvasColors[RED_4].green = 0;
    __utalCanvasColors[RED_4].blue = 0;

    __utalCanvasColors[MAROON].red = 128;
    __utalCanvasColors[MAROON].green = 0;
    __utalCanvasColors[MAROON].blue = 0;

    __utalCanvasColors[SGI_BEET].red = 142;
    __utalCanvasColors[SGI_BEET].green = 56;
    __utalCanvasColors[SGI_BEET].blue = 142;

    __utalCanvasColors[SGI_SLATEBLUE].red = 113;
    __utalCanvasColors[SGI_SLATEBLUE].green = 113;
    __utalCanvasColors[SGI_SLATEBLUE].blue = 198;

    __utalCanvasColors[SGI_LIGHTBLUE].red = 125;
    __utalCanvasColors[SGI_LIGHTBLUE].green = 158;
    __utalCanvasColors[SGI_LIGHTBLUE].blue = 192;

    __utalCanvasColors[SGI_TEAL].red = 56;
    __utalCanvasColors[SGI_TEAL].green = 142;
    __utalCanvasColors[SGI_TEAL].blue = 142;

    __utalCanvasColors[SGI_CHARTREUSE].red = 113;
    __utalCanvasColors[SGI_CHARTREUSE].green = 198;
    __utalCanvasColors[SGI_CHARTREUSE].blue = 113;

    __utalCanvasColors[SGI_OLIVEDRAB].red = 142;
    __utalCanvasColors[SGI_OLIVEDRAB].green = 142;
    __utalCanvasColors[SGI_OLIVEDRAB].blue = 56;

    __utalCanvasColors[SGI_BRIGHTGRAY].red = 197;
    __utalCanvasColors[SGI_BRIGHTGRAY].green = 193;
    __utalCanvasColors[SGI_BRIGHTGRAY].blue = 170;

    __utalCanvasColors[SGI_SALMON].red = 198;
    __utalCanvasColors[SGI_SALMON].green = 113;
    __utalCanvasColors[SGI_SALMON].blue = 113;

    __utalCanvasColors[SGI_DARKGRAY].red = 85;
    __utalCanvasColors[SGI_DARKGRAY].green = 85;
    __utalCanvasColors[SGI_DARKGRAY].blue = 85;

    __utalCanvasColors[SGI_GRAY_12].red = 30;
    __utalCanvasColors[SGI_GRAY_12].green = 30;
    __utalCanvasColors[SGI_GRAY_12].blue = 30;

    __utalCanvasColors[SGI_GRAY_16].red = 40;
    __utalCanvasColors[SGI_GRAY_16].green = 40;
    __utalCanvasColors[SGI_GRAY_16].blue = 40;

    __utalCanvasColors[SGI_GRAY_32].red = 81;
    __utalCanvasColors[SGI_GRAY_32].green = 81;
    __utalCanvasColors[SGI_GRAY_32].blue = 81;

    __utalCanvasColors[SGI_GRAY_36].red = 91;
    __utalCanvasColors[SGI_GRAY_36].green = 91;
    __utalCanvasColors[SGI_GRAY_36].blue = 91;

    __utalCanvasColors[SGI_GRAY_52].red = 132;
    __utalCanvasColors[SGI_GRAY_52].green = 132;
    __utalCanvasColors[SGI_GRAY_52].blue = 132;

    __utalCanvasColors[SGI_GRAY_56].red = 142;
    __utalCanvasColors[SGI_GRAY_56].green = 142;
    __utalCanvasColors[SGI_GRAY_56].blue = 142;

    __utalCanvasColors[SGI_LIGHTGRAY].red = 170;
    __utalCanvasColors[SGI_LIGHTGRAY].green = 170;
    __utalCanvasColors[SGI_LIGHTGRAY].blue = 170;

    __utalCanvasColors[SGI_GRAY_72].red = 183;
    __utalCanvasColors[SGI_GRAY_72].green = 183;
    __utalCanvasColors[SGI_GRAY_72].blue = 183;

    __utalCanvasColors[SGI_GRAY_76].red = 193;
    __utalCanvasColors[SGI_GRAY_76].green = 193;
    __utalCanvasColors[SGI_GRAY_76].blue = 193;

    __utalCanvasColors[SGI_GRAY_92].red = 234;
    __utalCanvasColors[SGI_GRAY_92].green = 234;
    __utalCanvasColors[SGI_GRAY_92].blue = 234;

    __utalCanvasColors[SGI_GRAY_96].red = 244;
    __utalCanvasColors[SGI_GRAY_96].green = 244;
    __utalCanvasColors[SGI_GRAY_96].blue = 244;

    __utalCanvasColors[WHITE].red = 255;
    __utalCanvasColors[WHITE].green = 255;
    __utalCanvasColors[WHITE].blue = 255;

    __utalCanvasColors[WHITE_SMOKE].red = 245;
    __utalCanvasColors[WHITE_SMOKE].green = 245;
    __utalCanvasColors[WHITE_SMOKE].blue = 245;

    __utalCanvasColors[GAINSBORO].red = 220;
    __utalCanvasColors[GAINSBORO].green = 220;
    __utalCanvasColors[GAINSBORO].blue = 220;

    __utalCanvasColors[LIGHTGREY].red = 211;
    __utalCanvasColors[LIGHTGREY].green = 211;
    __utalCanvasColors[LIGHTGREY].blue = 211;

    __utalCanvasColors[SILVER].red = 192;
    __utalCanvasColors[SILVER].green = 192;
    __utalCanvasColors[SILVER].blue = 192;

    __utalCanvasColors[DARKGRAY].red = 169;
    __utalCanvasColors[DARKGRAY].green = 169;
    __utalCanvasColors[DARKGRAY].blue = 169;

    __utalCanvasColors[GRAY].red = 128;
    __utalCanvasColors[GRAY].green = 128;
    __utalCanvasColors[GRAY].blue = 128;

    __utalCanvasColors[BLACK].red = 0;
    __utalCanvasColors[BLACK].green = 0;
    __utalCanvasColors[BLACK].blue = 0;

    __utalCanvasColors[GRAY_99].red = 252;
    __utalCanvasColors[GRAY_99].green = 252;
    __utalCanvasColors[GRAY_99].blue = 252;

    __utalCanvasColors[GRAY_98].red = 250;
    __utalCanvasColors[GRAY_98].green = 250;
    __utalCanvasColors[GRAY_98].blue = 250;

    __utalCanvasColors[GRAY_97].red = 247;
    __utalCanvasColors[GRAY_97].green = 247;
    __utalCanvasColors[GRAY_97].blue = 247;

    __utalCanvasColors[GRAY_95].red = 242;
    __utalCanvasColors[GRAY_95].green = 242;
    __utalCanvasColors[GRAY_95].blue = 242;

    __utalCanvasColors[GRAY_94].red = 240;
    __utalCanvasColors[GRAY_94].green = 240;
    __utalCanvasColors[GRAY_94].blue = 240;

    __utalCanvasColors[GRAY_93].red = 237;
    __utalCanvasColors[GRAY_93].green = 237;
    __utalCanvasColors[GRAY_93].blue = 237;

    __utalCanvasColors[GRAY_92].red = 235;
    __utalCanvasColors[GRAY_92].green = 235;
    __utalCanvasColors[GRAY_92].blue = 235;

    __utalCanvasColors[GRAY_91].red = 232;
    __utalCanvasColors[GRAY_91].green = 232;
    __utalCanvasColors[GRAY_91].blue = 232;

    __utalCanvasColors[GRAY_90].red = 229;
    __utalCanvasColors[GRAY_90].green = 229;
    __utalCanvasColors[GRAY_90].blue = 229;

    __utalCanvasColors[GRAY_89].red = 227;
    __utalCanvasColors[GRAY_89].green = 227;
    __utalCanvasColors[GRAY_89].blue = 227;

    __utalCanvasColors[GRAY_88].red = 224;
    __utalCanvasColors[GRAY_88].green = 224;
    __utalCanvasColors[GRAY_88].blue = 224;

    __utalCanvasColors[GRAY_87].red = 222;
    __utalCanvasColors[GRAY_87].green = 222;
    __utalCanvasColors[GRAY_87].blue = 222;

    __utalCanvasColors[GRAY_86].red = 219;
    __utalCanvasColors[GRAY_86].green = 219;
    __utalCanvasColors[GRAY_86].blue = 219;

    __utalCanvasColors[GRAY_85].red = 217;
    __utalCanvasColors[GRAY_85].green = 217;
    __utalCanvasColors[GRAY_85].blue = 217;

    __utalCanvasColors[GRAY_84].red = 214;
    __utalCanvasColors[GRAY_84].green = 214;
    __utalCanvasColors[GRAY_84].blue = 214;

    __utalCanvasColors[GRAY_83].red = 212;
    __utalCanvasColors[GRAY_83].green = 212;
    __utalCanvasColors[GRAY_83].blue = 212;

    __utalCanvasColors[GRAY_82].red = 209;
    __utalCanvasColors[GRAY_82].green = 209;
    __utalCanvasColors[GRAY_82].blue = 209;

    __utalCanvasColors[GRAY_81].red = 207;
    __utalCanvasColors[GRAY_81].green = 207;
    __utalCanvasColors[GRAY_81].blue = 207;

    __utalCanvasColors[GRAY_80].red = 204;
    __utalCanvasColors[GRAY_80].green = 204;
    __utalCanvasColors[GRAY_80].blue = 204;

    __utalCanvasColors[GRAY_79].red = 201;
    __utalCanvasColors[GRAY_79].green = 201;
    __utalCanvasColors[GRAY_79].blue = 201;

    __utalCanvasColors[GRAY_78].red = 199;
    __utalCanvasColors[GRAY_78].green = 199;
    __utalCanvasColors[GRAY_78].blue = 199;

    __utalCanvasColors[GRAY_77].red = 196;
    __utalCanvasColors[GRAY_77].green = 196;
    __utalCanvasColors[GRAY_77].blue = 196;

    __utalCanvasColors[GRAY_76].red = 194;
    __utalCanvasColors[GRAY_76].green = 194;
    __utalCanvasColors[GRAY_76].blue = 194;

    __utalCanvasColors[GRAY_75].red = 191;
    __utalCanvasColors[GRAY_75].green = 191;
    __utalCanvasColors[GRAY_75].blue = 191;

    __utalCanvasColors[GRAY_74].red = 189;
    __utalCanvasColors[GRAY_74].green = 189;
    __utalCanvasColors[GRAY_74].blue = 189;

    __utalCanvasColors[GRAY_73].red = 186;
    __utalCanvasColors[GRAY_73].green = 186;
    __utalCanvasColors[GRAY_73].blue = 186;

    __utalCanvasColors[GRAY_72].red = 184;
    __utalCanvasColors[GRAY_72].green = 184;
    __utalCanvasColors[GRAY_72].blue = 184;

    __utalCanvasColors[GRAY_71].red = 181;
    __utalCanvasColors[GRAY_71].green = 181;
    __utalCanvasColors[GRAY_71].blue = 181;

    __utalCanvasColors[GRAY_70].red = 179;
    __utalCanvasColors[GRAY_70].green = 179;
    __utalCanvasColors[GRAY_70].blue = 179;

    __utalCanvasColors[GRAY_69].red = 176;
    __utalCanvasColors[GRAY_69].green = 176;
    __utalCanvasColors[GRAY_69].blue = 176;

    __utalCanvasColors[GRAY_68].red = 173;
    __utalCanvasColors[GRAY_68].green = 173;
    __utalCanvasColors[GRAY_68].blue = 173;

    __utalCanvasColors[GRAY_67].red = 171;
    __utalCanvasColors[GRAY_67].green = 171;
    __utalCanvasColors[GRAY_67].blue = 171;

    __utalCanvasColors[GRAY_66].red = 168;
    __utalCanvasColors[GRAY_66].green = 168;
    __utalCanvasColors[GRAY_66].blue = 168;

    __utalCanvasColors[GRAY_65].red = 166;
    __utalCanvasColors[GRAY_65].green = 166;
    __utalCanvasColors[GRAY_65].blue = 166;

    __utalCanvasColors[GRAY_64].red = 163;
    __utalCanvasColors[GRAY_64].green = 163;
    __utalCanvasColors[GRAY_64].blue = 163;

    __utalCanvasColors[GRAY_63].red = 161;
    __utalCanvasColors[GRAY_63].green = 161;
    __utalCanvasColors[GRAY_63].blue = 161;

    __utalCanvasColors[GRAY_62].red = 158;
    __utalCanvasColors[GRAY_62].green = 158;
    __utalCanvasColors[GRAY_62].blue = 158;

    __utalCanvasColors[GRAY_61].red = 156;
    __utalCanvasColors[GRAY_61].green = 156;
    __utalCanvasColors[GRAY_61].blue = 156;

    __utalCanvasColors[GRAY_60].red = 153;
    __utalCanvasColors[GRAY_60].green = 153;
    __utalCanvasColors[GRAY_60].blue = 153;

    __utalCanvasColors[GRAY_59].red = 150;
    __utalCanvasColors[GRAY_59].green = 150;
    __utalCanvasColors[GRAY_59].blue = 150;

    __utalCanvasColors[GRAY_58].red = 148;
    __utalCanvasColors[GRAY_58].green = 148;
    __utalCanvasColors[GRAY_58].blue = 148;

    __utalCanvasColors[GRAY_57].red = 145;
    __utalCanvasColors[GRAY_57].green = 145;
    __utalCanvasColors[GRAY_57].blue = 145;

    __utalCanvasColors[GRAY_56].red = 143;
    __utalCanvasColors[GRAY_56].green = 143;
    __utalCanvasColors[GRAY_56].blue = 143;

    __utalCanvasColors[GRAY_55].red = 140;
    __utalCanvasColors[GRAY_55].green = 140;
    __utalCanvasColors[GRAY_55].blue = 140;

    __utalCanvasColors[GRAY_54].red = 138;
    __utalCanvasColors[GRAY_54].green = 138;
    __utalCanvasColors[GRAY_54].blue = 138;

    __utalCanvasColors[GRAY_53].red = 135;
    __utalCanvasColors[GRAY_53].green = 135;
    __utalCanvasColors[GRAY_53].blue = 135;

    __utalCanvasColors[GRAY_52].red = 133;
    __utalCanvasColors[GRAY_52].green = 133;
    __utalCanvasColors[GRAY_52].blue = 133;

    __utalCanvasColors[GRAY_51].red = 130;
    __utalCanvasColors[GRAY_51].green = 130;
    __utalCanvasColors[GRAY_51].blue = 130;

    __utalCanvasColors[GRAY_50].red = 127;
    __utalCanvasColors[GRAY_50].green = 127;
    __utalCanvasColors[GRAY_50].blue = 127;

    __utalCanvasColors[GRAY_49].red = 125;
    __utalCanvasColors[GRAY_49].green = 125;
    __utalCanvasColors[GRAY_49].blue = 125;

    __utalCanvasColors[GRAY_48].red = 122;
    __utalCanvasColors[GRAY_48].green = 122;
    __utalCanvasColors[GRAY_48].blue = 122;

    __utalCanvasColors[GRAY_47].red = 120;
    __utalCanvasColors[GRAY_47].green = 120;
    __utalCanvasColors[GRAY_47].blue = 120;

    __utalCanvasColors[GRAY_46].red = 117;
    __utalCanvasColors[GRAY_46].green = 117;
    __utalCanvasColors[GRAY_46].blue = 117;

    __utalCanvasColors[GRAY_45].red = 115;
    __utalCanvasColors[GRAY_45].green = 115;
    __utalCanvasColors[GRAY_45].blue = 115;

    __utalCanvasColors[GRAY_44].red = 112;
    __utalCanvasColors[GRAY_44].green = 112;
    __utalCanvasColors[GRAY_44].blue = 112;

    __utalCanvasColors[GRAY_43].red = 110;
    __utalCanvasColors[GRAY_43].green = 110;
    __utalCanvasColors[GRAY_43].blue = 110;

    __utalCanvasColors[GRAY_42].red = 107;
    __utalCanvasColors[GRAY_42].green = 107;
    __utalCanvasColors[GRAY_42].blue = 107;

    __utalCanvasColors[DIMGRAY].red = 105;
    __utalCanvasColors[DIMGRAY].green = 105;
    __utalCanvasColors[DIMGRAY].blue = 105;

    __utalCanvasColors[GRAY_40].red = 102;
    __utalCanvasColors[GRAY_40].green = 102;
    __utalCanvasColors[GRAY_40].blue = 102;

    __utalCanvasColors[GRAY_39].red = 99;
    __utalCanvasColors[GRAY_39].green = 99;
    __utalCanvasColors[GRAY_39].blue = 99;

    __utalCanvasColors[GRAY_38].red = 97;
    __utalCanvasColors[GRAY_38].green = 97;
    __utalCanvasColors[GRAY_38].blue = 97;

    __utalCanvasColors[GRAY_37].red = 94;
    __utalCanvasColors[GRAY_37].green = 94;
    __utalCanvasColors[GRAY_37].blue = 94;

    __utalCanvasColors[GRAY_36].red = 92;
    __utalCanvasColors[GRAY_36].green = 92;
    __utalCanvasColors[GRAY_36].blue = 92;

    __utalCanvasColors[GRAY_35].red = 89;
    __utalCanvasColors[GRAY_35].green = 89;
    __utalCanvasColors[GRAY_35].blue = 89;

    __utalCanvasColors[GRAY_34].red = 87;
    __utalCanvasColors[GRAY_34].green = 87;
    __utalCanvasColors[GRAY_34].blue = 87;

    __utalCanvasColors[GRAY_33].red = 84;
    __utalCanvasColors[GRAY_33].green = 84;
    __utalCanvasColors[GRAY_33].blue = 84;

    __utalCanvasColors[GRAY_32].red = 82;
    __utalCanvasColors[GRAY_32].green = 82;
    __utalCanvasColors[GRAY_32].blue = 82;

    __utalCanvasColors[GRAY_31].red = 79;
    __utalCanvasColors[GRAY_31].green = 79;
    __utalCanvasColors[GRAY_31].blue = 79;

    __utalCanvasColors[GRAY_30].red = 77;
    __utalCanvasColors[GRAY_30].green = 77;
    __utalCanvasColors[GRAY_30].blue = 77;

    __utalCanvasColors[GRAY_29].red = 74;
    __utalCanvasColors[GRAY_29].green = 74;
    __utalCanvasColors[GRAY_29].blue = 74;

    __utalCanvasColors[GRAY_28].red = 71;
    __utalCanvasColors[GRAY_28].green = 71;
    __utalCanvasColors[GRAY_28].blue = 71;

    __utalCanvasColors[GRAY_27].red = 69;
    __utalCanvasColors[GRAY_27].green = 69;
    __utalCanvasColors[GRAY_27].blue = 69;

    __utalCanvasColors[GRAY_26].red = 66;
    __utalCanvasColors[GRAY_26].green = 66;
    __utalCanvasColors[GRAY_26].blue = 66;

    __utalCanvasColors[GRAY_25].red = 64;
    __utalCanvasColors[GRAY_25].green = 64;
    __utalCanvasColors[GRAY_25].blue = 64;

    __utalCanvasColors[GRAY_24].red = 61;
    __utalCanvasColors[GRAY_24].green = 61;
    __utalCanvasColors[GRAY_24].blue = 61;

    __utalCanvasColors[GRAY_23].red = 59;
    __utalCanvasColors[GRAY_23].green = 59;
    __utalCanvasColors[GRAY_23].blue = 59;

    __utalCanvasColors[GRAY_22].red = 56;
    __utalCanvasColors[GRAY_22].green = 56;
    __utalCanvasColors[GRAY_22].blue = 56;

    __utalCanvasColors[GRAY_21].red = 54;
    __utalCanvasColors[GRAY_21].green = 54;
    __utalCanvasColors[GRAY_21].blue = 54;

    __utalCanvasColors[GRAY_20].red = 51;
    __utalCanvasColors[GRAY_20].green = 51;
    __utalCanvasColors[GRAY_20].blue = 51;

    __utalCanvasColors[GRAY_19].red = 48;
    __utalCanvasColors[GRAY_19].green = 48;
    __utalCanvasColors[GRAY_19].blue = 48;

    __utalCanvasColors[GRAY_18].red = 46;
    __utalCanvasColors[GRAY_18].green = 46;
    __utalCanvasColors[GRAY_18].blue = 46;

    __utalCanvasColors[GRAY_17].red = 43;
    __utalCanvasColors[GRAY_17].green = 43;
    __utalCanvasColors[GRAY_17].blue = 43;

    __utalCanvasColors[GRAY_16].red = 41;
    __utalCanvasColors[GRAY_16].green = 41;
    __utalCanvasColors[GRAY_16].blue = 41;

    __utalCanvasColors[GRAY_15].red = 38;
    __utalCanvasColors[GRAY_15].green = 38;
    __utalCanvasColors[GRAY_15].blue = 38;

    __utalCanvasColors[GRAY_14].red = 36;
    __utalCanvasColors[GRAY_14].green = 36;
    __utalCanvasColors[GRAY_14].blue = 36;

    __utalCanvasColors[GRAY_13].red = 33;
    __utalCanvasColors[GRAY_13].green = 33;
    __utalCanvasColors[GRAY_13].blue = 33;

    __utalCanvasColors[GRAY_12].red = 31;
    __utalCanvasColors[GRAY_12].green = 31;
    __utalCanvasColors[GRAY_12].blue = 31;

    __utalCanvasColors[GRAY_11].red = 28;
    __utalCanvasColors[GRAY_11].green = 28;
    __utalCanvasColors[GRAY_11].blue = 28;

    __utalCanvasColors[GRAY_10].red = 26;
    __utalCanvasColors[GRAY_10].green = 26;
    __utalCanvasColors[GRAY_10].blue = 26;

    __utalCanvasColors[GRAY_9].red = 23;
    __utalCanvasColors[GRAY_9].green = 23;
    __utalCanvasColors[GRAY_9].blue = 23;

    __utalCanvasColors[GRAY_8].red = 20;
    __utalCanvasColors[GRAY_8].green = 20;
    __utalCanvasColors[GRAY_8].blue = 20;

    __utalCanvasColors[GRAY_7].red = 18;
    __utalCanvasColors[GRAY_7].green = 18;
    __utalCanvasColors[GRAY_7].blue = 18;

    __utalCanvasColors[GRAY_6].red = 15;
    __utalCanvasColors[GRAY_6].green = 15;
    __utalCanvasColors[GRAY_6].blue = 15;

    __utalCanvasColors[GRAY_5].red = 13;
    __utalCanvasColors[GRAY_5].green = 13;
    __utalCanvasColors[GRAY_5].blue = 13;

    __utalCanvasColors[GRAY_4].red = 10;
    __utalCanvasColors[GRAY_4].green = 10;
    __utalCanvasColors[GRAY_4].blue = 10;

    __utalCanvasColors[GRAY_3].red = 8;
    __utalCanvasColors[GRAY_3].green = 8;
    __utalCanvasColors[GRAY_3].blue = 8;

    __utalCanvasColors[GRAY_2].red = 5;
    __utalCanvasColors[GRAY_2].green = 5;
    __utalCanvasColors[GRAY_2].blue = 5;

    __utalCanvasColors[GRAY_1].red = 3;
    __utalCanvasColors[GRAY_1].green = 3;
    __utalCanvasColors[GRAY_1].blue = 3;
}

ColorName __getColorByName( char* name )
{
    __init_colors();

    if( strcmp("indian red", name) == 0 ){ return INDIAN_RED; }
    if( strcmp("crimson", name) == 0 ){ return CRIMSON; }
    if( strcmp("lightpink", name) == 0 ){ return LIGHTPINK; }
    if( strcmp("lightpink 1", name) == 0 ){ return LIGHTPINK_1; }
    if( strcmp("lightpink 2", name) == 0 ){ return LIGHTPINK_2; }
    if( strcmp("lightpink 3", name) == 0 ){ return LIGHTPINK_3; }
    if( strcmp("lightpink 4", name) == 0 ){ return LIGHTPINK_4; }
    if( strcmp("pink", name) == 0 ){ return PINK; }
    if( strcmp("pink 1", name) == 0 ){ return PINK_1; }
    if( strcmp("pink 2", name) == 0 ){ return PINK_2; }
    if( strcmp("pink 3", name) == 0 ){ return PINK_3; }
    if( strcmp("pink 4", name) == 0 ){ return PINK_4; }
    if( strcmp("palevioletred", name) == 0 ){ return PALEVIOLETRED; }
    if( strcmp("palevioletred 1", name) == 0 ){ return PALEVIOLETRED_1; }
    if( strcmp("palevioletred 2", name) == 0 ){ return PALEVIOLETRED_2; }
    if( strcmp("palevioletred 3", name) == 0 ){ return PALEVIOLETRED_3; }
    if( strcmp("palevioletred 4", name) == 0 ){ return PALEVIOLETRED_4; }
    if( strcmp("lavenderblush 1", name) == 0 ){ return LAVENDERBLUSH_1; }
    if( strcmp("lavenderblush 2", name) == 0 ){ return LAVENDERBLUSH_2; }
    if( strcmp("lavenderblush 3", name) == 0 ){ return LAVENDERBLUSH_3; }
    if( strcmp("lavenderblush 4", name) == 0 ){ return LAVENDERBLUSH_4; }
    if( strcmp("violetred 1", name) == 0 ){ return VIOLETRED_1; }
    if( strcmp("violetred 2", name) == 0 ){ return VIOLETRED_2; }
    if( strcmp("violetred 3", name) == 0 ){ return VIOLETRED_3; }
    if( strcmp("violetred 4", name) == 0 ){ return VIOLETRED_4; }
    if( strcmp("hotpink", name) == 0 ){ return HOTPINK; }
    if( strcmp("hotpink 1", name) == 0 ){ return HOTPINK_1; }
    if( strcmp("hotpink 2", name) == 0 ){ return HOTPINK_2; }
    if( strcmp("hotpink 3", name) == 0 ){ return HOTPINK_3; }
    if( strcmp("hotpink 4", name) == 0 ){ return HOTPINK_4; }
    if( strcmp("raspberry", name) == 0 ){ return RASPBERRY; }
    if( strcmp("deeppink 1", name) == 0 ){ return DEEPPINK_1; }
    if( strcmp("deeppink 2", name) == 0 ){ return DEEPPINK_2; }
    if( strcmp("deeppink 3", name) == 0 ){ return DEEPPINK_3; }
    if( strcmp("deeppink 4", name) == 0 ){ return DEEPPINK_4; }
    if( strcmp("maroon 1", name) == 0 ){ return MAROON_1; }
    if( strcmp("maroon 2", name) == 0 ){ return MAROON_2; }
    if( strcmp("maroon 3", name) == 0 ){ return MAROON_3; }
    if( strcmp("maroon 4", name) == 0 ){ return MAROON_4; }
    if( strcmp("mediumvioletred", name) == 0 ){ return MEDIUMVIOLETRED; }
    if( strcmp("violetred", name) == 0 ){ return VIOLETRED; }
    if( strcmp("orchid", name) == 0 ){ return ORCHID; }
    if( strcmp("orchid 1", name) == 0 ){ return ORCHID_1; }
    if( strcmp("orchid 2", name) == 0 ){ return ORCHID_2; }
    if( strcmp("orchid 3", name) == 0 ){ return ORCHID_3; }
    if( strcmp("orchid 4", name) == 0 ){ return ORCHID_4; }
    if( strcmp("thistle", name) == 0 ){ return THISTLE; }
    if( strcmp("thistle 1", name) == 0 ){ return THISTLE_1; }
    if( strcmp("thistle 2", name) == 0 ){ return THISTLE_2; }
    if( strcmp("thistle 3", name) == 0 ){ return THISTLE_3; }
    if( strcmp("thistle 4", name) == 0 ){ return THISTLE_4; }
    if( strcmp("plum 1", name) == 0 ){ return PLUM_1; }
    if( strcmp("plum 2", name) == 0 ){ return PLUM_2; }
    if( strcmp("plum 3", name) == 0 ){ return PLUM_3; }
    if( strcmp("plum 4", name) == 0 ){ return PLUM_4; }
    if( strcmp("plum", name) == 0 ){ return PLUM; }
    if( strcmp("violet", name) == 0 ){ return VIOLET; }
    if( strcmp("magenta", name) == 0 ){ return MAGENTA; }
    if( strcmp("magenta 2", name) == 0 ){ return MAGENTA_2; }
    if( strcmp("magenta 3", name) == 0 ){ return MAGENTA_3; }
    if( strcmp("magenta 4", name) == 0 ){ return MAGENTA_4; }
    if( strcmp("purple", name) == 0 ){ return PURPLE; }
    if( strcmp("mediumorchid", name) == 0 ){ return MEDIUMORCHID; }
    if( strcmp("mediumorchid 1", name) == 0 ){ return MEDIUMORCHID_1; }
    if( strcmp("mediumorchid 2", name) == 0 ){ return MEDIUMORCHID_2; }
    if( strcmp("mediumorchid 3", name) == 0 ){ return MEDIUMORCHID_3; }
    if( strcmp("mediumorchid 4", name) == 0 ){ return MEDIUMORCHID_4; }
    if( strcmp("darkviolet", name) == 0 ){ return DARKVIOLET; }
    if( strcmp("darkorchid", name) == 0 ){ return DARKORCHID; }
    if( strcmp("darkorchid 1", name) == 0 ){ return DARKORCHID_1; }
    if( strcmp("darkorchid 2", name) == 0 ){ return DARKORCHID_2; }
    if( strcmp("darkorchid 3", name) == 0 ){ return DARKORCHID_3; }
    if( strcmp("darkorchid 4", name) == 0 ){ return DARKORCHID_4; }
    if( strcmp("indigo", name) == 0 ){ return INDIGO; }
    if( strcmp("blueviolet", name) == 0 ){ return BLUEVIOLET; }
    if( strcmp("purple 1", name) == 0 ){ return PURPLE_1; }
    if( strcmp("purple 2", name) == 0 ){ return PURPLE_2; }
    if( strcmp("purple 3", name) == 0 ){ return PURPLE_3; }
    if( strcmp("purple 4", name) == 0 ){ return PURPLE_4; }
    if( strcmp("mediumpurple", name) == 0 ){ return MEDIUMPURPLE; }
    if( strcmp("mediumpurple 1", name) == 0 ){ return MEDIUMPURPLE_1; }
    if( strcmp("mediumpurple 2", name) == 0 ){ return MEDIUMPURPLE_2; }
    if( strcmp("mediumpurple 3", name) == 0 ){ return MEDIUMPURPLE_3; }
    if( strcmp("mediumpurple 4", name) == 0 ){ return MEDIUMPURPLE_4; }
    if( strcmp("darkslateblue", name) == 0 ){ return DARKSLATEBLUE; }
    if( strcmp("lightslateblue", name) == 0 ){ return LIGHTSLATEBLUE; }
    if( strcmp("mediumslateblue", name) == 0 ){ return MEDIUMSLATEBLUE; }
    if( strcmp("slateblue", name) == 0 ){ return SLATEBLUE; }
    if( strcmp("slateblue 1", name) == 0 ){ return SLATEBLUE_1; }
    if( strcmp("slateblue 2", name) == 0 ){ return SLATEBLUE_2; }
    if( strcmp("slateblue 3", name) == 0 ){ return SLATEBLUE_3; }
    if( strcmp("slateblue 4", name) == 0 ){ return SLATEBLUE_4; }
    if( strcmp("ghostwhite", name) == 0 ){ return GHOSTWHITE; }
    if( strcmp("lavender", name) == 0 ){ return LAVENDER; }
    if( strcmp("blue", name) == 0 ){ return BLUE; }
    if( strcmp("blue 2", name) == 0 ){ return BLUE_2; }
    if( strcmp("blue 3", name) == 0 ){ return BLUE_3; }
    if( strcmp("blue 4", name) == 0 ){ return BLUE_4; }
    if( strcmp("navy", name) == 0 ){ return NAVY; }
    if( strcmp("midnightblue", name) == 0 ){ return MIDNIGHTBLUE; }
    if( strcmp("cobalt", name) == 0 ){ return COBALT; }
    if( strcmp("royalblue", name) == 0 ){ return ROYALBLUE; }
    if( strcmp("royalblue 1", name) == 0 ){ return ROYALBLUE_1; }
    if( strcmp("royalblue 2", name) == 0 ){ return ROYALBLUE_2; }
    if( strcmp("royalblue 3", name) == 0 ){ return ROYALBLUE_3; }
    if( strcmp("royalblue 4", name) == 0 ){ return ROYALBLUE_4; }
    if( strcmp("cornflowerblue", name) == 0 ){ return CORNFLOWERBLUE; }
    if( strcmp("lightsteelblue", name) == 0 ){ return LIGHTSTEELBLUE; }
    if( strcmp("lightsteelblue 1", name) == 0 ){ return LIGHTSTEELBLUE_1; }
    if( strcmp("lightsteelblue 2", name) == 0 ){ return LIGHTSTEELBLUE_2; }
    if( strcmp("lightsteelblue 3", name) == 0 ){ return LIGHTSTEELBLUE_3; }
    if( strcmp("lightsteelblue 4", name) == 0 ){ return LIGHTSTEELBLUE_4; }
    if( strcmp("lightslategray", name) == 0 ){ return LIGHTSLATEGRAY; }
    if( strcmp("slategray", name) == 0 ){ return SLATEGRAY; }
    if( strcmp("slategray 1", name) == 0 ){ return SLATEGRAY_1; }
    if( strcmp("slategray 2", name) == 0 ){ return SLATEGRAY_2; }
    if( strcmp("slategray 3", name) == 0 ){ return SLATEGRAY_3; }
    if( strcmp("slategray 4", name) == 0 ){ return SLATEGRAY_4; }
    if( strcmp("dodgerblue 1", name) == 0 ){ return DODGERBLUE_1; }
    if( strcmp("dodgerblue 2", name) == 0 ){ return DODGERBLUE_2; }
    if( strcmp("dodgerblue 3", name) == 0 ){ return DODGERBLUE_3; }
    if( strcmp("dodgerblue 4", name) == 0 ){ return DODGERBLUE_4; }
    if( strcmp("aliceblue", name) == 0 ){ return ALICEBLUE; }
    if( strcmp("steelblue", name) == 0 ){ return STEELBLUE; }
    if( strcmp("steelblue 1", name) == 0 ){ return STEELBLUE_1; }
    if( strcmp("steelblue 2", name) == 0 ){ return STEELBLUE_2; }
    if( strcmp("steelblue 3", name) == 0 ){ return STEELBLUE_3; }
    if( strcmp("steelblue 4", name) == 0 ){ return STEELBLUE_4; }
    if( strcmp("lightskyblue", name) == 0 ){ return LIGHTSKYBLUE; }
    if( strcmp("lightskyblue 1", name) == 0 ){ return LIGHTSKYBLUE_1; }
    if( strcmp("lightskyblue 2", name) == 0 ){ return LIGHTSKYBLUE_2; }
    if( strcmp("lightskyblue 3", name) == 0 ){ return LIGHTSKYBLUE_3; }
    if( strcmp("lightskyblue 4", name) == 0 ){ return LIGHTSKYBLUE_4; }
    if( strcmp("skyblue 1", name) == 0 ){ return SKYBLUE_1; }
    if( strcmp("skyblue 2", name) == 0 ){ return SKYBLUE_2; }
    if( strcmp("skyblue 3", name) == 0 ){ return SKYBLUE_3; }
    if( strcmp("skyblue 4", name) == 0 ){ return SKYBLUE_4; }
    if( strcmp("skyblue", name) == 0 ){ return SKYBLUE; }
    if( strcmp("deepskyblue 1", name) == 0 ){ return DEEPSKYBLUE_1; }
    if( strcmp("deepskyblue 2", name) == 0 ){ return DEEPSKYBLUE_2; }
    if( strcmp("deepskyblue 3", name) == 0 ){ return DEEPSKYBLUE_3; }
    if( strcmp("deepskyblue 4", name) == 0 ){ return DEEPSKYBLUE_4; }
    if( strcmp("peacock", name) == 0 ){ return PEACOCK; }
    if( strcmp("lightblue", name) == 0 ){ return LIGHTBLUE; }
    if( strcmp("lightblue 1", name) == 0 ){ return LIGHTBLUE_1; }
    if( strcmp("lightblue 2", name) == 0 ){ return LIGHTBLUE_2; }
    if( strcmp("lightblue 3", name) == 0 ){ return LIGHTBLUE_3; }
    if( strcmp("lightblue 4", name) == 0 ){ return LIGHTBLUE_4; }
    if( strcmp("powderblue", name) == 0 ){ return POWDERBLUE; }
    if( strcmp("cadetblue 1", name) == 0 ){ return CADETBLUE_1; }
    if( strcmp("cadetblue 2", name) == 0 ){ return CADETBLUE_2; }
    if( strcmp("cadetblue 3", name) == 0 ){ return CADETBLUE_3; }
    if( strcmp("cadetblue 4", name) == 0 ){ return CADETBLUE_4; }
    if( strcmp("turquoise 1", name) == 0 ){ return TURQUOISE_1; }
    if( strcmp("turquoise 2", name) == 0 ){ return TURQUOISE_2; }
    if( strcmp("turquoise 3", name) == 0 ){ return TURQUOISE_3; }
    if( strcmp("turquoise 4", name) == 0 ){ return TURQUOISE_4; }
    if( strcmp("cadetblue", name) == 0 ){ return CADETBLUE; }
    if( strcmp("darkturquoise", name) == 0 ){ return DARKTURQUOISE; }
    if( strcmp("azure 1", name) == 0 ){ return AZURE_1; }
    if( strcmp("azure 2", name) == 0 ){ return AZURE_2; }
    if( strcmp("azure 3", name) == 0 ){ return AZURE_3; }
    if( strcmp("azure 4", name) == 0 ){ return AZURE_4; }
    if( strcmp("lightcyan 1", name) == 0 ){ return LIGHTCYAN_1; }
    if( strcmp("lightcyan 2", name) == 0 ){ return LIGHTCYAN_2; }
    if( strcmp("lightcyan 3", name) == 0 ){ return LIGHTCYAN_3; }
    if( strcmp("lightcyan 4", name) == 0 ){ return LIGHTCYAN_4; }
    if( strcmp("paleturquoise 1", name) == 0 ){ return PALETURQUOISE_1; }
    if( strcmp("paleturquoise 2", name) == 0 ){ return PALETURQUOISE_2; }
    if( strcmp("paleturquoise 3", name) == 0 ){ return PALETURQUOISE_3; }
    if( strcmp("paleturquoise 4", name) == 0 ){ return PALETURQUOISE_4; }
    if( strcmp("darkslategray", name) == 0 ){ return DARKSLATEGRAY; }
    if( strcmp("darkslategray 1", name) == 0 ){ return DARKSLATEGRAY_1; }
    if( strcmp("darkslategray 2", name) == 0 ){ return DARKSLATEGRAY_2; }
    if( strcmp("darkslategray 3", name) == 0 ){ return DARKSLATEGRAY_3; }
    if( strcmp("darkslategray 4", name) == 0 ){ return DARKSLATEGRAY_4; }
    if( strcmp("cyan", name) == 0 ){ return CYAN; }
    if( strcmp("cyan 2", name) == 0 ){ return CYAN_2; }
    if( strcmp("cyan 3", name) == 0 ){ return CYAN_3; }
    if( strcmp("cyan 4", name) == 0 ){ return CYAN_4; }
    if( strcmp("teal", name) == 0 ){ return TEAL; }
    if( strcmp("mediumturquoise", name) == 0 ){ return MEDIUMTURQUOISE; }
    if( strcmp("lightseagreen", name) == 0 ){ return LIGHTSEAGREEN; }
    if( strcmp("manganeseblue", name) == 0 ){ return MANGANESEBLUE; }
    if( strcmp("turquoise", name) == 0 ){ return TURQUOISE; }
    if( strcmp("coldgrey", name) == 0 ){ return COLDGREY; }
    if( strcmp("turquoiseblue", name) == 0 ){ return TURQUOISEBLUE; }
    if( strcmp("aquamarine 1", name) == 0 ){ return AQUAMARINE_1; }
    if( strcmp("aquamarine 2", name) == 0 ){ return AQUAMARINE_2; }
    if( strcmp("aquamarine 3", name) == 0 ){ return AQUAMARINE_3; }
    if( strcmp("aquamarine 4", name) == 0 ){ return AQUAMARINE_4; }
    if( strcmp("mediumspringgreen", name) == 0 ){ return MEDIUMSPRINGGREEN; }
    if( strcmp("mintcream", name) == 0 ){ return MINTCREAM; }
    if( strcmp("springgreen", name) == 0 ){ return SPRINGGREEN; }
    if( strcmp("springgreen 1", name) == 0 ){ return SPRINGGREEN_1; }
    if( strcmp("springgreen 2", name) == 0 ){ return SPRINGGREEN_2; }
    if( strcmp("springgreen 3", name) == 0 ){ return SPRINGGREEN_3; }
    if( strcmp("mediumseagreen", name) == 0 ){ return MEDIUMSEAGREEN; }
    if( strcmp("seagreen 1", name) == 0 ){ return SEAGREEN_1; }
    if( strcmp("seagreen 2", name) == 0 ){ return SEAGREEN_2; }
    if( strcmp("seagreen 3", name) == 0 ){ return SEAGREEN_3; }
    if( strcmp("seagreen 4", name) == 0 ){ return SEAGREEN_4; }
    if( strcmp("emeraldgreen", name) == 0 ){ return EMERALDGREEN; }
    if( strcmp("mint", name) == 0 ){ return MINT; }
    if( strcmp("cobaltgreen", name) == 0 ){ return COBALTGREEN; }
    if( strcmp("honeydew 1", name) == 0 ){ return HONEYDEW_1; }
    if( strcmp("honeydew 2", name) == 0 ){ return HONEYDEW_2; }
    if( strcmp("honeydew 3", name) == 0 ){ return HONEYDEW_3; }
    if( strcmp("honeydew 4", name) == 0 ){ return HONEYDEW_4; }
    if( strcmp("darkseagreen", name) == 0 ){ return DARKSEAGREEN; }
    if( strcmp("darkseagreen 1", name) == 0 ){ return DARKSEAGREEN_1; }
    if( strcmp("darkseagreen 2", name) == 0 ){ return DARKSEAGREEN_2; }
    if( strcmp("darkseagreen 3", name) == 0 ){ return DARKSEAGREEN_3; }
    if( strcmp("darkseagreen 4", name) == 0 ){ return DARKSEAGREEN_4; }
    if( strcmp("palegreen", name) == 0 ){ return PALEGREEN; }
    if( strcmp("palegreen 1", name) == 0 ){ return PALEGREEN_1; }
    if( strcmp("palegreen 2", name) == 0 ){ return PALEGREEN_2; }
    if( strcmp("palegreen 3", name) == 0 ){ return PALEGREEN_3; }
    if( strcmp("palegreen 4", name) == 0 ){ return PALEGREEN_4; }
    if( strcmp("limegreen", name) == 0 ){ return LIMEGREEN; }
    if( strcmp("forestgreen", name) == 0 ){ return FORESTGREEN; }
    if( strcmp("green 1", name) == 0 ){ return GREEN_1; }
    if( strcmp("green 2", name) == 0 ){ return GREEN_2; }
    if( strcmp("green 3", name) == 0 ){ return GREEN_3; }
    if( strcmp("green 4", name) == 0 ){ return GREEN_4; }
    if( strcmp("green", name) == 0 ){ return GREEN; }
    if( strcmp("darkgreen", name) == 0 ){ return DARKGREEN; }
    if( strcmp("sapgreen", name) == 0 ){ return SAPGREEN; }
    if( strcmp("lawngreen", name) == 0 ){ return LAWNGREEN; }
    if( strcmp("chartreuse 1", name) == 0 ){ return CHARTREUSE_1; }
    if( strcmp("chartreuse 2", name) == 0 ){ return CHARTREUSE_2; }
    if( strcmp("chartreuse 3", name) == 0 ){ return CHARTREUSE_3; }
    if( strcmp("chartreuse 4", name) == 0 ){ return CHARTREUSE_4; }
    if( strcmp("greenyellow", name) == 0 ){ return GREENYELLOW; }
    if( strcmp("darkolivegreen 1", name) == 0 ){ return DARKOLIVEGREEN_1; }
    if( strcmp("darkolivegreen 2", name) == 0 ){ return DARKOLIVEGREEN_2; }
    if( strcmp("darkolivegreen 3", name) == 0 ){ return DARKOLIVEGREEN_3; }
    if( strcmp("darkolivegreen 4", name) == 0 ){ return DARKOLIVEGREEN_4; }
    if( strcmp("darkolivegreen", name) == 0 ){ return DARKOLIVEGREEN; }
    if( strcmp("olivedrab", name) == 0 ){ return OLIVEDRAB; }
    if( strcmp("olivedrab 1", name) == 0 ){ return OLIVEDRAB_1; }
    if( strcmp("olivedrab 2", name) == 0 ){ return OLIVEDRAB_2; }
    if( strcmp("olivedrab 3", name) == 0 ){ return OLIVEDRAB_3; }
    if( strcmp("olivedrab 4", name) == 0 ){ return OLIVEDRAB_4; }
    if( strcmp("ivory 1", name) == 0 ){ return IVORY_1; }
    if( strcmp("ivory 2", name) == 0 ){ return IVORY_2; }
    if( strcmp("ivory 3", name) == 0 ){ return IVORY_3; }
    if( strcmp("ivory 4", name) == 0 ){ return IVORY_4; }
    if( strcmp("beige", name) == 0 ){ return BEIGE; }
    if( strcmp("lightyellow 1", name) == 0 ){ return LIGHTYELLOW_1; }
    if( strcmp("lightyellow 2", name) == 0 ){ return LIGHTYELLOW_2; }
    if( strcmp("lightyellow 3", name) == 0 ){ return LIGHTYELLOW_3; }
    if( strcmp("lightyellow 4", name) == 0 ){ return LIGHTYELLOW_4; }
    if( strcmp("lightgoldenrodyellow", name) == 0 ){ return LIGHTGOLDENRODYELLOW; }
    if( strcmp("yellow", name) == 0 ){ return YELLOW_1; }
    if( strcmp("yellow 1", name) == 0 ){ return YELLOW_1; }
    if( strcmp("yellow 2", name) == 0 ){ return YELLOW_2; }
    if( strcmp("yellow 3", name) == 0 ){ return YELLOW_3; }
    if( strcmp("yellow 4", name) == 0 ){ return YELLOW_4; }
    if( strcmp("warmgrey", name) == 0 ){ return WARMGREY; }
    if( strcmp("olive", name) == 0 ){ return OLIVE; }
    if( strcmp("darkkhaki", name) == 0 ){ return DARKKHAKI; }
    if( strcmp("khaki 1", name) == 0 ){ return KHAKI_1; }
    if( strcmp("khaki 2", name) == 0 ){ return KHAKI_2; }
    if( strcmp("khaki 3", name) == 0 ){ return KHAKI_3; }
    if( strcmp("khaki 4", name) == 0 ){ return KHAKI_4; }
    if( strcmp("khaki", name) == 0 ){ return KHAKI; }
    if( strcmp("palegoldenrod", name) == 0 ){ return PALEGOLDENROD; }
    if( strcmp("lemonchiffon 1", name) == 0 ){ return LEMONCHIFFON_1; }
    if( strcmp("lemonchiffon 2", name) == 0 ){ return LEMONCHIFFON_2; }
    if( strcmp("lemonchiffon 3", name) == 0 ){ return LEMONCHIFFON_3; }
    if( strcmp("lemonchiffon 4", name) == 0 ){ return LEMONCHIFFON_4; }
    if( strcmp("lightgoldenrod 1", name) == 0 ){ return LIGHTGOLDENROD_1; }
    if( strcmp("lightgoldenrod 2", name) == 0 ){ return LIGHTGOLDENROD_2; }
    if( strcmp("lightgoldenrod 3", name) == 0 ){ return LIGHTGOLDENROD_3; }
    if( strcmp("lightgoldenrod 4", name) == 0 ){ return LIGHTGOLDENROD_4; }
    if( strcmp("banana", name) == 0 ){ return BANANA; }
    if( strcmp("gold 1", name) == 0 ){ return GOLD_1; }
    if( strcmp("gold 2", name) == 0 ){ return GOLD_2; }
    if( strcmp("gold 3", name) == 0 ){ return GOLD_3; }
    if( strcmp("gold 4", name) == 0 ){ return GOLD_4; }
    if( strcmp("cornsilk 1", name) == 0 ){ return CORNSILK_1; }
    if( strcmp("cornsilk 2", name) == 0 ){ return CORNSILK_2; }
    if( strcmp("cornsilk 3", name) == 0 ){ return CORNSILK_3; }
    if( strcmp("cornsilk 4", name) == 0 ){ return CORNSILK_4; }
    if( strcmp("goldenrod", name) == 0 ){ return GOLDENROD; }
    if( strcmp("goldenrod 1", name) == 0 ){ return GOLDENROD_1; }
    if( strcmp("goldenrod 2", name) == 0 ){ return GOLDENROD_2; }
    if( strcmp("goldenrod 3", name) == 0 ){ return GOLDENROD_3; }
    if( strcmp("goldenrod 4", name) == 0 ){ return GOLDENROD_4; }
    if( strcmp("darkgoldenrod", name) == 0 ){ return DARKGOLDENROD; }
    if( strcmp("darkgoldenrod 1", name) == 0 ){ return DARKGOLDENROD_1; }
    if( strcmp("darkgoldenrod 2", name) == 0 ){ return DARKGOLDENROD_2; }
    if( strcmp("darkgoldenrod 3", name) == 0 ){ return DARKGOLDENROD_3; }
    if( strcmp("darkgoldenrod 4", name) == 0 ){ return DARKGOLDENROD_4; }
    if( strcmp("orange 1", name) == 0 ){ return ORANGE_1; }
    if( strcmp("orange 2", name) == 0 ){ return ORANGE_2; }
    if( strcmp("orange 3", name) == 0 ){ return ORANGE_3; }
    if( strcmp("orange 4", name) == 0 ){ return ORANGE_4; }
    if( strcmp("floralwhite", name) == 0 ){ return FLORALWHITE; }
    if( strcmp("oldlace", name) == 0 ){ return OLDLACE; }
    if( strcmp("wheat", name) == 0 ){ return WHEAT; }
    if( strcmp("wheat 1", name) == 0 ){ return WHEAT_1; }
    if( strcmp("wheat 2", name) == 0 ){ return WHEAT_2; }
    if( strcmp("wheat 3", name) == 0 ){ return WHEAT_3; }
    if( strcmp("wheat 4", name) == 0 ){ return WHEAT_4; }
    if( strcmp("moccasin", name) == 0 ){ return MOCCASIN; }
    if( strcmp("papayawhip", name) == 0 ){ return PAPAYAWHIP; }
    if( strcmp("blanchedalmond", name) == 0 ){ return BLANCHEDALMOND; }
    if( strcmp("navajowhite 1", name) == 0 ){ return NAVAJOWHITE_1; }
    if( strcmp("navajowhite 2", name) == 0 ){ return NAVAJOWHITE_2; }
    if( strcmp("navajowhite 3", name) == 0 ){ return NAVAJOWHITE_3; }
    if( strcmp("navajowhite 4", name) == 0 ){ return NAVAJOWHITE_4; }
    if( strcmp("eggshell", name) == 0 ){ return EGGSHELL; }
    if( strcmp("tan", name) == 0 ){ return TAN; }
    if( strcmp("brick", name) == 0 ){ return BRICK; }
    if( strcmp("cadmiumyellow", name) == 0 ){ return CADMIUMYELLOW; }
    if( strcmp("antiquewhite", name) == 0 ){ return ANTIQUEWHITE; }
    if( strcmp("antiquewhite 1", name) == 0 ){ return ANTIQUEWHITE_1; }
    if( strcmp("antiquewhite 2", name) == 0 ){ return ANTIQUEWHITE_2; }
    if( strcmp("antiquewhite 3", name) == 0 ){ return ANTIQUEWHITE_3; }
    if( strcmp("antiquewhite 4", name) == 0 ){ return ANTIQUEWHITE_4; }
    if( strcmp("burlywood", name) == 0 ){ return BURLYWOOD; }
    if( strcmp("burlywood 1", name) == 0 ){ return BURLYWOOD_1; }
    if( strcmp("burlywood 2", name) == 0 ){ return BURLYWOOD_2; }
    if( strcmp("burlywood 3", name) == 0 ){ return BURLYWOOD_3; }
    if( strcmp("burlywood 4", name) == 0 ){ return BURLYWOOD_4; }
    if( strcmp("bisque 1", name) == 0 ){ return BISQUE_1; }
    if( strcmp("bisque 2", name) == 0 ){ return BISQUE_2; }
    if( strcmp("bisque 3", name) == 0 ){ return BISQUE_3; }
    if( strcmp("bisque 4", name) == 0 ){ return BISQUE_4; }
    if( strcmp("melon", name) == 0 ){ return MELON; }
    if( strcmp("carrot", name) == 0 ){ return CARROT; }
    if( strcmp("darkorange", name) == 0 ){ return DARKORANGE; }
    if( strcmp("darkorange 1", name) == 0 ){ return DARKORANGE_1; }
    if( strcmp("darkorange 2", name) == 0 ){ return DARKORANGE_2; }
    if( strcmp("darkorange 3", name) == 0 ){ return DARKORANGE_3; }
    if( strcmp("darkorange 4", name) == 0 ){ return DARKORANGE_4; }
    if( strcmp("orange", name) == 0 ){ return ORANGE; }
    if( strcmp("tan 1", name) == 0 ){ return TAN_1; }
    if( strcmp("tan 2", name) == 0 ){ return TAN_2; }
    if( strcmp("tan 3", name) == 0 ){ return TAN_3; }
    if( strcmp("tan 4", name) == 0 ){ return TAN_4; }
    if( strcmp("linen", name) == 0 ){ return LINEN; }
    if( strcmp("peachpuff 1", name) == 0 ){ return PEACHPUFF_1; }
    if( strcmp("peachpuff 2", name) == 0 ){ return PEACHPUFF_2; }
    if( strcmp("peachpuff 3", name) == 0 ){ return PEACHPUFF_3; }
    if( strcmp("peachpuff 4", name) == 0 ){ return PEACHPUFF_4; }
    if( strcmp("seashell 1", name) == 0 ){ return SEASHELL_1; }
    if( strcmp("seashell 2", name) == 0 ){ return SEASHELL_2; }
    if( strcmp("seashell 3", name) == 0 ){ return SEASHELL_3; }
    if( strcmp("seashell 4", name) == 0 ){ return SEASHELL_4; }
    if( strcmp("sandybrown", name) == 0 ){ return SANDYBROWN; }
    if( strcmp("rawsienna", name) == 0 ){ return RAWSIENNA; }
    if( strcmp("chocolate", name) == 0 ){ return CHOCOLATE; }
    if( strcmp("chocolate 1", name) == 0 ){ return CHOCOLATE_1; }
    if( strcmp("chocolate 2", name) == 0 ){ return CHOCOLATE_2; }
    if( strcmp("chocolate 3", name) == 0 ){ return CHOCOLATE_3; }
    if( strcmp("chocolate 4", name) == 0 ){ return CHOCOLATE_4; }
    if( strcmp("ivoryblack", name) == 0 ){ return IVORYBLACK; }
    if( strcmp("flesh", name) == 0 ){ return FLESH; }
    if( strcmp("cadmiumorange", name) == 0 ){ return CADMIUMORANGE; }
    if( strcmp("burntsienna", name) == 0 ){ return BURNTSIENNA; }
    if( strcmp("sienna", name) == 0 ){ return SIENNA; }
    if( strcmp("sienna 1", name) == 0 ){ return SIENNA_1; }
    if( strcmp("sienna 2", name) == 0 ){ return SIENNA_2; }
    if( strcmp("sienna 3", name) == 0 ){ return SIENNA_3; }
    if( strcmp("sienna 4", name) == 0 ){ return SIENNA_4; }
    if( strcmp("lightsalmon 1", name) == 0 ){ return LIGHTSALMON_1; }
    if( strcmp("lightsalmon 2", name) == 0 ){ return LIGHTSALMON_2; }
    if( strcmp("lightsalmon 3", name) == 0 ){ return LIGHTSALMON_3; }
    if( strcmp("lightsalmon 4", name) == 0 ){ return LIGHTSALMON_4; }
    if( strcmp("coral", name) == 0 ){ return CORAL; }
    if( strcmp("orangered 1", name) == 0 ){ return ORANGERED_1; }
    if( strcmp("orangered 2", name) == 0 ){ return ORANGERED_2; }
    if( strcmp("orangered 3", name) == 0 ){ return ORANGERED_3; }
    if( strcmp("orangered 4", name) == 0 ){ return ORANGERED_4; }
    if( strcmp("sepia", name) == 0 ){ return SEPIA; }
    if( strcmp("darksalmon", name) == 0 ){ return DARKSALMON; }
    if( strcmp("salmon 1", name) == 0 ){ return SALMON_1; }
    if( strcmp("salmon 2", name) == 0 ){ return SALMON_2; }
    if( strcmp("salmon 3", name) == 0 ){ return SALMON_3; }
    if( strcmp("salmon 4", name) == 0 ){ return SALMON_4; }
    if( strcmp("coral 1", name) == 0 ){ return CORAL_1; }
    if( strcmp("coral 2", name) == 0 ){ return CORAL_2; }
    if( strcmp("coral 3", name) == 0 ){ return CORAL_3; }
    if( strcmp("coral 4", name) == 0 ){ return CORAL_4; }
    if( strcmp("burntumber", name) == 0 ){ return BURNTUMBER; }
    if( strcmp("tomato 1", name) == 0 ){ return TOMATO_1; }
    if( strcmp("tomato 2", name) == 0 ){ return TOMATO_2; }
    if( strcmp("tomato 3", name) == 0 ){ return TOMATO_3; }
    if( strcmp("tomato 4", name) == 0 ){ return TOMATO_4; }
    if( strcmp("salmon", name) == 0 ){ return SALMON; }
    if( strcmp("mistyrose 1", name) == 0 ){ return MISTYROSE_1; }
    if( strcmp("mistyrose 2", name) == 0 ){ return MISTYROSE_2; }
    if( strcmp("mistyrose 3", name) == 0 ){ return MISTYROSE_3; }
    if( strcmp("mistyrose 4", name) == 0 ){ return MISTYROSE_4; }
    if( strcmp("snow 1", name) == 0 ){ return SNOW_1; }
    if( strcmp("snow 2", name) == 0 ){ return SNOW_2; }
    if( strcmp("snow 3", name) == 0 ){ return SNOW_3; }
    if( strcmp("snow 4", name) == 0 ){ return SNOW_4; }
    if( strcmp("rosybrown", name) == 0 ){ return ROSYBROWN; }
    if( strcmp("rosybrown 1", name) == 0 ){ return ROSYBROWN_1; }
    if( strcmp("rosybrown 2", name) == 0 ){ return ROSYBROWN_2; }
    if( strcmp("rosybrown 3", name) == 0 ){ return ROSYBROWN_3; }
    if( strcmp("rosybrown 4", name) == 0 ){ return ROSYBROWN_4; }
    if( strcmp("lightcoral", name) == 0 ){ return LIGHTCORAL; }
    if( strcmp("indianred", name) == 0 ){ return INDIANRED; }
    if( strcmp("indianred 1", name) == 0 ){ return INDIANRED_1; }
    if( strcmp("indianred 2", name) == 0 ){ return INDIANRED_2; }
    if( strcmp("indianred 4", name) == 0 ){ return INDIANRED_4; }
    if( strcmp("indianred 3", name) == 0 ){ return INDIANRED_3; }
    if( strcmp("brown", name) == 0 ){ return BROWN; }
    if( strcmp("brown 1", name) == 0 ){ return BROWN_1; }
    if( strcmp("brown 2", name) == 0 ){ return BROWN_2; }
    if( strcmp("brown 3", name) == 0 ){ return BROWN_3; }
    if( strcmp("brown 4", name) == 0 ){ return BROWN_4; }
    if( strcmp("firebrick", name) == 0 ){ return FIREBRICK; }
    if( strcmp("firebrick 1", name) == 0 ){ return FIREBRICK_1; }
    if( strcmp("firebrick 2", name) == 0 ){ return FIREBRICK_2; }
    if( strcmp("firebrick 3", name) == 0 ){ return FIREBRICK_3; }
    if( strcmp("firebrick 4", name) == 0 ){ return FIREBRICK_4; }
    if( strcmp("red", name) == 0 ){ return RED_1; }
    if( strcmp("red 1", name) == 0 ){ return RED_1; }
    if( strcmp("red 2", name) == 0 ){ return RED_2; }
    if( strcmp("red 3", name) == 0 ){ return RED_3; }
    if( strcmp("red 4", name) == 0 ){ return RED_4; }
    if( strcmp("maroon", name) == 0 ){ return MAROON; }
    if( strcmp("sgi beet", name) == 0 ){ return SGI_BEET; }
    if( strcmp("sgi slateblue", name) == 0 ){ return SGI_SLATEBLUE; }
    if( strcmp("sgi lightblue", name) == 0 ){ return SGI_LIGHTBLUE; }
    if( strcmp("sgi teal", name) == 0 ){ return SGI_TEAL; }
    if( strcmp("sgi chartreuse", name) == 0 ){ return SGI_CHARTREUSE; }
    if( strcmp("sgi olivedrab", name) == 0 ){ return SGI_OLIVEDRAB; }
    if( strcmp("sgi brightgray", name) == 0 ){ return SGI_BRIGHTGRAY; }
    if( strcmp("sgi salmon", name) == 0 ){ return SGI_SALMON; }
    if( strcmp("sgi darkgray", name) == 0 ){ return SGI_DARKGRAY; }
    if( strcmp("sgi gray 12", name) == 0 ){ return SGI_GRAY_12; }
    if( strcmp("sgi gray 16", name) == 0 ){ return SGI_GRAY_16; }
    if( strcmp("sgi gray 32", name) == 0 ){ return SGI_GRAY_32; }
    if( strcmp("sgi gray 36", name) == 0 ){ return SGI_GRAY_36; }
    if( strcmp("sgi gray 52", name) == 0 ){ return SGI_GRAY_52; }
    if( strcmp("sgi gray 56", name) == 0 ){ return SGI_GRAY_56; }
    if( strcmp("sgi lightgray", name) == 0 ){ return SGI_LIGHTGRAY; }
    if( strcmp("sgi gray 72", name) == 0 ){ return SGI_GRAY_72; }
    if( strcmp("sgi gray 76", name) == 0 ){ return SGI_GRAY_76; }
    if( strcmp("sgi gray 92", name) == 0 ){ return SGI_GRAY_92; }
    if( strcmp("sgi gray 96", name) == 0 ){ return SGI_GRAY_96; }
    if( strcmp("white", name) == 0 ){ return WHITE; }
    if( strcmp("white smoke", name) == 0 ){ return WHITE_SMOKE; }
    if( strcmp("gainsboro", name) == 0 ){ return GAINSBORO; }
    if( strcmp("lightgrey", name) == 0 ){ return LIGHTGREY; }
    if( strcmp("silver", name) == 0 ){ return SILVER; }
    if( strcmp("darkgray", name) == 0 ){ return DARKGRAY; }
    if( strcmp("gray", name) == 0 ){ return GRAY; }
    if( strcmp("black", name) == 0 ){ return BLACK; }
    if( strcmp("gray 99", name) == 0 ){ return GRAY_99; }
    if( strcmp("gray 98", name) == 0 ){ return GRAY_98; }
    if( strcmp("gray 97", name) == 0 ){ return GRAY_97; }
    if( strcmp("gray 95", name) == 0 ){ return GRAY_95; }
    if( strcmp("gray 94", name) == 0 ){ return GRAY_94; }
    if( strcmp("gray 93", name) == 0 ){ return GRAY_93; }
    if( strcmp("gray 92", name) == 0 ){ return GRAY_92; }
    if( strcmp("gray 91", name) == 0 ){ return GRAY_91; }
    if( strcmp("gray 90", name) == 0 ){ return GRAY_90; }
    if( strcmp("gray 89", name) == 0 ){ return GRAY_89; }
    if( strcmp("gray 88", name) == 0 ){ return GRAY_88; }
    if( strcmp("gray 87", name) == 0 ){ return GRAY_87; }
    if( strcmp("gray 86", name) == 0 ){ return GRAY_86; }
    if( strcmp("gray 85", name) == 0 ){ return GRAY_85; }
    if( strcmp("gray 84", name) == 0 ){ return GRAY_84; }
    if( strcmp("gray 83", name) == 0 ){ return GRAY_83; }
    if( strcmp("gray 82", name) == 0 ){ return GRAY_82; }
    if( strcmp("gray 81", name) == 0 ){ return GRAY_81; }
    if( strcmp("gray 80", name) == 0 ){ return GRAY_80; }
    if( strcmp("gray 79", name) == 0 ){ return GRAY_79; }
    if( strcmp("gray 78", name) == 0 ){ return GRAY_78; }
    if( strcmp("gray 77", name) == 0 ){ return GRAY_77; }
    if( strcmp("gray 76", name) == 0 ){ return GRAY_76; }
    if( strcmp("gray 75", name) == 0 ){ return GRAY_75; }
    if( strcmp("gray 74", name) == 0 ){ return GRAY_74; }
    if( strcmp("gray 73", name) == 0 ){ return GRAY_73; }
    if( strcmp("gray 72", name) == 0 ){ return GRAY_72; }
    if( strcmp("gray 71", name) == 0 ){ return GRAY_71; }
    if( strcmp("gray 70", name) == 0 ){ return GRAY_70; }
    if( strcmp("gray 69", name) == 0 ){ return GRAY_69; }
    if( strcmp("gray 68", name) == 0 ){ return GRAY_68; }
    if( strcmp("gray 67", name) == 0 ){ return GRAY_67; }
    if( strcmp("gray 66", name) == 0 ){ return GRAY_66; }
    if( strcmp("gray 65", name) == 0 ){ return GRAY_65; }
    if( strcmp("gray 64", name) == 0 ){ return GRAY_64; }
    if( strcmp("gray 63", name) == 0 ){ return GRAY_63; }
    if( strcmp("gray 62", name) == 0 ){ return GRAY_62; }
    if( strcmp("gray 61", name) == 0 ){ return GRAY_61; }
    if( strcmp("gray 60", name) == 0 ){ return GRAY_60; }
    if( strcmp("gray 59", name) == 0 ){ return GRAY_59; }
    if( strcmp("gray 58", name) == 0 ){ return GRAY_58; }
    if( strcmp("gray 57", name) == 0 ){ return GRAY_57; }
    if( strcmp("gray 56", name) == 0 ){ return GRAY_56; }
    if( strcmp("gray 55", name) == 0 ){ return GRAY_55; }
    if( strcmp("gray 54", name) == 0 ){ return GRAY_54; }
    if( strcmp("gray 53", name) == 0 ){ return GRAY_53; }
    if( strcmp("gray 52", name) == 0 ){ return GRAY_52; }
    if( strcmp("gray 51", name) == 0 ){ return GRAY_51; }
    if( strcmp("gray 50", name) == 0 ){ return GRAY_50; }
    if( strcmp("gray 49", name) == 0 ){ return GRAY_49; }
    if( strcmp("gray 48", name) == 0 ){ return GRAY_48; }
    if( strcmp("gray 47", name) == 0 ){ return GRAY_47; }
    if( strcmp("gray 46", name) == 0 ){ return GRAY_46; }
    if( strcmp("gray 45", name) == 0 ){ return GRAY_45; }
    if( strcmp("gray 44", name) == 0 ){ return GRAY_44; }
    if( strcmp("gray 43", name) == 0 ){ return GRAY_43; }
    if( strcmp("gray 42", name) == 0 ){ return GRAY_42; }
    if( strcmp("dimgray", name) == 0 ){ return DIMGRAY; }
    if( strcmp("gray 40", name) == 0 ){ return GRAY_40; }
    if( strcmp("gray 39", name) == 0 ){ return GRAY_39; }
    if( strcmp("gray 38", name) == 0 ){ return GRAY_38; }
    if( strcmp("gray 37", name) == 0 ){ return GRAY_37; }
    if( strcmp("gray 36", name) == 0 ){ return GRAY_36; }
    if( strcmp("gray 35", name) == 0 ){ return GRAY_35; }
    if( strcmp("gray 34", name) == 0 ){ return GRAY_34; }
    if( strcmp("gray 33", name) == 0 ){ return GRAY_33; }
    if( strcmp("gray 32", name) == 0 ){ return GRAY_32; }
    if( strcmp("gray 31", name) == 0 ){ return GRAY_31; }
    if( strcmp("gray 30", name) == 0 ){ return GRAY_30; }
    if( strcmp("gray 29", name) == 0 ){ return GRAY_29; }
    if( strcmp("gray 28", name) == 0 ){ return GRAY_28; }
    if( strcmp("gray 27", name) == 0 ){ return GRAY_27; }
    if( strcmp("gray 26", name) == 0 ){ return GRAY_26; }
    if( strcmp("gray 25", name) == 0 ){ return GRAY_25; }
    if( strcmp("gray 24", name) == 0 ){ return GRAY_24; }
    if( strcmp("gray 23", name) == 0 ){ return GRAY_23; }
    if( strcmp("gray 22", name) == 0 ){ return GRAY_22; }
    if( strcmp("gray 21", name) == 0 ){ return GRAY_21; }
    if( strcmp("gray 20", name) == 0 ){ return GRAY_20; }
    if( strcmp("gray 19", name) == 0 ){ return GRAY_19; }
    if( strcmp("gray 18", name) == 0 ){ return GRAY_18; }
    if( strcmp("gray 17", name) == 0 ){ return GRAY_17; }
    if( strcmp("gray 16", name) == 0 ){ return GRAY_16; }
    if( strcmp("gray 15", name) == 0 ){ return GRAY_15; }
    if( strcmp("gray 14", name) == 0 ){ return GRAY_14; }
    if( strcmp("gray 13", name) == 0 ){ return GRAY_13; }
    if( strcmp("gray 12", name) == 0 ){ return GRAY_12; }
    if( strcmp("gray 11", name) == 0 ){ return GRAY_11; }
    if( strcmp("gray 10", name) == 0 ){ return GRAY_10; }
    if( strcmp("gray 9", name) == 0 ){ return GRAY_9; }
    if( strcmp("gray 8", name) == 0 ){ return GRAY_8; }
    if( strcmp("gray 7", name) == 0 ){ return GRAY_7; }
    if( strcmp("gray 6", name) == 0 ){ return GRAY_6; }
    if( strcmp("gray 5", name) == 0 ){ return GRAY_5; }
    if( strcmp("gray 4", name) == 0 ){ return GRAY_4; }
    if( strcmp("gray 3", name) == 0 ){ return GRAY_3; }
    if( strcmp("gray 2", name) == 0 ){ return GRAY_2; }
    if( strcmp("gray 1", name) == 0 ){ return GRAY_1; }

    return BLACK;
}

UtalCanvasColor get_color_by_name(char name[COLOR_NAME_LENGTH])
{
    ColorName colorName = __getColorByName(name);
    return __utalCanvasColors[ colorName ];
}


