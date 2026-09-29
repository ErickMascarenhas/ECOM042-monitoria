/*******************************************************************
 * @file main.c
 *
 * @brief Main file.
 * @author João Matheus Nascimento Dias (jmnd@ic.ufal.br)
 * @author José Félix de Oliveira Neto (jfon@ic.ufal.br)
 * @author Erick Mascarenhas (edlm@ic.ufal.br)
 * @version 0.1
 * @date 29/09/2026
 *******************************************************************/

#include <stddef.h>

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/gpio/gpio_emul.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

#include "board_io.h"

/* Estímulo externo: o mesmo nó de devicetree que board_io.c usa, mas aqui
 * no papel de "mundo lá fora" apertando o botão. Não entra em board_io.h
 * porque não é função da placa — em hardware real quem aciona é o dedo. */
static const struct gpio_dt_spec button_stimulus = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);

int main(void)
{
	static const int sequence[] = {0, 1, 0, 1};
	int ret;

	ret = io_init();
	if (ret < 0) {
		printk("io_init falhou (%d)\n", ret);
		return 0;
	}

	for (size_t i = 0; i < ARRAY_SIZE(sequence); i++) {
		int state;

		ret = gpio_emul_input_set_dt(&button_stimulus, sequence[i]);
		if (ret < 0) {
			printk("nao foi possivel simular o botao (%d)\n", ret);
			return 0;
		}

		state = button_read();
		if (state < 0) {
			printk("leitura do botao falhou (%d)\n", state);
			return 0;
		}

		/* O LED espelha o botão: o valor impresso para os dois é o
		 * mesmo por construção. */
		ret = led_set(state == 1);
		if (ret < 0) {
			printk("escrita no LED falhou (%d)\n", ret);
			return 0;
		}

		printk("Button: %d -> LED: %d\n", state, state);
	}

	return 0;
}
