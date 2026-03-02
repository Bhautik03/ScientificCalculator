# Use official GCC image
FROM gcc:13

# Set working directory
WORKDIR /app

# Install required dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# Build Google Test
RUN cd /usr/src/gtest && \
    cmake . && \
    make && \
    cp lib/*.a /usr/lib

# Copy project files
COPY . .

# Build the project using modern CMake syntax
RUN cmake -S . -B build && \
    cmake --build build

# Default command (run calculator)
CMD ["./build/calculator"]