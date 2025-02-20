# Tests for SOS

## How to build

```
mkdir nucleof429zi_cicd_app
cd nucleof429zi_cicd_app
pipenv shell
pip3 install west
west init -m https://github.com/ericodle/nucleof429zi_cicd
west update
pip3 install -r zephyr/scripts/requirements-base.txt
west build -b nucleo_f429zi nucleof429zi_cicd
```
