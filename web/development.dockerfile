FROM node:20-alpine3.18
WORKDIR /web
COPY package.json package-lock.json ./
RUN npm install
COPY . .
CMD ["npm", "start"]