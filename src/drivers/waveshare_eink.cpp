#include "waveshare_eink.h"
#include "../../external/waveshare/e-Paper/EPD_4in26.h"
#include "../../external/waveshare/Config/DEV_Config.h"
#include <spdlog/spdlog.h>

WaveshareEink::WaveshareEink(bool verticalOrientation) : Display(verticalOrientation) {
    if(DEV_Module_Init() != 0) {
        spdlog::error("Failed to initlialise Waveshare Eink Display");
       //module doesnt load
    } else {
        spdlog::info("Waveshare Eink Device initialised");
    }

}
