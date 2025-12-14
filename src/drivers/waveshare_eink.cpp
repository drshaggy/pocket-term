#include "waveshare_eink.h"
#include "../../external/waveshare/EPD_4in26.h"
#include "../../external/waveshare/GUI/GUI_Paint.h"

#include <spdlog/spdlog.h>

WaveshareEink::WaveshareEink(bool verticalOrientation) : Display(verticalOrientation) {
    if(DEV_Module_Init() != 0) {
        spdlog::error("Failed to initlialise Waveshare Eink Display");
       //module doesnt load
    } else {
        m_cursor.x = 10;
        m_cursor.y = 20;
        m_width = EPD_4in26_WIDTH;
        m_height = EPD_4in26_HEIGHT;
        if (verticalOrientation) {
            m_rotation = ROTATE_90;
        } else {
            m_rotation = 0;
        }
        
        EPD_4in26_Init();
        EPD_4in26_Clear();
        DEV_Delay_ms(500);

        // Set framebuffer to display size
        m_displaySize = ((m_width % 8 == 0)? (m_width / 8 )
                                    : (m_width / 8 + 1)) * m_height;
        if((m_frameBuffer = (UBYTE *)malloc(m_displaySize)) == NULL) {
             spdlog::error("Failed to apply for black memory...\r\n");
        }
        printf("Paint_NewImage\r\n");
        Paint_NewImage(m_frameBuffer, m_width, m_height, 0, WHITE);
        Paint_SelectImage(m_frameBuffer);
        Paint_Clear(WHITE);
        DEV_Delay_ms(2000);
        println("Pocket Term");
        redraw();
        spdlog::info("Waveshare Eink Device initialised");
    }

}

int WaveshareEink::println(const std::string& text) {
    Paint_DrawString_EN(m_cursor.x, m_cursor.y, text.c_str(), &Font24, BLACK, WHITE);
    m_cursor.y += 20;
    return 0;
}

int WaveshareEink::print(const std::string& text) { 
    Paint_DrawString_EN(m_cursor.x, m_cursor.y, text.c_str(), &Font24, BLACK, WHITE);
    m_cursor.x = 17 * text.length();
    return 0;
    
}

int WaveshareEink::printHighlighted(const std::string& text) {
    Paint_DrawString_EN(m_cursor.x, m_cursor.y, text.c_str(), &Font24, WHITE, BLACK);
    m_cursor.y += 20;
    return 0;
}

int WaveshareEink::redraw() { 
    EPD_4in26_Display(m_frameBuffer);
    DEV_Delay_ms(2000);
    return 0;
}

int WaveshareEink::clear() {
    EPD_4in26_Clear();
    DEV_Delay_ms(500);
    return 0;
}
