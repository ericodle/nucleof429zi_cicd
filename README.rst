SOS Blinker for Nucleo-144 F429ZIThis project is a simple Zephyr RTOS-based application that blinks an LED in an SOS pattern ("... --- ...") using a Nucleo-144 F429ZI board. The intent is to use this project to test CI/CD automation with GitHub Actions and a self-hosted runner.

test run:

```
west build -p always -b nucleo_f429zi /home/eo/nucleof429zi_cicd  && west flash --runner openocd
```