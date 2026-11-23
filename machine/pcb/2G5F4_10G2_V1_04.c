#define MACHINE_CHIPSET RTL8372
#include "machine_defs.h"

/*
 * HYWS-SGT0204S on 2G5F4_10G2_V1.04 (RTL8372, 4 x 2.5G + 2 x SFP+).
 * flash_sio = 1: this board's flash is not usable in DIO mode.
 *
 * Known open issue: three LEDs on the front panel do not behave as the
 * stock firmware does; lamp layout was measured (see .led_mux) but not
 * fully resolved.
 */

__code const struct machine machine = {
	MACHINE_COMMON_SETTING,
	.n_sfp = 2,
	.log_to_phys_port = {0, 0, 0, 6, 1, 2, 3, 4, 5},
	.phys_to_log_port = {4, 5, 6, 7, 8, 3, 0, 0, 0},
	.is_sfp = {0, 0, 0, 2, 0, 0, 0, 0, 1},
	.sfp_port[0].pin_detect = GPIO38,
	.sfp_port[0].pin_los = GPIO37,
	.sfp_port[0].pin_tx_disable = GPIO_NA,
	.sfp_port[0].sds = 1,
	.sfp_port[0].i2c = I2CBUS( GPIO39_I2C_SDA4, GPIO40_I2C_SCL3_MDC1 ),
	.sfp_port[1].pin_detect = GPIO37,
	.sfp_port[1].pin_los = GPIO10_LED10,
	.sfp_port[1].pin_tx_disable = GPIO_NA,
	.sfp_port[1].sds = 0,
	.sfp_port[1].i2c = I2CBUS( GPIO41_I2C_SDA3_MDIO1, GPIO40_I2C_SCL3_MDC1 ),
	.reset_pin = GPIO_NA,
	.flash_sio = 1,
	.high_leds = { .mux = LED_27 | LED_28_SYS | LED_29, .enable = LED_27 | LED_28_SYS | LED_29 },
	/* logical 3 = SFP2, logical 4-7 = copper 1-4, logical 8 = SFP1 */
	.port_led_set = { 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	.led_sets = {
		{ /* copper: LED0 white 2.5G, LED1 blue 1G/100M/10M */
			LEDS_2G5 | LEDS_LINK | LEDS_ACT,
			LEDS_1G | LEDS_100M | LEDS_10M | LEDS_LINK | LEDS_ACT,
			0,
			0
		},
		{ /* SFP: one lamp per cage (pad 8 = SFP2, pad 26 = SFP1), both on
		     * LED0, so any link speed lights the lamp. */
			LEDS_10G | LEDS_1G | LEDS_2G5 | LEDS_LINK | LEDS_ACT,
			0,
			0,
			0
		},
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
	},
	.led_mux_custom = 1,
	/* Index is the DECIMAL pad number; each value is (logical << 2) | ledid.
	 * 0x3f disables the pad. Measured lamp layout on 2G5F4_10G2_V1.04:
	 *   pad  8 = SFP2 10G          pad  9 = 1 white
	 *   pad 10 = 1 blue            pad 12 = 2 white
	 *   pad 15 = 2 blue            pad 18 = 3 white
	 *   pad 21 = 3 blue            pad 24 = 4 white
	 *   pad 25 = 4 blue            pad 26 = SFP1
	 * That is all 10 lamps the pad table can drive: 8 copper plus one lamp
	 * per SFP cage (pad 8 = SFP2, pad 26 = SFP1). */
	.led_mux = {
		0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,	/* pads 0-7  */
		0x0c, 0x10, 0x11, 0x3f,					/* pads 8-11 */
		0x14, 0x3f, 0x3f, 0x15,					/* pads 12-15 */
		0x3f, 0x3f, 0x18, 0x3f,					/* pads 16-19 */
		0x3f, 0x19, 0x3f, 0x3f,					/* pads 20-23 */
		0x1c, 0x1d, 0x20, 0x3f					/* pads 24-27 */
	},
};

MACHINE_CUSTOM_INIT(
	reg_bit_set(RTL837X_REG_LED_GLB_IO_EN, 6);
)