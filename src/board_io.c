/*******************************************************************
 * @file board_io.c
 *
 * @brief Módulo de entradas/saídas sobre a API de GPIO do Zephyr.
 * @author Erick Mascarenhas (edlm@ic.ufal.br)
 * @version 0.1
 * @date 29/09/2026
 *******************************************************************/

#include <errno.h>
#include <stdbool.h>

#include <zephyr/drivers/gpio.h>

#include "board_io.h"

/* Pinos vêm do devicetree, nunca de constantes no código: trocar de placa
 * é trocar o devicetree, sem recompilar nenhuma decisão daqui. */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);

int io_init(void)
{
	int ret;

	if (!gpio_is_ready_dt(&led)) {
		return -ENODEV;
	}

	if (!gpio_is_ready_dt(&button)) {
		return -ENODEV;
	}

	/* INACTIVE respeita a polaridade declarada no devicetree: o LED nasce
	 * apagado mesmo que a placa o declare ativo em nível baixo. */
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return ret;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) {
		return ret;
	}

	return 0;
}

int led_set(bool on)
{
	return gpio_pin_set_dt(&led, on);
}

int button_read(void)
{
	return gpio_pin_get_dt(&button);
}
