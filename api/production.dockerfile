# Get a Maven image to create the new build.
FROM maven:3.9.3-eclipse-temurin-20-alpine as build

# Copy both the source files and the pom.xml to the build stage.
COPY src /usr/src/app/src
COPY pom.xml /usr/src/app

# Create the executable JAR file.
RUN mvn -f /usr/src/app/pom.xml clean package

# Start a new stage with a lean image to use as a runtime container. This also
# means that we can choose to keep only the JAR file from the build stage so
# that we can keep a smaller image.
FROM eclipse-temurin:20-jre-alpine as runtime

# Copy only the executable from the build stage to the runtime stage.
COPY --from=build /usr/src/app/target/api-0.0.1-SNAPSHOT.jar /executable.jar

# Run the executable..
ENTRYPOINT ["java", "-jar", "/executable.jar"]