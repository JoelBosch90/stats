package com.stats.api;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class PrivateController {

  @GetMapping("/private")
  public String getPrivate() {
    return "You got in!" + System.getenv("SUPERUSER_PASSWORD");
  }
}
