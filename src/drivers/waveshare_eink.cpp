#include "waveshare_eink.h"
#include "../../external/waveshare/EPD_4in26.h"
#include "../../external/waveshare/GUI/GUI_Paint.h"

#include <spdlog/spdlog.h>

WaveshareEink::WaveshareEink(bool verticalOrientation) : Display(verticalOrientation) {
    if(DEV_Module_Init() != 0) {
        spdlog::error("Failed to initlialise Waveshare Eink Display");
       //module doesnt load
    } else {
        EPD_4in26_Init();
        EPD_4in26_Clear();
        DEV_Delay_ms(500);

        m_width = EPD_4in26_WIDTH;
        m_height = EPD_4in26_HEIGHT;
        // Set framebuffer to display size
        if (verticalOrientation) {
            m_rotation = ROTATE_90;
        } else {
            m_rotation = 0;
        }
        m_displaySize = ((m_width % 8 == 0)? (m_width / 8 )
                                    : (m_width / 8 + 1)) * m_height;
        if((m_frameBuffer = (UBYTE *)malloc(m_displaySize)) == NULL) {
             spdlog::error("Failed to apply for black memory...\r\n");
        }
        printf("Paint_NewImage\r\n");
        Paint_NewImage(m_frameBuffer, m_height, m_width, m_rotation, WHITE);
        Paint_SelectImage(m_frameBuffer);
        Paint_Clear(WHITE);
        Paint_DrawString_EN(10, 20, "Pocket Term", &Font24, BLACK, WHITE);
        EPD_4in26_Display(m_frameBuffer);
        DEV_Delay_ms(2000);
        spdlog::info("Waveshare Eink Device initialised");
    }

}
