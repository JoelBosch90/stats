package com.stats.api;

import java.util.logging.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Service;
import org.springframework.lang.NonNull;

@Service
public class MessageService {
  private static final Logger LOGGER = Logger.getLogger(MessageService.class.getName());
  private final SimpMessagingTemplate template;

  @Autowired
  public MessageService(SimpMessagingTemplate template) {
    this.template = template;
  }

  public void sendMessageToTopic(String topic, @NonNull Object message) {
    try {
      template.convertAndSend("/topic/" + topic, message);
    } catch (Exception exception) {
      LOGGER.warning("Failed to send message to topic: " + topic + " - " + exception.getMessage());
    }
  }
}