# @todo: implement.
FROM node:18.13 AS build

WORKDIR /client

COPY package.json ./
COPY package-lock.json ./
RUN npm install

COPY . ./
RUN npm run build

FROM nginx:1.23.3-alpine
COPY --from=build /client/public /usr/share/nginx/html
COPY ./nginx/default.conf /etc/nginx/conf.d/default.conf