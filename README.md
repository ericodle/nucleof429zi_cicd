# Zephyr CICD TestApp
This is an educational repository for me to learn how to integrate GitHub Actions with a Zephyr project running on a nucleo f429zi board.

## Zephyr Setup

Before getting started, make sure you have a proper Zephyr development
environment. 
[Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html).

## Quick Setup

```shell
source ~/zephyrproject/.venv/bin/activate
west init -m https://github.com/ericodle/nucleof429zi_cicd --mr main my-workspace
cd my-workspace
west update
cd nucleof429zi_cicd
west build -b nucleo_f429zi app
west flash --runner openocd
```
Good luck.