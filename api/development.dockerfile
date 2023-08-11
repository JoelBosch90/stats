# Get a Maven image to run the development build.
FROM maven:3.9.3-eclipse-temurin-20-alpine

# Copy source files into the working directory of the container.
WORKDIR /api
COPY . /api

# Create the executable JAR file.
RUN mvn install

# Run the api using Maven.
ENTRYPOINT ["mvn", "spring-boot:run"]