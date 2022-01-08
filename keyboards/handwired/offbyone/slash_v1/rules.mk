# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
CUSTOM_MATRIX = lite

QUANTUM_LIB_SRC += i2c_master.c
