# Zephyr Example Application

<a href="https://github.com/zephyrproject-rtos/example-application/actions/workflows/build.yml?query=branch%3Amain">
  <img src="https://github.com/zephyrproject-rtos/example-application/actions/workflows/build.yml/badge.svg?event=push">
</a>
<a href="https://github.com/zephyrproject-rtos/example-application/actions/workflows/docs.yml?query=branch%3Amain">
  <img src="https://github.com/zephyrproject-rtos/example-application/actions/workflows/docs.yml/badge.svg?event=push">
</a>
<a href="https://zephyrproject-rtos.github.io/example-application">
  <img alt="Documentation" src="https://img.shields.io/badge/documentation-3D578C?logo=sphinx&logoColor=white">
</a>
<a href="https://zephyrproject-rtos.github.io/example-application/doxygen">
  <img alt="API Documentation" src="https://img.shields.io/badge/API-documentation-3D578C?logo=c&logoColor=white">
</a>

This repository contains a Zephyr example application. The main purpose of this
repository is to serve as a reference on how to structure Zephyr-based
applications. Some of the features demonstrated in this example are:

- Basic [Zephyr application][app_dev] skeleton
- [Zephyr workspace applications][workspace_app]
- [Zephyr modules][modules]
- [West T2 topology][west_t2]
- [Custom boards][board_porting]
- Custom [devicetree bindings][bindings]
- Out-of-tree [drivers][drivers]
- Out-of-tree libraries
- Example CI configuration (using GitHub Actions)
- Custom [west extension][west_ext]
- Custom [Zephyr runner][runner_ext]
- Doxygen and Sphinx documentation boilerplate

This repository is versioned together with the [Zephyr main tree][zephyr]. This
means that every time that Zephyr is tagged, this repository is tagged as well
with the same version number, and the [manifest](west.yml) entry for `zephyr`
will point to the corresponding Zephyr tag. For example, the `example-application`
v2.6.0 will point to Zephyr v2.6.0. Note that the `main` branch always
points to the development branch of Zephyr, also `main`.

[app_dev]: https://docs.zephyrproject.org/latest/develop/application/index.html
[workspace_app]: https://docs.zephyrproject.org/latest/develop/application/index.html#zephyr-workspace-app
[modules]: https://docs.zephyrproject.org/latest/develop/modules.html
[west_t2]: https://docs.zephyrproject.org/latest/develop/west/workspaces.html#west-t2
[board_porting]: https://docs.zephyrproject.org/latest/guides/porting/board_porting.html
[bindings]: https://docs.zephyrproject.org/latest/guides/dts/bindings.html
[drivers]: https://docs.zephyrproject.org/latest/reference/drivers/index.html
[zephyr]: https://github.com/zephyrproject-rtos/zephyr
[west_ext]: https://docs.zephyrproject.org/latest/develop/west/extensions.html
[runner_ext]: https://docs.zephyrproject.org/latest/develop/modules.html#external-runners

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
