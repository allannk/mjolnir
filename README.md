# Meson command
    $ meson build --cross-file cross-gcc.ini

# STM32 erase flash
Press reset shortly before
    # st-flash --reset --debug --connect-under-reset erase

# STM32 program chip
    $ sudo st-flash --reset write build/main.bin 0x8000000

# STM32 reset bricking
    # st-info --chipid --connect-under-reset
