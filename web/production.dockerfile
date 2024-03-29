FROM node:20-alpine3.18 as build
WORKDIR /web
COPY package.json package-lock.json ./
RUN npm install
COPY . .
RUN npm run build

FROM nginx:1.23.3-alpine
COPY nginx.conf /etc/nginx/nginx.conf
COPY --from=build /web/dist/web /usr/share/nginx/html