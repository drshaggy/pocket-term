#include "waveshare_eink.h"
#include "../../external/waveshare/EPD_4in26.h"
#include "../../external/waveshare/GUI/GUI_Paint.h"

#include <spdlog/spdlog.h>

WaveshareEink::WaveshareEink(bool verticalOrientation) : Display(verticalOrientation) {
    if(DEV_Module_Init() != 0) {
        spdlog::error("Failed to initlialise Waveshare Eink Display");
       //module doesnt load
    } else {
        spdlog::info("Initiliasing Waveshare Eink Display...");
        m_cursor.x = 10;
        m_cursor.y = 20;
        m_width = EPD_4in26_WIDTH;
        m_height = EPD_4in26_HEIGHT;
        if (verticalOrientation) {
            m_rotation = ROTATE_90;
        } else {
            m_rotation = 0;
        }
        
        EPD_4in26_Init_Fast();
        EPD_4in26_Clear();

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
        //println("Pocket Term");
        refresh();
        m_ready = true;
        spdlog::info("Waveshare Eink Device initialised");
    }

}


void WaveshareEink::refresh() { 
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    if (memcmp(m_frameBuffer, m_prevBuffer, m_displaySize) == 0) {
        return;
    }
    EPD_4in26_Display_Fast(m_frameBuffer);
    memcpy(m_prevBuffer, m_frameBuffer, m_displaySize);
}

void WaveshareEink::refreshPartial() {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    if (memcmp(m_frameBuffer, m_prevBuffer, m_displaySize) == 0) {
        return;
    }
    EPD_4in26_Display(m_frameBuffer);
    memcpy(m_prevBuffer, m_frameBuffer, m_displaySize);
}

int WaveshareEink::clear() {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    Paint_SelectImage(m_frameBuffer);
    Paint_Clear(WHITE);
    //EPD_4in26_Clear();
    return 0;
}

void WaveshareEink::drawText(const std::string& text, const uint8_t& x, const uint8_t& y, bool isHighlighted) {
    spdlog::debug("draw Text at {} {}", x, y);
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    Paint_SelectImage(m_frameBuffer);
    if (isHighlighted) {
        Paint_DrawString_EN(x, y, text.c_str(), &Font24, WHITE, BLACK);
    } else {
        Paint_DrawString_EN(x, y, text.c_str(), &Font24, BLACK, WHITE);
    }
    //m_cursor.x += Font24.Width * text.length();
}

void WaveshareEink::drawBox(const uint8_t& width, const uint8_t& height, const bool hasBorder, const bool isFilled, const uint8_t& x, const uint8_t& y) {
    spdlog::debug("draw Box at {} {}", x, y);
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    Paint_SelectImage(m_frameBuffer);
    Paint_DrawRectangle(x, y, x + width, y + height, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
} 
