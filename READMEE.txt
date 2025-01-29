
Zephyr Project Guide
https://blog.golioth.io/how-to-build-your-zephyr-app-in-a-standalone-folder/

*****
*****
In this

Python venv activate
source ~/zephyrproject/.venv/bin/activate

Zephyr SDK & Toolchain path
source ~/zephyrproject/zephyr/zephyr-env.sh

Build Project
west build -p always -b nrf52840dk/nrf52840 ./