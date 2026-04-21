# Copyright(c) The Maintainers of Nanvix.
# Licensed under the MIT License.

# =============================================================================
# nanvix/newlib
#
# Lightweight runtime image with Nanvix NewLib C library for i686-nanvix.
#
# This image is built by the release workflow, which copies pre-built artifacts
# into docker-install/ before running `docker build`.
#
# Build (from release workflow):
#   docker build -t ghcr.io/nanvix/newlib:latest .
#
# Verify:
#   docker run --rm ghcr.io/nanvix/newlib:latest ls /opt/nanvix/i686-nanvix/lib/libc.a
# =============================================================================

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Install minimal runtime dependencies.
RUN apt-get update && apt-get install -y --no-install-recommends \
        ca-certificates \
        make \
    && rm -rf /var/lib/apt/lists/*

COPY docker-install/ /opt/nanvix/

ENV PATH="/opt/nanvix/bin:${PATH}"

# Smoke test — verify cross-compiler and newlib are present.
RUN i686-nanvix-gcc --version && \
    ls /opt/nanvix/i686-nanvix/lib/libc.a

LABEL org.opencontainers.image.source="https://github.com/nanvix/newlib" \
      org.opencontainers.image.description="Nanvix NewLib C library and cross-tools (Binutils + GCC stage0 + NewLib) for i686-nanvix"
