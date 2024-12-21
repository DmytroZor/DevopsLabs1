FROM debian:bullseye-slim AS build
RUN apt-get update && apt-get install -y g++ git
WORKDIR /app
RUN git clone https://github.com/DmytroZor/DevopsLabs1.git .
RUN git checkout branchHTTPserver

FROM alpine:latest 
RUN apk add --no-cache libstdc++ libc6-compat
WORKDIR /app
COPY --from=build /app/HTTPserver .
EXPOSE 8081
CMD ["./HTTPserver"]
