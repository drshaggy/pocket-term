#include "waveshare_eink.h"
#include "../../external/waveshare/EPD_4in26.h"
#include "../../external/waveshare/Config/DEV_Config.h"
#include "../../external/waveshare/GUI/GUI_Paint.h"
#include "../../external/waveshare/GUI/GUI_BMPfile.h"

#include <spdlog/spdlog.h>

WaveshareEink::WaveshareEink(bool verticalOrientation) : Display(verticalOrientation) {
    if(DEV_Module_Init() != 0) {
        spdlog::error("Failed to initlialise Waveshare Eink Display");
       //module doesnt load
    } else {
        EPD_4in26_Init();
        EPD_4in26_Clear();
        DEV_Delay_ms(500);

        UBYTE *BlackImage;
        UDOUBLE Imagesize = ((EPD_4in26_WIDTH % 8 == 0)? (EPD_4in26_WIDTH / 8 )
                             : (EPD_4in26_WIDTH / 8 + 1)) * EPD_4in26_HEIGHT;
        if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
             spdlog::error("Failed to apply for black memory...\r\n");
        }
        printf("Paint_NewImage\r\n");
        Paint_NewImage(BlackImage, EPD_4in26_WIDTH, EPD_4in26_HEIGHT, 0, WHITE);
        Paint_SelectImage(BlackImage);
        Paint_Clear(WHITE);
        Paint_DrawString_EN(10, 20, "Pocket Term", &Font12, WHITE, BLACK);
        EPD_4in26_Display(BlackImage);
        DEV_Delay_ms(2000);
        spdlog::info("Waveshare Eink Device initialised");
    }

}
