package com.stats.api;

import java.io.IOException;
import java.util.logging.Logger;
import org.springframework.lang.NonNull;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

public class EchoHandler extends TextWebSocketHandler {
  private static final Logger LOGGER = Logger.getLogger(EchoHandler.class.getName());

  @Override
  public void afterConnectionEstablished(@NonNull WebSocketSession session) throws Exception {
    session.sendMessage(new TextMessage("{ \"message\": \"Hello!\" }"));
  }

  @Override
  public void handleTextMessage(@NonNull WebSocketSession session, @NonNull TextMessage message) {
    LOGGER.info("Handling message: " + message.getPayload());
    try {
      session.sendMessage(message);
    } catch (IOException exception) {
      LOGGER.severe("Failed to send message: " + exception.getMessage());
    }
  }
}