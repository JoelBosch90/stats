package com.stats.api;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Service;
import org.springframework.lang.NonNull;

@Service
public class MessageService {

  private final SimpMessagingTemplate template;

  @Autowired
  public MessageService(SimpMessagingTemplate template) {
    this.template = template;
  }

  public void sendMessageToTopic(String topic, @NonNull Object message) {
    template.convertAndSend("/topic/" + topic, message);
  }
}