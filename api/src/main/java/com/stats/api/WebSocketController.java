package com.stats.api;

import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.stereotype.Controller;

@Controller
public class WebSocketController {

  @MessageMapping("/data")
  @SendTo("/topic/records")
  public String sendData(String record) {
    // Process the record and send it to the "/topic/records" topic.
    return record;
  }
}