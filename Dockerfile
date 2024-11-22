# # Use the official Ubuntu image as a base
# FROM ubuntu:bionic

# # Install necessary packages
# RUN apt-get update && apt-get install -y \
#     git \
#     libncurses5-dev \
#     libncursesw5-dev \
#     hunspell \
#     hunspell-en-us \
#     make \
#     && apt-get clean

# # Install g++
# RUN apt-get install -y g++

# # Set environment variable to ensure dynamic libraries are found
# ENV LD_LIBRARY_PATH="/usr/lib/x86_64-linux-gnu:/usr/local/lib:$LD_LIBRARY_PATH"

# # Clone the Git repository
# RUN git clone https://github.com/TheSimmer101/wordle

# # Set the working directory
# WORKDIR /app

# # Copy local files to the working directory
# COPY . /app

# # Build the application
# #RUN make run

# # Run the application
# #CMD ["./your_program"]
# Use the official Ubuntu image as a base
FROM ubuntu:bionic

# Install necessary packages
RUN apt-get update && apt-get install -y \
    git \
    libncurses5-dev \
    libncursesw5-dev \
    hunspell \
    hunspell-en-us \
    libhunspell-dev \
    make \
    g++ \
    && apt-get clean

# Set environment variable to ensure dynamic libraries are found
ENV LD_LIBRARY_PATH="/usr/lib/x86_64-linux-gnu:/usr/local/lib:$LD_LIBRARY_PATH"

# Clone the Git repository
#RUN git clone https://github.com/TheSimmer101/wordle /app

COPY . .
# Set the working directory
WORKDIR /app

# Copy local files to the working directory
COPY . /app

# Create symbolic link for libncurses if necessary
RUN ln -s /usr/lib/x86_64-linux-gnu/libncurses.so.5 /usr/lib/x86_64-linux-gnu/libncurses.so.6 || true

# Ensure permissions and build the application
#RUN make

# Run the application
#CMD ["make", "run"]
