# Use official GCC image
FROM gcc:13

# Set working directory
WORKDIR /app

# Install required dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# Build Google Test (required on Debian)
RUN cd /usr/src/gtest && \
    cmake . && \
    make && \
    cp lib/*.a /usr/lib

# Copy project files
COPY . .

# Remove any existing build artifacts (safety cleanup)
RUN rm -rf build

# Build the project using modern CMake
RUN cmake -S . -B build && \
    cmake --build build

# Default command (run calculator)
CMD ["./build/calculator"]