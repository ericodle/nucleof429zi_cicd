# Use Arch Linux as the base image
FROM archlinux

ARG ZEPHYR_SDK_VERSION=0.17.0
ARG ZEPHYR_SDK_INSTALL_DIR=/opt/toolchains/zephyr-sdk-${ZEPHYR_SDK_VERSION}
ARG ZEPHYR_SDK_TOOLCHAINS="-t arm-zephyr-eabi"

# Update system and install required dependencies
RUN pacman -Syu --noconfirm \
    base-devel \
    lib32-glibc \
    lib32-gcc-libs \
    gcc-multilib \
    cmake \
    dtc \  
    git \
    ninja \
    wget \
    xz \
    python \
    python-pip \
    python-virtualenv \
    python-setuptools \
    gcc \
    gcc-libs \
    qemu-system-x86 \
    qemu-system-arm \
    && pacman -Scc --noconfirm  # Clean package cache

# Set up Python virtual environment
ENV VIRTUAL_ENV=/opt/venv
RUN python -m venv $VIRTUAL_ENV && \
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
COPY ./test-containers/arch/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# Set the entrypoint
ENTRYPOINT ["/entrypoint.sh"]
