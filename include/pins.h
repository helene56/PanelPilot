#ifndef PINS
#define PINS

#include "hardware/spi.h"

// const spi_inst_t* SPI_PORT = spi0;
#define SPI_PORT spi0
constexpr uint PIN_MISO {16};
constexpr uint PIN_CS   {17};
constexpr uint PIN_SCK  {18};
constexpr uint PIN_MOSI {19};
constexpr uint PIN_D_C  {22}; // data selection, command: 0, display data: 1
constexpr uint PIN_RST  {21};


#endif // PINS