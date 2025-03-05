FROM debian:stable-slim

ARG ZEPHYR_SDK_VERSION=0.17.0
ARG ZEPHYR_SDK_INSTALL_DIR=/opt/toolchains/zephyr-sdk-${ZEPHYR_SDK_VERSION}
ARG ZEPHYR_SDK_TOOLCHAINS="-t arm-zephyr-eabi"

# OS dependencies and packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    device-tree-compiler \
    git \
    ninja-build \
    wget \
    xz-utils \
    build-essential && apt-get clean && rm -rf /var/lib/apt/lists/*

# Zephyr SDK
RUN export sdk_file_name="zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-$(uname -m)_minimal.tar.xz" \
  && wget -q "https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${ZEPHYR_SDK_VERSION}/${sdk_file_name}" \
  && mkdir -p ${ZEPHYR_SDK_INSTALL_DIR} \
  && tar -xvf ${sdk_file_name} -C ${ZEPHYR_SDK_INSTALL_DIR} --strip-components=1 \
  && ${ZEPHYR_SDK_INSTALL_DIR}/setup.sh -c ${ZEPHYR_SDK_TOOLCHAINS} \
  && rm ${sdk_file_name}

# Set Zephyr SDK path
ENV ZEPHYR_TOOLCHAIN_VARIANT=zephyr
ENV ZEPHYR_SDK_INSTALL_DIR=/opt/toolchains/zephyr-sdk-${ZEPHYR_SDK_VERSION}

# Python
ENV VIRTUAL_ENV=/opt/venv
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    python3-venv \
  && python3 -m venv $VIRTUAL_ENV \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# Install West using the pip from the virtual environment
RUN $VIRTUAL_ENV/bin/pip install --no-cache-dir wheel west

# Copy source code (example)
COPY ./app/src /app/src
