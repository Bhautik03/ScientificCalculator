FROM gcc:13

WORKDIR /app

# Install CMake and Google Test
RUN apt-get update && apt-get install -y \
    cmake \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# Build and install gtest manually (required on Debian)
RUN cd /usr/src/gtest && \
    cmake . && \
    make && \
    cp lib/*.a /usr/lib

# Copy project files
COPY . .

# Build project
RUN mkdir build && cd build && cmake .. && make

# Run calculator
CMD ["./build/calculator"]
