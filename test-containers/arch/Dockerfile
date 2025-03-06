# Use Debian as the base image
FROM debian:latest

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
    build-essential \
    gcc \
    g++ \
    python3 \
    python3-pip \
    python3-venv \
    python3-dev \
    libc6-dev \
    libnewlib-dev \
    g++-multilib \
    qemu-utils qemu-system-x86 qemu-system-gui \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Set up Python virtual environment
ENV VIRTUAL_ENV=/opt/venv
RUN python3 -m venv $VIRTUAL_ENV && \
    $VIRTUAL_ENV/bin/pip install --no-cache-dir wheel west

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
ENV PATH="${VIRTUAL_ENV}/bin:${PATH}"

VOLUME /usr/src
WORKDIR /usr/src

# Copy the entrypoint script and make it executable
COPY ./test-containers/debian/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# Set the entrypoint
ENTRYPOINT ["/entrypoint.sh"]

