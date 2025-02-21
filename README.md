# Zephyr CICD TestApp
This is an educational repository for me to learn how to integrate GitHub Actions with a Zephyr project running on a nucleo f429zi board.

## Zephyr Setup

Before getting started, make sure you have a proper Zephyr development
environment. Follow the official
[Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html).

## Quick App Setup

```shell
source ~/zephyrproject/.venv/bin/activate
west init -m https://github.com/ericodle/nucleof429zi_cicd --mr main my-workspace
cd my-workspace
west update
cd nucleof429zi_cicd
west build -b nucleo_f429zi app
```

## Quick Testing/Documentation
```shell
west twister -T tests --integration
cd doc
pip install -r requirements.txt
doxygen
make html
```

## Step-by-Step Setup

Activate the zephyr virutal environment created during setup:

```shell
source ~/zephyrproject/.venv/bin/activate
```

Initialize my-workspace for the example-application (main branch):

```shell
west init -m https://github.com/ericodle/nucleof429zi_cicd --mr main my-workspace
cd my-workspace
```

Update Zephyr modules:

```shell
west update
```

To build the application, run the following command:

```shell
cd nucleof429zi_cicd
west build -b nucleo_f429zi app
```

Once you have built the application, run the following command to flash it to your board:

```shell
west flash --runner openocd
```

To execute Twister integration tests, run the following command:

```shell
west twister -T tests --integration
```

Documentation is provided for Doxygen and Sphinx. 
To build the documentation first change to the ``doc`` folder:

```shell
cd doc
```

Check if you have Doxygen installed:

```shell
sudo apt install doxygen
```

To install Sphinx, run:

```shell
pip install -r requirements.txt
```

Build API documentation (Doxygen) using the following command:

```shell
doxygen
```

The output will be stored in the ``_build_doxygen`` folder. You can browse it as a webpage from index.html.

Similarly, the Sphinx documentation (HTML) can be built using the following command:

```shell
make html
```

The output will be stored in the ``_build_sphinx`` folder. 
You can browse it as a webpage from index.html.
