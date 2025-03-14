#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19
#define PIN_D_C  15 // data selection, command: 0, display data: 1
// Data will be copied from src to dst
const char src[] = "Hello, world! (from DMA)";
char dst[count_of(src)];


char placeholder[1];

void write_to_display(const char command[], int d_c_state, int chan, dma_channel_config c)
{
    // to activate, drive cs low
    gpio_put(PIN_CS, 0);
    // set D/C
    gpio_put(PIN_D_C, d_c_state);
    // send the command
    dma_channel_configure(
        chan,              // Channel to be configured
        &c,                // The configuration we just created
        placeholder,       // store result from display readback
        command,           // command send to display
        count_of(command), // Number of transfers; in this case each is 1 byte.
        true               // Start immediately.
    );
    // to stop transmission drive high
    gpio_put(PIN_CS, 1);
    // for now lets just wait 3 us
    sleep_us(3);
}

void read_from_display(const char command[], char result[count_of(command)],int d_c_state, int chan, dma_channel_config c)
{
    // to activate, drive cs low
    gpio_put(PIN_CS, 0);
    // set D/C
    gpio_put(PIN_D_C, d_c_state);
    // send the command
    dma_channel_configure(
        chan,              // Channel to be configured
        &c,                // The configuration we just created
        result,            // store result from display readback
        command,           // command send to display
        count_of(command), // Number of transfers; in this case each is 1 byte.
        true               // Start immediately.
    );
    // to stop transmission drive high
    gpio_put(PIN_CS, 1);
    // display result
    puts(result);
    sleep_us(3);
}

int main()
{
    stdio_init_all();

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi
    
    // initialize D/C
    gpio_set_dir(PIN_D_C, GPIO_OUT);
    // Get a free channel, panic() if there are none
    int chan = dma_claim_unused_channel(true);
    
    // 8 bit transfers. Both read and write address increment after each
    // transfer (each pointing to a location in src or dst respectively).
    // No DREQ is selected, so the DMA transfers as fast as it can.
    
    dma_channel_config c = dma_channel_get_default_config(chan);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, true);
    
    dma_channel_configure(
        chan,          // Channel to be configured
        &c,            // The configuration we just created
        dst,           // The initial write address
        src,           // The initial read address
        count_of(src), // Number of transfers; in this case each is 1 byte.
        true           // Start immediately.
    );
    
    // We could choose to go and do something else whilst the DMA is doing its
    // thing. In this case the processor has nothing else to do, so we just
    // wait for the DMA to finish.
    dma_channel_wait_for_finish_blocking(chan);

    // allow usb time to connect
    sleep_ms(9000);

    // The DMA has now copied our text from the transmit buffer (src) to the
    // receive buffer (dst), so we can print it out from there.
    puts(dst);
    // 1. write a function to write to the slave (display)
    // 2. write a function to read from the slave to the master (rp2040)
    // 3. use one of the read functions to get a display id back send to usb serial monitor
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
