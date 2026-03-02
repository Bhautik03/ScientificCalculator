# -------- Build Stage --------
FROM gcc:13 AS builder

WORKDIR /app

RUN apt-get update && apt-get install -y \
    cmake \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# Build Google Test
RUN cd /usr/src/gtest && \
    cmake . && \
    make && \
    cp lib/*.a /usr/lib

COPY . .

RUN rm -rf build
RUN cmake -S . -B build && \
    cmake --build build

# -------- Runtime Stage --------
FROM debian:bookworm-slim

WORKDIR /app

COPY --from=builder /app/build/calculator ./calculator

CMD ["./calculator"]