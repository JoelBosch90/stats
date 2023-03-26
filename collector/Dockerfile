# We want to use a small base image.
FROM alpine:3.17 AS base

# Update package index
RUN apk update

# Install runtime dependencies.
RUN apk add --no-cache sqlite-libs libsodium libstdc++ libgcc

# We use a separate build stage so that we end up with a smaller image.
FROM base AS build

# Install build dependencies.
RUN apk add --no-cache build-base sqlite-dev openssl-dev libsodium-dev

# Copy source code into a new directory and build the application there.
COPY . /collector
RUN cd /collector && make

# Start from the base again to create the final image.
FROM base

# Copy the binary for the application.
COPY --from=build /collector/binary/logs_collector /usr/local/bin/logs_collector

# Start the program.
ENTRYPOINT ["/usr/local/bin/logs_collector"]