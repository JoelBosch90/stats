package com.stats.api;

import java.io.IOException;
import java.util.logging.Logger;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import org.springframework.lang.NonNull;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

@Component
public class MessageHandler extends TextWebSocketHandler {
  private static final Logger LOGGER = Logger.getLogger(MessageHandler.class.getName());
  private Map<String, WebSocketSession> sessions = new ConcurrentHashMap<>();

  @Override
  public void afterConnectionEstablished(@NonNull WebSocketSession session) throws Exception {
    LOGGER.info("Connection established: " + session.getId());

    sessions.put(session.getId(), session);
  }

  @Override
  public void handleTextMessage(@NonNull WebSocketSession session, @NonNull TextMessage message) {
    LOGGER.info("Received message: " + message.getPayload());
    // send(session, message);
  }

  public void directMessage(@NonNull String sessionId, @NonNull String message) {
    TextMessage textMessage = new TextMessage(message);
    WebSocketSession session = sessions.get(sessionId);

    send(session, textMessage);
  }

  public void broadcastMessage(@NonNull String message) {
    TextMessage textMessage = new TextMessage(message);

    for (WebSocketSession session : sessions.values()) {
      send(session, textMessage);
    }
  }

  private void send(WebSocketSession session, TextMessage message) {
    // Check if the session is still open before sending the message.
    if (message == null || session == null || !session.isOpen()) {
      return;
    }

    try {
      session.sendMessage(message);
    } catch (IOException exception) {
      LOGGER.severe("Failed to send message: " + exception.getMessage());
    }
  }
}