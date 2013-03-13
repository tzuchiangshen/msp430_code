#
# Makefile - top level make for fabooh examples
#
# includes.mk can be used to change MCU and BOARD variants
#

all:
	@make -C examples/basic all
	@make -C examples/led all
	@make -C examples/lcd all
	@make -C examples/math all
	@make -C examples/serial all
	@make -C examples/energia_ide_examples/blink all
	@make -C examples/energia_ide_examples/serial/ascii_table_extended all
	@make -C examples/spi all

clean:
	@make -C examples/basic clean
	@make -C examples/led clean
	@make -C examples/lcd clean
	@make -C examples/math clean
	@make -C examples/serial clean
	@make -C examples/energia_ide_examples/blink clean
	@make -C examples/energia_ide_examples/serial/ascii_table_extended clean
	@make -C examples/spi clean
	
