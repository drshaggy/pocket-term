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
        if((m_prevBuffer = (UBYTE *)malloc(m_displaySize)) == NULL) {
             spdlog::error("Failed to apply for black memory...\r\n");
        }
        Paint_NewImage(m_frameBuffer, m_width, m_height, 0, WHITE);
        Paint_SelectImage(m_frameBuffer);
        Paint_Clear(WHITE);
        DEV_Delay_ms(2000);
        //println("Pocket Term");
        refresh();
        spdlog::info("Waveshare Eink Device initialised");
    }

}

int WaveshareEink::println(const std::string& text) {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    Paint_SelectImage(m_frameBuffer);
    Paint_DrawString_EN(m_cursor.x, m_cursor.y, text.c_str(), &Font24, BLACK, WHITE);
    m_cursor.y += 20;
    m_cursor.x = 10;
    return 0;
}

int WaveshareEink::print(const std::string& text) { 
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    Paint_SelectImage(m_frameBuffer);
    Paint_DrawString_EN(m_cursor.x, m_cursor.y, text.c_str(), &Font24, BLACK, WHITE);
    m_cursor.x += Font24.Width * text.length();
    return 0;
    
}

int WaveshareEink::printHighlighted(const std::string& text) {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    Paint_SelectImage(m_frameBuffer);
    Paint_DrawString_EN(m_cursor.x, m_cursor.y, text.c_str(), &Font24, WHITE, BLACK);
    m_cursor.y += Font24.Height;
    return 0;
}

void WaveshareEink::refresh() { 
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    if (memcmp(m_frameBuffer, m_prevBuffer, m_displaySize) == 0) {
        return;
    }
    EPD_4in26_Display(m_frameBuffer);
    DEV_Delay_ms(2000);
    memcpy(m_prevBuffer, m_frameBuffer, m_displaySize);
}

int WaveshareEink::clear() {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    Paint_SelectImage(m_frameBuffer);
    Paint_Clear(WHITE);
    EPD_4in26_Clear();
    DEV_Delay_ms(2000);
    return 0;
}

void WaveshareEink::drawText(const std::string& text) {
    spdlog::debug("draw Text at {} {}", m_cursor.x, m_cursor.y);
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    Paint_SelectImage(m_frameBuffer);
    Paint_DrawString_EN(10, 10, text.c_str(), &Font24, BLACK, WHITE);
    //m_cursor.x += Font24.Width * text.length();
}
